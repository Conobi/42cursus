/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:03:10 by conobi            #+#    #+#             */
/*   Updated: 2023/01/17 17:58:39 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>

#include "Span.hpp"

static void testsAlot(std::size_t val) {
	Span sp = Span(val);

	srand(time(0));
	for (size_t i = 0; i < val; i++) sp.addNumber(rand());

	std::cout << "shortest: " << sp.shortestSpan() << std::endl;
	std::cout << "longest:  " << sp.longestSpan() << std::endl;
}

static void testsLimitCases() {
	std::cout << "--- Test with bound values ---" << std::endl;
	{
		Span sp = Span(2);

		sp.addNumber(2147483647);
		sp.addNumber(-2147483648);
		std::cout << "shortest: " << sp.shortestSpan() << std::endl;
		std::cout << "longest:  " << sp.longestSpan() << std::endl;
	}
	{
		Span sp = Span(2);

		sp.addNumber(-2147483648);
		sp.addNumber(2147483647);
		std::cout << "shortest: " << sp.shortestSpan() << std::endl;
		std::cout << "longest:  " << sp.longestSpan() << std::endl;
	}
	std::cout << "--- Test on exceptions ---" << std::endl;
	{
		try {
			Span(10).longestSpan();
		} catch (std::exception &e) {
			std::cerr << RED_FG << BOLD << "ERROR: " << RESET << e.what()
					  << std::endl;
		}
		try {
			Span(0).addNumber(4242);
		} catch (std::exception &e) {
			std::cerr << RED_FG << BOLD << "ERROR: " << RESET << e.what()
					  << std::endl;
		}
	}
}

static void testsSubject() {
	Span sp = Span(5);

	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
}

int main() {
	std::cout << "--- Test from the subject ---" << std::endl;
	testsSubject();
	std::cout << "--- Test with 10 000 values ---" << std::endl;
	testsAlot(10000);
	testsLimitCases();
	return 0;
}