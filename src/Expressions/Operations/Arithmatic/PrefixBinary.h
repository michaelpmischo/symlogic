// ============================================================================
//! @file PrefixBinary.h
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
#ifndef __MATHEMATICS_EXPRESSIONS_OPERATIONS_ARITHMATIC_PREFIXBINARY_H_
#define __MATHEMATICS_EXPRESSIONS_OPERATIONS_ARITHMATIC_PREFIXBINARY_H_
#include <Expressions/Operations/Binary.h>

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
// |                               PrefixBinary                               |
// |                                                                          |
// |__________________________________________________________________________|
class PrefixBinary : public Binary
{
public:
	PrefixBinary(const Token_t& token_in,
			Expression* left_in, 
			Expression* right_in, 
			const TokenPair_t& parentheses_in = { L"",L"" },
			const TokenPair_t& argumant_parentheses_in = { L"",L"" });
	PrefixBinary(const PrefixBinary& rhs);
	PrefixBinary(const PrefixBinary& rhs,
			const TokenPair_t& parentheses_in);
	PrefixBinary(PrefixBinary&& rhs);

	PrefixBinary& operator=(const PrefixBinary& rhs);
	PrefixBinary& operator=(PrefixBinary&& rhs);

	// Public Pure Virtual Functions of Expression Implemented.
	virtual TokenList_t infix() const override;
	virtual Expression* simplify() const override;;
	virtual Expression* derivative(const Token_t& token_in) const override;
	virtual Expression* integral(const Token_t& token_in) const override;
	virtual Real solution(const TokenValueMap_t& values_in = {}) const override;
	virtual Expression* copy(
			const TokenPair_t& parentheses_in = { L"",L"" }) const override;

	// Static Operations
	static bool is_token(const Token_t& token_in);
	static TokenPrecedence_t get_precedence(Type_t type_in, 
			const Token_t& token_in);

	virtual ~PrefixBinary() = default;

protected:
	static const ArithmaticBinaryHash_t operations;
	static const PrecedenceHash_t precedences;

private:
	static Real log(const Real& b, const Real& x);
	static Real nrt(const Real& n, const Real& x);

}; // class PrefixBinary
} // namespace Arithmatic
} // namespace Operations
} // namespace Expressions
} // namespace Mathematics

#endif // __MATHEMATICS_EXPRESSIONS_OPERATIONS_ARITHMATIC_PREFIXBINARY_H_