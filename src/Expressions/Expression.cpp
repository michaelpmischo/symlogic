// ============================================================================
//! @file Expression.h
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
#include <Expressions/Expression.h>

// Operands
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

// Set Operations

// Separators
#include <Expressions/Separators/Generic.h>
#include <Expressions/Separators/Brackets/Open.h>
#include <Expressions/Separators/Brackets/Close.h>

//  __________________________________________________________________________
// |                                                                          |
// | Class: Expression                                                        |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression::Expression(
		const Token_t& token_in, 
		const TokenPair_t& parentheses_in) :
#if defined(__UTF16_EXPRESSIONS__)
	token(unicode(token_in)),
#else
	token(token_in),
#endif
	type(get_type(token_in)),
	parentheses(parentheses_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Expression                                                        |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression::Expression(Real number_in,
		const TokenPair_t& parentheses_in) :
	token(L""),
	type(Type_t::UNKNOWN),
	parentheses(parentheses_in)
{
	TokenStream_t helper;
	helper << number_in;
	this->token = helper.str();
	this->type = get_type(this->token);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Expression                                                        |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression::Expression(const Expression& rhs) :
	token(rhs.token),
	type(rhs.type),
	parentheses(rhs.parentheses)
{
}

//  __________________________________________________________________________
// |                                                                          |
// | Class: Expression                                                        |
// | Function: Move Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression::Expression(Expression&& rhs) :
	token(rhs.token),
	type(rhs.type),
	parentheses(rhs.parentheses)
{
}

//  __________________________________________________________________________
// |                                                                          |
// | Class: Expression                                                        |
// | Function: Assignment Operator                                            |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression& 
Mathematics::Expressions::Expression::operator=(const Expression& rhs)
{
	this->token			= rhs.token;
	this->type			= rhs.type;
	this->parentheses	= rhs.parentheses;
	return *this;
}

//  __________________________________________________________________________
// |                                                                          |
// | Class: Expression                                                        |
// | Function: Move Operator                                                  |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression&
Mathematics::Expressions::Expression::operator=(Expression&& rhs)
{
	this->token			= rhs.token;
	this->type			= rhs.type;
	this->parentheses	= rhs.parentheses;
	return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Function: get_type                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression::Type_t
Mathematics::Expressions::Expression::get_type(const Token_t& token_in)
{
	//////////////////     SEPARATIONS        /////////////////
	if (Separators::Brackets::Open::is_token(token_in))
	{
		return Type_t::OPEN_BRACKET;
	}
	else if (Separators::Brackets::Close::is_token(token_in))
	{
		return Type_t::CLOSE_BRACKET;
	}
	else if (Separators::Generic::is_token(token_in))
	{
		return Type_t::SEPARATOR;
	}

	//////////////////     ARTIHMATIC        /////////////////
	else if (Operations::Arithmatic::PrefixUnary::is_token(token_in))
	{
		return Type_t::ARITHMATIC_PREFIX_UNARY;
	}
	else if (Operations::Arithmatic::PostfixUnary::is_token(token_in))
	{
		return Type_t::ARITHMATIC_POSTFIX_UNARY;
	}
	else if (Operations::Arithmatic::PrefixBinary::is_token(token_in))
	{
		return Type_t::ARITHMATIC_PREFIX_BINARY;
	}
	else if (Operations::Arithmatic::InfixBinary::is_token(token_in))
	{
		return Type_t::ARITHMATIC_INFIX_BINARY;
	}

	//////////////////     CACLCULUS        /////////////////
	else if (Operations::Calculus::PrefixDerivative::is_token(token_in))
	{
		return Type_t::CALCULUS_PREFIX_DERIVATIVE;
	}
	else if (Operations::Calculus::PostfixDerivative::is_token(token_in))
	{
		return Type_t::CALCULUS_POSTFIX_DERIVATIVE;
	}

	//////////////////     LOGICAL        /////////////////
	else if (Operations::Logical::InfixBinary::is_token(token_in))
	{
		return Type_t::LOGICAL_INFIX_BINARY;
	}

	//////////////////     OPERANDS        /////////////////
	else if (Operands::Constant::is_token(token_in))
	{
		return Type_t::CONSTANT;
	}
	else if (Operands::Number::is_token(token_in))
	{
		return Type_t::NUMBER;
	}
	else if (Operands::Variable::is_token(token_in))
	{
		return Type_t::VARIABLE;
	}
	else
	{
		return Type_t::UNKNOWN;
	}
}

//  __________________________________________________________________________
// |                                                                          |
// | Class: Expression                                                        |
// | Function: print                                                          |
// |__________________________________________________________________________|
Mathematics::Expressions::Token_t 
Mathematics::Expressions::Expression::print() const
{
	TokenStream_t stream;
	this->print(stream, L"", true);
	return stream.str();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Expression                                                        |
// | Function: precedence                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenPrecedence_t 
Mathematics::Expressions::Expression::get_precedence(
		Type_t type_in,
		const Token_t& token_in)
{
	switch (type_in)
	{
		case Type_t::OPEN_BRACKET:
		case Type_t::CLOSE_BRACKET:
		case Type_t::SEPARATOR:
			return Separators::Separator::get_precedence(type_in, token_in);
			break;

		case Type_t::ARITHMATIC_PREFIX_UNARY:
		case Type_t::ARITHMATIC_POSTFIX_UNARY:
		case Type_t::ARITHMATIC_PREFIX_BINARY:
		case Type_t::ARITHMATIC_INFIX_BINARY:
		case Type_t::ARITHMATIC_POSTFIX_BINARY:
		case Type_t::ARITHMATIC_PREFIX_TERNARY:
		case Type_t::ARITHMATIC_PREINFIX_TERNARY:
		case Type_t::ARITHMATIC_POSTINFIX_TERNARY:
		case Type_t::ARITHMATIC_POSTFIX_TERNARY:
		case Type_t::ARITHMATIC_PREFIX_SEQUENCE:
		case Type_t::CALCULUS_LIMIT:
		case Type_t::CALCULUS_PREFIX_DERIVATIVE:
		case Type_t::CALCULUS_POSTFIX_DERIVATIVE:
		case Type_t::CALCULUS_IMPLICIT_DERIVATIVE:
		case Type_t::CALCULUS_DEFINITE_INTEGRAL:
		case Type_t::CALCULUS_INDEFINITE_INTEGRAL:
		case Type_t::LOGICAL_INFIX_BINARY:
			return Operations::Operation::get_precedence(type_in, token_in);
			break;

		case Type_t::CONSTANT:
		case Type_t::NUMBER:
		case Type_t::VARIABLE:
		case Type_t::UNKNOWN:
		default:
			return Operands::Operand::get_precedence(type_in, token_in);
			break;
	}
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Expression                                                        |
// | Function: operator==                                                     |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Expression::operator==(
		const Expression& rhs) const
{
	return (this->token == rhs.token) && (this->type == rhs.type);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Expression                                                        |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression::~Expression()
{
}

