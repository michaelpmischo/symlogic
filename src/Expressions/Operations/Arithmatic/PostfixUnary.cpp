// ============================================================================
//! @file PostfixUnary.cpp
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
#include <Expressions/Operations/Arithmatic/PostfixUnary.h>
#include <cmath>

const Mathematics::Expressions::Operations::Unary::ArithmaticUnaryHash_t
Mathematics::Expressions::Operations::Arithmatic::PostfixUnary::operations = 
{
    {"!", &PostfixUnary::fact},
};


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixUnary                                                      |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Arithmatic::PostfixUnary::PostfixUnary(
        const Token_t& token_in, 
        Expression* left_in, 
        const TokenPair_t& parentheses_in,
        const TokenPair_t& argument_parentheses_in) :
    Unary(token_in, left_in, parentheses_in, argument_parentheses_in)
{
    if (this->get_type() != Type_t::ARITHMATIC_POSTFIX_UNARY)
    {
        std::stringstream stream;
        stream << this->get_token() << " is not an PrefixUnary!" << std::endl;
        throw(stream.str());
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixUnary                                                      |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Arithmatic::PostfixUnary::PostfixUnary(
        const PostfixUnary& rhs) :
    Unary(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixUnary                                                      |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Arithmatic::PostfixUnary::PostfixUnary(
        const PostfixUnary& rhs,
        const TokenPair_t& parentheses_in) :
    Unary(rhs, parentheses_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixUnary                                                      |
// | Function: Move Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Arithmatic::PostfixUnary::PostfixUnary(
        PostfixUnary&& rhs) :
    Unary(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixUnary                                                      |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Arithmatic::PostfixUnary& 
Mathematics::Expressions::Operations::Arithmatic::PostfixUnary::operator=(
        const PostfixUnary& rhs)
{
    Unary::operator=(rhs);
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixUnary                                                      |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Arithmatic::PostfixUnary& 
Mathematics::Expressions::Operations::Arithmatic::PostfixUnary::operator=(
        PostfixUnary&& rhs)
{
    Unary::operator=(rhs);
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixUnary                                                      |
// | Function: expression                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Operations::Arithmatic::PostfixUnary::infix() const
{
    TokenList_t output;
    this->add_open_parentheses(output);
    this->add_open_argument_parentheses(output);
    output.splice(output.end(), this->get_left()->infix());
    this->add_close_argument_parentheses(output);
    output.push_back(this->get_token());
    this->add_close_parentheses(output);
    return output;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixUnary                                                      |
// | Function: simplify                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operations::Arithmatic::PostfixUnary::simplify() const
{
    // TODO - Handle the PistfixUnary simplification
    return this->get_left()->simplify();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixUnary                                                      |
// | Function: derivative                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operations::Arithmatic::PostfixUnary::derivative(
        const Token_t& token_in) const
{
    // TODO - Handle the PistfixUnary derivatives
    return this->get_left()->derivative(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixUnary                                                      |
// | Function: integral                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operations::Arithmatic::PostfixUnary::integral(
        const Token_t& token_in) const
{
    // TODO - Handle the PistfixUnary integrals
    return this->get_left()->integral(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixUnary                                                      |
// | Function: solution                                                       |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PostfixUnary::solution(
        const TokenValueMap_t& values_in) const
{
    return this->operations.find(this->get_token())->second(
            this->get_left()->solution(values_in));
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixUnary                                                      |
// | Function: copy                                                           |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operations::Arithmatic::PostfixUnary::copy(
        const TokenPair_t& parentheses_in) const
{
    return new PostfixUnary(*this, parentheses_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixUnary                                                      |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Arithmatic::PostfixUnary::is_token(
        const Token_t& token_in)
{
    return (operations.find(token_in) != operations.end());
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixUnary                                                      |
// | Function: get_precedence                                                 |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenPrecedence_t
Mathematics::Expressions::Operations::Arithmatic::PostfixUnary::get_precedence(
        Type_t type_in,
        const Token_t& token_in)
{
    return MAX_PRECEDENCE;
}


// __________________________________________________________________________
// |                                                                          |
// | Class: N/A                                                               |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
// Some Numerical Operation Definitions
inline uint64_t fact(uint64_t x)
{
    return ((x > 1U) ? x * fact(x - 1U) : 1U);
}


// __________________________________________________________________________
// |                                                                          |
// | Class: PostfixUnary                                                      |
// | Function: fact                                                           |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operations::Arithmatic::PostfixUnary::fact(
        const Real& x)
{
    return ::fact(std::abs(x));
}



