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
	std::stringstream	out;
	std::string 		tmp;
	std::regex			commands_without_arguments("^(pop|dump|add|sub|mul|div|mod|print|exit|;;|;.+)$");
	std::regex			commands_with_arguments_int("^(push|assert) (int8|int16|int32)\\(([\\-]?[0-9]+)\\)$");
	std::regex			commands_with_arguments_float_double("^(push|assert) (float|double)\\(([\\-]?[0-9]+\\.[0-9]+)\\)$");
	std::regex			empty_line("^\\s*$");

	while (tmp != ";;")
	{
		try
		{
			std::getline(std::cin, tmp);
			if (std::regex_match(tmp.begin(), tmp.end(), empty_line)) {
				continue;
			}
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
					VM::vm->printOutput();
				}
				else if (tmp.rfind("mod", 0) == 0) {
					VM::vm->mod();
				}
				else if (tmp.rfind("dump", 0) == 0) {
					VM::vm->stackDump();
					VM::vm->printOutput();
				}
				else if (tmp.rfind("exit", 0) == 0) {
					VM::vm->exitProg();
					VM::vm->printOutput();
				}
			}
			else if (std::regex_match(tmp.begin(), tmp.end(), commands_with_arguments_float_double)) {
				std::string type = tmp.substr(tmp.find(" ") + 1, tmp.size());

				if (tmp.rfind("push", 0) == 0) {
					if (type.rfind("float", 0) == 0) {
						VM::vm->stackAdd( std::stof(type.substr(type.find("(") + 1, type.size() )) );
					}
					else if (type.rfind("double", 0) == 0) {
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
					if (type.rfind("int8", 0) == 0) {
						VM::vm->stackAdd( static_cast<char>( std::stoi(type.substr(type.find("(") + 1, type.size() )) ) );
					}
					else if (type.rfind("int16", 0) == 0) {
						VM::vm->stackAdd( static_cast<short int>( std::stoi(type.substr(type.find("(") + 1, type.size() )) ) );
					}
					else if (type.rfind("int32", 0) == 0) {
						VM::vm->stackAdd( std::stoi(type.substr(type.find("(") + 1, type.size() )) );
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
			out << e.what() << VM::vm->getLine() << std::endl;
			VM::vm->setQueue(out.str());
			std::cout << e.what() << VM::vm->getLine() << std::endl;
		}
		VM::vm->incrementLine();
	}
	VM::vm->exitProg();
	// VM::vm->printOutput();
}

void	file_input(int argc, char **argv)
{
	std::ifstream 	fs;
	std::string		tmp;
	std::regex		commands_without_arguments("^(pop|dump|add|sub|mul|div|mod|print|exit|;;|;.+)$");
	std::regex		commands_with_arguments_int("^(push|assert) (int8|int16|int32)\\(([\\-]?[0-9]+)\\)$");
	std::regex		commands_with_arguments_float_double("^(push|assert) (float|double)\\(([\\-]?[0-9]+\\.[0-9]+)\\)$");
	std::regex		empty_line("^\\s*$");

	for (int i = 1; i < argc; i++)
	{
		fs.open(argv[i], std::fstream::out);
		while (!fs.eof())
		{
			try
			{
				getline(fs, tmp);
				if (std::regex_match(tmp.begin(), tmp.end(), empty_line)) {
					continue;
				}
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
					}
				}
				else if (std::regex_match(tmp.begin(), tmp.end(), commands_with_arguments_float_double)) {
					std::string type = tmp.substr(tmp.find(" ") + 1, tmp.size());

					if (tmp.rfind("push", 0) == 0) {
						if (type.rfind("float", 0) == 0) {
							VM::vm->stackAdd( std::stof(type.substr(type.find("(") + 1, type.size() )) );
						}
						else if (type.rfind("double", 0) == 0) {
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
						if (type.rfind("int8", 0) == 0) {
							VM::vm->stackAdd( static_cast<char>( std::stoi(type.substr(type.find("(") + 1, type.size() )) ) );
						}
						else if (type.rfind("int16", 0) == 0) {
							VM::vm->stackAdd( static_cast<short int>( std::stoi(type.substr(type.find("(") + 1, type.size() )) ) );
						}
						else if (type.rfind("int32", 0) == 0) {
							VM::vm->stackAdd( std::stoi(type.substr(type.find("(") + 1, type.size() )) );
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
				VM::vm->setQueue(e.what());
			}
			VM::vm->incrementLine();
		}
		fs.close();
		VM::vm->exitProg();
		VM::vm->printOutput();
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
