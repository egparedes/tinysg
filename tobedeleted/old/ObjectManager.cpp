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
 * ObjectManager.cpp
 *
 *  Created on: Sep 18, 2008
 *      Author: yamokosk
 */

#include <tinysg/ObjectManager.h>

#include <boost/foreach.hpp>

namespace TinySG
{

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{
	destroyAllCollections();

	QueryIterator iter = queries_.begin();
	for (; iter != queries_.end(); ++iter)
	{
		delete iter->second;
	}
	queries_.clear();
}

Object* ObjectManager::createObject(const std::string& name, const std::string& type, const PropertyCollection* params)
{
	// First get the collection
	ObjectCollection* collection = getCollection(type);

	// Check name not used
	if ( collection->objects.find(name) != collection->objects.end() )
	{
		std::ostringstream msg;
		msg << "An object of type \"" << type << "\" with the name \"" << name << "\" already exists.";
		SML_EXCEPT(Exception::ERR_DUPLICATE_ITEM, msg.str());
	}

	Object* obj = collection->factory->createInstance(name, this, params);
	collection->objects[obj->getName()] = obj;
	return obj;
}

void ObjectManager::destroyObject(const std::string& name, const std::string& type)
{
	ObjectCollection* collection = getCollection( type );

	// Find the object in question
	ObjectsIterator iter = collection->objects.find( name );
	if ( iter == collection->objects.end() )
	{
		std::ostringstream msg;
		msg << "The object of type \"" << type << "\" and \"" << name << "\" does not exist.";
		SML_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, msg.str());
	}

	// Factories control object creation and deletion
	collection->factory->destroyInstance( iter->second );

	// Now just remove this item from the collection
	collection->objects.erase( iter );
}

void ObjectManager::destroyObject( Object* obj )
{
	destroyObject( obj->getName(), obj->getType() );
}

void ObjectManager::destroyAllObjects( const std::string& type )
{
	ObjectCollection* collection = getCollection( type );

	// Iterate over all objects in the collection, destroying them one by one
	std::pair<std::string, Object*> pair;
	BOOST_FOREACH( pair, collection->objects )
	{
		collection->factory->destroyInstance( pair.second );
	}
	collection->objects.clear();
}

unsigned int ObjectManager::getNumberObjects(const std::string& type) const
{
	ObjectCollection* oc = getCollection(type);
	return (unsigned int)(oc->objects.size());
}

Object* ObjectManager::getObject(const std::string& name, const std::string& type) const
{
	ObjectCollection* collection = getCollection( type );

	ObjectsIterator iter = collection->objects.find( name );
	if ( iter == collection->objects.end() )
	{
		std::ostringstream msg;
		msg << "The object of type \"" << type << "\" and \"" << name << "\" does not exist.";
		SML_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, msg.str());
	}

	return iter->second;
}

void ObjectManager::registerFactory( ObjectFactory* fact )
{
	CollectionsIterator iter = objectCollections_.find( fact->getType() );

	if ( iter != objectCollections_.end() )
	{
		std::ostringstream msg;
		msg << "An object factory of type \"" << fact->getType() << "\" is already registered.";
		SML_EXCEPT(Exception::ERR_DUPLICATE_ITEM, msg.str());
	}

	ObjectCollection* collection = new ObjectCollection();
	collection->objectType = fact->getType();
	collection->factory = fact;
	objectCollections_[ collection->objectType ] = collection;
}

ObjectFactory* ObjectManager::getFactory( const std::string& type ) const
{
	ObjectCollection* collection = getCollection(type);
	return collection->factory;
}

void ObjectManager::destroyCollection( const std::string& type )
{
	CollectionsIterator iter = objectCollections_.find(type);

	if ( iter == objectCollections_.end() )
	{
		std::ostringstream msg;
		msg << "The object collection of type \"" << type << "\" does not exist.";
		SML_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, msg.str());
	}

	// Delete all the objects stored in the collection
	destroyAllObjects( iter->second->objectType );

	// Delete the factory.. we control these too.
	// NB: No we don't. These factory pointers are now controlled by the plugins that provide them.
	//delete iter->second->factory;

	// Finally erase this collection
	objectCollections_.erase( iter );
}

void ObjectManager::destroyCollection( ObjectCollection* collection )
{
	destroyCollection( collection->objectType );
}

void ObjectManager::destroyAllCollections()
{
	std::pair<std::string, ObjectCollection*> pair;
	BOOST_FOREACH( pair, objectCollections_ )
	{
		destroyAllObjects( pair.first );
		delete pair.second;
	}
	objectCollections_.clear();
}

ObjectManager::ObjectCollection* ObjectManager::getCollection( const std::string& type ) const
{
	CollectionsConstIterator iter = objectCollections_.find(type);

	if ( iter == objectCollections_.end() )
	{
		std::ostringstream msg;
		msg << "The object collection of type \"" << type << "\" does not exist.";
		SML_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, msg.str());
	}

	return iter->second;
}

QueryResult* ObjectManager::performQuery( const std::string queryName, const PropertyCollection* params )
{
	QueryIterator iter = queries_.find(queryName);

	if ( iter == queries_.end() )
	{
		std::ostringstream msg;
		msg << "The query \"" << queryName << "\" does not exist.";
		SML_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, msg.str());
	}

	Query* q = iter->second;
	return q->execute(this, params);
}

void ObjectManager::addQuery( Query* query )
{
	if ( queries_.find(query->getType()) != queries_.end() )
	{
		std::ostringstream msg;
		msg << "The query \"" << query->getType() << "\" is already registered with this object manager.";
		SML_EXCEPT(Exception::ERR_DUPLICATE_ITEM, msg.str());
	}

	queries_[query->getType()] = query;
}

void ObjectManager::save(TinySG::Archive& ar)
{
	// Predeclare the loop variable
	std::pair<std::string, ObjectCollection*> oc;

	BOOST_FOREACH( oc, objectCollections_ )
	{
		ar.createCollection((oc.second)->objectType, (oc.second)->objects.size());

		// Predeclare the loop variable
		std::pair<std::string, Object*> obj;

		BOOST_FOREACH( obj, (oc.second)->objects )
		{
			ar.serializeObject((oc.second)->objectType, *(obj.second));
		}
	}
}

void ObjectManager::load(TinySG::Archive& ar)
{
	/*for (unsigned int nc=0; nc < ar.size(); ++nc)
	{
		Archive::Collection* c = ar.getCollection( nc );

		if ( ( c->collectionType.compare("SceneNodes") != 0 ) && ( c->collectionType.compare("Plugins") != 0 ) )
		{
			for (unsigned int n=0; n < c->size(); ++n)
			{
				PropertyCollection pc = c->objects[n];
				createObject(pc.getValue("name"), pc.getValue("type"), &pc);
			}
		}
	}*/
	Archive::Collection* c = ar.getNextCollection();

	while ( c != NULL )
	{
		for (unsigned int n=0; n < c->size(); ++n)
		{
			PropertyCollection pc = c->objects[n];
			createObject(pc.getValue("name"), pc.getValue("type"), &pc);
		}

		c = ar.getNextCollection();
	}
}

}
