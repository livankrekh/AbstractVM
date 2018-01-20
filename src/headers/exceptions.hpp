#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP
# include <iostream>
# include <string>
# include <exception>
# include <sstream>
# include "IOperands.hpp"

class  OverflowException : public std::exception
{
public:
	OverflowException(void) {}
	OverflowException(std::string const & type, int line);
	
	const char *what(void) const throw();
	
	~OverflowException(void) {}

private:
	std::string		_type;
	int				_line;

	OverflowException(OverflowException const & cp);
	OverflowException const & operator=(OverflowException const & rhs);
};

class  UnderflowException : public std::exception
{
public:
	UnderflowException(void) {}
	UnderflowException(std::string const & type, int line);
	
	const char *what(void) const throw();
	
	~UnderflowException(void) {}

private:
	std::string		_type;
	int				_line;

	UnderflowException(UnderflowException const & cp);
	UnderflowException const & operator=(UnderflowException const & rhs);
};

class DivisionException : public std::exception
{
public:
	DivisionException(void) {}

	const char *what(void) const throw();
	
	~DivisionException(void) {}

private:
	DivisionException(DivisionException const & cp);
	DivisionException const & operator=(DivisionException const & rhs);

};

#endif
