/*
 * EntityTest.cpp
 *
 *  Created on: Aug 11, 2008
 *      Author: yamokosk
 */

#include <cppunit/config/SourcePrefix.h>
#include "MovableObjectTest.h"

using namespace log4cxx;

LoggerPtr MovableObjectTest::logger(Logger::getLogger("MovableObjectTest"));

CPPUNIT_TEST_SUITE_REGISTRATION( MovableObjectTest );


TinySG::Object* TestObjectFactory::createInstanceImpl(const TinySG::PropertyCollection* params)
{
	return new TestObject();
}

void TestObjectFactory::destroyInstance(TinySG::Object* obj)
{
	TestObject* ptr = dynamic_cast<TestObject*>(obj);
	delete ptr;
}

void MovableObjectTest::setUp()
{
	n1 = new TinySG::SceneNode();//dynamic_cast<TinySG::SceneNode*>( nodefact.createInstance("n1", NULL, NULL) );
	n2 = new TinySG::SceneNode();//dynamic_cast<TinySG::SceneNode*>( nodefact.createInstance("n2", NULL, NULL) );
	n3 = new TinySG::SceneNode();//dynamic_cast<TinySG::SceneNode*>( nodefact.createInstance("n3", NULL, NULL) );
	n4 = new TinySG::SceneNode();//dynamic_cast<TinySG::SceneNode*>( nodefact.createInstance("n4", NULL, NULL) );

	/* Create tree
			n1
		  /	   \
		n2		n3
				|
				n4
	 */
	n1->addChild(n2);
	n1->addChild(n3);
	n3->addChild(n4);
	n1->update();

	obj = dynamic_cast<TestObject*>( objfact.createInstance("obj", NULL, NULL) );
	obj_copy = dynamic_cast<TestObject*>( objfact.createInstance("obj", NULL, NULL) );
}

void MovableObjectTest::tearDown()
{
	if (n1) delete n1; //nodefact.destroyInstance(n1);
	if (n2) delete n2; //nodefact.destroyInstance(n2);
	if (n3) delete n3; //nodefact.destroyInstance(n3);
	if (n4) delete n4; //nodefact.destroyInstance(n4);
	objfact.destroyInstance(obj);
	objfact.destroyInstance(obj_copy);
}

// Normal tests
void MovableObjectTest::testNumAttachedObjects()
{
	LOG4CXX_INFO(logger, "Test: " << __FUNCTION__);

	CPPUNIT_ASSERT( n3->numAttachedObjects() == 0 );
	n3->attachObject(obj);
	CPPUNIT_ASSERT( n3->numAttachedObjects() == 1 );
}

void MovableObjectTest::testGetObjectByName()
{
	LOG4CXX_INFO(logger, "Test: " << __FUNCTION__);

	n3->attachObject(obj);
	TestObject* ptr = dynamic_cast<TestObject*>(n3->getAttachedObject( obj->getName() ));

	CPPUNIT_ASSERT( ptr = obj );
}

void MovableObjectTest::testGetObjectByIndex()
{
	LOG4CXX_INFO(logger, "Test: " << __FUNCTION__);

	n3->attachObject(obj);
	TestObject* ptr = dynamic_cast<TestObject*>(n3->getAttachedObject( 0 ));

	CPPUNIT_ASSERT( ptr == obj );
}

void MovableObjectTest::testDetachObjectByPointer()
{
	LOG4CXX_INFO(logger, "Test: " << __FUNCTION__);

	CPPUNIT_ASSERT( !obj->isAttached() );
	n3->attachObject(obj);
	CPPUNIT_ASSERT( obj->isAttached() );
	n3->detachObject(obj);
	CPPUNIT_ASSERT( !obj->isAttached() );
}

void MovableObjectTest::testDetachObjectByName()
{
	LOG4CXX_INFO(logger, "Test: " << __FUNCTION__);

	CPPUNIT_ASSERT( !obj->isAttached() );
	n3->attachObject(obj);
	CPPUNIT_ASSERT( obj->isAttached() );
	n3->detachObject(obj->getName());
	CPPUNIT_ASSERT( !obj->isAttached() );
}

void MovableObjectTest::testDetachObjectByIndex()
{
	LOG4CXX_INFO(logger, "Test: " << __FUNCTION__);

	CPPUNIT_ASSERT( !obj->isAttached() );
	n3->attachObject(obj);
	CPPUNIT_ASSERT( obj->isAttached() );
	n3->detachObject( (unsigned short)0 );
	CPPUNIT_ASSERT( !obj->isAttached() );
}

void MovableObjectTest::testDetachAllObjects()
{
	LOG4CXX_INFO(logger, "Test: " << __FUNCTION__);

	CPPUNIT_ASSERT( !obj->isAttached() );
	n3->attachObject(obj);
	CPPUNIT_ASSERT( obj->isAttached() );
	n3->detachAllObjects();
	CPPUNIT_ASSERT( !obj->isAttached() );
}

void MovableObjectTest::testMovedNotification()
{
	LOG4CXX_INFO(logger, "Test: " << __FUNCTION__);

	n3->attachObject(obj);
	n3->translate(1.0, -3.0, 0.0);
	CPPUNIT_ASSERT( !obj->moved_ );
	n1->update();
	CPPUNIT_ASSERT( obj->moved_ );
}

// Exception tests
void MovableObjectTest::testAttachAttachedObject()
{
	LOG4CXX_INFO(logger, "Test: " << __FUNCTION__);

	n3->attachObject(obj);
	n1->attachObject(obj);
}

void MovableObjectTest::testAttachObjectWithSameName()
{
	LOG4CXX_INFO(logger, "Test: " << __FUNCTION__);

	n3->attachObject(obj);
	n3->attachObject(obj_copy);
}

void MovableObjectTest::testGetAttachedObjectByBadIndex()
{
	LOG4CXX_INFO(logger, "Test: " << __FUNCTION__);

	n3->attachObject(obj);
	n3->getAttachedObject(3);
}

void MovableObjectTest::testGetAttachedObjectByBadName()
{
	LOG4CXX_INFO(logger, "Test: " << __FUNCTION__);

	n3->attachObject(obj);
	n3->getAttachedObject("bad");
}

void MovableObjectTest::testDetachObjectByBadIndex()
{
	LOG4CXX_INFO(logger, "Test: " << __FUNCTION__);

	n3->attachObject(obj);
	n3->detachObject(3);
}

void MovableObjectTest::testDetachObjectByBadName()
{
	LOG4CXX_INFO(logger, "Test: " << __FUNCTION__);

	n3->attachObject(obj);
	n3->detachObject("bad");
}
