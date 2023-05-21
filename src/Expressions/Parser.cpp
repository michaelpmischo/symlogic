// ============================================================================
//! @file Parser.cpp
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
#include <Expressions/Parser.h>

// Number Nodes
#include <Expressions/Operands/Variable.h>
#include <Expressions/Operands/Constant.h>
#include <Expressions/Operands/Number.h>

// Arithmatic Operations
#include <Expressions/Operations/Arithmatic/PrefixUnary.h>
#include <Expressions/Operations/Arithmatic/PostfixUnary.h>
#include <Expressions/Operations/Arithmatic/PrefixBinary.h>
#include <Expressions/Operations/Arithmatic/InfixBinary.h>

// Calculus Operations
#include <Expressions/Operations/Calculus/PrefixDerivative.h>
#include <Expressions/Operations/Calculus/PostfixDerivative.h>

// Logical Operations
#include <Expressions/Operations/Logical/InfixBinary.h>

// Separators and Spaces
#include <Expressions/Separators/Generic.h>
#include <Expressions/Separators/Brackets/Open.h>
#include <Expressions/Separators/Brackets/Close.h>

// Exceptions
#include <Exceptions/Malformed.h>

// Standard C++ STL
#include <algorithm>
#include <sstream>

//  __________________________________________________________________________
// |                                                                          |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Parser::Parser()
{
}

//  __________________________________________________________________________
// |                                                                          |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Parser::parse(
        const Token_t& token_in)
{
    // Store the expression we are about to parse.
    this->passed_expression = token_in;

    ExpressionStack_t expression_stack;
    OperatorStack_t operator_stack;

    // Tokenize the expression.
    TokenNodeList_t tokens = this->tokenize(token_in);

    for (auto token : tokens)
    {
        switch (token.type)
        {
            case Expression::Type_t::OPEN_BRACKET:
                this->process_open_bracket(expression_stack, 
                    operator_stack, 
                    token);
                break;

            case Expression::Type_t::CLOSE_BRACKET:
                this->process_close_bracket(expression_stack, 
                    operator_stack, 
                    token);
                break;

            case Expression::Type_t::SEPARATOR:
                this->process_separator(expression_stack,
                    operator_stack,
                    token);
                break;

            case Expression::Type_t::ARITHMATIC_PREFIX_UNARY:
                this->process_arithmatic_prefix_unary(expression_stack, 
                    operator_stack, 
                    token);
                break;

            case Expression::Type_t::ARITHMATIC_POSTFIX_UNARY:
                this->process_arithmatic_postfix_unary(expression_stack,
                    operator_stack, 
                    token);
                break;

            case Expression::Type_t::ARITHMATIC_PREFIX_BINARY:
                this->process_arithmatic_prefix_binary(expression_stack,
                    operator_stack,
                    token);
                break;

            case Expression::Type_t::ARITHMATIC_INFIX_BINARY:
                this->process_arithmatic_infix_binary(expression_stack,
                    operator_stack,
                    token);
                break;

            case Expression::Type_t::ARITHMATIC_POSTFIX_BINARY:
            case Expression::Type_t::ARITHMATIC_PREFIX_TERNARY:
            case Expression::Type_t::ARITHMATIC_PREINFIX_TERNARY:
            case Expression::Type_t::ARITHMATIC_POSTINFIX_TERNARY:
            case Expression::Type_t::ARITHMATIC_POSTFIX_TERNARY:
                // TODO - These are not implemented yet. When they are add the 
                // parser processing to this section. Otherwise, these are 
                // treated as variables. 
                this->process_variable(expression_stack,
                    operator_stack,
                    token);
                break;

            case Expression::Type_t::ARITHMATIC_PREFIX_SEQUENCE:
                this->process_arithmatic_prefix_sequence(expression_stack,
                    operator_stack,
                    token);
                break;

            case Expression::Type_t::CALCULUS_LIMIT:
				// TODO - These are not implemented yet. When they are add the 
                // parser processing to this section. Otherwise, these are 
                // treated as variables. 
				this->process_variable(expression_stack,
					operator_stack,
					token);
				break;

            case Expression::Type_t::CALCULUS_PREFIX_DERIVATIVE:
				this->process_calculus_prefix_derivative(expression_stack,
					operator_stack,
					token);
				break;

            case Expression::Type_t::CALCULUS_POSTFIX_DERIVATIVE:
				this->process_calculus_postfix_derivative(expression_stack,
					operator_stack,
					token);
				break;

            case Expression::Type_t::CALCULUS_IMPLICIT_DERIVATIVE:
            case Expression::Type_t::CALCULUS_DEFINITE_INTEGRAL:
            case Expression::Type_t::CALCULUS_INDEFINITE_INTEGRAL:
                // TODO - These are not implemented yet. When they are add the 
                // parser processing to this section. Otherwise, these are 
                // treated as variables. 
                this->process_variable(expression_stack,
                    operator_stack,
                    token);
                break;

            case Expression::Type_t::LOGICAL_INFIX_BINARY:
                this->process_logical_infix_binary(expression_stack,
                    operator_stack,
                    token);
                break;

            // Create a new leaf node for any operand. Then push it onto the 
            // expression output nodes stack. This includes all  constants and 
            // variables. This is everything else that we did not recognize.
            case Expression::Type_t::CONSTANT:
                this->process_constant(expression_stack,
                    operator_stack,
                    token);
                break;

            case Expression::Type_t::NUMBER:
                this->process_number(expression_stack,
                    operator_stack,
                    token);
                break;

            case Expression::Type_t::VARIABLE:
            default:
                this->process_variable(expression_stack, 
                    operator_stack, 
                    token);
                break;
        }
    }

    // Clear the stacks of the remaining expressions until there is one 
    // expression node remaining and no operators left on the stack.
    while (!operator_stack.empty())
    {
        this->handle_stacks(expression_stack, operator_stack);
    }

    // There should only be one expression on the stack. If there are
    // more then the expression is malformed.
    if (expression_stack.size() > 1U)
    {
        throw Exceptions::Malformed(
            L"Too many Operands and not enough Operators!",
            this->passed_expression,
            expression_stack.top().location);
    }

    // The top of the stack has the current root node.
    return expression_stack.top().expression;
}

