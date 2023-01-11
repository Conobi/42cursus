/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:06:19 by conobi            #+#    #+#             */
/*   Updated: 2023/01/11 15:51:21 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "AForm.hpp"

class AForm;

class Bureaucrat {
	private:
		Bureaucrat();
		std::string _name;
		unsigned short _grade;

		void _gradeCheck(const unsigned short new_grade);

	public:
		Bureaucrat(const Bureaucrat &val);
		~Bureaucrat();
		Bureaucrat &operator=(const Bureaucrat &rhs);

		Bureaucrat(const std::string name, const unsigned short grade);

		std::string getName() const;
		unsigned short getGrade() const;

		void increaseGrade();
		void decreaseGrade();

		void signForm(AForm &AForm);
		void executeForm(AForm &AForm);

		class GradeTooHighException : public std::exception {
			public:
				virtual const char *what() const throw() {
					return (
						"Bureaucrat grade must be a number higher or equal to "
						"1.");
				}
		};

		class GradeTooLowException : public std::exception {
			public:
				virtual const char *what() const throw() {
					return (
						"Bureaucrat grade must be a number less or equal to "
						"150.");
				}
		};
};

std::ostream &operator<<(std::ostream &os, const Bureaucrat &val);

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
