/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:34:25 by conobi            #+#    #+#             */
/*   Updated: 2023/05/29 02:38:12 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#define RED_FG "\001\033[91m\002"
#define GRN_FG "\001\033[32m\002"
#define YEL_FG "\001\033[33m\002"
#define BLU_FG "\001\033[34m\002"
#define MAG_FG "\001\033[35m\002"
#define CYN_FG "\001\033[36m\002"
#define WHT_FG "\001\033[37m\002"
#define BLK_FG "\001\033[30m\002"
#define ACC_FG "\001\033[38;2;65;208;117m\002"

#define RED_BG "\001\033[101m\002"
#define GRN_BG "\001\033[42m\002"
#define YEL_BG "\001\033[43m\002"
#define BLU_BG "\001\033[44m\002"
#define MAG_BG "\001\033[45m\002"
#define CYN_BG "\001\033[46m\002"
#define WHT_BG "\001\033[47m\002"
#define BLK_BG "\001\033[40m\002"
#define ACC_BG "\001\033[48;2;65;208;117m\002"

#define RESET "\001\033[0m\002"
#define BOLD "\001\033[1m\002"
#define ITALIC "\001\033[3m\002"
#define UNDERLINE "\001\033[4m\002"

class BitcoinExchange {
	private:
		std::string _read_file(const std::string &filename);
		BitcoinExchange();
		std::string _input_csv;
		std::string _input_db;

	public:
		BitcoinExchange(const std::string &input_file);
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &val);

		BitcoinExchange &operator=(const BitcoinExchange &rhs);
};
