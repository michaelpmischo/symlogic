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
#include <Expressions/Operations/Logical/PrefixUnary.h>


const Mathematics::Expressions::Operations::Unary::LogicalUnaryHash_t
Mathematics::Expressions::Operations::Logical::PrefixUnary::operations =
{
    {"\xA9",		&PrefixUnary::NOT},
    {"\xAA",		&PrefixUnary::NOT},
};


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Logical::PrefixUnary::PrefixUnary(
        const Token_t& token_in, 
        Expression* left_in, 
        const TokenPair_t& parentheses_in,
        const TokenPair_t& argument_parentheses_in) :
    Unary(token_in, left_in, parentheses_in, argument_parentheses_in)
{
    if (this->get_type() != Type_t::LOGICAL_PREFIX_UNARY)
    {
        std::stringstream stream;
        stream << this->get_token() << " is not an Prefix Unary!" << std::endl;
        throw(stream.str());
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Logical::PrefixUnary::PrefixUnary(
        const PrefixUnary& rhs) :
    Unary(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Logical::PrefixUnary::PrefixUnary(
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
Mathematics::Expressions::Operations::Logical::PrefixUnary::PrefixUnary(
        PrefixUnary&& rhs) :
    Unary(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Logical::PrefixUnary& 
Mathematics::Expressions::Operations::Logical::PrefixUnary::operator=(
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
Mathematics::Expressions::Operations::Logical::PrefixUnary& 
Mathematics::Expressions::Operations::Logical::PrefixUnary::operator=(
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
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Operations::Logical::PrefixUnary::infix() const
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
Mathematics::Expressions::Operations::Logical::PrefixUnary::simplify() const
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
Mathematics::Expressions::Operations::Logical::PrefixUnary::derivative(
        const Token_t& token_in) const
{
    // TODO - Handle the PrefixUnary Derivatives
    return this->get_left()->derivative(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: integral                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Logical::PrefixUnary::integral(
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
Mathematics::Expressions::Operations::Logical::PrefixUnary::solution(
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
Mathematics::Expressions::Operations::Logical::PrefixUnary::copy(
        const TokenPair_t& parentheses_in) const
{
    return new PrefixUnary(*this);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Logical::PrefixUnary::is_token(
        const Token_t& token_in)
{
    return (operations.find(token_in) != operations.end());
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixUnary                                                       |
// | Function: get_precedence                                                 |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenPrecedence_t 
Mathematics::Expressions::Operations::Logical::PrefixUnary::get_precedence(
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
bool Mathematics::Expressions::Operations::Logical::PrefixUnary::NOT(
        const Real& x)
{
    return !(x != FALSE);
}
