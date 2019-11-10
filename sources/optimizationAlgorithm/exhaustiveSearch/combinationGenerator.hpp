///
/// @file combinationGenerator.hpp
/// @author Jxtopher
/// @version 1
/// @date 2019
/// @brief https://fr.wikipedia.org/wiki/Recherche_exhaustive
///

#ifndef COMBINATIONGENERATOR_H
#define COMBINATIONGENERATOR_H

#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "../../solution/population.hpp"
#include "../../solution/solutionArray.hpp"
#include "../optimizationAlgorithm.hpp"
#include "../../problem/problem.hpp"

namespace stocos 
{

template <typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class CombinationGenerator : public OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> {
   public:
    CombinationGenerator(std::mt19937 &mt_rand, 
                        std::shared_ptr<Statistic<SOL>> statistic, 
						std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
                        std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem)
        				: OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, std::move(statistic), std::move(stoppingCriteria), problem) {
                        nbCall = 0;
    }

    virtual ~CombinationGenerator() {}

    void reset() {
        for (unsigned int j = 0; j < _len_string; j++) _string[j] = 0;

        x = false;
        i = 0;

        while (_string[i] == (_nbDigit - 1)) {
            i++;
            x = true;
        }
    }

    void step() {
        _string[i]++;

        if (x) {
            for (unsigned int j = 0; j < i; j++) _string[j] = 0;
            i = 0;
        }

        while (_string[i] == (_nbDigit - 1)) {
            i++;
            x = true;
        }
    }

    bool stop() { return i < (_len_string); }

    std::unique_ptr<SOL> operator()(const SOL &s) {
        if (s.domain == nullptr) throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " [-] domain == nullptr)");
        // initialization
        _nbDigit = s.domain->size_domain(0);
        _len_string = s.sizeArray();
        _string = std::unique_ptr<unsigned int[]>(new unsigned int[_len_string]);


        solution = std::make_unique<SOL>(s);        
        reset();

        // Convert
        for(unsigned int i = 0 ; i < _len_string  ; i++) {
            solution->operator()(i, _string[i]);
        }

        // applay filtering
        this->_problem->evaluation(*solution);
        solution_star = std::make_unique<SOL>(*solution);
        if (this->_problem->solutionSelection(*solution, *solution_star)) {
            solution_star.reset(new SOL(*solution));
            std::cout<<*solution_star<<std::endl;
        }
        
        do {
            step();
            
            //Convert
            for(unsigned int i = 0 ; i < _len_string  ; i++) {
                solution->operator()(i, _string[i]);
            }
            
            // applay filtering
            this->_problem->evaluation(*solution);
            if (this->_problem->solutionSelection(*solution, *solution_star)) {
                solution_star.reset(new SOL(*solution));
                std::cout<<*solution_star<<std::endl;
            }

        } while (stop());

        return std::move(solution_star);
    }

    std::string className() const {
        if (_class_name.empty())
            return "CombinationGenerator";
        else 
            return _class_name;
    }

    void className(const std::string &class_name) {
        _class_name = class_name;
    }

   private:
    unsigned int _nbDigit;
    unsigned int _len_string;
    std::string _class_name;

    unsigned int nbCall;
    std::unique_ptr<unsigned int[]> _string;
    std::unique_ptr<SOL> solution;
    std::unique_ptr<SOL> solution_star;

    bool x;
    unsigned int i;
};

}
#endif