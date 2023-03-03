/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:18:51 by abastos           #+#    #+#             */
/*   Updated: 2023/03/03 15:29:10 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Command::Command(): _logger(*(new Logger("DefaultCommand"))) {};

Command::Command(const string &name, func_t f): _name(name), _executor(f), _logger(*(new Logger(name))) {};

Command::~Command() {};

const string &Command::name() const {
  return this->_name;
}

Command &Command::operator=(const Command &rhs) {
	if (this != &rhs) {
		this->_executor = rhs._executor;
    this->_name = rhs._name;
	}
	return *this;
}

void Command::execute(Client &client, const string &arg) const {
  this->_executor(client, arg);
}