//  __________________________________________________________________________
// |                                                                          |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t
Mathematics::Expressions::Parser::get_tokens(
        const Token_t& token_in) const
{
    TokenList_t tokens;
    TokenNodeList_t token_list = this->tokenize(token_in);

    for (auto token : token_list)
    {
        tokens.push_back(token.token);
    }
    return tokens;
}


//  __________________________________________________________________________
// |                                                                          |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
void Mathematics::Expressions::Parser::process_open_bracket(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const
{
    // TODO - '(' will eventually also be a binary * operator.
    operators_in.push(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
void Mathematics::Expressions::Parser::process_close_bracket(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const
{
    // Pop and process the entire stack of operators until we find the 
    // matching open bracket. If we fail to find the opposing bracket, 
    // then we will throw an error for a malformed expression.
    while ((!operators_in.empty()) && 
        (operators_in.top().token != 
            Separators::Bracket::get_opposing(token_in.token)))
    {
        this->handle_stacks(expressions_in, operators_in);
    }
    
    // Ensure that we found a closing bracket and that the expression is 
    // not malformed. If it is there will be nothing left in the operators
    // stack.
    if (operators_in.empty())
    {
        Token_t comment = L"Did you forget a matching \"" +
            Separators::Bracket::get_opposing(token_in.token) +
            L"\"?";
        throw Exceptions::Malformed(comment,
            this->passed_expression,
            token_in.location);
    }
    else
    {
        // Remove the open bracket. Then continue.
        operators_in.pop();

        // Indicate that this expression was surrounded by parentheses.
        expressions_in.top().expression->set_parentheses({
                Separators::Bracket::get_opposing(token_in.token),
                token_in.token });

    }

    // Check for any prefix operators.
    this->check_for_prefix(expressions_in, operators_in);
}

//  __________________________________________________________________________
// |                                                                          |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
void Mathematics::Expressions::Parser::process_separator(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const
{
    // Push the separator onto the operators. It is a null operator but
    // contains everything after it. Currently, we do not process these at 
    // all.
//	operators_in.push(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
void Mathematics::Expressions::Parser::process_arithmatic_prefix_unary(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const
{
    // Push this operator onto the stack and wait for the operand to 
    // complete it's sub tree.
    operators_in.push(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
void Mathematics::Expressions::Parser::process_arithmatic_post_prefix_unary(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const
{
    // Ensure that there is an operator is on the operator stack.
    if ((!operators_in.empty()) && (operators_in.top().type == 
            Expression::Type_t::ARITHMATIC_PREFIX_UNARY))
    {
        this->handle_stacks(expressions_in, operators_in);
    }
    else
    {
        TokenStream_t comment;
        comment << "Called Function: " << __FILE__ << ":" << __func__ <<
            ", Line: " << __LINE__ << std::endl <<
            "With: " << operators_in.top().token <<
            " on the top of the stack." << std::endl <<
            "And " << expressions_in.size() << " operands on the stack." <<
            std::endl;
        throw Exceptions::Malformed(comment.str(),
            this->passed_expression,
            token_in.location);
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
void Mathematics::Expressions::Parser::process_arithmatic_postfix_unary(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const
{
    if ((!expressions_in.empty()) &&
        (token_in.type == Expression::Type_t::ARITHMATIC_POSTFIX_UNARY))
    {
        // Prefix Unary operator is easy. We use the previous operand as the 
        // right node.
        operators_in.push(token_in);
        this->handle_stacks(expressions_in, operators_in);
    }
    else
    {
		TokenStream_t comment;
		comment << "Called Function: " << __FILE__ << ":" << __func__ <<
			", Line: " << __LINE__ << std::endl <<
			"With: " << operators_in.top().token <<
			" on the top of the stack." << std::endl <<
			"And " << expressions_in.size() << " operands on the stack." <<
			std::endl;
		throw Exceptions::Malformed(comment.str(),
			this->passed_expression,
			token_in.location);
    }
}

//  __________________________________________________________________________
// |                                                                          |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
void Mathematics::Expressions::Parser::process_arithmatic_prefix_binary(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const
{
    operators_in.push(token_in);
}

//  __________________________________________________________________________
// |                                                                          |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
void Mathematics::Expressions::Parser::process_arithmatic_post_prefix_binary(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const
{
    // Ensure that there is an operator is on the operator stack.
    if ((!operators_in.empty()) && (operators_in.top().type == 
        Expression::Type_t::ARITHMATIC_PREFIX_BINARY))
    {
        this->handle_stacks(expressions_in, operators_in);
    }
    else
    {
		TokenStream_t comment;
		comment << "Called Function: " << __FILE__ << ":" << __func__ <<
			", Line: " << __LINE__ << std::endl <<
			"With: " << operators_in.top().token <<
			" on the top of the stack." << std::endl <<
			"And " << expressions_in.size() << " operands on the stack." <<
			std::endl;
		throw Exceptions::Malformed(comment.str(),
			this->passed_expression,
			token_in.location);
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
void Mathematics::Expressions::Parser::process_arithmatic_infix_binary(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const
{
    // Continue popping operators off of the stack until we reach an operator
    // of an open bracket.
    while ((!operators_in.empty()) && 
        (!Separators::Brackets::Open::is_token(operators_in.top().token)) &&
        // This check is to ensure that the exponent operator has a right-
        // hand precedence. This means that the precedence of a right side 
        // exponent will not pop a left one.
        (((token_in.token != L"^") && 
            (Expression::get_precedence(operators_in.top().type, 
                operators_in.top().token) >=
                Expression::get_precedence(token_in.type, token_in.token))) || 
            ((token_in.token == L"^") && 
                (Expression::get_precedence(operators_in.top().type,
                    operators_in.top().token) >
                    Expression::get_precedence(token_in.type, token_in.token)))))
    {
        if (expressions_in.size() > 1U)
        {
            this->handle_stacks(expressions_in, operators_in);
        }
        else
        {
            Token_t comment = L"Two operands are required for operator \"" +
                token_in.token + L"\"!";
            throw Exceptions::Malformed(comment, this->passed_expression,
                token_in.location);
        }
    }

    // Check for any prefix operators.
    this->check_for_prefix(expressions_in, operators_in);

    // Push the operator onto the stack for later use.
    operators_in.push(token_in);
}



//  __________________________________________________________________________
// |                                                                          |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
void Mathematics::Expressions::Parser::process_arithmatic_prefix_sequence(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const
{
    operators_in.push(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
void Mathematics::Expressions::Parser::process_arithmatic_post_prefix_sequence(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const
{
    // Ensure that there is an operator is on the operator stack.
    if ((operators_in.size() > 3U) && (operators_in.top().type ==
        Expression::Type_t::ARITHMATIC_PREFIX_SEQUENCE))
    {
        this->handle_stacks(expressions_in, operators_in);
    }
    else
    {
		TokenStream_t comment;
		comment << "Called Function: " << __FILE__ << ":" << __func__ <<
			", Line: " << __LINE__ << std::endl <<
			"With: " << operators_in.top().token <<
			" on the top of the stack." << std::endl <<
			"And " << expressions_in.size() << " operands on the stack." <<
			std::endl;
		throw Exceptions::Malformed(comment.str(),
			this->passed_expression,
			token_in.location);
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
void Mathematics::Expressions::Parser::process_calculus_prefix_derivative(
    ExpressionStack_t& expressions_in,
    OperatorStack_t& operators_in,
    const TokenNode_t& token_in) const
{
    operators_in.push(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
void Mathematics::Expressions::Parser::process_calculus_post_prefix_derivative(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const
{
    // Ensure that there is an operator is on the operator stack.
    if ((operators_in.size() > 1U) && (operators_in.top().type ==
        Expression::Type_t::CALCULUS_PREFIX_DERIVATIVE))
    {
        this->handle_stacks(expressions_in, operators_in);
    }
    else
    {
		TokenStream_t comment;
		comment << "Called Function: " << __FILE__ << ":" << __func__ <<
			", Line: " << __LINE__ << std::endl <<
			"With: " << operators_in.top().token <<
			" on the top of the stack." << std::endl <<
			"And " << expressions_in.size() << " operands on the stack." <<
			std::endl;
		throw Exceptions::Malformed(comment.str(),
			this->passed_expression,
			token_in.location);
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
void Mathematics::Expressions::Parser::process_calculus_postfix_derivative(
    ExpressionStack_t& expressions_in,
    OperatorStack_t& operators_in,
    const TokenNode_t& token_in) const
{
	if ((expressions_in.size() > 1) &&
		(token_in.type == Expression::Type_t::ARITHMATIC_POSTFIX_UNARY))
	{
		// Prefix Derivative operator is easy. We use the previous operands 
        // as the variable and function node.
		operators_in.push(token_in);
		this->handle_stacks(expressions_in, operators_in);
	}
	else
	{
		TokenStream_t comment;
		comment << "Called Function: " << __FILE__ << ":" << __func__ <<
			", Line: " << __LINE__ << std::endl <<
			"With: " << operators_in.top().token <<
			" on the top of the stack." << std::endl <<
			"And " << expressions_in.size() << " operands on the stack." <<
			std::endl;
		throw Exceptions::Malformed(comment.str(),
			this->passed_expression,
			token_in.location);
	}
}


//  __________________________________________________________________________
// |                                                                          |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
void Mathematics::Expressions::Parser::process_logical_infix_binary(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const
{
    if (!expressions_in.empty())
    {
        // Pop and process the entire stack of operators. Period. This is the 
        // pivot point of the expression. (Remember that we added a 
        // protective "()" around the expression. Leave only that.)
        while (!operators_in.empty())
        {
            this->handle_stacks(expressions_in, operators_in);
        }

        // Throw the new tree onto the output expression stack.
        operators_in.push(token_in);
    }
    else
    {
        throw Exceptions::Malformed(
            L"Left side of the equation was not found!",
            this->passed_expression,
            token_in.location);
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
void Mathematics::Expressions::Parser::process_variable(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const
{
    // Any kind of operand goes directly to output as a leaf node.
    expressions_in.push({ new Operands::Variable(token_in.token), 
            token_in.location });
}


//  __________________________________________________________________________
// |                                                                          |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
void Mathematics::Expressions::Parser::process_constant(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const
{
    // Any kind of operand goes directly to output as a leaf node.
    expressions_in.push({ new Operands::Constant(token_in.token),
        token_in.location });
}


//  __________________________________________________________________________
// |                                                                          |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
void Mathematics::Expressions::Parser::process_number(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in,
        const TokenNode_t& token_in) const
{
    // Any kind of operand goes directly to output as a leaf node.
    expressions_in.push({ new Operands::Number(std::stold(token_in.token)),
        token_in.location });
}


//  __________________________________________________________________________
// |                                                                          |
// | Function: check_for_prefix                                               |
// |__________________________________________________________________________|
void Mathematics::Expressions::Parser::check_for_prefix(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in) const
{
    // Deal with any prefix unary operators that appeared before the open 
    // parentheses we just popped.
    if ((!operators_in.empty()) &&
        (operators_in.top().type ==
            Expression::Type_t::ARITHMATIC_PREFIX_UNARY))
    {
        this->process_arithmatic_post_prefix_unary(expressions_in,
            operators_in,
            operators_in.top());
    }

    // Deal with any prefix binary operators that appeared before the open 
    // parentheses we just popped.
    if ((!operators_in.empty()) &&
        (operators_in.top().type ==
            Expression::Type_t::ARITHMATIC_PREFIX_BINARY))
    {
        this->process_arithmatic_post_prefix_binary(expressions_in,
            operators_in,
            operators_in.top());
    }

    // Deal with any prefix sequence operators that appeared before the open 
    // parentheses we just popped.
    if ((!operators_in.empty()) &&
        (operators_in.top().type ==
            Expression::Type_t::ARITHMATIC_PREFIX_SEQUENCE))
    {
        this->process_arithmatic_post_prefix_sequence(expressions_in,
            operators_in,
            operators_in.top());
    }

    // Deal with any prefix sequence operators that appeared before the open 
    // parentheses we just popped.
    if ((!operators_in.empty()) &&
        (operators_in.top().type ==
            Expression::Type_t::CALCULUS_PREFIX_DERIVATIVE))
    {
        this->process_calculus_post_prefix_derivative(expressions_in,
            operators_in,
            operators_in.top());
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Function: handle_stacks                                                  |
// |__________________________________________________________________________|
void Mathematics::Expressions::Parser::handle_stacks(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in) const
{
    // Ensure that the top of the operator stack is actually an operator.
    // If it is not an operator then the expression is malformed. So, throw
    // an exception. Otherwise, process the operator and create new Expression 
    // nodes.
    switch (operators_in.top().type)
    {
        case Expression::Type_t::ARITHMATIC_PREFIX_UNARY:
        {
            Expression* left = expressions_in.top().expression;
            expressions_in.pop();

            // Add the new output operator to the expression node stack.
            expressions_in.push({ 
                new Operations::Arithmatic::PrefixUnary(
                    operators_in.top().token, 
                    left),
                operators_in.top().location });

            // Pop the operator off the stack.
            operators_in.pop();
            break;
        }

        case Expression::Type_t::ARITHMATIC_POSTFIX_UNARY:
        {
            Expression* left = expressions_in.top().expression;
            expressions_in.pop();

            // Add the new output operator to the expression node stack.
            expressions_in.push({ 
                new Operations::Arithmatic::PostfixUnary(
                    operators_in.top().token, 
                    left),
                operators_in.top().location });

            // Pop the operator off the stack.
            operators_in.pop();
            break;
        }

        case Expression::Type_t::ARITHMATIC_PREFIX_BINARY:
        {
            Expression* right = expressions_in.top().expression;
            expressions_in.pop();
            Expression* left = expressions_in.top().expression;
            expressions_in.pop();

            // Add the new output operator to the expression node stack.
            expressions_in.push({
                new Operations::Arithmatic::PrefixBinary(
                    operators_in.top().token,
                    left,
                    right,
                    { L"",L"" },
                    { L"(",L")" }),
                operators_in.top().location });

            // Pop the operator off the stack.
            operators_in.pop();
            break;
        }

        case Expression::Type_t::ARITHMATIC_INFIX_BINARY:
        {
            Expression* right = expressions_in.top().expression;
            expressions_in.pop();
            Expression* left = expressions_in.top().expression;
            expressions_in.pop();

            // Add the new output operator to the expression node stack.
            expressions_in.push({
                new Operations::Arithmatic::InfixBinary(
                    operators_in.top().token,
                    left,
                    right),
                operators_in.top().location });

            // Pop the operator off the stack.
            operators_in.pop();
            break;
        }

        case Expression::Type_t::ARITHMATIC_POSTFIX_BINARY:
        case Expression::Type_t::ARITHMATIC_PREFIX_TERNARY:
        case Expression::Type_t::ARITHMATIC_PREINFIX_TERNARY:
        case Expression::Type_t::ARITHMATIC_POSTINFIX_TERNARY:
        case Expression::Type_t::ARITHMATIC_POSTFIX_TERNARY:
            // Not implemented.
            break;

        case Expression::Type_t::ARITHMATIC_PREFIX_SEQUENCE:
        {
            break;
        }

        case Expression::Type_t::CALCULUS_PREFIX_DERIVATIVE:
        {
            Expression* function = expressions_in.top().expression;
            expressions_in.pop();
            Expression* variable = expressions_in.top().expression;
            expressions_in.pop();

            // Add the new output operator to the expression node stack.
            expressions_in.push({
                new Operations::Calculus::PrefixDerivative(
                    operators_in.top().token,
                    variable,
                    function),
                operators_in.top().location });

            // Pop the operator off the stack.
            operators_in.pop();
            break;
        }

        case Expression::Type_t::CALCULUS_POSTFIX_DERIVATIVE:
        {
            Expression* function = expressions_in.top().expression;
            expressions_in.pop();
            Expression* variable = expressions_in.top().expression;
            expressions_in.pop();

            // Add the new output operator to the expression node stack.
            expressions_in.push({
                new Operations::Calculus::PrefixDerivative(
                    operators_in.top().token,
                    variable,
                    function),
                operators_in.top().location });

            // Pop the operator off the stack.
            operators_in.pop();
            break;
        }
        case Expression::Type_t::CALCULUS_IMPLICIT_DERIVATIVE:
        case Expression::Type_t::CALCULUS_DEFINITE_INTEGRAL:
        case Expression::Type_t::CALCULUS_INDEFINITE_INTEGRAL:
            // Not implemented.
            break;

        case Expression::Type_t::LOGICAL_INFIX_BINARY:
        {
            Expression* right = expressions_in.top().expression;
            expressions_in.pop();
            Expression* left = expressions_in.top().expression;
            expressions_in.pop();

            // Add the new output operator to the expression node stack.
            expressions_in.push({
                new Operations::Logical::InfixBinary(
                    operators_in.top().token,
                    left, 
                    right),
                operators_in.top().location });

            // Pop the operator off the stack.
            operators_in.pop();
            break;
        }

        case Expression::Type_t::OPEN_BRACKET:
        {
            TokenStream_t comment;
            comment << L"Did you forget a matching \"" <<
                Separators::Bracket::get_opposing(operators_in.top().token) <<
                L"\" somewhere?";
            throw Exceptions::Malformed(comment.str(),
                this->passed_expression,
                operators_in.top().location);
        }

        case Expression::Type_t::CLOSE_BRACKET:
        default:
        {
            throw Exceptions::Malformed(L"Unexpected Token Found!",
                this->passed_expression,
                operators_in.top().location);
            break;
        }
    }
}

