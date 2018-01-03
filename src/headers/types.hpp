#ifndef IOPERANDS_HPP
# define IOPERANDS_HPP
# include <iostream>
# include <string>
# include "IOperands.hpp"

class 	Int8 : public IOperands
{
public:
	Int8(void);
	Int8(char value);
	Int8(Int8 const & cp);

	char	getValue(void);

	Int8 & 			operator=(Int8 const & cp);
	Int8 const *	operator=(Int8 const * cp);

	~Int8(void) {};

private:
	char	_val;
}

class 	Int16 : public IOperands
{
public:
	Int16(void);
	Int16(short int value);
	Int16(Int16 const & cp);

	short int	getValue(void);

	Int16 & 		operator=(Int16 const & cp);
	Int16 const *	operator=(Int16 const * cp);

	~Int16(void);

private:
	short int	_val;
}

class 	Int32 : public IOperands
{
public:
	Int32(void);
	Int32(int value);
	Int32(Int32 const & cp);

	int		getValue(void);

	Int32 & 		operator=(Int32 const & cp);
	Int32 const *	operator=(Int32 const * cp);

	~Int32(void);

private:
	int		_val;
}

class 	Float : public IOperands
{
public:
	Float(void);
	Float(float value);
	Float(Float const & cp);

	float	getValue(void);

	Float & 		operator=(Float const & cp);
	Float const *	operator=(Float const * cp);

	~Float(void);

private:
	float	_val;
}

class 	Double : public IOperands
{
public:
	Double(void);
	Double(double value);
	Double(Double const & cp);

	double	getValue(void);

	Double & 		operator=(Double const & cp);
	Double const *	operator=(Double const * cp);

	~Double(void);

private:
	double	_val;
}

#endif
