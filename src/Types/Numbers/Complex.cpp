// ============================================================================
//! @file Complex.cpp
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
#include <Types/Numbers/Complex.h>
#include <Exceptions/Undefined.h>

#include <sstream>


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Complex::Complex() :
    real(0.0),
    imaginary(0.0)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Complex::Complex(Real real_in) :
    real(real_in),
    imaginary(0.0)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Complex::Complex(Real real_in, Imaginary imaginary_in) :
    real(real_in),
    imaginary(imaginary_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Complex::Complex(const Complex& rhs) :
    real(rhs.real),
    imaginary(rhs.imaginary)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Complex::Complex(Complex&& rhs) :
    real(rhs.real),
    imaginary(rhs.imaginary)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Complex& Mathematics::Complex::operator=(const Complex& rhs)
{
    this->real = rhs.real;
    this->imaginary = rhs.imaginary;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Complex& Mathematics::Complex::operator=(Complex&& rhs)
{
    this->real					= rhs.real;
    this->imaginary				= rhs.imaginary;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Complex Mathematics::Complex::operator+(const Complex& rhs) const
{
    return Complex(this->real + rhs.real, this->imaginary + rhs.imaginary);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Complex Mathematics::Complex::operator+() const
{
    return Complex(+this->real, +this->imaginary);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Complex& Mathematics::Complex::operator+=(const Complex& rhs)
{
    *this = *this + rhs;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Complex Mathematics::Complex::operator-(const Complex& rhs) const
{
    return Complex(this->real - rhs.real, this->imaginary - rhs.imaginary);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Complex Mathematics::Complex::operator-() const
{
    return Complex(-this->real, -this->imaginary);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Complex& Mathematics::Complex::operator-=(const Complex& rhs)
{
    *this = *this - rhs;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Complex Mathematics::Complex::operator*(const Complex& rhs) const
{
    return Complex(this->real * rhs.real, this->imaginary * rhs.imaginary);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Complex& Mathematics::Complex::operator*=(const Complex& rhs)
{
    *this = *this * rhs;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Complex Mathematics::Complex::operator/(const Complex& rhs) const
{
    Complex out;
    if (rhs.real || rhs.imaginary) 
    {
        if (rhs.real)
        {
            out.real = this->real / rhs.real;
        }

        if (rhs.imaginary)
        {
            out.imaginary = this->imaginary / rhs.imaginary;
        }
    }
    else
    {
        std::wstringstream error;
        error << L"Operation : (" << *this << 
                L")/(" << rhs << L") is Undefined!";
        throw Exceptions::Undefined(error.str());
    }
    return out;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Complex& Mathematics::Complex::operator/=(const Complex& rhs)
{
    *this = *this / rhs;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Complex Mathematics::Complex::operator%(const Complex& rhs) const
{
    Complex out;
    if (rhs.real || rhs.imaginary)
    {
        if (rhs.real)
        {
            out.real = std::fmod(this->real, rhs.real);
        }

        if (rhs.imaginary)
        {
            out.imaginary = std::fmod(this->imaginary, rhs.imaginary);
        }
    }
    else
    {
        std::wstringstream error;
        error << L"Operation : (" << *this << 
                L")/(" << rhs << L") is Undefined!";
        throw Exceptions::Undefined(error.str());
    }
    return out;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Complex& Mathematics::Complex::operator%=(const Complex& rhs)
{
    *this = *this % rhs;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
bool Mathematics::Complex::operator==(const Complex& rhs) const
{
    return((this->real == rhs.real) && (this->imaginary == rhs.imaginary));
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
bool Mathematics::Complex::operator!=(const Complex& rhs) const
{
    return !(*this == rhs);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
bool Mathematics::Complex::operator<(const Complex& rhs) const
{
    // TODO - This may still need work.
    return this->real < rhs.real && this->imaginary < rhs.imaginary;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
bool Mathematics::Complex::operator<=(const Complex& rhs) const
{
    return !(*this > rhs);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
bool Mathematics::Complex::operator>(const Complex& rhs) const
{
    // TODO - This may still need work. How to compare compex numbers?
    return (this->real > rhs.real && this->imaginary > rhs.imaginary);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
bool Mathematics::Complex::operator>=(const Complex& rhs) const
{
    return !(*this < rhs);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
bool Mathematics::Complex::operator&&(const Complex& rhs) const
{
    return (this->real && rhs.real) && (this->imaginary && rhs.imaginary);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
bool Mathematics::Complex::operator||(const Complex& rhs) const
{
    return (this->real || rhs.real) || (this->imaginary || rhs.imaginary);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Complex                                                           |
// | Function:                                                                |
// |__________________________________________________________________________|
bool Mathematics::Complex::operator!() const
{
    return !(this->real && this->imaginary);
}

