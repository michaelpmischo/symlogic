// ============================================================================
//! @file Tokens.h
//! @author Michael P. MIscho
//! @date May 15, 2023
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
#ifndef __MATHEMATICS_EXPRESSIONS_TOKENS_H_
#define __MATHEMATICS_EXPRESSIONS_TOKENS_H_
#include <Types.h>		        // Real, Imaginary, Integer, Natural, etc...
#include <string>				// std::wstring
#include <list>					// std::list
#include <set>					// std::set
#include <map>					// std::map
#include <iostream>				// std::wostream
#include <sstream>				// std::wstringsyream

namespace Mathematics
{
namespace Expressions
{
#if defined(__WCHAR_EXPRESSIONS__)
  // Generic Token. This is a Unicode string for use with the Unicode 
  // mathematics characters 'u2200' - 'u22FF'.
  typedef std::basic_string<wchar_t>			Token_t;

  // Token Streams for easy I/O.
  typedef std::basic_stringstream<wchar_t>		TokenStream_t;
  typedef std::basic_istream<wchar_t>			TokenInputStream_t;
  typedef std::basic_ostream<wchar_t>			TokenOutputStream_t;

#elif defined(__UTF32_EXPRESSIONS__)
  // Generic Token. This is a Unicode string for use with the Unicode 
  // mathematics characters 'u2200' - 'u22FF'.
  typedef std::basic_string<char32_t>			Token_t;

  // Token Streams for easy I/O.
  typedef std::basic_stringstream<char32_t>		TokenStream_t;
  typedef std::basic_istream<char32_t>			TokenInputStream_t;
  typedef std::basic_ostream<char32_t>			TokenOutputStream_t;

#elif defined(__UTF16_EXPRESSIONS__)
  // Generic Token. This is a Unicode string for use with the Unicode 
  // mathematics characters 'u2200' - 'u22FF'.
  typedef std::basic_string<char16_t>			Token_t;

  // Token Streams for easy I/O.
  typedef std::basic_stringstream<char16_t>	    TokenStream_t;
  typedef std::basic_istream<char16_t>		    TokenInputStream_t;
  typedef std::basic_ostream<char16_t>		    TokenOutputStream_t;

#else //  __UTF8_EXPRESSIONS__
  typedef std::basic_string<char>		        Token_t;

  // Token Streams for easy I/O.
  typedef std::basic_stringstream<char>	        TokenStream_t;
  typedef std::basic_istream<char>			    TokenInputStream_t;
  typedef std::basic_ostream<char>			    TokenOutputStream_t;
#endif

// A token's precedence in order of operations.
typedef uint8_t TokenPrecedence_t;
typedef std::map<Token_t, TokenPrecedence_t> PrecedenceHash_t;


//  __________________________________________________________________________
// |                                                                          |
// |                                                                          |
// |                                 TokenPair_t                              |
// |                                                                          |
// |__________________________________________________________________________|
// 
// --------------------------------- Description ------------------------------
//! @brief A generic Pair of tokens. This is a common element in the token 
//! types.
// ____________________________________________________________________________
typedef std::pair<Token_t, Token_t>				TokenPair_t;
inline TokenOutputStream_t& operator<<(TokenOutputStream_t& stream,
    const TokenPair_t& rhs)
{
    stream << "<" << rhs.first << "," << rhs.second << L">";
    return stream;
}

//  __________________________________________________________________________
// |                                                                          |
// |                                                                          |
// |                              TokenValuePair_t                            |
// |                                                                          |
// |__________________________________________________________________________|
// 
// --------------------------------- Description ------------------------------
//! @brief A Pair of tokens with their numeric values. This is a common element 
//! in the token types. This is used for providing value information 
//! for a set of unknown tokens in an expression.
// ____________________________________________________________________________
typedef std::pair<Token_t, Real>				TokenValuePair_t;
inline TokenOutputStream_t& operator<<(TokenOutputStream_t& stream,
    const TokenValuePair_t& rhs)
{
    stream << "<" << rhs.first << "=" << rhs.second << L">";
    return stream;
}


//  __________________________________________________________________________
// |                                                                          |
// |                                                                          |
// |                                 TokenList_t                              |
// |                                                                          |
// |__________________________________________________________________________|
// 
// --------------------------------- Description ------------------------------
//! @brief A generic Token List. This is a basic ordered list Type used in the  
//! Mathematics Library.
// ____________________________________________________________________________
typedef std::list<Token_t>						TokenList_t;
inline TokenOutputStream_t& operator<<(TokenOutputStream_t& stream,
    const TokenList_t& rhs)
{
    Token_t separator = L"";
    for (auto token : rhs)
    {
        stream << separator << L"<" << token << L">";
        separator = L",";
    }
    return stream;
}


//  __________________________________________________________________________
// |                                                                          |
// |                                                                          |
// |                                  TokenSet_t                              |
// |                                                                          |
// |__________________________________________________________________________|
// 
// --------------------------------- Description ------------------------------
//! @brief A generic Token Set. An unordered collection of easy to search 
//! tokens.
// ____________________________________________________________________________
typedef std::set<Token_t>						TokenSet_t;
inline TokenOutputStream_t& operator<<(TokenOutputStream_t& stream,
    const TokenSet_t& rhs)
{
    Token_t separator = L"";
    for (auto token : rhs)
    {
        stream << separator << L"<" << token << L">";
        separator = L",";
    }
    return stream;
}


//  __________________________________________________________________________
// |                                                                          |
// |                                                                          |
// |                                  TokenMap_t                              |
// |                                                                          |
// |__________________________________________________________________________|
// 
// --------------------------------- Description ------------------------------
//! @brief A generic Token Map. This is an unordered collection of Tokens that 
//! are in pairs relating to other tokens.
// ____________________________________________________________________________
typedef std::map<Token_t, Token_t>				TokenMap_t;
inline TokenOutputStream_t& operator<<(TokenOutputStream_t& stream,
    const TokenMap_t& rhs)
{
    Token_t separator = L"";
    for (auto token : rhs)
    {
        stream << separator << token;
        separator = L",";
    }
    return stream;
}


//  __________________________________________________________________________
// |                                                                          |
// |                                                                          |
// |                               TokenValueMap_t                            |
// |                                                                          |
// |__________________________________________________________________________|
// 
// --------------------------------- Description ------------------------------
//! @brief A map of values for a certain token. This is commonly used for 
//! providing values for unknown tokens in an expression.
// ____________________________________________________________________________
typedef std::map<Token_t, Real>					TokenValueMap_t;
inline TokenOutputStream_t& operator<<(TokenOutputStream_t& stream,
    const TokenValueMap_t& rhs)
{
    Token_t separator = L"";
    for (auto token : rhs)
    {
        stream << separator << token;
        separator = L",";
    }
    return stream;
}

} // namespace Expressions
} // namespace Mathematics

#endif // __MATHEMATICS_EXPRESSIONS_TOKENS_H_