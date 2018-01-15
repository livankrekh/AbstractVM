#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP
# include <iostream>
# include <string>
# include <exception>
# include <sstream>

class  OverflowException : public std::exception
{
public:
	OverflowException(void) {}
	OverflowException(OverflowException const & cp) {}
	OverflowException(std::string const & type, int line);
	
	const char *what(void) const throw();
	
	~OverflowException(void) {}

	OverflowException const & operator=(OverflowException const & rhs) {}

private:
	std::string		_type;
	int				_line;
};

class  UnderflowException : public std::exception
{
public:
	UnderflowException(void) {}
	UnderflowException(UnderflowException const & cp) {}
	UnderflowException(std::string const & type, int line);
	
	const char *what(void) const throw();
	
	~UnderflowException(void) {}

	UnderflowException const & operator=(UnderflowException const & rhs) {}

private:
	std::string		_type;
	int				_line;
};

class DivisionException : public std::exception
{
public:
	DivisionException(void) {}
	DivisionException(DivisionException const & cp) {}
	
	const char *what(void) const throw();
	
	~DivisionException(void) {}

	DivisionException const & operator=(DivisionException const & rhs) {}


}

#endif
