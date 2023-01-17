/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:39:24 by conobi            #+#    #+#             */
/*   Updated: 2023/01/17 17:39:06 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Span {
	private:
		Span();
		std::vector<int> _arr;
		std::size_t _max_size;

	public:
		~Span();
		Span(const Span &val);
		Span &operator=(const Span &rhs);
		Span(const std::size_t size);

		void addNumber(const int val);
		long long shortestSpan();
		long long longestSpan();

		class UponSizeException : public std::exception {
			public:
				virtual const char *what() const throw() {
					return (
						"You cannot add more elements, the maximum number of "
						"elements that can be stored has been reached.");
				}
		};

		class NotEnoughNumbersException : public std::exception {
			public:
				virtual const char *what() const throw() {
					return (
						"You need more elements to be stored to use this "
						"function.");
				}
		};
};

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