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
#include <Exceptions/Malformed.h>
#include <codecvt>
#include <string>


//  __________________________________________________________________________
// |                                                                          |
// | Class: Malformed                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Exceptions::Malformed::Malformed(const wchar_t* explanation_in,
        const Expressions::Token_t& malformaed_expression_in,
        size_t malformed_location_in) :
    std::exception(),
    explanation(L"Expression is Malformed! "),
    malformed_expression(L"    "),
    malformed_location(L"    ")
{
    this->explanation.append(explanation_in);
    this->malformed_expression.append(malformaed_expression_in);

	this->malformed_location.insert(
        this->malformed_location.begin(), 
        malformed_location_in,
        L' ');
    this->malformed_location.append(L"^");
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Malformed                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Exceptions::Malformed::Malformed(
        const Expressions::Token_t& explanation_in,
	    const Expressions::Token_t& malformaed_expression_in,
	    size_t malformed_location_in) :
	std::exception(),
	explanation(L"Expression is Malformed! "),
	malformed_expression(L"    "),
	malformed_location(L"    ")
{
	this->explanation.append(explanation_in);
	this->malformed_expression.append(malformaed_expression_in);

	this->malformed_location.insert(
		this->malformed_location.begin(),
        malformed_location_in,
		L' ');
    this->malformed_location.append(L"^");
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Malformed                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Exceptions::Malformed::Malformed(const Malformed& rhs) :
    std::exception(),
    explanation(rhs.explanation)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Malformed                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Exceptions::Malformed::Malformed(const Malformed&& rhs) :
    std::exception(),
    explanation(rhs.explanation)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Malformed                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Exceptions::Malformed& 
Mathematics::Exceptions::Malformed::operator=(const Malformed& rhs)
{
    this->explanation = rhs.explanation;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Malformed                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Exceptions::Malformed& 
Mathematics::Exceptions::Malformed::operator=(Malformed&& rhs)
{
    this->explanation = rhs.explanation;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Malformed                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
const char* Mathematics::Exceptions::Malformed::what() const noexcept
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::stringstream error;
    error << converter.to_bytes(this->explanation) << std::endl <<  
        converter.to_bytes(this->malformed_expression) << std::endl <<
        converter.to_bytes(this->malformed_location);
	return error.str().c_str();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Malformed                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Token_t 
Mathematics::Exceptions::Malformed::what_utf16() const noexcept
{
    Expressions::TokenStream_t error;
    error << this->explanation << std::endl <<
        this->malformed_expression << std::endl <<
        this->malformed_location << std::endl;
	return error.str();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Malformed                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Exceptions::Malformed::~Malformed()
{
}
