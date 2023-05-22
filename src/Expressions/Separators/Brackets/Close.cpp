// ============================================================================
//! @file Close.cpp
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
#include <Expressions/Separators/Brackets/Close.h>

const Mathematics::TokenMap_t 
Mathematics::Expressions::Separators::Brackets::Close::brackets =
{
	// "[]"
	{"]", "["},

	// "{}"
	{"}", "{"},

	// "()"
	{")", "("},
};


//  __________________________________________________________________________
// |                                                                          |
// | Class: Close                                                             |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Brackets::Close::Close(
		const Token_t& token_in) :
	Bracket(token_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Close                                                             |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Brackets::Close::Close(
		const Close& rhs) :
	Bracket(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Close                                                             |
// | Function: Move Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Brackets::Close::Close(
		Close&& rhs) :
	Bracket(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Close                                                             |
// | Function: Assignment Operator                                            |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Brackets::Close& 
Mathematics::Expressions::Separators::Brackets::Close::operator=(
		const Close& rhs)
{
	Bracket::operator=(rhs);
	return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Close                                                             |
// | Function: Move Operator                                                  |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Brackets::Close&
Mathematics::Expressions::Separators::Brackets::Close::operator=(Close&& rhs)
{
	Bracket::operator=(rhs);
	return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Close                                                             |
// | Function: prefix                                                         |
// |__________________________________________________________________________|
Mathematics::TokenList_t 
Mathematics::Expressions::Separators::Brackets::Close::prefix() const
{
	return { this->get_token() };
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Close                                                             |
// | Function: infix                                                          |
// |__________________________________________________________________________|
Mathematics::TokenList_t 
Mathematics::Expressions::Separators::Brackets::Close::infix() const
{
	return this->prefix();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Close                                                             |
// | Function: postfix                                                        |
// |__________________________________________________________________________|
Mathematics::TokenList_t 
Mathematics::Expressions::Separators::Brackets::Close::postfix() const
{
	return this->prefix();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Close                                                             |
// | Function: size                                                           |
// |__________________________________________________________________________|
size_t Mathematics::Expressions::Separators::Brackets::Close::size() const
{
	return 1U;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Close                                                             |
// | Function: height                                                         |
// |__________________________________________________________________________|
size_t Mathematics::Expressions::Separators::Brackets::Close::height() const
{
	return 0U;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Close                                                             |
// | Function: simplify                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Separators::Brackets::Close::simplify() const
{
	return this->copy();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Close                                                             |
// | Function: derivative                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Separators::Brackets::Close::derivative(
		const Token_t& token_in) const
{
	return this->copy();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Close                                                             |
// | Function: integral                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Separators::Brackets::Close::integral(
		const Token_t& token_in) const
{
	return this->copy();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Close                                                             |
// | Function: solution                                                       |
// |__________________________________________________________________________|
Mathematics::Real 
Mathematics::Expressions::Separators::Brackets::Close::solution(
		const TokenValueMap_t& values_in) const
{
	return NAN;
}



//  __________________________________________________________________________
// |                                                                          |
// | Class: Close                                                             |
// | Function: solution                                                       |
// |__________________________________________________________________________|
Mathematics::TokenList_t 
Mathematics::Expressions::Separators::Brackets::Close::get_variables() const
{
	return {};
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Close                                                             |
// | Function: contains                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Separators::Brackets::Close::contains(
		const Token_t& token_in) const
{
	return false;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Close                                                             |
// | Function: contains_variable                                              |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Separators::Brackets::Close::contains_variable() const
{
	return false;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Close                                                             |
// | Function: copy                                                           |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Separators::Brackets::Close::copy(
	const TokenPair_t& parentheses_in) const
{
	return new Close(*this);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Close                                                             |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Separators::Brackets::Close::is_token(
		const Token_t& token_in)
{
	return (brackets.find(token_in) != brackets.end());
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Close                                                             |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
Mathematics::TokenPrecedence_t
Mathematics::Expressions::Separators::Brackets::Close::get_precedence(
		Type_t type_in,
		const Token_t& token_in)
{
	return MAX_PRECEDENCE;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Close                                                             |
// | Function: opposing                                                       |
// |__________________________________________________________________________|
Mathematics::Token_t
Mathematics::Expressions::Separators::Brackets::Close::get_opposing(
		const Token_t& token_in)
{
	if (Close::is_token(token_in))
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
// | Class: Close                                                             |
// | Function: print                                                          |
// |__________________________________________________________________________|
void Mathematics::Expressions::Separators::Brackets::Close::print(
		TokenStream_t& stream, 
		const Token_t& prefix_in,
		bool is_last) const
{
	stream << prefix_in << (!is_last ? "├──" : "└──") << "(" <<
		this->get_token() << ")" << std::endl;
}

