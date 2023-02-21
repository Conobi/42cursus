#include "Server.hpp"

int guard(int code, const char *process) {
  if (code == -1) {
    cerr << FRED("ERROR: ");
    perror(process);
    exit(EXIT_FAILURE);
  }
  return code;
}


Server::Server() {
  return;
}

Server::Server(const int port, const string password): _port(port), _password(password) {
  int opt = 1;

  cout << FGRN("Server listening on port ") << port << endl;
  // Create socket connection with ipv4 protocol
  this->createSocket(AF_INET, SOCK_STREAM, 0);

  // guard(fcntl(this->_sockfd, F_SETFL, O_NONBLOCK), "fcntl");

  guard(setsockopt(this->_sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)), "setsockopt");

  // Bind socket to port
  this->setSocketAddr(port);

  this->bindSocket(this->_sockfd);
}

Server::~Server() {

}

int Server::createSocket(const int domain, const int type, const int protocol) {
  this->_sockfd = guard(socket(domain, type, protocol), "socket");
  cout << FGRN("Socket created: ") << this->_sockfd << endl;
  return this->_sockfd;
}

void Server::setSocketAddr(const int port) {
  sockaddr_in sockAddr;

  bzero(&sockAddr, sizeof(sockAddr));
  // todo: replace AF_INET
  sockAddr.sin_family = AF_INET;
  sockAddr.sin_addr.s_addr = INADDR_ANY;
  sockAddr.sin_port = htons(port);

  this->_sockAddr = sockAddr;
}

void Server::bindSocket(const int socket) {
  if (bind(socket, (const struct sockaddr *)&this->_sockAddr, sizeof(this->_sockAddr)) < 0) {
    if (errno == EADDRINUSE) {
      perror(FRED("ERROR: ") "Address already in use");
      exit(EXIT_FAILURE);
    }
    perror(FRED("ERROR: ") "bind");
    exit(EXIT_FAILURE);
  }
}
