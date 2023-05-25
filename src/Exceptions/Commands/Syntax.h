// ============================================================================
//! @file Syntax.h
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
#ifndef __MATHEMATICS_COMMANDS_SYNTAX_H_
#define __MATHEMATICS_COMMANDS_SYNTAX_H_
#include <exception>
#include <string>

namespace Mathematics
{
namespace UI
{
namespace Core
{
class Syntax : public std::exception
{
public:
    Syntax(const char* explanation_in,
        const std::string& string_in,
        size_t location_in);
    Syntax(const std::string& explanation_in,
        const std::string& string_in,
        size_t location_in);

    Syntax(const Syntax& rhs);
    Syntax(const Syntax&& rhs);

    Syntax& operator=(const Syntax& rhs);
    Syntax& operator=(Syntax&& rhs);

    //! @brief Returns the explanatory string.
    //! @return Pointer to a null-terminated string with explanatory 
    //! information. The pointer is guaranteed to be valid at least until
    //! the exception object from which it is obtained is destroyed, or until 
    //! a non-const member function on the exception object is called.
    virtual const char* what() const noexcept override;

    ~Syntax();

protected:
    std::string                     explanation;
}; // class Syntax
} // namespace Core 
} // namespace UI
} // namespace Mathematics

#endif // __MATHEMATICS_COMMANDS_SYNTAX_H_
