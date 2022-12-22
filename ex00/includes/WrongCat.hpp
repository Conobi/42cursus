/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 01:16:15 by conobi            #+#    #+#             */
/*   Updated: 2022/12/22 01:52:56 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class WrongCat: public WrongAnimal {
	public:
		WrongCat();
		WrongCat(const WrongCat &val);
		~WrongCat();
		WrongCat &operator=(const WrongCat &rhs);

		void makeSound() const;
};
