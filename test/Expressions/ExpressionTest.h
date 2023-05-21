// ============================================================================
//! @file ExpressionTest.h
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
#ifndef __MATHEMATICS_EXPRESSION_TEST_H_
#define __MATHEMATICS_EXPRESSION_TEST_H_
#include <Test.h>
#include <deque>

namespace Mathematics
{
namespace Expressions
{
class Expression;

namespace Tests
{
    typedef std::deque<Real> ValueList_t;

typedef struct
{
    Token_t dydx;
    Token_t DyDx;
    ValueList_t x;
    ValueList_t y;
    ValueList_t y_prime;
    ValueList_t Dy;
    uint64_t exceptions;
} ExpressionVerificationData_t;

typedef struct
{
    Token_t name;
    Token_t expression;
    ExpressionVerificationData_t verify;
} ExpressionTestCase_t;

typedef std::list<ExpressionTestCase_t> ExpressionTestCases_t;


static const ExpressionTestCases_t expression_tests =
{
    {
        L"Test Case 1: Polynomial Expressions",
        L"(1/3)*x^2+3*x+11",
        {
            L"2/3*x+3",                                     // Derivative
            L"1/9*x^3+3/2*x^2+11*x",                        // Integral
            { 0,  1,            2,           3,     },      // x
            { 11, (43.0/3.0),   (55.0/3.0),  23,    },      // y
            { 3,  (11.0/3.0),   (13.0/3.0),  5,     },      // y_prime
            { 0,  (227.0/18.0), (257.0/9.0), 106.5, },      // Dy
            0U, // Exceptions
        },
    },

    {
        L"Test Case 2: Trigonometric Expressions",
        L"2*sin(x-pi/4)+cos(pi/x)-tan(x)",
        {
            L"2*cos(x-pi/4)-sin(pi/x)*(pi/(x^2)-(sec(x))^2",
            L"",
            { 3,                   }, // x
			{ 2.2421811877346927,  }, // y
			{ -2.2527795506076727, }, // dydx
			{ 0,                   }, // DyDx
            0U, // Exceptions
        },
    },

    {
        L"Test Case 3: Exponentials of x",
        L"x^x+sqrt(x-2)+ln(x^2-x)",
        {
            L"",
            L"",
            { 3,                 }, // x
			{29.791759469228055, }, // y
			{58.495865127372305, }, // dydx
			{0,                  }, // DyDx
            0U, // Exceptions
        },
    },
    {
        L"Test Case 4: Junk to Induce a Malformed Error.",
        L"23/&423]c +3 4tg sd strg][",
        {
			L"",
			L"",
            {}, // x
			{}, // y
			{}, // dydx
			{}, // DyDx
            1U, // Exceptions
        },
    },
};

class ExpressionTest : public Mathematics::Tests::Test
{
public:
    ExpressionTest();
    virtual ~ExpressionTest() = default;

    void run();

private:
    void execute_test(const ExpressionTestCase_t& test_case_in);
    void derivative_test(const ExpressionTestCase_t& test_case_in,
            const Expression* tree_in);
    void integral_test(const ExpressionTestCase_t& test_case_in,
            const Expression* tree_in);

}; // class ExpressionTests
} // namespace Tests
} // namespace Expressions
} // namespace Mathematics

#endif // __MATHEMATICS_EXPRESSION_TEST_H_