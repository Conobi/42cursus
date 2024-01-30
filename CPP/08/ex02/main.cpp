/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:03:02 by conobi            #+#    #+#             */
/*   Updated: 2023/01/17 20:00:35 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <list>

#include "MutantStack.hpp"

void testsMutant() {
	MutantStack<int> mstack;

	mstack.push(5);
	mstack.push(17);
	std::cout << mstack.top() << std::endl;
	mstack.pop();
	std::cout << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	//[...]
	mstack.push(0);
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite) {
		std::cout << *it << std::endl;
		++it;
	}
	std::stack<int> s(mstack);
}

void testsMutantCopy() {
	MutantStack<int> *init = new MutantStack<int>;
	MutantStack<int> &mstack = *init;

	mstack.push(5);
	mstack.push(17);
	std::cout << mstack.top() << std::endl;
	mstack.pop();
	std::cout << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	//[...]
	mstack.push(0);

	MutantStack<int> stack_cpy(mstack);
	delete init;
	MutantStack<int>::iterator it = stack_cpy.begin();
	MutantStack<int>::iterator ite = stack_cpy.end();
	++it;
	--it;

	while (it != ite) {
		std::cout << *it << std::endl;
		++it;
	}
}

void testsList() {
	std::list<int> lstack;

	lstack.push_back(5);
	lstack.push_back(17);
	std::cout << lstack.back() << std::endl;
	lstack.pop_back();
	std::cout << lstack.size() << std::endl;
	lstack.push_back(3);
	lstack.push_back(5);
	lstack.push_back(737);
	//[...]
	lstack.push_back(0);
	std::list<int>::iterator it = lstack.begin();
	std::list<int>::iterator ite = lstack.end();
	++it;
	--it;
	while (it != ite) {
		std::cout << *it << std::endl;
		++it;
	}
	std::list<int> s(lstack);
}

int main(void) {
	testsMutant();
	std::cout << "-----" << std::endl;
	testsList();
	std::cout << "-----" << std::endl;
	testsMutantCopy();
	return (0);
}