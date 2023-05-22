// ============================================================================
//! @file Rational.cpp
//! @author Michael P. MIscho
//! @date April 29, 2023
//! @brief This file is the header for the Integer number type header.
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
#include <Types/Numbers/Rational.h>
#include <Exceptions/Undefined.h>
#include <numeric> // std::gcd
#include <cmath>

// Helper Function.
Mathematics::Integer gcd(Mathematics::Integer a, Mathematics::Integer b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Rational::Rational() :
    numerator(0),
    denominator(1)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Rational::Rational(Integer numerator_in) :
    numerator(numerator_in),
    denominator(1)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Rational::Rational(Integer numerator_in, 
        Integer denominator_in) throw() :
    numerator(numerator_in),
    denominator(denominator_in)
{
    if (this->denominator == 0)
    {
        throw Exceptions::Undefined(
            "Rational is undefined when the Denominator is 0.");
    }
    this->reduce();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Rational::Rational(const Rational& rhs) :
    numerator(rhs.numerator),
    denominator(rhs.denominator)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Rational::Rational(Rational&& rhs) :
    numerator(rhs.numerator),
    denominator(rhs.denominator)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Rational& Mathematics::Rational::operator=(const Rational& rhs)
{
    this->numerator = rhs.numerator;
    this->denominator = rhs.denominator;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Rational& Mathematics::Rational::operator=(Rational&& rhs)
{
    this->numerator = rhs.numerator;
    this->denominator = rhs.denominator;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Rational Mathematics::Rational::operator+(
        const Rational& rhs) const
{
    Rational rational(
        (this->numerator * rhs.denominator + 
            rhs.numerator * this->denominator), 
        (this->denominator * rhs.denominator));
    return rational;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Rational Mathematics::Rational::operator+() const
{
    Rational rational(+this->numerator, this->denominator);
    return rational;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Rational& Mathematics::Rational::operator+=(const Rational& rhs)
{
    *this = *this + rhs;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Rational Mathematics::Rational::operator-(
        const Rational& rhs) const
{
    Rational rational((this->numerator * rhs.denominator - 
        rhs.numerator * this->denominator),
        (this->denominator * rhs.denominator));
    return rational;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Rational Mathematics::Rational::operator-() const
{
    Rational rational(-this->numerator, this->denominator);
    return rational;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Rational& Mathematics::Rational::operator-=(const Rational& rhs)
{
    *this = *this - rhs;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Rational Mathematics::Rational::operator*(
        const Rational& rhs) const
{
    Rational rational(this->numerator * rhs.numerator, 
        this->denominator * rhs.denominator);
    return rational;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Rational& Mathematics::Rational::operator*=(const Rational& rhs)
{
    *this = *this * rhs;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Rational Mathematics::Rational::operator/(
        const Rational& rhs) const
{
    Rational rational(this->numerator * rhs.denominator, 
        this->denominator * rhs.numerator);
    return rational;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Rational& Mathematics::Rational::operator/=(const Rational& rhs)
{
    *this = *this / rhs;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
bool Mathematics::Rational::operator==(const Rational& rhs) const
{
    return static_cast<Real>(*this) == static_cast<Real>(rhs);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
bool Mathematics::Rational::operator!=(const Rational& rhs) const
{
    return !(*this == rhs);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
bool Mathematics::Rational::operator<(const Rational& rhs) const
{
    return static_cast<Real>(*this) < static_cast<Real>(rhs);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
bool Mathematics::Rational::operator<=(const Rational& rhs) const
{
    return !(*this > rhs);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
bool Mathematics::Rational::operator>(const Rational& rhs) const
{
    return static_cast<Real>(*this) > static_cast<Real>(rhs);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
bool Mathematics::Rational::operator>=(const Rational& rhs) const
{
    return !(*this < rhs);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
bool Mathematics::Rational::operator&&(const Rational& rhs) const
{
    return (this->numerator && rhs.numerator);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
bool Mathematics::Rational::operator||(const Rational& rhs) const
{
    return (this->numerator || rhs.numerator);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
bool Mathematics::Rational::operator!() const
{
    return !(this->numerator);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Rational::operator Mathematics::Real() const
{
    return static_cast<Real>(this->numerator) / 
        static_cast<Real>(this->denominator);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
Mathematics::Rational& Mathematics::Rational::reduce()
{
    this->consolidate_sign();
    Integer divisor = gcd(this->numerator, this->denominator);
    this->numerator /= divisor;
    this->denominator /= divisor;
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Rational                                                          |
// | Function:                                                                |
// |__________________________________________________________________________|
void Mathematics::Rational::consolidate_sign()
{
    // Place the sign on in the numerator.
    if ((this->numerator < 0 && this->denominator < 0) ||
        (this->numerator >= 0 && this->denominator < 0))
    {
        this->numerator = -this->numerator;
        this->denominator = -this->denominator;
    }
}