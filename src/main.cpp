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

void	stdin_input(void)
{
	std::string 	tmp;
	std::regex reg("((assert|push) (int(8|16|32)|float|double)\([0-9\.]\)|add|sub|mul|div|mod|dump|print|exits|;;|;.*)([\s]|;.*)");

	while (tmp != ";;")
	{
		try
		{
			std::getline(std::cin, tmp);
			if (!std::regex_match(tmp.begin(), tmp.end(), reg))
				throw IncorrectSyntaxException(AVM::vm->getLine());
		}
		catch (std::exception const & e)
		{
			AVM::vm->setQueue(e.what());
			std::cout << e.what();
		}
		AVM::vm->incrementLine();
	}
}

int		main(int argc, char **argv)
{
	VM		*vm_main = new VM;

	AVM::vm = vm_main;
	if (argc == 2)
		stdin_input();
	// else
	// 	file_input(argv);
	argv = NULL;
	delete vm_main;
	return (0);
}
