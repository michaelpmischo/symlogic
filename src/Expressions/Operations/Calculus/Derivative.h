// ============================================================================
//! @file Derivative.h
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
#ifndef __MATHEMATICS_EXPRESSIONS_OPERATIONS_CALCULUS_DERIVATIVE_H_
#define __MATHEMATICS_EXPRESSIONS_OPERATIONS_CALCULUS_DERIVATIVE_H_
#include <Expressions/Operations/Functional.h>

namespace Mathematics
{
namespace Expressions
{
namespace Operations
{
class Unary;
class Binary;
class Ternary;

namespace Calculus
{
//  __________________________________________________________________________
// |                                                                          |
// |                                                                          |
// |                                 Derivative                               |
// |                                                                          |
// |__________________________________________________________________________|
class Derivative : public Functional
{
public:
	typedef Expression* (*DerivativeOperation_t)(
		const Token_t& token_in,
		const Expression* expression_in);
    typedef std::map<Token_t, DerivativeOperation_t> DerivativeHash_t;

    typedef Expression* (*UnaryDerivativeOperation_t)(
            const Token_t& token_in,
            const Unary* expression_in);
    typedef std::map<Token_t, UnaryDerivativeOperation_t> UnaryDerivativeHash_t;
	typedef Expression* (*BinaryDerivativeOperation_t)(
		    const Token_t& token_in,
		    const Binary* expression_in);
    typedef std::map<Token_t, BinaryDerivativeOperation_t> BinaryDerivativeHash_t;
	typedef Expression* (*TernaryDerivativeOperation_t)(
		const Token_t& token_in,
		const Ternary* expression_in);
    typedef std::map<Token_t, TernaryDerivativeOperation_t> TernaryDerivativeHash_t;
	typedef Expression* (*FunctionalDerivativeOperation_t)(
		const Token_t& token_in,
		const Functional* expression_in);
	typedef std::map<Token_t, FunctionalDerivativeOperation_t> FunctionalDerivativeHash_t;

    
    Derivative(const Token_t& token_in,
            Expression* variable_in,
            Expression* function_in,
            const TokenPair_t& parentheses_in = { L"",L"" },
            const TokenPair_t& argumant_parentheses_in = { L"",L"" });
    Derivative(const Derivative& rhs);
    Derivative(const Derivative& rhs, 
            const TokenPair_t& parentheses_in);
    Derivative(Derivative&& rhs);

    Derivative& operator=(const Derivative& rhs);
    Derivative& operator=(Derivative&& rhs);

    // Static Functions
    static bool is_token(const Token_t& token_in);
    static TokenPrecedence_t get_precedence(Type_t type_in, 
            const Token_t& token_in);

    // Derivative Static Functions
    static bool is_common(const Token_t& token_in);
	static Expression* get_common(const Token_t& token_in,
		const Unary* expression_in);
	static Expression* get_common(const Token_t& token_in,
		const Binary* expression_in);
	static Expression* get_common(const Token_t& token_in,
		const Ternary* expression_in);
	static Expression* get_common(const Token_t& token_in,
		const Functional* expression_in);

    virtual ~Derivative() = default;
protected:    
    static const UnaryDerivativeHash_t unary_common;
    static const BinaryDerivativeHash_t binary_common;
    static const TernaryDerivativeHash_t ternary_common;
    static const FunctionalDerivativeHash_t functional_common;

    inline Expression* get_variable() const;

private:
	// Unary Common Derivatives
	static Expression* ln(const Token_t& token_in,
		const Unary* expression_in);
	static Expression* exp(const Token_t& token_in,
		const Unary* expression_in);

	static Expression* sin(const Token_t& token_in,
		const Unary* expression_in);
	static Expression* cos(const Token_t& token_in,
		const Unary* expression_in);
	static Expression* tan(const Token_t& token_in,
		const Unary* expression_in);

	static Expression* power_rule(const Token_t& token_in,
		const Binary* expression_in);
	static Expression* product_rule(const Token_t& token_in,
		const Binary* expression_in);
	static Expression* quotient_rule(const Token_t& token_in,
		const Binary* expression_in);
	static Expression* sum_and_difference(const Token_t& token_in,
		const Binary* expression_in);

    Expression*						        variable;
}; // class Derivative
} // namespace Calculus
} // namespace Operations
} // namespace Expressions
} // namespace Mathematics



//  __________________________________________________________________________
// |                                                                          |
// | Class: Derivative                                                        |
// | Function: get_varaiable                                                  |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Calculus::Derivative::get_variable() const
{
    return this->variable;
}

#endif // __MATHEMATICS_EXPRESSIONS_OPERATIONS_CALCULUS_DERIVATIVE_H_