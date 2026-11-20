// ============================================================================
//! @file Generic.cpp
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
#include <Expressions/Separators/Generic.h>

const Mathematics::Expressions::TokenSet_t 
Mathematics::Expressions::Separators::Generic::generics =
{
    ",",
    " ",
    ":",
    ";",
};


//  __________________________________________________________________________
// |                                                                          |
// | Class: Generic                                                           |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Generic::Generic(
        const Token_t& token_in, Expression* next_in, 
        const TokenPair_t& parentheses_in) :
    Separator(token_in, parentheses_in),
    next(next_in)
{
}



//  __________________________________________________________________________
// |                                                                          |
// | Class: Generic                                                           |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Generic::Generic(const Generic& rhs) :
    Separator(rhs),
    next(rhs.next->copy())
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Generic                                                           |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Generic::Generic(const Generic& rhs, 
        const TokenPair_t& parentheses_in) :
    Separator(rhs, parentheses_in),
    next(rhs.next->copy())
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Generic                                                           |
// | Function: Move Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Generic::Generic(Generic&& rhs) :
    Separator(rhs),
    next(rhs.next->copy())
{
    delete rhs.next;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Generic                                                           |
// | Function: Assignment Operator                                            |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Generic&
Mathematics::Expressions::Separators::Generic::operator=(const Generic& rhs)
{
    Separator::operator=(rhs);
    this->next = rhs.next->copy();
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Generic                                                           |
// | Function: Move Operator                                                  |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Generic&
Mathematics::Expressions::Separators::Generic::operator=(Generic&& rhs)
{
    Separator::operator=(rhs);
    this->next = rhs.next->copy();
    delete rhs.next;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Generic                                                           |
// | Function: prefix                                                         |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Separators::Generic::prefix() const
{
    TokenList_t tokens;
    tokens.push_back(this->get_token());
    tokens.splice(tokens.end(), this->get_next()->prefix());
    return tokens;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Generic                                                           |
// | Function: infix                                                          |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Separators::Generic::infix() const
{
    return this->prefix();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Generic                                                           |
// | Function: postfix                                                        |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Separators::Generic::postfix() const
{
    TokenList_t tokens;
    tokens.splice(tokens.end(), this->get_next()->postfix());
    tokens.push_back(this->get_token());
    return tokens;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Generic                                                           |
// | Function: size                                                           |
// |__________________________________________________________________________|
size_t Mathematics::Expressions::Separators::Generic::size() const
{
    return 1U + this->get_next()->size();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Generic                                                           |
// | Function: height                                                         |
// |__________________________________________________________________________|
size_t Mathematics::Expressions::Separators::Generic::height() const
{
    return 1U + this->get_next()->height();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Generic                                                           |
// | Function: simplify                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Separators::Generic::simplify() const
{
    return this->get_next()->simplify();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Generic                                                           |
// | Function: derivative                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Separators::Generic::derivative(
        const Token_t& token_in) const
{
    return this->get_next()->derivative(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Generic                                                           |
// | Function: integral                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Separators::Generic::integral(
        const Token_t& token_in) const
{
    return this->get_next()->integral(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Generic                                                           |
// | Function: solution                                                       |
// |__________________________________________________________________________|
Mathematics::Real Mathematics::Expressions::Separators::Generic::solution(
        const TokenValueMap_t& values_in) const
{
    return this->get_next()->solution(values_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Generic                                                           |
// | Function: solution                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Separators::Generic::get_variables() const
{
    return this->get_next()->get_variables();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Generic                                                           |
// | Function: contains                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Separators::Generic::contains(
        const Token_t& token_in) const
{
    return false;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Generic                                                           |
// | Function: is_bracket                                                     |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Separators::Generic::is_bracket() const
{
    return false;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Generic                                                           |
// | Function: contains_variable                                              |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Separators::Generic::contains_variable() const
{
    return this->get_next()->contains_variable();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Generic                                                           |
// | Function: copy                                                           |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Separators::Generic::copy(
        const TokenPair_t& parentheses_in) const
{
    return new Generic(*this, parentheses_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Generic                                                           |
// | Function: get_branches                                                   |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression::ExpressionList_t
Mathematics::Expressions::Separators::Generic::get_branches() const
{
	return { this->get_next() };
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Generic                                                           |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Separators::Generic::is_token(
        const Token_t& token_in)
{
    return (generics.find(token_in) != generics.end());
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Generic                                                           |
// | Function: get_precedence                                                 |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenPrecedence_t
Mathematics::Expressions::Separators::Generic::get_precedence(
        Type_t type_in,
        const Token_t& token_in)
{
    return MIN_PRECEDENCE;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Generic                                                           |
// | Function: Destructor                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Generic::~Generic()
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Generic                                                           |
// | Function: print                                                          |
// |__________________________________________________________________________|
void Mathematics::Expressions::Separators::Generic::pretty_tree(
        std::stringstream& stream, 
        const std::string& prefix_in,
        bool is_last) const
{
	stream << prefix_in <<
		(!is_last ? "\xC3\xC4\xC4" : "\xC0\xC4\xC4") <<
		"(" << this->get_token() << ")" << std::endl;

    std::string new_prefix = prefix_in + (!is_last ? "\xB3   " : "    ");

	// Enter the next tree level - left and right branch
	stream << new_prefix << "\xB3   " << std::endl;
	this->get_next()->pretty_tree(stream, new_prefix, true);
}

