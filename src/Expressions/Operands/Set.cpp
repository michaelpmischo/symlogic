// ============================================================================
//! @file Set.cpp
//! @author Michael P. MIscho
//! @date May 26, 2023
//! @brief This file is the header for the Integer number type header.
//! @see 
// ____________________________________________________________________________
//! @copyright Copyright (C) 2023 Michael P. Mischo - All Rights Reserved
//! 
//! This program is free software; you can redistribute it and /or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation; either version 2 of the License, or
//! (at your option) any later version.
//!
//! This program is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//! GNU General Public License for more details.
//! 
//! You should have received a copy of the GNU General Public License
//! along with this program; if not, write to the Free Software
//! Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110 - 
//! 1301  USA
//! 
//! You may use, distribute and modify this code under the terms of the GPL
//! license. You should have received a copy of the GPL license with this 
//! file. If not, please write to: , or visit :
//! https://www.gnu.org/licenses/gpl-3.0.en.html
// ============================================================================
#include <Expressions/Operands/Set.h>


//  __________________________________________________________________________
// |                                                                          |
// | Class: Set                                                               |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Set::Set(
        const Token_t& token_in,
        const std::set<Real> elements_in,
        const TokenPair_t& parentheses_in) :
	Operand(token_in, parentheses_in),
    elements(elements_in)
{
    if (this->get_type() != Type_t::SET)
    {
        std::stringstream stream;
        stream << this->get_token() << " is not an Set!" << std::endl;
        throw(stream.str());
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Set                                                               |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Set::Set(const Set& rhs) :
    Operand(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Set                                                               |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Set::Set(const Set& rhs, 
        const TokenPair_t& parentheses_in) :
    Operand(rhs, parentheses_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Set                                                               |
// | Function: Move Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Set::Set(Set&& rhs) :
    Operand(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Set                                                               |
// | Function: Assignment Operator                                            |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Set& 
Mathematics::Expressions::Operands::Set::operator=(const Set& rhs)
{
    Operand::operator=(rhs);
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Set                                                               |
// | Function: Move Operator                                                  |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Set&
Mathematics::Expressions::Operands::Set::operator=(Set&& rhs)
{
    Operand::operator=(rhs);
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Set                                                               |
// | Function: contains_variable                                              |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operands::Set::contains_variable() const
{
    return true;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Set                                                               |
// | Function: copy                                                           |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operands::Set::copy(
        const TokenPair_t& parentheses_in) const
{
    return new Set(*this, parentheses_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Set                                                               |
// | Function: derivative                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operands::Set::derivative(
        const Token_t& token_in) const
{
    return this->copy();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Set                                                               |
// | Function: integral                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operands::Set::integral(
        const Token_t& token_in) const
{
    return this->copy();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Set                                                               |
// | Function: solution                                                       |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operands::Set::solution(
        const TokenValueMap_t& values_in) const
{
    return NAN;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Set                                                               |
// | Function: solution                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Operands::Set::get_variables() const
{
    return {this->get_token()};
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Set                                                               |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operands::Set::is_token(
        const Token_t& token_in)
{
	if (token_in.empty())
	{
		return false;
	}

    return false;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Set                                                               |
// | Function: get_precedence                                                 |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenPrecedence_t
Mathematics::Expressions::Operands::Set::get_precedence(
        Type_t type_in, 
        const Token_t& token_in)
{
    return MAX_PRECEDENCE;
}

