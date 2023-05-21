// ============================================================================
//! @file PostfixDerivative.cpp
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
#include <Expressions/Operations/Calculus/PostfixDerivative.h>

const Mathematics::Expressions::Operations::Calculus::Derivative::DerivativeHash_t
Mathematics::Expressions::Operations::Calculus::PostfixDerivative::operations =
{
	{L"'",		&PostfixDerivative::prime},
};


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixDerivative                                                 |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Calculus::PostfixDerivative::PostfixDerivative(
        const Token_t& token_in,
        Expression* variable_in,
        Expression* function_in, 
        const TokenPair_t& parentheses_in,
        const TokenPair_t& argument_parentheses_in) :
    Derivative(token_in, variable_in, function_in, parentheses_in, 
            argument_parentheses_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixDerivative                                                 |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Calculus::PostfixDerivative::PostfixDerivative(
        const PostfixDerivative& rhs) :
    Derivative(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixDerivative                                                 |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Calculus::PostfixDerivative::PostfixDerivative(
    const PostfixDerivative& rhs,
    const TokenPair_t& parentheses_in) :
    Derivative(rhs, parentheses_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixDerivative                                                 |
// | Function: Move Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Calculus::PostfixDerivative::PostfixDerivative(
        PostfixDerivative&& rhs) :
    Derivative(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixDerivative                                                 |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Calculus::PostfixDerivative&
Mathematics::Expressions::Operations::Calculus::PostfixDerivative::operator=(
        const PostfixDerivative& rhs)
{
    Derivative::operator=(rhs);
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixDerivative                                                 |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Calculus::PostfixDerivative&
Mathematics::Expressions::Operations::Calculus::PostfixDerivative::operator=(
        PostfixDerivative&& rhs)
{
    Derivative::operator=(rhs);
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixDerivative                                                 |
// | Function: expression                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Operations::Calculus::PostfixDerivative::infix() const
{
    TokenList_t output;
    this->add_open_parentheses(output);
    this->add_open_argument_parentheses(output);
    output.splice(output.end(), this->get_function()->infix());
    this->add_close_argument_parentheses(output);
    output.push_back(this->get_token());
    this->add_close_parentheses(output);
    return output;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixDerivative                                                 |
// | Function: simplify                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Calculus::PostfixDerivative::simplify() const
{
    // TODO - Handle the PostfixDerivative simplification
    return this->get_function()->simplify();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixDerivative                                                 |
// | Function: derivative                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Calculus::PostfixDerivative::derivative(
    const Token_t& token_in) const
{
    // TODO - Handle the PostfixDerivative PostfixDerivatives
    return this->get_function()->copy();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixDerivative                                                 |
// | Function: integral                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Calculus::PostfixDerivative::integral(
        const Token_t& token_in) const
{
    // TODO - Handle the PostfixDerivative Integrals
    return this->get_function()->integral(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixDerivative                                                 |
// | Function: solution                                                       |
// |__________________________________________________________________________|
Mathematics::Real
Mathematics::Expressions::Operations::Calculus::PostfixDerivative::solution(
	const TokenValueMap_t& values_in) const
{
	const DerivativeHash_t::const_iterator iter =
		    this->operations.find(this->get_token());
	if (iter != this->operations.end())
	{
		return iter->second(
			    this->get_variable()->get_token(),
			    this->get_function())->solution(values_in);
	}
	else
	{
		return this->get_function()->solution(values_in);
	}
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixDerivative                                                 |
// | Function: copy                                                           |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Calculus::PostfixDerivative::copy(
        const TokenPair_t& parentheses_in) const
{
    return new PostfixDerivative(*this, parentheses_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixDerivative                                                 |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Calculus::PostfixDerivative::is_token(
        const Token_t& token_in)
{
	return (operations.find(token_in) != operations.end());
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixDerivative                                                 |
// | Function: get_precedence                                                 |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenPrecedence_t 
Mathematics::Expressions::Operations::Calculus::PostfixDerivative::get_precedence(
        Type_t type_in,
        const Token_t& token_in)
{
    return MAX_PRECEDENCE;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PostfixDerivative                                                 |
// | Function: differentiate                                                  |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Calculus::PostfixDerivative::prime(
        const Token_t& token_in,
        const Expression* expression_in)
{
    return expression_in->derivative(token_in);
}