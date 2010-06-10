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
 * MathPrerequisites.h
 *
 *  Created on: Dec 1, 2008
 *      Author: yamokosk
 */

#ifndef MATHPREREQUISITES_H_
#define MATHPREREQUISITES_H_

#include "config.h"

#include <cmath>
#include <limits>		// For numeric limits
#include <algorithm>	// For min() and max
#include <cassert>
#include <cstring>

#ifdef _USE_DOUBLE_PRECISION_
typedef double Real;
#else
typedef float Real;
#endif

#endif /* MATHPREREQUISITES_H_ */
