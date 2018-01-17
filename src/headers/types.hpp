#ifndef IOPERANDS_HPP
# define IOPERANDS_HPP
# include <iostream>
# include <string>
# include <climits>
# include <limits>
# include "IOperands.hpp"
# include "exceptions.hpp"

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
				this->_val = static_cast<T>tmp;
			}
			else
			{
				tmp_float = std::stold(value);
				if (find_exceptions(tmp_float, this->_type) == 1)
					throw OverflowException(this->_type, this->_line);
				else if (find_exceptions(tmp_float, this->_type) == -1)
					throw UnderflowException(this->_type, this->_line);
				this->_val = static_cast<T>tmp_float;
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

		res = AVM::vm.createOperand(this->getPrecisionType(rhs),
									std::to_string(this->_val + rhs.getValue()));
		return (res);
	}

	IOperand const * operator-(IOperand const & rhs) const
	{
		IOperand const	*res;

		res = AVM::vm.createOperand(this->getPrecisionType(rhs),
									std::to_string(this->_val - rhs.getValue()));
		return (res);
	}

	IOperand const * operator*(IOperand const & rhs) const
	{
		IOperand const	*res;

		res = AVM::vm.createOperand(this->getPrecisionType(rhs),
									std::to_string(this->_val * rhs.getValue()));
		return (res);
	}

	IOperand const * operator/(IOperand const & rhs) const
	{
		IOperand const	*res;

		res = AVM::vm.createOperand(this->getPrecisionType(rhs),
									std::to_string(this->_val / rhs.getValue()));
		return (res);
	}

	IOperand const * operator%(IOperand const & rhs) const
	{
		IOperand const	*res;

		res = AVM::vm.createOperand(this->getPrecisionType(rhs),
									std::to_string(this->_val % rhs.getValue()));
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
		else if (types == INT32 && (tmp > INT_MAX || tmp < INT_MIN))
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