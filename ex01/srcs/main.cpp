/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:20:29 by conobi            #+#    #+#             */
/*   Updated: 2022/11/26 05:12:33 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "PhoneBook.hpp"
#include "Steps.hpp"

int main (void) {

	PhoneBook book;

	Steps::prompter("Command", book, Steps::command_manager);
	return (0);
}
