/*
 * EntityTest.h
 *
 *  Created on: Aug 11, 2008
 *      Author: yamokosk
 */

#ifndef MOVABLEOBJECT_TEST_H_
#define MOVABLEOBJECT_TEST_H_

// Logging
#include <log4cxx/logger.h>
// CppUnit
#include <cppunit/extensions/HelperMacros.h>
// Class to test
#include <tinysg/MovableObject.h>
#include <tinysg/SceneNode.h>

// TEST CLASSES (class to test is pure virtual)
class TestObject : public TinySG::MovableObject
{
public:
	TestObject() : moved_(false) {};
	virtual ~TestObject() {};

	virtual TinySG::MovableObject* clone() const {return NULL;}
	virtual void save(TinySG::PropertyCollection& pc) const {return;}
	bool moved_;

protected:
	virtual void notifyMoved(void) {moved_ = true;}
};

class TestObjectFactory : public TinySG::ObjectFactory
{
protected:
	// To be overloaded by specific object factories
	virtual TinySG::Object* createInstanceImpl(const TinySG::PropertyCollection* params = 0);

public:
	TestObjectFactory() : TinySG::ObjectFactory("TestObject") {};
	virtual ~TestObjectFactory() {};

	// To be overloaded by specific object factories
	virtual void destroyInstance(TinySG::Object* obj);
};


class MovableObjectTest : public CppUnit::TestFixture
{
	static log4cxx::LoggerPtr logger;

	CPPUNIT_TEST_SUITE(MovableObjectTest);
	CPPUNIT_TEST(testNumAttachedObjects);
	CPPUNIT_TEST(testGetObjectByName);
	CPPUNIT_TEST(testGetObjectByIndex);
	CPPUNIT_TEST(testDetachObjectByPointer);
	CPPUNIT_TEST(testDetachObjectByName);
	CPPUNIT_TEST(testDetachObjectByIndex);
	CPPUNIT_TEST(testDetachAllObjects);
	CPPUNIT_TEST(testMovedNotification);
	CPPUNIT_TEST_EXCEPTION( testAttachAttachedObject, TinySG::InvalidParametersException );
	CPPUNIT_TEST_EXCEPTION( testAttachObjectWithSameName, TinySG::ItemIdentityException );
	CPPUNIT_TEST_EXCEPTION( testGetAttachedObjectByBadIndex, TinySG::ItemIdentityException );
	CPPUNIT_TEST_EXCEPTION( testGetAttachedObjectByBadName, TinySG::ItemIdentityException );
	CPPUNIT_TEST_EXCEPTION( testDetachObjectByBadIndex, TinySG::ItemIdentityException );
	CPPUNIT_TEST_EXCEPTION( testDetachObjectByBadName, TinySG::ItemIdentityException );
	CPPUNIT_TEST_SUITE_END();
private:
	TestObjectFactory objfact;
	TestObject *obj, *obj_copy;
	TinySG::SceneNode *n1, *n2, *n3, *n4;
	//TinySG::NodeFactory nodefact;
public:
	void setUp();
	void tearDown();
protected:
	// Unittest declarations
	void testNumAttachedObjects();
	void testGetObjectByName();
	void testGetObjectByIndex();
	void testDetachObjectByPointer();
	void testDetachObjectByName();
	void testDetachObjectByIndex();
	void testDetachAllObjects();
	void testMovedNotification();

	// Exception tests
	void testAttachAttachedObject();
	void testAttachObjectWithSameName();
	void testGetAttachedObjectByBadIndex();
	void testGetAttachedObjectByBadName();
	void testDetachObjectByBadIndex();
	void testDetachObjectByBadName();
};

#endif /* ENTITYTEST_H_ */
