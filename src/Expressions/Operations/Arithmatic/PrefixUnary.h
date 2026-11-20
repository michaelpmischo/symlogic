// ============================================================================
//! @file PrefixUnary.h
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
#ifndef __MATHEMATICS_EXPRESSIONS_OPERATIONS_ARITHMATIC_PREFIXUNARY_H_
#define __MATHEMATICS_EXPRESSIONS_OPERATIONS_ARITHMATIC_PREFIXUNARY_H_
#include <Expressions/Operations/Unary.h>

namespace Mathematics
{
namespace Expressions
{
namespace Operations
{
namespace Arithmatic
{
//  __________________________________________________________________________
// |                                                                          |
// |                                                                          |
// |                                PrefixUnary                               |
// |                                                                          |
// |__________________________________________________________________________|
class PrefixUnary : public Unary
{
public:
    PrefixUnary(const Token_t& token_in,
            Expression* left_in, 
            const TokenPair_t& parentheses_in = { "","" },
            const TokenPair_t& argumant_parentheses_in = { "","" });
    PrefixUnary(const PrefixUnary& rhs);
    PrefixUnary(const PrefixUnary& rhs,
            const TokenPair_t& parentheses_in);
    PrefixUnary(PrefixUnary&& rhs);

    PrefixUnary& operator=(const PrefixUnary& rhs);
    PrefixUnary& operator=(PrefixUnary&& rhs);

    // Public Pure Virtual Functions of Expression Implemented.
    virtual TokenList_t infix() const override;
    virtual Expression* simplify() const override;
    virtual Expression* derivative(const Token_t& token_in) const override;
    virtual Expression* integral(const Token_t& token_in) const override;
    virtual Real solution(const TokenValueMap_t& values_in = {}) const override;
    virtual Expression* copy(
            const TokenPair_t& parentheses_in = { "","" }) const override;

    static bool is_token(const Token_t& token_in);
    static TokenPrecedence_t get_precedence(Type_t type_in, const Token_t& token_in);

    virtual ~PrefixUnary() = default;

protected:
    static const ArithmaticUnaryHash_t operations;

private:
    static Real negate(const Real& x);
    static Real ln(const Real& x);
    static Real sqrt(const Real& x);
    static Real exp(const Real& x);
    static Real abs(const Real& x);

    static Real sin(const Real& x);
    static Real cos(const Real& x);
    static Real tan(const Real& x);
    static Real csc(const Real& x);
    static Real sec(const Real& x);
    static Real cot(const Real& x);

    static Real asin(const Real& x);
    static Real acos(const Real& x);
    static Real atan(const Real& x);
    static Real acsc(const Real& x);
    static Real asec(const Real& x);
    static Real acot(const Real& x);

    static Real sinh(const Real& x);
    static Real cosh(const Real& x);
    static Real tanh(const Real& x);
    static Real csch(const Real& x);
    static Real sech(const Real& x);
    static Real coth(const Real& x);
    static Real asinh(const Real& x);
    static Real acosh(const Real& x);
    static Real atanh(const Real& x);
    static Real acsch(const Real& x);
    static Real asech(const Real& x);
    static Real acoth(const Real& x);
}; // class PrefixUnary
} // namespace Arithmatic
} // namespace Operations
} // namespace Expressions
} // namespace Mathematics

#endif // __MATHEMATICS_EXPRESSIONS_OPERATIONS_ARITHMATIC_PREFIXUNARY_H_