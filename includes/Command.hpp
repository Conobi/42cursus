/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:18:46 by abastos           #+#    #+#             */
/*   Updated: 2023/03/03 15:29:17 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Logger.hpp"
#include "irc.hpp"
#include "Client.hpp"

class Client;
// todo: maybe we should use an struct for args to support more than one arg
typedef void (*func_t)(Client &client, const string &);

class Command {
  private:

    string _name;
    func_t _executor;

    Logger &_logger;

  public:
    Command();
    Command(const string &name, func_t f);
    ~Command();

    Command & operator=(const Command &rhs);

    const string &name() const;
    void execute(Client &client, const string &arg) const;
};
