/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Input.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:32:17 by conobi            #+#    #+#             */
/*   Updated: 2023/03/21 16:30:01 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Input.hpp"

vector<string> splitByToken(string input, const string &delimiter) {
	size_t pos = 0;
	string token;
	vector<string> res;

	while ((pos = input.find(delimiter)) != string::npos) {
		token = input.substr(0, pos);
		res.push_back(token);
		input = input.substr(pos + delimiter.length());
	}
	res.push_back(input);
	return res;
}

enum DecoderState { PREFIX, COMMAND, PARAMETER };

Input::Input(const string &input) {
	// todo: Build the input here, and check for errors

	string result = input;
	size_t pos = result.find("\r\n");
	if (pos != std::string::npos) {
		result.erase(pos, 2);
	}

	string::size_type trail = result.find(" :");
	bool hasTrail = trail != string::npos;
	vector<string> inputSplit = splitByToken(result, " ");
	string afterTrail;

	if (hasTrail) {
		string beforeTrail = result.substr(0, trail);
		afterTrail = result.substr(trail + 2);
		inputSplit = splitByToken(beforeTrail, " ");
	} else {
		inputSplit = splitByToken(result, " ");
	}

	bool first = true;
	DecoderState state = PREFIX;
	string prefix;

	for (size_t i = 0; i < inputSplit.size(); i++) {
		switch (state) {
			case PREFIX:
			case COMMAND: {
				bool isPrefix = inputSplit[i][0] == ':';
				if (isPrefix && first) {
					if (inputSplit[i].size() < 2) {
						// todo: view if we need to throw an error
					}
					state = COMMAND;
					prefix = inputSplit[i].substr(1);
					first = false;
				} else {
					this->_command = inputSplit[i];
					state = PARAMETER;
				}
				break;
			}
			case PARAMETER: {
				this->_parameters.push_back(inputSplit[i]);
				break;
			}
		}
	}
	if (!afterTrail.empty()) {
		this->_parameters.push_back(afterTrail);
	}
}

Input::~Input() {
}
