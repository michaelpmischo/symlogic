// ============================================================================
//! @file CommandHandler.cpp
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
#include <UI/Core/Commands/CommandHandler.h>
#include <UI/Core/Expressions/ExpressionHandler.h>
#include <Exceptions/Commands/Syntax.h>
#include <UI/Core/Terminal.h>
#include <regex>
#include <iomanip>

Mathematics::UI::Core::CommandHandler* 
Mathematics::UI::Core::CommandHandler::singleton(0);

const std::map<std::string, std::string>
Mathematics::UI::Core::CommandHandler::COMMANDS =
{
	// Variable and Value Commands
	{ "set",			"set a variable value with a value. set(VARIABLE=VALUE)" },
	{ "unset",			"unset a variable value. unset(VARIABLE)" },

	// Expressions Commands
	{ "solve",			"solve an expression with the existing variable values. solve(EXPRESSION)" },
	{ "solvefor",		"solve an expression with the provided variable values. solvefor(EXPRESSION, VARIABLE=VALUE,[VARAIBLE=VALUE]...)" },
	{ "derivative",		"print the derivative of an expression. derivative(EXPRESSION)" },
	{ "integral",		"print the indefinite integral of an expression. integral(EXPRESSION)" },
	{ "simplify",		"print the simplified version of an expression. simplify(EXPRESSION)" },

	{ "clear",			"clear the existing variables and expressions" },
	{ "list",			"print a list of the stored expressions and variable values." },
	{ "save",			"save the current set of expressions and variable values to a file. save(FILENAME)" },
	{ "load",			"load a set of expressions and variable values from a file. load(FILENAME)" },

	{ "help",			"print this help." },
	{ "quit",			"quit the Mathematics Core terminal." },
	{ "exit",			"same as quit." },
};


