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
 * Object.h
 *
 *  Created on: Sep 18, 2008
 *      Author: yamokosk
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <tinysg/PropertyCollection.h>

#include <boost/cast.hpp>

namespace TinySG
{

// Forward declaration
class ObjectFactory;
class ObjectManager;

class Object
{
	friend class ObjectFactory;
	friend class ObjectManager;

public:
	Object() :
		manager_(NULL),
		factory_(NULL),
		name_("")
	{}
	virtual ~Object() {};

	// For the copy constructor
	virtual Object* clone() const = 0;

	// Used to save object data to XML
	virtual void save(PropertyCollection& pc) const = 0;

	//! Returns factory which created this mesh
	const ObjectFactory* getFactory() const {return factory_;}
	//! Returns the manager of this object
	const ObjectManager* getManager() const {return manager_;}
	//! Returns factory which created this mesh
	template<class T>
	const T* getAndCastFactory() const
	{
		return boost::polymorphic_downcast<T*>(factory_);
	}
	//! Returns the manager of this object
	template<class T>
	const T* getAndCastManager() const
	{
		return boost::polymorphic_downcast<T*>(manager_);
	}
	//! Returns the name of this object
	const std::string& getName() const {return name_;}
	//! Returns the object type
	const std::string& getType() const;

	const PropertyCollection& getProperties() const {return properties_;}

private:
	ObjectManager* manager_;
	ObjectFactory* factory_;
	std::string name_;
	PropertyCollection properties_;
};


class ObjectFactory
{
protected:
	// To be overloaded by specific object factories
	virtual Object* createInstanceImpl(const PropertyCollection* params) = 0;

public:
	ObjectFactory(const std::string& type) : type_(type) {};
	virtual ~ObjectFactory() {};

	const std::string& getType(void) const {return type_;}

	Object* createInstance( const std::string& name, ObjectManager* mgr, const PropertyCollection* params)
	{
		Object* obj = createInstanceImpl(params);
		obj->name_ = name;
		obj->factory_ = this;
		obj->manager_ = mgr;
		if (params != NULL) obj->properties_ = *params;
		return obj;
	}

	// To be overloaded by specific object factories
	virtual void destroyInstance(Object* obj) = 0;

private:
	const std::string type_;
};


}

#endif /* TINYSGOBJECT_H_ */
