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

    Json::Value initialization() {
        Json::Value params;
        params["method"] = "notify";
        params["params"].append("msgxxxxxxxxxxxxxxxxxxxxxx");
        params["id"] = 1;

        string output;
        string r;

        Json::Value json = params;
        Json::StreamWriterBuilder builder;
        builder["commentStyle"] = "None";
        builder["indentation"] = "";
        // std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
        // writer->write(json, &std::cout);
        output = Json::writeString(builder, json);
        cout << output << endl;

        try {
            client.SendRPCMessage(output, r);
            cout << r << endl;
        } catch (JsonRpcException &e) {
            cerr << e.what() << endl;
        }
    }

    Json::Value learning() {

    }
    Json::Value finish() {

    }

    void operator()() {

    }

   private:
    const Json::Value &_configuration;
    shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> _problem;
    HttpClient client;
    std::mt19937 mt_rand;
    vector<unique_ptr<OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>>> oAlgo;
};

#endif
