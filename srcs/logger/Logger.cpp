/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 02:07:13 by conobi            #+#    #+#             */
/*   Updated: 2023/02/23 03:30:03 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"

#include <ostream>

Logger::Logger(const string &class_name) : _class_name(class_name) {
	stringstream ss;

	ss << KBLU << class_name << " constructor called." << RST;
	this->log(ss.str(), true);
}

Logger::~Logger() {
	stringstream ss;

	ss << KYEL << this->_class_name << " destructor called." << RST;
	this->log(ss.str(), true);
}

void Logger::_format(ostream &os, const string &msg, const char *dt,
					 const ushort &level) {
	string level_str;
	stringstream color_class;

	color_class << left << setw(14);
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
					const ushort &level) {
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

void Logger::log(const string &msg, const bool &verbose_only) {
	this->_print(cout, msg, verbose_only, 0);
}

void Logger::info(const string &msg, const bool &verbose_only) {
	this->_print(cout, msg, verbose_only, 1);
}

void Logger::warn(const string &msg, const bool &verbose_only) {
	this->_print(cout, msg, verbose_only, 2);
}

void Logger::err(const string &msg) {
	this->_print(cerr, msg, false, 3);
}
