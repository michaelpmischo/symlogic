// ============================================================================
//! @file Malformed.h
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
#ifndef __MATHEMATICS_MALFORMED_H_
#define __MATHEMATICS_MALFORMED_H_
#include <Expressions/Tokens.h>
#include <exception>
#include <string>

namespace Mathematics
{
namespace Exceptions
{
class Malformed : public std::exception
{
public:
    Malformed(const wchar_t* explanation_in, 
            const Expressions::Token_t& malformaed_expression_in,
            size_t malformed_location_in);
    Malformed(const Expressions::Token_t& explanation_in,
            const Expressions::Token_t& malformaed_expression_in,
            size_t malformed_location_in);

    Malformed(const Malformed& rhs);
    Malformed(const Malformed&& rhs);

    Malformed& operator=(const Malformed& rhs);
    Malformed& operator=(Malformed&& rhs);

    //! @breif Returns the explanatory string.
    //! @return Pointer to a null-terminated string with explanatory 
    //! information. The pointer is guaranteed to be valid at least until
    //! the exception object from which it is obtained is destroyed, or until 
    //! a non-const member function on the exception object is called.
    virtual const char* what() const noexcept override;
    virtual Expressions::Token_t what_utf16() const noexcept;

    ~Malformed();

protected:
    Expressions::Token_t                         explanation;
    Expressions::Token_t                         malformed_expression;
    Expressions::Token_t                         malformed_location;
}; // class Malformed
} // namespace Exceptions
} // namespace Mathematics

#endif // __MATHEMATICS_MALFORMED_H_
