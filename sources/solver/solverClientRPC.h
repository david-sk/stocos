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
            mt_rand.seed(configuration["seed"].isInt());
        else
            mt_rand.seed(static_cast<std::mt19937::result_type>(time(0)));

        problem->loadInstance(_configuration["problem"]["instance"].asString());

        AlgoBuilder<SOL, TYPE_FITNESS, TYPE_CELL> algoBuilder(mt_rand, _problem);

        for (std::string const &id : _configuration["OptimizationAlgorithm"].getMemberNames())
            oAlgo.insert(oAlgo.begin(), algoBuilder(id, _configuration["OptimizationAlgorithm"][id]));

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
        std::unique_ptr<SOL> initial_solution = _problem->new_solution();
        _problem->full_eval(*initial_solution);
        Json::Value x = _configuration;
        x["aposd"]["initial_solution"] = initial_solution->asJson();
        std::cout<<x["aposd"]["initial_solution"]<<std::endl;
        received = initialization(x);
        object_id = received["object_id"].asString();
        
        unsigned int i = 0;
        do {
            if (!received["error"].empty()) {
                throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " received from aposd" + received["error_msg"].asString());
            }
            assert(received["num_paramter"].asUInt() < oAlgo.size());
            solution_t0->loadJson(received["Solution"]);
            oAlgo[received["num_paramter"].asUInt()]->reset();
			solution_t1 = oAlgo[received["num_paramter"].asUInt()]->operator()(*solution_t0);
            Json::Value send;
            send["Solution_t0"] = solution_t0->asJson();
            send["Solution_t1"] = solution_t1->asJson();
            send["num_paramter"] = received["num_paramter"].asUInt();
            send["object_id"] = object_id;
            received = learningOnline(send);
        } while(i++ < 100);

        Json::Value msgSendFinish;
        msgSendFinish["object_id"] = object_id;
        received = finish(msgSendFinish);
    }

   private:
    const Json::Value &_configuration;
    std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> _problem;
    HttpClient client;
    std::mt19937 mt_rand;
    std::vector<std::unique_ptr<OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>>> oAlgo;
    std::string object_id;
    Json::Value received;
    std::unique_ptr<SOL> solution_t0;
    std::unique_ptr<SOL> solution_t1;
};

#endif
