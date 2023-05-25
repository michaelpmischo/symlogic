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
#include <Exceptions/Expressions/Malformed.h>

// Standard C++ STL
#include <algorithm>
#include <sstream>

//  __________________________________________________________________________
// |                                                                          |
// | Class: Parser                                                            |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Parser::Parser()
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Parser                                                            |
// | Function: parse                                                          |
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
                this->process_variable(expression_stack, 
                    operator_stack, 
                    token);
                break;

            default:
                std::stringstream stream;
                stream << "Unknown Token: " << token.token;
                throw Malformed(stream.str(), this->passed_expression,
                    token.location);
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
        throw Malformed(
            "Too many Operands and not enough Operators!",
            this->passed_expression,
            expression_stack.top().location);
    }

    // The top of the stack has the current root node.
    return expression_stack.top().expression;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Parser                                                            |
// | Function: get_tokens                                                     |
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
// | Class: Parser                                                            |
// | Function: tokenize                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Parser::TokenNodeList_t 
Mathematics::Expressions::Parser::tokenize(
        const Token_t& token_in) const
{
    TokenNodeList_t tokens;
    Token_t collector;
    for (size_t character_location = 0U; 
        character_location < token_in.length(); 
        character_location++)
    {
        Token_t character = token_in.substr(character_location, 1);

        // Check the token and see if it means anything. If it does
        // then add it to the token list for output and clear the 
        // token collector.
        Expression::Type_t collector_type = Expression::get_type(collector);
        size_t collector_location = character_location - collector.length();
        if (this->complete(collector_type))
        {
            tokens.push_back({ collector, 
                collector_type, 
                collector_location });
            collector.clear();
        }

        // Now deal with the current character. Many tokens are single
        // character expressions. We need to handle them here.
         Expression::Type_t character_type = Expression::get_type(character);
        if (this->complete(character_type))
        {
            if (!collector.empty())
            {
				tokens.push_back({ collector, 
                    collector_type, 
                    collector_location });
                collector.clear();
            }
            tokens.push_back({ character, 
                character_type, 
                character_location });
        }
        else
        {
            collector.append(character);
        }

        // Get the last token if there is one and we are at the expression.
        if (!collector.empty() && ((character_location + 1) >= token_in.length()))
        {
            collector_type = Expression::get_type(collector);
			tokens.push_back({ collector,
	            collector_type,
	            collector_location });
			    collector.clear();
        }
    }

    return tokens;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Parser                                                            |
// | Function: handle_token                                                   |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Parser::complete(Expression::Type_t type_in) const
{
	switch (type_in)
	{
        case Expression::Type_t::OPEN_BRACKET:
	    case Expression::Type_t::CLOSE_BRACKET:
	    case Expression::Type_t::SEPARATOR:
	    case Expression::Type_t::ARITHMATIC_PREFIX_UNARY:
	    case Expression::Type_t::ARITHMATIC_POSTFIX_UNARY:
	    case Expression::Type_t::ARITHMATIC_PREFIX_BINARY:
	    case Expression::Type_t::ARITHMATIC_INFIX_BINARY:
	    case Expression::Type_t::ARITHMATIC_POSTFIX_BINARY:
	    case Expression::Type_t::ARITHMATIC_PREFIX_TERNARY:
	    case Expression::Type_t::ARITHMATIC_PREINFIX_TERNARY:
	    case Expression::Type_t::ARITHMATIC_POSTINFIX_TERNARY:
	    case Expression::Type_t::ARITHMATIC_POSTFIX_TERNARY:
	    case Expression::Type_t::ARITHMATIC_PREFIX_SEQUENCE:
	    case Expression::Type_t::CALCULUS_LIMIT:
	    case Expression::Type_t::CALCULUS_PREFIX_DERIVATIVE:
	    case Expression::Type_t::CALCULUS_POSTFIX_DERIVATIVE:
	    case Expression::Type_t::CALCULUS_IMPLICIT_DERIVATIVE:
	    case Expression::Type_t::CALCULUS_DEFINITE_INTEGRAL:
	    case Expression::Type_t::CALCULUS_INDEFINITE_INTEGRAL:
	    case Expression::Type_t::LOGICAL_INFIX_BINARY:
            return true;

	    case Expression::Type_t::CONSTANT:
	    case Expression::Type_t::NUMBER:
	    case Expression::Type_t::VARIABLE:
	    case Expression::Type_t::UNKNOWN:
        default:
            return false;
	}
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Parser                                                            |
// | Function: process_open_bracket                                           |
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
// | Class: Parser                                                            |
// | Function: process_close_bracket                                          |
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
        Token_t comment = "Did you forget a matching \"" +
            Separators::Bracket::get_opposing(token_in.token) +
            "\"?";
        throw Malformed(comment,
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
// | Class: Parser                                                            |
// | Function: process_separator                                              |
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
// | Class: Parser                                                            |
// | Function: process_arithmatic_prefix_unary                                |
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
// | Class: Parser                                                            |
// | Function: process_arithmatic_post_prefix_unary                           |
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
        throw Malformed(comment.str(),
            this->passed_expression,
            token_in.location);
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Parser                                                            |
// | Function: process_arithmatic_postfix_unary                               |
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
		throw Malformed(comment.str(),
			this->passed_expression,
			token_in.location);
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Parser                                                            |
// | Function: process_arithmatic_prefix_binary                               |
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
// | Class: Parser                                                            |
// | Function: process_arithmatic_post_prefix_binary                          |
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
		throw Malformed(comment.str(),
			this->passed_expression,
			token_in.location);
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Parser                                                            |
// | Function: process_arithmatic_infix_binary                                |
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
        (((token_in.token != "^") && 
            (Expression::get_precedence(operators_in.top().type, 
                operators_in.top().token) >=
                Expression::get_precedence(token_in.type, token_in.token))) || 
            ((token_in.token == "^") && 
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
            Token_t comment = "Two operands are required for operator \"" +
                token_in.token + "\"!";
            throw Malformed(comment, this->passed_expression,
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
// | Class: Parser                                                            |
// | Function: process_arithmatic_prefix_sequence                             |
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
// | Class: Parser                                                            |
// | Function: process_arithmatic_post_prefix_sequence                        |
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
		throw Malformed(comment.str(),
			this->passed_expression,
			token_in.location);
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Parser                                                            |
// | Function: process_calculus_prefix_derivative                             |
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
// | Class: Parser                                                            |
// | Function: process_calculus_post_prefix_derivative                        |
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
		throw Malformed(comment.str(),
			this->passed_expression,
			token_in.location);
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Parser                                                            |
// | Function: process_calculus_postfix_derivative                            |
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
		throw Malformed(comment.str(),
			this->passed_expression,
			token_in.location);
	}
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Parser                                                            |
// | Function: process_logical_infix_binary                                   |
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
        throw Malformed(
            "Left side of the equation was not found!",
            this->passed_expression,
            token_in.location);
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Parser                                                            |
// | Function: process_variable                                               |
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
// | Class: Parser                                                            |
// | Function: process_constant                                               |
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
// | Class: Parser                                                            |
// | Function: process_number                                                 |
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
// | Class: Parser                                                            |
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
// | Class: Parser                                                            |
// | Function: handle_stacks                                                  |
// |__________________________________________________________________________|
void Mathematics::Expressions::Parser::handle_stacks(
        ExpressionStack_t& expressions_in,
        OperatorStack_t& operators_in) const
{
    bool error = false;
    // Ensure that the top of the operator stack is actually an operator.
    // If it is not an operator then the expression is malformed. So, throw
    // an exception. Otherwise, process the operator and create new Expression 
    // nodes.
    switch (operators_in.top().type)
    {
        case Expression::Type_t::ARITHMATIC_PREFIX_UNARY:
        {
            if (expressions_in.size() > 0)
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
            }
            else
            {
				// Malformed ...
				error = true;
            }

            break;
        }

        case Expression::Type_t::ARITHMATIC_POSTFIX_UNARY:
        {
            if (expressions_in.size() > 0)
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
            }
            else
            {
				// Malformed ...
				error = true;
            }
            break;
        }

        case Expression::Type_t::ARITHMATIC_PREFIX_BINARY:
        {
            if (expressions_in.size() > 1)
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
                        { "","" },
                        { "(",")" }),
                    operators_in.top().location });

                // Pop the operator off the stack.
                operators_in.pop();
            }
            else
            {
                // Malformed ...
                error = true;
            }
            break;
        }

        case Expression::Type_t::ARITHMATIC_INFIX_BINARY:
        {
            if (expressions_in.size() > 1)
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
            }
            else
            {
				// Malformed ...
				error = true;
            }
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
            if (expressions_in.size() > 1)
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
            }
            else
            {
				// Malformed ...
				error = true;
            }
            break;
        }

        case Expression::Type_t::CALCULUS_POSTFIX_DERIVATIVE:
        {
            if (expressions_in.size() > 1)
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
            }
            else
            {
				// Malformed ...
				error = true;
            }
            break;
        }
        case Expression::Type_t::CALCULUS_IMPLICIT_DERIVATIVE:
        case Expression::Type_t::CALCULUS_DEFINITE_INTEGRAL:
        case Expression::Type_t::CALCULUS_INDEFINITE_INTEGRAL:
            // Not implemented.
            break;

        case Expression::Type_t::LOGICAL_INFIX_BINARY:
        {
            if (expressions_in.size() > 1)
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
            }
            else
            {
				// Malformed ...
				error = true;
            }
            break;
        }

        case Expression::Type_t::OPEN_BRACKET:
        {
            TokenStream_t comment;
            comment << "Did you forget a matching \"" <<
                Separators::Bracket::get_opposing(operators_in.top().token) <<
                "\" somewhere?";
            throw Malformed(comment.str(),
                this->passed_expression,
                operators_in.top().location);
        }

        case Expression::Type_t::CLOSE_BRACKET:
        default:
        {
            throw Malformed("Unexpected Token Found!",
                this->passed_expression,
                operators_in.top().location);
            break;
        }
    }
    if (error)
    {
		TokenStream_t stream;
		stream << "Operator: " << operators_in.top().token <<
			" Does not have enough Operands.";
		throw Malformed(stream.str(), this->passed_expression,
			operators_in.top().location);
    }
}

