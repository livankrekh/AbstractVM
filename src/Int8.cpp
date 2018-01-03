#include "headers/types.hpp"

// Constructors

Int8::Int8(void)
{
	this->_val = 0;
}

Int8::Int8(char value)
{
	this->_val = value;
}

Int8::Int8(Int8 const & cp)
{
	this->_val = cp.getValue();
}

// Member functions

char	Int8::getValue(void) const
{
	return (this->_val);
}

eOperandType	Int8::getType(void) const
{
	return (INT8);
}

int 	Int8::getPrecision(void)
{
	return (INT8);
}

int 	Int8::getPrecision(IOperand const & rhs)
{
	return (INT8 - rhs.getType());
}

std::string	const & toString(void)
{
	return (std::to_string(static_cast<int>this->_val));
}

// Operators

Int8 & operator=(Int8 const & cp)
{
	this->_val = cp.getValue();
	return (*this);
}

Int8 const * operator=(Int8 const * cp)
{
	this->_val = cp->getValue();
	return (this);
}

Int8::~Int8(void) {}
