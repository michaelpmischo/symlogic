// ============================================================================
//! @file Variable.cpp
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
#include <Expressions/Operands/Variable.h>
#include <Expressions/Operands/Constant.h>
#include <Expressions/Operands/Number.h>
#include <cmath>


#include <Expressions/Operations/Arithmatic/InfixBinary.h>
#include <Expressions/Operations/Calculus/PostfixDerivative.h>


//  __________________________________________________________________________
// |                                                                          |
// | Class: Variable                                                          |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Variable::Variable(
        const Token_t& token_in,
        const TokenPair_t& parentheses_in) :
	Operand(token_in, parentheses_in)
{
    if (this->get_type() != Type_t::VARIABLE)
    {
        std::stringstream stream;
        stream << this->get_token() << " is not an Variable!" << std::endl;
        throw(stream.str());
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Variable                                                          |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Variable::Variable(const Variable& rhs) :
    Operand(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Variable                                                          |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Variable::Variable(const Variable& rhs, 
        const TokenPair_t& parentheses_in) :
    Operand(rhs, parentheses_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Variable                                                          |
// | Function: Move Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Variable::Variable(Variable&& rhs) :
    Operand(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Variable                                                          |
// | Function: Assignment Operator                                            |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Variable& 
Mathematics::Expressions::Operands::Variable::operator=(const Variable& rhs)
{
    Operand::operator=(rhs);
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Variable                                                          |
// | Function: Move Operator                                                  |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Variable&
Mathematics::Expressions::Operands::Variable::operator=(Variable&& rhs)
{
    Operand::operator=(rhs);
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Variable                                                          |
// | Function: contains_variable                                              |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operands::Variable::contains_variable() const
{
    return true;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Variable                                                          |
// | Function: copy                                                           |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operands::Variable::copy(
        const TokenPair_t& parentheses_in) const
{
    return new Variable(*this, parentheses_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Variable                                                          |
// | Function: derivative                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operands::Variable::derivative(
        const Token_t& token_in) const
{
    if (this->contains(token_in))
    {
        return new Number(1);
    }
    else
    {
        return new Operations::Arithmatic::InfixBinary("*",
            new Operations::Calculus::PostfixDerivative("'",
                new Variable(token_in),
                this->copy()),
            this->copy());
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Variable                                                          |
// | Function: integral                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operands::Variable::integral(
        const Token_t& token_in) const
{
    if (this->contains(token_in))
    {
        return new Operations::Arithmatic::InfixBinary("/", 
            new Operations::Arithmatic::InfixBinary("^", 
                this->copy(),
                new Number(2),
                { "(",")" }),
            new Number(2));
    }
    else
    {
        return this->copy();
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Variable                                                          |
// | Function: solution                                                       |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Operands::Variable::solution(
        const TokenValueMap_t& values_in) const
{
    if (values_in.find(this->get_token()) != values_in.end())
    {
        return values_in.find(this->get_token())->second;
    }
    else
    {
        return NAN;
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Variable                                                          |
// | Function: solution                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Operands::Variable::get_variables() const
{
    return {this->get_token()};
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Variable                                                          |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operands::Variable::is_token(
        const Token_t& token_in)
{
	if (token_in.empty())
	{
		return false;
	}

    return (!Constant::is_token(token_in) && !Number::is_token(token_in) && 
        token_in.find_first_not_of(
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789._"
        ) == Token_t::npos);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Variable                                                          |
// | Function: get_precedence                                                 |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenPrecedence_t
Mathematics::Expressions::Operands::Variable::get_precedence(
        Type_t type_in, 
        const Token_t& token_in)
{
    return MAX_PRECEDENCE;
}

