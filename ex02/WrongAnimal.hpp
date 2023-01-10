/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 01:03:21 by conobi            #+#    #+#             */
/*   Updated: 2023/01/06 02:13:06 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "main.hpp"

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
