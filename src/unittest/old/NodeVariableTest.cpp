/*
 * test_nodevariable.cpp
 *
 *  Created on: Jul 21, 2008
 *      Author: yamokosk
 */

#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>

#include <iostream>
#include <SceneManager.h>
#include <Node.h>
#include <Variable.h>
#include <linalg/Vector.h>

using namespace sml;

BOOST_AUTO_TEST_CASE( basic_test )
{
	BOOST_TEST_MESSAGE( "Node/variable test." );

	SceneManager mgr;

	SceneNode* n1 = mgr.getRootNode()->createChild();
	SceneNode* n2 = n1->createChild();
	SceneNode* n3 = n2->createChild();
	SceneNode* n4 = n2->createChild();
	SceneNode* n5 = n4->createChild();

	Variable var1;
	var1.setType("translation");
	var1.subscribe(n2);
	var1.setVector( VectorFactory::Vector3( UNIT_X ) );
}
