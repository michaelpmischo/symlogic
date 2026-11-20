// ============================================================================
//! @file Terminal.h
//! @author Michael P. MIscho
//! @date May 22, 2023
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
#ifndef __MATHEMATICS_UI_CORE_TERMINAL_H_
#define __MATHEMATICS_UI_CORE_TERMINAL_H_
#include <string>

namespace Mathematics
{
namespace UI
{
namespace Core
{
class CommandHandler;
class ExpressionHandler;
//  __________________________________________________________________________
// |                                                                          |
// |                                                                          |
// |                                  Terminal                                |
// |                                                                          |
// |__________________________________________________________________________|
// 
// --------------------------------- Description ------------------------------
//! @brief
// ____________________________________________________________________________
class Terminal
{
public:
    static Terminal* instance();

    int run();

	int exit_success();
	int exit_failure();
    void output(const std::string& output_in);
    std::string title() const;

    ~Terminal();

private:
	Terminal();

	const char* input_prompt = " >>>: ";
	const char* output_prompt = " <<<: ";

    size_t count;

    static Terminal* singleton;
}; // class Terminal
} // namespace Core
} // namespace UI
} // namespace Mathematics

#endif