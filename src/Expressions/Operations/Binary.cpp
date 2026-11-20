// ============================================================================
//! @file Binary.cpp
//! @author Michael P. MIscho
//! @date May 11, 2023
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
#include <Expressions/Operations/Binary.h>
#include <Expressions/Operations/Arithmatic/InfixBinary.h>
#include <Expressions/Operations/Arithmatic/PrefixBinary.h>
#include <Expressions/Operations/Logical/InfixBinary.h>


//  __________________________________________________________________________
// |                                                                          |
// | Class: Binary                                                            |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Binary::Binary(
        const Token_t& token_in,
        Expression* left_in,
        Expression* right_in,
        const TokenPair_t& parentheses_in,
        const TokenPair_t& argument_parentheses_in) :
    Operation(token_in, parentheses_in, argument_parentheses_in),
    left(left_in),
    right(right_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Binary                                                            |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Binary::Binary(const Binary& rhs) :
    Operation(rhs),
    left(rhs.left->copy()),
    right(rhs.right->copy())
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Binary                                                            |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Binary::Binary(
        const Binary& rhs, const TokenPair_t& parentheses_in) :
    Operation(rhs, parentheses_in),
    left(rhs.left->copy()),
    right(rhs.right->copy())
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Binary                                                            |
// | Function: Move Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Binary::Binary(Binary&& rhs) :
    Operation(rhs),
    left(rhs.left->copy()),
    right(rhs.right->copy())
{
    delete rhs.left;
    delete rhs.right;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Binary                                                            |
// | Function: Assignment Operator                                            |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Binary& 
Mathematics::Expressions::Operations::Binary::operator=(const Binary& rhs)
{
    Operation::operator=(rhs);
    this->left = rhs.left->copy();
    this->right = rhs.right->copy();
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Binary                                                            |
// | Function: Move Operator                                                  |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Binary& 
Mathematics::Expressions::Operations::Binary::operator=(Binary&& rhs)
{
    Operation::operator=(rhs);
    this->left = rhs.get_left()->copy();
    this->right = rhs.get_right()->copy();
    delete rhs.left;
    delete rhs.right;
    return *this;
}

//  __________________________________________________________________________
// |                                                                          |
// | Class: Binary                                                            |
// | Function: operator==                                                     |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Binary::operator==(
        const Binary& rhs) const
{
    return ((Expression::operator==(rhs)) &&
        (*this->get_left() == *rhs.get_left()) && 
        (*this->get_right() == *rhs.get_right()));
}

//  __________________________________________________________________________
// |                                                                          |
// | Class: Binary                                                            |
// | Function: prefix                                                         |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Operations::Binary::prefix() const
{
    TokenList_t output;
    this->add_open_parentheses(output);
    output.push_back(this->get_token());
    this->add_open_argument_parentheses(output);
    output.splice(output.end(), this->get_left()->prefix());
    output.splice(output.end(), this->get_right()->prefix());
    this->add_close_argument_parentheses(output);
    this->add_close_parentheses(output);
    return output;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Binary                                                            |
// | Function: postfix                                                        |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Operations::Binary::postfix() const
{
    TokenList_t output;
    this->add_open_parentheses(output);
    this->add_open_argument_parentheses(output);
    output.splice(output.end(), this->get_left()->postfix());
    output.splice(output.end(), this->get_right()->postfix());
    this->add_close_argument_parentheses(output);
    output.push_back(this->get_token());
    this->add_close_parentheses(output);
    return output;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Binary                                                            |
// | Function: size                                                           |
// |__________________________________________________________________________|
size_t Mathematics::Expressions::Operations::Binary::size() const
{
    return 1U + this->get_left()->size() + this->get_right()->size();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Binary                                                            |
// | Function: height                                                         |
// |__________________________________________________________________________|
size_t Mathematics::Expressions::Operations::Binary::height() const
{
    return 1U + std::max(this->get_left()->height(),
            this->get_right()->height());
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Binary                                                            |
// | Function: contains                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Binary::contains(
        const Token_t& token_in) const
{
    return this->get_left()->contains(token_in) || 
        this->get_right()->contains(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Binary                                                            |
// | Function: contains_variable                                              |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Binary::contains_variable() const
{
    return this->get_left()->contains_variable() || 
        this->get_right()->contains_variable();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Binary                                                            |
// | Function: get_variables                                                  |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Operations::Binary::get_variables() const
{
    TokenList_t variables;
    variables.splice(variables.end(), this->get_left()->get_variables());
    variables.splice(variables.end(), this->get_right()->get_variables());
    variables.sort();
    variables.unique();
    return variables;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Binary                                                            |
// | Function: get_branches                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression::ExpressionList_t
Mathematics::Expressions::Operations::Binary::get_branches() const
{
	return { this->get_left(), this->get_right() };
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Binary                                                            |
// | Function: arity                                                          |
// |__________________________________________________________________________|
Mathematics::Natural 
Mathematics::Expressions::Operations::Binary::arity() const
{
    return 2U;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Binary                                                            |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operations::Binary::is_token(
        const Token_t& token_in)
{
    return 	Arithmatic::PrefixBinary::is_token(token_in) || 
        Arithmatic::InfixBinary::is_token(token_in) || 
//		Arithmatic::PostfixBinary::is_token(token_in) ||
        Logical::InfixBinary::is_token(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Binary                                                            |
// | Function: get_precedence                                                 |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenPrecedence_t 
Mathematics::Expressions::Operations::Binary::get_precedence(
        Type_t type_in, 
        const Token_t& token_in)
{
    switch (type_in)
    {
        case Type_t::ARITHMATIC_PREFIX_BINARY:
            return Arithmatic::PrefixBinary::get_precedence(type_in, 
                token_in);
            break;

        case Type_t::ARITHMATIC_INFIX_BINARY:
            return Arithmatic::InfixBinary::get_precedence(type_in, 
                token_in);
            break;

        case Type_t::ARITHMATIC_POSTFIX_BINARY:
        case Type_t::LOGICAL_INFIX_BINARY:
        default:
            return MIN_PRECEDENCE;
            break;
    }
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Binary                                                            |
// | Function: Destructor                                                     |
// |__________________________________________________________________________|
Mathematics::Expressions::Operations::Binary::~Binary()
{
    delete this->left;
    delete this->right;
}

//  __________________________________________________________________________
// |                                                                          |
// | Class: Binary                                                            |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
void Mathematics::Expressions::Operations::Binary::pretty_tree(
        std::stringstream& stream, 
        const std::string& prefix_in,
        bool is_last) const
{
	stream << prefix_in <<
		(!is_last ? "\xC3\xC4\xC4" : "\xC0\xC4\xC4") <<
		"(" << this->get_token() << ")" << std::endl;

	std::string new_prefix = prefix_in + (!is_last ? "\xB3   " : "    ");

	// Enter the next tree level - left and right branch
	stream << new_prefix << "\xB3   " << std::endl;
	this->get_left()->pretty_tree(stream, new_prefix, false);
	stream << new_prefix << "\xB3   " << std::endl;
	this->get_right()->pretty_tree(stream, new_prefix, true);
}
