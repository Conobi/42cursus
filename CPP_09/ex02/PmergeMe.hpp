/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:25:37 by conobi            #+#    #+#             */
/*   Updated: 2023/06/06 20:47:13 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <climits>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#define RED_FG "\001\033[91m\002"
#define GRN_FG "\001\033[32m\002"
#define YEL_FG "\001\033[33m\002"
#define BLU_FG "\001\033[34m\002"
#define MAG_FG "\001\033[35m\002"
#define CYN_FG "\001\033[36m\002"
#define WHT_FG "\001\033[37m\002"
#define BLK_FG "\001\033[30m\002"
#define ACC_FG "\001\033[38;2;65;208;117m\002"

#define RED_BG "\001\033[101m\002"
#define GRN_BG "\001\033[42m\002"
#define YEL_BG "\001\033[43m\002"
#define BLU_BG "\001\033[44m\002"
#define MAG_BG "\001\033[45m\002"
#define CYN_BG "\001\033[46m\002"
#define WHT_BG "\001\033[47m\002"
#define BLK_BG "\001\033[40m\002"
#define ACC_BG "\001\033[48;2;65;208;117m\002"

#define RESET "\001\033[0m\002"
#define BOLD "\001\033[1m\002"
#define ITALIC "\001\033[3m\002"
#define UNDERLINE "\001\033[4m\002"

#define THRESHOLD 15

class Utils {
	public:
		template <typename T>
		static std::string valToString(T value) {
			std::ostringstream ss;

			ss << value;
			return ss.str();
		}
};

class PmergeMe {
	private:
		PmergeMe();
		std::vector<int> _vec;
		std::deque<int> _deq;

		template <typename T>
		void _insertionSort(T &arr);
		void _merge(std::vector<int> &arr, int left, int mid, int right);
		void _mergeSort(std::vector<int> &arr, int left, int right);
		void _merge(std::deque<int> &deque, std::deque<int> &left,
					std::deque<int> &right);
		void _mergeSort(std::deque<int> &deque);

	public:
		PmergeMe(int argc, char **argv);
		PmergeMe(PmergeMe const &src);
		~PmergeMe();

		PmergeMe &operator=(PmergeMe const &rhs);

		std::vector<int> &getVector();
		std::deque<int> &getDeque();
		void printVector();
		void printDeque();

		void sortVector();
		void sortDeque();
};
