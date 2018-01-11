#ifndef IOPERANDS_HPP
# define IOPERANDS_HPP
# include <iostream>
# include <string>
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
		T	tmp;

		this->_stringVal = value;
		this->_type = type;
		try 
		{
			tmp = std::stoll(value);
			if ()
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
};

#endif