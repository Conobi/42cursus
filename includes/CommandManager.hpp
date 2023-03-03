/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:04:58 by abastos           #+#    #+#             */
/*   Updated: 2023/03/03 16:06:33 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Command.hpp"
#include <map>

#define COMMANDS \
X(NICK, "NICK") \
X(PING, "PING") \
X(USER, "USER") \
X(INVALID_COMMAND, "INVALID_COMMAND")

#define X(command, name) command,
enum Commands {
  COMMANDS
};
#undef X

#define X(command, name) name,
const string commands_name[] = {
  COMMANDS
};
#undef X

class Command;
class Client;

class CommandManager {
  private:
    map<string, Command> _commands;

    Logger &_logger;

    void _loadCommands();
  public:
    CommandManager();
    ~CommandManager();

    void executeCommand(Client &client, const string &command, const string &arg);
};

/**
 * Commands prototype
 */

void nickCommand(Client &client, const string &arg);
void pingCommand(Client &client, const string &arg);
void userCommand(Client &client, const string &arg);
