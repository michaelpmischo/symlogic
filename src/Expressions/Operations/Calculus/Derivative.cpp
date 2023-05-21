// ============================================================================
//! @file Derivative.cpp
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
#include <Expressions/Operations/Calculus/Derivative.h>
#include <Expressions/Operations/Calculus/PrefixDerivative.h>
#include <Expressions/Operations/Calculus/PostfixDerivative.h>

// For Common Derivatives
#include <Expressions/Operands/Number.h>
#include <Expressions/Operations/Unary.h>
#include <Expressions/Operations/Binary.h>
#include <Expressions/Operations/Ternary.h>
#include <Expressions/Operations/Functional.h>
#include <Expressions/Operations/Arithmatic/PrefixUnary.h>
#include <Expressions/Operations/Arithmatic/InfixBinary.h>


const Mathematics::Expressions::Operations::Calculus::Derivative::UnaryDerivativeHash_t
Mathematics::Expressions::Operations::Calculus::Derivative::unary_common =
{
// Unary Operations
	{L"ln",		&Derivative::ln},
//	{L"sqrt",	&Derivative::sqrt},
	{L"exp",	&Derivative::exp},
//	{L"abs",	&Derivative::abs},

	// Trigonometric Operations
	{L"sin",	&Derivative::sin},
	{L"cos",	&Derivative::cos},
	{L"tan",	&Derivative::tan},
//	{L"csc",	&Derivative::csc},
//	{L"sec",	&Derivative::sec},
//	{L"cot",	&Derivative::cot},

//	{L"asin",	&Derivative::asin},
//	{L"acos",	&Derivative::acos},
//	{L"atan",	&Derivative::atan},
//	{L"acsc",	&Derivative::acsc},
//	{L"asec",	&Derivative::asec},
//	{L"acot",	Derivative::acot},

//	{L"sinh",	&Derivative::sinh},
//	{L"cosh",	&Derivative::cosh},
//	{L"tanh",	&Derivative::tanh},
//	{L"csch",	&Derivative::csch},
//	{L"sech",	&Derivative::sech},
//	{L"coth",	&Derivative::coth},
//	{L"asinh",	&Derivative::asinh},
//	{L"acosh",	&Derivative::acosh},
//	{L"atanh",	&Derivative::atanh},
//	{L"acsch",	&Derivative::acsch},
//	{L"asech",	&Derivative::asech},
//	{L"acoth",	&Derivative::acoth},

#if defined(__UTF16_EXPRESSIONS__) || \
    defined(__WCHAR_EXPRESSIONS__) || \
    defined(__UTF32_EXPRESSIONS__)
//	{L"√",		&Derivative::sqrt},
//	{L"ℯ^",		&Derivative::exp},
#endif
};

const Mathematics::Expressions::Operations::Calculus::Derivative::BinaryDerivativeHash_t
Mathematics::Expressions::Operations::Calculus::Derivative::binary_common =
{
	// Binary Operations
	{L"^",		&Derivative::power_rule},
	{L"*",		&Derivative::product_rule},
	{L"/",		&Derivative::quotient_rule},
	{L"+",		&Derivative::sum_and_difference},
	{L"-",		&Derivative::sum_and_difference},

//	{L"log",	&Derivative::log},
//	{L"nrt",	&Derivative::nrt},

#if defined(__UTF16_EXPRESSIONS__) || \
    defined(__WCHAR_EXPRESSIONS__) || \
    defined(__UTF32_EXPRESSIONS__)
	{L"∙",		&Derivative::product_rule},
	{L"⨉",		&Derivative::product_rule},
	{L"÷",		&Derivative::quotient_rule},
//	{L"n√",		&Derivative::nrt},
#endif
};

const Mathematics::Expressions::Operations::Calculus::Derivative::TernaryDerivativeHash_t
Mathematics::Expressions::Operations::Calculus::Derivative::ternary_common =
{
	// Empty.
};

const Mathematics::Expressions::Operations::Calculus::Derivative::FunctionalDerivativeHash_t
Mathematics::Expressions::Operations::Calculus::Derivative::functional_common =
{
	// Empty.
};

