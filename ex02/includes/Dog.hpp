/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:49:34 by conobi            #+#    #+#             */
/*   Updated: 2022/12/26 18:19:23 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Dog: public AAnimal {
	private:
		Brain *_brain;

	public:
		Dog();
		Dog(const Dog &val);
		~Dog();
		Dog &operator=(const Dog &rhs);

		Brain &getBrain() const;

		virtual void makeSound() const;
		virtual void debugAddresses() const;
};
