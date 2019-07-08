#ifndef LOADPARAMETER_H
#define	LOADPARAMETER_H

#include <memory.h>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/filereadstream.h>

#include "../../optimizationAlgorithm/metaheuristic/bestImprovement.h"
#include "../../optimizationAlgorithm/metaheuristic/firstImprovement.h"

template<typename SOL, typename TYPE_FITNESS,typename TYPE_CELL>
class LoadingSolverParameters {
public:
    LoadingSolverParameters(string file) {
        loadParameter(file);
        id_optimizaionAlgorithm["BestImprovement"] = 0;
        //unique_ptr<StoppingCriteria<SOL,TYPE_FITNESS>> stoppingCriteria = Create_StoppingCriteria();

        //FirstImprovement<SOL, TYPE_FITNESS, TYPE_CELL>(this->_mt_rand, *statistic, *stoppingCriteria, _problem, *mutation_FlipBit_1, *selection)));
    }

    virtual ~LoadingSolverParameters() {

    }

    void loadParameter(string file) {
            using namespace rapidjson;

            // check if a file exist
            assert(access(file.c_str(), F_OK ) != -1);

            FILE* fp = fopen(file.c_str(), "rb");
            char readBuffer[65536];
            FileReadStream is(fp, readBuffer, sizeof(readBuffer));
            Document d;
            d.ParseStream(is);


            for (Value::ConstMemberIterator itr = d.MemberBegin() ; itr != d.MemberEnd(); ++itr) {
                //printf("Type of member %s is %s\n",
                //itr->name.GetString(), kTypeNames[itr->value.GetType()]);                
                switch(id_optimizaionAlgorithm[itr->name.GetString()]) {
                    case 0: // id_optimizaionAlgorithm["BestImprovement"]
                        cout<<"BestImprovement"<<endl;
                        break;
                    default:
                        break;
                }

            }
            fclose(fp);
    }


    unique_ptr<StoppingCriteria<SOL,TYPE_FITNESS>> Create_StoppingCriteria() {
        unique_ptr<StoppingCriteria<SOL,TYPE_FITNESS>> stoppingCriteria = make_unique<StoppingCriteria<SOL, TYPE_FITNESS>>();
        stoppingCriteria->addCriteria(new CriteriaBudget<SOL, TYPE_FITNESS>(55));
        stoppingCriteria->addCriteria(new CriteriaFitnessObjectif<SOL, TYPE_FITNESS>(25));
        return move(stoppingCriteria);
    }





private:
    std::map<std::string, int> id_optimizaionAlgorithm;

    vector<pair<string, unique_ptr<OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>>>> optimizationAlgorithm;
    

};


#endif
