///
/// @file solution.h
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief Definition of the number of goals, fitness, and fitnessIsValid
///

#ifndef SOLUTION_H
#define SOLUTION_H

#include <cassert>
#include <cstdio>
#include <cstring>
#include <memory>
#include <string>

#include <jsoncpp/json/json.h>

#include "../macro.h"



template <typename TYPE_FITNESS>
class Solution {
  public:
    Solution(const Solution& s) : _numberOfObjective(s._numberOfObjective) {
        DEBUG_TRACE("Constructeur de copie Solution");
        assert(0 < _numberOfObjective);
        _fitness = std::make_unique<TYPE_FITNESS[]>(_numberOfObjective);
        _fitnessIsValid = std::make_unique<bool[]>(_numberOfObjective);
            for(unsigned int i = 0; i < _numberOfObjective; i++) {
                _fitness[i] = s._fitness[i];
                _fitnessIsValid[i] = s._fitnessIsValid[i];
            }
    }

    Solution() : _numberOfObjective(1) {
        DEBUG_TRACE("Creation Solution");
        _fitness = std::make_unique<TYPE_FITNESS[]>(_numberOfObjective);
        _fitnessIsValid = std::make_unique<bool[]>(_numberOfObjective);
        for(unsigned int i = 0; i < _numberOfObjective; i++)
            _fitnessIsValid[i] = false;
    }

    Solution(const unsigned int numberOfObjective) : _numberOfObjective(numberOfObjective) {
        DEBUG_TRACE("Creation Solution");
        assert(0 < _numberOfObjective);
        _fitness = std::make_unique<TYPE_FITNESS[]>(_numberOfObjective);
        _fitnessIsValid = std::make_unique<bool[]>(_numberOfObjective);
        for(unsigned int i = 0; i < _numberOfObjective; i++)
            _fitnessIsValid[i] = false;
    }

    Solution(const Json::Value& jsonValue) : _numberOfObjective(0), _fitness(nullptr), _fitnessIsValid(nullptr) {
        DEBUG_TRACE("Creation Solution");
        loadJson(jsonValue);
    }

    Solution& operator=(const Solution& s) {
            if(_numberOfObjective != s._numberOfObjective) {
                _numberOfObjective = s._numberOfObjective;
                _fitness = std::unique_ptr<TYPE_FITNESS[]>(new TYPE_FITNESS[_numberOfObjective]);
                _fitnessIsValid = std::unique_ptr<bool[]>(new bool[_numberOfObjective]);
                for(unsigned int i = 0; i < _numberOfObjective; i++)
                    _fitnessIsValid[i] = false;
        }

            for(unsigned int i = 0; i < _numberOfObjective; i++) {
                _fitness[i] = s._fitness[i];
                _fitnessIsValid[i] = s._fitnessIsValid[i];
            }
        return *this;
    }

    ~Solution() {
        DEBUG_TRACE("Delete Solution");
        // delete [] _fitness;
        // delete [] _fitnessIsValid;
    }

    ///
    /// @brief Give for a numObjectif the state fitness
    ///
    /// @param numObjectif
    /// @return true if the fitness is valide
    /// @return false if the fitness is not valide
    ///
    bool fitnessIsValid(unsigned int numObjectif) const {
        assert(numObjectif < _numberOfObjective);
        return _fitnessIsValid[numObjectif];
    }

    bool fitnessIsValid() const {
        unsigned int numObjectif = 0;
        assert(numObjectif < _numberOfObjective);
        return _fitnessIsValid[numObjectif];
    }

    void setFitness(unsigned int numObjectif, TYPE_FITNESS value) {
        assert(numObjectif < _numberOfObjective);
        _fitness[numObjectif] = value;
        _fitnessIsValid[numObjectif] = true;
    }

    void setFitness(TYPE_FITNESS value) {
        unsigned int numObjectif = 0;
        assert(numObjectif < _numberOfObjective);
        _fitness[numObjectif] = value;
        _fitnessIsValid[numObjectif] = true;
    }

    TYPE_FITNESS getFitness() const {
        unsigned int numObjectif = 0;
        assert(numObjectif < _numberOfObjective);
        return _fitness[numObjectif];
    }

    TYPE_FITNESS getFitness(unsigned int numObjectif) const {
        assert(numObjectif < _numberOfObjective);
        return _fitness[numObjectif];
    }

    unsigned int numberOfObjective() const {
        return _numberOfObjective;
    }

    // --------------------------------------------------------------------
    friend std::ostream& operator<<(std::ostream& out, const Solution<TYPE_FITNESS>& s) {
        for(unsigned int i = 0; i < s.numberOfObjective(); i++)
            out << s.getFitness(i);
        return out;
    }

    void loadJson(const std::string& strJson) {
        Json::Value root;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(strJson.c_str(), root); // parse process
        if(!parsingSuccessful)
            throw std::runtime_error(reader.getFormattedErrorMessages());
        loadJson(root);
    }

    void loadJson(const Json::Value& jsonValue) {
        _numberOfObjective = jsonValue["fitness"].size();
            if(this->_fitness == nullptr) {
                this->_fitness = std::unique_ptr<TYPE_FITNESS[]>(new TYPE_FITNESS[this->_numberOfObjective]);
                this->_fitnessIsValid = std::unique_ptr<bool[]>(new bool[this->_numberOfObjective]);
            } else {
                this->_fitness.reset(static_cast<TYPE_FITNESS*>(realloc(
                    static_cast<void*>(this->_fitness.release()), this->_numberOfObjective * sizeof(TYPE_FITNESS))));
                this->_fitnessIsValid.reset(static_cast<bool*>(realloc(
                    static_cast<void*>(this->_fitnessIsValid.release()), this->_numberOfObjective * sizeof(bool))));
            }
            for(unsigned int i = 0; i < jsonValue["fitness"].size(); i++) {
                _fitness[i] = static_cast<TYPE_FITNESS>(jsonValue["fitness"][i].asDouble());
                _fitnessIsValid[i] = jsonValue["fitnessIsValid"][i].asBool();
            }
    }

    Json::Value asJson() const {
        Json::Value jsonValue;
            for(unsigned int i = 0; i < _numberOfObjective; i++) {
                jsonValue["fitness"].append(_fitness[i]);
                jsonValue["fitnessIsValid"].append(_fitnessIsValid[i]);
            }
        return jsonValue;
    }

  protected:
    unsigned int _numberOfObjective; ///< number of objectif
    std::unique_ptr<TYPE_FITNESS[]> _fitness; ///< list of fitness
    std::unique_ptr<bool[]> _fitnessIsValid; ///< list of the fitness state
};

#endif