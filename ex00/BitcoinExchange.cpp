/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:34:28 by conobi            #+#    #+#             */
/*   Updated: 2023/06/01 15:35:27 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::string BitcoinExchange::_read_file(const std::string &filename) {
	std::ifstream in_file(filename.c_str());
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
	if (this != &rhs) {
		this->_csv_data = rhs._csv_data;
	}
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
	char remain[80];

	nb_line = 1;
	std::memset(remain, 0, 80);

	for (; std::getline(ss_csv, line); ++nb_line) {
		if (nb_line == 1)
			continue;
		if (std::sscanf(line.c_str(), "%d-%d-%d,%f%79s", &year, &month, &day,
						&val, remain) != 4)
			throw std::runtime_error("Invalid entry line " +
									 Utils::valToString(nb_line) + ": " + line +
									 " in the CSV.\n");
		this->_csv_data[this->_getTimestamp(day, month, year)] = val;
	}
}

void BitcoinExchange::_read_db(const std::string &input_db) {
	std::string line;
	std::istringstream ss_db(input_db);
	int nb_line;
	int year;
	int month;
	int day;
	float val;
	char remain[80];
	time_t time;
	std::map<time_t, float>::iterator needle;

	std::memset(remain, 0, 80);
	nb_line = 1;

	for (; std::getline(ss_db, line); ++nb_line) {
		try {
			if (line.empty() || nb_line == 1)
				continue;
			if (std::sscanf(line.c_str(), "%d-%d-%d | %f%79s", &year, &month,
							&day, &val, remain) != 4)
				throw std::runtime_error("Invalid entry line " +
										 Utils::valToString(nb_line) + ": " +
										 line);
			if (val < 0)
				throw std::runtime_error(Utils::valToString(val) +
										 " is not a positive number (line " +
										 Utils::valToString(nb_line) + ").");
			if (val > 1000)
				throw std::runtime_error(Utils::valToString(val) +
										 " is greater than 1000 (line " +
										 Utils::valToString(nb_line) + ").");
			time = this->_getTimestamp(day, month, year);
			needle = this->_csv_data.lower_bound(time);
			if (time < this->_csv_data.begin()->first)
				throw std::runtime_error("No data found for " +
										 Utils::valToString(day) + "/" +
										 Utils::valToString(month) + "/" +
										 Utils::valToString(year) + ".");
			std::cout << "On " << std::setw(2) << std::setfill('0') << day
					  << "/" << std::setw(2) << std::setfill('0') << month
					  << "/" << year << " => " << std::setw(6)
					  << std::setfill(' ') << val << " = "
					  << needle->second * val << std::endl;

		} catch (const std::exception &e) {
			std::cerr << YEL_FG << e.what() << RESET << std::endl;
		}
	}
}

BitcoinExchange::BitcoinExchange(const std::string &input_file) {
	std::string input_csv;
	std::string input_db;

	input_csv = this->_read_file("data.csv");
	this->_parse_csv(input_csv);
	input_db = this->_read_file(input_file);
	this->_read_db(input_db);
}
