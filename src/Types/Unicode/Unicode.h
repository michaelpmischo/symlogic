// ============================================================================
//! @file Unicode.h
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
#ifndef __MATHEMATICS_UNICODE_H_
#define __MATHEMATICS_UNICODE_H_
#include <Expressions/Tokens.h>

namespace Mathematics
{
namespace Expressions
{
const TokenMap_t AEITHMATIC_OPERATORS =
{
#if defined(__WCHAR_EXPRESSIONS__) || \
    defined(__UTF16_EXPRESSIONS__) || \
    defined(__UTF32_EXPRESSIONS__)
    { L"*",				    L"∙" },
    { L"/",				    L"÷" },
    { L"exp",			    L"ℯ^" },
    { L"nrt",               L"n\u221A" },
    { L"sqrt",			    L"\u221A" },
    { L"sum",			    L"\u2211" },        // Not Implemented
    { L"product",		    L"\u220F" },        // Not Implemented
    { L"coproduct",		    L"\u2210" },        // Not Implemented
#endif
}; // AEITHMATIC_OPERATORS


const TokenMap_t CALCULUS_OPERATORS =
{
#if defined(__WCHAR_EXPRESSIONS__) || \
    defined(__UTF16_EXPRESSIONS__) || \
    defined(__UTF32_EXPRESSIONS__)
	{ L"integral",          L"\u222B" },            // Not Implemented
	{ L"partial",		    L"\u2202\u2202?" },     // Not Implemented
#endif
}; // CALCULUS_OPERATORS

const TokenMap_t LOGICAL_OPERATORS =
{
#if defined(__WCHAR_EXPRESSIONS__) || \
    defined(__UTF16_EXPRESSIONS__) || \
    defined(__UTF32_EXPRESSIONS__)
    { L"~=",                L"\u2248" },
    { L"!=",                L"\u2260"},
	{ L">=",				L"\u2265" },
	{ L"=<",				L"\u2264"},
	{ L"and",			    L"\u2227"},     // Not Implemented
	{ L"or",				L"\u2228"},     // Not Implemented
	{ L"there_exists",      L"\u2203"},     // Not Implemented
	{ L"not_exists",        L"\u2204"},     // Not Implemented
#endif
}; // LOGICAL_OPERATORS

const TokenMap_t SET_OPERATORS =
{
#if defined(__WCHAR_EXPRESSIONS__) || \
    defined(__UTF16_EXPRESSIONS__) || \
    defined(__UTF32_EXPRESSIONS__)
    { L"intersection",	    L"\u2229" },    // Not Implemented
    { L"union",			    L"\u222A" },    // Not Implemented
    { L"subset",		    L"\u2282" },    // Not Implemented
    { L"superset",		    L"\u2283" },    // Not Implemented
    { L"not_subset",	    L"\u2284" },    // Not Implemented
    { L"not_superset",	    L"\u2285" },    // Not Implemented
    { L"element_of",		L"\u22F2" },    // Not Implemented
    { L"not_element_of",	L"\u2209" },    // Not Implemented
    { L"contain",		    L"\u22FA" },    // Not Implemented
    { L"not_constain",	    L"\u220C" },    // Not Implemented
    { L"for_all",		    L"\u2200" },    // Not Implemented
#endif
}; // SET_OPERATORS

const TokenMap_t SETS =
{
#if defined(__WCHAR_EXPRESSIONS__) || \
    defined(__UTF16_EXPRESSIONS__) || \
    defined(__UTF32_EXPRESSIONS__)
    {L"{}",				    L"\u2205"},     // The Empty Set
    {L"{REAL}",			    L"\u211D"},     // All Real Numbers
    {L"{NATURAL}",		    L"\u2115"},     // All Natural Numbers
    {L"{COMPLEX}",		    L"\u2102"},     // All Complex Numbers
    {L"{INTEGERS}",		    L"\u2124"},     // All Integer Numbers
    {L"{RATIONAL}",		    L"\u211A"},     // All Rational Numbers
#endif
}; // SETS

const TokenMap_t UNITS =
{
#if defined(__WCHAR_EXPRESSIONS__) || \
    defined(__UTF16_EXPRESSIONS__) || \
    defined(__UTF32_EXPRESSIONS__)
    {L"Ohms",			    L"\u2126"},
    {L"Celsius",		    L"\u2103"},
    {L"Fahrenheit",		    L"\u2109"},
#endif
}; // UNITS

const TokenMap_t GREEK =
{
#if defined(__WCHAR_EXPRESSIONS__) || \
    defined(__UTF16_EXPRESSIONS__)
	// Uppercase
    {L"ALPHA",		        L"\u0391"},
    {L"BETA",		        L"\u0392"},
    {L"GAMMA",		        L"\u0393"},
    {L"DELTA",		        L"\u0394"},
    {L"EPSILON",	        L"\u0395"},
    {L"ZETA",		        L"\u0396"},
    {L"ETA",		        L"\u0397"},
    {L"THETA",		        L"\u0398"},
    {L"IOTA",		        L"\u0399"},
    {L"KAPPA",		        L"\u039A"},
    {L"LAMBDA",		        L"\u039B"},
    {L"MU",			        L"\u039C"},
    {L"NU",			        L"\u039D"},
    {L"XI",			        L"\u039E"},
    {L"OMICRON",	        L"\u039F"},
    {L"PI",			        L"\u03A0"},
    {L"RHO",		        L"\u03A1"},
    {L"SIGMA",		        L"\u03A3"},
    {L"TAU",		        L"\u03A4"},
    {L"UPSILON",	        L"\u03A5"},
    {L"PHI",		        L"\u03A6"},
    {L"CHI",		        L"\u03A7"},
    {L"PSI",		        L"\u03A8"},
    {L"OMEGA",		        L"\u03A9"},

    // Lowercase
    {L"alpha",		        L"\u03B1"},
    {L"beta",		        L"\u03B2"},
    {L"gamma",		        L"\u03B3"},
    {L"delta",		        L"\u03B4"},
    {L"epsilon",	        L"\u03B5"},
    {L"zeta",		        L"\u03B6"},
    {L"eta",		        L"\u03B7"},
    {L"theta",		        L"\u03B8"},
    {L"iota",		        L"\u03B9"},
    {L"kappa",		        L"\u03BA"},
    {L"lambda",	            L"\u03BB"},
    {L"mL",			        L"\u03BC"},
    {L"nL",			        L"\u03BD"},
    {L"xi",			        L"\u03BE"},
    {L"omicron",	        L"\u03BF"},
    {L"pi",			        L"\u03C0"},
    {L"rho",		        L"\u03C1"},
    {L"sigma",		        L"\u03C3"},
    {L"taL",		        L"\u03C4"},
    {L"upsilon",	        L"\u03C5"},
    {L"phi",		        L"\u03C6"},
    {L"chi",		        L"\u03C7"},
    {L"psi",		        L"\u03C8"},
    {L"omega",		        L"\u03C9"},
#endif
#ifdef __UTF32_EXPRESSIONS__
    // Uppercase
    {U"ALPHA",		U"𝜜"},
    {U"BETA",		U"𝜝"},
    {U"GAMMA",		U"𝜞"},
    {U"DELTA",		U"𝜟"},
    {U"EPSILON",	U"𝜠"},
    {U"ZETA",		U"𝜡"},
    {U"ETA",		U"𝜢"},
    {U"THETA",		U"𝜣"},
    {U"IOTA",		U"𝜤"},
    {U"KAPPA",		U"𝜥"},
    {U"LAMBDA",		U"𝜦"},
    {U"MU",			U"𝜧"},
    {U"NU",			U"𝜨"},
    {U"XI",			U"𝜩"},
    {U"OMICRON",	U"𝜪"},
    {U"PI",			U"𝜫"},
    {U"RHO",		U"𝜬"},
    {U"SIGMA",		U"𝜮"},
    {U"TAU",		U"𝜯"},
    {U"UPSILON",	U"𝜰"},
    {U"PHI",		U"𝜱"},
    {U"CHI",		U"𝜲"},
    {U"PSI",		U"𝜳"},
    {U"OMEGA",		U"𝜴"},

    // Lowercase
	{U"alpha",		U"𝜶"},
	{U"beta",		U"𝜷"},
	{U"gamma",		U"𝜸"},
	{U"delta",		U"𝜹"},
	{U"epsilon",	U"𝜺"},
	{U"zeta",		U"𝜻"},
	{U"eta",		U"𝜼"},
	{U"theta",		U"𝜽"},
	{U"iota",		U"𝜾"},
	{U"kappa",		U"𝜿"},
	{U"lambda",	    U"𝝀"},
	{U"mL",			U"𝝁"},
	{U"nL",			U"𝝂"},
	{U"xi",			U"𝝃"},
	{U"omicron",	U"𝝄"},
	{U"pi",			U"𝝅"},
	{U"rho",		U"𝝆"},
	{U"sigma",		U"𝝈"},
	{U"taL",		U"𝝉"},
	{U"upsilon",	U"𝝊"},
	{U"phi",		U"𝝓"},
	{U"chi",		U"𝝌"},
	{U"psi",		U"𝝍"},
	{U"omega",		U"𝝎"},
#endif
}; // GREEK

inline Token_t replace(const Token_t& token_in)
{
    if (AEITHMATIC_OPERATORS.find(token_in) != 
            AEITHMATIC_OPERATORS.end())
    {
        return AEITHMATIC_OPERATORS.find(token_in)->second;
    }
	else if (CALCULUS_OPERATORS.find(token_in) !=
        CALCULUS_OPERATORS.end())
	{
		return CALCULUS_OPERATORS.find(token_in)->second;
	}
	else if (LOGICAL_OPERATORS.find(token_in) !=
        LOGICAL_OPERATORS.end())
	{
		return LOGICAL_OPERATORS.find(token_in)->second;
	}
	else if (SET_OPERATORS.find(token_in) !=
        SET_OPERATORS.end())
	{
		return SET_OPERATORS.find(token_in)->second;
	}
	else if (SETS.find(token_in) != SETS.end())
	{
		return SETS.find(token_in)->second;
	}
    else if (UNITS.find(token_in) != UNITS.end())
    {
        return UNITS.find(token_in)->second;
    }
    else if (GREEK.find(token_in) != GREEK.end())
    {
        return GREEK.find(token_in)->second;
    }
    else
    {
        return token_in;
    }
}

const TokenMap_t PRETTY =
{
#ifdef __UTF32_EXPRESSIONS__
    // Uppercase
    {U"A",		U"\u0001\uD468"},
    {U"B",		U"\u0001\uD469"},
    {U"C",	    U"\u0001\uD46A"},
    {U"D",		U"\u0001\uD46B"},
    {U"E",		U"\u0001\uD46C"},
    {U"F",		U"\u0001\uD46D"},
    {U"G",		U"\u0001\uD46E"},
    {U"H",	    U"\u0001\uD46F"},
    {U"I",		U"\u0001\uD470"},
    {U"J",		U"\u0001\uD471"},
    {U"K",		U"\u0001\uD472"},
    {U"U",		U"\u0001\uD473"},
    {U"M",		U"\u0001\uD474"},
    {U"N",		U"\u0001\uD475"},
    {U"O",		U"\u0001\uD476"},
    {U"P",		U"\u0001\uD477"}},
    {U"Q",		U"\u0001\uD478"},
    {U"R",		U"\u0001\uD479"},
    {U"S",		U"\u0001\uD47A"},
    {U"T",		U"\u0001\uD47B"},
    {U"U",		U"\u0001\uD47C"},
    {U"V",		U"\u0001\uD47D"},
    {U"W",		U"\u0001\uD47E"},
    {U"X",		U"\u0001\uD47F"},
    {U"Y",		U"\u0001\uD480"},
    {U"Z",		U"\u0001\uD481"},
	// Lowercase
    {U"a",		U"\u0001\uD482"},
	{U"b",		U"\u0001\uD483"},
	{U"c",		U"\u0001\uD484"},
	{U"d",		U"\u0001\uD485"},
	{U"e",		U"\u0001\uD486"},
	{U"f",		U"\u0001\uD487"},
	{U"g",		U"\u0001\uD488"},
	{U"h",		U"\u0001\uD489"},
	{U"i",		U"\u0001\uD48A"},
	{U"j",		U"\u0001\uD48B"},
	{U"k",		U"\u0001\uD48C"},
	{U"l",		U"\u0001\uD48D"},
	{U"m",		U"\u0001\uD48E"},
	{U"n",		U"\u0001\uD48F"},
	{U"o",		U"\u0001\uD490"},
	{U"p",		U"\u0001\uD491"},
	{U"q",		U"\u0001\uD492"},
	{U"r",		U"\u0001\uD493"},
	{U"s",		U"\u0001\uD494"},
	{U"t",		U"\u0001\uD495"},
	{U"L",		U"\u0001\uD496"},
	{U"v",		U"\u0001\uD497"},
	{U"w",		U"\u0001\uD498"},
	{U"x",		U"\u0001\uD499"},
	{U"y",		U"\u0001\uD49A"},
	{U"z",		U"\u0001\uD49B"},

