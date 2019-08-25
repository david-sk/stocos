///
/// @file problem.h
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief description of the optimization problem
///


#ifndef PROBLEM_H
#define PROBLEM_H

#include "../solution/solution.h"


template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class Problem {
public:
	Problem() {

	}

	virtual ~Problem() {

	}
	
	// Loading an instance
    virtual Json::Value loadInstance(const std::string &file) const {
		if (access(file.c_str(), F_OK ) == -1) {
			throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " [-] the file does not exist : "+ file);
		}
        Json::Value root;  // will contains the root value after parsing.
        Json::Reader reader;
        std::ifstream test(file, std::ifstream::binary);
        bool parsingSuccessful = reader.parse(test, root, false);

        if (!parsingSuccessful)
            throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " " +reader.getFormattedErrorMessages());

        std::string encoding = root.get("encoding", "UTF-8").asString();
		return root;
    }

	virtual void loadJson(const Json::Value &config) = 0;
	
	// Generating a solution
	virtual void reset_solution(SOL &s) const {
		std::cerr<<"[-] Not implemented : reset_solution()"<<std::endl;
		exit(EXIT_FAILURE);
	}
	virtual std::unique_ptr<SOL> new_solution() const {
		std::cerr<<"[-] Not implemented : new_solution()"<<std::endl;
		exit(EXIT_FAILURE);
	}

	// Evaluation of the solution
	virtual void full_eval(SOL &s) = 0;
	/*virtual void incremental_eval(const SOL &s, const std::vector<std::pair<unsigned int, TYPE_CELL>> &_listOfMutations) const {
		std::cerr<<"[-] not implemented"<<std::endl;
		exit(EXIT_FAILURE);
	};*/
	virtual bool filtering(SOL &s) const {
		std::cerr<<"[-] Not implemented : getFitnessObjectif()"<<std::endl;
		exit(EXIT_FAILURE);
		return true;
	}
	virtual TYPE_FITNESS getFitnessObjectif() const {
		std::cerr<<"[-] Not implemented : getFitnessObjectif()"<<std::endl;
		exit(EXIT_FAILURE);
	}

	virtual TYPE_FITNESS getFitnessObjectif(unsigned int numObjectif) const {
		std::cerr<<"[-] Not implemented : getFitnessObjectif(unsigned int numObjectif)"<<std::endl;
		exit(EXIT_FAILURE);
	}
	
	
private:
	
};

#endif