///
/// \file solverClientRPC.h
/// \author your name (you@domain.com)
/// \brief
/// \version 0.1
/// \date 2019-08-12
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
    SolverClientRPC(const Json::Value &configuration, shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem)
        : Solver(), _configuration(configuration), _problem(problem), client("http://localhost:8080") {
        if (!configuration["seed"].empty())
            mt_rand.seed(configuration["seed"].isInt());
        else
            mt_rand.seed(static_cast<mt19937::result_type>(time(0)));

        problem->loadInstance(_configuration["problem"]["instance"].asString());

        AlgoBuilder<SOL, TYPE_FITNESS, TYPE_CELL> algoBuilder(mt_rand, _problem);

        for (string const &id : _configuration["OptimizationAlgorithm"].getMemberNames())
            oAlgo.insert(oAlgo.begin(), algoBuilder(id, _configuration["OptimizationAlgorithm"][id]));
    }
    virtual ~SolverClientRPC() {}

    string jsonAsString(const Json::Value &json) {
        Json::StreamWriterBuilder builder;
        builder["commentStyle"] = "None";
        builder["indentation"] = "";
        return Json::writeString(builder, json);
    }

    Json::Value stringAsjson(const string &strJson) {
        Json::Value root;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(strJson.c_str(), root);
        if (!parsingSuccessful) throw runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " " + reader.getFormattedErrorMessages());
        return root;
    }

    Json::Value initialization(const Json::Value &configuration, unsigned int id = 1) {
        Json::Value params;
        params["method"] = "initialization";
        params["params"].append(jsonAsString(configuration["aposd"]));
        params["id"] = id;

        string result;

        try {
            client.SendRPCMessage(jsonAsString(params), result);
        } catch (JsonRpcException &e) {
            throw runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " " + e.what());
        }
        return stringAsjson(result);
    }

    Json::Value learning() {
        Json::Value params;
        return params;
    }
    Json::Value finish() {
        Json::Value params;
        return params;
    }

    void operator()() {
        cout<<initialization(_configuration)<<endl;
    }

   private:
    const Json::Value &_configuration;
    shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> _problem;
    HttpClient client;
    std::mt19937 mt_rand;
    vector<std::unique_ptr<OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>>> oAlgo;
};

#endif
