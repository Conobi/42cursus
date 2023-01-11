/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:00:05 by conobi            #+#    #+#             */
/*   Updated: 2023/01/11 15:35:45 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "Bureaucrat.hpp"

class Bureaucrat;

class Form {
	private:
		Form();
		const std::string _name;
		const unsigned short _grade_to_sign;
		const unsigned short _grade_to_exec;
		bool _is_signed;

		void _gradeCheck(const unsigned short new_grade);

	public:
		Form(const Form &val);
		~Form();
		Form &operator=(const Form &rhs);

		Form(const std::string name, const unsigned short grade_to_sign,
			 const unsigned short grade_to_exec);

		std::string getName() const;
		unsigned short getGradeToSign() const;
		unsigned short getGradeToExec() const;
		bool isSigned() const;

		void beSigned(Bureaucrat &Bureaucrat);

		class GradeTooHighException : public std::exception {
			public:
				virtual const char *what() const throw() {
					return ("Form specified grade is out of bound (< 1)");
				}
		};

		class GradeTooLowException : public std::exception {
			public:
				virtual const char *what() const throw() {
					return (
						"Form specified grade is out of bound (> 150) or "
						"Bureaucrat's grade isn't high enough.");
				}
		};
};

std::ostream &operator<<(std::ostream &os, const Form &val);

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
