/*
 * ArchiveTest.h
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
#include <tinysg/Archive.h>
#include <tinysg/>
//#include <tinysg/SceneFile.h>

class ArchiveTest : public CppUnit::TestFixture
{
	static log4cxx::LoggerPtr logger;

	CPPUNIT_TEST_SUITE( ArchiveTest );
	CPPUNIT_TEST( testSave );
	CPPUNIT_TEST( testLoad );
	CPPUNIT_TEST_SUITE_END();

protected:

public:
	void setUp();
	void tearDown();

protected:
	// Level 1 test cases
	void testSave();
	void testLoad();
};

#endif /* NODETEST_H_ */
