#ifndef VM_HPP
# define VM_HPP
# include <stack>
# include <queue>
# include "types.hpp"

class VM
{
public:
	VM(void);
	VM(VM const & cp) {}
	~VM();

	IOperand const * createOperand( eOperandType type, std::string const & value ) const;
	
private:
	IOperand const * (*functptr[5])(std::string const & value);
	std::stack	_stack;
	std::queue	_output;

	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;
};

#endif
