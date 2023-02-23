/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_utils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:12:44 by conobi            #+#    #+#             */
/*   Updated: 2023/02/23 01:28:48 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>

#include "Server.hpp"

void Server::log(const string &msg, const bool &verbose_only) {
	bool verbose_mode = false;
	char *env_value = getenv("VERBOSE");

	if (env_value && (static_cast<string>(env_value) == "true" ||
					  static_cast<string>(env_value) == "1"))
		verbose_mode = true;

	if (!verbose_only || (verbose_only && verbose_mode)) {
		time_t now = time(0);
		char *dt = ctime(&now);
		dt[strlen(dt) - 1] = '\0';
		cout << "[" << dt << "] " << msg << endl;
	}
}
