#include "headers/VM.hpp"

VM::VM(void)
{
	this->funcptr[0] = this->createInt8;
	this->funcptr[1] = this->createInt16;
	this->funcptr[2] = this->createInt32;
	this->funcptr[3] = this->createFloat;
	this->funcptr[4] = this->createDouble;
}

IOperand const * VM::createInt8(std::string const & value) const
{
	IOperand const * res = new Types(value, INT8);
	return (res);
}

IOperand const * VM::createInt16(std::string const & value) const
{
	IOperand const * res = new Types(value, INT16);
	return (res);
}

IOperand const * VM::createInt32(std::string const & value) const
{
	IOperand const * res = new Types(value, INT32);
	return (res);
}

IOperand const * VM::createFloat(std::string const & value) const
{
	IOperand const * res = new Types(value, FLOAT);
	return (res);
}

IOperand const * VM::createDouble(std::string const & value) const
{
	IOperand const * res = new Types(value, DOUBLE);
	return (res);
}

IOperand const * createOperand(eOperandType type, std::string const & value) const
{
	IOperand const * newOperand;

	newOperand = this->funcptr[type](value);
	return (newOperand);
}