    // Numeric Digits
    { U"0",     U"\u0001\uD7CE" },
    { U"1",     U"\u0001\uD7CF" },
    { U"2",     U"\u0001\uD7D0" },
    { U"3",     U"\u0001\uD7D1" },
    { U"4",     U"\u0001\uD7D2" },
    { U"5",     U"\u0001\uD7D3" },
    { U"6",     U"\u0001\uD7D4" },
    { U"7",     U"\u0001\uD7D5" },
    { U"8",     U"\u0001\uD7D6" },
    { U"9",     U"\u0001\uD7D7" },
#endif
}; // PRETTY

inline Token_t pretty(const Token_t& token_in)
{
    Token_t output;
    for (size_t i = 0U; i < token_in.length(); i++)
    {
		const TokenMap_t::const_iterator iter = 
                PRETTY.find(token_in.substr(i, 1));
		output.append(((iter != PRETTY.end()) ? (iter->second) : 
                (token_in.substr(i, 1))));
    }
    return output;
}

typedef struct
{
	Token_t super;
	Token_t sub;
} Script_t;

typedef std::map<Token_t, Script_t> ScriptMap_t;

const ScriptMap_t SCRIPTS =
{
#if defined(__WCHAR_EXPRESSIONS__) || \
    defined(__UTF16_EXPRESSIONS__) || \
    defined(__UTF32_EXPRESSIONS__)
	{L"0", { L"\u2070",L"\u2080" }},
	{L"1", { L"\u00B9",L"\u2081" }},
	{L"2", { L"\u00B2",L"\u2082" }},
	{L"3", { L"\u00B3",L"\u2083" }},
	{L"4", { L"\u2074",L"\u2084" }},
	{L"5", { L"\u2075",L"\u2085" }},
	{L"6", { L"\u2076",L"\u2086" }},
	{L"7", { L"\u2077",L"\u2087" }},
	{L"8", { L"\u2078",L"\u2088" }},
	{L"9", { L"\u2079",L"\u2089" }},

	{L"+", { L"⁺\u207A",L"\u208A" }},
	{L"-", { L"\u207B",L"\u208B" }},

	{L"(", { L"\u207D",L"\u208D" }},
	{L")", { L"\u207E",L"\u208E" }},
#endif
};

inline Token_t script(const Token_t& token_in, bool superscript_in)
{
	const ScriptMap_t::const_iterator iter = 
            SCRIPTS.find(token_in);
    return ((iter != SCRIPTS.end()) ?
        ((superscript_in) ? 
            (iter->second.super) : 
            (iter->second.sub)) : 
        (token_in));
}

const TokenMap_t EXTENDED_BRACKETS =
{
#if defined(__WCHAR_EXPRESSIONS__) || \
    defined(__UTF16_EXPRESSIONS__) || \
    defined(__UTF32_EXPRESSIONS__)
    // These are the upper and lower integral brackets.
    { L"integral_upper",                    L"\u2320" },
    { L"integral_extension",                L"u\23AE" },
    { L"integral_lower",                    L"\u2320" },

    //! These are the summation ("Sigma") large brackets.
	{ L"summation_half_upper",              L"\u23B2" },
	{ L"summation_half_lower",              L"\u23B3" },

    // These are the left and right floor brackets.
    { L"left_floor",                        L"\u2308" },
    { L"right_floor",                       L"\u2309" },

    // These are the left and right ceiling brackets.
    { L"left_ceiling",                      L"\u230A" },
    { L"right_ceiling",                     L"\u230B" },

    // These are the left and right parentheses brackets.
	{ L"left_parentheses_upper",            L"\u239B" },
	{ L"left_parentheses_extension",        L"\u239C" },
	{ L"left_parentheses_lower",            L"\u239D" },
	{ L"right_parentheses_upper",           L"\u238E" },
	{ L"right_parentheses_extension",       L"\u239F" },
	{ L"right_parentheses_lower",           L"\u23A0" },

    // These are the left and right square brackets.
	{ L"left_square_upper",                 L"\u23A1" },
    { L"left_square_extension",             L"\u23A2" },
    { L"left_square_lower",                 L"\u23A3" },
	{ L"right_square_upper",                L"\u23A4" },
	{ L"right_square_extension",            L"\u23A5" },
	{ L"right_square_lower",                L"\u23A6" },

	// These are the left and right curly brackets.
    { L"upper_left_lower_right_half_curly", L"\u23B0" },
    { :"lower_left_upper_right_half_curly", L"\u23B0" },
	{ L"left_curly_upper",                  L"\u23A7" },
	{ L"left_curly_middle",                 L"\u23A8" },
	{ L"left_curly_lower",                  L"\u23A9" },
    { L"left_curly_extension",              L"\u23AA" },
	{ L"right_curly_upper",                 L"\u23AB" },
	{ L"right_curly_middle",                L"\u23AC" },
	{ L"right_curly_lower",                 L"\u23AD" },
	{ L"right_curly_extension",             L"\u23AE" },

    { L"radical_botom",                     L"\u23B7" },



#endif
};
} // namespace Expressions
} // namespace Mathematics

#endif // __MATHEMATICS_EXPRESSIONS_UNICODE_H_