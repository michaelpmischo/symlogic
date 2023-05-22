// ============================================================================
//! @file Unary.cpp
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
#include <Expressions/Operations/Unary.h>
#include <Expressions/Operations/Arithmatic/PostfixUnary.h>
#include <Expressions/Operations/Arithmatic/PrefixUnary.h>
#include <iostream>

//  __________________________________________________________________________
// |                                                                          |
// | Class: Unary                                                             |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Unary::Unary(const Token_t& token_in,
        Expression* left_in,
        const TokenPair_t& parentheses_in,
        const TokenPair_t& argument_parentheses_in) :
    Operation(token_in, parentheses_in, argument_parentheses_in),
    left(left_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Unary                                                             |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Unary::Unary(const Unary& rhs) :
    Operation(rhs),
    left(rhs.left->copy())
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Unary                                                             |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Unary::Unary(const Unary& rhs, 
        const TokenPair_t& parentheses_in) :
    Operation(rhs, parentheses_in),
    left(rhs.left->copy())
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Unary                                                             |
// | Function: Move Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Unary::Unary(Unary&& rhs) :
    Operation(rhs),
    left(rhs.left->copy())
{
    delete rhs.left;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Unary                                                             |
// | Function: Assignment Operator                                            |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Unary& 
Mathematics::Expressions::Operations::Unary::operator=(const Unary& rhs)
{
    Operation::operator=(rhs);
    this->left = rhs.left->copy();
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Unary                                                             |
// | Function: Move Operator                                                  |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Unary& 
Mathematics::Expressions::Operations::Unary::operator=(Unary&& rhs)
{
    Operation::operator=(rhs);
    this->left = rhs.left->copy();
    delete rhs.left;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Unary                                                             |
// | Function: operator==                                                     |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Unary::operator==(
        const Unary& rhs) const
{
    return Expression::operator==(rhs) &&
        *this->get_left() == *rhs.get_left();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Unary                                                             |
// | Function: prefix                                                         |
// |__________________________________________________________________________|
Mathematics::TokenList_t 
Mathematics::Expressions::Operations::Unary::prefix() const
{
    TokenList_t output;
    this->add_open_parentheses(output);
    output.push_back(this->get_token());
    this->add_open_argument_parentheses(output);
    output.splice(output.end(), this->left->prefix());
    this->add_close_argument_parentheses(output);
    this->add_close_parentheses(output);
    return output;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Unary                                                             |
// | Function: postfix                                                        |
// |__________________________________________________________________________|
Mathematics::TokenList_t 
Mathematics::Expressions::Operations::Unary::postfix() const
{
    TokenList_t output;
    this->add_open_parentheses(output);
    this->add_open_argument_parentheses(output);
    output.splice(output.end(), this->left->postfix());
    this->add_close_argument_parentheses(output);
    output.push_back(this->get_token());
    this->add_close_parentheses(output);
    return output;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Unary                                                             |
// | Function: size                                                           |
// |__________________________________________________________________________|
size_t Mathematics::Expressions::Operations::Unary::size() const
{
    return 1U + this->left->size();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Unary                                                             |
// | Function: height                                                         |
// |__________________________________________________________________________|
size_t Mathematics::Expressions::Operations::Unary::height() const
{
    return 1U + this->left->height();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Unary                                                             |
// | Function: contains                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Unary::contains(
        const Token_t& token_in) const
{
    return this->get_left()->contains(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Unary                                                             |
// | Function: contains_variable                                              |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Unary::contains_variable() const
{
    return this->get_left()->contains_variable();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Unary                                                             |
// | Function: get_variables                                                  |
// |__________________________________________________________________________|
Mathematics::TokenList_t  
Mathematics::Expressions::Operations::Unary::get_variables() const
{
    TokenList_t variables;
    variables.splice(variables.end(), this->get_left()->get_variables());
    variables.sort();
    variables.unique();
    return variables;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Unary                                                             |
// | Function: arity                                                          |
// |__________________________________________________________________________|
Mathematics::Natural 
Mathematics::Expressions::Operations::Unary::arity() const
{
    return 1U;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Unary                                                             |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Unary::is_token(
        const Token_t& token_in)
{
    return Arithmatic::PrefixUnary::is_token(token_in) ||
        Arithmatic::PostfixUnary::is_token(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Unary                                                             |
// | Function: get_precedence                                                 |
// |__________________________________________________________________________|
Mathematics::TokenPrecedence_t 
Mathematics::Expressions::Operations::Unary::get_precedence(
        Type_t type_in, 
        const Token_t& token_in)
{
    switch (type_in)
    {
        case Type_t::ARITHMATIC_PREFIX_UNARY:
            return Arithmatic::PrefixUnary::get_precedence(type_in, 
                token_in);
            break;

        case Type_t::ARITHMATIC_POSTFIX_UNARY:
            return Arithmatic::PostfixUnary::get_precedence(type_in, 
                token_in);
            break;

        default:
            return MIN_PRECEDENCE;
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Unary                                                             |
// | Function: Destructor                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Unary::~Unary()
{
    delete this->left;
}

//  __________________________________________________________________________
// |                                                                          |
// | Class: Unary                                                             |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
void Mathematics::Expressions::Operations::Unary::print(
        TokenStream_t& stream, 
        const Token_t& prefix_in,
        bool is_last) const
{
    stream << prefix_in << (!is_last ? "├──" : "└──") << "(" <<
        this->get_token() << ")" << std::endl;

    std::wstring new_prefix = prefix_in + (!is_last ? "│   " : "    ");

    // Enter the next tree level - left and right branch
    stream << new_prefix << "│   " << std::endl;
    this->left->print(stream, new_prefix, true);
}


