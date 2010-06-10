/*
 * TriMeshTest.h
 *
 *  Created on: Aug 11, 2008
 *      Author: yamokosk
 */

#ifndef TRIMESHTEST_H_
#define TRIMESHTEST_H_

// Logging
#include <log4cxx/logger.h>
// CppUnit
#include <cppunit/extensions/HelperMacros.h>
// Class to test
#include <tinysg/TriMesh.h>

class TriMeshTest : public CppUnit::TestFixture
{
	static log4cxx::LoggerPtr logger;

	CPPUNIT_TEST_SUITE( TriMeshTest );
	CPPUNIT_TEST( testAddVertex );
	CPPUNIT_TEST( testAddFace );
	CPPUNIT_TEST_SUITE_END();

protected:
	TinySG::TriMesh::Vertex* vertData;
	TinySG::TriMesh::Face* faceData;

public:
	void setUp();
	void tearDown();

protected:
	void testAddVertex();
	void testAddFace();
};

#endif /* NODETEST_H_ */
