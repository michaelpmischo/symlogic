// ============================================================================
//! @file ExpressionHandler.cpp
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
#include <UI/Core/Expressions/ExpressionHandler.h>
#include <Expressions/Operands/Constant.h>
#include <Expressions/Operands/Number.h>
#include <UI/Core/Terminal.h>
#include <limits>

Mathematics::UI::Core::ExpressionHandler* 
Mathematics::UI::Core::ExpressionHandler::singleton(0);


//  __________________________________________________________________________
// |                                                                          |
// | Class: ExpressionHandler                                                 |
// | Function: instance                                                       |
// |__________________________________________________________________________|
Mathematics::UI::Core::ExpressionHandler*
Mathematics::UI::Core::ExpressionHandler::instance()
{
	if (!singleton)
	{
		singleton = new ExpressionHandler();
	}
	return singleton;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: ExpressionHandler                                                 |
// | Function: instance                                                       |
// |__________________________________________________________________________|
void Mathematics::UI::Core::ExpressionHandler::handle(
		const std::string& raw_expression_in)
{
	Expressions::Expression* parsed_expression = 
			this->parser.parse(raw_expression_in);
	this->expressions.push_back(parsed_expression);
	std::stringstream stream;
	stream << std::endl << parsed_expression->pretty_tree();
	Terminal::instance()->output(stream.str());
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: ExpressionHandler                                                 |
// | Function: add                                                            |
// |__________________________________________________________________________|
void Mathematics::UI::Core::ExpressionHandler::add(
	const std::string& variable_in, const std::string& value_in)
{
	std::stringstream stream;
	Real value;
	if (Expressions::Operands::Constant::is_token(value_in))
	{
		value = Expressions::Operands::Constant::value(value_in);
	}
	else if(Expressions::Operands::Number::is_token(value_in))
	{
		value = std::stold(value_in);
	}
	else
	{
		stream << "Not a Value: " << value_in;
		Terminal::instance()->output(stream.str());
		return;
	}

	Expressions::TokenValueMap_t::iterator iter = 
			this->variables.find(variable_in);
	stream.precision(std::numeric_limits<Real>::max_digits10);
	if (iter != this->variables.end())
	{
		stream << "Set: " << variable_in << " = " << value;
		Terminal::instance()->output(stream.str());
		iter->second = value;
	}
	else
	{
		stream << "Set: " << variable_in << " = " << value;
		Terminal::instance()->output(stream.str());
		this->variables.insert({ variable_in, value });
	}
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: ExpressionHandler                                                 |
// | Function: remove                                                         |
// |__________________________________________________________________________|
void Mathematics::UI::Core::ExpressionHandler::remove(
		const std::string& variable_in)
{
	this->variables.erase(variable_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: ExpressionHandler                                                 |
// | Function: remove                                                         |
// |__________________________________________________________________________|
void Mathematics::UI::Core::ExpressionHandler::remove(size_t index_in)
{
	std::stringstream stream;
	if (index_in < this->expressions.size())
	{
		this->expressions.erase(
			std::next(this->expressions.begin(), index_in));
	}
	else
	{
		stream << "Expression: " << index_in << " does not exist!";
		Terminal::instance()->output(stream.str());
		this->list();
	}
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: ExpressionHandler                                                 |
// | Function: solve                                                          |
// |__________________________________________________________________________|
void Mathematics::UI::Core::ExpressionHandler::solve(
	size_t index_in) const
{
	std::stringstream stream;
	if (index_in < this->expressions.size())
	{
		Real solution = this->expressions[index_in]->solution(
				this->variables);

		if (std::isnan(solution))
		{
			stream << "Undefined";
		}
		else if (std::isinf(solution))
		{
			if (solution < 0.0)
			{
				stream << "-\xEC"; // -infinity 
			}
			else
			{
				stream << "+\xEC"; // +infinity
			}
			
		}
		else
		{
			stream.precision(std::numeric_limits<Real>::max_digits10);
			stream << solution;
		}
		Terminal::instance()->output(stream.str());
	}
	else
	{
		stream << "Expression: " << index_in << " does not exist!";
		Terminal::instance()->output(stream.str());
		this->list();
	}
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: ExpressionHandler                                                 |
// | Function: list                                                           |
// |__________________________________________________________________________|
void Mathematics::UI::Core::ExpressionHandler::list() const
{
	size_t i = 0U;
	std::stringstream stream;
	stream << std::endl;
	stream << "Expressions: " << std::endl;
	for (auto expression : this->expressions)
	{
		Expressions::TokenList_t tokens = expression->infix();
		stream << "[" << i << "] ";
		for (auto token : tokens)
		{
			stream << token;
		}
		stream << std::endl;
		i++;
	}

	i = 0U;
	stream << std::endl;
	stream << "Variables: " << std::endl;
	for (auto variable : this->variables)
	{
		stream << "[" << i << "] " << variable.first <<
			" = " << variable.second;
		i++;
	}
	Terminal::instance()->output(stream.str());
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: ExpressionHandler                                                 |
// | Function: clear                                                          |
// |__________________________________________________________________________|
void Mathematics::UI::Core::ExpressionHandler::clear()
{
	this->expressions.clear();
	this->variables.clear();
}
