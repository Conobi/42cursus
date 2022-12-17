/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:52:50 by conobi            #+#    #+#             */
/*   Updated: 2022/12/17 02:41:34 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <cmath>

class Fixed {
	private:
		int _value;
		static const int _fractional = 8;

	public:
		Fixed(void);
		Fixed(const Fixed &val);
		Fixed(const float val);
		Fixed(const int val);
		~Fixed();

		Fixed &operator=(const Fixed &rhs);
		Fixed &operator++();
		Fixed operator++(int);
		Fixed &operator--();
		Fixed operator--(int);

		Fixed operator+(const Fixed &rhs) const;
		Fixed operator-(const Fixed &rhs) const;
		Fixed operator*(const Fixed &rhs) const;
		Fixed operator/(const Fixed &rhs) const;

		bool operator>(const Fixed &rhs) const;
		bool operator<(const Fixed &rhs) const;
		bool operator>=(const Fixed &rhs) const;
		bool operator<=(const Fixed &rhs) const;
		bool operator==(const Fixed &rhs) const;
		bool operator!=(const Fixed &rhs) const;


		int getRawBits(void) const;
		void setRawBits(int const raw);
		int toInt(void) const;
		float toFloat(void) const;

		static Fixed &min(Fixed &a, Fixed &b);
		static const Fixed &min(Fixed const &a, Fixed const &b);
		static Fixed &max(Fixed &a, Fixed &b);
		static const Fixed &max(Fixed const &a, Fixed const &b);
};

std::ostream &operator<<(std::ostream &os, const Fixed &val);

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
