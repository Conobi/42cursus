/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:41:47 by conobi            #+#    #+#             */
/*   Updated: 2023/01/11 16:20:53 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AForm.hpp"

class RobotomyRequestForm : public AForm {
	private:
		RobotomyRequestForm();
		const std::string _target;

		virtual void _executor() const;

	public:
		RobotomyRequestForm(const RobotomyRequestForm &val);
		virtual ~RobotomyRequestForm();
		RobotomyRequestForm &operator=(const RobotomyRequestForm &rhs);

		RobotomyRequestForm(const std::string target);

		std::string getTarget() const;
};
