/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:40:35 by conobi            #+#    #+#             */
/*   Updated: 2022/11/28 19:10:50 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <string>
#include <iostream>
#include <sys/time.h>

int	Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;

/* CONSTRUCTOR x DESTRUCTOR */

Account::Account(int initial_deposit) {
	this->_accountIndex = t::getNbAccounts();
	this->_amount = initial_deposit;
	this->_totalAmount += initial_deposit;
	this->_nbDeposits = 0;
	this->_nbWithdrawals = 0;
	this->_nbAccounts += 1;

	this->_displayTimestamp();
	std::cout
		<< "index:" << this->_accountIndex
		<< ";amount:" << this->_amount
		<< ";created" << std::endl;
}

Account::~Account(void) {
	this->_displayTimestamp();
	std::cout
		<< "index:" << this->_accountIndex
		<< ";amount:" << this->_amount
		<< ";closed" << std::endl;
}

Account::Account(void) {
}

/* GETTERS */

int Account::getNbAccounts(void) {
	return (t::_nbAccounts);
}

int Account::getTotalAmount(void) {
	return (t::_totalAmount);
}

int Account::getNbDeposits(void) {
	return (t::_totalNbDeposits);
}

int Account::getNbWithdrawals(void) {
	return (t::_totalNbWithdrawals);
}

void Account::displayAccountsInfos(void) {
	t::_displayTimestamp();
	std::cout
		<< "accounts:" << t::getNbAccounts()
		<< ";total:" << t::getTotalAmount()
		<< ";deposits:" << t::getNbDeposits()
		<< ";withdrawals:" << t::getNbWithdrawals()
		<< std::endl;
}

/* SETTERS */

void Account::makeDeposit( int deposit ) {
	int bak_amount;

	bak_amount = this->_amount;

	this->_amount += deposit;
	t::_totalAmount += deposit;
	this->_nbDeposits += 1;
	t::_totalNbDeposits += 1;

	this->_displayTimestamp();
	std::cout
		<< "index:" << this->_accountIndex
		<< ";p_amount:" << bak_amount
		<< ";deposit:" << deposit
		<< ";amount:" << this->_amount
		<< ";nb_deposits:" << this->_nbDeposits
		<< std::endl;
}

bool Account::makeWithdrawal( int withdrawal ) {
	int bak_amount;

	bak_amount = this->_amount;

	if (withdrawal > this->checkAmount()) {
		this->_displayTimestamp();
		std::cout
			<< "index:" << this->_accountIndex
			<< ";p_amount:" << bak_amount
			<< ";withdrawal:" << "refused"
			<< std::endl;
		return (false);
	} else {
		this->_amount -= withdrawal;
		t::_totalAmount -= withdrawal;
		this->_nbWithdrawals += 1;
		t::_totalNbWithdrawals += 1;

		this->_displayTimestamp();
		std::cout
			<< "index:" << this->_accountIndex
			<< ";p_amount:" << bak_amount
			<< ";withdrawal:" << withdrawal
			<< ";amount:" << this->_amount
			<< ";nb_withdrawals:" << this->_nbDeposits
			<< std::endl;
		return (true);
	}
}

int Account::checkAmount(void) const {
	return (this->_amount);
}

void Account::displayStatus(void) const {
	this->_displayTimestamp();
	std::cout
		<< "index:" << this->_accountIndex
		<< ";amount:" << this->_amount
		<< ";deposits:" << this->_nbDeposits
		<< ";withdrawals:" << this->_nbWithdrawals
		<< std::endl;
}

/* UTILS */

void Account::_displayTimestamp(void) {
	struct timeval tp;
	gettimeofday(&tp, NULL);
	std::cout << "[" << tp.tv_sec << "_" << tp.tv_usec << "] ";
}
