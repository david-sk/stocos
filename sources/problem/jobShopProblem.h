///
/// \file evalJobShopProblem.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief https://developers.google.com/optimization/scheduling/job_shop
///

#ifndef EVALJOBSHOPPROBLEM_H
#define EVALJOBSHOPPROBLEM_H

#include <map>
#include <utility>

#include "../solution/solutionArray.h"
#include "problem.h"

template<class SOL>
class JobShopProblem : public Problem<SOL, bool> {
    public:
    
    JobShopProblem(string pathfile_instance) {
        loadInstance(pathfile_instance);
    }
    
    ~JobShopProblem() {

    }

    void loadInstance(string file) {
        using namespace rapidjson;

        // check if a file exist
        assert(access(file.c_str(), F_OK ) != -1);

        FILE* fp = fopen(file.c_str(), "rb");
        char readBuffer[65536];
        FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        Document d;
        d.ParseStream(is);
        Value& problem = d["problem"];
        Value& jobs = problem["jobs"];

        for (SizeType i = 0; i < jobs.Size(); i++) {
            //cerr<<jobs[i].GetString()<<endl;
            Value& job = problem[jobs[i].GetString()];
            instance.push_back(vector<pair<unsigned int, unsigned int>>());

            for (SizeType j = 0; j < job.Size(); j++) {
                Value& machine_id = job[j]["machine_id"];
                Value& processing_time = job[j]["processing_time"];

                instance[i].push_back(pair<unsigned int, unsigned int>(static_cast<unsigned int>(machine_id.GetInt()), static_cast<unsigned int>(processing_time.GetInt())));
            }
        }
        fclose(fp);
    }


    friend std::ostream & operator<< (std::ostream &out, const EvalJobShopProblem<SOL> &e) {
        cout<<"job X : (machine_id, processing_time)";
        vector<vector<pair<unsigned int, unsigned int>>> const _instance = e.getInstance();
        for(unsigned int i = 0 ; i < _instance.size() ; i++) {
            out<<endl<<"job "<<i<<":"<<endl;
            for(unsigned int j = 0 ; j < _instance[i].size() ; j++) {
                 out<<"("<<_instance[i][j].first<<", "<<_instance[i][j].second<<"), ";
            }
        }
        return out;
    }

    const vector<vector<pair<unsigned int, unsigned int>>> &getInstance() const {
        return instance;
    }

    void full_eval(SOL &s) const {
        
    }

    /*void incremental(SolutionArray const &s, unsigned int mutatedCell) const {

    }*/

    void reset_solution(SOL &s) const {
        
    }

    private:
        vector<vector<pair<unsigned int, unsigned int>>> instance;
};

#endif