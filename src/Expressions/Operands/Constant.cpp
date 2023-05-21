// ============================================================================
//! @file Constant.cpp
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
#include <Expressions/Operands/Constant.h>

// Included for Calculus Operations.
#include <Expressions/Operands/Number.h>
#include <Expressions/Operands/Variable.h>
#include <Expressions/Operations/Arithmatic/InfixBinary.h>

const Mathematics::Expressions::Operands::Constant::ConstantHash_t 
Mathematics::Expressions::Operands::Constant::constants =
{
    {L"pi",	    Mathematics::𝝅},
    {L"e",	    Mathematics::ℯ},

#if defined(__UTF16_EXPRESSIONS__)
    {L"𝝅",      Mathematics::𝝅},
    {L"ℯ",      Mathematics::ℯ},
    {L"φ",      Mathematics::φ},
#endif

};


//  __________________________________________________________________________
// |                                                                          |
// | Class: Constant                                                          |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Constant::Constant(const Token_t& token_in,
        const TokenPair_t& parentheses_in) :
    Operand(token_in, parentheses_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Constant                                                          |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Constant::Constant(const Constant& rhs) :
    Operand(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Constant                                                          |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Constant::Constant(const Constant& rhs, 
        const TokenPair_t& parentheses_in) :
    Operand(rhs, parentheses_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Constant                                                          |
// | Function: Move Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Constant::Constant(Constant&& rhs) :
    Operand(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Constant                                                          |
// | Function: Assignment Operator                                            |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Constant& 
Mathematics::Expressions::Operands::Constant::operator=(
        const Constant& rhs)
{
    Operand::operator=(rhs);
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Constant                                                          |
// | Function: Move Operator                                                  |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Constant& 
Mathematics::Expressions::Operands::Constant::operator=(
        Constant&& rhs)
{
    Operand::operator=(rhs);
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Constant                                                          |
// | Function: contains_variable                                              |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operands::Constant::contains_variable() const 
{
    return false;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Constant                                                          |
// | Function: contains_variable                                              |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operands::Constant::copy(
        const TokenPair_t& parentheses_in) const
{
    return new Constant(*this, parentheses_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Constant                                                          |
// | Function: derivative                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operands::Constant::derivative(
        const Token_t& token_in) const
{
    return new Number(0);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Constant                                                          |
// | Function: integral                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operands::Constant::integral(
        const Token_t& token_in) const
{
    if (this->contains(token_in))
    {
        return new Operations::Arithmatic::InfixBinary(L"*", 
            this->copy(),
            new Variable(token_in));
    }
    else
    {
        return this->copy();
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Constant                                                          |
// | Function: solution                                                       |
// |__________________________________________________________________________|
Mathematics::Real Mathematics::Expressions::Operands::Constant::solution(
        const TokenValueMap_t& values_in) const
{
    return constants.find(this->get_token())->second;
}



//  __________________________________________________________________________
// |                                                                          |
// | Class: Constant                                                          |
// | Function: solution                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t
Mathematics::Expressions::Operands::Constant::get_variables() const
{
    return {};
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Constant                                                          |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operands::Constant::is_token(
        const Token_t& token_in)
{
    return (constants.find(token_in) != constants.end());
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Constant                                                          |
// | Function: get_precedence                                                 |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenPrecedence_t
Mathematics::Expressions::Operands::Constant::get_precedence(
        Type_t type_in, 
        const Token_t& token_in)
{
    return MAX_PRECEDENCE;
}


