// ============================================================================
//! @file Operand.cpp
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
#include <Expressions/Operands/Operand.h>
#include <Expressions/Operands/Constant.h>
#include <Expressions/Operands/Number.h>
#include <Expressions/Operands/Variable.h>
#include <iostream>


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operand                                                           |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Operand::Operand(const Token_t& token_in,
        const TokenPair_t& parentheses_in) :
    Expression(token_in, parentheses_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operand                                                           |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Operand::Operand(Real number_in,
        const TokenPair_t& parentheses_in) :
    Expression(number_in, parentheses_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operand                                                           |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Operand::Operand(const Operand& rhs) :
    Expression(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operand                                                           |
// | Function: Copy Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Operand::Operand(const Operand& rhs, 
        const TokenPair_t& parentheses_in) :
    Expression(rhs.get_token(), parentheses_in)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operand                                                           |
// | Function: Move Constructor                                               |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Operand::Operand(Operand&& rhs) :
    Expression(rhs)
{
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operand                                                           |
// | Function: Assignment Operator                                            |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Operand& 
Mathematics::Expressions::Operands::Operand::operator=(const Operand& rhs)
{
    Expression::operator=(rhs);
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operand                                                           |
// | Function: Move Operator                                                  |
// |__________________________________________________________________________|
Mathematics::Expressions::Operands::Operand& 
Mathematics::Expressions::Operands::Operand::operator=(Operand&& rhs)
{
    Expression::operator=(rhs);
    return *this;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operand                                                           |
// | Function: is_operator                                                    |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operands::Operand::is_operator() const
{
    return false;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operand                                                           |
// | Function: in_operand                                                     |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operands::Operand::is_operand() const
{
    return true;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operand                                                           |
// | Function: is_separator                                                   |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operands::Operand::is_separator() const
{
    return false;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operand                                                           |
// | Function: is_bracket                                                     |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operands::Operand::is_bracket() const
{
    return false;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operand                                                           |
// | Function: prefix                                                         |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Operands::Operand::prefix() const
{
    return this->infix();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operand                                                           |
// | Function: infix                                                          |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Operands::Operand::infix() const
{
    TokenList_t output;
    this->add_open_parentheses(output);
    output.push_back(this->get_token());
    this->add_close_parentheses(output);
    return output;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operand                                                           |
// | Function: postfix                                                        |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenList_t 
Mathematics::Expressions::Operands::Operand::postfix() const
{
    return this->infix();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operand                                                           |
// | Function: size                                                           |
// |__________________________________________________________________________|
size_t Mathematics::Expressions::Operands::Operand::size() const
{
    return 1U;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operand                                                           |
// | Function: height                                                         |
// |__________________________________________________________________________|
size_t Mathematics::Expressions::Operands::Operand::height() const
{
    return 0U;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operand                                                           |
// | Function: contains                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operands::Operand::contains(
        const Token_t& token_in) const
{
    return (this->get_token() == token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operand                                                           |
// | Function: simplify                                                       |
// |__________________________________________________________________________|
Mathematics::Expressions::Expression* 
Mathematics::Expressions::Operands::Operand::simplify() const
{
    return this->copy();
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operand                                                           |
// | Function: is_token                                                       |
// |__________________________________________________________________________|
bool Mathematics::Expressions::Operands::Operand::is_token(
        const Token_t& token_in)
{
    return Constant::is_token(token_in) || Number::is_token(token_in) || 
            Variable::is_token(token_in);
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operand                                                           |
// | Function: get_precedence                                                 |
// |__________________________________________________________________________|
Mathematics::Expressions::TokenPrecedence_t
Mathematics::Expressions::Operands::Operand::get_precedence(Type_t type_in, 
        const Token_t& token_in)
{
    return MIN_PRECEDENCE;
}


//  __________________________________________________________________________
// |                                                                          |
// | Class: Operand                                                           |
// | Function: Constructor                                                    |
// |__________________________________________________________________________|
void Mathematics::Expressions::Operands::Operand::print(TokenStream_t& stream, 
        const Token_t& prefix_in,
        bool is_last) const
{
    stream << prefix_in << (!is_last ? L"├──" : L"└──") << L"(" <<
        this->get_token() << L")" << std::endl;
}

