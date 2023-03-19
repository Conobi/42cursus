/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_clients.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:26:32 by conobi            #+#    #+#             */
/*   Updated: 2023/03/19 23:52:27 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Client &Server::_createNewClient() {
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

	Socket::epollAdd(this->_socket.epoll_fd(), client_fd, EPOLLIN | EPOLLPRI);

	this->_clients.push_back(Client(client_fd, client_ip, client_port));
	return (this->_clients.back());
}

void Server::_acceptNewClient() {
	Client &new_client = this->_createNewClient();

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

void Server::_handleClientEvent(int client_fd, uint32_t revents) {
	Client &client = this->_findClient(client_fd);

	if (revents & EPOLLIN || revents & EPOLLPRI) {
		this->_handleClientRead(client);

	} else if (revents & EPOLLOUT) {
		_logger.info("Write handler", true);
		// this->_handleClientWrite(client);
	} else if (revents & EPOLLERR || revents & EPOLLHUP) {
		_logger.info("Error handler", true);

		this->closeClient(client);
	} else {
		throw runtime_error("Unexpected event on client " + client.ip() + ":" +
							Utils::valToString(client.port()) +
							". revents: " + Utils::valToString(revents));
	}
}

void Server::closeClient(const Client &client) {
	int fd;

	_logger.log("Client " + client.ip() + ":" +
					Utils::valToString(client.port()) +
					" has closed its connection.",
				false);

	for (vector<Channel>::iterator channel = this->channels().begin();
		 channel != this->channels().end(); channel++) {
		if (channel->clients().find(client) != channel->clients().end()) {
			channel->clientLeave(client);
			this->_logger.info("Client " + client.nick() + " has left " +
								   channel->name() + " (connection closed).",
							   false);
			channel->broadcastMessage(
				NULL,
				Output(*this, &client, "QUIT",
					   ":Connection closed by the client"),
				ROLE_NONE);
			if (channel->clients().size() == 0) {
				this->_logger.info("Channel " + channel->name() +
									   " is now empty. Deleting it.",
								   false);
				this->channels().erase(find(this->channels().begin(),
											this->channels().end(), *channel));
				channel = this->channels().begin();
			}
		}
	}

	fd = client.fd();

	this->_clients.erase(
		remove(this->_clients.begin(), this->_clients.end(), client),
		this->_clients.end());

	if (close(fd) < -1) {
		throw runtime_error("Cannot close client fd. close(): " +
							Utils::valToString(strerror(errno)));
	}
}

Client *Server::getClient(const string &client_nick) {
	for (vector<Client>::iterator it = this->_clients.begin();
		 it != this->_clients.end(); it++) {
		if ((*it).nick() == client_nick)
			return &*it;
	}
	return NULL;
}
