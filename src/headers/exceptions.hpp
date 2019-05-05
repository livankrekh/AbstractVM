/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liabanzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 15:51:50 by liabanzh          #+#    #+#             */
/*   Updated: 2018/01/28 15:51:51 by liabanzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP
# include "IOperands.hpp"
# include <exception>
# include <sstream>
# include <string.h>

class  OverflowException : public std::exception
{
public:
	OverflowException(eOperandType const & type, int line);
	
	virtual const char *what(void) const throw();
	
	~OverflowException(void) throw() {}

private:
	std::string		_type;

	OverflowException const & operator=(OverflowException const & rhs);

public:
	int	_line;
};

class  UnderflowException : public std::exception
{
public:
	UnderflowException(eOperandType const & type, int line);
	
	virtual const char *what(void) const throw();
	
	~UnderflowException(void) throw() {}

private:
	std::string		_type;

	UnderflowException const & operator=(UnderflowException const & rhs);

public:
	int	_line;
};

class DivisionException : public std::exception
{
public:
	DivisionException(void) : _line(-1) {}
	DivisionException(int line);

	virtual const char *what(void) const throw();
	
	~DivisionException(void) throw() {}

private:
	DivisionException const & operator=(DivisionException const & rhs);

public:
	int	_line;

};

class ModulWithFloat : public std::exception
{
public:
	ModulWithFloat(void) : _line(-1) {}
	ModulWithFloat(eOperandType const & type, int line);

	virtual const char *what(void) const throw();

	~ModulWithFloat(void) throw() {}

private:
	std::string		_type;

	ModulWithFloat const & operator=(ModulWithFloat const & rhs);

public:
	int	 _line;
};

class StackEmptyException : public std::exception
{
public:
	StackEmptyException(void) : _line(-1) {}
	StackEmptyException(int line);

	virtual const char *what(void) const throw();

	~StackEmptyException(void) throw() {}

private:
	StackEmptyException const & operator=(StackEmptyException const & rhs);

public:
	int	 _line;
};

class MinimumException : public std::exception
{
public:
	MinimumException(void) : _line(-1) {}
	MinimumException(int line);

	virtual const char *what(void) const throw();

	~MinimumException(void) throw() {}

private:
	MinimumException const & operator=(MinimumException const & rhs);

public:
	int	_line;
};

class AssertFalseException : public std::exception
{
public:
	AssertFalseException(void) : _line(-1) {}
	AssertFalseException(int line);

	virtual const char *what(void) const throw();

	~AssertFalseException(void) throw() {}

private:
	AssertFalseException const & operator=(AssertFalseException const & rhs);

public:
	int _line;
};

class IncorrectSyntaxException : public std::exception
{
public:
	IncorrectSyntaxException(void) : _line(-1) {}
	IncorrectSyntaxException(int line);

	virtual const char *what(void) const throw();

	~IncorrectSyntaxException(void) throw() {}

private:
	IncorrectSyntaxException const & operator=(IncorrectSyntaxException const & rhs);

public:
	int	_line;
};

#endif
