// ============================================================================
//! @file ExpressionHandler.h
//! @author Michael P. MIscho
//! @date May 22, 2023
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
#ifndef __MATHEMATICS_UI_CORE_EXPRESSIONHANDLER_H_
#define __MATHEMATICS_UI_CORE_EXPRESSIONHANDLER_H_
#include <Expressions/Parser.h>
#include <Expressions/Tokens.h>
#include <deque>

namespace Mathematics
{
namespace Expressions
{
class Expression;
}
namespace UI
{
namespace Core
{
//  __________________________________________________________________________
// |                                                                          |
// |                                                                          |
// |                             ExpressionHandler                            |
// |                                                                          |
// |__________________________________________________________________________|
// 
// --------------------------------- Description ------------------------------
//! @brief
// ____________________________________________________________________________
class ExpressionHandler
{
public:
	static ExpressionHandler* instance();

	void handle(const std::string& raw_expression_in);

	void add(const Expressions::Token_t& variable_in, 
		const Expressions::Token_t& value_in);
	void remove(const Expressions::Token_t& variable_in);
	void remove(size_t index_in);
	void solve(size_t index_in) const;
	void list() const;
	void clear();
	~ExpressionHandler() = default;

private:
	ExpressionHandler() = default;

	Expressions::Parser						parser;
	std::deque<Expressions::Expression*>	expressions;
	Expressions::TokenValueMap_t			variables;

	static ExpressionHandler* singleton;
}; // class ExpressionHandler
} // namespace Core
} // namespace UI
} // namespace Mathematics

#endif // __MATHEMATICS_UI_CORE_EXPRESSIONHANDLER_H_