/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_utils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:12:44 by conobi            #+#    #+#             */
/*   Updated: 2023/02/22 14:50:42 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>

#include "Server.hpp"

void Server::log(const string &msg, const bool &verbose_only) {
	string verbose_mode = static_cast<string>(getenv("VERBOSE"));
	if ((verbose_only && (verbose_mode == "true" || verbose_mode == "1")) ||
		!verbose_only) {
		time_t now = time(0);
		char *dt = ctime(&now);
		cout << "[" << dt << "] " << msg << endl;
	}
}
