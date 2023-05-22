// ============================================================================
//! @file Undefined.h
//! @author Michael P. MIscho
//! @date April 29, 2023
//! @brief This file is the header for the Integer number type header.
//! @see https://en.wikipedia.org/wiki/Complex_number
// ____________________________________________________________________________
//! @copyright Copyright (C) 2024 Michael P. Mischo - All Rights Reserved
//! You may use, distribute and modify this code under the terms of the GPL
//! license. You should have received a copy of the GPL license with this 
//! file. If not, please write to: , or visit :
//! https://www.gnu.org/licenses/gpl-3.0.en.html
// ============================================================================
#ifndef __MATHEMATICS_UNDEFINED_H_
#define __MATHEMATICS_UNDEFINED_H_
#include <exception>
#include <string>

namespace Mathematics
{
    namespace Exceptions
    {
        class Undefined : public std::exception
        {
        public:
            Undefined(const wchar_t* explanation_in);
            Undefined(const std::string& explanation_in);

            Undefined(const Undefined& rhs);
            Undefined(const Undefined&& rhs);

            Undefined& operator=(const Undefined& rhs);
            Undefined& operator=(Undefined&& rhs);

            //! @breif Returns the explanatory string.
            //! @return Pointer to a null-terminated string with explanatory 
            //! information. The pointer is guaranteed to be valid at least until
            //! the exception object from which it is obtained is destroyed, or until 
            //! a non-const member function on the exception object is called.
            virtual const char* what() const noexcept override;

            ~Undefined();

        protected:
            std::string                     explanation;
        }; // class Undefined
    } // namespace Exceptions
} // namespace Mathematics

#endif // __MATHEMATICS_UNDEFINED_H_
