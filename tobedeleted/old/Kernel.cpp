/*************************************************************************
 * TinySG, Copyright (C) 2007, 2008  J.D. Yamokoski
 * All rights reserved.
 * Email: yamokosk at gmail dot com
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of the License,
 * or (at your option) any later version. The text of the GNU Lesser General
 * Public License is included with this library in the file LICENSE.TXT.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the file LICENSE.TXT for
 * more details.
 *
 *************************************************************************/
/*
 * Kernel.cpp
 *
 *  Created on: Jul 23, 2008
 *      Author: yamokosk
 */

#include "Kernel.h"
#include "SceneGraph.h"
#include "MovableObject.h"
#include "SceneFile.h"

#include <boost/foreach.hpp>

namespace TinySG
{

using namespace log4cxx;
LoggerPtr Kernel::logger(Logger::getLogger("Kernel"));

template<> Kernel* Singleton<Kernel>::ms_Singleton = 0;
Kernel* Kernel::getSingletonPtr(void)
{
	return ms_Singleton;
}
Kernel& Kernel::getSingleton(void)
{
	assert( ms_Singleton );  return ( *ms_Singleton );
}

Kernel::Kernel() :
	graph_(NULL),
	objMgr_(NULL)
{

}

Kernel::~Kernel()
{
	/* IMPORTANT: Order of operation is key.
	 * 	1. First notify plugins that they are getting deleted.
	 *  2. Free space allocated to the plugins.
	 *  3. Free space allocated to the dynamically loaded libraries.
	 */
	std::pair<std::string, Plugin*> plugin;
	BOOST_FOREACH( plugin, registeredPlugins_ )
	{
		(plugin.second)->unload();
		delete (plugin.second);
	}

	BOOST_FOREACH( DynamicallyLoadedLibrary* lib, libraryHandles_ )
	{
		delete lib;
	}

	if (graph_) delete graph_;
	if (objMgr_) delete objMgr_;
}

void Kernel::initialize()
{
	pm = PluginManager::getInstance();
	pm.getPlatformServices().invokeService = invokeService;
	pm.loadAll(Path::makeAbsolute(argv[1]));
	PluginManager::initializePlugin(StaticPlugin_InitPlugin);

	// Activate the battle manager
	BattleManager::getInstance().go();
}

int Kernel::invokeService(const char* serviceName, void* serviceParams)
{

}

void Kernel::loadScene(const std::string& filename)
{
	Archive ar; SceneFileReader sr;
	sr.load(filename, ar);

	// Load the scene graph
	graph_->load(ar);

	// Load the plugins
	Archive::Collection* collection = ar.getNextCollection();
	for (unsigned int n=0; n < collection->size(); ++n)
	{
		PropertyCollection pc = collection->objects[n];
		loadPlugin(pc.getValue("name"));
	}

	// Load the objects
	objMgr_->load(ar);
}

void Kernel::saveScene(const std::string& filename)
{
	Archive ar;

	// Save the scene graph
	graph_->save(ar);

	// Next record the loaded plugins
	ar.createCollection("Plugins", (unsigned int)libraryHandles_.size());
	BOOST_FOREACH( DynamicallyLoadedLibrary* lib, libraryHandles_ )
	{
		ar.serializeObject("Plugins", *lib);
	}

	// Finally save the objects
	objMgr_->save(ar);

	SceneFileWriter sw;
	sw.save(filename, ar);
}

void Kernel::addObjectFactory(ObjectFactory* fact)
{
	objMgr_->registerFactory( fact );
}

ObjectFactory* Kernel::getObjectFactory(const std::string& typeName)
{
	return objMgr_->getFactory( typeName );
}

void Kernel::addSceneQuery(Query* query)
{
	graph_->addQuery(query);
}

void Kernel::addObjectQuery(Query* query)
{
	objMgr_->addQuery(query);
}

void Kernel::loadPlugin(const std::string& libName)
{
	DynamicallyLoadedLibrary* lib = NULL;

	try {
		lib = new DynamicallyLoadedLibrary(libName);
		PluginFactoryPtr fact( dynamicallyLoadClass<PluginFactory,DriverFactoryMakerFunc>( *lib, "createPluginFactory" ) );
		Plugin* plugin = fact->createPlugin();

		registerPlugin(plugin);
	} catch (const ItemIdentityException& e) {
		// A plugin is being loaded twice!
		delete lib;

		// Log the problem
		LOG4CXX_ERROR(logger, "Plugin \"" << libName << "\" already loaded: " << e.what());
		return;
	} catch (const DynamicLoadException& e) {
		// Some other problem encountered. Possibly the library to load does not exist.
		if (lib != NULL) delete lib;

		// Log the problem
		LOG4CXX_ERROR(logger, "Plugin \"" << libName << "\" load failed: " << e.what());
		return;
	}

	// Save handle to loaded library
	libraryHandles_.push_back(lib);
}

void Kernel::registerPlugin( Plugin* p )
{
	std::string type = p->getType();
	// Check that we don't already have one of this type registered
	if ( registeredPlugins_.find( type ) != registeredPlugins_.end() )
	{
		SML_EXCEPT(Exception::ERR_DUPLICATE_ITEM, "Plugin type \"" + type + "\" already registered");
	}

	p->initialize();
	p->registerFactories(this);
	p->registerQueries(this);

	registeredPlugins_[type] = p;
}

}
