/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liabanzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 15:52:03 by liabanzh          #+#    #+#             */
/*   Updated: 2018/01/28 15:52:04 by liabanzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_HPP
# define TYPES_HPP
# include "exceptions.hpp"
# include <stack>
# include <queue>
# include <climits>
# include <limits>
# include <cfloat>
# include <cmath>

class VM;
typedef IOperand const * (VM::*MFPTR)(long double val) const;

class VM
{
public:
	VM(void);
	~VM(void);

	IOperand const * 	createOperand( eOperandType type, long double val ) const;
	long				getLine(void);
	void				incrementLine(void);

	// with stack

	void				add(void);
	void				sub(void);
	void				mul(void);
	void				div(void);
	void				mod(void);

	//Funcs with stack

	void				stackAdd(const std::string & n, eOperandType const & type);

	void				stackPop(void);
	void				stackDump(void);
	void				stackAssert(eOperandType const & type, long double val);
	void				stackPrint(void);
	void				exitProg(void);
	void				printOutput(void);

	void				setQueue(std::string const & inf);

	static VM 			*vm;

private:
	MFPTR							funcptr[5];
	std::vector<IOperand const *>	_stack;
	std::vector<std::string>		_output;
	unsigned long					_line;

	IOperand const * createInt8( long double val ) const;
	IOperand const * createInt16( long double val ) const;
	IOperand const * createInt32( long double val ) const;
	IOperand const * createFloat( long double val ) const;
	IOperand const * createDouble( long double val ) const;

public:
	IOperand const * createOperand( eOperandType type, const std::string & value ) const;
};

template<typename T>
class Type : public IOperand
{
public:
	Type(void);
	Type(Type const & cp);
	Type(std::string const & value, eOperandType const & type)
	{
		long long	tmp;
		long double tmp_float;

		this->_stringVal = value;
		this->_type = type;
		if (this->_type < FLOAT)
		{
			tmp = std::stoll(value);
			if (find_exceptions(tmp, this->_type) == 1)
				throw OverflowException(this->_type, VM::vm->getLine());
			else if (find_exceptions(tmp, this->_type) == -1)
				throw UnderflowException(this->_type, VM::vm->getLine());
			this->_val = tmp;
		}
		else
		{
			tmp_float = std::stold(value);
			if (find_exceptions(tmp_float, this->_type) == 1)
				throw OverflowException(this->_type, VM::vm->getLine());
			else if (find_exceptions(tmp_float, this->_type) == -1)
				throw UnderflowException(this->_type, VM::vm->getLine());
			this->_val = tmp_float;
		}
	}

	Type(T val, eOperandType const & type)
	{
		this->_type = type;

		if (this->_type < FLOAT)
		{
			this->_stringVal = std::to_string( static_cast<long long>(val) );

			if (find_exceptions(val, this->_type) == 1)
				throw OverflowException(this->_type, VM::vm->getLine());
			else if (find_exceptions(val, this->_type) == -1)
				throw UnderflowException(this->_type, VM::vm->getLine());

			this->_val = val;
		}
		else
		{
			this->_stringVal = std::to_string(val);

			if (find_exceptions(val, this->_type) == 1)
				throw OverflowException(this->_type, VM::vm->getLine());
			else if (find_exceptions(val, this->_type) == -1)
				throw UnderflowException(this->_type, VM::vm->getLine());

			this->_val = val;
		}
	}

	IOperand const * operator+(IOperand const & rhs) const
	{
		IOperand const	*res;
		Type 			*cpy;
		long double 	tmp;
		eOperandType	type;

		cpy = reinterpret_cast<Type*>(const_cast<IOperand*>(&rhs));
		tmp = this->_val + cpy->getValue();
		type = this->getPrecisionType(rhs);
		if (find_exceptions(tmp, type) < 0)
			throw UnderflowException(type, VM::vm->getLine());
		else if (find_exceptions(tmp, type) > 0)
			throw OverflowException(type, VM::vm->getLine());
		res = VM::vm->createOperand( type, std::to_string(tmp) );
		return (res);
	}

	IOperand const * operator-(IOperand const & rhs) const
	{
		IOperand const	*res;
		Type 			*cpy;
		long double		tmp;
		eOperandType	type;

		cpy = reinterpret_cast<Type*>(const_cast<IOperand*>(&rhs));
		tmp = this->_val - cpy->getValue();
		type = this->getPrecisionType(rhs);
		if (find_exceptions(tmp, type) < 0)
			throw UnderflowException(type, VM::vm->getLine());
		else if (find_exceptions(tmp, type) > 0)
			throw OverflowException(type, VM::vm->getLine());
		res = VM::vm->createOperand(type, std::to_string(tmp) );
		return (res);
	}

	IOperand const * operator*(IOperand const & rhs) const
	{
		IOperand const	*res;
		Type 			*cpy;
		long double		tmp;
		eOperandType	type;

		cpy = reinterpret_cast<Type*>(const_cast<IOperand*>(&rhs));
		tmp = this->_val * cpy->getValue();

		type = this->getPrecisionType(rhs);
		if (find_exceptions(tmp, type) < 0)
			throw OverflowException(type, VM::vm->getLine());
		else if (find_exceptions(tmp, type) > 0)
			throw UnderflowException(type, VM::vm->getLine());
		res = VM::vm->createOperand( type, std::to_string(tmp) );
		return (res);
	}

	IOperand const * operator/(IOperand const & rhs) const
	{
		IOperand const	*res;
		Type 			*cpy;
		long double		tmp;
		eOperandType	type;

		cpy = reinterpret_cast<Type*>(const_cast<IOperand*>(&rhs));
		if (cpy->getValue() == 0)
			throw DivisionException();
		tmp = this->_val / cpy->getValue();
		type = this->getPrecisionType(rhs);
		res = VM::vm->createOperand( type, std::to_string(tmp) );
		return (res);
	}

	IOperand const * operator%(IOperand const & rhs) const
	{
		IOperand const	*res;
		Type 			*cpy;
		long double		tmp;
		eOperandType	type;

		cpy = reinterpret_cast<Type*>(const_cast<IOperand*>(&rhs));
		if (cpy->getValue() == 0)
			throw DivisionException();
		type = this->getPrecisionType(rhs);
		if (type >= FLOAT)
			throw ModulWithFloat(type, VM::vm->getLine());
		tmp = static_cast<int>(this->_val) % static_cast<int>(cpy->getValue());
		res = VM::vm->createOperand( type, std::to_string(tmp) );
		return (res);
	}

	int 			getPrecision(void) const
	{
		return (this->_type);
	}

	eOperandType	getType(void) const
	{
		return (this->_type);
	}

	T const &		getValue(void) const
	{
		return (this->_val);
	}

	std::string const & toString(void) const
	{
		return (this->_stringVal);
	}

	template<typename V>
	static int		find_exceptions(V tmp, eOperandType const & type)
	{
		if (type == INT8 && (tmp > SCHAR_MAX || tmp < SCHAR_MIN))
			return (tmp > SCHAR_MAX ? 1 : -1);
		else if (type == INT16 && (tmp > SHRT_MAX || tmp < SHRT_MIN))
			return (tmp > SHRT_MAX ? 1 : -1);
		else if (type == INT32 && (tmp > INT_MAX || tmp < INT_MIN))
			return (tmp > INT_MAX ? 1 : -1);
		else if (type == FLOAT && (tmp > FLT_MAX 
				|| tmp < -FLT_MAX))
			return (tmp > FLT_MAX ? 1 : -1);
		else if (type == DOUBLE && (tmp > DBL_MAX
				|| tmp < -DBL_MAX))
			return (tmp > DBL_MAX ? 1 : -1);
		return (0);
	}

private:
	eOperandType	_type;
	std::string		_stringVal;
	T 				_val;

	eOperandType	getPrecisionType(IOperand const & rhs) const
	{
		return (this->getPrecision() >= rhs.getPrecision()
			? this->getType() : rhs.getType());
	}
};

#endif
