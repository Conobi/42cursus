/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 01:08:35 by conobi            #+#    #+#             */
/*   Updated: 2022/11/26 18:48:45 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <string>
# include <iostream>
# include "Contact.hpp"

class PhoneBook
{
	private:
		Contact _contacts[9];
		int _contacts_created;
		bool _is_full(void);
		bool _push_up(Contact new_user);

	public:
		PhoneBook (): _contacts_created(0) {};
		~PhoneBook ();

		bool add_contact (Contact user);
		void list_contacts (void) const;
		void show_user (int index) const;
};

#endif
