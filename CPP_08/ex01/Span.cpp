/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:47:29 by conobi            #+#    #+#             */
/*   Updated: 2023/01/18 14:06:00 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

/* ORTHODOX FORM COMPLIANCE */

Span::Span() {
}

Span::Span(const Span &val) {
	*this = val;
}

Span::~Span() {
}

Span &Span::operator=(const Span &rhs) {
	this->_arr = rhs._arr;
	return (*this);
}

/* ASSIGNEMENT CONSTRUCTOR */

Span::Span(const std::size_t max_size) : _max_size(max_size) {
}

/* MEMBER FUNCTIONS */
void Span::addNumber(const int val) {
	std::vector<int> &vec = this->_arr;

	if (vec.size() >= this->_max_size)
		throw Span::UponSizeException();

	vec.insert(std::upper_bound(vec.begin(), vec.end(), val), val);
}

/* MEMBER FUNCTIONS */
void Span::addNumbers(const int val[], const std::size_t size) {
	for (size_t i = 0; i < size; i++) {
		this->addNumber(val[i]);
	}
}


long long Span::longestSpan() {
	if (this->_arr.size() <= 1)
		throw Span::NotEnoughNumbersException();

	return (static_cast<long long>(this->_arr.back()) -
			static_cast<long long>(this->_arr.front()));
}

long long Span::shortestSpan() {
	std::vector<int> &vec = this->_arr;
	long long minimum_span = vec.back();
	long long temp_val;

	if (this->_arr.size() <= 1)
		throw Span::NotEnoughNumbersException();

	for (std::vector<int>::iterator it = ++(vec.begin()); it != vec.end();
		 ++it) {
		temp_val =
			(static_cast<long long>(*it) - static_cast<long long>(*(it - 1)));
		if (temp_val < minimum_span)
			minimum_span = temp_val;
	}
	return (minimum_span);
}
