#ifndef VM_HPP
# define VM_HPP
# include <stack>
# include <queue>
# include "IOperands.hpp"

template<typename T>
class Types;

class VM
{
public:
	VM(void);
	~VM(void);

	IOperand const * createOperand( eOperandType type, std::string const & value ) const;
	
private:
	IOperand const * (*funcptr[5])(std::string const & value);
	std::stack<IOperand*>	_stack;
	std::queue<std::string>	_output;

	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;
};

namespace AVM
{
	VM 	vm;
}

#endif
