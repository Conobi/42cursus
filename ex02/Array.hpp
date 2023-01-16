/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:00:19 by conobi            #+#    #+#             */
/*   Updated: 2023/01/16 15:54:10 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// #include <cstddef>
#include <exception>
#include <iostream>

template <typename T>
class Array {
	private:
		T *_arr_ptr;
		std::size_t _size;

	public:
		Array() {
			this->_arr_ptr = NULL;
			this->_size = 0;
		}

		Array(unsigned int n) {
			this->_arr_ptr = new T[n];
			this->_size = static_cast<std::size_t>(n);
		}

		Array(const Array &val) {
			this->_arr_ptr = new T[val._size];
			this->_size = static_cast<std::size_t>(val._size);

			*this = val;
		}

		~Array() {
			delete[] this->_arr_ptr;
		}

		Array &operator=(const Array &rhs) {
			for (std::size_t i = 0; i < rhs._size; i++) {
				this->_arr_ptr[i] = rhs._arr_ptr[i];
			}
			return (*this);
		}

		T &operator[](std::size_t index) {
			if (index >= this->size())
				throw Array::OutOfRangeIndexException();
			return (this->_arr_ptr[index]);
		}

		std::size_t size() {
			return (this->_size);
		}

		class OutOfRangeIndexException : public std::exception {
			public:
				virtual const char *what() const throw() {
					return ("No entry was found for the index given.");
				}
		};
};
