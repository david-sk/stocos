///
/// @file message.h
/// @author Jxtopher
/// @brief
/// @version 0.1
/// @copyright CC-BY-NC-SA
/// @date 2020-10
///
///
#ifndef MESSAGES_H
#define MESSAGES_H

namespace stocos {

#include <iostream>
#include <string>
#include <unordered_map>

class Messages : protected std::unordered_map<std::string, std::string> {
  public:
	Messages() {
		this->operator[]("STOChastic Optimization Solver") = "STOChastic Optimization Solver";
	}

	virtual std::string operator()(const std::string code) const {
		return this->at(code);
	}
};

} // namespace stocos

#endif