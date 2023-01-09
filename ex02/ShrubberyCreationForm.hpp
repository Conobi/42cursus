/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:46:39 by conobi            #+#    #+#             */
/*   Updated: 2023/01/09 14:26:44 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <fstream>

#include "AForm.hpp"

class ShrubberyCreationForm : public AForm {
	private:
		const std::string _target;

		virtual void _executor() const;

	public:
		ShrubberyCreationForm();
		ShrubberyCreationForm(const ShrubberyCreationForm &val);
		virtual ~ShrubberyCreationForm();
		ShrubberyCreationForm &operator=(const ShrubberyCreationForm &rhs);

		ShrubberyCreationForm(const std::string name, const std::string target);

		std::string getTarget() const;
};
