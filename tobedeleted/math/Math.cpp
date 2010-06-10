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

#include "Math.h"
#include "asm_math.h"
#include "Constants.h"

using namespace constants;

bool Math::RealEqual( Real a, Real b, Real tolerance )
{
	if (fabs(b-a) <= tolerance)
		return true;
	else
		return false;
}
//-----------------------------------------------------------------------
Real Math::InvSqrt(Real fValue)
{
	return Real(asm_rsq(fValue));
}
//-----------------------------------------------------------------------
Real Math::UnitRandom ()
{
	return asm_rand() / asm_rand_max();
}

//-----------------------------------------------------------------------
Real Math::RangeRandom (Real fLow, Real fHigh)
{
	return (fHigh-fLow)*UnitRandom() + fLow;
}

//-----------------------------------------------------------------------
Real Math::SymmetricRandom ()
{
	return 2.0f * UnitRandom() - 1.0f;
}

Real Math::gaussianDistribution(Real x, Real offset, Real scale)
{
	Real nom = Math::Exp(
		-Math::Sqr(x - offset) / (2 * Math::Sqr(scale)));
	Real denom = scale * Math::Sqrt(2 * pi);

	return nom / denom;

}

