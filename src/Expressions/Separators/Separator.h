// ============================================================================
//! @file Separator.h
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
#ifndef __MATHEMATICS_EXPRESSIONS_SEPARATORS_SEPARATOR_H_
#define __MATHEMATICS_EXPRESSIONS_SEPARATORS_SEPARATOR_H_
#include <Expressions/Expression.h>

namespace Mathematics
{
namespace Expressions
{
namespace Separators
{
//  __________________________________________________________________________
// |                                                                          |
// |                                                                          |
// |                                  Separator                               |
// |                                                                          |
// |__________________________________________________________________________|
// 
// --------------------------------- Description ------------------------------
//! @brief
// ____________________________________________________________________________
class Separator : public Expression
{
public:
    Separator(const Token_t& token_in,
            const TokenPair_t& parenethesis_in = { "","" });
    Separator(const Separator& rhs);
    Separator(const Separator& rhs,
            const TokenPair_t& parenethesis_in);
    Separator(Separator&& rhs);

    Separator& operator=(const Separator& rhs);
    Separator& operator=(Separator&& rhs);

    // Implemented Pure Virtual Functions of Expression
    virtual bool is_operator() const override;
    virtual bool is_operand() const override;
    virtual bool is_separator() const override;

    // Static Functions
    static bool is_token(const Token_t& token_in);
    static TokenPrecedence_t get_precedence(Type_t type_in,
        const Token_t& token_in);

    virtual ~Separator() = default;
}; // class Separator
} // namespace Separators
} // namespace Expressions
} // namespace Mathematics

#endif // __MATHEMATICS_EXPRESSIONS_SEPARATORS_SEPARATOR_H_


