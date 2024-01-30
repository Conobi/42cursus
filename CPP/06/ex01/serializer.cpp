/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:19:36 by conobi            #+#    #+#             */
/*   Updated: 2023/01/13 15:21:24 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

uintptr_t serialize(Data *toast) {
	return (reinterpret_cast<uintptr_t>(toast));
}

Data *deserialize(uintptr_t raw) {
	return (reinterpret_cast<Data *>(raw));
}