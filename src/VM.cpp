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

IOperand const * VM::createInt8(std::string const & value) const
{
	return reinterpret_cast<IOperand const *>(new Type<long double>(value, INT8));
}

IOperand const * VM::createInt16(std::string const & value) const
{
	return reinterpret_cast<IOperand const *>(new Type<long double>(value, INT16));
}

IOperand const * VM::createInt32(std::string const & value) const
{
	return reinterpret_cast<IOperand const *>(new Type<long double>(value, INT32));
}

IOperand const * VM::createFloat(std::string const & value) const
{
	return reinterpret_cast<IOperand const *>(new Type<long double>(value, FLOAT));
}

IOperand const * VM::createDouble(std::string const & value) const
{
	return reinterpret_cast<IOperand const *>(new Type<long double>(value, DOUBLE));
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

void			VM::stackAdd(char n)
{
	_stack.push_back(this->createOperand(INT8, std::to_string(n)));
}

void			VM::stackAdd(short int n)
{
	_stack.push_back(this->createOperand(INT16, std::to_string(n)));
}

void			VM::stackAdd(int n)
{
	_stack.push_back(this->createOperand(INT32, std::to_string(n)));
}

void			VM::stackAdd(float n)
{
	_stack.push_back(this->createOperand(FLOAT, std::to_string(n)));
}

void			VM::stackAdd(double n)
{
	_stack.push_back(this->createOperand(DOUBLE, std::to_string(n)));
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
	if (_stack.back()->getType() != type || static_cast<float>(std::stold(_stack.back()->toString())) != static_cast<float>(val))
		throw AssertFalseException();
}

void			VM::stackPrint(void)
{
	std::stringstream ss;

	if (_stack.size() < 1)
		throw StackEmptyException();

	if (_stack[_stack.size() - 1]->getType() != INT8)
		throw AssertFalseException();
	ss << static_cast<char>(std::stoi(_stack[_stack.size() - 1]->toString()));
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
