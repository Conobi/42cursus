/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:27:07 by conobi            #+#    #+#             */
/*   Updated: 2023/01/13 16:09:09 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "type.hpp"

class Base {
	public:
		virtual ~Base();
};

class A : public Base {};

class B : public Base {};

class C : public Base {};