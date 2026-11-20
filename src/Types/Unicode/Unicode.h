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
#include <string>
#include <map>
#include <vector>

namespace Mathematics
{
#if defined(__UTF32_EXPRESSIONS__)
typedef std::basic_string<char32_t> string_t;
#elif defined(__UTF16_EXPRESSIONS__)
typedef std::basic_string<char16_t> string_t;
#else
typedef std::basic_string<wchar_t> string_t;
#endif

typedef std::map<string_t, string_t> UnicodeMap_t;

const UnicodeMap_t AEITHMATIC_OPERATORS =
{
#if defined(__WCHAR_EXPRESSIONS__) || \
    defined(__UTF16_EXPRESSIONS__) || \
    defined(__UTF32_EXPRESSIONS__)
    { "*",				    "∙" },
    { "/",				    "÷" },
    { "exp",			    "ℯ^" },
    { "nrt",               "n\u221A" },
    { "sqrt",			    "\u221A" },
    { "sum",			    "\u2211" },        // Not Implemented
    { "product",		    "\u220F" },        // Not Implemented
    { "coproduct",		    "\u2210" },        // Not Implemented
#endif
}; // AEITHMATIC_OPERATORS


const UnicodeMap_t CALCULUS_OPERATORS =
{
#if defined(__WCHAR_EXPRESSIONS__) || \
    defined(__UTF16_EXPRESSIONS__) || \
    defined(__UTF32_EXPRESSIONS__)
	{ "integral",          "\u222B" },            // Not Implemented
	{ "partial",		    "\u2202\u2202?" },     // Not Implemented
#endif
}; // CALCULUS_OPERATORS

const UnicodeMap_t LOGICAL_OPERATORS =
{
#if defined(__WCHAR_EXPRESSIONS__) || \
    defined(__UTF16_EXPRESSIONS__) || \
    defined(__UTF32_EXPRESSIONS__)
    { "~=",                "\u2248" },
    { "!=",                "\u2260"},
	{ ">=",				"\u2265" },
	{ "=<",				"\u2264"},
	{ "and",			    "\u2227"},     // Not Implemented
	{ "or",				"\u2228"},     // Not Implemented
	{ "there_exists",      "\u2203"},     // Not Implemented
	{ "not_exists",        "\u2204"},     // Not Implemented
#endif
}; // LOGICAL_OPERATORS

const UnicodeMap_t SET_OPERATORS =
{
#if defined(__WCHAR_EXPRESSIONS__) || \
    defined(__UTF16_EXPRESSIONS__) || \
    defined(__UTF32_EXPRESSIONS__)
    { "intersection",	    "\u2229" },    // Not Implemented
    { "union",			    "\u222A" },    // Not Implemented
    { "subset",		    "\u2282" },    // Not Implemented
    { "superset",		    "\u2283" },    // Not Implemented
    { "not_subset",	    "\u2284" },    // Not Implemented
    { "not_superset",	    "\u2285" },    // Not Implemented
    { "element_of",		"\u22F2" },    // Not Implemented
    { "not_element_of",	"\u2209" },    // Not Implemented
    { "contain",		    "\u22FA" },    // Not Implemented
    { "not_constain",	    "\u220C" },    // Not Implemented
    { "for_all",		    "\u2200" },    // Not Implemented
#endif
}; // SET_OPERATORS

const UnicodeMap_t SETS =
{
#if defined(__WCHAR_EXPRESSIONS__) || \
    defined(__UTF16_EXPRESSIONS__) || \
    defined(__UTF32_EXPRESSIONS__)
    {"{}",				    "\u2205"},     // The Empty Set
    {"{REAL}",			    "\u211D"},     // All Real Numbers
    {"{NATURAL}",		    "\u2115"},     // All Natural Numbers
    {"{COMPLEX}",		    "\u2102"},     // All Complex Numbers
    {"{INTEGERS}",		    "\u2124"},     // All Integer Numbers
    {"{RATIONAL}",		    "\u211A"},     // All Rational Numbers
#endif
}; // SETS

const UnicodeMap_t UNITS =
{
#if defined(__WCHAR_EXPRESSIONS__) || \
    defined(__UTF16_EXPRESSIONS__) || \
    defined(__UTF32_EXPRESSIONS__)
    {"Ohms",			    "\u2126"},
    {"Celsius",		    "\u2103"},
    {"Fahrenheit",		    "\u2109"},
#endif
}; // UNITS

const UnicodeMap_t GREEK =
{
#if defined(__WCHAR_EXPRESSIONS__) || \
    defined(__UTF16_EXPRESSIONS__)
	// Uppercase
    {"ALPHA",		        "\u0391"},
    {"BETA",		        "\u0392"},
    {"GAMMA",		        "\u0393"},
    {"DELTA",		        "\u0394"},
    {"EPSILON",	        "\u0395"},
    {"ZETA",		        "\u0396"},
    {"ETA",		        "\u0397"},
    {"THETA",		        "\u0398"},
    {"IOTA",		        "\u0399"},
    {"KAPPA",		        "\u039A"},
    {"LAMBDA",		        "\u039B"},
    {"MU",			        "\u039C"},
    {"NU",			        "\u039D"},
    {"XI",			        "\u039E"},
    {"OMICRON",	        "\u039F"},
    {"PI",			        "\u03A0"},
    {"RHO",		        "\u03A1"},
    {"SIGMA",		        "\u03A3"},
    {"TAU",		        "\u03A4"},
    {"UPSILON",	        "\u03A5"},
    {"PHI",		        "\u03A6"},
    {"CHI",		        "\u03A7"},
    {"PSI",		        "\u03A8"},
    {"OMEGA",		        "\u03A9"},

    // Lowercase
    {"alpha",		        "\u03B1"},
    {"beta",		        "\u03B2"},
    {"gamma",		        "\u03B3"},
    {"delta",		        "\u03B4"},
    {"epsilon",	        "\u03B5"},
    {"zeta",		        "\u03B6"},
    {"eta",		        "\u03B7"},
    {"theta",		        "\u03B8"},
    {"iota",		        "\u03B9"},
    {"kappa",		        "\u03BA"},
    {"lambda",	            "\u03BB"},
    {"m",			        "\u03BC"},
    {"n",			        "\u03BD"},
    {"xi",			        "\u03BE"},
    {"omicron",	        "\u03BF"},
    {"pi",			        "\u03C0"},
    {"rho",		        "\u03C1"},
    {"sigma",		        "\u03C3"},
    {"ta",		        "\u03C4"},
    {"upsilon",	        "\u03C5"},
    {"phi",		        "\u03C6"},
    {"chi",		        "\u03C7"},
    {"psi",		        "\u03C8"},
    {"omega",		        "\u03C9"},
#endif
#ifdef __UTF32_EXPRESSIONS__
    // Uppercase
    {U"ALPHA",		U"\u0001\uD6A8"},
    {U"BETA",		U"\u0001\uD6A9"},
    {U"GAMMA",		U"\u0001\uD6AA"},
    {U"DELTA",		U"\u0001\uD6AB"},
    {U"EPSILON",	U"\u0001\uD6AC"},
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
	{U"m",			U"𝝁"},
	{U"n",			U"𝝂"},
	{U"xi",			U"𝝃"},
	{U"omicron",	U"𝝄"},
	{U"pi",			U"𝝅"},
	{U"rho",		U"𝝆"},
	{U"sigma",		U"𝝈"},
	{U"tau",		U"𝝉"},
	{U"upsilon",	U"𝝊"},
	{U"phi",		U"𝝓"},
	{U"chi",		U"𝝌"},
	{U"psi",		U"𝝍"},
	{U"omega",		U"𝝎"},
#endif
}; // GREEK

inline string_t replace(const string_t& token_in)
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

const UnicodeMap_t PRETTY =
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
	{U"",		U"\u0001\uD496"},
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

inline string_t pretty(const string_t& token_in)
{
    string_t output;
    for (size_t i = 0U; i < token_in.length(); i++)
    {
		const UnicodeMap_t::const_iterator iter =
                PRETTY.find(token_in.substr(i, 1));
		output.append(((iter != PRETTY.end()) ? (iter->second) : 
                (token_in.substr(i, 1))));
    }
    return output;
}

typedef struct
{
	string_t super;
    string_t sub;
} Script_t;

typedef std::map<string_t, std::vector<string_t>> ScriptMap_t;

const ScriptMap_t SCRIPTS =
{
#if defined(__WCHAR_EXPRESSIONS__) || \
    defined(__UTF16_EXPRESSIONS__) || \
    defined(__UTF32_EXPRESSIONS__)
	{"0", { "\u2070","\u2080" }},
	{"1", { "\u00B9","\u2081" }},
	{"2", { "\u00B2","\u2082" }},
	{"3", { "\u00B3","\u2083" }},
	{"4", { "\u2074","\u2084" }},
	{"5", { "\u2075","\u2085" }},
	{"6", { "\u2076","\u2086" }},
	{"7", { "\u2077","\u2087" }},
	{"8", { "\u2078","\u2088" }},
	{"9", { "\u2079","\u2089" }},

	{"+", { "⁺\u207A","\u208A" }},
	{"-", { "\u207B","\u208B" }},

	{"(", { "\u207D","\u208D" }},
	{")", { "\u207E","\u208E" }},
#endif
};

enum class ScriptType_t : size_t
{
    SUB = 0U,
    SUPER,
};
inline string_t script(const string_t& token_in, ScriptType_t type_in)
{
	const ScriptMap_t::const_iterator iter = 
            SCRIPTS.find(token_in);
    return ((iter != SCRIPTS.end()) ?
        (iter->second[static_cast<size_t>(type_in)]) :
        (token_in));
}

const UnicodeMap_t EXTENDED_BRACKETS =
{
#if defined(__WCHAR_EXPRESSIONS__) || \
    defined(__UTF16_EXPRESSIONS__) || \
    defined(__UTF32_EXPRESSIONS__)
    // These are the upper and lower integral brackets.
    { "integral_upper",                    "\u2320" },
    { "integral_extension",                "u\23AE" },
    { "integral_lower",                    "\u2320" },

    //! These are the summation ("Sigma") large brackets.
	{ "summation_half_upper",              "\u23B2" },
	{ "summation_half_lower",              "\u23B3" },

    // These are the left and right floor brackets.
    { "left_floor",                        "\u2308" },
    { "right_floor",                       "\u2309" },

    // These are the left and right ceiling brackets.
    { "left_ceiling",                      "\u230A" },
    { "right_ceiling",                     "\u230B" },

    // These are the left and right parentheses brackets.
	{ "left_parentheses_upper",            "\u239B" },
	{ "left_parentheses_extension",        "\u239C" },
	{ "left_parentheses_lower",            "\u239D" },
	{ "right_parentheses_upper",           "\u238E" },
	{ "right_parentheses_extension",       "\u239F" },
	{ "right_parentheses_lower",           "\u23A0" },

    // These are the left and right square brackets.
	{ "left_square_upper",                 "\u23A1" },
    { "left_square_extension",             "\u23A2" },
    { "left_square_lower",                 "\u23A3" },
	{ "right_square_upper",                "\u23A4" },
	{ "right_square_extension",            "\u23A5" },
	{ "right_square_lower",                "\u23A6" },

	// These are the left and right curly brackets.
    { "upper_left_lower_right_half_curly", "\u23B0" },
    { "lower_left_upper_right_half_curly", "\u23B0" },
	{ "left_curly_upper",                  "\u23A7" },
	{ "left_curly_middle",                 "\u23A8" },
	{ "left_curly_lower",                  "\u23A9" },
    { "left_curly_extension",              "\u23AA" },
	{ "right_curly_upper",                 "\u23AB" },
	{ "right_curly_middle",                "\u23AC" },
	{ "right_curly_lower",                 "\u23AD" },
	{ "right_curly_extension",             "\u23AE" },

    { "radical_botom",                     "\u23B7" },
#endif
};
} // namespace Mathematics

#endif // __MATHEMATICS_UNICODE_H_