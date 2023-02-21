#pragma once
#include "irc.hpp"

class Server {
  public:
    Server();

  private:
    int _port;
    string password;
};
