// ============================================================================
//! @file Test.h
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
//! but WITHstd::cout ANY WARRANTY; without even the implied warranty of
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
#ifndef __TEST_H_
#define __TEST_H_
#include <Types.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <deque>
#include <sstream>

namespace Mathematics
{
	static const std::string DIVIDER0("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
	static const std::string DIVIDER1("*******************************************************************************");
	static const std::string DIVIDER2("===============================================================================");
	static const std::string DIVIDER3("-------------------------------------------------------------------------------");
	static const std::string DIVIDER4("_______________________________________________________________________________");
	static const std::string DIVIDER5("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	static const std::string VERIFY(" --- Verifying ...");
	static const std::string PASS(" --- PASSED --- ");
	static const std::string FAIL(" --- FAILED --- ");

class Test
{
public:
	Test(const std::string& log_name = "test.log");
	virtual void run() = 0;

	float64_t grade() const;
	void summary(std::ostream& steam) const;

protected:
	typedef std::deque<std::deque<std::string>> Record_t;
	virtual ~Test();

	inline void reset();
	inline void begin_test();
	inline void end_test();
	inline void push_heading(const std::string& heading_in);

	template <typename T>
	void verify_eq(const T& a, const T& b);

	template<typename T>
	void verify_ne(const T& a, const T& b);

	template<typename T>
	void verify_lt(const T& a, const T& b);

	template<typename T>
	void verify_gt(const T& a, const T& b);

	void verify_true(bool a);
	void verify_false(bool a);

	std::ofstream log;
	Record_t results;

private:
	uint64_t total;
	uint64_t passed;

	uint64_t test_number;
}; // class Test
} // Namespace Mathematics

void Mathematics::Test::reset()
{
	this->total = this->passed = this->test_number = 0;
	this->results.clear();
}

void Mathematics::Test::begin_test()
{
	this->results.push_back({});
}

void Mathematics::Test::end_test()
{
	this->test_number++;
}

void Mathematics::Test::push_heading(const std::string& heading_in)
{
	this->results[this->test_number].push_back(heading_in);
}

template <typename T>
void Mathematics::Test::verify_eq(const T& a, const T& b)
{
	std::stringstream stream;
	std::cout << VERIFY << std::endl;
	this->total++;
	if (a == b)
	{
		stream << PASS << "[" << a << " == " << b << "]";
		this->passed++;
	}
	else
	{
		stream << FAIL << "[" << a << " == " << b << "]" ;
	}
	this->results[this->test_number].push_back(stream.str());
	std::cout << stream.str() << std::endl << std::endl;
}

template<typename T>
void Mathematics::Test::verify_ne(const T& a, const T& b)
{
	std::stringstream stream;
	std::cout << VERIFY << std::endl;
	this->total++;
	if (a != b)
	{
		stream << PASS << "[" << a << " != " << b << "]";
		this->passed++;
	}
	else
	{
		stream << FAIL << "[" << a << " != " << b << "]";
	}
	this->results[this->test_number].push_back(stream.str());
	std::cout << stream.str() << std::endl << std::endl;
}

template<typename T>
void Mathematics::Test::verify_lt(const T& a, const T& b)
{
	std::stringstream stream;
	std::cout << VERIFY << std::endl;
	this->total++;
	if (a < b)
	{
		stream << PASS << "[" << a << " < " << b << "]";
		this->passed++;
	}
	else
	{
		stream << FAIL << "[" << a << " < " << b << "]";
	}
	this->results[this->test_number].push_back(stream.str());
	std::cout << stream.str() << std::endl << std::endl;
}

template<typename T>
void Mathematics::Test::verify_gt(const T& a, const T& b)
{
	std::stringstream stream;
	std::cout << VERIFY << std::endl;
	this->total++;
	if (a > b)
	{
		stream << PASS << "[" << a << " > " << b << "]";
		this->passed++;
	}
	else
	{
		stream << FAIL << "[" << a << " > " << b << "]";
	}
	this->results[this->test_number].push_back(stream.str());
	std::cout << stream.str() << std::endl << std::endl;
}


#endif // __TEST_UTILS_H_