/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:46:44 by conobi            #+#    #+#             */
/*   Updated: 2023/01/06 02:05:51 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main(void) {
	const Animal *cato;
	const Animal *dogo;
	const Animal *meta;

	const WrongAnimal *tema;
	const WrongAnimal *toca;

	meta = new Animal();
	cato = new Cat();
	dogo = new Dog();
	tema = new WrongAnimal();
	toca = new WrongCat();

	std::cout << meta->getType() << ": ";
	meta->makeSound();
	std::cout << std::endl;

	std::cout << cato->getType() << ": ";
	cato->makeSound();
	std::cout << std::endl;

	std::cout << dogo->getType() << ": ";
	dogo->makeSound();
	std::cout << std::endl;

	std::cout << tema->getType() << ": ";
	tema->makeSound();
	std::cout << std::endl;

	std::cout << toca->getType() << ": ";
	toca->makeSound();
	std::cout << std::endl;

	delete cato;
	delete dogo;
	delete meta;
	delete toca;
	delete tema;
	return (0);
}

// SUBJECT EXAMPLE MAIN
// int main()
// {
// 	const Animal* meta = new Animal();
// 	const Animal* j = new Dog();
// 	const Animal* i = new Cat();
// 	std::cout << j->getType() << " " << std::endl;
// 	std::cout << i->getType() << " " << std::endl;
// 	i->makeSound(); //will output the cat sound!
// 	j->makeSound();
// 	meta->makeSound();

// 	return 0;
// }
