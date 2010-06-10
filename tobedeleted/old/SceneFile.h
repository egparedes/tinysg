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
 * Serializer.h
 *
 *  Created on: Nov 13, 2008
 *      Author: yamokosk
 */

#ifndef SERIALIZER_H_
#define SERIALIZER_H_


#include <tinysg/Archive.h>
#include <tinysg/PropertyCollection.h>

#include <tinysg/tinyxml.h>

namespace TinySG
{

class SceneFileWriter
{
public:
	SceneFileWriter() {};
	virtual ~SceneFileWriter() {};

	void save(const std::string& filename, const Archive& ar) const;

private:
	TiXmlElement* saveCollection(TiXmlElement* parent, const Archive::Collection& c) const;
	TiXmlElement* saveObject(TiXmlElement* parent, const PropertyCollection& pc) const;
};


class SceneFileReader
{
public:
	SceneFileReader() {};
	virtual ~SceneFileReader() {};

	void load(const std::string& filename, Archive& ar);

private:
	void loadCollection(TiXmlElement* node, Archive& ar) const;
	PropertyCollection loadObject(TiXmlElement* node) const;
};

}  // namespace TinySG

#endif
