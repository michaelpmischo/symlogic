// ============================================================================
//! @file Functional.cpp
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
#include <Expressions/Operations/Functional.h>
#include <Expressions/Operations/Calculus/Derivative.h>


//  __________________________________________________________________________
// |                                                                          |
// | Class: Functional                                                        |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Functional::Functional(
        const Token_t& token_in,
        Expression* function_in,
        const TokenPair_t& parentheses_in,
        const TokenPair_t& argument_parentheses_in) :
    Operation(token_in, parentheses_in, argument_parentheses_in),
    function(function_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Functional                                                        |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Functional::Functional(
        const Functional& rhs) :
    Operation(rhs),
    function(rhs.function->copy())
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Functional                                                        |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Functional::Functional(
        const Functional& rhs, 
        const TokenPair_t& parentheses_in) :
    Operation(rhs, parentheses_in),
    function(rhs.function->copy())
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Functional                                                        |
// | Function: Move Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Functional::Functional(
        Functional&& rhs) :
    Operation(rhs),
    function(rhs.function->copy())
{
    delete rhs.function;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Functional                                                        |
// | Function: Assignment Operator                                            |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Functional& 
Mathematics::Expressions::Operations::Functional::operator=(
        const Functional& rhs)
{
    Operation::operator=(rhs);
    this->function = rhs.function->copy();
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Functional                                                        |
// | Function: Move Operator                                                  |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Functional& 
Mathematics::Expressions::Operations::Functional::operator=(
        Functional&& rhs)
{
    Operation::operator=(rhs);
    this->function = rhs.function->copy();
    delete rhs.function;
    return *this;
}

//  __________________________________________________________________________
// |                                                                          |
// | Class: Functional                                                        |
// | Function: operator==                                                     |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Functional::operator==(
        const Functional& rhs) const
{
    return ((Expression::operator==(rhs)) &&
        (*this->get_function() == *rhs.get_function()));
}

//  __________________________________________________________________________
// |                                                                          |
// | Class: Functional                                                        |
// | Function: prefix                                                         |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Operations::Functional::prefix() const
{
    TokenList_t output;
    this->add_open_parentheses(output);
    output.push_back(this->get_token());
    this->add_open_argument_parentheses(output);
    output.splice(output.end(), this->get_function()->prefix());
    this->add_close_argument_parentheses(output);
    this->add_close_parentheses(output);
    return output;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Functional                                                        |
// | Function: postfix                                                        |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Operations::Functional::postfix() const
{
    TokenList_t output;
    this->add_open_parentheses(output);
    this->add_open_argument_parentheses(output);
    output.splice(output.end(), this->get_function()->postfix());
    this->add_close_argument_parentheses(output);
    output.push_back(this->get_token());
    this->add_close_parentheses(output);
    return output;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Functional                                                        |
// | Function: size                                                           |
// |__________________________________________________________________________|
size_t Mathematics::Expressions::Operations::Functional::size() const
{
    return 1U + this->get_function()->size();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Functional                                                        |
// | Function: height                                                         |
// |__________________________________________________________________________|
size_t Mathematics::Expressions::Operations::Functional::height() const
{
    return 1U + this->get_function()->height();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Functional                                                        |
// | Function: contains                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Functional::contains(
        const Token_t& token_in) const
{
    return this->get_function()->contains(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Functional                                                        |
// | Function: contains_variable                                              |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Functional::contains_variable() const
{
    return this->get_function()->contains_variable();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Functional                                                        |
// | Function: get_variables                                                  |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Operations::Functional::get_variables() const
{
    TokenList_t variables;
    variables.splice(variables.end(), this->get_function()->get_variables());
    variables.sort();
    variables.unique();
    return variables;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Functional                                                        |
// | Function: arity                                                          |
// |__________________________________________________________________________|
Mathematics::Natural 
Mathematics::Expressions::Operations::Functional::arity() const
{
    return 1U;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Functional                                                        |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Functional::is_token(
        const Token_t& token_in)
{
    return 	//Calculus::Limit::is_token(token_in) ||
        Calculus::Derivative::is_token(token_in); // ||
//		Calculus::ImplicitDerivative::is_token(token_in) || 
//		Calculus::DefiniteIntegral::is_token(token_in) ||
//		Calculus::ImplicitDerivative::is_token(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Functional                                                        |
// | Function: get_precedence                                                 |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenPrecedence_t 
Mathematics::Expressions::Operations::Functional::get_precedence(
        Type_t type_in, 
        const Token_t& token_in)
{
    return MIN_PRECEDENCE;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Functional                                                        |
// | Function: Destructor                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Functional::~Functional()
{
    delete this->function;
}

//  __________________________________________________________________________
// |                                                                          |
// | Class: Functional                                                        |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
void Mathematics::Expressions::Operations::Functional::print(
        TokenStream_t& stream, 
        const Token_t& prefix_in,
        bool is_last) const
{
    stream << prefix_in << (!is_last ? L"├──" : L"└──") << L"(" <<
        this->get_token() << L")" << std::endl;

    std::wstring new_prefix = prefix_in + (!is_last ? L"│   " : L"    ");

    // Enter the next tree level - function and right branch
    stream << new_prefix << L"│   " << std::endl;
    this->get_function()->print(stream, new_prefix, true);
}
