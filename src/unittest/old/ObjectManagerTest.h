/*
 * ObjectManagerTest.h
 *
 *  Created on: Sep 18, 2008
 *      Author: yamokosk
 */

#ifndef OBJECTMANAGERTEST_H_
#define OBJECTMANAGERTEST_H_

#include <tinysg/Exception.h>
#include <tinysg/ObjectManager.h>

// Logging
#include <log4cxx/logger.h>

#include <cppunit/extensions/HelperMacros.h>

class ObjectManagerTest: public CPPUNIT_NS::TestFixture
{
	static log4cxx::LoggerPtr logger;

	CPPUNIT_TEST_SUITE(ObjectManagerTest);
	CPPUNIT_TEST(testSimpleManager);
	CPPUNIT_TEST_EXCEPTION( testCreateDuplicateObject, TinySG::ItemIdentityException );
	CPPUNIT_TEST_EXCEPTION( testDestroyInvalidObject, TinySG::ItemIdentityException );
	CPPUNIT_TEST_EXCEPTION( testGetInvalidObject, TinySG::ItemIdentityException );
	CPPUNIT_TEST_EXCEPTION( testRegisterDuplicateFactory, TinySG::ItemIdentityException );
	CPPUNIT_TEST_EXCEPTION( testDestroyInvalidCollection, TinySG::ItemIdentityException );
	CPPUNIT_TEST_EXCEPTION( testGetInvalidCollection, TinySG::ItemIdentityException );
	CPPUNIT_TEST_SUITE_END();
private:
	// Member variables here
public:
	void setUp();
	void tearDown();
protected:
	// Unittest declarations
	void testSimpleManager();

	// Exception tests
	void testCreateDuplicateObject();
	void testDestroyInvalidObject();
	void testGetInvalidObject();
	void testRegisterDuplicateFactory();
	void testDestroyInvalidCollection();
	void testGetInvalidCollection();
};


#endif /* OBJECTMANAGERTEST_H_ */
