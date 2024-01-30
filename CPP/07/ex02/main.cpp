/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:59:42 by conobi            #+#    #+#             */
/*   Updated: 2023/01/16 16:03:53 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

#define MAX_VAL 12

int main(void) {
	{
		Array<int> numbers(MAX_VAL);
		int* mirror = new int[MAX_VAL];
		srand(time(NULL));
		for (int i = 0; i < MAX_VAL; i++) {
			const int value = rand();
			numbers[i] = value;
			mirror[i] = value;
		}
		{
			Array<int> tmp = numbers;
			Array<int> test(tmp);
		}

		for (int i = 0; i < MAX_VAL; i++) {
			if (mirror[i] != numbers[i]) {
				std::cerr << "didn't save the same value!!" << std::endl;
				return 1;
			}
		}
		try {
			numbers[-2] = 0;
		} catch (const std::exception& e) {
			std::cerr << e.what() << '\n';
		}
		try {
			numbers[MAX_VAL] = 0;
		} catch (const std::exception& e) {
			std::cerr << e.what() << '\n';
		}

		for (int i = 0; i < MAX_VAL; i++) {
			numbers[i] = rand();
		}
		delete[] mirror;
	}
	{
		std::cout << std::endl
				  << "------ EMPTY ------" << std::endl
				  << std::endl;

		Array<int> emptyArray;

		std::cout << std::endl << "------ INT ------" << std::endl << std::endl;

		Array<int> intArray(3);
		intArray[0] = 1;
		intArray[1] = 2;
		intArray[2] = 3;
		std::cout << "intArray[0]: " << intArray[0] << std::endl;
		std::cout << "intArray[1]: " << intArray[1] << std::endl;
		std::cout << "intArray[2]: " << intArray[2] << std::endl;

		std::cout << std::endl
				  << "------ FLOAT ------" << std::endl
				  << std::endl;

		Array<float> floatArray(4);
		floatArray[0] = 1.1;
		floatArray[1] = 2.2;
		floatArray[2] = 3.3;
		floatArray[3] = 42.4242;
		std::cout << "floatArray[0]: " << floatArray[0] << std::endl;
		std::cout << "floatArray[1]: " << floatArray[1] << std::endl;
		std::cout << "floatArray[2]: " << floatArray[2] << std::endl;
		std::cout << "floatArray[2]: " << floatArray[3] << std::endl;

		std::cout << std::endl
				  << "------ COPY ------" << std::endl
				  << std::endl;

		Array<int> copyArray(intArray);
		std::cout << "intArray[1] : " << intArray[1] << std::endl;
		std::cout << "copyArray[1]: " << copyArray[1] << std::endl << std::endl;

		intArray[1] = 4;
		std::cout << "intArray[1] : " << intArray[1] << std::endl;
		std::cout << "copyArray[1]: " << copyArray[1] << std::endl;

		std::cout << std::endl
				  << "------ EXCEPTION ------" << std::endl
				  << std::endl;

		Array<double> doubleArray(3);
		std::cout << "doubleArray size: " << doubleArray.size() << std::endl;

		try {
			std::cout << "doubleArray[5]: " << doubleArray[5] << std::endl
					  << std::endl
					  << std::endl;
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl << std::endl;
		}
	}
	return (0);
}