/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:46:44 by conobi            #+#    #+#             */
/*   Updated: 2022/12/26 17:57:36 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

int main (void) {
	const Animal *animals[6];
	const Animal *softcpy[6];
	const Animal *deepcpy[6];

	std::cout << "------------ 00 ------------" << std::endl;

	for (size_t i = 0; i < 6; i++) {
		if (i >= 3) {
			animals[i] = new Cat;
		} else {
			animals[i] = new Dog;
		}
	}

	std::cout << "------------ 01 ------------" << std::endl;

	for (size_t i = 0; i < 6; i++) {
		softcpy[i] = animals[i];
		softcpy[i]->debugAddresses();
	}

	std::cout << "------------ 02 ------------" << std::endl;
	
	for (size_t i = 0; i < 6; i++) {
		deepcpy[i] = new Animal(*animals[i]);
	}

	std::cout << "------------ 03 ------------" << std::endl;

	for (size_t i = 0; i < 6; i++) {
		delete animals[i];
	}

	std::cout << "------------ 04 ------------" << std::endl;

	for (size_t i = 0; i < 6; i++) {
		delete deepcpy[i];
	}

	std::cout << "------------ 05 ------------" << std::endl;

	const Cat *taro = new Cat;
	const Cat *taho = new Cat(*taro);

	taro->debugAddresses();
	taho->debugAddresses();

	delete taho;
	delete taro;


	return (0);
}

// FIRST ADDRESSES OF STEP 1 and STEP 3 should be sames (softcpy);
// FIRST ADDRESSES OF STEP 1 and STEP 4 should be different (deepcpy);