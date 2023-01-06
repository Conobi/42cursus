/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:46:44 by conobi            #+#    #+#             */
/*   Updated: 2023/01/06 02:11:03 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

#include "AAnimal.hpp"
#include "Brain.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main(void) {
	const AAnimal *AAnimals[6];
	const AAnimal *softcpy[6];

	std::cout << "------------ 00 ------------" << std::endl;

	for (size_t i = 0; i < 6; i++) {
		if (i >= 3) {
			AAnimals[i] = new Cat;
		} else {
			AAnimals[i] = new Dog;
		}
	}

	std::cout << "------------ 01 ------------" << std::endl;

	for (size_t i = 0; i < 6; i++) {
		softcpy[i] = AAnimals[i];
		softcpy[i]->debugAddresses();
	}

	std::cout << "------------ 02 ------------" << std::endl;

	for (size_t i = 0; i < 6; i++) {
		delete AAnimals[i];
	}

	std::cout << "------------ 03 ------------" << std::endl;

	const Cat *taro = new Cat;
	const Cat *taho = new Cat(*taro);

	taro->debugAddresses();
	taho->debugAddresses();

	delete taro;
	delete taho;

	return (0);
}
