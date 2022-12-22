/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 01:03:21 by conobi            #+#    #+#             */
/*   Updated: 2022/12/22 02:18:15 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "polymorphism.hpp"

class WrongAnimal {
	protected:
		std::string _type;

	public:
		WrongAnimal();
		WrongAnimal(const WrongAnimal &val);
		~WrongAnimal();
		WrongAnimal &operator=(const WrongAnimal &rhs);

		std::string getType() const;

		void makeSound() const;
};
