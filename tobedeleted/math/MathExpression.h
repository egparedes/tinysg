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
 * MathExpression.h
 *
 *  Created on: Jul 17, 2008
 *      Author: yamokosk
 */

#ifndef MATHEXPRESSION_H_
#define MATHEXPRESSION_H_

#include <string>
#include <vector>

#include "MathPrerequisites.h"

class ExpressionFactory
{
public:
	static Real getAsReal(const std::string& expr);
	static int getAsInt(const std::string& expr);

	template<class T>
	static T getAsSequence(const std::string& expr, unsigned int len)
	{
		std::vector<Real> v; v.resize(len);
		parseVector(expr.c_str(), v);
		return T(&v[0]);
	};

private:
	static Real parseValue(const char* str);
	static void parseVector(const char* str, std::vector<Real>&);
};

#endif /* MATHEXPRESSION_H_ */
