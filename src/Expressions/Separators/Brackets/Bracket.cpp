// ============================================================================
//! @file Bracket.cpp
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
#include <Expressions/Separators/Brackets/Bracket.h>
#include <Expressions/Separators/Brackets/Close.h>
#include <Expressions/Separators/Brackets/Open.h>

//  __________________________________________________________________________
// |                                                                          |
// | Class: Bracket                                                           |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Bracket::Bracket(
        const Token_t& token_in,
        const TokenPair_t& parenethesis_in) :
    Separator(token_in, parenethesis_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Bracket                                                           |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Bracket::Bracket(const Bracket& rhs) :
	Separator(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Bracket                                                           |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Bracket::Bracket(
        const Bracket& rhs,
        const TokenPair_t& parenethesis_in) :
    Separator(rhs, parenethesis_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Bracket                                                           |
// | Function: Move Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Bracket::Bracket(
        Bracket&& rhs) :
    Separator(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Bracket                                                           |
// | Function: Assignment Operator                                            |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Bracket& 
Mathematics::Expressions::Separators::Bracket::operator=(
        const Bracket& rhs)
{
    Separator::operator=(rhs);
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Bracket                                                           |
// | Function: Move Operator                                                  |
// |__________________________________________________________________________|
Mathematics::Expressions::Separators::Bracket& 
Mathematics::Expressions::Separators::Bracket::operator=(
        Bracket&& rhs)
{
    Separator::operator=(rhs);
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Bracket                                                           |
// | Function: is_bracket                                                     |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Separators::Bracket::is_bracket() const
{
    return true;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Bracket                                                           |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Separators::Bracket::is_token(
        const Token_t& token_in)
{
    return Brackets::Open::is_token(token_in) ||
        Brackets::Close::is_token(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Bracket                                                           |
// | Function: get_precedence                                                 |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenPrecedence_t 
Mathematics::Expressions::Separators::Bracket::get_precedence(
        Type_t type_in,
        const Token_t& token_in)
{
    switch (type_in)
    {
        case Type_t::OPEN_BRACKET:
            return Brackets::Open::get_precedence(type_in, token_in);
            break;

        case Type_t::CLOSE_BRACKET:
            return Brackets::Close::get_precedence(type_in, token_in);
            break;

        default:
            return MIN_PRECEDENCE;

    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Bracket                                                           |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Token_t 
Mathematics::Expressions::Separators::Bracket::get_opposing(
        const Token_t& token_in)
{
    if (Brackets::Close::is_token(token_in))
    {
        return Brackets::Close::get_opposing(token_in);
    }
    else if (Brackets::Open::is_token(token_in))
    {
        return Brackets::Open::get_opposing(token_in);
    }
    else
    {
        return "";
    }
}



