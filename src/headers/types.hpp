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

class VM;
typedef IOperand const * (VM::*MFPTR)(std::string const & value) const;

class VM
{
public:
	VM(void);
	~VM(void);

	IOperand const * 	createOperand( eOperandType type, std::string const & value ) const;
	long				getLine(void);
	void				incrementLine(void);

	// with stack

	void				add(void);
	void				sub(void);
	void				mul(void);
	void				div(void);
	void				mod(void);

	//Funcs with stack

	void				stackAdd(char n);
	void				stackAdd(short int n);
	void				stackAdd(int n);
	void				stackAdd(float n);
	void				stackAdd(double n);

	void				stackPop(void);
	void				stackDump(void);
	bool				stackAssert(eOperandType const & type, long double val);
	void				stackPrint(void);
	void				exitProg(void);

	void				setQueue(std::string const & inf);

private:
	MFPTR							funcptr[5];
	std::vector<IOperand const *>	_stack;
	std::vector<std::string>		_output;
	unsigned long					_line;

	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;
};

namespace AVM
{
	VM 		*vm;
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
		try
		{
			if (this->_type < FLOAT)
			{
				tmp = std::stoll(value);
				if (find_exceptions(tmp, this->_type) == 1)
					throw OverflowException(this->_type, AVM::vm->getLine());
				else if (find_exceptions(tmp, this->_type) == -1)
					throw UnderflowException(this->_type, AVM::vm->getLine());
				this->_val = static_cast<T>(tmp);
			}
			else
			{
				tmp_float = std::stold(value);
				if (find_exceptions(tmp_float, this->_type) == 1)
					throw OverflowException(this->_type, AVM::vm->getLine());
				else if (find_exceptions(tmp_float, this->_type) == -1)
					throw UnderflowException(this->_type, AVM::vm->getLine());
				this->_val = static_cast<T>(tmp_float);
			}
		}
		catch (std::exception const & e)
		{
			std::cout << e.what();
			exit(0);
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
			throw UnderflowException(type, AVM::vm->getLine());
		else
			throw OverflowException(type, AVM::vm->getLine());
		res = AVM::vm->createOperand(type,
						std::to_string(type < FLOAT ? static_cast<long>(tmp) : tmp));
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
			throw UnderflowException(type, AVM::vm->getLine());
		else
			throw OverflowException(type, AVM::vm->getLine());
		res = AVM::vm->createOperand(type,
						std::to_string(type < FLOAT ? static_cast<long>(tmp) : tmp));
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
			throw OverflowException(type, AVM::vm->getLine());
		else
			throw UnderflowException(type, AVM::vm->getLine());
		res = AVM::vm->createOperand(type,
						std::to_string(type < FLOAT ? static_cast<long>(tmp) : tmp));
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
			throw DivisionException(AVM::vm->getLine());
		tmp = this->_val / cpy->getValue();
		type = this->getPrecisionType(rhs);
		res = AVM::vm->createOperand(type,
						std::to_string(type < FLOAT ? static_cast<long>(tmp) : tmp));
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
			throw DivisionException(AVM::vm->getLine());
		type = this->getPrecisionType(rhs);
		if (type >= FLOAT)
			throw ModulWithFloat(type, AVM::vm->getLine());
		tmp = static_cast<int>(this->_val) % static_cast<int>(cpy->getValue());
		res = AVM::vm->createOperand(type,
						std::to_string(static_cast<long>(tmp)));
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

private:
	eOperandType	_type;
	std::string		_stringVal;
	T 				_val;

	template<typename V>
	int		find_exceptions(V tmp, eOperandType const & type) const
	{
		if (type == INT8 && (tmp > SCHAR_MAX || tmp < SCHAR_MIN))
			return (tmp > SCHAR_MAX ? 1 : -1);
		else if (type == INT16 && (tmp > SHRT_MAX || tmp < SHRT_MIN))
			return (tmp > SHRT_MAX ? 1 : -1);
		else if (type == INT32 && (tmp > INT_MAX || tmp < INT_MIN))
			return (tmp > INT_MAX ? 1 : -1);
		else if (type == FLOAT && (tmp > std::numeric_limits<float>::max() 
			|| tmp < std::numeric_limits<float>::lowest()))
			return (tmp > std::numeric_limits<float>::max() ? 1 : -1);
		else if (type == DOUBLE && (tmp > std::numeric_limits<double>::max()
			|| tmp < std::numeric_limits<double>::lowest()))
			return (tmp > std::numeric_limits<double>::max() ? 1 : -1);
		return (0);
	}

	eOperandType	getPrecisionType(IOperand const & rhs) const
	{
		return (this->getPrecision() >= rhs.getPrecision()
			? this->getType() : rhs.getType());
	}
};

#endif
