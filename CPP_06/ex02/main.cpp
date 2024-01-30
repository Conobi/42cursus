/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:40:33 by conobi            #+#    #+#             */
/*   Updated: 2023/01/13 16:16:05 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "type.hpp"

class uh : public Base {};

int main(void) {
	Base* toast0 = generate();
	Base& toast1 = *toast0;

	uh* unknown_derivated0 = new uh;
	uh& unknown_derivated1 = *unknown_derivated0;

	std::cout << "--- test 0 (expected: A, B or C) ---" << std::endl;

	identify(toast0);
	identify(toast1);

	std::cout << std::endl << "--- test 1 (expected: unknown) ---" << std::endl;

	identify(unknown_derivated0);
	identify(unknown_derivated1);

	delete toast0;
	delete unknown_derivated0;

	return (0);
}