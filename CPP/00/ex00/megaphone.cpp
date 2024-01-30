/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:08:47 by conobi            #+#    #+#             */
/*   Updated: 2022/11/24 01:03:56 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>

int main (int argc, char **argv) {

	int		i;
	size_t	j;

	if (argc < 2)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	else {
		for (i = 1; i < argc; i++) {
			for (j = 0; j < strlen(argv[i]); j++)
				std::cout << (char)toupper((int)(argv[i][j]));
			std::cout << " ";
		}
		std::cout << std::endl;
	}
	return (0);
}
