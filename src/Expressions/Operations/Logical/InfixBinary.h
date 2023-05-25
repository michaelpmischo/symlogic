// ============================================================================
//! @file InfixBinary.h
//! @author Michael P. MIscho
//! @date May 4, 2023
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
#ifndef __MATHEMATICS_EXPRESSIONS_OPERATIONS_LOGICAL_INFIXBINARY_H_
#define __MATHEMATICS_EXPRESSIONS_OPERATIONS_LOGICAL_INFIXBINARY_H_
#include <Expressions/Operations/Binary.h>

namespace Mathematics
{
namespace Expressions
{
namespace Operations
{
namespace Logical
{
//  __________________________________________________________________________
// |                                                                          |
// |                                                                          |
// |                                InfixBinary                               |
// |                                                                          |
// |__________________________________________________________________________|
class InfixBinary : public Binary
{
public:
    InfixBinary(const Token_t& token_in,
            Expression* left_in,
            Expression* right_in,
            const TokenPair_t& parentheses_in = { "","" },
            const TokenPair_t& argumant_parentheses_in = { "","" });

    InfixBinary(const InfixBinary& rhs);
    InfixBinary(const InfixBinary& rhs,
            const TokenPair_t& parentheses_in);
    InfixBinary(InfixBinary&& rhs);

    InfixBinary& operator=(const InfixBinary& rhs);
    InfixBinary& operator=(InfixBinary&& rhs);

    // Public Pure Virtual Functions of Expression Implemented.
    virtual TokenList_t infix() const override;
    virtual Expression* simplify() const override;;
    virtual Expression* derivative(const Token_t& token_in) const override;
    virtual Expression* integral(const Token_t& token_in) const override;
    virtual Real solution(const TokenValueMap_t& values_in = {}) const override;
    virtual Expression* copy(
        const TokenPair_t& parentheses_in = { "","" }) const override;

    static bool is_token(const Token_t& token_in);
    static TokenPrecedence_t get_precedence(Type_t type_in,
        const Token_t& token_in);

    virtual ~InfixBinary() = default;

protected:
    static const LogicalBinaryHash_t operations;
    static const PrecedenceHash_t precedences;

private:
    
    static bool approximation(const Real& x, const Real& y);
    static bool equal(const Real& x, const Real& y);
    static bool not_equal(const Real& x, const Real& y);
    static bool greater_than(const Real& x, const Real& y);
    static bool less_than(const Real& x, const Real& y);
    static bool less_than_or_equal(const Real& x, const Real& y);
    static bool greater_than_or_equal(const Real& x, const Real& y);
    static bool implies(const Real& x, const Real& y);
    static bool and(const Real& x, const Real& y);
    static bool or(const Real& x, const Real& y);
}; // class InfixBinary
} // namespace Logical
} // namespace Operations
} // namespace Expressions
} // namespace Mathematics

#endif // __MATHEMATICS_EXPRESSIONS_OPERATIONS_LOGICAL_INFIXBINARY_H_