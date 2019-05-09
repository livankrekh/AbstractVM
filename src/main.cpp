/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liabanzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 15:40:54 by liabanzh          #+#    #+#             */
/*   Updated: 2018/01/28 15:40:55 by liabanzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/types.hpp"
#include <fstream>
#include <regex>
#include <sstream>

void	stdin_input(void)
{
	std::string 		tmp;
	std::regex			commands_without_arguments("^(pop|dump|add|sub|mul|div|mod|print|exit|;;|;.*)$");
	std::regex			commands_with_arguments_int("^(push|assert) (int8|int16|int32)\\(([\\-]?[0-9]+)\\)\\s*(;.*)?$");
	std::regex			commands_with_arguments_float_double("^(push|assert) (float|double)\\(([\\-]?[0-9]+\\.[0-9]+)\\)\\s*(;.*)?$");
	std::regex			empty_line("^\\s*$");
	bool				exit;

	while (tmp != ";;")
	{
		try
		{
			std::getline(std::cin, tmp);
			if (tmp == ";;")
				break;
			if (std::regex_match(tmp.begin(), tmp.end(), empty_line)) {
				continue;
			}
			exit = false;
			if (std::regex_match(tmp.begin(), tmp.end(), commands_without_arguments)) {
				if (tmp.rfind("pop", 0) == 0) {
					VM::vm->stackPop();
				}
				else if (tmp.rfind("add", 0) == 0) {
					VM::vm->add();
				}
				else if (tmp.rfind("sub", 0) == 0) {
					VM::vm->sub();
				}
				else if (tmp.rfind("mul", 0) == 0) {
					VM::vm->mul();
				}
				else if (tmp.rfind("div", 0) == 0) {
					VM::vm->div();
				}
				else if (tmp.rfind("print", 0) == 0) {
					VM::vm->stackPrint();
				}
				else if (tmp.rfind("mod", 0) == 0) {
					VM::vm->mod();
				}
				else if (tmp.rfind("dump", 0) == 0) {
					VM::vm->stackDump();
				}
				else if (tmp.rfind("exit", 0) == 0) {
					VM::vm->exitProg();
					VM::vm->printOutput();
					exit = true;
				}
			}
			else if (std::regex_match(tmp.begin(), tmp.end(), commands_with_arguments_float_double)) {
				std::string type = tmp.substr(tmp.find(" ") + 1, tmp.size());

				if (tmp.rfind("push", 0) == 0) {
					long double val = std::stod(type.substr(type.find("(") + 1, type.size() ));

					if (type.rfind("float", 0) == 0) {
						int except = Type<float>::find_exceptions(val, FLOAT);

						if (except == 1)
							throw OverflowException(FLOAT, VM::vm->getLine());
						else if (except == -1)
							throw UnderflowException(FLOAT, VM::vm->getLine());
						VM::vm->stackAdd( std::stof(type.substr(type.find("(") + 1, type.size() )) );
					}
					else if (type.rfind("double", 0) == 0) {
						int except = Type<double>::find_exceptions(val, DOUBLE);

						if (except == 1)
							throw OverflowException(DOUBLE, VM::vm->getLine());
						else if (except == -1)
							throw UnderflowException(DOUBLE, VM::vm->getLine());
						VM::vm->stackAdd( std::stod(type.substr(type.find("(") + 1, type.size() )) );
					}
				}
				else if (tmp.rfind("assert", 0) == 0) {
					if (type.rfind("float", 0) == 0) {
						VM::vm->stackAssert(FLOAT, std::stof(type.substr(type.find("(") + 1, type.size() )) );
					}
					else if (type.rfind("double", 0) == 0) {
						VM::vm->stackAssert(DOUBLE, std::stod(type.substr(type.find("(") + 1, type.size() )) );
					}
				}
			}
			else if (std::regex_match(tmp.begin(), tmp.end(), commands_with_arguments_int)) {
				std::string type = tmp.substr(tmp.find(" ") + 1, tmp.size());

				if (tmp.rfind("push", 0) == 0) {
					long long val = std::stoll(type.substr(type.find("(") + 1, type.size() ));

					if (type.rfind("int8", 0) == 0) {
						int except = Type<char>::find_exceptions(val, INT8);

						if (except == 1)
							throw OverflowException(INT8, VM::vm->getLine());
						else if (except == -1)
							throw UnderflowException(INT8, VM::vm->getLine());
						VM::vm->stackAdd( static_cast<char>( std::stoi(type.substr(type.find("(") + 1, type.size() )) ) );
					}
					else if (type.rfind("int16", 0) == 0) {
						int except = Type<short int>::find_exceptions(val, INT16);

						if (except == 1)
							throw OverflowException(INT16, VM::vm->getLine());
						else if (except == -1)
							throw UnderflowException(INT16, VM::vm->getLine());
						VM::vm->stackAdd( static_cast<short int>( std::stoi(type.substr(type.find("(") + 1, type.size() )) ) );
					}
					else if (type.rfind("int32", 0) == 0) {
						int except = Type<int>::find_exceptions(val, INT32);

						if (except == 1)
							throw OverflowException(INT32, VM::vm->getLine());
						else if (except == -1)
							throw UnderflowException(INT32, VM::vm->getLine());
						VM::vm->stackAdd( std::stoi(type.substr(type.find("(") + 1, type.size() )) );
					}
				}
				if (tmp.rfind("assert", 0) == 0) {
					long long val = std::stoll(type.substr(type.find("(") + 1, type.size() ));

					if (type.rfind("int8", 0) == 0) {
						int except = Type<char>::find_exceptions(val, INT8);

						if (except == 1)
							throw OverflowException(INT8, VM::vm->getLine());
						else if (except == -1)
							throw UnderflowException(INT8, VM::vm->getLine());
						VM::vm->stackAssert(INT8, val);
					}
					else if (type.rfind("int16", 0) == 0) {
						int except = Type<char>::find_exceptions(val, INT16);

						if (except == 1)
							throw OverflowException(INT16, VM::vm->getLine());
						else if (except == -1)
							throw UnderflowException(INT16, VM::vm->getLine());
						VM::vm->stackAssert(INT16, val);
					}
					else if (type.rfind("int32", 0) == 0) {
						int except = Type<char>::find_exceptions(val, INT32);

						if (except == 1)
							throw OverflowException(INT32, VM::vm->getLine());
						else if (except == -1)
							throw UnderflowException(INT32, VM::vm->getLine());
						VM::vm->stackAssert(INT32, val);
					}
				}
			}
			else
			{
				throw IncorrectSyntaxException();
			}
		}
		catch (std::exception const & e)
		{
			std::stringstream	out;

			if (strlen(e.what()) > 1 && e.what()[strlen(e.what()) - 1] == '#')
				out << e.what() << VM::vm->getLine();
			else
				out << e.what();
			VM::vm->setQueue(out.str());
		}
		VM::vm->incrementLine();
	}
	try
	{
		if (!exit)
			throw NoExitException();
	}
	catch (std::exception const & e)
	{
		std::stringstream	out;

		out << e.what();
		VM::vm->setQueue(out.str());
	}

	VM::vm->printOutput();
	VM::vm->exitProg();
}

void	file_input(int argc, char **argv)
{
	std::stringstream	out;
	std::ifstream 		fs;
	std::string			tmp;
	std::regex			commands_without_arguments("^(pop|dump|add|sub|mul|div|mod|print|exit|;;|;.*)$");
	std::regex			commands_with_arguments_int("^(push|assert) (int8|int16|int32)\\(([\\-]?[0-9]+)\\)\\s*(;.*)?$");
	std::regex			commands_with_arguments_float_double("^(push|assert) (float|double)\\(([\\-]?[0-9]+\\.[0-9]+)\\)\\s*(;.*)?$");
	std::regex			empty_line("^\\s*$");
	bool				exit;

	for (int i = 1; i < argc; i++)
	{
		fs.open(argv[i], std::fstream::out);
		while (!fs.eof())
		{
			try
			{
				getline(fs, tmp);

				if (tmp == ";;")
					break;
				if (std::regex_match(tmp.begin(), tmp.end(), empty_line)) {
					continue;
				}

				exit = false;

				if (std::regex_match(tmp.begin(), tmp.end(), commands_without_arguments)) {
					if (tmp.rfind("pop", 0) == 0) {
						VM::vm->stackPop();
					}
					else if (tmp.rfind("add", 0) == 0) {
						VM::vm->add();
					}
					else if (tmp.rfind("sub", 0) == 0) {
						VM::vm->sub();
					}
					else if (tmp.rfind("mul", 0) == 0) {
						VM::vm->mul();
					}
					else if (tmp.rfind("div", 0) == 0) {
						VM::vm->div();
					}
					else if (tmp.rfind("print", 0) == 0) {
						VM::vm->stackPrint();
					}
					else if (tmp.rfind("mod", 0) == 0) {
						VM::vm->mod();
					}
					else if (tmp.rfind("dump", 0) == 0) {
						VM::vm->stackDump();
					}
					else if (tmp.rfind("exit", 0) == 0) {
						VM::vm->exitProg();
						exit = true;
					}
				}
				else if (std::regex_match(tmp.begin(), tmp.end(), commands_with_arguments_float_double)) {
					std::string type = tmp.substr(tmp.find(" ") + 1, tmp.size());

					if (tmp.rfind("push", 0) == 0) {
						long double val = std::stold(type.substr(type.find("(") + 1, type.size() ));

						if (type.rfind("float", 0) == 0) {
							int except = Type<float>::find_exceptions(val, FLOAT);

							if (except == 1)
								throw OverflowException(FLOAT, VM::vm->getLine());
							else if (except == -1)
								throw UnderflowException(FLOAT, VM::vm->getLine());
							VM::vm->stackAdd( std::stof(type.substr(type.find("(") + 1, type.size() )) );
						}
						else if (type.rfind("double", 0) == 0) {
							int except = Type<double>::find_exceptions(val, DOUBLE);

							if (except == 1)
								throw OverflowException(DOUBLE, VM::vm->getLine());
							else if (except == -1)
								throw UnderflowException(DOUBLE, VM::vm->getLine());
							VM::vm->stackAdd( std::stod(type.substr(type.find("(") + 1, type.size() )) );
						}
					}
					else if (tmp.rfind("assert", 0) == 0) {
						if (type.rfind("float", 0) == 0) {
							VM::vm->stackAssert(FLOAT, std::stof(type.substr(type.find("(") + 1, type.size() )) );
						}
						else if (type.rfind("double", 0) == 0) {
							VM::vm->stackAssert(DOUBLE, std::stod(type.substr(type.find("(") + 1, type.size() )) );
						}
					}
				}
				else if (std::regex_match(tmp.begin(), tmp.end(), commands_with_arguments_int)) {
					std::string type = tmp.substr(tmp.find(" ") + 1, tmp.size());

					if (tmp.rfind("push", 0) == 0) {
						long long val = std::stoll(type.substr(type.find("(") + 1, type.size() ));

						if (type.rfind("int8", 0) == 0) {
							int except = Type<char>::find_exceptions(val, INT8);

							if (except == 1)
								throw OverflowException(INT8, VM::vm->getLine());
							else if (except == -1)
								throw UnderflowException(INT8, VM::vm->getLine());
							VM::vm->stackAdd( static_cast<char>( std::stoi(type.substr(type.find("(") + 1, type.size() )) ) );
						}
						else if (type.rfind("int16", 0) == 0) {
							int except = Type<short int>::find_exceptions(val, INT16);

							if (except == 1)
								throw OverflowException(INT16, VM::vm->getLine());
							else if (except == -1)
								throw UnderflowException(INT16, VM::vm->getLine());
							VM::vm->stackAdd( static_cast<short int>( std::stoi(type.substr(type.find("(") + 1, type.size() )) ) );
						}
						else if (type.rfind("int32", 0) == 0) {
							int except = Type<int>::find_exceptions(val, INT32);

							if (except == 1)
								throw OverflowException(INT32, VM::vm->getLine());
							else if (except == -1)
								throw UnderflowException(INT32, VM::vm->getLine());
							VM::vm->stackAdd( std::stoi(type.substr(type.find("(") + 1, type.size() )) );
						}
					}
					if (tmp.rfind("assert", 0) == 0) {
						long long val = std::stoll(type.substr(type.find("(") + 1, type.size() ));

						if (type.rfind("int8", 0) == 0) {
							int except = Type<char>::find_exceptions(val, INT8);

							if (except == 1)
								throw OverflowException(INT8, VM::vm->getLine());
							else if (except == -1)
								throw UnderflowException(INT8, VM::vm->getLine());
							VM::vm->stackAssert(INT8, val);
						}
						else if (type.rfind("int16", 0) == 0) {
							int except = Type<char>::find_exceptions(val, INT16);

							if (except == 1)
								throw OverflowException(INT16, VM::vm->getLine());
							else if (except == -1)
								throw UnderflowException(INT16, VM::vm->getLine());
							VM::vm->stackAssert(INT16, val);
						}
						else if (type.rfind("int32", 0) == 0) {
							int except = Type<char>::find_exceptions(val, INT32);

							if (except == 1)
								throw OverflowException(INT32, VM::vm->getLine());
							else if (except == -1)
								throw UnderflowException(INT32, VM::vm->getLine());
							VM::vm->stackAssert(INT32, val);
						}
					}
				}
				else
				{
					throw IncorrectSyntaxException();
				}
			}
			catch (std::exception const & e)
			{
				if (strlen(e.what()) > 1 && e.what()[strlen(e.what()) - 1] == '#')
					out << e.what() << VM::vm->getLine() << std::endl;
				else
					out << e.what();
				VM::vm->setQueue(out.str());
			}
			VM::vm->incrementLine();
		}
		fs.close();
		try
		{
			if (!exit)
				throw NoExitException();
		}
		catch (std::exception const & e)
		{
			out << e.what() << std::endl;
			VM::vm->setQueue(out.str());
		}
		VM::vm->printOutput();
		VM::vm->exitProg();
	}
}

int		main(int argc, char **argv)
{
	VM		*vm_main = new VM;

	VM::vm = vm_main;
	if (argc == 1)
		stdin_input();
	else
		file_input(argc, argv);
	delete vm_main;
	return (0);
}
