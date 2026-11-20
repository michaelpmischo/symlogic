// ____________________________________________________________________________
//! @file Version.h
//! @author Michael P. MIscho
//! @date May 20, 2023
//! @brief
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
//! https://www.gnu.org/licenses/
// ____________________________________________________________________________
#ifndef __MATHEMATICS_VERSION_H_
#define __MATHEMATICS_VERSION_H_

namespace Mathematics
{
	namespace Version
	{
		const uint8_t MAJOR = 0U;
		const uint8_t MINOR = 0U;
		const uint16_t REVISION = 3U;
	}
#if defined(_WIN32)
	const std::string PLATFORM = "Microsoft Windows (32-bit)";
#elif defined(_WIN64)
	const std::string PLATFORM = "Microsoft Windows (64-bit)";
#else
	const std::string PLATFORM = "Linux (64-bit)";
#endif
	
} // namespace Mathematics

#endif // __MATHEMATICS_VERSION_H_