#ifndef TYPES_HPP
# define TYPES_HPP
# include <iostream>
# include <string>
# include <stack>
# include <queue>
# include <climits>
# include <limits>
# include "exceptions.hpp"

class VM;
typedef IOperand const * (VM::*MFPTR)(std::string const & value) const;

class VM
{
public:
	VM(void);
	~VM(void);

	IOperand const * createOperand( eOperandType type, std::string const & value ) const;
	
private:
	MFPTR					funcptr[5];
	std::stack<IOperand*>	_stack;
	std::queue<std::string>	_output;

	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;
};

template<typename T>
class Type : public IOperand
{
public:
	VM 				vm;

	Type(void);
	Type(Type const & cp);
	Type(std::string const & value, eOperandType const & type)
	{
		long long	tmp;
		long double tmp_float;

		this->_stringVal = value;
		this->_type = type;
		this->_line = 1;
		try 
		{
			if (this->_type < FLOAT)
			{
				tmp = std::stoll(value);
				if (find_exceptions(tmp, this->_type) == 1)
					throw OverflowException(this->_type, this->_line);
				else if (find_exceptions(tmp, this->_type) == -1)
					throw UnderflowException(this->_type, this->_line);
				this->_val = static_cast<T>(tmp);
			}
			else
			{
				tmp_float = std::stold(value);
				if (find_exceptions(tmp_float, this->_type) == 1)
					throw OverflowException(this->_type, this->_line);
				else if (find_exceptions(tmp_float, this->_type) == -1)
					throw UnderflowException(this->_type, this->_line);
				this->_val = static_cast<T>(tmp_float);
			}
		}
		catch (std::exception const & e)
		{
			std::cout << e.what();
			exit(0);
		}
	}

	//TODO: Exception conditions in operators

	IOperand const * operator+(IOperand const & rhs) const
	{
		IOperand const	*res;
		Type 			*cpy;

		cpy = reinterpret_cast<Type*>(const_cast<IOperand*>(&rhs));
		res = vm.createOperand(this->getPrecisionType(rhs),
									std::to_string(this->_val + cpy->getValue()));
		return (res);
	}

	IOperand const * operator-(IOperand const & rhs) const
	{
		IOperand const	*res;
		Type 			*cpy;

		cpy = reinterpret_cast<Type*>(const_cast<IOperand*>(&rhs));
		res = vm.createOperand(this->getPrecisionType(rhs),
									std::to_string(this->_val - cpy->getValue()));
		return (res);
	}

	IOperand const * operator*(IOperand const & rhs) const
	{
		IOperand const	*res;
		Type 			*cpy;

		cpy = reinterpret_cast<Type*>(const_cast<IOperand*>(&rhs));
		res = vm.createOperand(this->getPrecisionType(rhs),
									std::to_string(this->_val * cpy->getValue()));
		return (res);
	}

	IOperand const * operator/(IOperand const & rhs) const
	{
		IOperand const	*res;
		Type 			*cpy;

		cpy = reinterpret_cast<Type*>(const_cast<IOperand*>(&rhs));
		res = vm.createOperand(this->getPrecisionType(rhs),
									std::to_string(this->_val / cpy->getValue()));
		return (res);
	}

	IOperand const * operator%(IOperand const & rhs) const
	{
		IOperand const	*res;
		Type 			*cpy;

		cpy = reinterpret_cast<Type*>(const_cast<IOperand*>(&rhs));
		res = vm.createOperand(this->getPrecisionType(rhs),
									std::to_string(static_cast<int>(this->_val) % static_cast<int>(cpy->getValue())));
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
	long			_line;

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