/*************************************************************************
 * SceneML, Copyright (C) 2007, 2008  J.D. Yamokoski
 * All rights reserved.
 * Email: yamokosk at gmail dot com
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of the License,
 * or (at your option) any later version. The text of the GNU Lesser General
 * Public License is included with this library in the file LICENSE.TXT.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the file LICENSE.TXT for
 * more details.
 *
 *************************************************************************/
/*
 * SignalTest.cpp
 *
 *  Created on: Aug 27, 2008
 *      Author: yamokosk
 */

#include <cppunit/config/SourcePrefix.h>
#include "CoordinateTransformTest.h"
#include <sstream>

using namespace log4cxx;

LoggerPtr CoordinateTransformTest::logger(Logger::getLogger("SignalTest"));

CPPUNIT_TEST_SUITE_REGISTRATION( SignalTest );

class HelloObserver : public sml::Observer
{
public:
	HelloObserver() : Observer() {}
	virtual ~HelloObserver() {};

	virtual void update(Subject* sub, int hint)
	{
		std::cout << "Hello ";
	}
};

class WorldObserver : public sml::Observer
{
public:
	WorldObserver() : Observer() {}
	virtual ~WorldObserver() {};

	virtual void update(Subject* sub, int hint)
	{
		std::cout << "World!" << std::endl;
	}
};

class Numbers : public sml::Subject
{
public:
	Numbers() : Subject(), a_(0), b_(0.0) {}
	virtual ~Numbers() {};

	enum NumbersHint {
		FloatHint=0,
		IntHint
	};

	void setInt(int a)
	{
		a_ = a;
		this->notify(IntHint);
	}
	void setFloat(float b)
	{
		b_ = b;
		this->notify(FloatHint);
	}

	int a_;
	float b_;
};

class FloatObserver : public sml::Observer
{
public:
	FloatObserver() : Observer() {};
	virtual ~FloatObserver() {};

	virtual void update(Subject* sub, int hint)
	{
		if (hint == Numbers::FloatHint) {
			Numbers* num = boost::polymorphic_downcast<Numbers*>(sub);
			std::cout << "float = " << num->b_ << std::endl;
		}
	}
};

class IntObserver : public sml::Observer
{
public:
	IntObserver() : Observer() {};
	virtual ~IntObserver() {};

	virtual void update(Subject* sub, int hint)
	{
		if (hint == Numbers::IntHint) {
			Numbers* num = boost::polymorphic_downcast<Numbers*>(sub);
			std::cout << "int = " << num->a_ << std::endl;
		}
	}
};

void SignalTest::setUp()
{

}

void SignalTest::tearDown()
{

}

void SignalTest::simpleObserverTest()
{
	HelloObserver obs1;
	WorldObserver obs2;

	Subject sub;
	sub.subscribe(&obs1);
	sub.subscribe(&obs2);
	sub.notify();

	sub.unsubscribe(&obs1);
	sub.notify();
}

void SignalTest::complexObserverTest()
{
	FloatObserver obs1;
	IntObserver obs2;

	Numbers sub;
	sub.subscribe(&obs1);
	sub.subscribe(&obs2);
	sub.notify();

	sub.setInt(1);
	sub.setFloat(2.0);
	sub.setFloat(3.0);
	sub.setInt(4);

	sub.unsubscribe(&obs1);
	sub.unsubscribe(&obs2);
	sub.setFloat(100.0);
	sub.setInt(100);
}
