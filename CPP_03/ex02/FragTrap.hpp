/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:40:59 by conobi            #+#    #+#             */
/*   Updated: 2023/01/09 17:34:47 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap {
	private:
		/* data */
	public:
		FragTrap();
		FragTrap(const FragTrap &val);
		~FragTrap();
		FragTrap &operator=(const FragTrap &rhs);

		FragTrap(const std::string name);

		void attack(const std::string &target);
		void highFivesGuys();
};
