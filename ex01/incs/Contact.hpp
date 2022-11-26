/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 00:41:08 by conobi            #+#    #+#             */
/*   Updated: 2022/11/26 21:10:09 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <string>
# include <iostream>

class Contact
{
	private:
		int	_index;
		std::string _first_name;
		std::string _last_name;
		std::string _nickname;
		std::string _phone_number;
		std::string _secret;


	public:
		Contact ();
		~Contact ();

		bool is_valid (void) const;

		bool set_first_name (std::string str);
		std::string get_first_name (void) const;
		bool set_last_name (std::string str);
		std::string get_last_name (void) const;
		bool set_nickname (std::string str);
		std::string get_nickname (void) const;
		std::string get_name (void) const;
		bool set_phone_number (std::string str);
		std::string get_phone_number (void) const;
		bool set_secret (std::string str);
		std::string get_secret (void) const;
		bool set_index (int index);
		int get_index (void) const;
};

#endif
