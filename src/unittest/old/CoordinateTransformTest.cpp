/*
 * CoordinateTransformTest.cpp
 *
 *  Created on: Aug 12, 2008
 *      Author: yamokosk
 */

#include <cppunit/config/SourcePrefix.h>
#include <sstream>

#include "CoordinateTransformTest.h"
#include <linalg/Util.h>


using namespace log4cxx;

LoggerPtr CoordinateTransformTest::logger(Logger::getLogger("CoordinateTransformTest"));

CPPUNIT_TEST_SUITE_REGISTRATION( CoordinateTransformTest );

void CoordinateTransformTest::setUp()
{

}

void CoordinateTransformTest::tearDown()
{

}

void CoordinateTransformTest::testUpdateCachedTransform()
{
	LOG4CXX_INFO(logger, "Test: " << __FUNCTION__);

	TinySG::Real ang = TinySG::pi/3.0;
	TinySG::Quaternion q = TinySG::QuatFromAngleAxis(ang, TinySG::VectorFactory::Vector3( TinySG::UNIT_X ));
	LOG4CXX_INFO(logger, "Created quaternion using utility method.");

	// Create transform
	TinySG::CoordinateTransform c;
	c.setPosition(0, 1.0, -1.0);
	c.setOrientation( q );

	LOG4CXX_INFO(logger, "Calling getFullTransform first time.");
	Matrix t = c.getFullTransform();

	LOG4CXX_INFO(logger, "Calling getFullTransform second time.");
	t = c.getFullTransform();

	LOG4CXX_INFO(logger, "Modifying transform.");
	c.setPosition(1, 0, 1);

	LOG4CXX_INFO(logger, "Calling getFullTransform third time.");
	t = c.getFullTransform();
}
