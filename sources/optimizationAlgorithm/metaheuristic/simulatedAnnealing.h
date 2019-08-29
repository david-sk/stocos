///
/// @file simulatedAnnealing.h
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief 
///

#ifndef SIMULATEDANNELING_H
#define SIMULATEDANNELING_H


template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class SimulatedAnnealing : public OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> {
    public:
    SimulatedAnnealing(std::mt19937 &mt_rand, 
        std::shared_ptr<Statistic<SOL>> statistic,
        std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
        std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
        std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> atomicOperations) : 
        OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, std::move(statistic), std::move(stoppingCriteria), problem),
        _atomicOperations(std::move(atomicOperations)) {
        BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":"<<__LINE__<<" Creation SimulatedAnnealing";
    }
    virtual ~SimulatedAnnealing() {
        
    }

    std::unique_ptr<SOL> operator()(const SOL &s) {
        solution_star = s;
        // if (!solution_star.fitnessIsValid()) {
        //     this->_problem.full_eval(solution_star);
        // }

        return std::move(std::make_unique<SOL>(solution_star));
    }



    std::string className() const {
        if (_class_name.empty())
            return "SimulatedAnnealing";
        else 
            return _class_name;
    }

    void className(const std::string &class_name) {
        _class_name = class_name;
    }

    protected:
    std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> _atomicOperations;
    std::string _class_name;

    SOL solution_star;
};

#endif