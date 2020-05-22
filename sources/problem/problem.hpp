///
/// @file problem.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief description of the optimization problem
///

#ifndef PROBLEM_H
#define PROBLEM_H

#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <fstream>   // std::ifstream
#include <iostream>  // std::cout, std::endl
#include <sstream>   // std::stringstream
#include <stdexcept> // std::runtime_error
#include <utility>   // std::pair
#include <vector>	// std::vector

#include "../solution/population.hpp"
#include "../solution/solution.hpp"

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL> class Problem {
  public:
	Problem() {}

	virtual ~Problem() {}

	///
	/// @brief give an instance from the json file in Json format
	///
	/// @param file 		path of the json file
	/// @return Json::Value give aconfiguration of the problem in Json format
	///
	virtual Json::Value loadInstance(const std::string& pathfile) const {
		if(!std::ifstream(pathfile.c_str()).good()) {
			throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
									 " [-] the file does not exist : " + pathfile);
		}

		Json::Value root; // will contains the root value after parsing.
		Json::Reader reader;
		bool parsingSuccessful;

		std::ifstream file(pathfile.c_str(), std::ios_base::binary);
		if(file.is_open()) {
			char buffer[2];
			unsigned char magic_number_gzip[2] = {0x1F, 0x8B};
			file.read(buffer, 2);
			file.seekg(0);
			if(static_cast<unsigned char>(buffer[0]) == magic_number_gzip[0] &&
			   static_cast<unsigned char>(buffer[1]) == magic_number_gzip[1]) { // gzip
				boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
				in.push(boost::iostreams::gzip_decompressor());
				in.push(file);
				std::stringstream dst;
				boost::iostreams::filtering_streambuf<boost::iostreams::output> out(dst);
				boost::iostreams::copy(in, out);
				parsingSuccessful = reader.parse(dst.str(), root);
			} else // json file
				parsingSuccessful = reader.parse(file, root, false);
		} else
			throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
									 " [-] Error opening file : " + pathfile);

		if(!parsingSuccessful)
			throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
									 " " + reader.getFormattedErrorMessages());

		std::string encoding = root.get("encoding", "UTF-8").asString();
		return root;
	}

	///
	/// @brief Load the configuration in the instance problem
	///
	/// @param config file of the configuration in Json format
	///
	virtual void loadJson(const Json::Value& config) = 0;

	///
	/// @brief
	///
	/// @param s
	///
	virtual void resetSolution(SOL& s) const {
		throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
								 "[-] Not implemented : resetSolution(SOL &s)");
	}

	///
	/// @brief Generating a solution
	///
	/// @return std::unique_ptr<SOL> the solution
	///
	virtual std::unique_ptr<SOL> new_solution() const {
		throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
								 "[-] Not implemented : new_solution(SOL &s)");
	}

	///
	/// @brief Check the solution structure : array size and the number of the objectif
	///
	/// @param s 		representation of the solution
	/// @return true 	if the solution structure is valid
	/// @return false 	if the solution structure is not valid
	///
	virtual bool checkSolutionStructure(const SOL& s) const {
		throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
								 "[-] Not implemented : new_solution(SOL &s)");
	}

	///
	/// @brief Evaluation of the solution
	///
	/// @param s solution with the update fitness
	///
	virtual void evaluation(SOL& s) = 0;

	///
	/// @brief Evaluation incremetal of the solution
	///
	/// @param s
	/// @param _listOfMutations
	///
	virtual void evaluationIncremental(
		const SOL& s,
		const std::vector<std::pair<unsigned int, TYPE_CELL>>& _listOfMutations) const {
		throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
								 "[-] Not implemented : evaluationIncremental(...)");
	}

	///
	/// @brief Evaluation d'une sous-solution
	///
	/// @param s
	/// @return true 	si une sous-solution valid
	/// @return false 	si une sous-solution **non** valid
	///
	virtual bool evaluationSubSolution(SOL& s) const {
		throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
								 "[-] Not implemented : evaluationSubSolution(SOL &s)");
	}

	///
	/// @brief Get the Fitness Objectif object
	///
	/// @param numObjectif
	/// @return TYPE_FITNESS
	///
	virtual TYPE_FITNESS getFitnessObjectif(unsigned int numObjectif = 0) const {
		throw std::runtime_error(
			std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
			"[-] Not implemented : getFitnessObjectif(unsigned int numObjectif)");
	}

	///-------------

	virtual bool solutionSelection(const SOL& s_worst, const SOL& s_best) {
		throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
								 "[-] Not implemented : solutionSelection(...)");
	}

	virtual unsigned int solutionSelection(const Population<SOL>& p) {
		throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
								 "[-] Not implemented : solutionSelection(...)");
	}
};

} // namespace stocos

#endif