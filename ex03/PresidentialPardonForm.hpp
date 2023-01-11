/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:27:30 by conobi            #+#    #+#             */
/*   Updated: 2023/01/11 16:19:16 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AForm.hpp"

class PresidentialPardonForm : public AForm {
	private:
		PresidentialPardonForm();
		const std::string _target;

		virtual void _executor() const;

	public:
		PresidentialPardonForm(const PresidentialPardonForm &val);
		virtual ~PresidentialPardonForm();
		PresidentialPardonForm &operator=(const PresidentialPardonForm &rhs);

		PresidentialPardonForm(const std::string target);

		std::string getTarget() const;
};
