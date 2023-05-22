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
Mathematics::Tests::ExpressionTest::ExpressionTest() :
	Test("ExpressionTest.log")
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: ExpressionTest                                                    |
// | Function: run                                                            |
// |__________________________________________________________________________|
void Mathematics::Tests::ExpressionTest::run()
{
	stdout_t << DIVIDER0 << std::endl;
	stdout_t << typeid(Expressions::Expression).name() << 
		" Test" << std::endl;
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
	stdout_t << "End of Test." << std::endl;
	stdout_t << DIVIDER0 << std::endl;
	stdout_t << std::endl;
	stdout_t << std::endl;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: ExpressionTest                                                    |
// | Function: execute_test                                                   |
// |__________________________________________________________________________|
void Mathematics::Tests::ExpressionTest::execute_test(
		const ExpressionTestCase_t& test_case_in)
{
	uint64_t exceptions = 0;
	stdout_t << DIVIDER2 << std::endl;
	stdout_t << test_case_in.name << std::endl;
	this->push_heading(test_case_in.name);
	stdout_t << "Expression: " << test_case_in.expression << std::endl;
	stdout_t << DIVIDER2 << std::endl;

	Expressions::Parser parser;

	stdout_t << "Tokenizeing Expression: " << test_case_in.expression << std::endl;
	stdout_t << parser.get_tokens(test_case_in.expression) << std::endl;
	stdout_t << std::endl;

	stdout_t << DIVIDER3 << std::endl;
	stdout_t << "Parsing Expression: " << test_case_in.expression << std::endl;
	Expressions::Expression* tree = nullptr;
	try
	{
		tree = parser.parse(test_case_in.expression);
		stdout_t << "Parsing Complete..." << std::endl;
		stdout_t << std::endl;
		this->verify_ne<void*>(tree, nullptr);
		this->verify_eq<bool>(test_case_in.verify.exception, false);
		stdout_t << std::endl;
		stdout_t << std::endl;

		
		stdout_t << DIVIDER3 << std::endl;
		stdout_t << "Post Parse Expression: " << std::endl;
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
		stdout_t << "Tree Output: " << std::endl;
		stdout_t << "Infix  : " << tree->infix() << std::endl;
		stdout_t << "Prefix : " << tree->prefix() << std::endl;
		stdout_t << "Postfix: " << tree->postfix() << std::endl;
		stdout_t << "Size   : " << tree->size() << std::endl;
		stdout_t << "Height : " << tree->height() << std::endl;
		stdout_t << std::endl;

		stdout_t << "Variable List: " << std::endl;
		stdout_t << tree->get_variables() << std::endl;
		stdout_t << std::endl;

		stdout_t << DIVIDER3 << std::endl;
		stdout_t << "Tree Solutions:" << std::endl;
		for (size_t i = 0U;
			(i < test_case_in.verify.x.size() && i < test_case_in.verify.y.size());
			i++)
		{
			TokenValueMap_t variables = { {"x", test_case_in.verify.x[i]},};
			Real sol = tree->solution(variables);
			stdout_t << "Solution: y(" << test_case_in.verify.x[i] << ") = " << sol << std::endl;
			this->verify_eq<Real>(sol, test_case_in.verify.y[i]);
			stdout_t << std::endl;
		}
		stdout_t << std::endl;

		stdout_t << DIVIDER3 << std::endl;
		stdout_t << "Expression Tree: " << std::endl;
		stdout_t << tree->print();
		stdout_t << std::endl;

		this->derivative_test(test_case_in, tree);
		this->integral_test(test_case_in, tree);
	}
	catch (Mathematics::Exceptions::Malformed& error)
	{
		stdout_t << "Error: " << error.what(nullptr) << std::endl;
		this->verify_eq<bool>(test_case_in.verify.exception, true);
	}
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: ExpressionTest                                                    |
// | Function: derivative_test                                                |
// |__________________________________________________________________________|
void Mathematics::Tests::ExpressionTest::derivative_test(
	const ExpressionTestCase_t& test_case_in,
	const Expressions::Expression* tree_in)
{
	this->push_heading(test_case_in.name + " Derivative Tests");
	stdout_t << DIVIDER2 << std::endl;
	stdout_t << "Taking Derivative: " << test_case_in.expression << std::endl;
	Expressions::Expression* derivative = tree_in->derivative("x");
	stdout_t << "Differentiation Complete..." << std::endl;
	stdout_t << std::endl;

	stdout_t << "Derivative Expression: " << std::endl;
	TokenList_t tokens = derivative->infix();
	for (auto token : tokens)
	{
		stdout_t << token;
	}
	stdout_t << std::endl;
	stdout_t << std::endl;

	stdout_t << "Derivative Tree Output: " << std::endl;
	stdout_t << "Infix  : " << derivative->infix() << std::endl;
	stdout_t << "Prefix : " << derivative->prefix() << std::endl;
	stdout_t << "Postfix: " << derivative->postfix() << std::endl;
	stdout_t << "Size   : " << derivative->size() << std::endl;
	stdout_t << "Height : " << derivative->height() << std::endl;
	stdout_t << std::endl;

	stdout_t << "Derivative Variable List: " << std::endl;
	stdout_t << derivative->get_variables() << std::endl;
	stdout_t << std::endl;


	stdout_t << DIVIDER3 << std::endl;
	stdout_t << "Derivative Tree Solution:" << std::endl;
	for (size_t i = 0U;
		(i < test_case_in.verify.x.size() && i < test_case_in.verify.y_prime.size());
		i++)
	{
		TokenValueMap_t variables = { {"x", test_case_in.verify.x[i]},};
		Real sol = derivative->solution(variables);
		stdout_t << "Solution: y'(" << test_case_in.verify.x[i] << ") = " << sol << std::endl;
		this->verify_eq<Real>(sol, test_case_in.verify.y_prime[i]);
		stdout_t << std::endl;
	}
	stdout_t << std::endl;

	stdout_t << DIVIDER3 << std::endl;
	stdout_t << "Derivative Tree: " << std::endl;
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
void Mathematics::Tests::ExpressionTest::integral_test(
	const ExpressionTestCase_t& test_case_in,
	const Expressions::Expression* tree_in)
{
	this->push_heading(test_case_in.name + " Integral Tests");
	stdout_t << DIVIDER2 << std::endl;
	stdout_t << "Taking Integral: " << test_case_in.expression << std::endl;
	Expressions::Expression* integral = tree_in->integral("x");
	stdout_t << "Integration Complete..." << std::endl;
	stdout_t << std::endl;

	stdout_t << "Integral Expression: " << std::endl;
	TokenList_t tokens = integral->infix();
	for (auto token : tokens)
	{
		stdout_t << token;
	}
	stdout_t << std::endl;
	stdout_t << std::endl;

	stdout_t << "Integral Tree Output: " << std::endl;
	stdout_t << "Infix  : " << integral->infix() << std::endl;
	stdout_t << "Prefix : " << integral->prefix() << std::endl;
	stdout_t << "Postfix: " << integral->postfix() << std::endl;
	stdout_t << "Size   : " << integral->size() << std::endl;
	stdout_t << "Height : " << integral->height() << std::endl;
	stdout_t << std::endl;

	stdout_t << "Integral Variable List: " << std::endl;
	stdout_t << integral->get_variables() << std::endl;
	stdout_t << std::endl;

	stdout_t << DIVIDER3 << std::endl;
	stdout_t << "Integral Tree Solution:" << std::endl;
	for (size_t i = 0U; 
		(i < test_case_in.verify.x.size() && i < test_case_in.verify.Dy.size());
		i++)
	{
		TokenValueMap_t variables = { {"x", test_case_in.verify.x[i]},};
		Real sol = integral->solution(variables);
		stdout_t << "Solution: Dy(" << test_case_in.verify.x[i] << ") = " << sol << std::endl;
		this->verify_eq<Real>(sol, test_case_in.verify.Dy[i]);
		stdout_t << std::endl;
	}
	stdout_t << std::endl;

	stdout_t << DIVIDER3 << std::endl;
	stdout_t << "Integral Tree: " << std::endl;
	stdout_t << integral->print();
	stdout_t << std::endl;

	// End of Integral Test Case.
	stdout_t << DIVIDER2 << std::endl;
	stdout_t << std::endl;
}