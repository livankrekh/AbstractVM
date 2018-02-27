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
	std::regex 			reg("((assert|push) (int(8|16|32)|float|double)\([0-9\.]\)|add|sub|mul|div|mod|dump|print|exits|;;|;.*)([\s]|;.*)");

	while (tmp != ";;")
	{
		try
		{
			std::getline(std::cin, tmp);
			if (!std::regex_match(tmp.begin(), tmp.end(), reg))
				throw IncorrectSyntaxException();
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
	VM::vm->printOutput();
}

void	file_input(int argc, char **argv)
{
	std::ifstream 	fs;
	std::string		tmp;
	std::regex 		reg("((assert|push) (int(8|16|32)|float|double)\([0-9\.]\)|add|sub|mul|div|mod|dump|print|exits|;;|;.*)([\s]|;.*)");

	for (int i = 1; i < argc; i++)
	{
		fs.open(argv[i], std::fstream::out);
		while (!fs.eof())
		{
			try
			{
				getline(fs, tmp);
				if (!std::regex_match(tmp.begin(), tmp.end(), reg))
					throw IncorrectSyntaxException();
			}
			catch (std::exception const & e)
			{
				VM::vm->setQueue(e.what());
				std::cout << e.what();
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
