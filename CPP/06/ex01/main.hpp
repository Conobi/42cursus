/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:13:00 by conobi            #+#    #+#             */
/*   Updated: 2023/01/13 15:20:47 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

struct Data {
		std::string str0;
		std::string str1;
		std::string str2;
};

uintptr_t serialize(Data *toast);

Data *deserialize(uintptr_t raw);
