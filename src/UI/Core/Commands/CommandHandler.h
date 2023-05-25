// ============================================================================
//! @file CommandHandler.h
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
#ifndef __MATHEMATICS_UI_CORE_COMMANDHANDLER_H_
#define __MATHEMATICS_UI_CORE_COMMANDHANDLER_H_
#include <string>
#include <set>
#include <map>
#include <deque>

namespace Mathematics
{
namespace UI
{
namespace Core
{

//  __________________________________________________________________________
// |                                                                          |
// |                                                                          |
// |                               CommandHandler                             |
// |                                                                          |
// |__________________________________________________________________________|
// 
// --------------------------------- Description ------------------------------
//! @brief
// ____________________________________________________________________________
class CommandHandler
{
public:
	static CommandHandler* instance();

	void handle(const std::string& line_in);

	~CommandHandler() = default;

private:
	typedef struct
	{
		std::string string;
		size_t		location;
	} StringInfo_t;

	typedef std::deque<StringInfo_t> StringInfos_t;
	typedef struct
	{
		StringInfo_t command;
		StringInfos_t arguments;
	} CommandInfo_t;

	typedef std::deque<CommandInfo_t> CommandInfos_t;
	typedef struct
	{
		StringInfo_t line;
		CommandInfos_t commands;
	} CommandsInfo_t;

	CommandHandler() = default;

	void process_commands(const CommandsInfo_t& commands_in) const;
	void process_command(const CommandInfo_t& command_in) const;

	void set(const CommandInfo_t& command_in) const;
	void unset(const CommandInfo_t& command_in) const;
	void solve(const CommandInfo_t& command_in) const;
	void solvefor(const CommandInfo_t& command_in) const;
	void quit() const;
	void help() const;

	void syntax_error(std::string explanation_in, 
		size_t location_in) const;

	// Preprocessing Command Inputs
	CommandsInfo_t parse(const std::string& line_in) const;
	CommandInfo_t parse_command(const std::string& command_in,
		size_t location_in) const;
	StringInfos_t parse_arguments(const std::string& arguments_in,
		size_t location_in) const;

	// String Manipulations.
	StringInfos_t split(std::string command_in,
		const std::string& delimeter_in = " ",
		size_t location_in = 0U) const;
	std::string replace(std::string command_in, 
		const std::string& token_in = " ") const;
	std::string strip(std::string command_in,
		const std::string& token_in = " ") const;

	//std::deque<std::string>	history;

	static const std::map<std::string, std::string> COMMANDS;
	static CommandHandler* singleton;

	std::string line;
}; // class CommandHandler
} // namespace Core
} // namespace UI
} // namespace Mathematics

#endif // __MATHEMATICS_UI_CORE_COMMANDHANDLER_H_