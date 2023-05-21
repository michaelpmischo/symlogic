// ============================================================================
//! @file ExpressionTest.cpp
//! @author Michael P. MIscho
//! @date May 4, 2023
//! @brief This file is the header for the Integer number type header.
//! @see 
// ____________________________________________________________________________
//! @copyright Copyright (C) 2023 Michael P, Mischo - All Rights Reserved
//! 
//! This program is free software; you can redistribute it and /or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation; either version 2 of the License, or
//! (at your option) any later version.
//!
//! This program is distributed in the hope that it will be useful,
//! but WITHstdout_t ANY WARRANTY; without even the implied warranty of
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
#include <Expressions/ExpressionTest.h>

// Include Unit Under Test
#include <Expressions/Expression.h>
#include <Expressions/Parser.h>

#include <Exceptions/Malformed.h>
#include <Exceptions/Undefined.h>


//  __________________________________________________________________________
// |                                                                          |
// | Class: ExpressionTest                                                    |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Tests::ExpressionTest::ExpressionTest() :
	Test(L"ExpressionTest.log")
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: ExpressionTest                                                    |
// | Function: run                                                            |
// |__________________________________________________________________________|
void Mathematics::Expressions::Tests::ExpressionTest::run()
{
	stdout_t << DIVIDER0 << std::endl;
	stdout_t << typeid(Expression).name() << 
		L" Test" << std::endl;
	stdout_t << DIVIDER0 << std::endl;
	stdout_t << std::endl;

	for (auto test_case : Tests::expression_tests)
	{
		this->begin_test();
		this->execute_test(test_case);
		this->end_test();
		stdout_t << std::endl;
	}

	stdout_t << std::endl;
	this->summary(this->log);
	this->summary(stdout_t);
	stdout_t << std::endl;
	stdout_t << L"End of Test." << std::endl;
	stdout_t << DIVIDER0 << std::endl;
	stdout_t << std::endl;
	stdout_t << std::endl;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: ExpressionTest                                                    |
// | Function: execute_test                                                   |
// |__________________________________________________________________________|
void Mathematics::Expressions::Tests::ExpressionTest::execute_test(
		const ExpressionTestCase_t& test_case_in)
{
	uint64_t exceptions = 0;
	stdout_t << DIVIDER2 << std::endl;
	stdout_t << test_case_in.name << std::endl;
	stdout_t << L"Expression: " << test_case_in.expression << std::endl;
	stdout_t << DIVIDER2 << std::endl;

	Parser parser;

	stdout_t << L"Tokenizeing Expression: " << test_case_in.expression << std::endl;
	stdout_t << parser.get_tokens(test_case_in.expression) << std::endl;
	stdout_t << std::endl;

	stdout_t << DIVIDER3 << std::endl;
	stdout_t << L"Parsing Expression: " << test_case_in.expression << std::endl;
	Expression* tree = nullptr;
	try
	{
		tree = parser.parse(test_case_in.expression);
		stdout_t << L"Parsing Complete..." << std::endl;
		stdout_t << std::endl;
		this->verify_ne<void*>(tree, nullptr);
		this->verify_eq<uint64_t>(test_case_in.verify.exceptions, 0U);
		stdout_t << std::endl;
		stdout_t << std::endl;

		stdout_t << DIVIDER3 << std::endl;
		stdout_t << L"Post Parse Expression: " << std::endl;
		TokenList_t tokens = tree->infix();
		TokenStream_t out;
		for (auto token : tokens)
		{
			out << token;
		}
		stdout_t << out.str() << std::endl;
		stdout_t << std::endl;
		this->verify_eq<Token_t>(out.str(), test_case_in.expression);
		stdout_t << std::endl;

		stdout_t << DIVIDER3 << std::endl;
		stdout_t << L"Tree Output: " << std::endl;
		stdout_t << L"Infix  : " << tree->infix() << std::endl;
		stdout_t << L"Prefix : " << tree->prefix() << std::endl;
		stdout_t << L"Postfix: " << tree->postfix() << std::endl;
		stdout_t << L"Size   : " << tree->size() << std::endl;
		stdout_t << L"Height : " << tree->height() << std::endl;
		stdout_t << std::endl;

		stdout_t << L"Variable List: " << std::endl;
		stdout_t << tree->get_variables() << std::endl;
		stdout_t << std::endl;

		stdout_t << DIVIDER3 << std::endl;
		stdout_t << L"Tree Solutions:" << std::endl;
		for (size_t i = 0U;
			(i < test_case_in.verify.x.size() && i < test_case_in.verify.y.size());
			i++)
		{
			TokenValueMap_t variables = { {L"x", test_case_in.verify.x[i]},};
			Real sol = tree->solution(variables);
			stdout_t << L"Solution: y(" << test_case_in.verify.x[i] << L") = " << sol << std::endl;
			this->verify_eq<Real>(sol, test_case_in.verify.y[i]);
			stdout_t << std::endl;
		}
		stdout_t << std::endl;

		stdout_t << DIVIDER3 << std::endl;
		stdout_t << L"Expression Tree: " << std::endl;
		stdout_t << tree->print();
		stdout_t << std::endl;

		this->derivative_test(test_case_in, tree);
		this->integral_test(test_case_in, tree);
	}
	catch (Mathematics::Exceptions::Malformed& error)
	{
		stdout_t << L"Error: " << error.what_utf16() << std::endl;
		this->verify_ne<uint64_t>(test_case_in.verify.exceptions, 0U);
	}
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: ExpressionTest                                                    |
// | Function: derivative_test                                                |
// |__________________________________________________________________________|
void Mathematics::Expressions::Tests::ExpressionTest::derivative_test(
	const ExpressionTestCase_t& test_case_in,
	const Expression* tree_in)
{
	stdout_t << DIVIDER2 << std::endl;
	stdout_t << L"Taking Derivative: " << test_case_in.expression << std::endl;
	Expression* derivative = tree_in->derivative(L"x");
	stdout_t << L"Differentiation Complete..." << std::endl;
	stdout_t << std::endl;

	stdout_t << L"Derivative Expression: " << std::endl;
	TokenList_t tokens = derivative->infix();
	for (auto token : tokens)
	{
		stdout_t << token;
	}
	stdout_t << std::endl;
	stdout_t << std::endl;

	stdout_t << L"Derivative Tree Output: " << std::endl;
	stdout_t << L"Infix  : " << derivative->infix() << std::endl;
	stdout_t << L"Prefix : " << derivative->prefix() << std::endl;
	stdout_t << L"Postfix: " << derivative->postfix() << std::endl;
	stdout_t << L"Size   : " << derivative->size() << std::endl;
	stdout_t << L"Height : " << derivative->height() << std::endl;
	stdout_t << std::endl;

	stdout_t << L"Derivative Variable List: " << std::endl;
	stdout_t << derivative->get_variables() << std::endl;
	stdout_t << std::endl;


	stdout_t << DIVIDER3 << std::endl;
	stdout_t << L"Derivative Tree Solution:" << std::endl;
	for (size_t i = 0U;
		(i < test_case_in.verify.x.size() && i < test_case_in.verify.y_prime.size());
		i++)
	{
		TokenValueMap_t variables = { {L"x", test_case_in.verify.x[i]},};
		Real sol = derivative->solution(variables);
		stdout_t << L"Solution: y'(" << test_case_in.verify.x[i] << L") = " << sol << std::endl;
		this->verify_eq<Real>(sol, test_case_in.verify.y_prime[i]);
		stdout_t << std::endl;
	}
	stdout_t << std::endl;

	stdout_t << DIVIDER3 << std::endl;
	stdout_t << L"Derivative Tree: " << std::endl;
	stdout_t << derivative->print();
	stdout_t << std::endl;

	// End of DerivativeTestCase.
	stdout_t << DIVIDER2 << std::endl;
	stdout_t << std::endl;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: ExpressionTest                                                    |
// | Function: integral_test                                                  |
// |__________________________________________________________________________|
void Mathematics::Expressions::Tests::ExpressionTest::integral_test(
	const ExpressionTestCase_t& test_case_in,
	const Expression* tree_in)
{
	stdout_t << DIVIDER2 << std::endl;
	stdout_t << L"Taking Integral: " << test_case_in.expression << std::endl;
	Expression* integral = tree_in->integral(L"x");
	stdout_t << L"Integration Complete..." << std::endl;
	stdout_t << std::endl;

	stdout_t << L"Integral Expression: " << std::endl;
	TokenList_t tokens = integral->infix();
	for (auto token : tokens)
	{
		stdout_t << token;
	}
	stdout_t << std::endl;
	stdout_t << std::endl;

	stdout_t << L"Integral Tree Output: " << std::endl;
	stdout_t << L"Infix  : " << integral->infix() << std::endl;
	stdout_t << L"Prefix : " << integral->prefix() << std::endl;
	stdout_t << L"Postfix: " << integral->postfix() << std::endl;
	stdout_t << L"Size   : " << integral->size() << std::endl;
	stdout_t << L"Height : " << integral->height() << std::endl;
	stdout_t << std::endl;

	stdout_t << L"Integral Variable List: " << std::endl;
	stdout_t << integral->get_variables() << std::endl;
	stdout_t << std::endl;

	stdout_t << DIVIDER3 << std::endl;
	stdout_t << L"Integral Tree Solution:" << std::endl;
	for (size_t i = 0U; 
		(i < test_case_in.verify.x.size() && i < test_case_in.verify.Dy.size());
		i++)
	{
		TokenValueMap_t variables = { {L"x", test_case_in.verify.x[i]},};
		Real sol = integral->solution(variables);
		stdout_t << L"Solution: Dy(" << test_case_in.verify.x[i] << L") = " << sol << std::endl;
		this->verify_eq<Real>(sol, test_case_in.verify.Dy[i]);
		stdout_t << std::endl;
	}
	stdout_t << std::endl;

	stdout_t << DIVIDER3 << std::endl;
	stdout_t << L"Integral Tree: " << std::endl;
	stdout_t << integral->print();
	stdout_t << std::endl;

	// End of Integral Test Case.
	stdout_t << DIVIDER2 << std::endl;
	stdout_t << std::endl;
}