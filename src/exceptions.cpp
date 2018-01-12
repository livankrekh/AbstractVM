#include "headers/exceptions.hpp"
#include "headers/IOperands.hpp"

std::string *STR_TYPE = ["INT8", "INT16", "INT32", "Float", "Double"];

OverflowException::OverflowException(eOperandType const & type, int line)
{
	this->_type = STR_TYPE[type];
	this->_line = line;
}

const char *OverflowException::what(void) const throw()
{
	std::stringstream error;

	error << "\033[31mError #01: Overflow type " << this->_type;
	error << " \033[1min line #" << this->_line << "\033[0m\033[0m" << std::endl;
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
	error << " \033[1min line #" << this->_line << "\033[0m\033[0m" << std::endl;
	return (error.str().c_str());
}
