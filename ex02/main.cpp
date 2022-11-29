/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:23:26 by conobi            #+#    #+#             */
/*   Updated: 2022/11/29 17:33:02 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>

int main (void) {
	std::string hibrain =  "HI THIS IS BRAIN";
	std::string *stringPTR = &hibrain;
	std::string &stringREF = hibrain;

	std::cout << "hibrain address:" << &hibrain << std::endl;
	std::cout << "stringPTR address:" << &(*stringPTR) << std::endl;
	std::cout << "stringREF address:" << &stringREF << std::endl << std::endl;

	std::cout << "hibrain content:" << hibrain << std::endl;
	std::cout << "stringPTR content:" << *stringPTR << std::endl;
	std::cout << "stringREF content:" << stringREF << std::endl;

	return (0);
}
