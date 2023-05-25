// ============================================================================
//! @file Basic.h
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
#ifndef __MATHEMATICS_TYPES_BASIC_H_
#define __MATHEMATICS_TYPES_BASIC_H_
#include <Types/Basic/Definitions.h>
#include <cstdint>
#include <iostream>

// Definition of the floating point types.
typedef float float32_t;
typedef double float64_t;
typedef long double float128_t;

// IEEE-Std. 754 Types
typedef float32_t ieee754_single;
typedef float64_t ieee754_double;
typedef float64_t ieee754_quadruple;

typedef long long smax_t;
typedef unsigned long long umax_t;

    // Try to define a larger integer type.
#ifndef int128_t
  #ifdef __int128
    typedef __int128 int128_t;
  #endif
#endif

#ifdef int128_t
  #undef smax_t
  #define int128_t smax_t;
#endif

    // Try to define a larger unsigned type
#ifndef uint128_t
  #ifdef __uint128
    typedef __uint128 uint128_t;
  #else
    #ifdef __int128
      typedef unsigned __int128 uint128_t;
    #endif
  #endif
#endif

#ifdef uint128_t
  #undef umax_t
  #define uint128_t umax_t;
#endif

#ifdef __CHECK_FOR_INT128__
  #ifdef __SIZEOF_INT128__ 
    #error 128-bit integers are available!
  #endif 
  #ifdef __int128
    #error 128-bit integers are available!
  #endif
#endif

#endif // __MATHEMATICS_TYPES_BASIC_H_

