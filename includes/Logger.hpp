/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 02:07:26 by conobi            #+#    #+#             */
/*   Updated: 2023/02/23 17:01:25 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Term syntax
#define RST "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"
#define KGRE "\x1B[90m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST
#define FGRE(x) KGRE x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST

class Logger {
	private:
		Logger();

		string _class_name;

		void _format(ostream &os, const string &msg, const char *dt,
					 const ushort &level) const;
		void _print(ostream &os, const string &msg, const bool &verbose_only,
					const ushort &level) const;

	public:
		Logger(const string &class_name);
		~Logger();
		Logger(const Logger &val);
		Logger &operator=(const Logger &rhs);

		void log(const string &msg, const bool &verbose_only) const;
		void info(const string &msg, const bool &verbose_only) const;
		void warn(const string &msg, const bool &verbose_only) const;
		void err(const string &msg) const;
};
