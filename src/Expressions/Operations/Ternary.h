// ============================================================================
//! @file Ternary.h
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
#ifndef __MATHEMATICS_EXPRESSIONS_OPERATIONS_TERNARY_H_
#define __MATHEMATICS_EXPRESSIONS_OPERATIONS_TERNARY_H_
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
// |                                   Ternary                                |
// |                                                                          |
// |__________________________________________________________________________|
class Ternary : public Operation
{
public:
    typedef Real (*ArithmaticTernaryOperation_t)(const Real&, 
            const Real&, 
            const Real&);
    typedef bool (*LogicalTernaryOperation_t)(const Real&, 
            const Real&, 
            const Real&);

    typedef std::map<Token_t, ArithmaticTernaryOperation_t> 
            ArithmaticTernaryHash_t;
    typedef std::map<Token_t, LogicalTernaryOperation_t> 
            LogicalTernaryHash_t;

    Ternary(const Token_t& token_in,
            Expression* left_in,
            Expression* middle_in,
            Expression* right_in,
            const TokenPair_t& parentheses_in = { L"",L"" },
            const TokenPair_t& argumant_parentheses_in = { L"",L"" });

    Ternary(const Ternary& rhs);
    Ternary(const Ternary& rhs,
            const TokenPair_t& parentheses_in);
    Ternary(Ternary&& rhs);

    Ternary& operator=(const Ternary& rhs);
    Ternary& operator=(Ternary&& rhs);

    bool operator==(const Ternary& rhs) const;

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

    virtual ~Ternary();

	inline Expression* get_left() const;
	inline Expression* get_middle() const;
	inline Expression* get_right() const;

protected:

    // Protected Pure Virtual Functions
    virtual void print(TokenStream_t& stream, const Token_t& prefix_in, 
            bool left_in) const override;

private:
    Expression* left;
    Expression* middle;
    Expression* right;
}; // class Ternary
} // namespace Operations
} // namespace Expressions
} // namespace Mathematics


//  __________________________________________________________________________
// |                                                                          |
// | Class: Ternary                                                           |
// | Function: get_left                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Ternary::get_left() const
{
    return this->left;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Ternary                                                           |
// | Function: get_middle                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Ternary::get_middle() const
{
    return this->middle;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Ternary                                                           |
// | Function: get_right                                                      |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Ternary::get_right() const
{
    return this->right;
}

#endif // __MATHEMATICS_EXPRESSIONS_OPERATIONS_TERNARY_H_