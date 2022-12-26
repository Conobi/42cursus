/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:49:34 by conobi            #+#    #+#             */
/*   Updated: 2022/12/26 18:15:48 by conobi           ###   ########lyon.fr   */
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
		
		Brain &getBrain() const;

		virtual void makeSound() const;
		virtual void debugAddresses() const;

};
