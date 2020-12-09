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

#include <cstdarg>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

class Messages : protected std::unordered_map<std::string, std::string> {
  public:
    Messages() {
        this->operator[]("STOChastic Optimization Solver") = "STOChastic Optimization Solver";
        this->operator[]("TEST") = "[$1] This i$s the test $0 name $1.";
    }

    virtual std::string operator()(const std::string code) const {
        return this->at(code);
    }

    // Replace $[0-9]+ with a arg
    virtual std::string operator()(const std::string code,
                                   const std::initializer_list<std::string>& args) const {
        std::map<unsigned int, unsigned int> refactoring;
        std::string ret;
        unsigned int j = 0;
        for(unsigned int i = 0; i < this->at(code).size(); i++) {
            if(this->at(code)[i] == '$') {
                std::stringstream ss_num_arg;
                do {
                    j = 0;
                    i++;
                    while(j < 10 && this->at(code)[i] != numeric[j]) j++;
                    if(this->at(code)[i] == numeric[j]) ss_num_arg << numeric[j];
                } while(this->at(code)[i] == numeric[j]);
                if(!ss_num_arg.str().empty()) {
                    unsigned int num_arg;
                    ss_num_arg >> num_arg;
                    refactoring[ret.size()] = num_arg;
                } else
                    i--;
            }
            ret += this->at(code)[i];
        }

        unsigned int shift = 0;
        for(std::map<unsigned int, unsigned int>::const_iterator it = refactoring.begin();
            it != refactoring.end(); ++it) {
            auto vi = args.begin();
            std::advance(vi, it->second);
            ret.insert(it->first + shift, *vi);
            shift += vi->size();
        }
        return ret;
    }

  private:
    const unsigned char numeric[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
};

} // namespace stocos

#endif
