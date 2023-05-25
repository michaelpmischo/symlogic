// ============================================================================
//! @file Unary.h
//! @author Michael P. MIscho
//! @date May 11, 2023
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
#ifndef __MATHEMATICS_EXPRESSIONS_OPERATIONS_UNARY_H_
#define __MATHEMATICS_EXPRESSIONS_OPERATIONS_UNARY_H_
#include <Expressions/Operations/Operation.h>

namespace Mathematics
{
namespace Expressions
{
namespace Operations
{
//  __________________________________________________________________________
// |                                                                          |
// |                                                                          |
// |                                    Unary                                 |
// |                                                                          |
// |__________________________________________________________________________|
class Unary : public Operation
{
public:
    typedef Real(*ArithmaticUnaryOperation_t)(const Real&);
    typedef bool (*LogicalUnaryOperation_t)(const Real&);

    typedef std::map<Token_t, ArithmaticUnaryOperation_t> 
            ArithmaticUnaryHash_t;
    typedef std::map<Token_t, LogicalUnaryOperation_t> LogicalUnaryHash_t;

    Unary(const Token_t& token_in,
            Expression* operand_in,
            const TokenPair_t& parentheses_in = { "","" },
            const TokenPair_t& argumant_parentheses_in = { "","" });

    Unary(const Unary& rhs);
    Unary(const Unary& rhs,
            const TokenPair_t& parentheses_in);
    Unary(Unary&& rhs);

    Unary& operator=(const Unary& rhs);
    Unary& operator=(Unary&& rhs);

    bool operator==(const Unary& rhs) const;

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

    virtual ~Unary();

    inline Expression* get_left() const;

protected:

    // Private Pure Virtual Functions
    virtual void pretty_tree(std::stringstream& stream, const std::string& prefix_in,
            bool left_in) const override;

private:
    Expression*										left;
}; // class Unary
} // namespace Operations
} // namespace Expressions
} // namespace Mathematics

//  __________________________________________________________________________
// |                                                                          |
// | Class: Unary                                                             |
// | Function: get_operand                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Unary::get_left() const
{
    return this->left;
}

#endif // __MATHEMATICS_EXPRESSIONS_OPERATIONS_UNARY_H_