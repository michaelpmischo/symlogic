// ============================================================================
//! @file Rational.h
//! @author Michael P. MIscho
//! @date April 29, 2023
//! @brief This file is the header for the Rational number type header.
//! @see https://en.wikipedia.org/wiki/Rational_number
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
#ifndef __MATHEMATICS_RATIONAL_H_
#define __MATHEMATICS_RATIONAL_H_
#include <Types/Numbers/Number.h>

namespace Mathematics
{
//  __________________________________________________________________________
// |                                                                          |
// |                                                                          |
// |                                   Rational                               |
// |                                                                          |
// |__________________________________________________________________________|
// 
// --------------------------------- Description ------------------------------
//! @brief Rational Numbers (Q)
//! A number form the set of Rationals where a rational is a value that can 
//! be expressed as a quotient fraction of two integers from (Z).
// ____________________________________________________________________________
class Rational
{
public:

    Rational();
    Rational(Integer numerator_in);
    Rational(Integer numerator_in, Integer denominator_in);

    // Copy/Move Constructor
    Rational(const Rational& rhs);
    Rational(Rational&& rhs);

    // Copy/Move Operator
    Rational& operator=(const Rational& rhs);
    Rational& operator=(Rational&& rhs);

    // We can simplify a Rational Number
    Rational& reduce();

    // Arithmetic Operators
    Rational operator+(const Rational& rhs) const;
    Rational operator+() const;
    Rational& operator+=(const Rational& rhs);
    Rational operator-(const Rational& rhs) const;
    Rational operator-() const;
    Rational& operator-=(const Rational& rhs);
    Rational operator*(const Rational& rhs) const;
    Rational& operator*=(const Rational& rhs);
    Rational operator/(const Rational& rhs) const;
    Rational& operator/=(const Rational& rhs);
    Rational operator%(const Rational& rhs) const;
    Rational& operator%=(const Rational& rhs);

    bool operator==(const Rational& rhs) const;
    bool operator!=(const Rational& rhs) const;
    bool operator<(const Rational& rhs) const;
    bool operator<=(const Rational& rhs) const;
    bool operator>(const Rational& rhs) const;
    bool operator>=(const Rational& rhs) const;
    bool operator&&(const Rational& rhs) const;
    bool operator||(const Rational& rhs) const;
    bool operator!() const;

    // I/O Operators
    friend std::ostream& operator<<(std::ostream& stream, const Rational& number_in)
    {
        if ((number_in.numerator == 0) ||
            (number_in.denominator == 1))
        {
            stream << number_in.numerator;
        }
        else
        {
            stream << number_in.numerator << "/" << number_in.denominator;
        }
        return stream;
    }

    friend std::istream& operator>>(std::istream& is, Rational& number_in)
    {
        std::cout << "Enter the Numerator:";
        is >> number_in.numerator;
        std::cout << "Enter the Denominator:";
        is >> number_in.denominator;
        number_in.reduce();
        return is;
    }

    // Casting Operators
    operator Real() const;

    // Public Inline Getters.
    inline Integer get_numerator() const;
    inline Integer get_denominator() const;

    //! Destructor
    ~Rational() = default;

private:
    //! Collect the signs and put any in the numerator.
    void consolidate_sign();

    Integer									numerator;
    Integer									denominator;
}; // class Rational
} // namespace Mathematics


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Integer Mathematics::Rational::get_numerator() const
{
    return this->numerator;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Integer Mathematics::Rational::get_denominator() const
{
    return this->denominator;
}

#endif // __MATHEMATICS_RATIONAL_H_