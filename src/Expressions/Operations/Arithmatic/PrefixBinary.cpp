// ============================================================================
//! @file PrefixBinary.cpp
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
#include <Expressions/Operations/Arithmatic/PrefixBinary.h>
#include <cmath>

const Mathematics::Expressions::Operations::Binary::ArithmaticBinaryHash_t
Mathematics::Expressions::Operations::Arithmatic::PrefixBinary::operations = 
{
    {"log",	&PrefixBinary::log},
    {"nrt",	&PrefixBinary::nrt},

#if defined(__UTF16_EXPRESSIONS__) || \
    defined(__WCHAR_EXPRESSIONS__) || \
    defined(__UTF32_EXPRESSIONS__)
    {"n√",		&PrefixBinary::nrt},
#endif
};


const Mathematics::Expressions::PrecedenceHash_t
Mathematics::Expressions::Operations::Arithmatic::PrefixBinary::precedences =
{
    {"log", 50U},
    {"nrt", 50U},

#if defined(__UTF16_EXPRESSIONS__) || \
    defined(__WCHAR_EXPRESSIONS__) || \
    defined(__UTF32_EXPRESSIONS__)
    {"n√",	50U},
#endif
};

//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixBinary                                                      |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Arithmatic::PrefixBinary::PrefixBinary(
        const Token_t& token_in, 
        Expression* left_in, 
        Expression* right_in, 
        const TokenPair_t& parentheses_in,
        const TokenPair_t& argument_parentheses_in) :
    Binary(token_in, left_in, right_in, parentheses_in, 
            argument_parentheses_in)
{
    if (this->get_type() != Type_t::ARITHMATIC_PREFIX_BINARY)
    {
        std::stringstream stream;
        stream << this->get_token() << " is not an PrefixBinary!" << std::endl;
        throw(stream.str());
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixBinary                                                      |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Arithmatic::PrefixBinary::PrefixBinary(
        const PrefixBinary& rhs) :
    Binary(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixBinary                                                      |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Arithmatic::PrefixBinary::PrefixBinary(
        const PrefixBinary& rhs,
        const TokenPair_t& parentheses_in) :
    Binary(rhs, parentheses_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixBinary                                                      |
// | Function: Move Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Arithmatic::PrefixBinary::PrefixBinary(
        PrefixBinary&& rhs) :
    Binary(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixBinary                                                      |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Arithmatic::PrefixBinary& 
Mathematics::Expressions::Operations::Arithmatic::PrefixBinary::operator=(
        const PrefixBinary& rhs)
{
    Binary::operator=(rhs);
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixBinary                                                      |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Arithmatic::PrefixBinary& 
Mathematics::Expressions::Operations::Arithmatic::PrefixBinary::operator=(
        PrefixBinary&& rhs)
{
    Binary::operator=(rhs);
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixBinary                                                      |
// | Function: infix                                                          |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Operations::Arithmatic::PrefixBinary::infix() const
{
    TokenList_t output;
    this->add_open_parentheses(output);
    this->add_open_argument_parentheses(output);
    output.splice(output.end(), this->get_left()->infix());
    output.splice(output.end(), this->get_right()->infix());
    this->add_close_argument_parentheses(output);
    output.push_back(this->get_token());
    this->add_close_parentheses(output);
    return output;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixBinary                                                      |
// | Function: simplify                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operations::Arithmatic::PrefixBinary::simplify() const
{
    // TODO - Handle the PrefixBinary simplification
    return new PrefixBinary(this->get_token(),
        this->get_left()->simplify(),
        this->get_right()->simplify());
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixBinary                                                      |
// | Function: derivative                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operations::Arithmatic::PrefixBinary::derivative(
        const Token_t& token_in) const
{
    // TODO - Handle the PrefixBinary derivatives
    return new PrefixBinary(this->get_token(),
        this->get_left()->derivative(token_in),
        this->get_right()->derivative(token_in));
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixBinary                                                      |
// | Function: integral                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operations::Arithmatic::PrefixBinary::integral(
        const Token_t& token_in) const
{
    // TODO - Handle the PrefixBinary integrals
    return new PrefixBinary(this->get_token(),
        this->get_left()->integral(token_in),
        this->get_right()->integral(token_in));
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixBinary                                                      |
// | Function: solution                                                       |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixBinary::solution(
        const TokenValueMap_t& values_in) const
{
    return this->operations.find(this->get_token())->second(
        this->get_left()->solution(values_in),
        this->get_right()->solution(values_in));
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixBinary                                                      |
// | Function: copy                                                           |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operations::Arithmatic::PrefixBinary::copy(
        const TokenPair_t& parentheses_in) const
{
    return new PrefixBinary(*this, parentheses_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixBinary                                                      |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Arithmatic::PrefixBinary::is_token(
        const Token_t& token_in)
{
    return (operations.find(token_in) != operations.end());
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixBinary                                                      |
// | Function: get_precedence                                                 |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenPrecedence_t 
Mathematics::Expressions::Operations::Arithmatic::PrefixBinary::get_precedence(
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
// | Class: PrefixBinary                                                      |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixBinary::log(
        const Real& b, 
        const Real& x)
{
    return (std::log(x) / std::log(b));
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixBinary                                                      |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
Mathematics::Real
Mathematics::Expressions::Operations::Arithmatic::PrefixBinary::nrt(
        const Real& n, 
        const Real& x)
{
    return std::pow(x, (1.0 / n));
}