//  __________________________________________________________________________
// |                                                                          |
// | Class: Derivative                                                        |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Calculus::Derivative::Derivative(
        const Token_t& token_in, 
        Expression* variable_in,
        Expression* function_in, 
        const TokenPair_t& parentheses_in,
        const TokenPair_t& argument_parentheses_in) :
    Functional(token_in, function_in, parentheses_in, argument_parentheses_in),
    variable(variable_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Derivative                                                        |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Calculus::Derivative::Derivative(
        const Derivative& rhs) :
    Functional(rhs),
    variable(rhs.variable->copy())
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Derivative                                                        |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Calculus::Derivative::Derivative(
        const Derivative& rhs, 
        const TokenPair_t& parentheses_in) :
    Functional(rhs, parentheses_in),
    variable(rhs.variable->copy())
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Derivative                                                        |
// | Function: Move Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Calculus::Derivative::Derivative(
        Derivative&& rhs) :
    Functional(rhs),
    variable(rhs.variable->copy())
{
    delete rhs.variable;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Derivative                                                        |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Calculus::Derivative&
Mathematics::Expressions::Operations::Calculus::Derivative::operator=(
        const Derivative& rhs)
{
    Functional::operator=(rhs);
    this->variable = rhs.variable->copy();
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Derivative                                                        |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Calculus::Derivative&
Mathematics::Expressions::Operations::Calculus::Derivative::operator=(
        Derivative&& rhs)
{
    Functional::operator=(rhs);
    this->variable = rhs.variable->copy();
    delete rhs.variable;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Derivative                                                        |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Calculus::Derivative::is_token(
        const Token_t& token_in)
{
    return Calculus::PrefixDerivative::is_token(token_in) || 
			Calculus::PostfixDerivative::is_token(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Derivative                                                        |
// | Function: get_precedence                                                 |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenPrecedence_t 
Mathematics::Expressions::Operations::Calculus::Derivative::get_precedence(
        Type_t type_in, 
        const Token_t& token_in)
{
    return MAX_PRECEDENCE;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Derivative                                                        |
// | Function: is_common                                                      |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Calculus::Derivative::is_common(
	const Token_t& token_in)
{
	return ((unary_common.find(token_in) != unary_common.end()) ||
		(binary_common.find(token_in) != binary_common.end()) ||
		(ternary_common.find(token_in) != ternary_common.end()));
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Derivative                                                        |
// | Function: get_common                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operations::Calculus::Derivative::get_common(
	const Token_t& token_in,
	const Unary* expression_in)
{
	const UnaryDerivativeHash_t::const_iterator iter = unary_common.find(
			expression_in->get_token());
	if (iter != unary_common.end())
	{
		return iter->second(
			token_in,
			expression_in);
	}
	else
	{
		// Maybe do something here. But, not yet.
		return expression_in->copy();
	}
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Derivative                                                        |
// | Function: get_common                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operations::Calculus::Derivative::get_common(
	const Token_t& token_in,
	const Binary* expression_in)
{
	const BinaryDerivativeHash_t::const_iterator iter = binary_common.find(
		expression_in->get_token());
	if (iter != binary_common.end())
	{
		return iter->second(
			token_in,
			expression_in);
	}
	else
	{
		// Maybe do something here. But, not yet.
		return expression_in->copy();
	}
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Derivative                                                        |
// | Function: get_common                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operations::Calculus::Derivative::get_common(
	const Token_t& token_in,
	const Ternary* expression_in)
{
	const TernaryDerivativeHash_t::const_iterator iter = ternary_common.find(
		expression_in->get_token());
	if (iter != ternary_common.end())
	{
		return iter->second(
			token_in,
			expression_in);
	}
	else
	{
		// Maybe do something here. But, not yet.
		return expression_in->copy();
	}
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Derivative                                                        |
// | Function: get_common                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operations::Calculus::Derivative::get_common(
		const Token_t& token_in,
		const Functional* expression_in)
{
	const FunctionalDerivativeHash_t::const_iterator iter = 
			functional_common.find(expression_in->get_token());
	if (iter != functional_common.end())
	{
		return iter->second(
			token_in,
			expression_in);
	}
	else
	{
		// Maybe do something here. But, not yet.
		return expression_in->copy();
	}
}



//  __________________________________________________________________________
// |                                                                          |
// | Class: Derivative                                                        |
// | Function: ln                                                             |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operations::Calculus::Derivative::ln(
	const Token_t& token_in,
	const Unary* expression_in)
{
	if (expression_in->contains_variable())
	{
		return new Arithmatic::InfixBinary(L"*",
			new Arithmatic::InfixBinary(L"/",
				new Operands::Number(1),
				expression_in->get_left()->copy({ L"(",L")" })),
			// Chain Rule
			expression_in->get_left()->derivative(token_in));
	}
	else
	{
		return new Operands::Number(0);
		}
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Derivative                                                        |
// | Function: exp                                                            |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operations::Calculus::Derivative::exp(
	const Token_t& token_in,
	const Unary* expression_in)
{
	if (expression_in->contains_variable())
	{
		return new Arithmatic::InfixBinary(L"*",
			new Arithmatic::PrefixUnary(L"exp",
				expression_in->get_left()->copy({ L"(", L")" })),
			// Chain Rule
			expression_in->get_left()->derivative(token_in));
	}
	else
	{
		return new Operands::Number(0);
	}
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Derivative                                                        |
// | Function: sin                                                            |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operations::Calculus::Derivative::sin(
	const Token_t& token_in,
	const Unary* expression_in)
{
	if (expression_in->contains_variable())
	{
		return new Arithmatic::InfixBinary(L"*",
			new Arithmatic::PrefixUnary(L"cos",
				expression_in->get_left()->copy({ L"(",L")" })),
			// Chain Rule...
			expression_in->get_left()->derivative(token_in));
	}
	else
	{
		return new Operands::Number(0);
		}
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Derivative                                                        |
// | Function: cos                                                            |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operations::Calculus::Derivative::cos(
	const Token_t& token_in,
	const Unary* expression_in)
{
	if (expression_in->contains_variable())
	{
		return new Arithmatic::PrefixUnary(L"~",
			new Arithmatic::InfixBinary(L"*",
				// Chain Rule...
				new Arithmatic::PrefixUnary(L"sin",
					expression_in->get_left()->copy({ L"(",L")" })),
				// Chain Rule...
				expression_in->get_left()->derivative(token_in)));
	}
	else
	{
		return new Operands::Number(0);
	}
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Derivative                                                        |
// | Function: tan                                                            |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operations::Calculus::Derivative::tan(
	const Token_t& token_in,
	const Unary* expression_in)
{
	if (expression_in->contains_variable())
	{
		return new Arithmatic::InfixBinary(L"*",
			new Arithmatic::InfixBinary(L"^",
				new Arithmatic::PrefixUnary(L"sec",
					expression_in->get_left()->copy({ L"(",L")" }),
					{ L"(",L")" }),
				new Operands::Number(2)),
			// Chain Rule...
			expression_in->get_left()->derivative(token_in));
	}
	else
	{
		return new Operands::Number(0);
	}

}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Derivative                                                        |
// | Function: power_rule                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operations::Calculus::Derivative::power_rule(
	const Token_t& token_in,
	const Binary* expression_in)
{
	if ((expression_in->get_left()->contains(token_in)) &&
		(expression_in->get_right()->contains(token_in)))
	{
		// Derive by using the power rule and the product rule. Create the 
		// rearranged expression on the stack so it will be garbage collected
		// upon return.
		Arithmatic::PrefixUnary expression(L"exp",
			new Arithmatic::InfixBinary(L"*",
				expression_in->get_right()->copy(),
				new Arithmatic::PrefixUnary(L"ln",
					expression_in->get_left()->copy(),
					{ L"",L"" },
					{ L"(",L")" }),
				{ L"(",L")" }));
		return expression.derivative(token_in);
	}
	else if (expression_in->get_left()->contains(token_in))
	{
		if (expression_in->get_right()->contains_variable())
		{
			// This is the classic power rule.
			return new Arithmatic::InfixBinary(L"*",
				new Arithmatic::InfixBinary(L"*",
					expression_in->get_right()->copy(),
					new Arithmatic::InfixBinary(L"^",
						expression_in->get_left()->copy(),
						new Arithmatic::InfixBinary(L"-",
							expression_in->get_right()->copy(),
							new Operands::Number(1),
							{ L"(",L")" }))),
				// Chain Rule...
				expression_in->get_left()->derivative(token_in));
		}
		else
		{
			TokenValueMap_t values;
			// This is the classic power rule.
			return new Arithmatic::InfixBinary(L"*",
				new Arithmatic::InfixBinary(L"*",
					expression_in->get_right()->copy(),
					new Arithmatic::InfixBinary(L"^",
						expression_in->get_left()->copy(),
						new Operands::Number(
							expression_in->get_right()->solution(values) - 1.0))),
				// Chain Rule...
				expression_in->get_left()->derivative(token_in));
		}
	}
	else if (expression_in->get_right()->contains(token_in))
	{
		return new Arithmatic::InfixBinary(L"*",
			new Arithmatic::InfixBinary(L"*",
				expression_in->copy(),
				new Arithmatic::PrefixUnary(L"ln",
					expression_in->get_left()->copy(),
					{ L"",L"" },
					{ L"(",L")" })),
			// Chain Rule...
			expression_in->get_right()->derivative(token_in));
	}
	else
	{
		return new Operands::Number(0);
	}
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Derivative                                                        |
// | Function: product_rule                                                   |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operations::Calculus::Derivative::product_rule(
	const Token_t& token_in,
	const Binary* expression_in)
{
	if ((expression_in->get_left()->contains(token_in)) &&
		(expression_in->get_right()->contains(token_in)))
	{
		// Product Rule...
		return new Arithmatic::InfixBinary(L"+",
			new Arithmatic::InfixBinary(L"*",
				expression_in->get_left()->derivative(token_in),
				expression_in->get_right()->copy()),
			new Arithmatic::InfixBinary(L"*",
				expression_in->get_left()->copy(),
				expression_in->get_right()->derivative(token_in)),
			{ L"(",L")" });
	}
	else if (expression_in->get_left()->contains(token_in))
	{
		return new Arithmatic::InfixBinary(L"*",
			expression_in->get_left()->derivative(token_in),
			expression_in->get_right()->copy());
	}
	else if (expression_in->get_right()->contains(token_in))
	{
		return new Arithmatic::InfixBinary(L"*",
			expression_in->get_left()->copy(),
			expression_in->get_right()->derivative(token_in));
	}
	else
	{
		return new Operands::Number(0);
	}
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Derivative                                                        |
// | Function: quotient_rule                                                  |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operations::Calculus::Derivative::quotient_rule(
	const Token_t& token_in,
	const Binary* expression_in)
{
	if ((expression_in->get_left()->contains(token_in)) &&
		(expression_in->get_right()->contains(token_in)))
	{
		// Quotient Rule...
		return new Arithmatic::InfixBinary(L"/",
			new Arithmatic::InfixBinary(L"-",
				new Arithmatic::InfixBinary(L"*",
					expression_in->get_left()->derivative(token_in),
					expression_in->get_right()->copy()),
				new Arithmatic::InfixBinary(L"*",
					expression_in->get_left()->copy(),
					expression_in->get_right()->derivative(token_in)),
				{ L"(",L")" }),
			new Arithmatic::InfixBinary(L"^",
				expression_in->get_right()->copy(),
				new Operands::Number(2.0),
				{ L"(",L")" }));
	}
	else if (expression_in->get_left()->contains(token_in))
	{
		return new Arithmatic::InfixBinary(L"/",
			expression_in->get_left()->derivative(token_in),
			expression_in->get_right()->copy({ L"(",L")" }));
	}
	else if (expression_in->get_right()->contains(token_in))
	{
		Arithmatic::InfixBinary expression(L"^",
			expression_in->get_left()->copy(),
			new Arithmatic::PrefixUnary(L"~",
				expression_in->get_right()->copy(),
				{ L"(",L")" }));
		return expression.derivative(token_in);
	}
	else
	{
		return new Operands::Number(0);
	}
}



//  __________________________________________________________________________
// |                                                                          |
// | Class: Derivative                                                        |
// | Function: sum_and_difference                                             |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression*
Mathematics::Expressions::Operations::Calculus::Derivative::sum_and_difference(
	const Token_t& token_in,
	const Binary* expression_in)
{
	return new Arithmatic::InfixBinary(expression_in->get_token(),
			expression_in->get_left()->derivative(token_in),
			expression_in->get_right()->derivative(token_in));
}