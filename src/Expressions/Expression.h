// ============================================================================
//! @file Expression.h
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
#ifndef __MATHEMATICS_EXPRESSIONS_EXPRESSION_H_
#define __MATHEMATICS_EXPRESSIONS_EXPRESSION_H_
#include <Expressions/Tokens.h>
#include <deque>

namespace Mathematics
{
namespace Expressions
{
//  __________________________________________________________________________
// |                                                                          |
// |                                                                          |
// |                                 Expression                               |
// |                                                                          |
// |__________________________________________________________________________|
// 
// --------------------------------- Description ------------------------------
//! @brief
// ____________________________________________________________________________
class Expression
{
public:
    typedef std::deque<Expression*> ExpressionList_t;
    enum : TokenPrecedence_t
    {
        MIN_PRECEDENCE = 0U,
        MAX_PRECEDENCE = static_cast<TokenPrecedence_t>(-1),
    };

    //! This is all the known classifications of the expression types 
    //! found in the ASCII/Unicode mathematical expressions.
    enum class Type_t
    {
        //! Separator Types.
        OPEN_BRACKET,
        CLOSE_BRACKET,
        SEPARATOR,

        //! Arithmatic Operator Types:
        ARITHMATIC_PREFIX_UNARY,
        ARITHMATIC_POSTFIX_UNARY,
        ARITHMATIC_PREFIX_BINARY,
        ARITHMATIC_INFIX_BINARY,
        ARITHMATIC_POSTFIX_BINARY,              // Unimplemented
        ARITHMATIC_PREFIX_TERNARY,              // Unimplemented
        ARITHMATIC_PREINFIX_TERNARY,            // Unimplemented
        ARITHMATIC_POSTINFIX_TERNARY,           // Unimplemented
        ARITHMATIC_POSTFIX_TERNARY,             // Unimplemented
        ARITHMATIC_PREFIX_SEQUENCE,             // Unimplemented

        //! Calculus Operator Types
        CALCULUS_LIMIT,                         // Unimplemented
        CALCULUS_PREFIX_DERIVATIVE,
        CALCULUS_POSTFIX_DERIVATIVE,
        CALCULUS_IMPLICIT_DERIVATIVE,           // Unimplemented
        CALCULUS_DEFINITE_INTEGRAL,             // Unimplemented
        CALCULUS_INDEFINITE_INTEGRAL,           // Unimplemented


        //! Logical Operator Types
        LOGICAL_PREFIX_UNARY,                   // Unimplemented
        LOGICAL_INFIX_BINARY,

        //! Operand Types:
        NUMBER,
        CONSTANT,
        VARIABLE,
        SET,

        // Unknown Type, currently we default to a 
        // variable type. So, we should not encounter this
        // in use.
        UNKNOWN,
    };

    Expression(const Token_t& token_in, 
            const TokenPair_t& parentheses_in = { "","" });
    Expression(Real number_in, 
            const TokenPair_t& parentheses_in = { "","" });
    Expression(const Expression& token_in);
    Expression(Expression&& token_in);

    Expression& operator=(const Expression& token_in);
    Expression& operator=(Expression&& token_in);

    // Public Operators
    bool operator!=(const Expression& token_in) const;
    bool operator==(const Expression& token_in) const;

    std::string pretty_tree() const;

    // Public Pure Virtual Functions

    // Basic Tree Operations.
    virtual TokenList_t prefix() const = 0;
    virtual TokenList_t infix() const = 0;
    virtual TokenList_t postfix() const = 0;
    virtual size_t size() const = 0;
    virtual size_t height() const = 0;

    // Mathematics Expression Operations
    virtual Expression* simplify() const = 0;
    virtual Expression* derivative(const Token_t& token_in) const = 0;
    virtual Expression* integral(const Token_t& token_in) const = 0;
    virtual Real solution(const TokenValueMap_t& values_in = {}) const = 0;
    virtual TokenList_t get_variables() const = 0;

    // Node Status Operations
    virtual bool is_operator() const = 0;
    virtual bool is_operand() const = 0;
    virtual bool is_separator() const = 0;
    virtual bool is_bracket() const = 0;