//  __________________________________________________________________________
// |                                                                          |
// | Class: CommandHandler                                                    |
// | Function: instance                                                       |
// |__________________________________________________________________________|
Mathematics::UI::Core::CommandHandler* 
Mathematics::UI::Core::CommandHandler::instance()
{
	if (!singleton)
	{
		singleton = new CommandHandler();
	}
	return singleton;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: CommandHandler                                                    |
// | Function: handle                                                         |
// |__________________________________________________________________________|
void Mathematics::UI::Core::CommandHandler::handle(
		const std::string& line_in)
{
	this->line = line_in;
	CommandsInfo_t commands = this->parse(line_in);
	this->process_commands(commands);
}

//  __________________________________________________________________________
// |                                                                          |
// | Class: CommandHandler                                                    |
// | Function: process_commands                                               |
// |__________________________________________________________________________|
void Mathematics::UI::Core::CommandHandler::process_commands(
	const CommandsInfo_t& commands_in) const
{
	// Process the queue of commands.
	for (auto command : commands_in.commands)
	{
		this->process_command(command);
	}
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: CommandHandler                                                    |
// | Function: process_command                                                |
// |__________________________________________________________________________|
void Mathematics::UI::Core::CommandHandler::process_command(
	const CommandInfo_t& command_info_in) const
{
	// If this is not a command. Then we assume it is an expression.
	if (COMMANDS.find(command_info_in.command.string) == COMMANDS.end())
	{
		ExpressionHandler::instance()->handle(command_info_in.raw);
	}

	else if (command_info_in.command.string == "set")
	{
		this->set(command_info_in);
	}
	else if (command_info_in.command.string == "unset")
	{
		this->unset(command_info_in);
	}

	else if (command_info_in.command.string == "solve")
	{
		this->solve(command_info_in);
	}
	else if (command_info_in.command.string == "solvefor")
	{
		this->solvefor(command_info_in);
	}
	else if (command_info_in.command.string == "clear")
	{
		ExpressionHandler::instance()->clear();
	}
	else if (command_info_in.command.string == "list")
	{
		ExpressionHandler::instance()->list();
	}
	else if (command_info_in.command.string == "save")
	{
	}
	else if (command_info_in.command.string == "load")
	{
	}
	else if (command_info_in.command.string == "help")
	{
		this->help();
	}
	else if (command_info_in.command.string == "quit" ||
		command_info_in.command.string == "exit")
	{
		Terminal::instance()->exit_success();
	}
	else
	{
		//TODO -- ERROR.	
	}
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: CommandHandler                                                    |
// | Function: set                                                            |
// |__________________________________________________________________________|
void Mathematics::UI::Core::CommandHandler::set(
	const CommandInfo_t& command_info_in) const
{
	if (!command_info_in.arguments.empty())
	{
		for (auto argument : command_info_in.arguments)
		{
			// Split at the equals sign.
			std::deque<StringInfo_t> split = 
				this->split(argument.string, "=");
			if (split.size() == 2)
			{
				ExpressionHandler::instance()->add(
					split[0].string, split[1].string);
			}
			else
			{
				// TODO -- Throw an error.
				this->syntax_error("Argument for \"set\" must use the "
					"form VARIABLE \"=\" VALUE",
					argument.location);
				return;
			}
		}
	}
	else
	{
		// TODO -- Throw an error...
		this->syntax_error("No arguments provided for \"set\"",
			command_info_in.command.location);
	}
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: CommandHandler                                                    |
// | Function: set                                                            |
// |__________________________________________________________________________|
void Mathematics::UI::Core::CommandHandler::unset(
	const CommandInfo_t& command_info_in) const
{
	if (!command_info_in.arguments.empty())
	{
		for (auto argument : command_info_in.arguments)
		{
			ExpressionHandler::instance()->remove(argument.string);
		}
	}
	else
	{
		// TODO -- Throw an Error...
		this->syntax_error("No arguments provided for \"unset\"",
			command_info_in.command.location);
	}
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: CommandHandler                                                    |
// | Function: solve                                                          |
// |__________________________________________________________________________|
void Mathematics::UI::Core::CommandHandler::solve(
	const CommandInfo_t& command_info_in) const
{
	if (!command_info_in.arguments.empty())
	{
		for (auto argument : command_info_in.arguments)
		{
			// Ensure the argument is an integer value.
			if (argument.string.find_first_not_of("0123456789") ==
				std::string::npos)
			{
				ExpressionHandler::instance()->solve(
					std::stoul(argument.string));
			}
			else
			{
				// TODO -- Throw an error...
				this->syntax_error(
					"Argument provided for \"solve\" is not an integer index.",
					argument.location);
				return;
			}
		}
	}
	else
	{
		// TODO -- Throw an Error ...
		this->syntax_error("No arguments provided for \"solve\"",
			command_info_in.command.location);
	}
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: CommandHandler                                                    |
// | Function: solvefor                                                       |
// |__________________________________________________________________________|
void Mathematics::UI::Core::CommandHandler::solvefor(
		const CommandInfo_t& command_info_in) const
{
	if (!command_info_in.arguments.empty())
	{
		// Create a new command for the set portion of this command.
		CommandInfo_t set_command;
		std::deque<StringInfo_t> arguments = command_info_in.arguments;
		arguments.pop_front();
		set_command.command = { "set", command_info_in.command.location };
		set_command.arguments = arguments;

		// Set the Variables.
		this->set(set_command);

		// Create a new command for the solve command.
		CommandInfo_t solve_command;
		solve_command.command = { "solve", command_info_in.command.location };
		solve_command.arguments = { {command_info_in.arguments[0]} };

		// Solve the expression.
		this->solve(solve_command);
	}
	else
	{
		// TODO -- Raise an error. 
		this->syntax_error("No arguments provided for \"solvefor\"",
			command_info_in.command.location);
	}
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: CommandHandler                                                    |
// | Function: help                                                           |
// |__________________________________________________________________________|
void Mathematics::UI::Core::CommandHandler::help() const
{
	std::stringstream stream;
	stream << Terminal::instance()->name() << std::endl;
	stream << " --- Available Commands: " << std::endl;
	stream << std::setiosflags(std::ios::left) << std::setw(20) << 
		"Command" << "| " << "Description" << std::endl;
	stream << "____________________|_______________________________"
		"____________________________" << std::endl;
	for (auto com : COMMANDS)
	{
		std::string description = com.second;
		bool first = true;
		while (!description.empty())
		{
			if (first)
			{
				stream << std::setiosflags(std::ios::left) << 
					std::setw(20) << com.first;
				first = false;
			}
			else
			{
				stream << std::setiosflags(std::ios::left) << 
					std::setw(20) << " ";
			}
			stream << "| " << std::setiosflags(std::ios::left) << 
				std::setw(20) << description.substr(0, 58);
			description.erase(0, 58);
			stream << std::endl;
		}

	}
	Terminal::instance()->output(stream.str());
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: CommandHandler                                                    |
// | Function: parse                                                          |
// |__________________________________________________________________________|
Mathematics::UI::Core::CommandHandler::CommandsInfo_t
Mathematics::UI::Core::CommandHandler::parse(const std::string& line_in) const
{
	CommandsInfo_t commands;
	commands.line.string = line_in;
	commands.line.location = 0U;

	std::deque<StringInfo_t> split_commands = this->split(line_in, "&&");
	for (auto command : split_commands)
	{
		commands.commands.push_back(this->parse_command(command.string, 
			command.location));
	}
	return commands;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: CommandHandler                                                    |
// | Function: parse_command                                                  |
// |__________________________________________________________________________|
Mathematics::UI::Core::CommandHandler::CommandInfo_t
Mathematics::UI::Core::CommandHandler::parse_command(
		const std::string& command_in, size_t location_in) const
{
	CommandInfo_t command;
	command.raw = command_in;
	
	// An open parentheses indicates arguments are provided.
	size_t arguments_begin = command_in.find_first_of("(");

	// If this command contains arguments, then we must parse those as well.
	if (arguments_begin != std::string::npos)
	{
		// Put the command on the output after striping all the spaces.
		command.command.string = this->strip(
			command_in.substr(0, arguments_begin));
		command.command.location = location_in + 
			command_in.find_first_not_of(" ");

		// Strip the first open parentheses.
		std::string arguments = command_in.substr(
				arguments_begin + 1, std::string::npos);

		// And the close parentheses.
		size_t arguments_end = arguments.find_last_of(")");
		if (arguments_end != std::string::npos)
		{
			arguments.erase(arguments_end, std::string::npos);
		}
		else
		{
			// throw an error... "No closing parentheses for command."
			std::stringstream stream;
			stream << "No closing parentheses for call to \"" <<
				command.command.string << "\"";
			this->syntax_error(stream.str(),
				command.command.location);
		}

		// Split the arguments at the commas.
		command.arguments = this->parse_arguments(arguments, 
			location_in + arguments_begin + 1);
	}
	else
	{
		// This command has no arguments so the command should be striped 
		// of whitespace and returned.
		command.command = { this->strip(command_in), 
			location_in + command_in.find_first_not_of(" ")};
	}
	return command;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: CommandHandler                                                    |
// | Function: parse_arguments                                                |
// |__________________________________________________________________________|
Mathematics::UI::Core::CommandHandler::StringInfos_t 
Mathematics::UI::Core::CommandHandler::parse_arguments(
	const std::string& arguments_in,
	size_t location_in) const
{
	StringInfos_t arguments;
	StringInfos_t split_arguments = this->split(arguments_in, ",", location_in);

	for (auto argument : split_arguments)
	{
		arguments.push_back({ this->strip(argument.string), 
			argument.location +
			argument.string.find_first_not_of(" ") });
	}
	return arguments;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: CommandHandler                                                    |
// | Function: syntax_error                                                   |
// |__________________________________________________________________________|
void Mathematics::UI::Core::CommandHandler::syntax_error(
		std::string explanation_in, size_t location_in) const
{
	throw Syntax(explanation_in, this->line, location_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: CommandHandler                                                    |
// | Function: split                                                          |
// |__________________________________________________________________________|
std::deque<Mathematics::UI::Core::CommandHandler::StringInfo_t>
Mathematics::UI::Core::CommandHandler::split(std::string string_in,
	const std::string& delimiter_in,
	size_t location_in) const
{
	std::deque<StringInfo_t> strings;
	size_t location = location_in;
	for (size_t i = 0; i != std::string::npos; )
	{
		// Find the next delimiter index
		i = string_in.find(delimiter_in);

		// Get the substring up to the next delimiter.
		std::string substring = string_in.substr(0, i);

		// If the substring is not "", then add it to the output.
		if (!substring.empty())
		{
			strings.push_back({ substring, location });
		}

		// Erase the substring and the next delimiter from the original 
		// string. (We can modify the passed in string since is a copy.
		string_in.erase(0, i + delimiter_in.length());

		location += i + delimiter_in.length();
	}
	return strings;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: CommandHandler                                                    |
// | Function: replace                                                        |
// |__________________________________________________________________________|
std::string Mathematics::UI::Core::CommandHandler::replace(
		std::string string_in,
		const std::string& token_in) const
{
	string_in = std::regex_replace(string_in, std::regex(token_in), "");
	return string_in;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: CommandHandler                                                    |
// | Function: strip                                                          |
// |__________________________________________________________________________|
std::string Mathematics::UI::Core::CommandHandler::strip(
	std::string string_in,
	const std::string& token_in) const
{
	size_t start = string_in.find_first_not_of(token_in);
	string_in.erase(0, start);
	size_t end = string_in.find_last_not_of(token_in);
	string_in.erase(end + 1, std::string::npos);
	return string_in;
}