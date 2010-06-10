/*
 * VersionTest.cpp
 *
 *  Created on: Aug 11, 2008
 *      Author: yamokosk
 */

#include <cppunit/config/SourcePrefix.h>
#include "VersionTest.h"

using namespace log4cxx;

LoggerPtr VersionTest::logger(Logger::getLogger("VersionTest"));

CPPUNIT_TEST_SUITE_REGISTRATION( VersionTest );

void VersionTest::setUp()
{

}

void VersionTest::tearDown()
{

}

void VersionTest::testCreateFromString()
{
	LOG4CXX_INFO(logger, "Test: " << __FUNCTION__);

	TinySG::Version v("1.2.3");
	TinySG::Version a(1, 2, 3);

	CPPUNIT_ASSERT( v == a );
}

void VersionTest::testOperators()
{
	LOG4CXX_INFO(logger, "Test: " << __FUNCTION__);

	TinySG::Version v1("1.2.1");
	TinySG::Version v2("2.1.9");
	TinySG::Version v3("2.2.5");

	CPPUNIT_ASSERT( v1 <= v2 );
	CPPUNIT_ASSERT( v2 <= v3 );
	CPPUNIT_ASSERT( v3 > v2 );
}
