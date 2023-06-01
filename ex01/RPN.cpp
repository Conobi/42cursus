/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:38:25 by conobi            #+#    #+#             */
/*   Updated: 2023/06/01 17:06:24 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

#include <cctype>
#include <stdexcept>
#include <string>

RPN::~RPN() {
}

RPN::RPN(const RPN &val) {
	*this = val;
}

RPN &RPN::operator=(const RPN &rhs) {
	if (this != &rhs) {
		this->_stack = rhs._stack;
	}
	return (*this);
}

void RPN::_evalOperator(const std::string &op) {
	int a;
	int b;

	if (this->_stack.size() < 2)
		throw std::runtime_error("Invalid expression");
	b = this->_stack.top();
	this->_stack.pop();
	a = this->_stack.top();
	this->_stack.pop();
	if (op == "+")
		this->_stack.push(a + b);
	else if (op == "-")
		this->_stack.push(a - b);
	else if (op == "*")
		this->_stack.push(a * b);
	else if (op == "/") {
		if (b == 0)
			throw std::runtime_error("Division by zero");
		this->_stack.push(a / b);
	}
}

int RPN::_strToInt(const std::string &str) {
	int number;

	if (str.length() > 1 || !isdigit(str[0]))
		throw std::runtime_error("Invalid expression");
	if (isdigit(str[0]))
		number = str[0] - '0';
	return (number);
}

RPN::RPN(const std::string expr) {
	// Split the expression, add the numbers to the stack and evaluate the
	// operators. We are forbidden to use a vector.
	std::stringstream ss(expr);
	std::string token;
	int number;

	while (std::getline(ss, token, ' ')) {
		if (token == "+" || token == "-" || token == "*" || token == "/") {
			this->_evalOperator(token);
		} else {
			try {
				number = this->_strToInt(token.c_str());
				if (number < 0)
					throw std::runtime_error("Invalid expression");
				this->_stack.push(number);
			} catch (std::runtime_error &e) {
				throw e;
			} catch (std::exception &e) {
				throw std::runtime_error("Invalid expression");
			}
		}
	}
	if (this->_stack.size() != 1)
		throw std::runtime_error("Invalid expression");
	std::cout << this->_stack.top() << std::endl;
}
