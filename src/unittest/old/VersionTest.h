/*
 * VersionTest.h
 *
 *  Created on: Aug 11, 2008
 *      Author: yamokosk
 */

#ifndef ARCHIVETEST_H_
#define ARCHIVETEST_H_

// Logging
#include <log4cxx/logger.h>
// CppUnit
#include <cppunit/extensions/HelperMacros.h>
// Class to test
#include <tinysg/Version.h>

class VersionTest : public CppUnit::TestFixture
{
	static log4cxx::LoggerPtr logger;

	CPPUNIT_TEST_SUITE( VersionTest );
	CPPUNIT_TEST( testCreateFromString );
	CPPUNIT_TEST( testOperators );
	CPPUNIT_TEST_SUITE_END();

protected:

public:
	void setUp();
	void tearDown();

protected:
	// Level 1 test cases
	void testCreateFromString();
	void testOperators();
};

#endif /* NODETEST_H_ */
