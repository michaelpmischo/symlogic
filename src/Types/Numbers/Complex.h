// ============================================================================
//! @file Complex.h
//! @author Michael P. MIscho
//! @date April 29, 2023
//! @brief This file is the header for the Integer number type header.
//! @see https://en.wikipedia.org/wiki/Complex_number
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
#ifndef __MATHEMATICS_COMPLEX_H_
#define __MATHEMATICS_COMPLEX_H_
#include <Types/Numbers/Number.h>

namespace Mathematics
{
//  __________________________________________________________________________
// |                                                                          |
// |                                                                          |
// |                                   Complex                                |
// |                                                                          |
// |__________________________________________________________________________|
// 
// --------------------------------- Description ------------------------------
//! @brief Complex Number (C)
//! A number from the set of complex numbers where a complex number is a real 
//! number with an imaginary extension of a real number multiplied by the 
//! imaginary unit i. Where i = sqrt(-1). Complex numbers can be expressed
//! in the form a + ib. Where a is the real value and b is the imaginary 
//! value.
// ____________________________________________________________________________
class Complex
{
public:
    Complex();
    Complex(Real real_in);
    Complex(Real real_in, Imaginary imaginary_in);

    // Copy/Move Constructor
    Complex(const Complex& rhs);
    Complex(Complex&& rhs);

    // Copy/Move Operator
    Complex& operator=(const Complex& rhs);
    Complex& operator=(Complex&& rhs);

    // Arithmetic Operators
    Complex operator+(const Complex& rhs) const;
    Complex operator+() const;
    Complex& operator+=(const Complex& rhs);
    Complex operator-(const Complex& rhs) const;
    Complex operator-() const;
    Complex& operator-=(const Complex& rhs);
    Complex operator*(const Complex& rhs) const;
    Complex& operator*=(const Complex& rhs);
    Complex operator/(const Complex& rhs) const;
    Complex& operator/=(const Complex& rhs);
    Complex operator%(const Complex& rhs) const;
    Complex& operator%=(const Complex& rhs);

    bool operator==(const Complex& rhs) const;
    bool operator!=(const Complex& rhs) const;
    bool operator<(const Complex& rhs) const;
    bool operator<=(const Complex& rhs) const;
    bool operator>(const Complex& rhs) const;
    bool operator>=(const Complex& rhs) const;
    bool operator&&(const Complex& rhs) const;
    bool operator||(const Complex& rhs) const;
    bool operator!() const;

    friend ostream_t& operator<<(ostream_t& stream, const Complex& number_in)
    {
        stream << number_in.real;
        if (number_in.imaginary != 0.0)
        {
            stream << ((number_in.imaginary < 0.0) ?
#ifdef __WCHAR_IO__
			 "-ⅈ" : "+ⅈ");
#else
            "-i" : "+i");
#endif
			stream << abs(number_in.imaginary);
        }
        return stream;
    }

    friend istream_t& operator>>(istream_t& stream, Complex& number_in)
    {
        std::cout << "Enter the Real factor:";
        stream >> number_in.real;
        std::cout << "Enter the Imaginary factor:";
        stream >> number_in.imaginary;
        return stream;
    }

    ~Complex() = default;

    inline Real get_real() const;
    inline Imaginary get_imaginary() const;
    inline Complex conjugate() const;

private:
    Real								real;
    Imaginary							imaginary;
};
} // namespace Mathematics


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Real Mathematics::Complex::get_real() const
{
    return this->real;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Imaginary Mathematics::Complex::get_imaginary() const
{
    return this->imaginary;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Complex Mathematics::Complex::conjugate() const
{
    return Complex(this->real, -this->imaginary);
}

#endif // __MATHEMATICS_COMPLEX_H_