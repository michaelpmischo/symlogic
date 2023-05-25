// ============================================================================
//! @file Syntax.cpp
//! @author Michael P. MIscho
//! @date May 24, 2023
//! @brief This file is the header for the Integer number type header.
//! @see https://en.wikipedia.org/wiki/Complex_number
// ____________________________________________________________________________
//! @copyright Copyright (C) 2024 Michael P. Mischo - All Rights Reserved
//! You may use, distribute and modify this code under the terms of the GPL
//! license. You should have received a copy of the GPL license with this 
//! file. If not, please write to: , or visit :
//! https://www.gnu.org/licenses/gpl-3.0.en.html
// ============================================================================
#include <Exceptions/Commands/Syntax.h>


//  __________________________________________________________________________
// |                                                                          |
// | Class: Syntax                                                            |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::UI::Core::Syntax::Syntax(const char* explanation_in,
        const std::string& string_in,
        size_t location_in) :
    std::exception(),
    explanation("Syntax Error! ")
{
    this->explanation.append(explanation_in);
    this->explanation.append("\n");
    this->explanation.append(string_in);
    this->explanation.append("\n");

    std::string location;
	location.insert(location.begin(), location_in,' ');
    location.append("^");

    this->explanation.append(location);


}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Syntax                                                            |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::UI::Core::Syntax::Syntax(const std::string& explanation_in,
	    const std::string& string_in,
	    size_t location_in) :
	std::exception(),
	explanation("Syntax Error! ")
{
	this->explanation.append(explanation_in);
	this->explanation.append("\n");
	this->explanation.append(string_in);
	this->explanation.append("\n");

	std::string location;
	location.insert(location.begin(), location_in, ' ');
	location.append("^");

	this->explanation.append(location);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Syntax                                                            |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::UI::Core::Syntax::Syntax(const Syntax& rhs) :
    std::exception(),
    explanation(rhs.explanation)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Syntax                                                            |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::UI::Core::Syntax::Syntax(const Syntax&& rhs) :
    std::exception(),
	explanation(rhs.explanation)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Syntax                                                            |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::UI::Core::Syntax&
Mathematics::UI::Core::Syntax::operator=(const Syntax& rhs)
{
    this->explanation = rhs.explanation;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Syntax                                                            |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::UI::Core::Syntax&
Mathematics::UI::Core::Syntax::operator=(Syntax&& rhs)
{
    this->explanation = rhs.explanation;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Syntax                                                            |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
const char* Mathematics::UI::Core::Syntax::what() const noexcept
{
	return this->explanation.c_str();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Syntax                                                            |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::UI::Core::Syntax::~Syntax()
{
}
