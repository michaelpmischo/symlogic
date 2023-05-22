// ============================================================================
//! @file Open.h
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
#ifndef __MATHEMATICS_EXPRESSIONS_SEPARATORS_BRACKETS_OPEN_H_
#define __MATHEMATICS_EXPRESSIONS_SEPARATORS_BRACKETS_OPEN_H_
#include <Expressions/Separators/Brackets/Bracket.h>

namespace Mathematics
{
namespace Expressions
{
namespace Separators
{
namespace Brackets
{
//  __________________________________________________________________________
// |                                                                          |
// |                                                                          |
// |                                    Open                                  |
// |                                                                          |
// |__________________________________________________________________________|
// 
// --------------------------------- Description ------------------------------
//! @brief
// ____________________________________________________________________________
class Open : public Bracket
{
public:
	Open(const Token_t& token_in, Expression* inside_in);

	Open(const Open& rhs);
	Open(Open&& rhs);

	Open& operator=(const Open& rhs);
	Open& operator=(Open&& rhs);

	// Implemented Pure Virtual Functions from Expression.
	virtual TokenList_t prefix() const override;
	virtual TokenList_t infix() const override;
	virtual TokenList_t postfix() const override;
	virtual size_t size() const override;
	virtual size_t height() const override;
	virtual Expression* simplify() const override;
	virtual Expression* derivative(const Token_t& token_in) const override;
	virtual Expression* integral(const Token_t& token_in) const override;
	Real solution(const TokenValueMap_t& values_in = {}) const override;
	virtual TokenList_t get_variables() const override;
	virtual bool contains(const Token_t& token_in) const override;
	virtual bool contains_variable() const override;
	virtual Expression* copy(
			const TokenPair_t& parentheses_in = { "","" }) const override;

	static bool is_token(const Token_t& token_in);
	static TokenPrecedence_t get_precedence(Type_t type_in,
		const Token_t& token_in);
	static Token_t get_opposing(const Token_t& token_in);

	virtual ~Open();

protected:

	void print(TokenStream_t& stream, const Token_t& prefix_in, 
			bool last_in) const override;

	inline Expression* get_inside() const;

private:
	static const TokenMap_t brackets;

	Expression* inside;
}; // class Open
} // namespace Brackets
} // namespace Separators
} // namespace Expressions
} // namespace Mathematics


//  __________________________________________________________________________
// |                                                                          |
// | Class: Open                                                              |
// | Function: get_inside                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Separators::Brackets::Open::get_inside() const
{
	return this->inside;
}

#endif // __MATHEMATICS_EXPRESSIONS_SEPARATORS_BRACKETS_OPEN_H_