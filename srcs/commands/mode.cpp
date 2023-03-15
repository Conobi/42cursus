/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:24:04 by abastos           #+#    #+#             */
/*   Updated: 2023/03/15 17:57:59 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

static string cleanByTokens(const string &str, const string &tokens) {
  string result;
  for (size_t i = 0; i < str.size(); i++) {
    if (tokens.find(str[i]) != string::npos) {
      result += str[i];
    }
  }
  return result;
}

static string createModeString(const Channel *channel) {
  string modeString = " +";

  if (channel->invite_mode()) {
    modeString += "i";
  }

  if (channel->password_mode()) {
    modeString += "k";
  }

  // todo: idk if this is the right way to do it if there are no modes
  return modeString.size() > 2 ? modeString : "";
}

void Command::mode(Server &server, Client &client, const Input &input) {
  if (input.parameters().size() < 1) {
    client.sendMessage(Output(server, NULL, "461", input.command() + " :Not enough parameters"));
    return;
  }

  string target = input.parameters()[0];

  Channel *channel = server.getChannel(target);

  if (!channel) {
    client.sendMessage(Output(server, &client, "403", client.nick() + " " + target + " :No such channel"));
    return;
  }


  if (input.parameters().size() == 1) {
    client.sendMessage(Output(server, &client, "324", client.nick() + " " + target + createModeString(channel)));
    // todo: maybe send the creation time too
    // client.sendMessage(Output(server, &client, "329", client.nick() + " " + target + " " + to_string(channel->creation_time())));
    return;
  }

  if (!channel->isOp(client)) {
    client.sendMessage(Output(server, &client, "482", client.nick() + " " + target + " :You're not channel operator"));
    return;
  }

  string mode = input.parameters()[1];

  if ((mode[0] != '+' && mode[0] != '-')) {
    client.sendMessage(Output(server, &client, "472", client.nick() + " " + mode[0] + " :is unknown mode char to me"));
    return;
  }

  bool toSet = mode[0] == '+';
  bool modeChanged = false;

  for (size_t i = 1; i < mode.size(); i++) {
    switch (mode[i]) {
      case 'i': {
        channel->invite_mode() = toSet;
        modeChanged = true;
        break;
      }
      case 'k': {
        channel->password_mode() = toSet;
        modeChanged = true;
        break;
      }
      case 'o': {

      }
      default:
        client.sendMessage(Output(server, &client, "472", client.nick() + " " + mode[i] + " :is unknown mode char to me"));
    }
  }
  if (modeChanged) {
    channel->broadcastMessage(Output(server, &client, "", "MODE " + target + " " + mode[0] + cleanByTokens(mode, "ik")), ROLE_NONE);
  }
}
