/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:39:44 by conobi            #+#    #+#             */
/*   Updated: 2022/12/05 16:11:16 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
# define HARL_HPP

# include <string>
# include <iostream>

class Harl {
	private:
		typedef void (Harl:: *_cmnd_ptr)(void) const;
		_cmnd_ptr _cmnd_ptrs[4];
		std::string _cmnd_strs[4];
		void _debug(void) const;
		void _info(void) const;
		void _warning(void) const;
		void _error(void) const;


	public:
		Harl(/* args */);
		~Harl();
		void complain (std::string level);
};

#endif
