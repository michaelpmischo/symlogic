// ============================================================================
//! @file Ternary.cpp
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
#include <Expressions/Operations/Ternary.h>
#include <iostream>


//  __________________________________________________________________________
// |                                                                          |
// | Class: Ternary                                                           |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Ternary::Ternary(
        const Token_t& token_in,
        Expression* left_in,
        Expression* middle_in,
        Expression* right_in,
        const TokenPair_t& parentheses_in,
        const TokenPair_t& argumant_parentheses_in) :
    Operation(token_in, parentheses_in, argumant_parentheses_in),
    left(left_in),
    middle(middle_in),
    right(right_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Ternary                                                           |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Ternary::Ternary(const Ternary& rhs) :
    Operation(rhs),
    left(rhs.left->copy()),
    middle(rhs.middle->copy()),
    right(rhs.right->copy())
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Ternary                                                           |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Ternary::Ternary(const Ternary& rhs, 
        const TokenPair_t& parentheses_in) :
    Operation(rhs, parentheses_in),
    left(rhs.left->copy()),
    middle(rhs.middle->copy()),
    right(rhs.right->copy())
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Ternary                                                           |
// | Function: Move Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Ternary::Ternary(Ternary&& rhs) :
    Operation(rhs),
    left(rhs.left->copy()),
    middle(rhs.middle->copy()),
    right(rhs.right->copy())
{
    delete rhs.left;
    delete rhs.middle;
    delete rhs.right;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Ternary                                                           |
// | Function: Assignment Operator                                            |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Ternary& 
Mathematics::Expressions::Operations::Ternary::operator=(const Ternary& rhs)
{
    Operation::operator=(rhs);
    this->left = rhs.left->copy();
    this->middle = rhs.middle->copy();
    this->right = rhs.right->copy();
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Ternary                                                           |
// | Function: Move Operator                                                  |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Ternary& 
Mathematics::Expressions::Operations::Ternary::operator=(Ternary&& rhs)
{
    Operation::operator=(rhs);
    this->left = rhs.left->copy();
    this->middle = rhs.middle->copy();
    this->right = rhs.right->copy();
    delete rhs.left;
    delete rhs.middle;
    delete rhs.right;
    return *this;
}

//  __________________________________________________________________________
// |                                                                          |
// | Class: Ternary                                                           |
// | Function: operator==                                                     |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Ternary::operator==(
        const Ternary& rhs) const
{
    return ((Expression::operator==(rhs)) &&
        (*this->get_left() == *rhs.get_left()) && 
        (*this->get_middle() == *rhs.get_middle()) &&
        (*this->get_right() == *rhs.get_right()));
}

//  __________________________________________________________________________
// |                                                                          |
// | Class: Ternary                                                           |
// | Function: prefix                                                         |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Operations::Ternary::prefix() const
{
    TokenList_t output;
    this->add_open_parentheses(output);
    output.push_back(this->get_token());
    this->add_open_argument_parentheses(output);
    output.splice(output.end(), this->left->prefix());
    output.splice(output.end(), this->middle->prefix());
    output.splice(output.end(), this->right->prefix());
    this->add_close_argument_parentheses(output);
    this->add_close_parentheses(output);
    return output;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Ternary                                                           |
// | Function: postfix                                                        |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Operations::Ternary::postfix() const
{
    TokenList_t output;
    this->add_open_parentheses(output);
    this->add_open_argument_parentheses(output);
    output.splice(output.end(), this->left->postfix());
    output.splice(output.end(), this->middle->postfix());
    output.splice(output.end(), this->right->postfix());
    this->add_close_argument_parentheses(output);
    output.push_back(this->get_token());
    this->add_close_parentheses(output);
    return output;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Ternary                                                           |
// | Function: size                                                           |
// |__________________________________________________________________________|
size_t Mathematics::Expressions::Operations::Ternary::size() const
{
    return 1U + this->get_left()->size() + this->get_middle()->size() +
        this->get_right()->size();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Ternary                                                           |
// | Function: height                                                         |
// |__________________________________________________________________________|
size_t Mathematics::Expressions::Operations::Ternary::height() const
{
    return 1U + std::max({ this->get_left()->height(),
            this->get_middle()->height(),
            this->get_right()->height() });
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Ternary                                                           |
// | Function: contains                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Ternary::contains(
        const Token_t& token_in) const
{
    return this->get_left()->contains(token_in) || 
        this->get_middle()->contains(token_in) ||
        this->get_right()->contains(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Ternary                                                           |
// | Function: contains_variable                                              |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Ternary::contains_variable() const
{
    return this->get_left()->contains_variable() || 
        this->get_middle()->contains_variable() ||
        this->get_right()->contains_variable();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Ternary                                                           |
// | Function: get_variables                                                  |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Operations::Ternary::get_variables() const
{
    TokenList_t variables;
    variables.splice(variables.end(), this->get_left()->get_variables());
    variables.splice(variables.end(), this->get_middle()->get_variables());
    variables.splice(variables.end(), this->get_right()->get_variables());
    variables.sort();
    variables.unique();
    return variables;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Ternary                                                           |
// | Function: arity                                                          |
// |__________________________________________________________________________|
Mathematics::Natural 
Mathematics::Expressions::Operations::Ternary::arity() const
{
    return 3U;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Ternary                                                           |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Ternary::is_token(
        const Token_t& token_in)
{
    return false;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Ternary                                                           |
// | Function: get_precedence                                                 |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenPrecedence_t 
Mathematics::Expressions::Operations::Ternary::get_precedence(
        Type_t type_in, 
        const Token_t& token_in)
{
    return MIN_PRECEDENCE;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Ternary                                                           |
// | Function: Destructor                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Ternary::~Ternary()
{
    delete this->left;
    delete this->middle;
    delete this->right;
}

//  __________________________________________________________________________
// |                                                                          |
// | Class: Ternary                                                           |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
void Mathematics::Expressions::Operations::Ternary::print(
        TokenStream_t& stream, 
        const Token_t& prefix_in,
        bool is_last) const
{
    stream << prefix_in << (!is_last ? L"├──" : L"└──") << L"(" <<
            this->get_token() << L")" << std::endl;

    std::wstring new_prefix = prefix_in + (!is_last ? L"│   " : L"    ");

    // Enter the next tree level - left and right branch
    stream << new_prefix << L"│   " << std::endl;
    this->get_left()->print(stream, new_prefix, false);
    stream << new_prefix << L"│   " << std::endl;
    this->get_middle()->print(stream, new_prefix, false);
    stream << new_prefix << L"│   " << std::endl;
    this->get_right()->print(stream, new_prefix, true);
}
