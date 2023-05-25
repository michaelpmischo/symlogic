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
//! but WITHstd::cout ANY WARRANTY; without even the implied warranty of
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

#include <Exceptions/Expressions/Malformed.h>
#include <Exceptions/Undefined.h>


//  __________________________________________________________________________
// |                                                                          |
// | Class: ExpressionTest                                                    |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Tests::ExpressionTest::ExpressionTest() :
	Test("ExpressionTest.log")
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: ExpressionTest                                                    |
// | Function: run                                                            |
// |__________________________________________________________________________|
void Mathematics::Expressions::Tests::ExpressionTest::run()
{
	std::cout << DIVIDER0 << std::endl;
	std::cout << typeid(Expression).name() << 
		" Test" << std::endl;
	std::cout << DIVIDER0 << std::endl;
	std::cout << std::endl;

	for (auto test_case : Tests::expression_tests)
	{
		this->begin_test();
		this->execute_test(test_case);
		this->end_test();
		std::cout << std::endl;
	}

	std::cout << std::endl;
	this->summary(this->log);
	this->summary(std::cout);
	std::cout << std::endl;
	std::cout << "End of Test." << std::endl;
	std::cout << DIVIDER0 << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
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
	std::cout << DIVIDER2 << std::endl;
	std::cout << test_case_in.name << std::endl;
	this->push_heading(test_case_in.name);
	std::cout << "Expression: " << test_case_in.expression << std::endl;
	std::cout << DIVIDER2 << std::endl;

	Parser parser;

	std::cout << "Tokenizeing Expression: " << test_case_in.expression << std::endl;
	std::cout << parser.get_tokens(test_case_in.expression) << std::endl;
	std::cout << std::endl;

	std::cout << DIVIDER3 << std::endl;
	std::cout << "Parsing Expression: " << test_case_in.expression << std::endl;
	Expression* tree = nullptr;
	try
	{
		tree = parser.parse(test_case_in.expression);
		std::cout << "Parsing Complete..." << std::endl;
		std::cout << std::endl;
		this->verify_gt<void*>(tree, nullptr);
		this->verify_false(test_case_in.verify.exception);
		std::cout << std::endl;
		std::cout << std::endl;

		
		std::cout << DIVIDER3 << std::endl;
		std::cout << "Post Parse Expression: " << std::endl;
		TokenList_t tokens = tree->infix();
		TokenStream_t out;
		for (auto token : tokens)
		{
			out << token;
		}
		std::cout << out.str() << std::endl;
		std::cout << std::endl;
		this->verify_eq<Token_t>(out.str(), test_case_in.expression);
		std::cout << std::endl;

		std::cout << DIVIDER3 << std::endl;
		std::cout << "Tree Output: " << std::endl;
		std::cout << "Infix  : " << tree->infix() << std::endl;
		std::cout << "Prefix : " << tree->prefix() << std::endl;
		std::cout << "Postfix: " << tree->postfix() << std::endl;
		std::cout << "Size   : " << tree->size() << std::endl;
		std::cout << "Height : " << tree->height() << std::endl;
		std::cout << std::endl;

		std::cout << "Variable List: " << std::endl;
		std::cout << tree->get_variables() << std::endl;
		std::cout << std::endl;

		std::cout << DIVIDER3 << std::endl;
		std::cout << "Tree Solutions:" << std::endl;
		for (size_t i = 0U;
			(i < test_case_in.verify.x.size() && i < test_case_in.verify.y.size());
			i++)
		{
			TokenValueMap_t variables = { {"x", test_case_in.verify.x[i]},};
			Real sol = tree->solution(variables);
			std::cout << "Solution: y(" << test_case_in.verify.x[i] << ") = " << sol << std::endl;
			this->verify_eq<Real>(sol, test_case_in.verify.y[i]);
			std::cout << std::endl;
		}
		std::cout << std::endl;

		std::cout << DIVIDER3 << std::endl;
		std::cout << "Expression Tree: " << std::endl;
		std::cout << tree->pretty_tree();
		std::cout << std::endl;

		this->derivative_test(test_case_in, tree);
		this->integral_test(test_case_in, tree);
	}
	catch (Mathematics::Expressions::Malformed& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
		this->verify_true(test_case_in.verify.exception);
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
	this->push_heading(test_case_in.name + " Derivative Tests");
	std::cout << DIVIDER2 << std::endl;
	std::cout << "Taking Derivative: " << test_case_in.expression << std::endl;
	Expression* derivative = tree_in->derivative("x");
	std::cout << "Differentiation Complete..." << std::endl;
	std::cout << std::endl;

	std::cout << "Derivative Expression: " << std::endl;
	TokenList_t tokens = derivative->infix();
	for (auto token : tokens)
	{
		std::cout << token;
	}
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Derivative Tree Output: " << std::endl;
	std::cout << "Infix  : " << derivative->infix() << std::endl;
	std::cout << "Prefix : " << derivative->prefix() << std::endl;
	std::cout << "Postfix: " << derivative->postfix() << std::endl;
	std::cout << "Size   : " << derivative->size() << std::endl;
	std::cout << "Height : " << derivative->height() << std::endl;
	std::cout << std::endl;

	std::cout << "Derivative Variable List: " << std::endl;
	std::cout << derivative->get_variables() << std::endl;
	std::cout << std::endl;

	std::cout << DIVIDER3 << std::endl;
	std::cout << "Derivative Tree Solution:" << std::endl;
	for (size_t i = 0U;
		(i < test_case_in.verify.x.size() && i < test_case_in.verify.y_prime.size());
		i++)
	{
		TokenValueMap_t variables = { {"x", test_case_in.verify.x[i]},};
		Real sol = derivative->solution(variables);
		std::cout << "Solution: y'(" << test_case_in.verify.x[i] << ") = " << sol << std::endl;
		this->verify_eq<Real>(sol, test_case_in.verify.y_prime[i]);
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << DIVIDER3 << std::endl;
	std::cout << "Derivative Tree: " << std::endl;
	std::cout << derivative->pretty_tree();
	std::cout << std::endl;

	// End of DerivativeTestCase.
	std::cout << DIVIDER2 << std::endl;
	std::cout << std::endl;
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
	this->push_heading(test_case_in.name + " Integral Tests");
	std::cout << DIVIDER2 << std::endl;
	std::cout << "Taking Integral: " << test_case_in.expression << std::endl;
	Expression* integral = tree_in->integral("x");
	std::cout << "Integration Complete..." << std::endl;
	std::cout << std::endl;

	std::cout << "Integral Expression: " << std::endl;
	TokenList_t tokens = integral->infix();
	for (auto token : tokens)
	{
		std::cout << token;
	}
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Integral Tree Output: " << std::endl;
	std::cout << "Infix  : " << integral->infix() << std::endl;
	std::cout << "Prefix : " << integral->prefix() << std::endl;
	std::cout << "Postfix: " << integral->postfix() << std::endl;
	std::cout << "Size   : " << integral->size() << std::endl;
	std::cout << "Height : " << integral->height() << std::endl;
	std::cout << std::endl;

	std::cout << "Integral Variable List: " << std::endl;
	std::cout << integral->get_variables() << std::endl;
	std::cout << std::endl;

	std::cout << DIVIDER3 << std::endl;
	std::cout << "Integral Tree Solution:" << std::endl;
	for (size_t i = 0U; 
		(i < test_case_in.verify.x.size() && i < test_case_in.verify.Dy.size());
		i++)
	{
		TokenValueMap_t variables = { {"x", test_case_in.verify.x[i]},};
		Real sol = integral->solution(variables);
		std::cout << "Solution: Dy(" << test_case_in.verify.x[i] << ") = " << sol << std::endl;
		this->verify_eq<Real>(sol, test_case_in.verify.Dy[i]);
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << DIVIDER3 << std::endl;
	std::cout << "Integral Tree: " << std::endl;
	std::cout << integral->pretty_tree();
	std::cout << std::endl;

	// End of Integral Test Case.
	std::cout << DIVIDER2 << std::endl;
	std::cout << std::endl;
}