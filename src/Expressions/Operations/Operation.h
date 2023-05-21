// ============================================================================
//! @file Operation.h
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
#ifndef __MATHEMATICS_EXPRESSIONS_OPERATIONS_OPERATION_H_
#define __MATHEMATICS_EXPRESSIONS_OPERATIONS_OPERATION_H_
#include <Expressions/Expression.h>

namespace Mathematics
{
namespace Expressions
{
namespace Operations
{
//  __________________________________________________________________________
// |                                                                          |
// |                                                                          |
// |                                  Operation                               |
// |                                                                          |
// |__________________________________________________________________________|
class Operation : public Expression
{
public:
    Operation(const Token_t& token_in, 
            const TokenPair_t& parentheses_in = { L"",L"" },
            const TokenPair_t& argument_parentheses_in = { L"",L"" });
    Operation(const Operation& rhs);
    Operation(const Operation& rhs, 
            const TokenPair_t& parentheses_in);
    Operation(Operation&& rhs);

    Operation& operator=(const Operation& rhs);
    Operation& operator=(Operation&& rhs);

    // Implemented Pure Virtual Functions of Expression
    virtual bool is_operator() const override;
    virtual bool is_operand() const override;
    virtual bool is_separator() const override;
    virtual bool is_bracket() const override;

    virtual Natural arity() const = 0;

    static bool is_token(const Token_t& token_in);
    static TokenPrecedence_t get_precedence(Type_t type_in,
        const Token_t& token_in);

    virtual ~Operation() = default;
protected:
    inline void add_open_argument_parentheses(TokenList_t& tokens_in) const;
    inline void add_close_argument_parentheses(TokenList_t& tokens_in) const;
private:
    inline bool areguments_parenthesized() const;

    TokenPair_t							argumant_parentheses;
}; // class Operation
} // namespace Operations
} // namespace Expressions
} // namespace Mathematics


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operation                                                         |
// | Function: areguments_parenthesized                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Operation::areguments_parenthesized() const 
{
    return ((this->argumant_parentheses.first != L"") &&
        (this->argumant_parentheses.second != L""));
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operation                                                         |
// | Function: add_open_argument_parentheses                                  |
// |__________________________________________________________________________|
void Mathematics::Expressions::Operations::Operation::add_open_argument_parentheses(
        TokenList_t& tokens_in) const
{
    if (this->areguments_parenthesized())
    {
        tokens_in.push_back(this->argumant_parentheses.first);
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operation                                                         |
// | Function: add_close_argument_parentheses                                 |
// |__________________________________________________________________________|
void Mathematics::Expressions::Operations::Operation::add_close_argument_parentheses(
    TokenList_t& tokens_in) const
{
    if (this->areguments_parenthesized())
    {
        tokens_in.push_back(this->argumant_parentheses.second);
    }
}


#endif // __MATHEMATICS_EXPRESSIONS_OPERATIONS_OPERATION_H_


