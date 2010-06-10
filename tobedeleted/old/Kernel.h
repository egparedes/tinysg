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
 * Kernel.h
 *
 *  Created on: Jul 23, 2008
 *      Author: yamokosk
 */

#ifndef KERNEL_H_
#define KERNEL_H_

// Logging
#include <log4cxx/logger.h>

// Plugin framework
#include <plugin_framework/Singleton.h>
#include <plugin_framework/PluginManager.h>

// Stuff from the object model
#include <api/Query.h>
#include <api/Archive.h>

// Internal includes
#include "Exception.h"
#include "Map.h"
#include "SceneGraph.h"

namespace tinysg
{

class Kernel : public Singleton<Kernel>
{
	static log4cxx::LoggerPtr logger;
public:
	Kernel();
	virtual ~Kernel();

	// Override standard Singleton retrieval.
	static Kernel& getSingleton(void);
	static Kernel* getSingletonPtr(void);

	void loadScene(const std::string& filename);
	void saveScene(const std::string& filename);

	void initialize();

	// Managers
	SceneGraph*	getSceneGraph() const {return graph_;}
	ObjectManager*	getEntityManager() const {return objMgr_;}
	const SceneGraph* getSceneManager() const {return graph_;}
	const ObjectManager* getMeshManager() const {return objMgr_;}

	// Register a new EntityFactory which will create new Entity instances of a particular type, as identified by the getType() method.
	void addObjectFactory (ObjectFactory *fact);
	// Get a EntityFactory for the given type.
	ObjectFactory* getObjectFactory (const std::string &typeName);

	// Register new queries with their respective managers
	void addSceneQuery(Query* query);
	void addObjectQuery(Query* query);

	// Plugins
	// Internal methods
	void loadPlugin(const std::string& libName);
	// Container for all externally loaded libraries (aka plugins)
	std::vector<DynamicallyLoadedLibrary*> libraryHandles_;
	// Internal method for registering loaded plugins
	void registerPlugin( Plugin* );

private:
	static int invokeService(const char* serviceName, void* serviceParams);

	PluginManager& pm;
	ObjectManager* createObjectManager() {};
	SceneGraph* createSceneGraph() {};

	SceneGraph*	graph_;
	ObjectManager* objMgr_;

	PluginInstanceMap	registeredPlugins_;
};

}

#endif /* ROOT_H_ */