    // Tree Status Operations
    virtual bool contains_variable() const = 0;
    virtual bool contains(const Token_t& token_in) const = 0;

    // Management Operations
    virtual Expression* copy(
            const TokenPair_t& parentheses_in = { "","" }) const = 0;
    virtual ExpressionList_t get_branches() const = 0;

    // This should be protected but because this is a tree the inherited
    // node types cannot call this function on a cousin instance of a
    // child class. So, it is declared public here. Terrible...
    virtual void pretty_tree(
            std::stringstream& stream, 
            const std::string& prefix_in, 
            bool is_last) const = 0;

    // Getters.
    inline Token_t get_token() const;
    inline Type_t get_type() const;

    // Status
    inline bool is_type(Type_t type_in) const;

    // Setters
    inline void set_parentheses(const TokenPair_t& parentheses_in);

    // Static Functions
    static Type_t get_type(const Token_t& token_in);

    // Fetch the precedence of this expressions token in order of operations.
    static TokenPrecedence_t get_precedence(Type_t tpe_in, 
            const Token_t& token_in);

    friend TokenOutputStream_t& operator<<(TokenOutputStream_t& stream,
        const Expression& rhs)
    {
        stream << rhs.get_token();
        return stream;
    }

    friend TokenInputStream_t& operator<<(TokenInputStream_t& stream,
        Expression& rhs)
    {
        stream >> rhs.token;
        rhs.type = Expression::get_type(rhs.token);
        return stream;
    }

    virtual ~Expression();

protected:
    inline std::wstring get_wtoken() const;
    inline void add_open_parentheses(TokenList_t& tokens_in) const;
    inline void add_close_parentheses(TokenList_t& tokens_in) const;

private:
    inline bool parenthesized() const;

    Token_t                         token;
    Type_t                          type;

    // If this expression is wrapped in parentheses or other separator
    // this is where they are stored.
    TokenPair_t                     parentheses;
}; // class Expression
} // namespace Expressions
} // namespace Mathematics


//  __________________________________________________________________________
// |                                                                          |
// | Class: Expression                                                        |
// | Function: get_token                                                      |
// |__________________________________________________________________________|
Mathematics::Expressions::Token_t 
Mathematics::Expressions::Expression::get_token() const
{
    return this->token;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Expression                                                        |
// | Function: get_token                                                      |
// |__________________________________________________________________________|
std::wstring Mathematics::Expressions::Expression::get_wtoken() const
{
    std::wstring out;
    WConverter_t                    wide_converter;
#if defined(__WCHAR_EXPRESSIONS__) || \
    defined(__UTF16_EXPRESSIONS__) || \
    defined(__UTF32_EXPRESSIONS__)
    out = std::wstring(reinterpret_cast<wchar_t*>(this->token.c_str()));
#else
    out = wide_converter.from_bytes(this->token);
#endif
    
return out;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Expression                                                        |
// | Function: get_type                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression::Type_t 
Mathematics::Expressions::Expression::get_type() const
{
    return this->type;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Expression                                                        |
// | Function: set_parentheses                                                |
// |__________________________________________________________________________|
void Mathematics::Expressions::Expression::set_parentheses(
        const TokenPair_t& parentheses_in)
{
    this->parentheses = parentheses_in;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Expression                                                        |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Expression::is_type(Type_t type_in) const
{
    return (this->type == type_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Expression                                                        |
// | Function: parenthesized                                                  |
// |__________________________________________________________________________|
void Mathematics::Expressions::Expression::add_open_parentheses(
        TokenList_t& tokens_in) const
{
    if (this->parenthesized())
    {
        tokens_in.push_back(this->parentheses.first);
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Expression                                                        |
// | Function: parenthesized                                                  |
// |__________________________________________________________________________|
void Mathematics::Expressions::Expression::add_close_parentheses(
        TokenList_t& tokens_in) const
{
    if (this->parenthesized())
    {
        tokens_in.push_back(this->parentheses.second);
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Expression                                                        |
// | Function: parenthesized                                                  |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Expression::parenthesized() const
{
    return ((this->parentheses.first != "") &&
        (this->parentheses.second != ""));
}


#endif // __MATHEMATICS_EXPRESSIONS_EXPRESSION_H_

