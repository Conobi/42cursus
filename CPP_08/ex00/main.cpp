/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:50:37 by conobi            #+#    #+#             */
/*   Updated: 2023/01/17 15:26:33 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include "easyfind.hpp"

static void testsIntVector() {
	std::vector<int> test;

	test.push_back(10);
	test.push_back(5);
	test.push_back(42);
	test.push_back(32);
	test.push_back(0);
	test.push_back(-2424);
	test.push_back(64);
	// test.push_back(666);

	try {
		std::cout << *easyfind(test, 10) << std::endl;
		std::cout << *easyfind(test, 5) << std::endl;
		std::cout << *easyfind(test, 42) << std::endl;
		std::cout << *easyfind(test, 32) << std::endl;
		std::cout << *easyfind(test, 64) << std::endl;
		std::cout << *easyfind(test, 0) << std::endl;
		std::cout << *easyfind(test, -2424) << std::endl;
		std::cout << *easyfind(test, 64) << std::endl;
		std::cout << *easyfind(test, 666) << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}

static void testsDoubleVector() {
	std::vector<double> test;

	test.push_back(10);
	test.push_back(5);
	test.push_back(42);
	test.push_back(32);
	test.push_back(0);
	test.push_back(-2424);
	test.push_back(64);
	test.push_back(42.123456);
	// test.push_back(666);

	try {
		std::cout << *easyfind(test, 10) << std::endl;
		std::cout << *easyfind(test, 5) << std::endl;
		std::cout << *easyfind(test, 42) << std::endl;
		std::cout << *easyfind(test, 32) << std::endl;
		std::cout << *easyfind(test, 64) << std::endl;
		std::cout << *easyfind(test, 0) << std::endl;
		std::cout << *easyfind(test, -2424) << std::endl;
		std::cout << *easyfind(test, 64) << std::endl;
		std::cout << *easyfind(test, 666) << std::endl;
		// std::cout << *easyfind(test, 42.123456) << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}

int main(void) {
	// std::vector test[7] = {10, 5, 42, 32, 64, 0, -2424};
	testsIntVector();
	std::cout << "------" << std::endl;
	testsDoubleVector();
	return (0);
}