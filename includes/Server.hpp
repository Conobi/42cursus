#pragma once
#include "irc.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

class Server {
  public:
    Server();
    Server(const int port, const string password);
    ~Server();

    int createSocket(const int domain, const int type, const int protocol);
    void setSocketAddr(const int port);
    void bindSocket(const int socket);

  private:
    int _port;
    string _password;
    int _sockfd;
    struct sockaddr_in _sockAddr;
    struct _sockaddr_in_serv_addr;
    struct _cli_addr;

};
