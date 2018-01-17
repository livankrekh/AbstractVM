#include "headers/VM.hpp"
#include "headers/types.hpp"

VM::VM(void)
{
	this->funcptr[0] = (this->createInt8);
	this->funcptr[1] = (this->createInt16);
	this->funcptr[2] = (this->createInt32);
	this->funcptr[3] = (this->createFloat);
	this->funcptr[4] = (this->createDouble);
}

IOperand const * VM::createInt8(std::string const & value) const
{
	return reinterpret_cast<IOperand const *>(new Types<char>(value, INT8));
}

IOperand const * VM::createInt16(std::string const & value) const
{
	return reinterpret_cast<IOperand const *>(new Types<short int>(value, INT16));
}

IOperand const * VM::createInt32(std::string const & value) const
{
	return reinterpret_cast<IOperand const *>(new Types<int>(value, INT32));
}

IOperand const * VM::createFloat(std::string const & value) const
{
	return reinterpret_cast<IOperand const *>(new Types<float>(value, FLOAT));
}

IOperand const * VM::createDouble(std::string const & value) const
{
	return reinterpret_cast<IOperand const *>(new Types<double>(value, DOUBLE));
}

IOperand const * createOperand(eOperandType type, std::string const & value) const
{
	IOperand const * newOperand;

	newOperand = funcptr[type](value);
	return (newOperand);
}
