/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:31:53 by conobi            #+#    #+#             */
/*   Updated: 2022/11/28 20:02:56 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main (void) {
	Zombie *foo;

	std::cout << "newZombie(), named Foo:" << std::endl;
	foo = newZombie("Foo");
	foo->announce();
	std::cout << "randomChump(), named Bar:" << std::endl;
	randomChump("Bar");
	delete (foo);
	return (0);
}
