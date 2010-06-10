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
 * Archive.h
 *
 *  Created on: Nov 5, 2008
 *      Author: yamokosk
 */

#ifndef ARCHIVE_H_
#define ARCHIVE_H_

//#include <tinysg/tinyxml.h>
#include <tinysg/PropertyCollection.h>

#include <vector>

namespace TinySG
{

class Archive
{
public:
	struct Collection
	{
		Collection(const std::string& id, unsigned int num=0);
		std::vector<PropertyCollection> objects;
		unsigned int size() {return (unsigned int)objects.size();}
		std::string collectionType;
	};
	typedef std::map<std::string, Collection*> CollectionMap;

	Archive();
	virtual ~Archive();

	Collection* createCollection(const std::string& cname, unsigned int num=0);
	Collection* getCollection( const std::string& type ) const;
	Collection* getCollection( unsigned int index ) const;
	Collection* getFirstCollection();
	Collection* getNextCollection();
	unsigned int size() const {return (unsigned int)collections.size();}

	template<class T>
	void serializeObject(const std::string& cname, const T& obj);

	void setVersion(const unsigned int v) {version = v;}
	unsigned int getVersion() {return version;}

private:
	CollectionMap collections;
	CollectionMap::iterator currentCollection;
	unsigned int version;
};

template<class T>
void Archive::serializeObject(const std::string& cname, const T& obj)
{
	Archive::Collection* c = getCollection(cname);
	if ( c != NULL )
	{
		PropertyCollection pc;
		obj.save(pc);
		c->objects.push_back(pc);
	}
}

}  // namespace TinySG

#endif /* ARCHIVE_H_ */
