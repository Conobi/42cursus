/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:09:17 by conobi            #+#    #+#             */
/*   Updated: 2023/01/14 17:54:11 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

class Awesome {
	public:
		Awesome(void) : _n(42) {
			return;
		}

		int get(void) const {
			return this->_n;
		}

	private:
		int _n;
};

std::ostream& operator<<(std::ostream& o, Awesome const& rhs) {
	o << rhs.get();
	return o;
}

int main() {
	int tab[] = {0, 1, 2, 3, 4};
	Awesome tab2[5];

	iter(tab, 5, print);
	std::cout << "------" << std::endl;
	iter(tab, 5, add_ft);
	iter(tab, 5, print);
	std::cout << "------" << std::endl;
	iter(tab2, 5, print);
	return 0;
}