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

VM 		*VM::vm;

VM::VM(void)
{
	this->funcptr[0] = &VM::createInt8;
	this->funcptr[1] = &VM::createInt16;
	this->funcptr[2] = &VM::createInt32;
	this->funcptr[3] = &VM::createFloat;
	this->funcptr[4] = &VM::createDouble;
	this->_line = 1;
	VM::vm = &(*this);
}

VM::~VM(void)
{
	while (!_stack.empty())
	{
		delete _stack[0];
		_stack.erase(_stack.begin());
	}
}

IOperand const * VM::createInt8(long double val) const
{
	return reinterpret_cast<IOperand const *>(new Type<long double>(val, INT8));
}

IOperand const * VM::createInt16(long double val) const
{
	return reinterpret_cast<IOperand const *>(new Type<long double>(val, INT16));
}

IOperand const * VM::createInt32(long double val) const
{
	return reinterpret_cast<IOperand const *>(new Type<long double>(val, INT32));
}

IOperand const * VM::createFloat(long double val) const
{
	return reinterpret_cast<IOperand const *>(new Type<long double>(val, FLOAT));
}

IOperand const * VM::createDouble(long double val) const
{
	return reinterpret_cast<IOperand const *>(new Type<long double>(val, DOUBLE));
}

IOperand const * VM::createOperand(eOperandType type, const std::string & value ) const
{
	IOperand const * newOperand;
	long double val;

	val = std::stold(value);
	newOperand = (this->*funcptr[type])(val);
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

void			VM::add(void)
{
	IOperand const * res;

	if (_stack.size() < 2)
		throw MinimumException();
	res = *(_stack[_stack.size() - 1]) + *(_stack[_stack.size() - 2]);
	_stack.pop_back();
	_stack.pop_back();
	_stack.push_back(res);
}

void			VM::sub(void)
{
	IOperand const * res;

	if (_stack.size() < 2)
		throw MinimumException();
	res = *(_stack[_stack.size() - 2]) - *(_stack[_stack.size() - 1]);
	_stack.pop_back();
	_stack.pop_back();
	_stack.push_back(res);
}

void			VM::mul(void)
{
	IOperand const * res;

	if (_stack.size() < 2)
		throw MinimumException();
	res = *(_stack[_stack.size() - 1]) * *(_stack[_stack.size() - 2]);

	_stack.pop_back();
	_stack.pop_back();
	_stack.push_back(res);
}

void			VM::div(void)
{
	IOperand const * res;

	if (_stack.size() < 2)
		throw MinimumException();
	res = *(_stack[_stack.size() - 2]) / *(_stack[_stack.size() - 1]);
	_stack.pop_back();
	_stack.pop_back();
	_stack.push_back(res);
}

void			VM::mod(void)
{
	IOperand const * res;

	if (_stack.size() < 2)
		throw MinimumException();
	res = *(_stack[_stack.size() - 2]) % *(_stack[_stack.size() - 1]);
	_stack.pop_back();
	_stack.pop_back();
	_stack.push_back(res);
}

void			VM::stackAdd(const std::string & n, eOperandType const & type)
{
	_stack.push_back(this->createOperand(type, n));
}

void			VM::stackPop(void)
{
	if (_stack.empty())
		throw StackEmptyException();
	_stack.pop_back();
}

void			VM::stackDump(void)
{
	std::string 	tmp;

	_output.push_back("\033[34m\033[1mDump________________________");
	for (int i = _stack.size() - 1; i >= 0; i--)
		_output.push_back(_stack[i]->toString());
	_output.push_back("____________________________\033[0m");
}

void			VM::stackAssert(eOperandType const & type, long double val)
{
	if (_stack.size() < 1)
		throw StackEmptyException();

	if (_stack.back()->getType() != type
			|| static_cast<double>(std::stod(_stack.back()->toString()) != static_cast<double>(val) ) )
		throw AssertFalseException();
}

void			VM::stackPrint(void)
{
	std::stringstream ss;

	if (_stack.size() < 1)
		throw StackEmptyException();

	if (_stack[_stack.size() - 1]->getType() != INT8)
		throw AssertFalseException();

	ss << "\033[32m\033[1m";
	ss << static_cast<char>(std::stoi(_stack.back()->toString()));
	ss << "\033[0m";

	_output.push_back(ss.str());
}

void			VM::printOutput(void)
{
	while (!_output.empty())
	{
		std::cout << _output[0] << std::endl;
		_output.erase(_output.begin());
	}
}

void			VM::exitProg(void)
{
	while (!_stack.empty())
	{
		delete _stack[0];
		_stack.erase(_stack.begin());
	}
	_output.push_back("\033[31m\033[1mExit________________________\033[0m");
}

void			VM::setQueue(std::string const & inf)
{
	this->_output.push_back(inf);
}
