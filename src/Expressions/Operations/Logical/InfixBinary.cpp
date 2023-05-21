// ============================================================================
//! @file InfixBinary.cpp
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
#include <Expressions/Operations/Logical/InfixBinary.h>

const Mathematics::Expressions::Operations::Binary::LogicalBinaryHash_t 
Mathematics::Expressions::Operations::Logical::InfixBinary::operations = 
{
    {L"=",		&InfixBinary::equal},
    {L"!=",		&InfixBinary::not_equal},
    {L">",		&InfixBinary::greater_than},
    {L"<",		&InfixBinary::less_than},
    {L">=",		&InfixBinary::greater_than_or_equal},
    {L"<=",		&InfixBinary::less_than_or_equal},
    {L"->",		&InfixBinary::implies},
    {L"and",	&InfixBinary::and},
    {L"or",		&InfixBinary::or},

#if defined(__UTF16_EXPRESSIONS__) || \
    defined(__WCHAR_EXPRESSIONS__) || \
    defined(__UTF32_EXPRESSIONS__)
    {L"≈",		&InfixBinary::approximation},
    {L"≠",		&InfixBinary::not_equal},
    {L"≥",		&InfixBinary::greater_than_or_equal},
    {L"≤",		&InfixBinary::less_than_or_equal},
    {L"⋀",		&InfixBinary:: and},
    {L"⋁",		&InfixBinary:: or},
#endif
};


const Mathematics::Expressions::PrecedenceHash_t
Mathematics::Expressions::Operations::Logical::InfixBinary::precedences =
{
};


//  __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Logical::InfixBinary::InfixBinary(
        const Token_t& token_in, 
        Expression* left_in, 
        Expression* right_in, 
        const TokenPair_t& parentheses_in,
        const TokenPair_t& argument_parentheses_in) :
    Binary(token_in, left_in, right_in, parentheses_in, 
            argument_parentheses_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Logical::InfixBinary::InfixBinary(
        const InfixBinary& rhs) :
    Binary(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Logical::InfixBinary::InfixBinary(
        const InfixBinary& rhs,
        const TokenPair_t& parentheses_in) :
    Binary(rhs, parentheses_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: Move Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Logical::InfixBinary::InfixBinary(
        InfixBinary&& rhs) :
    Binary(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Logical::InfixBinary& 
Mathematics::Expressions::Operations::Logical::InfixBinary::operator=(
        const InfixBinary& rhs)
{
    Binary::operator=(rhs);
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Logical::InfixBinary& 
Mathematics::Expressions::Operations::Logical::InfixBinary::operator=(
        InfixBinary&& rhs)
{
    Binary::operator=(rhs);
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: infix                                                          |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Operations::Logical::InfixBinary::infix() const
{
    TokenList_t output;
    this->add_open_parentheses(output);
    this->add_open_argument_parentheses(output);
    output.splice(output.end(), this->get_left()->infix());
    this->add_close_argument_parentheses(output);
    output.push_back(this->get_token());
    this->add_open_argument_parentheses(output);
    output.splice(output.end(), this->get_right()->infix());
    this->add_close_argument_parentheses(output);
    this->add_close_parentheses(output);
    return output;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: simplify                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operations::Logical::InfixBinary::simplify() const
{
    return new InfixBinary(this->get_token(),
            this->get_left()->simplify(), 
            this->get_right()->simplify());
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: derivative                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Logical::InfixBinary::derivative(
        const Token_t& token_in) const
{
    return new InfixBinary(this->get_token(),
            this->get_left()->derivative(token_in),
            this->get_right()->derivative(token_in));
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: integral                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Logical::InfixBinary::integral(
        const Token_t& token_in) const
{
    return new InfixBinary(this->get_token(),
            this->get_left()->integral(token_in),
            this->get_right()->integral(token_in));
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: solution                                                       |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Logical::InfixBinary::solution(
        const TokenValueMap_t& values_in) const
{
    return ((this->operations.find(this->get_token())->second(
            this->get_left()->solution(values_in),
            this->get_right()->solution(values_in))) != FALSE ? TRUE : FALSE);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: copy                                                           |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operations::Logical::InfixBinary::copy(
        const TokenPair_t& parentheses_in) const
{
    return new InfixBinary(*this, parentheses_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Logical::InfixBinary::is_token(
        const Token_t& token_in)
{
    return (operations.find(token_in) != operations.end());
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: get_precedence                                                 |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenPrecedence_t 
Mathematics::Expressions::Operations::Logical::InfixBinary::get_precedence(
        Type_t type_in,
        const Token_t& token_in)
{
    return MIN_PRECEDENCE;
}


// __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Logical::InfixBinary::approximation(
        const Real& x,
        const Real& y)
{
    return ((x + x * 0.05 >= y) && (x - x * 0.05 <= y));
}


// __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Logical::InfixBinary::equal(
        const Real& x, 
        const Real& y)
{
    return (x == y);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Logical::InfixBinary::not_equal(
        const Real& x, 
        const Real& y)
{
    return (x != y);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Logical::InfixBinary::less_than(
        const Real& x,
        const Real& y)
{
    return (x < y);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Logical::InfixBinary::greater_than(
        const Real& x,
        const Real& y)
{
    return (x > y);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Logical::InfixBinary::less_than_or_equal(
        const Real& x,
        const Real& y)
{
    return (x <= y);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Logical::InfixBinary::greater_than_or_equal(
        const Real& x,
        const Real& y)
{
    return (x >= y);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Logical::InfixBinary::implies(
        const Real& x,
        const Real& y)
{
    return (x == y);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: and                                                            |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Logical::InfixBinary::and(
        const Real& x,
        const Real& y)
{
    return (x && y);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: or                                                             |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Logical::InfixBinary::or(
        const Real& x,
        const Real& y)
{
    return (x || y);
}

