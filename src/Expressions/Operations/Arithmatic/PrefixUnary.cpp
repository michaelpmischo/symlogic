// ============================================================================
//! @file PrefixUnary.cpp
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
#include <Expressions/Operations/Arithmatic/PrefixUnary.h>

// Common derivatives...
#include <Expressions/Operations/Calculus/Derivative.h>

const Mathematics::Expressions::Operations::Unary::ArithmaticUnaryHash_t
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::operations =
{
    {"~",		&PrefixUnary::negate},
    {"ln",		&PrefixUnary::ln},
    {"sqrt",	&PrefixUnary::sqrt},
    {"exp",	&PrefixUnary::exp},
    {"abs",	&PrefixUnary::abs},

    // Trigonometric Operations
    {"sin",	&PrefixUnary::sin},
    {"cos",	&PrefixUnary::cos},
    {"tan",	&PrefixUnary::tan},
    {"csc",	&PrefixUnary::csc},
    {"sec",	&PrefixUnary::sec},
    {"cot",	&PrefixUnary::cot},

    {"asin",	&PrefixUnary::asin},
    {"acos",	&PrefixUnary::acos},
    {"atan",	&PrefixUnary::atan},
    {"acsc",	&PrefixUnary::acsc},
    {"asec",	&PrefixUnary::asec},
    {"acot",	PrefixUnary::acot},

    {"sinh",	&PrefixUnary::sinh},
    {"cosh",	&PrefixUnary::cosh},
    {"tanh",	&PrefixUnary::tanh},
    {"csch",	&PrefixUnary::csch},
    {"sech",	&PrefixUnary::sech},
    {"coth",	&PrefixUnary::coth},
    {"asinh",	&PrefixUnary::asinh},
    {"acosh",	&PrefixUnary::acosh},
    {"atanh",	&PrefixUnary::atanh},
    {"acsch",	&PrefixUnary::acsch},
    {"asech",	&PrefixUnary::asech},
    {"acoth",	&PrefixUnary::acoth},

#if defined(__UTF16_EXPRESSIONS__) || \
    defined(__WCHAR_EXPRESSIONS__) || \
    defined(__UTF32_EXPRESSIONS__)
    {"√",		&PrefixUnary::sqrt},
    {"ℯ^",		&PrefixUnary::exp},
#endif
};


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::PrefixUnary(
        const Token_t& token_in, 
        Expression* left_in, 
        const TokenPair_t& parentheses_in,
        const TokenPair_t& argument_parentheses_in) :
    Unary(token_in, left_in, parentheses_in, argument_parentheses_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::PrefixUnary(
        const PrefixUnary& rhs) :
    Unary(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::PrefixUnary(
        const PrefixUnary& rhs,
        const TokenPair_t& parentheses_in) :
    Unary(rhs, parentheses_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: Move Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::PrefixUnary(
        PrefixUnary&& rhs) :
    Unary(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary& 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::operator=(
        const PrefixUnary& rhs)
{
    Unary::operator=(rhs);
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary& 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::operator=(
        PrefixUnary&& rhs)
{
    Unary::operator=(rhs);
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: expression                                                     |
// |__________________________________________________________________________|
Mathematics::TokenList_t 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::infix() const
{
    TokenList_t output;
    this->add_open_parentheses(output);
    output.push_back(this->get_token());
    this->add_open_argument_parentheses(output);
    output.splice(output.end(), this->get_left()->infix());
    this->add_close_argument_parentheses(output);
    this->add_close_parentheses(output);
    return output;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: simplify                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::simplify() const
{
    // TODO - Handle the PrefixUnary simplification
    return this->get_left()->simplify();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: derivative                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::derivative(
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
// | Class: PrefixUnary                                                       |
// | Function: integral                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::integral(
        const Token_t& token_in) const
{
    // TODO - Handle the PrefixUnary Integrals
    return this->get_left()->integral(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: solution                                                       |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::solution(
        const TokenValueMap_t& values_in) const
{
    return this->operations.find(this->get_token())->second(
            this->get_left()->solution(values_in));
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: copy                                                           |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::copy(
        const TokenPair_t& parentheses_in) const
{
    return new PrefixUnary(*this);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::is_token(
        const Token_t& token_in)
{
    return (operations.find(token_in) != operations.end());
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: get_precedence                                                 |
// |__________________________________________________________________________|
Mathematics::TokenPrecedence_t 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::get_precedence(
        Type_t type_in, 
        const Token_t& token_in)
{
    return MAX_PRECEDENCE;
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: negate                                                         |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::negate(
        const Real& x)
{
    return -x;
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::ln(
        const Real& x)
{
    return std::log(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::sqrt(
        const Real& x)
{
    return std::sqrt(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::exp(
        const Real& x)
{
    return std::exp(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::abs(
        const Real& x)
{
    return std::fabs(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: sin                                                            |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::sin(
        const Real& x)
{
    return std::sin(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: cos                                                            |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::cos(
        const Real& x)
{
    return std::cos(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: tan                                                            |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::tan(
        const Real& x)
{
    return std::tan(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: csc                                                            |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::csc(
        const Real& x)
{
    return 1.0 / std::sin(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: sec                                                            |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::sec(
        const Real& x)
{
    return 1.0 / std::cos(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: cot                                                            |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::cot(
        const Real& x)
{
    return 1.0 / std::tan(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: asin                                                           |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::asin(
        const Real& x)
{
    return std::asin(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: acos                                                           |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::acos(
        const Real& x)
{
    return std::acos(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: atan                                                           |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::atan(
        const Real& x)
{
    return std::atan(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: acsc                                                           |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::acsc(
        const Real& x)
{
    return 1.0 / std::asin(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: asec                                                           |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::asec(
        const Real& x)
{
    return 1.0 / std::acos(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: acot                                                           |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::acot(
        const Real& x)
{
    return 1.0 / std::atan(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: sinh                                                           |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::sinh(
        const Real& x)
{
    return std::sinh(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: cosh                                                           |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::cosh(
        const Real& x)
{
    return std::cosh(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: tanh                                                           |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::tanh(
        const Real& x)
{
    return std::tanh(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: csch                                                           |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::csch(
        const Real& x)
{
    return 1.0 / std::sinh(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: sech                                                           |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::sech(
        const Real& x)
{
    return 1.0 / std::cosh(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: coth                                                           |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::coth(
        const Real& x)
{
    return 1.0 / std::tanh(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: asinh                                                          |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::asinh(
        const Real& x)
{
    return std::asinh(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: acosh                                                          |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::acosh(
        const Real& x)
{
    return std::acosh(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: atanh                                                          |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::atanh(
        const Real& x)
{
    return std::atanh(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: acsch                                                          |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::acsch(
        const Real& x)
{
    return 1.0 / std::asinh(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: asech                                                          |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::asech(
        const Real& x)
{
    return 1.0 / std::acosh(x);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: acoth                                                          |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PrefixUnary::acoth(
        const Real& x)
{
    return 1.0 / std::atanh(x);
}

