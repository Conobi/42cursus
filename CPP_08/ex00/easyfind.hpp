/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:51:01 by conobi            #+#    #+#             */
/*   Updated: 2023/01/17 15:33:44 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <exception>
#include <vector>

template <typename T>
typename T::iterator easyfind(T& haystack, const int& needle) {
	typename T::iterator it;
	it = std::search_n(haystack.begin(), haystack.end(), 1, needle);

	if (it != haystack.end())
		return (it);
	else
		throw std::invalid_argument("No value has been found for this input.");
}
