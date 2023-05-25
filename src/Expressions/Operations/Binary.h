// ============================================================================
//! @file Binary.h
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
#ifndef __MATHEMATICS_EXPRESSIONS_OPERATIONS_BINARY_H_
#define __MATHEMATICS_EXPRESSIONS_OPERATIONS_BINARY_H_
#include <Expressions/Operations/Operation.h>
#include <map>

namespace Mathematics
{
namespace Expressions
{
namespace Operations
{
//  __________________________________________________________________________
// |                                                                          |
// |                                                                          |
// |                                   Binary                                 |
// |                                                                          |
// |__________________________________________________________________________|
class Binary : public Operation
{
public:
    typedef Real (*ArithmaticBinaryOperation_t)(const Real&, const Real&);
    typedef bool (*LogicalBinaryOperation_t)(const Real&, const Real&);

    typedef std::map<Token_t, ArithmaticBinaryOperation_t> 
            ArithmaticBinaryHash_t;
    typedef std::map<Token_t, LogicalBinaryOperation_t> LogicalBinaryHash_t;

    Binary(const Token_t& token_in,
            Expression* left_in, 
            Expression* right_in,
            const TokenPair_t& parentheses_in = { "","" },
            const TokenPair_t& argumant_parentheses_in = { "","" });
    Binary(const Binary& rhs);
    Binary(const Binary& rhs,
            const TokenPair_t& parentheses_in);
    Binary(Binary&& rhs);

    Binary& operator=(const Binary& rhs);
    Binary& operator=(Binary&& rhs);

    bool operator==(const Binary& rhs) const;

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

    virtual ~Binary();

	inline Expression* get_left() const;
	inline Expression* get_right() const;

protected:

    // Protected Pure Virtual Functions
    virtual void pretty_tree(std::stringstream& stream, const std::string& prefix_in, 
            bool left_in) const override;

private:
    Expression* left;
    Expression* right;
}; // class Binary
} // namespace Operations
} // namespace Expressions
} // namespace Mathematics


//  __________________________________________________________________________
// |                                                                          |
// | Class: Binary                                                            |
// | Function: get_left                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Binary::get_left() const
{
    return this->left;
}

//  __________________________________________________________________________
// |                                                                          |
// | Class: Binary                                                            |
// | Function: get_right                                                      |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Binary::get_right() const
{
    return this->right;
}

#endif // __MATHEMATICS_EXPRESSIONS_OPERATIONS_BINARY_H_