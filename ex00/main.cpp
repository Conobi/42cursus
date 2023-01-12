/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:14:08 by conobi            #+#    #+#             */
/*   Updated: 2023/01/12 20:26:29 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

/*
	WARNING : THIS CODE IS A BIG MENHIR!
	char = 1, int = 2, float = 3, double = 4
	Otherwise, we return 0.
*/

static unsigned short detectType(const std::string str) {
	std::stringstream ss(str);
	int integer_part, decimal_part = 0;
	char point, f = 0;
	std::string trail = "";

	(void)trail;

	if (str == "nanf" || str == "-inff" || str == "+inff")
		return (3);
	else if (str == "nan" || str == "-inf" || str == "+inf")
		return (4);
	else if (ss.str().length() == 1 && !(static_cast<int>(str[0]) >= '0' &&
										 static_cast<int>(str[0]) <= '9'))
		return (1);
	else if (ss.str().length() == 1)
		return (2);
	else {
		if ((ss >> integer_part >> std::noskipws >> point >> std::noskipws >>
			 decimal_part >> std::noskipws >> f) &&
			point == '.' && f == 'f') {
			ss >> trail;
			if (trail.length() > 0)
				return (0);
			return (3);
		}
		std::stringstream().swap(ss);
		ss << str;
		if ((ss >> integer_part >> std::noskipws >> point >> std::noskipws >>
			 decimal_part) &&
			point == '.' && ss.eof())
			return (4);
		std::stringstream().swap(ss);
		ss << str;
		if ((ss >> integer_part) && ss.eof())
			return (2);
	}
	return (0);
}

static void printAsChar(std::string str) {
	char val = str[0];

	std::cout << "char: ";
	if (static_cast<int>(val) < 0)
		std::cout << RED_FG << "impossible" << RESET << std::endl;
	else if (static_cast<int>(val) >= 0 && static_cast<int>(val) <= 31)
		std::cout << YEL_FG << "Non displayable" << RESET << std::endl;
	else
		std::cout << "'" << static_cast<char>(val) << "'" << std::endl;

	std::cout << "int: " << static_cast<int>(val) << std::endl
			  << "float: " << std::fixed << std::setprecision(1)
			  << static_cast<float>(val) << "f" << std::endl
			  << "double: " << static_cast<double>(val) << std::endl;
}

static void printAsInt(std::string str) {
	std::stringstream ss(str);
	int val;

	ss >> val;

	std::cout << "char: ";
	if (static_cast<int>(val) < 0)
		std::cout << RED_FG << "impossible" << RESET << std::endl;
	else if (static_cast<int>(val) >= 0 && static_cast<int>(val) <= 31)
		std::cout << YEL_FG << "Non displayable" << RESET << std::endl;
	else
		std::cout << "'" << static_cast<char>(val) << "'" << std::endl;

	std::cout << "int: " << static_cast<int>(val) << std::endl
			  << "float: " << std::fixed << std::setprecision(1)
			  << static_cast<float>(val) << "f" << std::endl
			  << "double: " << static_cast<double>(val) << std::endl;
}

static void printAsFloat(std::string str) {
	std::stringstream ss(str.substr(1, str.length() - 1));
	float val;

	ss >> val;
	std::cout << "char: ";
	if (static_cast<int>(val) < 0)
		std::cout << RED_FG << "impossible" << RESET << std::endl;
	else if (static_cast<int>(val) >= 0 && static_cast<int>(val) <= 31)
		std::cout << YEL_FG << "Non displayable" << RESET << std::endl;
	else
		std::cout << "'" << static_cast<char>(val) << "'" << std::endl;

	std::cout << "int: " << static_cast<int>(val) << std::endl
			  << "float: " << std::fixed << std::setprecision(1)
			  << static_cast<float>(val) << "f" << std::endl
			  << "double: " << static_cast<double>(val) << std::endl;
}

static void unprintable() {
	std::cout << "char: " << RED_FG << "impossible" << RESET << std::endl;
	std::cout << "int: " << RED_FG << "impossible" << RESET << std::endl;
	std::cout << "float: " << RED_FG << "impossible" << RESET << std::endl;
	std::cout << "double: " << RED_FG << "impossible" << RESET << std::endl;
}

int main(int argc, char **argv) {
	unsigned short type;

	if (argc == 2) {
		try {
			type = detectType(argv[1]);

			switch (type) {
				case 1:
					printAsChar(argv[1]);
					break;
				case 2:
					printAsInt(argv[1]);
					break;
				case 3:
					printAsFloat(argv[1]);
					break;
				// case 4:
				//     printAsDouble(argv[1]);
				//     break;
				default:
					unprintable();
					break;
			}
		} catch (std::exception &e) {
			std::cerr << RED_FG << BOLD << "ERROR: " << RESET << e.what()
					  << std::endl;
		}
	} else {
		std::cerr << RED_FG << BOLD << "ERROR: " << RESET
				  << "The value to convert is needed as an argument."
				  << std::endl;
		return (1);
	}
	return (0);
}