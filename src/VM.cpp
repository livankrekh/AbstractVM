#include "headers/VM.hpp"

VM::VM(void)
{
	this->funcptr[0] = &VM::createInt8;
	this->funcptr[1] = &VM::createInt16;
	this->funcptr[2] = &VM::createInt32;
	this->funcptr[3] = &VM::createFloat;
	this->funcptr[4] = &VM::createDouble;
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
