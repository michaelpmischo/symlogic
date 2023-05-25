// ============================================================================
//! @file Definitions.h
//! @author Michael P. MIscho
//! @date May 12, 2023
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
#ifndef __MATHEMATICS_DEFINITIONS_H_
#define __MATHEMATICS_DEFINITIONS_H_
#include <fcntl.h>
#include <stdio.h>
#include <io.h>

#if defined(__WCHAR_EXPRESSIONS__)
  #ifndef __WCHAR_IO__
    #define __WCHAR_IO__
  #endif
  #define LITERAL_PREFIX L
  // Change the standard cout to the 16-bit character cout.
  #ifndef __SETMODE__
    #ifdef _WIN32
      #define __SETMODE__ _setmode(_fileno(stdout), _O_WTEXT); \
                          _setmode(_fileno(stdin), _O_WTEXT); \
                          _setmode(_fileno(stderr), _O_WTEXT);
    #else
      #define __SETMODE__
    #endif
  #endif
#elif defined(__UTF32_EXPRESSIONS__)
  #ifndef __UTF32_IO__
    #define __UTF32_IO__
  #endif
  #define LITERAL_PREFIX U
  // Change the standard cout to the 16-bit character cout.
  #ifndef __SETMODE__
    #ifdef _WIN32
      #error Error: Windows does not currently support 32-bit \
                    Unicode in the Console!
      #define __SETMODE__ _setmode(_fileno(stdout), _O_U32TEXT); \
                          _setmode(_fileno(stdin), _O_U32TEXT); \
                          _setmode(_fileno(stderr), _O_U32TEXT);
    #else
      #define __SETMODE__
    #endif
  #endif
#elif defined(__UTF16_EXPRESSIONS__)
  #ifndef __UTF16_IO__
    #define __UTF16_IO__
  #endif
  #define LITERAL_PREFIX u
  // Change the standard cout to the 16-bit character cout.
  #ifndef __SETMODE__
    #ifdef _WIN32
      #define __SETMODE__ _setmode(_fileno(stdout), _O_U16TEXT); \
                          _setmode(_fileno(stdin), _O_U16TEXT); \
                          _setmode(_fileno(stderr), _O_U16TEXT);
    #else
      #define __SETMODE__
    #endif
  #endif
#elif defined(__UTF8_EXPRESSIONS__)
  #define LITERAL_PREFIX u8
  #ifndef __SETMODE__
    #ifdef _WIN32
      #define __SETMODE__ _setmode(_fileno(stdout), _O_U8TEXT); \
                          _setmode(_fileno(stdin), _O_U8TEXT); \
                          _setmode(_fileno(stderr), _O_U8TEXT);
    #else
      #define __SETMODE__
    #endif
  #endif
#else
  #define LITERAL_PREFIX
  #ifndef __SETMODE__
    #define __SETMODE__
  #endif
#endif

#ifndef __SETWMODE__
  #ifdef _WIN32
    #define __SETWMODE__ _setmode(_fileno(stdout), _O_WTEXT); \
                         _setmode(_fileno(stdin), _O_WTEXT); \
                         _setmode(_fileno(stderr), _O_WTEXT);
  #else
    #define __SETWMODE__
  #endif
#endif

#ifndef __UNSETWMODE__
  #ifdef _WIN32
    #define __UNSETWMODE__ _setmode(_fileno(stdout), _O_TEXT); \
                           _setmode(_fileno(stdin), _O_TEXT); \
                           _setmode(_fileno(stderr), _O_TEXT);
  #else
    #define __UNSETWMODE__
  #endif
#endif


#endif // __MATHEMATICS_DEFINITIONS_H_

