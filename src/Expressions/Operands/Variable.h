// ============================================================================
//! @file Variable.h
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
#ifndef __MATHEMATICS_EXPRESSIONS_OPERANDS_VARIABLE_H_
#define __MATHEMATICS_EXPRESSIONS_OPERANDS_VARIABLE_H_
#include <Expressions/Operands/Operand.h>

namespace Mathematics
{
namespace Expressions
{
namespace Operands
{
//  __________________________________________________________________________
// |                                                                          |
// |                                                                          |
// |                                  Variable                                |
// |                                                                          |
// |__________________________________________________________________________|
// 
// --------------------------------- Description ------------------------------
//! @brief
// ____________________________________________________________________________
class Variable : public Operand
{
public:
    Variable(const Token_t& token_in,
        const TokenPair_t& parentheses_in = { L"",L"" });
    Variable(const Variable& rhs);
    Variable(const Variable& rhs,
        const TokenPair_t& parentheses_in);
    Variable(Variable&& rhs);

    Variable& operator=(const Variable& rhs);
    Variable& operator=(Variable&& rhs);

    // Implemented Pure Virtual Functions from Expression.
    virtual bool contains_variable() const override;
    virtual Expression* derivative(const Token_t& token_in) const override;
    virtual Expression* integral(const Token_t& token_in) const override;
    virtual Real solution(const TokenValueMap_t& values_in = {}) const override;
    virtual TokenList_t get_variables() const override;
    virtual Expression* copy(
        const TokenPair_t& parentheses_in = {L"",L"" }) const override;

    static bool is_token(const Token_t& token_in);
    static TokenPrecedence_t get_precedence(Type_t type_in, 
        const Token_t& token_in);

    virtual ~Variable() = default;
}; // class Variable
} // namespace Operands
} // namespace Expressions
} // namespace Mathematics

#endif // __MATHEMATICS_EXPRESSIONS_OPERANDS_VARIABLE_H_