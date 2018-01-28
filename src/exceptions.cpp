/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liabanzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 15:51:20 by liabanzh          #+#    #+#             */
/*   Updated: 2018/01/28 15:51:24 by liabanzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/exceptions.hpp"

std::string STR_TYPE[5] = {"INT8", "INT16", "INT32", "Float", "Double"};

OverflowException::OverflowException(eOperandType const & type, int line)
{
	this->_type = STR_TYPE[type];
	this->_line = line;
}

const char *OverflowException::what(void) const throw()
{
	std::stringstream error;

	error << "\033[31mError #01: Overflow type " << this->_type;
	error << " \033[1mat line #" << this->_line << "\033[0m\033[0m" << std::endl;
	return (error.str().c_str());
}

UnderflowException::UnderflowException(eOperandType const & type, int line)
{
	this->_type = STR_TYPE[type];
	this->_line = line;
}

const char *UnderflowException::what(void) const throw()
{
	std::stringstream error;

	error << "\033[31mError #02: Underflow type " << this->_type;
	error << " \033[1mat line #" << this->_line << "\033[0m\033[0m" << std::endl;
	return (error.str().c_str());
}

DivisionException::DivisionException(int line)
{
	this->_line = line;
}

const char * DivisionException::what(void) const throw()
{
	std::stringstream error;

	error << "\033[31mError #03: Division by zero at line " << this->_line;
	error << "!\033[0m" << std::endl;
	return (error.str().c_str());
}

ModulWithFloat::ModulWithFloat(eOperandType const & type, int line)
{
	this->_type = STR_TYPE[type];
	this->_line = line;
}

const char * ModulWithFloat::what(void) const throw()
{
	std::stringstream error;

	error << "\033[31mError #04: Can't modulo with type " << this->_type;
	error << " \033[1mat line #" << this->_line << "\033[0m\033[0m" << std::endl;
	return (error.str().c_str());
}

StackEmptyException::StackEmptyException(int line)
{
	this->_line = line;
}

const char * StackEmptyException::what(void) const throw()
{
	std::stringstream error;

	error << "\033[31mError #05: Action with empty stack ";
	error << " \033[1mat line #" << this->_line << "\033[0m\033[0m" << std::endl;
	return (error.str().c_str());
}

MinimumException::MinimumException(int line)
{
	this->_line = line;
}

const char * MinimumException::what(void) const throw()
{
	std::stringstream error;

	error << "\033[31mError #06: Can't do this action - stack has less 2 elements ";
	error << " \033[1mat line #" << this->_line << "\033[0m\033[0m" << std::endl;
	return (error.str().c_str());
}

AssertFalseException::AssertFalseException(int line)
{
	this->_line = line;
}

const char * AssertFalseException::what(void) const throw()
{
	std::stringstream error;

	error << "\033[31mError #07: Command Assert get false ";
	error << " \033[1mat line #" << this->_line << "\033[0m\033[0m" << std::endl;
	return (error.str().c_str());
}