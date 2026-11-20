// ============================================================================
//! @file ExpressionPrinter.cpp
//! @author Michael P. MIscho
//! @date May 25, 2023
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
#include <UI/Core/Expressions/ExpressionPrinter.h>
#include <Expressions/Expression.h>

const Mathematics::UI::Core::ExpressionPrinter::CharacterMap_t
Mathematics::UI::Core::ExpressionPrinter::characters =
{
};


//  __________________________________________________________________________
// |                                                                          |
// | Class: ExpressionPrinter                                                 |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::UI::Core::ExpressionPrinter::ExpressionPrinter(
		const Expressions::Expression* expression_in) :
	expression(to_string(expression_in))
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: ExpressionPrinter                                                 |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
std::string Mathematics::UI::Core::ExpressionPrinter::get_string() const
{
	std::string output;
	for (auto string : this->expression)
	{
		output += string + "\n";
	}
	return output;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: ExpressionPrinter                                                 |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
std::string Mathematics::UI::Core::ExpressionPrinter::to_string(
	const Expressions::Expression* expression_in)
{
	std::stringstream stream;
	Expressions::TokenList_t tokens = expression_in->infix();
	for (auto token : tokens)
	{
		stream << token;
	}
	return stream.str();
}