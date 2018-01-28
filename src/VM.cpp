/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VM.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liabanzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 15:51:02 by liabanzh          #+#    #+#             */
/*   Updated: 2018/01/28 15:51:04 by liabanzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/types.hpp"

VM::VM(void)
{
	this->funcptr[0] = &VM::createInt8;
	this->funcptr[1] = &VM::createInt16;
	this->funcptr[2] = &VM::createInt32;
	this->funcptr[3] = &VM::createFloat;
	this->funcptr[4] = &VM::createDouble;
	this->_line = 0;
}

IOperand const * VM::createInt8(std::string const & value) const
{
	return reinterpret_cast<IOperand const *>(new Type<char>(value, INT8));
}

IOperand const * VM::createInt16(std::string const & value) const
{
	return reinterpret_cast<IOperand const *>(new Type<short int>(value, INT16));
}

IOperand const * VM::createInt32(std::string const & value) const
{
	return reinterpret_cast<IOperand const *>(new Type<int>(value, INT32));
}

IOperand const * VM::createFloat(std::string const & value) const
{
	return reinterpret_cast<IOperand const *>(new Type<float>(value, FLOAT));
}

IOperand const * VM::createDouble(std::string const & value) const
{
	return reinterpret_cast<IOperand const *>(new Type<double>(value, DOUBLE));
}

IOperand const * VM::createOperand(eOperandType type, std::string const & value) const
{
	IOperand const * newOperand;

	newOperand = (this->*funcptr[type])(value);
	return (newOperand);
}

long			VM::getLine(void)
{
	return (this->_line);
}

void			VM::incrementLine(void)
{
	this->_line++;
}
