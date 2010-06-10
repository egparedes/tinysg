/*
 * ArchiveTest.cpp
 *
 *  Created on: Aug 11, 2008
 *      Author: yamokosk
 */

#include <cppunit/config/SourcePrefix.h>
#include "ArchiveTest.h"

using namespace log4cxx;

LoggerPtr ArchiveTest::logger(Logger::getLogger("ArchiveTest"));

CPPUNIT_TEST_SUITE_REGISTRATION( ArchiveTest );

class A
{
public:
	A() : parent(NULL), name("") {};
	A(const std::string& n) : parent(NULL), name(n) {}
	void save(TinySG::PropertyCollection& pc) const
	{
		pc.addPair( TinySG::RequiredProperty("class", "AClass") );
		pc.addPair( TinySG::RequiredProperty("name", name.c_str()) );
		if (parent != NULL)
			pc.addPair( TinySG::OptionalProperty("parent", parent->name.c_str()) );
	}
	A* parent;
	std::string name;
};

void ArchiveTest::setUp()
{

}

void ArchiveTest::tearDown()
{

}

void ArchiveTest::testSave()
{
	LOG4CXX_INFO(logger, "Test: " << __FUNCTION__);

	A a1("a1"), a2("a2"), a3("a3"), a4("a4");
	a2.parent = &a1;
	a3.parent = &a1;
	a4.parent = &a2;

	TinySG::Archive ar;
	ar.createCollection("SomeObjects");
	ar.serializeObject("SomeObjects", a1);
	ar.serializeObject("SomeObjects", a2);
	ar.serializeObject("SomeObjects", a3);
	ar.serializeObject("SomeObjects", a4);

	TinySG::SceneFileWriter writer;
	writer.save("out.xml", ar);
	/*
	// s1
	TinySG::Serializable* s1 = new TinySG::Serializable();
	s1->type = "node";
	s1->attributes.addPair( TinySG::RequiredProperty("name", "obj1") );
	s1->attributes.addPair( TinySG::RequiredProperty("junk", "23.12") );
	s1->attributes.addPair( TinySG::RequiredProperty("parent", "world") );
	s1->parameters.addPair( TinySG::RequiredProperty("translation", "0 0 0") );
	s1->parameters.addPair( TinySG::RequiredProperty("length", "1") );
	s1->parameters.addPair( TinySG::RequiredProperty("radius", "2") );

	// obj 2
	TinySG::Serializable* s2 = new TinySG::Serializable();
	s2->type = "node";
	s2->attributes.addPair( TinySG::RequiredProperty("name", "obj2") );
	s2->attributes.addPair( TinySG::RequiredProperty("parent", "obj1") );
	s2->parameters.addPair( TinySG::RequiredProperty("length", "1") );

	// c1
	TinySG::CompositeItem* c1 = new TinySG::CompositeItem();
	c1->type = "nodes";
	c1->attributes.addPair( TinySG::RequiredProperty("name", "nodes") );
	c1->attributes.addPair( TinySG::RequiredProperty("parent", "collection") );
	c1->parameters.addPair( TinySG::RequiredProperty("size", "10") );
	c1->items.push_back( s1 );
	c1->items.push_back( s2 );

	// obj 3
	TinySG::Serializable* s3 = new TinySG::Serializable();
	s3->type = "object";
	s3->attributes.addPair( TinySG::RequiredProperty("name", "obj3") );
	s3->attributes.addPair( TinySG::RequiredProperty("parent", "obj1") );
	s3->parameters.addPair( TinySG::RequiredProperty("help", "who?") );

	// obj 3
	TinySG::Serializable* s4 = new TinySG::Serializable();
	s4->type = "object";
	s4->attributes.addPair( TinySG::RequiredProperty("name", "obj3") );
	s4->attributes.addPair( TinySG::RequiredProperty("parent", "obj1") );

	// obj 3
	TinySG::Serializable* s5 = new TinySG::Serializable();
	s5->type = "object";
	s5->parameters.addPair( TinySG::RequiredProperty("length", "4") );
	s5->parameters.addPair( TinySG::RequiredProperty("width", "2") );
	s5->parameters.addPair( TinySG::RequiredProperty("height", "9") );

	// archive
	TinySG::Archive ar;
	ar.data.type = "objects";
	ar.data.attributes.addPair( TinySG::RequiredProperty("name", "objects") );
	ar.data.items.push_back( s3 );
	ar.data.items.push_back( s4 );
	ar.data.items.push_back( s5 );
	ar.data.items.push_back( c1 );

	ar.writeToXML("out.xml");*/
}

void ArchiveTest::testLoad()
{
	TinySG::Archive ar;
	TinySG::SceneFileWriter writer; TinySG::SceneFileReader reader;
	reader.load("out.xml", ar);
	writer.save("out_check.xml", ar);
}
