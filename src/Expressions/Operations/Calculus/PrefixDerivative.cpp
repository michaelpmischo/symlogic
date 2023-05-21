// ============================================================================
//! @file PrefixDerivative.cpp
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
#include <Expressions/Operations/Calculus/PrefixDerivative.h>

const Mathematics::Expressions::Operations::Calculus::Derivative::DerivativeHash_t
Mathematics::Expressions::Operations::Calculus::PrefixDerivative::operations = 
{
    {L"derivative",	&PrefixDerivative::differentiate},
};

//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixDerivative                                                  |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Calculus::PrefixDerivative::PrefixDerivative(
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
// | Class: PrefixDerivative                                                  |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Calculus::PrefixDerivative::PrefixDerivative(
        const PrefixDerivative& rhs) :
    Derivative(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixDerivative                                                  |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Calculus::PrefixDerivative::PrefixDerivative(
    const PrefixDerivative& rhs,
    const TokenPair_t& parentheses_in) :
    Derivative(rhs, parentheses_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixDerivative                                                  |
// | Function: Move Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Calculus::PrefixDerivative::PrefixDerivative(
        PrefixDerivative&& rhs) :
    Derivative(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixDerivative                                                  |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Calculus::PrefixDerivative&
Mathematics::Expressions::Operations::Calculus::PrefixDerivative::operator=(
        const PrefixDerivative& rhs)
{
    Derivative::operator=(rhs);
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixDerivative                                                  |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Calculus::PrefixDerivative&
Mathematics::Expressions::Operations::Calculus::PrefixDerivative::operator=(
        PrefixDerivative&& rhs)
{
    Derivative::operator=(rhs);
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixDerivative                                                  |
// | Function: expression                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t
Mathematics::Expressions::Operations::Calculus::PrefixDerivative::infix() const
{
    TokenList_t output;
    this->add_open_parentheses(output);
    output.push_back(this->get_token());
    this->add_open_argument_parentheses(output);
    output.splice(output.end(), this->get_function()->infix());
    this->add_close_argument_parentheses(output);
    this->add_close_parentheses(output);
    return output;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixDerivative                                                  |
// | Function: simplify                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Calculus::PrefixDerivative::simplify() const
{
    // TODO - Handle the PrefixDerivative simplification
    return this->get_function()->simplify();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixDerivative                                                  |
// | Function: derivative                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Calculus::PrefixDerivative::derivative(
        const Token_t& token_in) const
{
    // TODO - Handle the PrefixDerivative PrefixDerivatives
    return this->get_function()->derivative(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixDerivative                                                  |
// | Function: integral                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Calculus::PrefixDerivative::integral(
        const Token_t& token_in) const
{
    // TODO - Handle the PrefixDerivative Integrals
    return this->get_function()->copy();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixDerivative                                                  |
// | Function: solution                                                       |
// |__________________________________________________________________________|
Mathematics::Real
Mathematics::Expressions::Operations::Calculus::PrefixDerivative::solution(
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
// | Class: PrefixDerivative                                                  |
// | Function: copy                                                           |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Calculus::PrefixDerivative::copy(
        const TokenPair_t& parentheses_in) const
{
    return new PrefixDerivative(*this, parentheses_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixDerivative                                                  |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Calculus::PrefixDerivative::is_token(
        const Token_t& token_in)
{
    return (operations.find(token_in) != operations.end());
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixDerivative                                                  |
// | Function: get_precedence                                                 |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenPrecedence_t 
Mathematics::Expressions::Operations::Calculus::PrefixDerivative::get_precedence(
        Type_t type_in,
        const Token_t& token_in)
{
    return MAX_PRECEDENCE;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: PrefixDerivative                                                  |
// | Function: differentiate                                                  |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Calculus::PrefixDerivative::differentiate(
        const Token_t& token_in,
        const Expression* expression_in)
{
    return expression_in->derivative(token_in);
}