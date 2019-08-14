///
/// \file evolutionaryAlgorithm.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2019-06
/// \brief 
///
 

#ifndef EVOLUTIONARYALGORITHM_H
#define EVOLUTIONARYALGORITHM_H

#include <random>

#include "../../solution/population.h"
#include "operator/atomicOperation.h"
#include "../optimizationAlgorithm.h"
#include "../../problem/problem.h"
#include "selection/selection.h"

using namespace std;

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class EvolutionaryAlgorithm : public OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> {
    public:
    EvolutionaryAlgorithm(std::mt19937 &mt_rand, 
    std::unique_ptr<Statistic<SOL>> statistic,
    std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
    shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
    std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> atomicOperations,
    std::unique_ptr<Selection<SOL>> selection,
    unsigned int mu = 50,
    unsigned int lambda = 50) : 
    OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, move(statistic), move(stoppingCriteria), problem),
    _atomicOperations(move(atomicOperations)),
    _selection(move(selection)),
    _mu(mu),
    _lambda(lambda) {
        DEBUG_TRACE("Creation EvolutionaryAlgorithm");
        rid = make_unique<uniform_int_distribution<unsigned int>>(0, _mu-1);
    }

    ~EvolutionaryAlgorithm() {
    }
    
    std::unique_ptr<SOL> operator()(const SOL &s) {
        solution_star = s;

        if (!solution_star.fitnessIsValid()) {
            this->_problem->full_eval(solution_star);
        }

        // Initialisation de la population à partir d'une solution
        for (SOL &p : parents)
            p = solution_star;
        
        while (parents.size() < _mu)
            parents.push_back(solution_star);

        for (SOL &p : parents)
            _atomicOperations->operator()(p);
        
        // Evaluation des parents
        for (SOL &p : parents)
            this->_problem->full_eval(p);
        
        while (offsprings.size() < _lambda)
            offsprings.push_back(solution_star);
        
        // 
        while (this->_stoppingCriteria->operator()(solution_star)) {
            this->_statistic->operator()(solution_star);

            // selection de deux parents aléatoire et différent pour construire la population enfants
            for (auto it=offsprings.begin(); it != offsprings.end(); ++it) {
                unsigned int e1 = rid->operator()(this->_mt_rand);
                unsigned int e2 = rid->operator()(this->_mt_rand);

                while (e1 == e2) 
                    e2 = rid->operator()(this->_mt_rand);
                
                if (_selection->operator()(parents[e1], parents[e2]))
                    *it = parents[e1];
                else 
                    *it = parents[e2];
            }
            
            // Mutation des enfants et construction la population parents.
            for (SOL &o : offsprings)
                _atomicOperations->operator()(o);
            
            // Remplacement
            for (unsigned int i = 0 ; i < _mu ; i++) {
                parents[i] = offsprings[i];
            }
            
            // Evaluation des parents
            for (SOL &p : parents)
                this->_problem->full_eval(p);

            // Find best
            for (SOL &p : parents) {
                if (_selection->operator()(p, solution_star))
                    solution_star = p;
            }
        }

        this->_statistic->operator()(solution_star);

        return move(make_unique<SOL>(solution_star));
    }


    string className() const {
        return "EvolutionaryAlgorithm";
    }
    
    protected:
        std::unique_ptr<uniform_int_distribution<unsigned int>> rid;
        std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> _atomicOperations;
        std::unique_ptr<Selection<SOL>> _selection;
        SOL solution_star;
        Population<SOL> parents;
        Population<SOL> offsprings;
        unsigned int _mu;
        unsigned int _lambda;
};

#endif

