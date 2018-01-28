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
	error << " \033[1minat line #" << this->_line << "\033[0m\033[0m" << std::endl;
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
	error << " \033[1minat line #" << this->_line << "\033[0m\033[0m" << std::endl;
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

	error << "\033[31mError #02: Can't modulo with type " << this->_type;
	error << " \033[1minat line #" << this->_line << "\033[0m\033[0m" << std::endl;
	return (error.str().c_str());
}
