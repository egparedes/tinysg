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

/*
 * Code taken from the OGRE (Object-oriented Graphics Rendering Engine) Project
 * http://www.ogre3d.org/
 */

#ifndef _SML_MATH_H_FILE_
#define _SML_MATH_H_FILE_

#include "Constants.h"
#include "MathPrerequisites.h"

class Math
{
public:
	static inline Real Abs (Real fValue) { return Real(fabs(fValue)); }
	static inline Real Sqr (Real fValue) { return fValue*fValue; }
	static inline Real Sqrt (Real fValue) { return Real(sqrt(fValue)); }
	static bool RealEqual(Real a, Real b, Real tolerance = std::numeric_limits<Real>::epsilon());
	template <typename T>
	static T Clamp(T val, T minval, T maxval)
	{
		assert (minval < maxval && "Invalid clamp range");
		return std::max(std::min(val, maxval), minval);
	}
	static Real InvSqrt(Real fValue);
	static Real UnitRandom ();  // in [0,1]
	static Real RangeRandom (Real fLow, Real fHigh);  // in [fLow,fHigh]
	static Real SymmetricRandom ();  // in [-1,1]
	static Real gaussianDistribution(Real x, Real offset = 0.0f, Real scale = 1.0f);
	static inline Real Exp (Real fValue) { return Real(exp(fValue)); }
};


#endif
