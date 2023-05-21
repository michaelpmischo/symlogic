// ============================================================================
//! @file Constants/h
//! @author Michael P. MIscho
//! @date April 29, 2023
//! @brief This file is the header for the Integer number type header.
//! @see 
// ____________________________________________________________________________
//! @copyright Copyright (C) 2024 Michael P. Mischo - All Rights Reserved
//! You may use, distribute and modify this code under the terms of the GPL
//! license. You should have received a copy of the GPL license with this 
//! file. If not, please write to: , or visit :
//! https://www.gnu.org/licenses/gpl-3.0.en.html
// ============================================================================
#ifndef __MATHEMATICS_CONSTANTS_H_
#define __MATHEMATICS_CONSTANTS_H_
#include <Types/Numbers/Complex.h>
#include <Types/Numbers/Rational.h>

namespace Mathematics
{
//! Archimedes' Constant (pi) -
//! The ratio between the circumference and diameter of a circle.
const float128_t 𝝅 = 3.141592653589793238462643383279503;

//! Euler's Number
//! The constant occurs in many natural models. Also known as
//! the exponential growth constant. This occurs in finance, population,
//! decay, and many other natural models.
const float128_t ℯ = 2.718281828459045235360287471352662;

//! Golden Ratio
//! The constant occurs many times in nature.
const float128_t φ = 1.6180339887498948482045868343656;
}

#endif // __MATHEMATICS_CONSTANTS_H_