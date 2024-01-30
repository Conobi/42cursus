/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:35:06 by conobi            #+#    #+#             */
/*   Updated: 2023/06/07 01:24:05 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <cstddef>
#include <vector>

int convertToInt(const char *str) {
	char *endptr;
	long long int result = std::strtoll(str, &endptr, 10);

	if (*endptr != '\0' || str == endptr || result > INT_MAX ||
		strlen(str) > 10)
		throw std::invalid_argument("Invalid positive integer: " +
									std::string(str));

	if (result < 0)
		throw std::out_of_range("Non-positive integer: " +
								Utils::valToString(result));

	return result;
}

PmergeMe::PmergeMe(int argc, char **argv) {
	int value;

	for (int i = 1; i < argc; ++i) {
		value = convertToInt(argv[i]);
		this->_vec.push_back(value);
		this->_deq.push_back(value);
	}
}

PmergeMe::~PmergeMe() {
}

PmergeMe::PmergeMe(const PmergeMe &val) {
	*this = val;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &rhs) {
	if (this != &rhs) {
		this->_vec = rhs._vec;
		this->_deq = rhs._deq;
	}
	return (*this);
}

std::vector<int> &PmergeMe::getVector() {
	return (this->_vec);
}

std::deque<int> &PmergeMe::getDeque() {
	return (this->_deq);
}

template <typename T>
void PmergeMe::_insertionSort(T &arr) {
	int n = arr.size();

	for (int i = 1; i < n; ++i) {
		int key = arr[i];
		int j = i - 1;

		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			--j;
		}

		arr[j + 1] = key;
	}
}

void PmergeMe::sortVector() {
	this->_mergeSort(this->_vec, 0, this->_vec.size() - 1);
}

void PmergeMe::_merge(std::vector<int> &arr, int left, int mid, int right) {
	int n1 = mid - left + 1;  // Size of left subarray
	int n2 = right - mid;	  // Size of right subarray

	std::vector<int> leftArr(n1);
	std::vector<int> rightArr(n2);

	for (int i = 0; i < n1; ++i) leftArr[i] = arr[left + i];
	for (int j = 0; j < n2; ++j) rightArr[j] = arr[mid + 1 + j];

	int left_i = 0;
	int right_i = 0;
	int merged_i = left;

	while (left_i < n1 && right_i < n2) {
		if (leftArr[left_i] <= rightArr[right_i]) {
			arr[merged_i] = leftArr[left_i];
			++left_i;
		} else {
			arr[merged_i] = rightArr[right_i];
			++right_i;
		}
		++merged_i;
	}

	// Copy the remaining elements
	while (left_i < n1) {
		arr[merged_i] = leftArr[left_i];
		++left_i;
		++merged_i;
	}
	while (right_i < n2) {
		arr[merged_i] = rightArr[right_i];
		++right_i;
		++merged_i;
	}
}

void PmergeMe::_mergeSort(std::vector<int> &arr, int left, int right) {
	if (right - left <= THRESHOLD) {
		this->_insertionSort(arr);
	} else if (left < right) {
		int mid = (left + right) / 2;

		this->_mergeSort(arr, left, mid);
		this->_mergeSort(arr, mid + 1, right);

		this->_merge(arr, left, mid, right);
	}
}

void PmergeMe::_merge(std::deque<int> &deque, std::deque<int> &left,
					  std::deque<int> &right) {
	while (!left.empty() && !right.empty()) {
		if (left.front() <= right.front()) {
			deque.push_back(left.front());
			left.pop_front();
		} else {
			deque.push_back(right.front());
			right.pop_front();
		}
	}

	// Copy the remaining elements, if any
	while (!left.empty()) {
		deque.push_back(left.front());
		left.pop_front();
	}
	while (!right.empty()) {
		deque.push_back(right.front());
		right.pop_front();
	}
}

void PmergeMe::_mergeSort(std::deque<int> &deque) {
	if (deque.size() <= THRESHOLD) {
		this->_insertionSort(deque);
		return;
	}
	std::deque<int> left;
	std::deque<int> right;
	int middle = deque.size() / 2;

	// Split the deque into two halves
	for (int i = 0; i < middle; ++i) left.push_back(deque[i]);
	for (size_t i = middle; i < deque.size(); ++i) right.push_back(deque[i]);

	// Recursive calls to merge sort the two halves
	this->_mergeSort(left);
	this->_mergeSort(right);

	// Merge the sorted halves
	deque.clear();	// Clear the original deque
	this->_merge(deque, left, right);
}

void PmergeMe::sortDeque() {
	this->_mergeSort(this->_deq);
	return;
}

void PmergeMe::printVector() {
	for (std::vector<int>::iterator it = this->_vec.begin();
		 it != this->_vec.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::printDeque() {
	for (std::deque<int>::iterator it = this->_deq.begin();
		 it != this->_deq.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}
