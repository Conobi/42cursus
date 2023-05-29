/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:34:28 by conobi            #+#    #+#             */
/*   Updated: 2023/05/30 01:04:14 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

#include <sstream>
#include <stdexcept>
#include <string>

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

time_t BitcoinExchange::_getTimestamp(int day, int month, int year) {
	struct tm time_info;
	std::string err;

	time_info.tm_year = year - 1900;
	time_info.tm_mon = month - 1;
	time_info.tm_mday = day;
	time_info.tm_hour = 0;
	time_info.tm_min = 0;
	time_info.tm_sec = 0;
	time_info.tm_isdst = -1;

	time_t timestamp = mktime(&time_info);

	if (timestamp == -1) {
		err = "Cannot convert the `" + Utils::valToString(year) + "-" +
			  Utils::valToString(month) + "-" + Utils::valToString(day) +
			  "`. Is it a valid date?";
		throw std::runtime_error(err);
	}

	return timestamp;
}

void BitcoinExchange::_parse_csv(const std::string &input_csv) {
	std::string line;
	std::istringstream ss_csv(input_csv);
	int nb_line;
	int year;
	int month;
	int day;
	float val;

	nb_line = 0;
	for (; std::getline(ss_csv, line); ++nb_line) {
		if (std::sscanf(line.c_str(), "%d-%d-%d,%f", &year, &month, &day,
						&val) != 4)
			throw std::runtime_error("Wasn't able to parse line " +
									 Utils::valToString(nb_line) + ":\n" +
									 line + "in the CSV.\n");
		this->_csv_data[this->_getTimestamp(day, month, year)] = val;
	}
}

void BitcoinExchange::_parse_db(const std::string &input_db) {
	std::string line;
	std::istringstream ss_db(input_db);
	int nb_line;
	int year;
	int month;
	int day;
	float val;

	nb_line = 0;
	for (; std::getline(ss_db, line); ++nb_line) {
		if (std::sscanf(line.c_str(), "%d-%d-%d | %f", &year, &month, &day,
						&val) != 4)
			throw std::runtime_error("Wasn't able to parse line " +
									 Utils::valToString(nb_line) + ":\n" +
									 line + "in the input DB.\n");
		this->_db_data[this->_getTimestamp(day, month, year)] = val;
	}
}

BitcoinExchange::BitcoinExchange(const std::string &input_file) {
	std::string input_csv;
	std::string input_db;

	input_csv = this->_read_file("data.csv");
	this->_parse_csv(input_csv);
	input_db = this->_read_file(input_file);
	this->_parse_db(input_db);
}
