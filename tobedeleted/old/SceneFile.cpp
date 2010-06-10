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
 * SceneFile.cpp
 *
 *  Created on: Nov 13, 2008
 *      Author: yamokosk
 */

#include <tinysg/config.h>
#include <tinysg/SceneFile.h>
#include <boost/foreach.hpp>
#include <sstream>

namespace TinySG
{

void SceneFileWriter::save(const std::string& filename, const Archive& ar) const
{
	TiXmlDocument doc;
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
	doc.LinkEndChild( decl );

	// Create root node
	TiXmlElement * root = new TiXmlElement("TinySG");
	doc.LinkEndChild( root );

	// Write version
	std::stringstream ss; ss << TINYSG_VERSION;
	root->SetAttribute("version", ss.str().c_str() );

	// Write items
	for (unsigned int n=0; n < ar.size(); ++n)
	{
		Archive::Collection* c = ar.getCollection(n);
		if ( c != NULL )
		{
			saveCollection(root, *c);
		}
	}

	// Responsible for writing file
	doc.SaveFile( filename.c_str() );
}

TiXmlElement* SceneFileWriter::saveCollection(TiXmlElement* parent, const Archive::Collection& c) const
{
	TiXmlElement* me = new TiXmlElement( c.collectionType.c_str() );
	parent->LinkEndChild( me );

	BOOST_FOREACH( PropertyCollection pc, c.objects )
	{
		saveObject(me, pc);
	}

	return me;
}

TiXmlElement* SceneFileWriter::saveObject(TiXmlElement* parent, const PropertyCollection& pc) const
{
	TiXmlElement* me = new TiXmlElement( pc.getValue("class").c_str() );
	parent->LinkEndChild( me );

	for (unsigned int n=0; n < pc.size(); ++n)
	{
		PropertyPair p = pc.getPair(n);

		// Skip the object's class as we have already used it
		if ( p.getPropertyName().compare("class") != 0 )
		{
			/*
			 * Required properties become XML attributes while non-required properties
			 * become parameters.
			 */
			if ( p.isRequired() ) {
				me->SetAttribute(p.getPropertyName().c_str(), p.getPropertyValue().c_str());
			} else {
				TiXmlElement* parameter = new TiXmlElement("parameter");
				parameter->SetAttribute("type", p.getPropertyName().c_str());
				parameter->SetAttribute("value", p.getPropertyValue().c_str());
				me->LinkEndChild(parameter);
			}
		}
	}

	return me;
}


void SceneFileReader::load(const std::string& filename, Archive& ar)
{
	TiXmlDocument doc(filename.c_str());
	if ( !doc.LoadFile() )
	{
		// Throw error
		return;
	}

	TiXmlHandle hDoc(&doc);
	TiXmlElement * root = hDoc.FirstChildElement().Element();

	// should always have a valid root but handle gracefully if it does
	if ( root == NULL )
	{
		// Throw an error
		return;
	}

	// Check that its one of our XML files
	if ( strcmp(root->Value(), "TinySG") != 0 )
	{
		// Throw an error
		return;
	}

	// Set the version
	int ver = 0;
	root->Attribute("version", &ver);
	ar.setVersion( (unsigned int)ver );

	// Read in all elements
	TiXmlElement* child = root->FirstChildElement();
	while ( child != NULL )
	{
		loadCollection(child, ar);
		child = child->NextSiblingElement();
	}
}

void SceneFileReader::loadCollection(TiXmlElement* node, Archive& ar) const
{
	if ( node == NULL ) return;

	Archive::Collection* c = ar.createCollection(node->Value());
	if ( c != NULL )
	{
		TiXmlElement* child = node->FirstChildElement();
		while ( child != NULL )
		{
			c->objects.push_back( loadObject(child) );
			child = child->NextSiblingElement();
		}
	}
}

PropertyCollection SceneFileReader::loadObject(TiXmlElement* node) const
{
	if ( node == NULL ) return PropertyCollection();

	PropertyCollection pc;

	// Save the object's class as a required property.
	pc.addPair( RequiredProperty("class", node->Value()) );

	// Iterate over attributes and save them as required properties.
	TiXmlAttribute* attrib = node->FirstAttribute();
	while ( attrib != NULL )
	{
		pc.addPair( RequiredProperty(attrib->Name(), attrib->Value()) );
		attrib = attrib->Next();
	}

	/*
	 * Iterate over child nodes. We only look for children labeled parameters
	 * and save them as optional properties.
	 */
	TiXmlElement* child = node->FirstChildElement("parameter");
	while ( child != NULL )
	{
		pc.addPair( OptionalProperty(child->Attribute("type"), child->Attribute("value")) );
		child = child->NextSiblingElement("parameter");
	}

	return pc;
}

}
