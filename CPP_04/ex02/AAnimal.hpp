/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:10:13 by conobi            #+#    #+#             */
/*   Updated: 2023/01/06 02:13:00 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "main.hpp"

class AAnimal {
	protected:
		std::string _type;

	public:
		AAnimal();
		AAnimal(const AAnimal &val);
		virtual ~AAnimal();
		AAnimal &operator=(const AAnimal &rhs);

		std::string getType() const;

		virtual void makeSound() const = 0;
		virtual void debugAddresses() const;
};
