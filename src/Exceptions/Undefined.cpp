// ============================================================================
//! @file Undefined.cpp
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
#include <Exceptions/Undefined.h>
#include <codecvt>
#include <string>


//  __________________________________________________________________________
// |                                                                          |
// | Class: Undefined                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Undefined::Undefined(const char* explanation_in) :
    std::exception(),
    explanation("Value is Undefined! ")
{
    this->explanation.append(explanation_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Undefined                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Undefined::Undefined(
        const std::string& explanation_in) :
    std::exception(),
    explanation("Value is Undefined! ")
{
    this->explanation.append(explanation_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Undefined                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Undefined::Undefined(const Undefined& rhs) :
    std::exception(),
    explanation(rhs.explanation)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Undefined                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Undefined::Undefined(const Undefined&& rhs) :
    std::exception(),
    explanation(rhs.explanation)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Undefined                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Undefined& 
Mathematics::Undefined::operator=(const Undefined& rhs)
{
    this->explanation = rhs.explanation;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Undefined                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Undefined& 
Mathematics::Undefined::operator=(Undefined&& rhs)
{
    this->explanation = rhs.explanation;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Undefined                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
const char* Mathematics::Undefined::what() const noexcept
{
    return this->explanation.c_str();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Undefined                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Undefined::~Undefined()
{
}
