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
	OverflowException(void);
	OverflowException(eOperandType const & type, int line);
	
	virtual const char *what(void) const throw();
	
	~OverflowException(void) throw() {}

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
	
	~UnderflowException(void) throw() {}

private:
	std::string		_type;
	int				_line;

	UnderflowException const & operator=(UnderflowException const & rhs);
};

class DivisionException : public std::exception
{
public:
	DivisionException(void) {}

	virtual const char *what(void) const throw();
	
	~DivisionException(void) throw() {}

private:
	DivisionException const & operator=(DivisionException const & rhs);

};

class ModulWithFloat : public std::exception
{
public:
	ModulWithFloat(void);
	ModulWithFloat(eOperandType const & type, int line);

	virtual const char *what(void) const throw();

	~ModulWithFloat(void) throw() {}

private:
	int				_line;
	std::string		_type;

	ModulWithFloat const & operator=(ModulWithFloat const & rhs);
};

class StackEmptyException : public std::exception
{
public:
	StackEmptyException(void) {}

	virtual const char *what(void) const throw();

	~StackEmptyException(void) throw() {}
};

class MinimumException : public std::exception
{
public:
	MinimumException(void) {}

	virtual const char *what(void) const throw();

	~MinimumException(void) throw() {}
};

class AssertFalseException : public std::exception
{
public:
	AssertFalseException(void) {}

	virtual const char *what(void) const throw();

	~AssertFalseException(void) throw() {}
};

class IncorrectSyntaxException : public std::exception
{
public:
	IncorrectSyntaxException(void) {}

	virtual const char *what(void) const throw();

	~IncorrectSyntaxException(void) throw() {}
};

#endif
