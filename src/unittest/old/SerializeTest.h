/*
 * SerializeTest.h
 *
 *  Created on: Sep 9, 2008
 *      Author: yamokosk
 */

#ifndef SERIALIZETEST_H_
#define SERIALIZETEST_H_

// Logging
#include <log4cxx/logger.h>

#include <cppunit/extensions/HelperMacros.h>

class SerializeTest: public CPPUNIT_NS::TestFixture
{
	static log4cxx::LoggerPtr logger;

	CPPUNIT_TEST_SUITE(SerializeTest);
	CPPUNIT_TEST(testSimpleClass);
	CPPUNIT_TEST(testManagerClass);
	CPPUNIT_TEST_SUITE_END();
private:
	// Member variables here
public:
	void setUp();
	void tearDown();
protected:
	// Unittest declarations
	void testSimpleClass();
	void testManagerClass();

};

#endif /* COORDINATETRANSFORMTEST_H_ */
