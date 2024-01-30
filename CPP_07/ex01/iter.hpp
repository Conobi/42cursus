/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:48:23 by conobi            #+#    #+#             */
/*   Updated: 2023/01/14 17:53:48 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

/* for main.cpp tests purpose */

template <typename T>
void print(T &x) {
	std::cout << x << std::endl;
	return;
}

template <typename T>
void add_ft(T &x) {
	x += 42;
	return;
}

/* My iter function */

template <typename T>
void iter(T array[], const size_t nb, void f(T &)) {
	for (size_t i = 0; i < nb; i++) {
		f(array[i]);
	}
}