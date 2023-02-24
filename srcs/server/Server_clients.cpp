/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_clients.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:26:32 by conobi            #+#    #+#             */
/*   Updated: 2023/02/24 02:56:14 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Client &Server::_createNewClient() {
	Client *new_client;

	int client_fd;
	ushort client_port;
	string client_ip;

	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(addr);

	bzero(&addr, sizeof(addr));

	client_fd =
		accept(this->_socket.sock_fd(), (struct sockaddr *)&addr, &addr_len);

	if (client_fd < 0) {
		throw runtime_error(
			"Unexpected issue on client connection. accept(): " +
			Utils::valToString(strerror(errno)));
	}

	client_ip = inet_ntoa(addr.sin_addr);
	client_port = ntohs(addr.sin_port);

	new_client = new Client(client_fd, client_ip, client_port);

	return (*new_client);
}

void Server::_acceptNewClient() {
	Client &new_client = this->_createNewClient();

	Socket::epollAdd(this->_socket.epoll_fd(), new_client.fd(),
					 EPOLLIN | EPOLLPRI);
	this->_clients.push_back(new_client);

	_logger.log("Client " + new_client.ip() + ":" +
					Utils::valToString(new_client.port()) +
					" has been accepted.",
				false);
}

Client &Server::_findClient(int client_fd) {
	// Find the client in the vector by its fd
	vector<Client>::iterator client =
		find(this->_clients.begin(), this->_clients.end(), client_fd);

	// Is this code even reachable?
	if (client == this->_clients.end()) {
		if (close(client_fd) < 0) {
			throw runtime_error(
				"A client sent an event but wasn't registered in the "
				"socket. In addition, we were unable to close its fd. "
				"close(): " +
				Utils::valToString(strerror(errno)));
		}
		throw runtime_error(
			"A client sent an event but wasn't registered in the socket.");
	}

	return (*client);
}

void Server::_closeClient(const Client &client) {
	_logger.log("Client " + client.ip() + ":" +
					Utils::valToString(client.port()) +
					" has closed its connection.",
				false);

	this->_clients.erase(
		remove(this->_clients.begin(), this->_clients.end(), client.fd()),
		this->_clients.end());
}

void Server::_handleClientEvent(int client_fd, uint32_t revents) {
	Client &client = this->_findClient(client_fd);

	if (revents & EPOLLIN || revents & EPOLLPRI) {
		this->_handleClientRead(client);

	} else if (revents & EPOLLOUT) {
		_logger.info("Write handler", true);
		// this->_handleClientWrite(client);
	} else if (revents & EPOLLERR || revents & EPOLLHUP) {
		_logger.info("Error handler", true);

		this->_closeClient(client);
	} else {
		throw runtime_error("Unexpected event on client " + client.ip() + ":" +
							Utils::valToString(client.port()) +
							". revents: " + Utils::valToString(revents));
	}
}
