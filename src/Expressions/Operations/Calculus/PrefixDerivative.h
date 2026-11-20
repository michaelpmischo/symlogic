// ============================================================================
//! @file PrefixDerivative.h
//! @author Michael P. MIscho
//! @date May 18, 2023
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
#ifndef __MATHEMATICS_EXPRESSIONS_OPERATIONS_CALCULUS_PREFIXDERIVATIVE_H_
#define __MATHEMATICS_EXPRESSIONS_OPERATIONS_CALCULUS_PREFIXDERIVATIVE_H_
#include <Expressions/Operations/Calculus/Derivative.h>

namespace Mathematics
{
namespace Expressions
{
namespace Operations
{
namespace Calculus
{
//  __________________________________________________________________________
// |                                                                          |
// |                                                                          |
// |                               PrefixDerivative                           |
// |                                                                          |
// |__________________________________________________________________________|
class PrefixDerivative : public Derivative
{
public:
    PrefixDerivative(const Token_t& token_in,
            Expression* variable_in,
            Expression* function_in,
            const TokenPair_t& parentheses_in = { "","" },
            const TokenPair_t& argumant_parentheses_in = { "","" });
    PrefixDerivative(const PrefixDerivative& rhs);
    PrefixDerivative(const PrefixDerivative& rhs,
            const TokenPair_t& parentheses_in);
    PrefixDerivative(PrefixDerivative&& rhs);

    PrefixDerivative& operator=(const PrefixDerivative& rhs);
    PrefixDerivative& operator=(PrefixDerivative&& rhs);

    // Public Pure Virtual Functions of Expression Implemented.
    virtual TokenList_t infix() const override;
    virtual Expression* simplify() const override;
    virtual Expression* derivative(const Token_t& token_in) const override;
    virtual Expression* integral(const Token_t& token_in) const override;
    virtual Real solution(const TokenValueMap_t& values_in = {}) const override;
    virtual Expression* copy(
            const TokenPair_t& parentheses_in = { "","" }) const override;

    // Static Functions
    static bool is_token(const Token_t& token_in);
    static TokenPrecedence_t get_precedence(Type_t type_in, 
            const Token_t& token_in);

    virtual ~PrefixDerivative() = default;
protected:
    static const DerivativeHash_t operations;

private:
    static Expression* differentiate(const Token_t& token_in,
            const Expression* expression_in);
}; // class PrefixDerivative
} // namespace Calculus
} // namespace Operations
} // namespace Expressions
} // namespace Mathematics


#endif // __MATHEMATICS_EXPRESSIONS_OPERATIONS_CALCULUS_PREFIXDERIVATIVE_H_