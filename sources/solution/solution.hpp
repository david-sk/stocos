///
/// @file solution.hpp
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

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

#include <jsoncpp/json/json.h>

namespace stocos 
{

template <typename TYPE_FITNESS>
class Solution {
  public:
    Solution(const Solution& s) : _number_of_objective(s._number_of_objective) {
        BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":"<<__LINE__<<" Constructeur de copie Solution";
        assert(0 < _number_of_objective);
        _fitness = std::make_unique<TYPE_FITNESS[]>(_number_of_objective);
        _fitness_is_valid = std::make_unique<bool[]>(_number_of_objective);
            for(unsigned int i = 0; i < _number_of_objective; i++) {
                _fitness[i] = s._fitness[i];
                _fitness_is_valid[i] = s._fitness_is_valid[i];
            }
    }

    Solution() : _number_of_objective(1) {
        BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":"<<__LINE__<<" Creation Solution";
        _fitness = std::make_unique<TYPE_FITNESS[]>(_number_of_objective);
        _fitness_is_valid = std::make_unique<bool[]>(_number_of_objective);
        for(unsigned int i = 0; i < _number_of_objective; i++)
            _fitness_is_valid[i] = false;
    }

    Solution(const unsigned int number_of_objective) : _number_of_objective(number_of_objective) {
        BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":"<<__LINE__<<" Creation Solution";
        assert(0 < _number_of_objective);
        _fitness = std::make_unique<TYPE_FITNESS[]>(_number_of_objective);
        _fitness_is_valid = std::make_unique<bool[]>(_number_of_objective);
        for(unsigned int i = 0; i < _number_of_objective; i++)
            _fitness_is_valid[i] = false;
    }

    Solution(const Json::Value& jsonValue) : _number_of_objective(0), _fitness(nullptr), _fitness_is_valid(nullptr) {
        BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":"<<__LINE__<<" Creation Solution";
        loadJson(jsonValue);
    }

    Solution& operator=(const Solution& s) {
            if(_number_of_objective != s._number_of_objective) {
                _number_of_objective = s._number_of_objective;
                _fitness = std::unique_ptr<TYPE_FITNESS[]>(new TYPE_FITNESS[_number_of_objective]);
                _fitness_is_valid = std::unique_ptr<bool[]>(new bool[_number_of_objective]);
                for(unsigned int i = 0; i < _number_of_objective; i++)
                    _fitness_is_valid[i] = false;
        }

            for(unsigned int i = 0; i < _number_of_objective; i++) {
                _fitness[i] = s._fitness[i];
                _fitness_is_valid[i] = s._fitness_is_valid[i];
            }
        return *this;
    }

    ~Solution() {
        BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":"<<__LINE__<<" Delete Solution";
    }

    ///
    /// @brief Give for a numObjectif the state fitness
    ///
    /// @param numObjectif
    /// @return true if the fitness is valide
    /// @return false if the fitness is not valide
    ///
    bool fitnessIsValid(unsigned int numObjectif = 0) const {
        assert(numObjectif < _number_of_objective);
        return _fitness_is_valid[numObjectif];
    }

    void setFitness(unsigned int numObjectif, TYPE_FITNESS value) {
        assert(numObjectif < _number_of_objective);
        _fitness[numObjectif] = value;
        _fitness_is_valid[numObjectif] = true;
    }

    void setFitness(TYPE_FITNESS value) {
        unsigned int numObjectif = 0;
        assert(numObjectif < _number_of_objective);
        _fitness[numObjectif] = value;
        _fitness_is_valid[numObjectif] = true;
    }

    TYPE_FITNESS getFitness(unsigned int numObjectif = 0) const {
        assert(numObjectif < _number_of_objective);
        return _fitness[numObjectif];
    }

    unsigned int numberOfObjective() const {
        return _number_of_objective;
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
            throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " " +reader.getFormattedErrorMessages());
        loadJson(root);
    }

    void loadJson(const Json::Value& jsonValue) {
        _number_of_objective = jsonValue["fitness"].size();
            if(this->_fitness == nullptr) {
                this->_fitness = std::unique_ptr<TYPE_FITNESS[]>(new TYPE_FITNESS[this->_number_of_objective]);
                this->_fitness_is_valid = std::unique_ptr<bool[]>(new bool[this->_number_of_objective]);
            } else {
                this->_fitness.reset(static_cast<TYPE_FITNESS*>(realloc(
                    static_cast<void*>(this->_fitness.release()), this->_number_of_objective * sizeof(TYPE_FITNESS))));
                this->_fitness_is_valid.reset(static_cast<bool*>(realloc(
                    static_cast<void*>(this->_fitness_is_valid.release()), this->_number_of_objective * sizeof(bool))));
            }
            for(unsigned int i = 0; i < jsonValue["fitness"].size(); i++) {
                _fitness[i] = static_cast<TYPE_FITNESS>(jsonValue["fitness"][i].asDouble());
                _fitness_is_valid[i] = jsonValue["fitnessIsValid"][i].asBool();
            }
    }

    Json::Value asJson() const {
        Json::Value jsonValue;
            for(unsigned int i = 0; i < _number_of_objective; i++) {
                jsonValue["fitness"].append(_fitness[i]);
                jsonValue["fitnessIsValid"].append(_fitness_is_valid[i]);
            }
        return jsonValue;
    }

  protected:
    unsigned int _number_of_objective;            ///< number of objectif
    std::unique_ptr<TYPE_FITNESS[]> _fitness;     ///< list of fitness
    std::unique_ptr<bool[]> _fitness_is_valid;    ///< list of the fitness state
};

}
#endif