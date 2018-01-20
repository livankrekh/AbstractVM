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
	OverflowException(void);
	OverflowException(eOperandType const & type, int line);
	
	virtual const char *what(void) const throw();
	
	~OverflowException(void) throw();

private:
	std::string		_type;
	int				_line;

	OverflowException const & operator=(OverflowException const & rhs);
};

class  UnderflowException : public std::exception
{
public:
	UnderflowException(void);
	UnderflowException(eOperandType const & type, int line);
	
	virtual const char *what(void) const throw();
	
	~UnderflowException(void) throw();

private:
	std::string		_type;
	int				_line;

	UnderflowException const & operator=(UnderflowException const & rhs);
};

class DivisionException : public std::exception
{
public:
	DivisionException(void);

	virtual const char *what(void) const throw();
	
	~DivisionException(void) throw();

private:
	DivisionException const & operator=(DivisionException const & rhs);

};

#endif
