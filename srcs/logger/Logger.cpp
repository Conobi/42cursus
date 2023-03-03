/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 02:07:13 by conobi            #+#    #+#             */
/*   Updated: 2023/03/03 15:35:48 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"

Logger::~Logger() {
	this->log(KYEL + this->_class_name + " has been destroyed." + RST, true);
}

Logger::Logger(const Logger &val) {
	*this = val;
	this->log(KBLU + this->_class_name + " copy constructor called." + RST,
			  true);
}

Logger &Logger::operator=(const Logger &rhs) {
	this->_class_name = rhs._class_name;
	this->log(KGRE + this->_class_name + " assignation operator called." + RST,
			  true);
	return *this;
}

Logger::Logger(const string &class_name) : _class_name(class_name) {
	this->log(KBLU + class_name + " constructor called." + RST, true);
}

void Logger::_format(ostream &os, const string &msg, const char *dt,
					 const ushort &level) const {
	string level_str;
	stringstream color_class;

	color_class << left << setw(20);
	switch (level) {
		case 1:
			level_str = FBLU("INFO: ");
			color_class << KBLU + this->_class_name;
			break;
		case 2:
			level_str = FYEL("WARNING: ");
			color_class << KYEL + this->_class_name;
			break;
		case 3:
			level_str = FRED("ERROR: ");
			color_class << KRED + this->_class_name;
			break;
		default:
			level_str = "";
			color_class << KGRN + this->_class_name;
			break;
	}
	color_class << RST;

	os << color_class.str() << KGRE << " [" << dt << "] " << RST << level_str
	   << msg << endl;
}

void Logger::_print(ostream &os, const string &msg, const bool &verbose_only,
					const ushort &level) const {
	bool verbose_mode = false;
	const char *env_value = getenv("VERBOSE");

	if (env_value) {
		string temp = env_value;
		if (temp == "true" || temp == "1")
			verbose_mode = true;
	}

	if (!verbose_only || (verbose_only && verbose_mode)) {
		time_t now = time(0);
		char *dt = ctime(&now);
		if (dt) {
			dt[strlen(dt) - 1] = '\0';
			this->_format(os, msg, dt, level);
		}
	}
}

void Logger::log(const string &msg, const bool &verbose_only) const {
	this->_print(cout, msg, verbose_only, 0);
}

void Logger::info(const string &msg, const bool &verbose_only) const {
	this->_print(cout, msg, verbose_only, 1);
}

void Logger::warn(const string &msg, const bool &verbose_only) const {
	this->_print(cout, msg, verbose_only, 2);
}

void Logger::err(const string &msg) const {
	this->_print(cerr, msg, false, 3);
}
