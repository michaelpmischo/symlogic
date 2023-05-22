// ============================================================================
//! @file Functional.h
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
#ifndef __MATHEMATICS_EXPRESSIONS_OPERATIONS_FUNCTIONAL_H_
#define __MATHEMATICS_EXPRESSIONS_OPERATIONS_FUNCTIONAL_H_
#include <Expressions/Operations/Operation.h>

namespace Mathematics
{
namespace Expressions
{
namespace Operations
{
//  _________________________________________________________________________
// |                                                                          |
// |                                                                          |
// |                                 Functional                               |
// |                                                                          |
// |__________________________________________________________________________|
class Functional : public Operation
{
public:
    Functional(const Token_t& token_in,
            Expression* function_in,
            const TokenPair_t& parentheses_in = { "","" },
            const TokenPair_t& argumant_parentheses_in = { "","" });

    Functional(const Functional& rhs);
    Functional(const Functional& rhs,
            const TokenPair_t& parentheses_in);
    Functional(Functional&& rhs);

    Functional& operator=(const Functional& rhs);
    Functional& operator=(Functional&& rhs);

    bool operator==(const Functional& rhs) const;

    // Implemented Pure Virtual Functions of Expression
    virtual TokenList_t prefix() const override;
    virtual TokenList_t postfix() const override;
    virtual size_t size() const override;
    virtual size_t height() const override;
    virtual bool contains(const Token_t& token_in) const override;
    virtual bool contains_variable() const override;
    virtual TokenList_t get_variables() const override;

    virtual Natural arity() const override;

    static bool is_token(const Token_t& token_in);
    static TokenPrecedence_t get_precedence(Type_t type_in,
            const Token_t& token_in);

    virtual ~Functional();

	inline Expression* get_function() const;

protected:

    // Protected Pure Virtual Functions
    virtual void print(TokenStream_t& stream, const Token_t& prefix_in,
            bool left_in) const override;

private:
    Expression*									function;
}; // class Functional
} // namespace Operations
} // namespace Expressions
} // namespace Mathematics


//  __________________________________________________________________________
// |                                                                          |
// | Class: Functional                                                        |
// | Function: get_function                                                   |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Functional::get_function() const
{
    return this->function;
}

#endif // __MATHEMATICS_EXPRESSIONS_OPERATIONS_FUNCTIONAL_H_