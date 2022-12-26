/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:49:34 by conobi            #+#    #+#             */
/*   Updated: 2022/12/26 16:30:16 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Cat: public Animal {
	private:
		Brain *_brain;

	public:
		Cat();
		Cat(const Cat &val);
		~Cat();
		Cat &operator=(const Cat &rhs);

		virtual void makeSound() const;
		virtual void debugAddresses() const;
};
