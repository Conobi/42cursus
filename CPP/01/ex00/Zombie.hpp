/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:30:42 by conobi            #+#    #+#             */
/*   Updated: 2022/11/28 19:53:00 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>
# include <iostream>

# define BLU_FG "\001\033[34m\002"
# define RESET "\001\033[0m\002"
# define ITALIC "\001\033[3m\002"

class Zombie {
	private:
		std::string _name;

	public:
		Zombie(std::string name);
		~Zombie();
		void announce(void);
};

Zombie *newZombie(std::string name);
void randomChump(std::string name);

#endif
