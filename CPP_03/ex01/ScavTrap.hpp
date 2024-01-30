/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:40:59 by conobi            #+#    #+#             */
/*   Updated: 2023/01/09 17:27:31 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {
	private:
		/* data */
	public:
		ScavTrap();
		ScavTrap(const ScavTrap &val);
		~ScavTrap();
		ScavTrap &operator=(const ScavTrap &rhs);

		ScavTrap(const std::string name);

		void attack(const std::string &target);
		void guardGate();
};
