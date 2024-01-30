/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:03:34 by conobi            #+#    #+#             */
/*   Updated: 2023/01/17 19:57:46 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <deque>
#include <exception>
#include <iostream>
#include <stack>
#include <string>

#define RED_FG "\001\033[91m\002"
#define GRN_FG "\001\033[32m\002"
#define YEL_FG "\001\033[33m\002"
#define BLU_FG "\001\033[34m\002"
#define MAG_FG "\001\033[35m\002"
#define CYN_FG "\001\033[36m\002"
#define WHT_FG "\001\033[37m\002"
#define BLK_FG "\001\033[30m\002"
#define ACC_FG "\001\033[38;2;65;208;117m\002"

#define RED_BG "\001\033[101m\002"
#define GRN_BG "\001\033[42m\002"
#define YEL_BG "\001\033[43m\002"
#define BLU_BG "\001\033[44m\002"
#define MAG_BG "\001\033[45m\002"
#define CYN_BG "\001\033[46m\002"
#define WHT_BG "\001\033[47m\002"
#define BLK_BG "\001\033[40m\002"
#define ACC_BG "\001\033[48;2;65;208;117m\002"

#define RESET "\001\033[0m\002"
#define BOLD "\001\033[1m\002"
#define ITALIC "\001\033[3m\002"
#define UNDERLINE "\001\033[4m\002"

template <typename T>
class MutantStack : public std::stack<T> {
	public:
		typedef typename std::stack<T>::container_type::iterator iterator;

		MutantStack();
		~MutantStack();
		MutantStack(const MutantStack &val);
		MutantStack &operator=(const MutantStack &rhs);

		typename std::stack<T>::container_type::iterator begin() {
			return (std::begin(std::stack<T>::c));
		}

		typename std::stack<T>::container_type::iterator end() {
			return (std::end(std::stack<T>::c));
		}
};

/* ORTHODOX FORM COMPLIANCE */
template <typename T>
MutantStack<T>::MutantStack() {
	std::cout << BLU_FG << ITALIC << "MutantStack Default constructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
	return;
}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack<T> &val) {
	std::cout << MAG_FG << ITALIC << "MutantStack Copy constructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
	*this = val;
}

template <typename T>
MutantStack<T>::~MutantStack() {
	std::cout << YEL_FG << ITALIC << "MutantStack Destructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
}

template <typename T>
MutantStack<T> &MutantStack<T>::operator=(const MutantStack<T> &rhs) {
	std::cout << MAG_FG << ITALIC << "MutantStack Copy assignment " << RESET
			  << ITALIC << "operator called" << RESET << std::endl;
	this->c = rhs.c;
	return (*this);
}