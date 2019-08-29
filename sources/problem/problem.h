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

#include <iostream>
#include <utility>
#include <stdexcept>

#include "../solution/solution.h"
#include "../solution/population.h"


template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class Problem {
public:
	Problem() {

	}

	virtual ~Problem() {

	}
	
	/// 
	/// @brief give an instance from the json file in Json format
	/// 
	/// @param file 		path of the json file
	/// @return Json::Value give aconfiguration of the problem in Json format
	///
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

	/// 
	/// @brief Load the configuration in the instance problem
	/// 
	/// @param config file of the configuration in Json format
	///
	virtual void loadJson(const Json::Value &config) = 0;
	
	/// 
	/// @brief 
	/// 
	/// @param s 
	///
	virtual void reset_solution(SOL &s) const {
		throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + "[-] Not implemented : reset_solution(SOL &s)");
	}

	/// 
	/// @brief Generating a solution
	/// 
	/// @return std::unique_ptr<SOL> the solution
	///
	virtual std::unique_ptr<SOL> new_solution() const {
		throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + "[-] Not implemented : new_solution(SOL &s)");
	}

	/// 
	/// @brief Check the solution structure : array size and the number of the objectif
	/// 
	/// @param s 		representation of the solution
	/// @return true 	if the solution structure is valid
	/// @return false 	if the solution structure is not valid
	///
	virtual bool check_solution(const SOL &s) const {
		throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + "[-] Not implemented : new_solution(SOL &s)");
	}

	

	/// 
	/// @brief Evaluation of the solution
	/// 
	/// @param s solution with the update fitness 
	///
	virtual void full_eval(SOL &s) = 0;
	
	virtual void incremental_eval(const SOL &s, const std::vector<std::pair<unsigned int, TYPE_CELL>> &_listOfMutations) const {
		throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + "[-] Not implemented : incremental_eval(...)");
	}
	

	/// 
	/// @brief Evaluation d'une sous-solution
	/// 
	/// @param s 
	/// @return true 	si une sous-solution valid
	/// @return false 	si une sous-solution **non** valid
	///
	virtual bool filtering(SOL &s) const {
		throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + "[-] Not implemented : filtering(SOL &s)");
	}

	/// 
	/// @brief Give the area of validity of the variables 
	/// 
	/// @param index 
	/// @return std::pair<TYPE_CELL, TYPE_CELL> <upper bound, low bound>
	///
	virtual std::pair<TYPE_CELL, TYPE_CELL> domain(unsigned index) const {
		throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + "[-] Not implemented : domain()");
	}

	/// 
	/// @brief Get the Fitness Objectif object
	/// 
	/// @param numObjectif 
	/// @return TYPE_FITNESS 
	///
	virtual TYPE_FITNESS getFitnessObjectif(unsigned int numObjectif = 0) const {
		throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + "[-] Not implemented : getFitnessObjectif(unsigned int numObjectif)");
	}

	///-------------

	virtual bool solutionSelection(const SOL &s_worst, const SOL &s_best) {
		throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + "[-] Not implemented : solutionSelection(...)");
	}

	virtual unsigned int solutionSelection(const Population<SOL> &p) {
		throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + "[-] Not implemented : solutionSelection(...)");
	}
};

#endif