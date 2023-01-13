/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:08:49 by conobi            #+#    #+#             */
/*   Updated: 2023/01/13 16:09:24 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "type.hpp"

#include "Base.hpp"

Base* generate(void) {
	srand(time(NULL));
	int randNum = (rand() % 3);
	Base* ret_ptr;

	switch (randNum) {
		case 0:
			ret_ptr = new A;
			break;
		case 1:
			ret_ptr = new B;
			break;
		default:
			ret_ptr = new C;
			break;
	}

	return (ret_ptr);
}

void identify(Base* p) {
	if (dynamic_cast<A*>(p) != nullptr)
		std::cout << "(*) type: A" << std::endl;
	else if (dynamic_cast<B*>(p) != nullptr)
		std::cout << "(*) type: B" << std::endl;
	else if (dynamic_cast<C*>(p) != nullptr)
		std::cout << "(*) type: C" << std::endl;
	else
		std::cout << "(*) type: Unknown" << std::endl;
}

void identify(Base& p) {
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "(&) type: A" << std::endl;
	} catch (std::bad_cast& e) {
		try {
			(void)dynamic_cast<B&>(p);
			std::cout << "(&) type: B" << std::endl;
		} catch (std::bad_cast& e) {
			try {
				(void)dynamic_cast<C&>(p);
				std::cout << "(&) type: C" << std::endl;
			} catch (std::bad_cast& e) {
				std::cout << "(&) type: Unknown" << std::endl;
			}
		}
	}
}