/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:27:30 by conobi            #+#    #+#             */
/*   Updated: 2023/01/07 16:03:55 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AForm.hpp"

class PresidentialPardonForm : public AForm {
	private:
		const std::string _target;

		virtual void _executor() const;

	public:
		PresidentialPardonForm();
		PresidentialPardonForm(const PresidentialPardonForm &val);
		virtual ~PresidentialPardonForm();
		PresidentialPardonForm &operator=(const PresidentialPardonForm &rhs);

		PresidentialPardonForm(const std::string name,
							   const std::string target);

		std::string getTarget() const;
};
