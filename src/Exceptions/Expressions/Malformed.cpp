// ============================================================================
//! @file Malformed.cpp
//! @author Michael P. MIscho
//! @date April 29, 2023
//! @brief This file is the header for the Integer number type header.
//! @see https://en.wikipedia.org/wiki/Complex_number
// ____________________________________________________________________________
//! @copyright Copyright (C) 2024 Michael P. Mischo - All Rights Reserved
//! You may use, distribute and modify this code under the terms of the GPL
//! license. You should have received a copy of the GPL license with this 
//! file. If not, please write to: , or visit :
//! https://www.gnu.org/licenses/gpl-3.0.en.html
// ============================================================================
#include <Exceptions/Expressions/Malformed.h>
#include <codecvt>
#include <string>


//  __________________________________________________________________________
// |                                                                          |
// | Class: Malformed                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Malformed::Malformed(const char* explanation_in,
        const Token_t& expression_in,
        size_t location_in) :
    std::exception(),
    explanation("Expression is Malformed! ")
{
    this->explanation.append(explanation_in);
    this->explanation.append("\n");
    this->explanation.append(expression_in);
    this->explanation.append("\n");

    std::string location;
	location.insert(location.begin(), location_in,' ');
    location.append("^");

    this->explanation.append(location);


}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Malformed                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Malformed::Malformed(const std::string& explanation_in,
	    const Token_t& expression_in,
	    size_t location_in) :
	std::exception(),
	explanation("Expression is Malformed! ")
{
	this->explanation.append(explanation_in);
	this->explanation.append("\n");
	this->explanation.append(expression_in);
	this->explanation.append("\n");

	std::string location;
	location.insert(location.begin(), location_in, ' ');
	location.append("^");

	this->explanation.append(location);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Malformed                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Malformed::Malformed(const Malformed& rhs) :
    std::exception(),
    explanation(rhs.explanation)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Malformed                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Malformed::Malformed(const Malformed&& rhs) :
    std::exception(),
	explanation(rhs.explanation)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Malformed                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Malformed& 
Mathematics::Expressions::Malformed::operator=(const Malformed& rhs)
{
    this->explanation = rhs.explanation;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Malformed                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Malformed& 
Mathematics::Expressions::Malformed::operator=(Malformed&& rhs)
{
    this->explanation = rhs.explanation;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Malformed                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
const char* Mathematics::Expressions::Malformed::what() const noexcept
{
	return this->explanation.c_str();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Malformed                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Malformed::~Malformed()
{
}
