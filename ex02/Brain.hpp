/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 02:19:25 by conobi            #+#    #+#             */
/*   Updated: 2023/01/06 02:12:57 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "main.hpp"

class Brain {
	private:
		std::string _ideas[100];

	public:
		Brain();
		Brain(const Brain &val);
		virtual ~Brain();
		Brain &operator=(const Brain &rhs);

		const std::string *getIdeas() const;
		const std::string getIdea(size_t index) const;
		void setIdea(size_t index, std::string str);
};
