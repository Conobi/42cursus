/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:34:28 by conobi            #+#    #+#             */
/*   Updated: 2023/05/29 02:40:01 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::string BitcoinExchange::_read_file(const std::string &filename) {
	std::ifstream in_file(filename);
	std::stringstream file_content;

	if (in_file.is_open()) {
		file_content << in_file.rdbuf();
		in_file.close();
		return (file_content.str());
	}
	throw std::runtime_error("An error occured while reading `" + filename +
							 "`. " + "Does it exists and is it readable?");
}

BitcoinExchange::~BitcoinExchange() {
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &val) {
	*this = val;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs) {
	return (*this);
}

BitcoinExchange::BitcoinExchange(const std::string &input_file) {
	this->_input_csv = _read_file("data.csv");
	this->_input_db = _read_file(input_file);
}
