/*
 * ObjectManagerTest.cpp
 *
 *  Created on: Sep 15, 2008
 *      Author: yamokosk
 */

#include <cppunit/config/SourcePrefix.h>
#include "ObjectManagerTest.h"

using namespace log4cxx;

LoggerPtr ObjectManagerTest::logger(Logger::getLogger("ObjectManagerTest"));

CPPUNIT_TEST_SUITE_REGISTRATION( ObjectManagerTest );


class MyObject : public TinySG::Object
{
public:
	MyObject(double d) : TinySG::Object(), val(d) {};
	virtual ~MyObject() {};

	virtual TinySG::Object* clone() const {return NULL;}
	virtual void save(TinySG::PropertyCollection& pc) const {return;}
	double val;
};

class MyObjectFactory : public TinySG::ObjectFactory
{
protected:
	virtual TinySG::Object* createInstanceImpl(const TinySG::PropertyCollection* params)
	{
		return (new MyObject(1.0));
	}

public:
	MyObjectFactory() : TinySG::ObjectFactory("MyObject") {};
	virtual ~MyObjectFactory() {};
	virtual void destroyInstance(TinySG::Object* obj) {delete obj;}
};


class MyManager : public TinySG::ObjectManager
{
public:
	MyManager()
	{
		registerFactory( new MyObjectFactory() );
	}
	void deleteMyCollection(const std::string& type)
	{
		destroyCollection(type);
	}
	void getMyCollection(const std::string& type)
	{
		getCollection(type);
	}
	virtual ~MyManager() {};
};

void ObjectManagerTest::setUp()
{

}

void ObjectManagerTest::tearDown()
{

}

void ObjectManagerTest::testSimpleManager()
{
	LOG4CXX_INFO(logger, "Running " << __FUNCTION__);

	MyManager mgr;

	MyObject* one = dynamic_cast<MyObject*>( mgr.createObject("one","MyObject") );
	MyObject* two = dynamic_cast<MyObject*>( mgr.createObject("two","MyObject") );
	MyObject* three = dynamic_cast<MyObject*>( mgr.createObject("three","MyObject") );

	CPPUNIT_ASSERT( dynamic_cast<MyObject*>( mgr.getObject("one","MyObject") ) == one );
	CPPUNIT_ASSERT( dynamic_cast<MyObject*>( mgr.getObject("two","MyObject") ) == two );
	CPPUNIT_ASSERT( dynamic_cast<MyObject*>( mgr.getObject("three","MyObject") ) == three );

	LOG4CXX_INFO(logger, "Exiting " << __FUNCTION__);
}

void ObjectManagerTest::testCreateDuplicateObject()
{
	MyManager mgr;
	MyObject* one = dynamic_cast<MyObject*>( mgr.createObject("one","MyObject") );
	MyObject* two = dynamic_cast<MyObject*>( mgr.createObject("one","MyObject") ); // Exception
}

void ObjectManagerTest::testDestroyInvalidObject()
{
	MyManager mgr;
	mgr.destroyObject("one","MyObject"); // Exception
}

void ObjectManagerTest::testGetInvalidObject()
{
	MyManager mgr;
	mgr.getObject("one","MyObject"); // Exception
}

void ObjectManagerTest::testRegisterDuplicateFactory()
{
	MyManager mgr;
	mgr.registerFactory( new MyObjectFactory() ); // Exception
}

void ObjectManagerTest::testDestroyInvalidCollection()
{
	MyManager mgr;
	mgr.deleteMyCollection("Double"); // Exception
}

void ObjectManagerTest::testGetInvalidCollection()
{
	MyManager mgr;
	mgr.getMyCollection("Double"); // Exception
}


