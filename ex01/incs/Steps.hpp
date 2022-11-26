/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Steps.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 02:44:10 by conobi            #+#    #+#             */
/*   Updated: 2022/11/26 23:21:13 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_HPP
# define PROMPT_HPP

# include <string>
# include <iostream>
# include "PhoneBook.hpp"
# include "Contact.hpp"

class Steps
{
	private:
		static void prompter (
			const std::string prompt,
			PhoneBook book,
			bool (*manager)(std::string, PhoneBook)
		);

		static bool command_manager(
			const std::string input,
			PhoneBook book
		);

		static bool add_manager(
			PhoneBook book
		);

		static void add_prompter (
			const std::string prompt,
			Contact	*new_user,
			bool (Contact::*manager)(std::string)
		);

	public:
		Steps();
		~Steps();

};

#endif
