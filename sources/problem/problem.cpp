///
/// @file problem.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief description of the optimization problem
///
#include <problem/problem.h>

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
Problem<SOL,TYPE_FITNESS,TYPE_CELL>::Problem() {
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
Problem<SOL,TYPE_FITNESS,TYPE_CELL>::~Problem() {
}

///
/// @brief give an instance from the json file in Json format
///
/// @param file 		path of the json file
/// @return Json::Value give aconfiguration of the problem in Json format
///
template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
Json::Value Problem<SOL,TYPE_FITNESS,TYPE_CELL>::loadInstance(const std::string& pathfile) const {
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

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
void Problem<SOL,TYPE_FITNESS,TYPE_CELL>::resetSolution(SOL& s) const {
	throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
								"[-] Not implemented : resetSolution(SOL &s)");
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
std::unique_ptr<SOL> Problem<SOL,TYPE_FITNESS,TYPE_CELL>::new_solution() const {
	throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
								"[-] Not implemented : new_solution(SOL &s)");
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
bool Problem<SOL,TYPE_FITNESS,TYPE_CELL>::checkSolutionStructure(const SOL& s) const {
	throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
								"[-] Not implemented : new_solution(SOL &s)");
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
void Problem<SOL,TYPE_FITNESS,TYPE_CELL>::evaluation(SOL& s) = 0;

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
void Problem<SOL,TYPE_FITNESS,TYPE_CELL>::evaluationIncremental(
	const SOL& s,
	const std::vector<std::pair<unsigned int, TYPE_CELL>>& _listOfMutations) const {
	throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
								"[-] Not implemented : evaluationIncremental(...)");
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
bool Problem<SOL,TYPE_FITNESS,TYPE_CELL>::evaluationSubSolution(SOL& s) const {
	throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
								"[-] Not implemented : evaluationSubSolution(SOL &s)");
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
TYPE_FITNESS Problem<SOL,TYPE_FITNESS,TYPE_CELL>::getFitnessObjectif(unsigned int numObjectif) const {
	throw std::runtime_error(
		std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
		"[-] Not implemented : getFitnessObjectif(unsigned int numObjectif)");
}

///-------------
template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
bool Problem<SOL,TYPE_FITNESS,TYPE_CELL>::solutionSelection(const SOL& s_worst, const SOL& s_best) {
	throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
								"[-] Not implemented : solutionSelection(...)");
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
unsigned int Problem<SOL,TYPE_FITNESS,TYPE_CELL>::solutionSelection(const Population<SOL>& p) {
	throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
								"[-] Not implemented : solutionSelection(...)");
}

} // namespace stocos