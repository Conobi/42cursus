/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:49:34 by conobi            #+#    #+#             */
/*   Updated: 2023/01/06 02:08:35 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal {
	private:
		Brain *_brain;

	public:
		Cat();
		Cat(const Cat &val);
		~Cat();
		Cat &operator=(const Cat &rhs);

		Brain &getBrain() const;

		virtual void makeSound() const;
		virtual void debugAddresses() const;
};
