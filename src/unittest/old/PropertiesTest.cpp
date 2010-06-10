/*************************************************************************
 * SceneML, Copyright (C) 2007, 2008  J.D. Yamokoski
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
 * test_properties.cpp
 *
 *  Created on: Jul 17, 2008
 *      Author: yamokosk
 */

#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>

#include <iostream>
#include <PropertyCollection.h>

using namespace sml;

BOOST_AUTO_TEST_CASE( add_pair_test )
{
	BOOST_TEST_MESSAGE( "Add pair test." );

	PropertyCollection pc;
	pc.addPair( RequiredProperty("required", "3.0") );
	pc.addPair( OptionalProperty("optional", "hello") );

	BOOST_CHECK_EQUAL( pc.size(), 2 );
}

BOOST_AUTO_TEST_CASE( update_pair_test )
{
	BOOST_TEST_MESSAGE( "Update pair test." );

	PropertyCollection pc;
	pc.addPair( RequiredProperty("required", "3.0") );
	pc.updatePair("required", "4.0", true);

	std::string val = pc.getValue("required");

	BOOST_CHECK_EQUAL( val, "4.0" );
}

/*BOOST_AUTO_TEST_CASE( get_value_test )
{
	BOOST_TEST_MESSAGE( "Testing node create methods." );

	// Functions to test:
	//	createChild()
	//	addChild()
	//	numChildren()
	//	getChild()

	SceneManager mgr;
	SceneNode n1(&mgr, "node1");
	SceneNode n2(&mgr, "node2");

	//	addChild(), numChildren(), getChild(), getParent()
	n1.addChild(&n2);
	BOOST_CHECK_EQUAL( n1.numChildren(), 1 );
	BOOST_CHECK_EQUAL( n1.getChild(0)->getName().compare("node2"), 0 );
	BOOST_CHECK_EQUAL( n1.getChild("node2")->getName().compare("node2"), 0 );
	BOOST_CHECK_EQUAL( n2.getParent()->getName().compare("node1"), 0 );
	BOOST_CHECK_THROW( n1.addChild(&n2), sml::Exception );

	// removeChild(), numChildren()
	n1.removeChild(&n2);
	BOOST_CHECK_EQUAL( n1.numChildren(), 0 );
	BOOST_CHECK_THROW( n1.removeChild("node2"), sml::Exception )
}

BOOST_AUTO_TEST_CASE( pose_tests )
{
	BOOST_TEST_MESSAGE( "Testing node create methods." );

	// Functions to test:
	//	createChild()
	//	addChild()
	//	numChildren()
	//	getChild()

	SceneManager mgr;
	SceneNode n1(&mgr, "node1");

	//	addChild(), numChildren(), getChild(), getParent()
	n1.addChild(&n2);
	BOOST_CHECK_EQUAL( n1.numChildren(), 1 );
	BOOST_CHECK_EQUAL( n1.getChild(0)->getName().compare("node2"), 0 );
	BOOST_CHECK_EQUAL( n1.getChild("node2")->getName().compare("node2"), 0 );
	BOOST_CHECK_EQUAL( n2.getParent()->getName().compare("node1"), 0 );
	BOOST_CHECK_THROW( n1.addChild(&n2), sml::Exception );

	// removeChild(), numChildren()
	n1.removeChild(&n2);
	BOOST_CHECK_EQUAL( n1.numChildren(), 0 );
	BOOST_CHECK_THROW( n1.removeChild("node2"), sml::Exception )
}*/
