// ============================================================================
//! @file Open.cpp
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
#include <Expressions/Separators/Brackets/Open.h>

const Mathematics::Expressions::TokenMap_t 
Mathematics::Expressions::Separators::Brackets::Open::brackets =
{
    // "[]"
    {"[", "]"},

    // "{}"
    {"{", "}"},

    // "()"
    {"(", ")"},
};


//  __________________________________________________________________________
// |                                                                          |
// | Class: Open                                                              |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Brackets::Open::Open(
        const Token_t& token_in,
        Expression* inside_in) :
    Bracket(token_in, { token_in , Open::get_opposing(token_in) }),
    inside(inside_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Open                                                              |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Brackets::Open::Open(const Open& rhs) :
    Bracket(rhs),
    inside(rhs.inside->copy())
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Open                                                              |
// | Function: Move Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Brackets::Open::Open(Open&& rhs) :
    Bracket(rhs),
    inside(rhs.inside->copy())
{
    delete rhs.inside;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Open                                                              |
// | Function: Assignment Operator                                            |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Brackets::Open& 
Mathematics::Expressions::Separators::Brackets::Open::operator=(
        const Open& rhs)
{
    Bracket::operator=(rhs);
    this->inside = rhs.inside->copy();
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Open                                                              |
// | Function: Move Operator                                                  |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Brackets::Open& 
Mathematics::Expressions::Separators::Brackets::Open::operator=(Open&& rhs)
{
    Bracket::operator=(rhs);
    this->inside = rhs.inside->copy();
    delete rhs.inside;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Open                                                              |
// | Function: prefix                                                         |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Separators::Brackets::Open::prefix() const
{
    TokenList_t output;
    output.push_back(this->get_token());
    output.push_back(Bracket::get_opposing(this->get_token()));
    output.splice(output.end(), this->inside->prefix());
    return output;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Open                                                              |
// | Function: infix                                                          |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Separators::Brackets::Open::infix() const
{
    TokenList_t output;
    output.push_back(this->get_token());
    output.splice(output.end(), this->inside->infix());
    output.push_back(Bracket::get_opposing(this->get_token()));
    return output;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Open                                                              |
// | Function: postfix                                                        |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Separators::Brackets::Open::postfix() const
{
    TokenList_t output;
    output.splice(output.end(), this->inside->postfix());
    output.push_back(this->get_token());
    output.push_back(Bracket::get_opposing(this->get_token()));
    return output;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Open                                                              |
// | Function: size                                                           |
// |__________________________________________________________________________|
size_t Mathematics::Expressions::Separators::Brackets::Open::size() const
{
    return 1U + this->inside->size();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Open                                                              |
// | Function: height                                                         |
// |__________________________________________________________________________|
size_t Mathematics::Expressions::Separators::Brackets::Open::height() const
{
    return 1U + this->inside->height();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Open                                                              |
// | Function: simplify                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Separators::Brackets::Open::simplify() const
{
    return this->inside->simplify();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Open                                                              |
// | Function: derivative                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Separators::Brackets::Open::derivative(
        const Token_t& token_in) const
{
    return this->inside->derivative(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Open                                                              |
// | Function: integral                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Separators::Brackets::Open::integral(
        const Token_t& token_in) const
{
    return this->inside->integral(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Open                                                              |
// | Function: solution                                                       |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Separators::Brackets::Open::solution(
        const TokenValueMap_t& values_in) const
{
    return this->get_inside()->solution(values_in);
}



//  __________________________________________________________________________
// |                                                                          |
// | Class: Open                                                              |
// | Function: solution                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Separators::Brackets::Open::get_variables() const
{
    return this->get_inside()->get_variables();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Open                                                              |
// | Function: contains                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Separators::Brackets::Open::contains(
        const Token_t& token_in) const
{
    return this->inside->contains(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Open                                                              |
// | Function: contains_variable                                              |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Separators::Brackets::Open::contains_variable() const
{
    return this->inside->contains_variable();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Open                                                              |
// | Function: copy                                                           |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Separators::Brackets::Open::copy(
        const TokenPair_t& parentheses_in) const
{
    return new Open(*this);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Open                                                              |
// | Function: get_branches                                                   |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression::ExpressionList_t
Mathematics::Expressions::Separators::Brackets::Open::get_branches() const
{
	return { this->get_inside() };
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Open                                                              |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Separators::Brackets::Open::is_token(
        const Token_t& token_in)
{
    return (brackets.find(token_in) != brackets.end());
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Open                                                              |
// | Function: get_precedence                                                 |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenPrecedence_t
Mathematics::Expressions::Separators::Brackets::Open::get_precedence(
        Type_t type_in,
        const Token_t& token_in)
{
    return MIN_PRECEDENCE;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Open                                                              |
// | Function: opposing                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Token_t
Mathematics::Expressions::Separators::Brackets::Open::get_opposing(
        const Token_t& token_in)
{
    if (Open::is_token(token_in))
    {
        return brackets.find(token_in)->second;
    }
    else
    {
        return "";
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Open                                                              |
// | Function: Destructor                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Brackets::Open::~Open()
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Open                                                              |
// | Function: print                                                          |
// |__________________________________________________________________________|
void Mathematics::Expressions::Separators::Brackets::Open::pretty_tree(
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
	this->get_inside()->pretty_tree(stream, new_prefix, true);
}
