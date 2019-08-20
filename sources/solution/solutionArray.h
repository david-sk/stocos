///
/// @file solutionArray.h
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

#include <jsoncpp/json/json.h>

#include "solution.h"



template <typename TYPE_FITNESS, typename TYPE_CELL>
class SolutionArray : public Solution<TYPE_FITNESS> {
   public:
    SolutionArray() : 
		Solution<TYPE_FITNESS>(1), 
		_sizeArray(1) {
        DEBUG_TRACE("Creation SolutionArray");
        array = new TYPE_CELL[_sizeArray];
    }

    SolutionArray(const unsigned int sizeArray) : 
		Solution<TYPE_FITNESS>(1), 
		_sizeArray(sizeArray) {
        DEBUG_TRACE("Creation SolutionArray");
        array = new TYPE_CELL[sizeArray];
    }

    SolutionArray(const unsigned int numberOfObjective, const unsigned int sizeArray)
        : Solution<TYPE_FITNESS>(numberOfObjective), 
		_sizeArray(sizeArray) {
        DEBUG_TRACE("Creation SolutionArray");
        array = new TYPE_CELL[sizeArray];
    }

    SolutionArray(const SolutionArray &s) : 
		Solution<TYPE_FITNESS>(s), 
		_sizeArray(s._sizeArray) {
        array = new TYPE_CELL[_sizeArray];

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
        DEBUG_TRACE("Delete SolutionArray");
        delete[] array;
    }

    SolutionArray &operator=(const SolutionArray &s) {
        Solution<TYPE_FITNESS>::operator=(s);
        if (_sizeArray != s._sizeArray) {
            // this->~SolutionArray();
            _sizeArray = s._sizeArray;
            array = new TYPE_CELL[_sizeArray];
        }

        for (unsigned int i = 0; i < _sizeArray; i++) {
            array[i] = s.array[i];
        }

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
            for (unsigned int i = 0; i < this->_numberOfObjective; i++) this->_fitnessIsValid[i] = false;
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
        if (!parsingSuccessful) throw std::runtime_error(reader.getFormattedErrorMessages());
        loadJson(root);
    }

    void loadJson(const Json::Value &jsonValue) {
        Solution<TYPE_FITNESS>::loadJson(jsonValue);
        _sizeArray = jsonValue["solution"].size();
        if (array == nullptr)
            array = new TYPE_CELL[_sizeArray];
        else
            array = static_cast<TYPE_CELL *>(realloc(array, _sizeArray * sizeof(TYPE_CELL)));
        for (unsigned int i = 0; i < jsonValue["solution"].size(); i++) array[i] = jsonValue["solution"][i].asDouble();
    }

    Json::Value asJson() const {
        Json::Value jsonValue = Solution<TYPE_FITNESS>::asJson();
        for (unsigned int i = 0; i < _sizeArray; i++) 
            jsonValue["solution"].append(array[i]);
        return jsonValue;
    }

   private:
    TYPE_CELL *array;
    unsigned int _sizeArray;
};

#endif