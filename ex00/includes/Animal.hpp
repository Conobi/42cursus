/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:49:34 by conobi            #+#    #+#             */
/*   Updated: 2022/12/22 02:25:06 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "main.hpp"

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
