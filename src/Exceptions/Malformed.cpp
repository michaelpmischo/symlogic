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
Mathematics::Exceptions::Malformed::Malformed(const char* explanation_in,
        const std::string& malformaed_expression_in,
        size_t malformed_location_in) :
    std::exception(),
    explanation("Expression is Malformed! "),
    malformed_expression("    "),
    malformed_location("    ")
{
    this->explanation.append(explanation_in);
    this->malformed_expression.append(malformaed_expression_in);

	this->malformed_location.insert(
        this->malformed_location.begin(), 
        malformed_location_in,
        ' ');
    this->malformed_location.append("^");
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Malformed                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Exceptions::Malformed::Malformed(const std::string& explanation_in,
	    const Token_t& malformaed_expression_in,
	    size_t malformed_location_in) :
	std::exception(),
	explanation("Expression is Malformed! "),
	malformed_expression("    "),
	malformed_location("    ")
{
	this->explanation.append(explanation_in);
	this->malformed_expression.append(malformaed_expression_in);

	this->malformed_location.insert(
		this->malformed_location.begin(),
        malformed_location_in,
		' ');
    this->malformed_location.append("^");
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Malformed                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Exceptions::Malformed::Malformed(const Malformed& rhs) :
    std::exception(),
    explanation(rhs.explanation),
    malformed_expression(rhs.malformed_expression),
    malformed_location(rhs.malformed_location)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Malformed                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Exceptions::Malformed::Malformed(const Malformed&& rhs) :
    std::exception(),
	explanation(rhs.explanation),
    malformed_expression(rhs.malformed_expression),
	malformed_location(rhs.malformed_location)
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
    this->malformed_expression = rhs.malformed_expression;
    this->malformed_location = rhs.malformed_location;
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
	this->malformed_expression = rhs.malformed_expression;
	this->malformed_location = rhs.malformed_location;
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
Mathematics::Token_t 
Mathematics::Exceptions::Malformed::what(void* __unused) const noexcept
{
    TokenStream_t error;
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
