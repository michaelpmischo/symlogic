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
}
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
    bool exception;
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
        "Test Case 1: Polynomial Expressions",
        "(1/3)*x^2+3*x+11",
        {
            "2/3*x+3",                                     // Derivative
            "1/9*x^3+3/2*x^2+11*x",                        // Integral
            { 0,  1,            2,           3,     },      // x
            { 11, (43.0/3.0),   (55.0/3.0),  23,    },      // y
            { 3,  (11.0/3.0),   (13.0/3.0),  5,     },      // y_prime
            { 0,  (227.0/18.0), (257.0/9.0), 106.5, },      // Dy
            false, // Exceptions
        },
    },

    {
        "Test Case 2: Trigonometric Expressions",
        "2*sin(x-pi/4)+cos(pi/x)-tan(x)",
        {
            "2*cos(x-pi/4)-sin(pi/x)*(pi/(x^2)-(sec(x))^2",
            "",
            { -3,                 -2,                  -1,                  1,                   2,                  3                    }, // x
			{ 1.5579404429452075, -2.8824601163257264, -1.3967148031440488, -2.1314908943363098, 4.0595011166929833, 2.2421811877346927,  }, // y
			{ -2.92225405564, -8.43425862087, -3.85143565113, -1.47139629302, -5.86237711438, -2.523106397,   }, // dydx
			{}, // DyDx
            false, // Exceptions
        },
    },

    {
		"Test Case 2b: Trigonometric Expressions",
		"pi*(sin(pi/x))/(x^2)+2*sin(x+(pi/4))-(sec(x))^2",
		{
			"",
			"",
			{ -3,                 -2,                  -1,                  1,                   2,                  3                    }, // x
			{ 28.118588330699076, 3.6491706619643756, -3.8514356511333512, -1.4713962930158078, -5.1929643379627297, -2.2527795506076727,  }, // y
			{ -2.92225405564, -8.43425862087, -3.85143565113, -1.47139629302, -5.86237711438, -2.523106397,   }, // dydx
			{}, // DyDx
			false, // Exceptions
		},
	},

    {
        "Test Case 3: Exponentials of x",
        "x^x+sqrt(x-2)+ln(x^2-x)",
        {
            "x^x*(ln(x)-1)-1/(sqrt(x-2)+(2*x-1)/(x^2-x)",
            "",
            { 3,             4,             5,             }, // x
			{ 29.791759469228055, 259.89912021216111, 3129.7277830811231, }, // y
			{ 2.11707724858, 98.3907424175, 1904.03519189, }, // dydx
			{}, // DyDx
            false, // Exceptions
        },
    },
    {
        "Test Case 4: Junk to Induce a Malformed Error.",
        "23/&423]c +3 4tg sd strg][",
        {
			"",
			"",
            {}, // x
			{}, // y
			{}, // dydx
			{}, // DyDx
            true, // Exceptions
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
            const Expressions::Expression* tree_in);
    void integral_test(const ExpressionTestCase_t& test_case_in,
            const Expressions::Expression* tree_in);

}; // class ExpressionTests
} // namespace Tests
} // namespace Mathematics

#endif // __MATHEMATICS_EXPRESSION_TEST_H_