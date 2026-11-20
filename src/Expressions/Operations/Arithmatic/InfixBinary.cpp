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
#include <Expressions/Operations/Arithmatic/InfixBinary.h>
#include <cmath>

// For the Derivatives and Integrals
#include <Expressions/Operations/Calculus/Derivative.h>

const Mathematics::Expressions::Operations::Binary::ArithmaticBinaryHash_t
Mathematics::Expressions::Operations::Arithmatic::InfixBinary::operations =
{
    {"^",		&InfixBinary::pow},
    {"*",		&InfixBinary::mul},
    {"/",		&InfixBinary::div},
    {"\xF6",	&InfixBinary::div},
    {"+",		&InfixBinary::add},
    {"-",		&InfixBinary::sub},
};


const Mathematics::Expressions::PrecedenceHash_t
Mathematics::Expressions::Operations::Arithmatic::InfixBinary::precedences =
{
    {"^",		5U},
    {"*",		3U},
    {"/",		3U},
    {"\xF6",    3U},
    {"+",		1U},
    {"-",		1U},
};


//  __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Arithmatic::InfixBinary::InfixBinary(
        const Token_t& token_in,
        Expression* left_in,
        Expression* right_in,
        const TokenPair_t& parentheses_in,
        const TokenPair_t& argument_parentheses_in) :
    Binary(token_in, left_in, right_in, parentheses_in, 
            argument_parentheses_in)
{
    if (this->get_type() != Type_t::ARITHMATIC_INFIX_BINARY)
    {
        std::stringstream stream;
        stream << this->get_token() << " is not an InfixBinary!" << std::endl;
        throw(stream.str());
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Arithmatic::InfixBinary::InfixBinary(
        const InfixBinary& rhs) :
    Binary(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Arithmatic::InfixBinary::InfixBinary(
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
Mathematics::Expressions::Operations::Arithmatic::InfixBinary::InfixBinary(
        InfixBinary&& rhs) :
    Binary(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Arithmatic::InfixBinary&
Mathematics::Expressions::Operations::Arithmatic::InfixBinary::operator=(
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
Mathematics::Expressions::Operations::Arithmatic::InfixBinary&
Mathematics::Expressions::Operations::Arithmatic::InfixBinary::operator=(
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
Mathematics::Expressions::Operations::Arithmatic::InfixBinary::infix() const
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
Mathematics::Expressions::Operations::Arithmatic::InfixBinary::simplify() const
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
Mathematics::Expressions::Operations::Arithmatic::InfixBinary::derivative(
    const Token_t& token_in) const
{
    // TODO - Handle the PrefixUnary Derivatives
    if (Calculus::Derivative::is_common(this->get_token()))
    {
        return Calculus::Derivative::get_common(token_in, this);
    }
    else
    {
        return this->get_left()->derivative(token_in);
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: integral                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operations::Arithmatic::InfixBinary::integral(
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
Mathematics::Expressions::Operations::Arithmatic::InfixBinary::solution(
    const TokenValueMap_t& values_in) const
{
    return this->operations.find(this->get_token())->second(
        this->get_left()->solution(values_in),
        this->get_right()->solution(values_in));
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: copy                                                           |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Arithmatic::InfixBinary::copy(
    const TokenPair_t& parentheses_in) const
{
    return new InfixBinary(*this, parentheses_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Arithmatic::InfixBinary::is_token(
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
Mathematics::Expressions::Operations::Arithmatic::InfixBinary::get_precedence(
        Type_t type_in, 
        const Token_t& token_in)
{
    PrecedenceHash_t::const_iterator iter = precedences.find(token_in);
    if (iter != precedences.end())
    {
        return iter->second;
    }
    else
    {
        return MIN_PRECEDENCE;
    }
}


// __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: pow                                                            |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::InfixBinary::pow(
        const Real& x,
        const Real& y)
{
    return std::pow(x, y);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: mul                                                            |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::InfixBinary::mul(
        const Real& x,
        const Real& y)
{
    return (x * y);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: div                                                            |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::InfixBinary::div(
        const Real& x,
        const Real& y)
{
    return (x / y);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: add                                                            |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::InfixBinary::add(
        const Real& x,
        const Real& y)
{
    return (x + y);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: InfixBinary                                                       |
// | Function: sub                                                            |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::InfixBinary::sub(
        const Real& x,
        const Real& y)
{
    return (x - y);
}

