/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:36:58 by conobi            #+#    #+#             */
/*   Updated: 2022/11/29 19:58:03 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

static std::string string_replacer (
	const std::string str,
	const std::string to_find,
	const std::string to_replace
) {
	std::string ret;
	size_t n;
	size_t len_to_find;
	size_t len_to_replace;

	ret = str;
	len_to_find = to_find.length();
	len_to_replace = to_replace.length();

	while (len_to_find && ret.find(to_find) != ret.npos) {
		n = ret.find(to_find);
		ret = ret.substr(0, n)
			+ to_replace
			+ ret.substr(n + len_to_find, ret.length() - 1);
	}

	return (ret);
}

static std::string read_file (
	const std::string filename
) {
	std::ifstream in_file(filename);
	std::stringstream file_content;

	if (in_file.is_open()) {
		file_content << in_file.rdbuf();
		in_file.close();
		return (file_content.str());
	}
	std::cerr
		<< RED_FG
		<< "An error occured while reading `"
		<< filename << "`. "
		<< "Does it exists and is it readable?"
		<< RESET << std::endl;
	return ("");
}

static bool write_file (
	const std::string filename,
	const std::string content
) {
	std::ofstream out_file(filename);

	if (out_file.is_open()) {
		out_file << content;
		out_file.close();
		return (true);
	}
	std::cerr
		<< RED_FG
		<< "An error occured while writing to `"
		<< filename << "`."
		<< RESET << std::endl;
	return (false);
}

static void loser_replace (
	std::string filename,
	std::string to_find,
	std::string to_replace
) {
	std::string file_content;

	file_content = read_file(filename);
	if (file_content.length() > 0) {
		file_content = string_replacer(file_content, to_find, to_replace);
		write_file(filename + ".replace", file_content);
	}
}

int main(int argc, char *argv[]) {
	if (argc == 4 && std::string(argv[1]).length() > 0) {
		loser_replace(argv[1], argv[2], argv[3]);
		return (0);
	}
	std::cerr << RED_FG
		<< "Incorrect arguments." << std::endl
		<< RESET << BOLD
		<< "Usage :" << RESET << std::endl
		<< argv[0] << " <filename> <string to find> <string to replace>"
		<< RESET << std::endl;
	return (22);
}
