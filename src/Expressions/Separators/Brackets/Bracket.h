// ============================================================================
//! @file Bracket.h
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
#ifndef __MATHEMATICS_EXPRESSIONS_SEPARATORS_BRACKETS_BRACKET_H_
#define __MATHEMATICS_EXPRESSIONS_SEPARATORS_BRACKETS_BRACKET_H_
#include <Expressions/Separators/Separator.h>

namespace Mathematics
{
namespace Expressions
{
namespace Separators
{
//  __________________________________________________________________________
// |                                                                          |
// |                                                                          |
// |                                   Bracket                                |
// |                                                                          |
// |__________________________________________________________________________|
// 
// --------------------------------- Description ------------------------------
//! @brief
// ____________________________________________________________________________
class Bracket : public Separator
{
public:

    Bracket(const Token_t& token_in,
            const TokenPair_t& parenethesis_in = { L"",L"" });
    Bracket(const Bracket& rhs);
    Bracket(const Bracket& rhs, const TokenPair_t& parenethesis_in);
    Bracket(Bracket&& rhs);

    Bracket& operator=(const Bracket& rhs);
    Bracket& operator=(Bracket&& rhs);

    virtual bool is_bracket() const override;

    static bool is_token(const Token_t& token_in);
    static TokenPrecedence_t get_precedence(Type_t type_in,
            const Token_t& token_in);
    static Token_t get_opposing(const Token_t& token_in);

    virtual ~Bracket() = default;
}; // class Bracket
} // namespace Separators
} // namespace Expressions
} // namespace Mathematics

#endif // __MATHEMATICS_EXPRESSIONS_SEPARATORS_BRACKETS_BRACKET_H_