/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:48:35 by abastos           #+#    #+#             */
/*   Updated: 2023/03/03 16:06:15 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "CommandManager.hpp"

CommandManager::CommandManager():  _logger(*(new Logger("CommandManager"))) {
  this->_loadCommands();
}

CommandManager::~CommandManager() {}

void CommandManager::_loadCommands()  {
  size_t commands_size = 0;

  for (size_t i = NICK; i != INVALID_COMMAND; i++) {
    string command = commands_name[static_cast<Commands>(i)];
    if (command == "INVALID_COMMAND") {
      continue;
    }
    this->_logger.info("Loading command: " + command, true);

    switch (static_cast<Commands>(i)) {
      case NICK:
        this->_commands[command] = Command(command, nickCommand);
        break;
      case PING:
        this->_commands[command] = Command(command, pingCommand);
        break;
      case USER:
        this->_commands[command] = Command(command, userCommand);
        break;
      default:
        break;
    }
    commands_size += 1;
  }

  this->_logger.info("Loaded " + Utils::valToString(commands_size) + " commands", true);
}

void CommandManager::executeCommand(Client &client, const string &command, const string &arg) {
  map<string, Command>::iterator it = this->_commands.find(command);
  if (it != this->_commands.end()) {
    it->second.execute(client, arg);
  } else {
    this->_logger.info("Command not found: " + command, true);
  }
}
