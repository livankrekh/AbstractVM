#ifndef IOPERANDS_HPP
# define IOPERANDS_HPP
# include <iostream>
# include <string>
# include <climits>
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
					throw UnderflowException();
				this->_val = static_cast<T>tmp;
			}
			else
			{
				this->_val = static_cast<T>std::stod(value);
			}
		}
		catch (std::exception const & e)
		{
			std::cout << e.what();
			exit(0);
		}
	}

	eOperandType	getType(void)
	{
		return (this->_type);
	}

private:
	eOperandType	_type;
	std::string		_stringVal;
	T 				_val;
	long			_line;

	int		find_exceptions(long long tmp, eOperandType const & type) const
	{
		if (type == INT8 && (tmp > SCHAR_MAX || tmp < SCHAR_MIN))
			return (tmp > SCHAR_MAX ? 1 : -1);
		else if (type == INT16 && (tmp > SHRT_MAX || tmp < SHRT_MIN))
			return (tmp > SHRT_MAX ? 1 : -1);
		else if (types == INT32 && (tmp > INT_MAX || tmp < INT_MIN))
			return (tmp > INT_MAX ? 1 : -1);
	}
};

#endif