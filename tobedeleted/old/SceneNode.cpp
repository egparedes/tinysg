/*************************************************************************
* TinySG, Copyright (C) 2007, 2008  J.D. Yamokoski
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

#include "SceneNode.h"
/*
#include "Exception.h"
#include "MathExpression.h"
#include "SceneGraph.h"

#include <boost/cast.hpp>

#include <iostream>
#include <sstream>

namespace TinySG {

using namespace log4cxx;

// Initialize static elements
LoggerPtr SceneNode::logger(Logger::getLogger("TinySG.Node"));

// ****************************************************************************

// Class implementation
SceneNode::SceneNode() :
	parent_(NULL),
	level_(0),
	orientation_( Quaternion::IDENTITY ),
	position_( Vector3::ZERO ),
	scale_( Vector3::UNIT_SCALE ),
	derivedOrientation_( Quaternion::IDENTITY ),
	derivedPosition_( Vector3::ZERO ),
	derivedScale_( Vector3::UNIT_SCALE ),
	cachedTransform_( Matrix4::IDENTITY ),
	validWorldTransform_(true),
	cachedTransformOutOfDate_(false)
{

}

SceneNode::~SceneNode()
{
	removeAllChildren();

	if (parent_)
		parent_->removeChild(this);

	// Remove ourselves from the update queue
	//dequeueForUpdate(this);

	// Detach all objects, do this manually to avoid needUpdate() call
	// which can fail because of deleted items
	ObjectMap::iterator itr;
	MovableObject* ret;
	for ( itr = sceneObjects_.begin(); itr != sceneObjects_.end(); ++itr )
	{
		ret = itr->second;
		ret->notifyAttached((SceneNode*)0);
	}
	sceneObjects_.clear();
}

Object* SceneNode::clone() const
{
	return new SceneNode(*this);
}

void SceneNode::save(PropertyCollection& pc) const
{
	// Class identifier
	pc.addPair( RequiredProperty("class", getType()) );

	// Required object information
	pc.addPair( RequiredProperty("name", getName()) );

	// Optional information
	if ( hasParent() ) pc.addPair( OptionalProperty("parent", getParent()->getName()) );

	// Not really optional but looks better if the following is set as parameters
	pc.addPair( OptionalProperty("position", getPosition().toString() ) );
	pc.addPair( OptionalProperty("orientation", getOrientation().toString() ) );
	pc.addPair( OptionalProperty("scale", getScale().toString() ) );
}

//! Adds a (precreated) child scene node to this node.
void SceneNode::addChild (SceneNode* child)
{
	if ( child->hasParent() )
	{
		SML_EXCEPT(Exception::ERR_INVALIDPARAMS,
			"Node '" + child->getName() + "' already was a child of '" + child->getParent()->getName() + "'.");
	}

	if ( children_.find( child->getName() ) != children_.end())
	{
		SML_EXCEPT(Exception::ERR_DUPLICATE_ITEM, "Node with identical name already attached to this node.");
	}

	children_[child->getName()] = child;
	child->setParent(this);
}

//! Reports the number of child nodes under this one.
unsigned short SceneNode::numChildren (void) const
{
	return static_cast< unsigned short >( children_.size() );
}

//! Gets a pointer to a child node.
SceneNode* SceneNode::getChild (unsigned short index) const
{
	if( index < children_.size() )
	{
		ConstChildNodeIterator i = children_.begin();
		while (index--) ++i;
		return i->second;
	} else {
		SML_EXCEPT(Exception::ERR_INVALIDPARAMS, "Child index out of bounds.");
	}
}

//! Gets a pointer to a named child node.
SceneNode* SceneNode::getChild (const std::string& name) const
{
	ConstChildNodeIterator i = children_.find(name);

	if (i == children_.end())
	{
		SML_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, "Child node named " + name + " does not exist.");
	}
	return i->second;
}

//! Drops the specified child from this node.
SceneNode* SceneNode::removeChild (unsigned short index)
{
	SceneNode* ret;
	if (index < children_.size())
	{
		ChildNodeIterator i = children_.begin();
		while (index--) ++i;
		ret = i->second;

		children_.erase(i);
		ret->setParent(NULL);
		return ret;
	}
	else
	{
		SML_EXCEPT(Exception::ERR_INVALIDPARAMS, "Child index out of bounds.");
	}
	return 0;
}

//! Drops the specified child from this node.
SceneNode* SceneNode::removeChild (SceneNode *child)
{
	if (child)
		removeChild( child->getName() );
	return child;
}

//! Drops the named child from this node.
SceneNode* SceneNode::removeChild (const std::string &name)
{
	ChildNodeIterator i = children_.find(name);

	if (i == children_.end())
	{
		SML_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, "Child node named " + name + " does not exist.");
	}

	SceneNode* ret = i->second;
	children_.erase(i);
	ret->setParent(NULL);

	return ret;
}

//! Removes all child Nodes attached to this node.
void SceneNode::removeAllChildren (void)
{
	ChildNodeMap::iterator i, iend;
	iend = children_.end();
	for (i = children_.begin(); i != iend; ++i)
	{
		i->second->setParent(0);
	}
	children_.clear();
}

//! Gets the parent of this SceneNode.
SceneNode* SceneNode::getParent(void) const
{
	return parent_;
}


void SceneNode::setOrientation (const Quaternion &q)
{
	LOG4CXX_TRACE(logger, "Entering " << __FUNCTION__ );
	orientation_ = q;
	notifyUpdate( PoseChangedBit );
}

void SceneNode::setOrientation (Real w, Real x, Real y, Real z)
{
	Quaternion q(w, x, y, z);
	setOrientation(q);
}

void SceneNode::setPosition(const Vector3 &pos)
{
	LOG4CXX_TRACE(logger, "Entering " << __FUNCTION__ );
	position_ = pos;
	notifyUpdate( PoseChangedBit );
}

void SceneNode::setPosition(Real x, Real y, Real z)
{
	LOG4CXX_TRACE(logger, "Entering " << __FUNCTION__ );
	Vector3 v(x, y, z);
	setPosition(v);
}

void SceneNode::setScale(const Vector3 &s)
{
	scale_ = s;
	notifyUpdate( ScaleChangedBit );
}

void SceneNode::setScale(Real x, Real y, Real z)
{
	Vector3 s(x, y, z);
	setScale(s);
}

const Matrix4& SceneNode::getFullTransform() const
{
	if ( cachedTransformOutOfDate_ )
	{
		LOG4CXX_TRACE(logger, "Cached transform out of date. Calling update method.");
		updateCachedTransform();
		cachedTransformOutOfDate_ = false;
	} else {
		LOG4CXX_TRACE(logger, "Cached transform is OK.");
	}
	return cachedTransform_;
}

void SceneNode::updateCachedTransform() const
{
	//cachedTransform_ = RotFromQuaternion( getOrientation() );
	//cachedTransform_.SubMatrix(1,3,4,4) = getPosition();
	cachedTransform_.makeTransform(getPosition(), getScale(), getOrientation());
}

const Quaternion& SceneNode::getParentOrientation() const
{
	return parent_->getDerivedOrientation();
}

const Vector3& SceneNode::getParentPosition() const
{
	return parent_->getDerivedPosition();
}

const Vector3& SceneNode::getParentScale() const
{
	return parent_->getDerivedScale();
}

const Quaternion& SceneNode::getDerivedOrientation()
{
	return derivedOrientation_;
}

const Vector3& SceneNode::getDerivedPosition()
{
	return derivedPosition_;
}

const Vector3& SceneNode::getDerivedScale()
{
	return derivedScale_;
}

//! Moves the node along the cartesian axes.
void SceneNode::translate(const Vector3 &d, TransformSpace relativeTo)
{
	switch(relativeTo)
	{
	case TS_LOCAL:
		// position is relative to parent so transform downwards
		position_ += (orientation_ * d);
		break;
	case TS_WORLD:
		// position is relative to parent so transform upwards
		if (parent_)
		{
			Quaternion qi( parent_->getDerivedOrientation().Inverse() );
			position_ += (qi * d); //	/ parent_->_getDerivedScale();
		}
		else
		{
			position_ += d;
		}
		break;
	case TS_PARENT:
		position_ += d;
		break;
	}
	notifyUpdate( PoseChangedBit );
}

//! Moves the node along the cartesian axes.
void SceneNode::translate(Real x, Real y, Real z, TransformSpace relativeTo)
{
	Vector3 v(x, y, z);
	translate(v, relativeTo);
}

//! Moves the node along arbitrary axes.
void SceneNode::translate(const Matrix3 &axes, const Vector3 &move, TransformSpace relativeTo)
{
	Vector3 derived = axes * move;
	translate(derived, relativeTo);
}

//! Moves the node along arbitrary axes.
void SceneNode::translate(const Matrix3 &axes, Real x, Real y, Real z, TransformSpace relativeTo)
{
	Vector3 d(x, y, z);
	translate(axes,d,relativeTo);
}

//! Rotate the node around an arbitrary axis.
void SceneNode::rotate(const Vector3 &axis, Real angle, TransformSpace relativeTo)
{
	Quaternion q(angle, axis);
	rotate(q, relativeTo);
}

//! Rotate the node around an aritrary axis using a Quarternion.
void SceneNode::rotate(const Quaternion &q, TransformSpace relativeTo)
{
	switch(relativeTo)
	{
	case TS_LOCAL:
		// Note the order of the mult, i.e. q comes after
		orientation_ = orientation_ * q;
		break;
	case TS_WORLD:
		// Rotations are normally relative to local axes, transform up
		if (parent_)
		{
			Quaternion qi( parent_->getDerivedOrientation().Inverse() );
			orientation_ = orientation_ * qi * q * getDerivedOrientation();
		} else {

		}
		break;
	case TS_PARENT:
		// Rotations are normally relative to local axes, transform up
		orientation_ = q * orientation_;
		break;
	}
	notifyUpdate( PoseChangedBit );
}


//-----------------------------------------------------------------------
void SceneNode::attachObject(MovableObject* obj)
{
	if ( obj->isAttached() )
	{
		SML_EXCEPT(Exception::ERR_INVALIDPARAMS, "Object already attached to a Node.");
	}

	if ( sceneObjects_.find( obj->getName() ) != sceneObjects_.end())
	{
		SML_EXCEPT(Exception::ERR_DUPLICATE_ITEM, "Object with identical name already attached to this node.");
	}

	sceneObjects_[obj->getName()] = obj;
	obj->notifyAttached(this);

	// Make sure bounds get updated (must go right to the top)
	notifyUpdate( BoundsChangedBit );
}

unsigned short SceneNode::numAttachedObjects(void) const
{
	return static_cast< unsigned short >( sceneObjects_.size() );
}

MovableObject* SceneNode::getAttachedObject(unsigned short index)
{
	if (index < sceneObjects_.size())
	{
		ObjectMap::iterator i = sceneObjects_.begin();
		// Increment (must do this one at a time)
		while (index--)++i;

		return i->second;
	}
	else
	{
		SML_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, "Object index out of bounds.");
	}
	return 0;
}

MovableObject* SceneNode::getAttachedObject(const std::string& name)
{
	// Look up
	ObjectMap::iterator i = sceneObjects_.find(name);

	if (i == sceneObjects_.end())
	{
		SML_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, "Attached object " + name + " not found.");
	}

	return i->second;

}

MovableObject* SceneNode::detachObject(unsigned short index)
{
	MovableObject* ret;
	if (index < sceneObjects_.size())
	{

		ObjectMap::iterator i = sceneObjects_.begin();
		// Increment (must do this one at a time)
		while (index--)++i;

		ret = i->second;
		sceneObjects_.erase(i);
		ret->notifyAttached((SceneNode*)0);

		// Make sure bounds get updated (must go right to the top)
		notifyUpdate( BoundsChangedBit );

		return ret;

	}
	else
	{
		SML_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, "Object index out of bounds.");
	}
	return 0;

}

MovableObject* SceneNode::detachObject(const std::string& name)
{
	ObjectMap::iterator it = sceneObjects_.find(name);
	if (it == sceneObjects_.end())
	{
		SML_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, "Object " + name + " is not attached to this node.");
	}
	MovableObject* ret = it->second;
	sceneObjects_.erase(it);
	ret->notifyAttached((SceneNode*)0);
	// Make sure bounds get updated (must go right to the top)
	notifyUpdate( BoundsChangedBit );

	return ret;
}

void SceneNode::detachObject(MovableObject* obj)
{
	ObjectMap::iterator i, iend;
	iend = sceneObjects_.end();
	for (i = sceneObjects_.begin(); i != iend; ++i)
	{
		if (i->second == obj)
		{
			sceneObjects_.erase(i);
			break;
		}
	}
	obj->notifyAttached((SceneNode*)0);

	// Make sure bounds get updated (must go right to the top)
	notifyUpdate( BoundsChangedBit );
}

void SceneNode::detachAllObjects(void)
{
	ObjectMap::iterator itr;
	MovableObject* ret;
	for ( itr = sceneObjects_.begin(); itr != sceneObjects_.end(); itr++ )
	{
		ret = itr->second;
		ret->notifyAttached((SceneNode*)0);
	}
	sceneObjects_.clear();
	// Make sure bounds get updated (must go right to the top)
	notifyUpdate( BoundsChangedBit );
}


//-----------------------------------------------------------------------
void SceneNode::updateFromParent()
{
	if ( hasParent()  )
	{
		// Set level
		//level_ = getParent()->getLevel() + 1;

		derivedOrientation_ = getParentOrientation() * orientation_;

		//derivedScale_ = parentScale * scale_;
		derivedScale_ = getParentScale();
		// Update scale

		// Change position vector based on parent's orientation & scale
		//derivedPosition_ = parentOrientation * (parentScale_ * position_);
		derivedPosition_ = getParentOrientation() * position_;

		// Add altered position vector to parents
		derivedPosition_ += getParentPosition();
	} else {
		level_ = 0;

		// Root node, no parent
		derivedOrientation_ = orientation_;
		derivedPosition_ = position_;
		derivedScale_ = scale_;
	}

	validWorldTransform_ = true;

	// Notify objects that it has been moved
	ObjectMap::const_iterator i;
	for (i = sceneObjects_.begin(); i != sceneObjects_.end(); ++i)
	{
		MovableObject* object = i->second;
		object->notifyMoved();
	}
}

void SceneNode::update(uint8_t flags)
{
	//LOG4CXX_TRACE(logger, "Entering " << __FUNCTION__ << " for node \"" << getName() << "\" with flags: " << (unsigned int)flags );

	uint8_t childFlags = 0;
	if ( (flags & ParentChangedBit) || !validWorldTransform_ )
	{
		updateFromParent();
		childFlags |= ParentChangedBit;
	}

	//LOG4CXX_INFO(logger, "Setting child flags to: " << (unsigned int)childFlags );
	ChildNodeMap::iterator i, iend;
	iend = children_.end();
	for (i = children_.begin(); i != iend; ++i)
	{
		i->second->update( childFlags );
	}
}

void SceneNode::notifyUpdate(uint8_t hint)
{
	//notifyChildren(hint);
	validWorldTransform_ = false;
	cachedTransformOutOfDate_ = true;
}

void SceneNode::setParent(SceneNode *parent)
{
	bool different = (parent != parent_);

	parent_ = parent;

	if (different)
		notifyUpdate( ParentChangedBit );
}

void SceneNode::setParent(const std::string& name)
{
	SceneNode* parent = getAndCastManager<SceneGraph>()->getNode(name);
	setParent(parent);
}

// ****************************************************************************
Object* SceneNodeFactory::createInstanceImpl(const PropertyCollection* params)
{
	SceneNode* node = new SceneNode();

	if ( params->hasProperty("parent") )
	{
		node->setParent( params->getValue("parent") );
	}

	if ( params->hasProperty("position") )
	{
		Vector3 pos = ExpressionFactory::getAsSequence<Vector3>(params->getValue("position"), 3);
		node->setPosition( pos );
	}

	if ( params->hasProperty("orientation") )
	{
		Quaternion q = ExpressionFactory::getAsSequence<Quaternion>(params->getValue("orientation"), 4);
		node->setOrientation( q );
	}

	if ( params->hasProperty("scale") )
	{
		Vector3 scale = ExpressionFactory::getAsSequence<Vector3>(params->getValue("scale"), 3);
		node->setScale( scale );
	}

	return node;
}

void SceneNodeFactory::destroyInstance(Object* obj)
{
	SceneNode* n = dynamic_cast<SceneNode*>(obj);
	delete n;
}

} // Namespace: TinySG

*/
/*ostream& operator << (ostream& os, const TinySG::SceneNode& s)
{
	return os << "Name: " << s.getName() << std::endl
	   << "Tmatrix: " << std::endl << s.getFullTransform() << std::endl;
}*/
