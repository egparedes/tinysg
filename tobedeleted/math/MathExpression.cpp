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
 * ExpressionFactory.cpp
 *
 *  Created on: Jul 17, 2008
 *      Author: yamokosk
 */

#include "MathExpression.h"
#include <cstring>

#include "Constants.h"
using namespace constants;

#if defined(HAVE_MUPARSER)
#include <muParser/muParser.h>

Real ExpressionFactory::getAsReal(const std::string& expr)
{
	return parseValue( expr.c_str() );
}

int ExpressionFactory::getAsInt(const std::string& expr)
{
	return (int)parseValue( expr.c_str() );
}

Real ExpressionFactory::parseValue(const char* str)
{
	mu::Parser parser_;
	parser_.DefineConst("pi", pi);
	parser_.DefineConst("e", e);

	// Give expression to parser
	parser_.SetExpr(str);
	// Evaluate string
	return (Real)parser_.Eval();
}

void ExpressionFactory::parseVector(const char* str, std::vector<Real>& data)
{
	mu::Parser parser_;
	parser_.DefineConst("pi", pi);
	parser_.DefineConst("e", e);

	// Copy incoming char buffer to local one
	int length = strlen(str);
	char* buf = new char[length+1];

	memset(buf, '\0', (length+1)*sizeof(char));
	memcpy(buf, str, length*sizeof(char));

	// Step through each token, evaluate it, and store it in our return vector
	char* tok = strtok(buf, " ,");
	for (unsigned int n=0; n < data.size(); ++n)
	{
		if ( tok == NULL ) break;

		try {
			//Real val = parseValue(tok);
			//values.push_back( val );
			data[n] = parseValue(tok);
		} catch (mu::Parser::exception_type &e) {
			std::cout << e.GetMsg() << std::endl;
		}

		// Get new token
		tok = strtok(NULL, " ,");
	}

	// Delete temporary char buffer
	delete [] buf;
}

#else

#include <sstream>

Real ExpressionFactory::getAsReal(const std::string& expr)
{
	return parseValue( expr.c_str() );
}

int ExpressionFactory::getAsInt(const std::string& expr)
{
	return (int)parseValue( expr.c_str() );
}

Real ExpressionFactory::parseValue(const char* str)
{
	std::string in(str);
	std::istringstream stm(str);

	Real val;
	stm >> val;
	return val;
}

void ExpressionFactory::parseVector(const char* str, std::vector<Real>& data)
{
	std::string in(str);
	std::istringstream stm(str);

	Real val = 0.0;

	while ( stm.good() )
	{
		stm >> val;
		data.push_back(val);
	}
}

#endif
