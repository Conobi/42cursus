/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:25:24 by conobi            #+#    #+#             */
/*   Updated: 2023/06/07 01:23:22 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <ctime>

#include "PmergeMe.hpp"

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Usage: ./pmergeMe \"1 3 4 2 5\"" << std::endl;
		return (1);
	}

	try {
		std::string numbers;
		for (int i = 1; i < argc; i++) {
			if (i != 1)
				numbers += " ";
			numbers += argv[i];
		}

		PmergeMe mergeInsertSort(argc, argv);

		std::cout << "Before: ";
		mergeInsertSort.printVector();
		clock_t beginVector = clock();
		mergeInsertSort.sortVector();
		clock_t endVector = clock();
		double elapsedSecsVector = static_cast<double>(endVector - beginVector);
		std::cout << "After: ";
		mergeInsertSort.printVector();
		std::cout << "Time to process a range of "
				  << mergeInsertSort.getVector().size()
				  << " elements with std::vector: " << elapsedSecsVector
				  << " us" << std::endl;

		clock_t beginList = clock();
		mergeInsertSort.sortDeque();
		clock_t endList = clock();
		mergeInsertSort.printDeque();
		double elapsedSecsList = static_cast<double>(endList - beginList);
		std::cout << "Time to process a range of "
				  << mergeInsertSort.getDeque().size()
				  << " elements with std::deque: " << elapsedSecsList << " us"
				  << std::endl;

	} catch (std::exception& e) {
		std::cout << RED_FG << e.what() << RESET << std::endl;
		return (1);
	}

	return (0);
}
