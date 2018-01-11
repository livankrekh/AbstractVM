#include "headers/exceptions.hpp"

OverflowException::OverflowException(std::string const & type, int line)
{
	this->_type = type;
	this->_line = line;
}

const char *OverflowException::what(void) const throw()
{
	std::stringstream error;

	error << "\033[31mError #01: Overflow type " << this->_type;
	error << " \033[1min line #" << this->_line << "\033[0m\033[0m" << std::endl;
	return (error.str().c_str());
}

UnderflowException::UnderflowException(std::string const & type, int line)
{
	this->_type = type;
	this->_line = line;
}

const char *UnderflowException::what(void) const throw()
{
	std::stringstream error;

	error << "\033[31mError #02: Underflow type " << this->_type;
	error << " \033[1min line #" << this->_line << "\033[0m\033[0m" << std::endl;
	return (error.str().c_str());
}
