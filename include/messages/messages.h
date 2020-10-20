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
#include <map>
#include <vector>
#include <sstream>
#include <cstdarg>

class Messages : protected std::unordered_map<std::string, std::string> {
  public:
	Messages() {
		this->operator[]("STOChastic Optimization Solver") = "STOChastic Optimization Solver";
		this->operator[]("TEST") = "[$1] This is the test $0 name $1.";
	}

	virtual std::string operator()(const std::string code) const {
		return this->at(code);
	}

	virtual std::string operator()(const std::string code, const std::initializer_list<std::string> &args) const {
		std::map<unsigned int, unsigned int> refactoring;
		std::string s;
		unsigned int j = 0;
		for (unsigned int i = 0 ; i < this->at(code).size() ; i++) {
			if (this->at(code)[i] == '$') {
				std::stringstream ss_num_arg;
				do {
					j=0;
					i++;
					while (j < 10 && this->at(code)[i] != numeric[j]) j++;
					if (this->at(code)[i] == numeric[j]) ss_num_arg<<numeric[j];
				} while (this->at(code)[i] == numeric[j]);
				unsigned int num_arg;
				ss_num_arg>>num_arg;
				refactoring[s.size()] = num_arg;
			}
			s += this->at(code)[i];
		}

		unsigned int shift = 0;
		for (std::map<unsigned int, unsigned int>::const_iterator it = refactoring.begin(); it != refactoring.end(); ++it) {
			auto vi = args.begin();
			std::advance(vi, it->second);
			s.insert(it->first + shift, *vi);
			shift+= vi->size();
		}

		std::cout<<">"<<s<<"<"<<std::endl;
		return s;
	}

  private:
	const unsigned char numeric[10] = {'0','1','2','3','4','5','6','7','8','9'};
};

} // namespace stocos

#endif