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
 * ObjectManager.h
 *
 *  Created on: Sep 18, 2008
 *      Author: yamokosk
 */

#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

// External
#include <string>
#include <boost/cast.hpp>

// Internal
#include <tinysg/Exception.h>
#include <tinysg/Object.h>
#include <tinysg/Query.h>
#include <tinysg/Map.h>
#include <tinysg/Archive.h>
#include <tinysg/Query.h>

namespace TinySG
{

class ObjectManager
{
public:
	typedef MAP<std::string, Object*> Objects;
	typedef Objects::iterator ObjectsIterator;
	typedef Objects::const_iterator ObjectsConstIterator;

	struct ObjectCollection
	{
		std::string objectType;
		ObjectFactory* factory;
		Objects objects;
	};

	typedef MAP<std::string, ObjectCollection*> Collections;
	typedef Collections::iterator CollectionsIterator;
	typedef Collections::const_iterator CollectionsConstIterator;

	typedef MAP<std::string, Query*> Queries;
	typedef Queries::iterator QueryIterator;

public:
	ObjectManager();
	virtual ~ObjectManager();

	// Object management
	Object* createObject(const std::string& name, const std::string& type, const PropertyCollection* params=NULL);
	void destroyObject(const std::string& name, const std::string& type);
	void destroyObject(Object* obj);
	void destroyAllObjects( const std::string& type );
	Object* getObject(const std::string& name, const std::string& type) const;
	unsigned int getNumberObjects(const std::string& type) const;

	// Factory management
	void registerFactory( ObjectFactory* obj );
	ObjectFactory* getFactory( const std::string& type ) const;

	// Collections management
	void destroyCollection( const std::string& type );
	void destroyCollection( ObjectCollection* collection );
	void destroyAllCollections();
	ObjectCollection* getCollection( const std::string& type ) const;

	// Load and save from an archive
	//virtual void save(TinySG::Archive& ar) const = 0;
	//virtual void load(const TinySG::Archive& ar, unsigned int version) = 0;

	// Query management
	QueryResult* performQuery( const std::string queryName, const PropertyCollection* params=0 );
	void addQuery( Query* query );

	// Support for casting to a desired derived class
	template <class T>
	T* createAndCastObject(const std::string& name, const std::string& type, const PropertyCollection* params=NULL)
	{
		Object* obj = createObject(name, type, params);
		return boost::polymorphic_downcast<T*>( obj );
	}
	template <class T>
	T* getAndCastObject(const std::string& name, const std::string& type) const
	{
		Object* obj = getObject(name, type);
		return boost::polymorphic_downcast<T*>( obj );
	}
	template <class T>
	T* getAndCastFactory( const std::string& type ) const
	{
		ObjectFactory* fact = getFactory(type);
		return boost::polymorphic_downcast<T*>( fact );
	}
	template <class T>
	T* performAndCastQuery( const std::string queryName, const PropertyCollection* params=0 )
	{
		QueryResult* res = performQuery(queryName, params);
		return boost::polymorphic_downcast<T*>( res );
	}

	void save(Archive& ar);
	void load(Archive& ar);

private:
	Collections objectCollections_;
	Queries queries_;
};

}

#endif /* OBJECTMANAGER_H_ */
