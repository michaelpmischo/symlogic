// ============================================================================
//! @file Expression.h
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
#ifndef __MATHEMATICS_TYPES_NUMBER_H_
#define __MATHEMATICS_TYPES_NUMBER_H_
#include <Types/Basic/Basic.h>

namespace Mathematics
{
    //! Real Numbers (R)
    //! A number from the set of Real numbers. All numbers on the continuous
    //! number line. A real number is any number when squared is greater than
    //! or equal to zero. R = {n^2 >= 0}
    typedef float128_t Real;

    //! Imaginary Numbers (i)
    //! A number from the set of imaginary numbers. An imaginary number is any 
    //! real number multiplied by the imaginary unit vector i, where i = sqrt(-1). 
    //! This value is implied to be multiplied by the imaginary unit i. 
    typedef float128_t Imaginary;

    //! Integer Numbers (Z)
    //! A number from the set of Integers 0, 1, 2, 3, 4, ..., inf including the
    //! negated values of these numbers. Integers are both positive and negative 
    //! discrete numbers including zero.
    typedef smax_t Integer;

    //! Natural Numbers (N)
    //! A positive number of the set of numbers 1, 2, 3, 4, 5, ... , inf. This 
    //! sometimes includes 0 depending on the standard and definition.
    typedef umax_t Natural;

    // Real Value Booleans.
    const Real TRUE				= 1.0;
    const Real FALSE			= 0.0;
}

#endif // __MATHEMATICS_TYPES_NUMBER_H_

