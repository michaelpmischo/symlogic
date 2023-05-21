// ============================================================================
//! @file Test.cpp
//! @author Michael P. MIscho
//! @date May 4, 2023
//! @brief This file is the header for the Integer number type header.
//! @see 
// ____________________________________________________________________________
//! @copyright Copyright (C) 2023 Michael P, Mischo - All Rights Reserved
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
#include <Test.h>

Mathematics::Tests::Test::Test(const Expressions::Token_t& log_name) :
	total(0U),
	passed(0U),
	test_number(0U)
{
	this->log.open(log_name, std::wostream::out | std::wostream::trunc);
	if (!this->log.is_open())
	{
		std::cerr << "Failed to open the test log." << std::endl;
	}
	this->reset();
}

Mathematics::Tests::Test::~Test()
{
	this->log.close();
}

Mathematics::float64_t Mathematics::Tests::Test::grade() const
{
	if (this->total > 0)
	{
		return static_cast<float64_t>(this->passed) /
			static_cast<float64_t>(this->total) *
			100.0;
	}
	else
	{
		return 0.0;
	}

}

void Mathematics::Tests::Test::summary(Expressions::TokenOutputStream_t& stream) const
{
	stream << DIVIDER0 << std::endl;
	stream << "Test Results Summary" << std::endl;
	uint64_t test_number = 0U;
	for (auto test : this->results)
	{
		stream << std::endl << DIVIDER2 << std::endl;
		stream << "Test Case #" << test_number++ << " results: " << std::endl;
		for (auto result: test)
		{
			stream << result << std::endl;
		}
	}
	stream << std::endl << DIVIDER2 << std::endl;
	stream << "Total Passed: " << this->passed << std::endl;
	stream << "Total Run   : " << this->total << std::endl;
	stream << "Overall     : " << this->grade() << "%" << std::endl;
	stream << DIVIDER0 << std::endl;
	stream << std::endl;
	stream << std::endl;
}
