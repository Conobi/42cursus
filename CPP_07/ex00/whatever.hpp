/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:26:30 by conobi            #+#    #+#             */
/*   Updated: 2023/01/14 15:43:08 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

template <typename T>
void swap(T& val1, T& val2) {
	T tmp = val1;

	val1 = val2;
	val2 = tmp;
}

template <typename T>
T min(const T& val1, const T& val2) {
	if (val1 < val2)
		return (val1);
	return (val2);
}

template <typename T>
T max(const T& val1, const T& val2) {
	if (val1 > val2)
		return (val1);
	return (val2);
}