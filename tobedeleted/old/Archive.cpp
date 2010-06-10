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
 * Archive.cpp
 *
 *  Created on: Nov 13, 2008
 *      Author: yamokosk
 */

#include <tinysg/Archive.h>

namespace TinySG
{

Archive::Collection::Collection(const std::string& id, unsigned int num) :
	collectionType(id)
{
	objects.reserve(num);
}

Archive::Archive() :
	version(0)
{
	currentCollection = collections.begin();
}

Archive::~Archive()
{
	CollectionMap::iterator itr = collections.begin();
	for (; itr != collections.end(); ++itr)
	{
		delete itr->second;
	}
}

Archive::Collection* Archive::createCollection(const std::string& cname, unsigned int num)
{
	if (collections.find(cname) != collections.end())
	{
		// Throw error
		return NULL;
	}

	Archive::Collection* c = new Archive::Collection(cname, num);
	collections[cname] = c;
	return c;
}

Archive::Collection* Archive::getCollection( const std::string& type ) const
{
	CollectionMap::const_iterator itr = collections.find(type);
	if ( itr != collections.end() )
		return itr->second;
	else
		return NULL;
}

Archive::Collection* Archive::getCollection( unsigned int index ) const
{
	if( index < size() )
	{
		CollectionMap::const_iterator i = collections.begin();
		while (index--) ++i;
		return i->second;
	} else {
		//SML_EXCEPT(Exception::ERR_INVALIDPARAMS, "Child index out of bounds.");
		return NULL;
	}
}

Archive::Collection* Archive::getFirstCollection()
{
	currentCollection = collections.begin();
	if ( currentCollection != collections.end() )
	{
		return currentCollection->second;
	} else {
		return NULL;
	}
}

Archive::Collection* Archive::getNextCollection()
{
	if ( ++currentCollection != collections.end() )
	{
		return currentCollection->second;
	} else {
		return NULL;
	}
}

}
