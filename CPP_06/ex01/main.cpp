/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:22:32 by conobi            #+#    #+#             */
/*   Updated: 2023/01/13 15:21:30 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

int main(void) {
	Data *test0;
	Data *test1;
	uintptr_t test0_ptr;

	test0 = new Data;
	(*test0).str0 = "Bidule";
	(*test0).str1 = "Truc";
	(*test0).str2 = "Machin";

	std::cout << "--- test0 ---" << std::endl;
	std::cout << (*test0).str0 << ", " << (*test0).str1 << ", " << (*test0).str2
			  << std::endl;

	std::cout << std::endl << "--- serialize ---" << std::endl;
	test0_ptr = serialize(test0);
	std::cout << test0_ptr << std::endl;

	std::cout << std::endl
			  << "--- test1 (deserialized test0_ptr) ---" << std::endl;

	test1 = deserialize(test0_ptr);
	std::cout << (*test1).str0 << ", " << (*test1).str1 << ", " << (*test1).str2
			  << std::endl;

	delete test0;
	return (0);
}