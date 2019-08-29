///
/// @file solverClientRPC.h
/// @author your name (you@domain.com)
/// @brief
/// @version 0.1
/// @date 2019-08-12
///
/// http://pooh.poly.asu.edu/Ser321/Resources/doc/json-api-docs/jsonrpc-cpp-api-html/index.html
/// main.cpp -ljsoncpp -lcurl -ljsonrpccpp-common -ljsonrpccpp-client -o sampleclient
///
///
#ifndef SOLVER_CLIENT_RPC_H
#define SOLVER_CLIENT_RPC_H

#include <jsonrpccpp/client.h>
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <iostream>
#include <memory>

using namespace jsonrpc;

template <typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class SolverClientRPC : public Solver {
   public:
    SolverClientRPC(const Json::Value &configuration, std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem)
        : Solver(), _configuration(configuration), _problem(problem), client("http://localhost:8080") {
        if (!configuration["seed"].empty())
            mt_rand.seed(configuration["seed"].asInt());
        else
            mt_rand.seed(static_cast<std::mt19937::result_type>(time(0)));

        // Definition of the optimization problem
        if (!_configuration["problem"]["instance"].empty()) {
            Json::Value tmp = problem->loadInstance(_configuration["problem"]["instance"].asString());
            problem->loadJson(tmp);
        } else if (!_configuration["problem"]["numInstance"].empty())
            problem->loadJson(_configuration);
        else
            throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " [-] Problem does not exist.");


        // Definition of optimization algorithms
        AlgoBuilder<SOL, TYPE_FITNESS, TYPE_CELL> algoBuilder(mt_rand, _problem, _configuration);

        for (std::string const & id : _configuration["OptimizationAlgorithm"].getMemberNames())
            optimizationAlgorithm[stoul(id)] = algoBuilder(_configuration["OptimizationAlgorithm"][id]);

        // Create the initial solution
        if (_configuration["initial_solution"].empty())
            initial_solution = _problem->new_solution();
        else
            initial_solution = std::make_unique<SOL>(_configuration["initial_solution"]);

        if (!initial_solution->fitnessIsValid()) {
            _problem->full_eval(*initial_solution);
        }

        // Construction du global criterea
        global_stopping_criteria = algoBuilder.stoppingCriteria(_configuration["StoppingCriteria"]);


        // Allocation 
        solution_t0 = std::make_unique<SOL>();
        solution_t1 = std::make_unique<SOL>();
    }
    virtual ~SolverClientRPC() {}

    std::string jsonAsString(const Json::Value &json) {
        Json::StreamWriterBuilder builder;
        builder["commentStyle"] = "None";
        builder["indentation"] = "";
        return Json::writeString(builder, json);
    }

    Json::Value stringAsjson(const std::string &strJson) {
        Json::Value root;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(strJson.c_str(), root);
        if (!parsingSuccessful) throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " " + reader.getFormattedErrorMessages());
        return root;
    }

    Json::Value initialization(const Json::Value &configuration, unsigned int id = 0) {
        Json::Value params;
        params["method"] = "initialization";
        params["params"].append(jsonAsString(configuration["aposd"]));
        params["id"] = id;

        std::string result;

        try {
            client.SendRPCMessage(jsonAsString(params), result);
        } catch (JsonRpcException &e) {
            throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " " + e.what());
        }
        return stringAsjson(result);
    }

    Json::Value learningOnline(const Json::Value &msgSend, unsigned int id = 0) {
        Json::Value params;
        params["method"] = "learning";
        params["params"].append(jsonAsString(msgSend));
        params["id"] = id;

        std::string result;

        try {
            client.SendRPCMessage(jsonAsString(params), result);
        } catch (JsonRpcException &e) {
            throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " " + e.what());
        }
        return stringAsjson(result);
    }

    Json::Value finish(const Json::Value &msgSend, unsigned int id = 0) {
        Json::Value params;
        params["method"] = "finish";
        params["params"].append(jsonAsString(msgSend));
        params["id"] = id;

        std::string result;

        try {
            client.SendRPCMessage(jsonAsString(params), result);
        } catch (JsonRpcException &e) {
            throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " " + e.what());
        }
        return stringAsjson(result);
    }

    void operator()() {
        // Ajout à la configuration une solution initial à envoyer au serveur
        Json::Value aposd_configuration = _configuration;
        aposd_configuration["aposd"]["initial_solution"] = initial_solution->asJson();
        std::cout<<aposd_configuration["aposd"]["initial_solution"]<<std::endl;
        
        received = initialization(aposd_configuration);
        object_id = received["object_id"].asString();
        
        unsigned int i = 0;
        do {
            // Si le message reçu est une erreur
            if (!received["error"].empty())
                throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " received from aposd" + received["error_msg"].asString());
            
            // Check du numero du paramètre reçus
            assert(received["num_paramter"].asUInt() < optimizationAlgorithm.size());

            //
            solution_t0->loadJson(received["Solution"]);
            optimizationAlgorithm[received["num_paramter"].asUInt()]->reset();
			solution_t1 = optimizationAlgorithm[received["num_paramter"].asUInt()]->operator()(*solution_t0);

            Json::Value send;
            send["Solution_t0"] = solution_t0->asJson();
            send["Solution_t1"] = solution_t1->asJson();
            send["num_paramter"] = received["num_paramter"].asUInt();
            send["object_id"] = object_id;
            received = learningOnline(send);
        } while(global_stopping_criteria->operator()(*solution_t1));

        Json::Value msgSendFinish;
        msgSendFinish["object_id"] = object_id;
        received = finish(msgSendFinish);
    }

   private:
    const Json::Value &_configuration;
    std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> _problem;
    HttpClient client;
    std::mt19937 mt_rand;
    std::map<unsigned int, std::unique_ptr<OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>>> optimizationAlgorithm;
    std::unique_ptr<StoppingCriteria<SOL,TYPE_FITNESS>> global_stopping_criteria;
    std::string object_id;
    Json::Value received;
    std::unique_ptr<SOL> initial_solution;
    std::unique_ptr<SOL> solution_t0;
    std::unique_ptr<SOL> solution_t1;
};

#endif
