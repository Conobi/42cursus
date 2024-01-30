/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:41:38 by conobi            #+#    #+#             */
/*   Updated: 2022/12/05 17:00:19 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl() {
	_cmnd_ptrs[0] = &Harl::_debug;
	_cmnd_ptrs[1] = &Harl::_info;
	_cmnd_ptrs[2] = &Harl::_warning;
	_cmnd_ptrs[3] = &Harl::_error;
	_cmnd_strs[0] = "DEBUG";
	_cmnd_strs[1] = "INFO";
	_cmnd_strs[2] = "WARNING";
	_cmnd_strs[3] = "ERROR";
}

Harl::~Harl() {
}

void Harl::complain(std::string level) {
	for (size_t i = 0; i < 4; i++) {
		if (level == _cmnd_strs[i]) {
			(void)(this->*_cmnd_ptrs[i])();
			return ;
		}
	}
}

void Harl::_debug(void) const {
	std::cout << "I love having extra bacon for my ";
	std::cout << "7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!";
	std::cout << std::endl;
}

void Harl::_info(void) const {
	std::cout << " cannot believe adding extra bacon costs more money. ";
	std::cout << "You didn’t put enough bacon in my burger! ";
	std::cout << "If you did, I wouldn’t be asking for more!";
	std::cout << std::endl;
}

void Harl::_warning(void) const {
	std::cout << "I think I deserve to have some extra bacon for free. ";
	std::cout << "I’ve been coming for years whereas you started working ";
	std::cout << "here since last month. ";
	std::cout << "I think I deserve to have some extra bacon for free.";
	std::cout << std::endl;
}

void Harl::_error(void) const {
	std::cout << "This is unacceptable! I want to speak to the manager now.";
	std::cout << std::endl;
}

