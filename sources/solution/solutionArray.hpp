///
/// @file solutionArray.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef SOLUTIONARRAY_H
#define SOLUTIONARRAY_H

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

#include <jsoncpp/json/json.h>

#include "solution.hpp"

namespace stocos 
{

template <typename TYPE_FITNESS, typename TYPE_CELL>
class SolutionArray : public Solution<TYPE_FITNESS> {
   public:
    SolutionArray() : 
		Solution<TYPE_FITNESS>(1), 
		_sizeArray(1) {
        BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":"<<__LINE__<<" Creation SolutionArray";
        array = std::make_unique<TYPE_CELL[]>(_sizeArray);
    }

    SolutionArray(const unsigned int sizeArray) : 
		Solution<TYPE_FITNESS>(1), 
		_sizeArray(sizeArray) {
        BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":"<<__LINE__<<" Creation SolutionArray";
        array = std::make_unique<TYPE_CELL[]>(_sizeArray);
    }

    SolutionArray(const unsigned int numberOfObjective, const unsigned int sizeArray)
        : Solution<TYPE_FITNESS>(numberOfObjective), 
		_sizeArray(sizeArray) {
        BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":"<<__LINE__<<" Creation SolutionArray";
        array = std::make_unique<TYPE_CELL[]>(_sizeArray);
    }

    SolutionArray(const SolutionArray &s) : 
		Solution<TYPE_FITNESS>(s), 
		_sizeArray(s._sizeArray) {
        BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":"<<__LINE__<<" Creation SolutionArray";
        array = std::make_unique<TYPE_CELL[]>(_sizeArray);

        for (unsigned int i = 0; i < _sizeArray; i++) {
            array[i] = s.array[i];
        }
    }

    SolutionArray(const Json::Value &jsonValue) : 
		Solution<TYPE_FITNESS>(jsonValue), 
		array(nullptr),
		_sizeArray(0) {
        loadJson(jsonValue);
    }

    SolutionArray(const std::string &solution) :
        Solution<TYPE_FITNESS>(),
		array(nullptr),
		_sizeArray(0) {
			loadJson(solution);
    }

    ~SolutionArray() {
        BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":"<<__LINE__<<" Delete SolutionArray";
    }

    SolutionArray &operator=(const SolutionArray &s) {
        Solution<TYPE_FITNESS>::operator=(s);
        if (_sizeArray != s._sizeArray) {
            _sizeArray = s._sizeArray;
            array = std::make_unique<TYPE_CELL[]>(_sizeArray);
        }

        for (unsigned int i = 0; i < _sizeArray; i++)
            array[i] = s.array[i];

        return *this;
    }

    bool operator==(const SolutionArray &s) const {
        if (sizeArray() != s.sizeArray())
            return false;
        else {
            for (unsigned int i = 0; i < s.sizeArray(); i++) {
                if (array[i] != s(i)) return false;
            }
        }
        return true;
    }

    void operator()(const unsigned int index, const TYPE_CELL value) {
        assert(index < _sizeArray);
        if (array[index] != value) {
            for (unsigned int i = 0; i < this->_number_of_objective; i++) this->_fitness_is_valid[i] = false;
            array[index] = value;
        }
    }

    TYPE_CELL operator()(const unsigned int index) const {
        assert(index < _sizeArray);
        return array[index];
    }

    unsigned int sizeArray() const { return _sizeArray; }

    // --------------------------------------------------------------------
    friend std::ostream &operator<<(std::ostream &out, SolutionArray<TYPE_FITNESS, TYPE_CELL> const &s) {
        for (unsigned int i = 0; i < s.numberOfObjective(); i++) out << s.getFitness(i) << " ";
        out << ": ";
        for (unsigned int i = 0; i < s.sizeArray(); i++) out << s(i) << " ";
        return out;
    }

    void loadJson(const std::string &strJson) {
        Json::Value root;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(strJson.c_str(), root);  // parse process
        if (!parsingSuccessful) throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " " +reader.getFormattedErrorMessages());
        loadJson(root);
    }

    void loadJson(const Json::Value &jsonValue) {
        Solution<TYPE_FITNESS>::loadJson(jsonValue);
        _sizeArray = jsonValue["solution"].size();
        if (array == nullptr)
            array = std::make_unique<TYPE_CELL[]>(_sizeArray);
        else
            this->array.reset(static_cast<TYPE_CELL*>(realloc(static_cast<void*>(this->array.release()), this->_sizeArray * sizeof(TYPE_CELL))));
        for (unsigned int i = 0; i < jsonValue["solution"].size(); i++) array[i] = jsonValue["solution"][i].asDouble();
    }

    Json::Value asJson() const {
        Json::Value jsonValue = Solution<TYPE_FITNESS>::asJson();
        for (unsigned int i = 0; i < _sizeArray; i++) 
            jsonValue["solution"].append(array[i]);
        return jsonValue;
    }

   private:
    std::unique_ptr<TYPE_CELL[]> array;
    unsigned int _sizeArray;
};

}
#endif