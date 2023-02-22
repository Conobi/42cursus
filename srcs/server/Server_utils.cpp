/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_utils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:12:44 by conobi            #+#    #+#             */
/*   Updated: 2023/02/22 02:22:09 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// todo: remove guard and implement exceptions
int Server::_guard(int code, const char *process) {
	if (code == -1) {
		cerr << FRED("ERROR: ");
		perror(process);
		exit(EXIT_FAILURE);
	}
	return code;
}
