/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:49:34 by conobi            #+#    #+#             */
/*   Updated: 2022/12/22 02:18:08 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "polymorphism.hpp"

class Animal {
	protected:
		std::string _type;

	public:
		Animal();
		Animal(const Animal &val);
		virtual ~Animal();
		Animal &operator=(const Animal &rhs);

		std::string getType() const;

		virtual void makeSound() const;
};
