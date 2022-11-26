/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 01:08:35 by conobi            #+#    #+#             */
/*   Updated: 2022/11/26 05:54:09 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"

class PhoneBook
{
	private:
		Contact _contacts[9];

	public:
		PhoneBook (/* args */);
		~PhoneBook ();

		bool add_contact (Contact user);
		void list_contacts (void) const;
		int show_user (int index) const;
};

#endif
