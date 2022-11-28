/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 01:08:35 by conobi            #+#    #+#             */
/*   Updated: 2022/11/28 17:03:00 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "main.hpp"

class PhoneBook
{
	private:
		Contact _contacts[9];
		int _contacts_created;

		bool _is_full(void);
		bool _push_up(Contact *new_user);
		std::string _cut_dot(std::string str, size_t length) const;

		bool _add_contact (Contact *user);
		bool _list_contacts (void) const;
		Contact *_find_user (int index);
		void _show_user (Contact *user) const;


		void _add_prompter (
			const std::string prompt,
			Contact	*new_user,
			bool (Contact::*manager)(std::string)
		);
		void _search_prompter (
			const std::string prompt
		);

		bool _add_manager (void);
		bool _search_manager (void);
		bool _command_manager (const std::string input);

	public:
		PhoneBook (): _contacts_created(0) {};
		~PhoneBook ();

		void prompter (const std::string prompt);

};

#endif
