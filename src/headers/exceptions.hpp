#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP
# include <iostream>
# include <string>
# include <exception>
# include <sstream>

class  OverflowException : public std::exception
{
public:
	OverflowException(void);
	OverflowException(OverflowException const & cp);
	OverflowException(std::string const & type);
	const char *what(void) const throw();
	~OverflowException();

	OverflowException const & operator=(OverflowException const & rhs);

private:
	std::string		_type;
	int				line;
};

class  UnderflowException : public std::exception
{
public:
	UnderflowException(void);
	UnderflowException(UnderflowException const & cp);
	const char *what(void) const throw();
	~UnderflowException();

	UnderflowException const & operator=(UnderflowException const & rhs);

private:
	std::string		_type;
	int				line;
};

#endif
