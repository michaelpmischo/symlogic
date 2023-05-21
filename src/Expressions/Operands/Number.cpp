// ============================================================================
//! @file Number.cpp
//! @author Michael P. MIscho
//! @date May 12, 2023
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
#include <Expressions/Operands/Number.h>

// Included for Calculus Operations.
#include <Expressions/Operands/Variable.h>
#include <Expressions/Operations/Arithmatic/InfixBinary.h>

//  __________________________________________________________________________
// |                                                                          |
// | Class: Number                                                            |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Number::Number(const Real& value_in, 
        const TokenPair_t& parentheses_in) :
    Operand(value_in, parentheses_in),
    value(value_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Number                                                            |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Number::Number(const Number& rhs) :
    Operand(rhs),
    value(rhs.value)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Number                                                            |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Number::Number(const Number& rhs, 
        const TokenPair_t& parentheses_in) :
    Operand(rhs, parentheses_in),
    value(rhs.value)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Number                                                            |
// | Function: Move Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Number::Number(Number&& rhs) :
    Operand(rhs),
    value(rhs.value)
{
}

//  __________________________________________________________________________
// |                                                                          |
// | Class: Number                                                            |
// | Function: Assignment Operator                                            |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Number&
Mathematics::Expressions::Operands::Number::operator=(const Number& rhs)
{
    Operand::operator=(rhs);
    this->value = rhs.value;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Number                                                            |
// | Function: Move Operator                                                  |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Number&
Mathematics::Expressions::Operands::Number::operator=(Number&& rhs)
{
    Operand::operator=(rhs);
    this->value = rhs.value;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Number                                                            |
// | Function: operator==                                                     |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operands::Number::operator==(
        const Number& rhs) const
{
    return (this->value == rhs.value);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Number                                                            |
// | Function: contains_variable                                              |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operands::Number::contains_variable() const
{
    return false;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Number                                                            |
// | Function: copy                                                           |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operands::Number::copy(
        const TokenPair_t& parentheses_in) const
{
    return new Number(*this, parentheses_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Number                                                            |
// | Function: derivative                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operands::Number::derivative(
        const Token_t& token_in) const
{
    return new Number(0);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Number                                                            |
// | Function: integral                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operands::Number::integral(
        const Token_t& token_in) const
{
    return new Operations::Arithmatic::InfixBinary(L"*" , 
        this->copy(),
        new Variable(token_in));
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Number                                                            |
// | Function: solution                                                       |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operands::Number::solution(
        const TokenValueMap_t& values_in) const
{
    return this->value;
}



//  __________________________________________________________________________
// |                                                                          |
// | Class: Number                                                            |
// | Function: solution                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Operands::Number::get_variables() const
{
    return {};
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Number                                                            |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operands::Number::is_token(
        const Token_t& token_in)
{
    return (token_in.find_first_not_of(L"0123456789.") == 
        Token_t::npos);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Number                                                            |
// | Function: get_precedence                                                 |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenPrecedence_t
Mathematics::Expressions::Operands::Number::get_precedence(Type_t type_in, 
        const Token_t& token_in)
{

    return MAX_PRECEDENCE;
}

//  __________________________________________________________________________
// |                                                                          |
// | Class: Number                                                            |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
void Mathematics::Expressions::Operands::Number::print(TokenStream_t& stream,
    const Token_t& prefix_in,
    bool is_last) const
{
    stream << prefix_in << (!is_last ? L"├──" : L"└──") << L"(" <<
        this->value << L")" << std::endl;
}


