// ============================================================================
//! @file Separator.cpp
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
#include <Expressions/Separators/Separator.h>
#include <Expressions/Separators/Brackets/Bracket.h>
#include <Expressions/Separators/Generic.h>


//  __________________________________________________________________________
// |                                                                          |
// | Class: Separator                                                         |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Separator::Separator(
		const Token_t& token_in, 
		const TokenPair_t& parentheses_in) :
	Expression(token_in, parentheses_in)
{
}

//  __________________________________________________________________________
// |                                                                          |
// | Class: Separator                                                         |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Separator::Separator(
		const Separator& rhs) :
	Expression(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Separator                                                         |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Separator::Separator(
		const Separator& rhs,
		const TokenPair_t& parentheses_in) :
	Expression(rhs.get_token(), parentheses_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Separator                                                         |
// | Function: Move Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Separator::Separator(Separator&& rhs) :
	Expression(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Separator                                                         |
// | Function: Assignment Operator                                            |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Separator& 
Mathematics::Expressions::Separators::Separator::operator=(
		const Separator& rhs)
{
	Expression::operator=(rhs);
	return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Separator                                                         |
// | Function: Move Operator                                                  |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Separator& 
Mathematics::Expressions::Separators::Separator::operator=(Separator&& rhs)
{
	Expression::operator=(rhs);
	return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Separator                                                         |
// | Function: is_operator                                                    |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Separators::Separator::is_operator() const
{
	return false;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Separator                                                         |
// | Function: in_operand                                                     |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Separators::Separator::is_operand() const
{
	return false;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Separator                                                         |
// | Function: in_separator                                                   |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Separators::Separator::is_separator() const
{
	return true;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Separator                                                         |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Separators::Separator::is_token(
		const Token_t& token_in)
{
	return Generic::is_token(token_in) ||
		Bracket::is_token(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Separator                                                         |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenPrecedence_t 
Mathematics::Expressions::Separators::Separator::get_precedence(
		Type_t type_in, 
		const Token_t& token_in)
{
	switch (type_in)
	{
		case Type_t::OPEN_BRACKET:
		case Type_t::CLOSE_BRACKET:
			return Bracket::get_precedence(type_in, token_in);
			break;

		case Type_t::SEPARATOR:
			return Generic::get_precedence(type_in, token_in);
			break;

		default:
			return MIN_PRECEDENCE;
			break;

	}
}


