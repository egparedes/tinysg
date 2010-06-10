/*
 * TriMeshTest.cpp
 *
 *  Created on: Oct 31, 2008
 *      Author: yamokosk
 */

#include <cppunit/config/SourcePrefix.h>
#include "TriMeshTest.h"

using namespace log4cxx;

LoggerPtr TriMeshTest::logger(Logger::getLogger("TriMeshTest"));

CPPUNIT_TEST_SUITE_REGISTRATION( TriMeshTest );


void TriMeshTest::setUp()
{
	vertData = NULL;
	faceData = NULL;
}

void TriMeshTest::tearDown()
{
	if (vertData != NULL) delete [] vertData;
	if (faceData != NULL) delete [] faceData;
}

void TriMeshTest::testAddVertex()
{
	LOG4CXX_INFO(logger, "Test: " << __FUNCTION__);

	TinySG::TriMesh mesh;

	mesh.init(3,0);

	float x = 0.0, y = 1.0, z = 3.1;
	for (unsigned int n=0; n < 3; ++n)
	{
		//LOG4CXX_DEBUG(logger, "Creating vertex with values: " << x << ", " << y << ", " << z);
		unsigned int id = mesh.addVertex(x, y, z);
		CPPUNIT_ASSERT( id == n );
	}
	CPPUNIT_ASSERT( mesh.numVertices() == 3 );

	// Test memcpy using mesh's pointer to raw data
	vertData = new TinySG::TriMesh::Vertex[mesh.numVertices()];
	memcpy(vertData, mesh.vertexData(), mesh.numVertices()*mesh.vertexStride());

	// Check that the contents of the data match what we set above
	for (unsigned int n=0; n < mesh.numVertices(); ++n)
	{
		//LOG4CXX_DEBUG(logger, "Got a vertex with values: " << vertData[n].x << ", " << vertData[n].y << ", " << vertData[n].z);
		CPPUNIT_ASSERT( vertData[n].x  == x );
		CPPUNIT_ASSERT( vertData[n].y  == y );
		CPPUNIT_ASSERT( vertData[n].z  == z );
	}
}

void TriMeshTest::testAddFace()
{
	LOG4CXX_INFO(logger, "Test: " << __FUNCTION__);

	TinySG::TriMesh mesh;

	mesh.init(0,3);

	unsigned int v1 = 0, v2 = 10, v3 = 4;
	for (unsigned int n=0; n < 3; ++n)
	{
		//LOG4CXX_DEBUG(logger, "Creating vertex with values: " << x << ", " << y << ", " << z);
		unsigned int id = mesh.addFace(v1, v2, v3);
		CPPUNIT_ASSERT( id == n );
	}
	CPPUNIT_ASSERT( mesh.numFaces() == 3 );

	// Test memcpy using mesh's pointer to raw data
	faceData = new TinySG::TriMesh::Face[mesh.numFaces()];
	memcpy(faceData, mesh.faceData(), mesh.numFaces()*mesh.faceStride());

	// Check that the contents of the data match what we set above
	for (unsigned int n=0; n < mesh.numFaces(); ++n)
	{
		//LOG4CXX_DEBUG(logger, "Got a vertex with values: " << vertData[n].x << ", " << vertData[n].y << ", " << vertData[n].z);
		CPPUNIT_ASSERT( faceData[n].v1  == v1 );
		CPPUNIT_ASSERT( faceData[n].v2  == v2 );
		CPPUNIT_ASSERT( faceData[n].v3  == v3 );
	}
}
