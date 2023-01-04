/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:00:05 by conobi            #+#    #+#             */
/*   Updated: 2023/01/04 19:17:06 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Bureaucrat.hpp"

class Form {
    private:
        const std::string _name;
        const unsigned short _grade_to_sign;
        const unsigned short _grade_to_exec;
        bool _is_signed;

        void _gradeCheck(const unsigned short new_grade);

    public:
        Form();
        Form(const Form &val);
        ~Form();
        Form &operator=(const Form &rhs);

        Form(const std::string name, const unsigned short grade_to_sign,
             const unsigned short grade_to_exec);

        std::string getName() const;
        unsigned short getGradeToSign() const;
        unsigned short getGradeToExec() const;
        bool isSigned() const;

        void beSigned(Bureaucrat &person);

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
