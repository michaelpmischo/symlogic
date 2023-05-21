// ============================================================================
//! @file Operation.cpp
//! @author Michael P. MIscho
//! @date May 11, 2023
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
#include <Expressions/Operations/Operation.h>

#include <Expressions/Operations/Unary.h>
#include <Expressions/Operations/Binary.h>
#include <Expressions/Operations/Ternary.h>
#include <Expressions/Operations/Functional.h>

//  __________________________________________________________________________
// |                                                                          |
// | Class: Operation                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Operation::Operation(
        const Token_t& token_in,
        const TokenPair_t& parentheses_in,
        const TokenPair_t& argument_parentheses_in) :
    Expression(token_in, parentheses_in),
    argumant_parentheses(argument_parentheses_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operation                                                         |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Operation::Operation(
        const Operation& rhs) :
    Expression(rhs),
    argumant_parentheses(rhs.argumant_parentheses)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operation                                                         |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Operation::Operation(
        const Operation& rhs, 
        const TokenPair_t& parentheses_in) :
    Expression(rhs.get_token(), parentheses_in),
    argumant_parentheses(rhs.argumant_parentheses)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operation                                                         |
// | Function: Move Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Operation::Operation(Operation&& rhs) :
    Expression(rhs),
    argumant_parentheses(rhs.argumant_parentheses)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operation                                                         |
// | Function: Assignment Operator                                            |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Operation& 
Mathematics::Expressions::Operations::Operation::operator=(
        const Operation& rhs)
{
    Expression::operator=(rhs);
    this->argumant_parentheses = rhs.argumant_parentheses;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operation                                                         |
// | Function: Move Operator                                                  |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Operation& 
Mathematics::Expressions::Operations::Operation::operator=(Operation&& rhs)
{
    Expression::operator=(rhs);
    this->argumant_parentheses = rhs.argumant_parentheses;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operation                                                         |
// | Function: is_operator                                                    |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Operation::is_operator() const
{
    return true;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operation                                                         |
// | Function: in_operand                                                     |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Operation::is_operand() const
{
    return false;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operation                                                         |
// | Function: is_separator                                                   |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Operation::is_separator() const
{
    return false;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operation                                                         |
// | Function: is_bracket                                                     |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Operation::is_bracket() const
{
    return false;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operation                                                         |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Operation::is_token(
        const Token_t& token_in)
{
    return Unary::is_token(token_in) || Binary::is_token(token_in) ||
            Ternary::is_token(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operation                                                         |
// | Function: get_precedence                                                 |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenPrecedence_t
Mathematics::Expressions::Operations::Operation::get_precedence(
        Type_t type_in, 
        const Token_t& token_in)
{
    switch (type_in)
    {
        case Type_t::ARITHMATIC_PREFIX_UNARY:
        case Type_t::ARITHMATIC_POSTFIX_UNARY:
            return Unary::get_precedence(type_in, token_in);

        case Type_t::ARITHMATIC_PREFIX_BINARY:
        case Type_t::ARITHMATIC_INFIX_BINARY:
        case Type_t::ARITHMATIC_POSTFIX_BINARY:
        case Type_t::LOGICAL_INFIX_BINARY:
            return Binary::get_precedence(type_in, token_in);

        case Type_t::ARITHMATIC_PREFIX_TERNARY:
        case Type_t::ARITHMATIC_PREINFIX_TERNARY:
        case Type_t::ARITHMATIC_POSTINFIX_TERNARY:
        case Type_t::ARITHMATIC_POSTFIX_TERNARY:
            return Ternary::get_precedence(type_in, token_in);

        case Type_t::ARITHMATIC_PREFIX_SEQUENCE:
            return MIN_PRECEDENCE;

        case Type_t::CALCULUS_LIMIT:
        case Type_t::CALCULUS_PREFIX_DERIVATIVE:
        case Type_t::CALCULUS_POSTFIX_DERIVATIVE:
        case Type_t::CALCULUS_IMPLICIT_DERIVATIVE:
        case Type_t::CALCULUS_DEFINITE_INTEGRAL:
        case Type_t::CALCULUS_INDEFINITE_INTEGRAL:
            return Functional::get_precedence(type_in, token_in);

        default:
            return MIN_PRECEDENCE;
    }
}

