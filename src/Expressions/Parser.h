// ============================================================================
//! @file Parser.h
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
#ifndef __MATHEMATICS_EXPRESSIONS_PARSER_H_
#define __MATHEMATICS_EXPRESSIONS_PARSER_H_
#include <Expressions/Expression.h>
#include <stack>

namespace Mathematics
{
namespace Expressions
{
//  __________________________________________________________________________
// |                                                                          |
// |                                                                          |
// |                                   Parser                                 |
// |                                                                          |
// |__________________________________________________________________________|
// 
// --------------------------------- Description ------------------------------
//! @brief
// ____________________________________________________________________________
class Parser
{
public:
    Parser();
    ~Parser() = default;

    Expression* parse(const Token_t& token_in);
    TokenList_t get_tokens(const Token_t& token_in) const;

private:
    typedef struct
    {
        Token_t								token;
        Expression::Type_t					type;
        size_t								location;
    } TokenNode_t;

    typedef struct
    {
        Expression* expression;
        size_t								location;
    } ExpressionNode_t;

    // Internal Stack Types for use in the parsing algorithms
    typedef std::stack<ExpressionNode_t> ExpressionStack_t;
    typedef std::stack<TokenNode_t> OperatorStack_t;
    typedef std::list<TokenNode_t> TokenNodeList_t;

    TokenNodeList_t tokenize(const Token_t& token_in) const;
    bool complete(Expression::Type_t type_in) const;

    void process_open_bracket(ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const;

    void process_close_bracket(ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const;

    void process_separator(ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const;

    void process_arithmatic_prefix_unary(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const;

    void process_arithmatic_post_prefix_unary(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const;

    void process_arithmatic_postfix_unary(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const;

    void process_arithmatic_prefix_binary(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const;

    void process_arithmatic_post_prefix_binary(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const;

    void process_arithmatic_infix_binary(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const;

    void process_arithmatic_prefix_sequence(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const;

    void process_arithmatic_post_prefix_sequence(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const;

	void process_calculus_prefix_derivative(
		ExpressionStack_t& expressions_in,
		OperatorStack_t& operators_in,
		const TokenNode_t& token_in) const;

	void process_calculus_post_prefix_derivative(
		ExpressionStack_t& expressions_in,
		OperatorStack_t& operators_in,
		const TokenNode_t& token_in) const;

	void process_calculus_postfix_derivative(
		ExpressionStack_t& expressions_in,
		OperatorStack_t& operators_in,
		const TokenNode_t& token_in) const;

	void process_logical_infix_binary(
		ExpressionStack_t& expressions_in,
		OperatorStack_t& operators_in,
		const TokenNode_t& token_in) const;

    void process_constant(ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const;

    void process_number(ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const;

    void process_variable(ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const;

    void check_for_prefix(ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in) const;

    //! @brief Reports a malformed Exception and displays the location
    //! where the expression is malformed. (Roughly)
    void handle_stacks(ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in) const;

    //! This is the initial expression string that was passed to the 
    //! parser. This is used for reporting any errors.
    Token_t					passed_expression;
}; // class Parser
} // namespace Expressions
} // namespace Mathematics

#endif // __MATHEMATICS_PARSER_H_