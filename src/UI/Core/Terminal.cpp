// ============================================================================
//! @file Terminal.cpp
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
#include <UI/Core/Terminal.h>
#include <UI/Core/Commands/CommandHandler.h>
#include <UI/Core/Expressions/ExpressionHandler.h>
#include <Exceptions/Commands/Syntax.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

Mathematics::UI::Core::Terminal* Mathematics::UI::Core::Terminal::singleton(0);

//  __________________________________________________________________________
// |                                                                          |
// | Class: Terminal                                                          |
// | Function: instance                                                       |
// |__________________________________________________________________________|
Mathematics::UI::Core::Terminal* Mathematics::UI::Core::Terminal::instance()
{
	if (!singleton)
	{
		singleton = new Terminal();
	}
	return singleton;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Terminal                                                          |
// | Function: run                                                            |
// |__________________________________________________________________________|
int Mathematics::UI::Core::Terminal::run()
{
	std::time_t now = std::time(0);
	std::cout << this->name() << std::endl <<
		std::asctime(std::localtime(&now));
	while (true)
	{
		std::string input;

		// Prompt for new input.
		std::cout << std::endl << "[" << count << "]" << input_prompt;
		std::getline(std::cin, input);

		try
		{
			CommandHandler::instance()->handle(input);
			count++;
		}
		catch (Syntax& error)
		{
			this->output(error.what());
		}
		
	}
	this->exit_failure();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Terminal                                                          |
// | Function: exit_success                                                   |
// |__________________________________________________________________________|
int Mathematics::UI::Core::Terminal::exit_success()
{
	std::exit(EXIT_SUCCESS);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Terminal                                                          |
// | Function: exit_failure                                                   |
// |__________________________________________________________________________|
int Mathematics::UI::Core::Terminal::exit_failure()
{
	std::exit(EXIT_FAILURE);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Terminal                                                          |
// | Function: output                                                         |
// |__________________________________________________________________________|
void Mathematics::UI::Core::Terminal::output(const std::string& output_in)
{
	std::cout << std::endl << "[" << count << "]" << this->output_prompt;
	std::cout << output_in << std::endl;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Terminal                                                          |
// | Function: Destructor                                                     |
// |__________________________________________________________________________|
Mathematics::UI::Core::Terminal::~Terminal()
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Terminal                                                          |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::UI::Core::Terminal::Terminal() :
	count(0)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Terminal                                                          |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
std::string Mathematics::UI::Core::Terminal::name() const
{
	return "Symbolic Mathematics Core Terminal Version 0.0.1";
}