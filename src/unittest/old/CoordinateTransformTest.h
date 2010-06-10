/*
 * CoordinateTransformTest.h
 *
 *  Created on: Aug 12, 2008
 *      Author: yamokosk
 */

#ifndef COORDINATETRANSFORMTEST_H_
#define COORDINATETRANSFORMTEST_H_

// Logging
#include <log4cxx/logger.h>
// CppUnit
#include <cppunit/extensions/HelperMacros.h>
// Class to test
#include <CoordinateTransform.h>

class CoordinateTransformTest: public CPPUNIT_NS::TestFixture
{
	static log4cxx::LoggerPtr logger;

	CPPUNIT_TEST_SUITE(CoordinateTransformTest);
	CPPUNIT_TEST(testUpdateCachedTransform);
	CPPUNIT_TEST_SUITE_END();
private:
	// Member variables here
public:
	void setUp();
	void tearDown();
protected:
	// Unittest declarations
	void testUpdateCachedTransform();
};

#endif /* COORDINATETRANSFORMTEST_H_ */
