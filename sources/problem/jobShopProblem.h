///
/// @file jobShopProblem.h
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief https://developers.google.com/optimization/scheduling/job_shop
///

#ifndef EVALJOBSHOPPROBLEM_H
#define EVALJOBSHOPPROBLEM_H

#include <jsoncpp/json/json.h>
#include <fstream>
#include <map>
#include <utility>

#include "../solution/solutionArray.h"
#include "problem.h"

using TYPE_FITNESS_JOBSHOPPROBLEM = double;
using TYPE_CELL_JOBSHOPPROBLEM = bool;
using SOL_JOBSHOPPROBLEM = SolutionArray<TYPE_FITNESS_JOBSHOPPROBLEM, TYPE_CELL_JOBSHOPPROBLEM>;
class JobShopProblem : public Problem<SOL_JOBSHOPPROBLEM, TYPE_FITNESS_JOBSHOPPROBLEM, TYPE_CELL_JOBSHOPPROBLEM> {
   public:
    JobShopProblem(std::string pathfile_instance) { loadInstance(pathfile_instance); }

    ~JobShopProblem() {}

    virtual void loadInstance(const Json::Value &config) {
        // std::cout<<root<<std::endl;
        // for (auto name : root["problem"].getMemberNames()) {
        //     std::cout<<name<<std::endl;
        // }

        // _N = root["problem"]["N"].asUInt();
    }

    friend std::ostream &operator<<(std::ostream &out, const JobShopProblem &e) {
        std::cout << "job X : (machine_id, processing_time)";
        std::vector<std::vector<std::pair<unsigned int, unsigned int>>> const _instance = e.getInstance();
        for (unsigned int i = 0; i < _instance.size(); i++) {
            out << std::endl << "job " << i << ":" << std::endl;
            for (unsigned int j = 0; j < _instance[i].size(); j++) {
                out << "(" << _instance[i][j].first << ", " << _instance[i][j].second << "), ";
            }
        }
        return out;
    }

    const std::vector<std::vector<std::pair<unsigned int, unsigned int>>> &getInstance() const { return instance; }

    void full_eval(SOL_JOBSHOPPROBLEM &s) {}

    /*void incremental(SolutionArray const &s, unsigned int mutatedCell) const {

    }*/

    void reset_solution(SOL_JOBSHOPPROBLEM &s) const {}

   private:
    std::vector<std::vector<std::pair<unsigned int, unsigned int>>> instance;
};

#endif