///
/// @file criteria.h
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief 
///

#ifndef STATISTIC_H
#define STATISTIC_H

#include <iostream>
#include <string>
#include <fstream>

#include <mongo/client/dbclient.h>

#include "sensor.h"



template<class SOL>
class Statistic {
    public:

    static constexpr const char* NONE = "none";
	static constexpr const char* STDOUT = "stdout";
	static constexpr const char* FILE = "file";
    static constexpr const char* MONGODB = "mongodb";

    Statistic(bool none = false) : _none(none) {
        if (none)
            recording = NONE;
        else 
            recording = STDOUT;
        
        builder["commentStyle"] = "None";
        builder["indentation"] = "";
    }

    /// 
    /// @brief Enrengistre les données dans un fichier
    /// 
    /// @param namefile name of the output file
    ///
    Statistic(const std::string &namefile) : _namefile(namefile) {
        recording = FILE;
        _none = false;
        outFile.open(_namefile);
        
        builder["commentStyle"] = "None";
        builder["indentation"] = "";
    }

    Statistic(const std::string &mongo_hostname, const std::string &mongo_database, const std::string &mongo_collection, const std::string &mongo_username = "", const std::string & mongo_pwd = "") :
        _mongo_hostname(mongo_hostname),
        _mongo_database(mongo_database),
        _mongo_collection(mongo_collection),
        _mongo_username(mongo_username),
        _mongo_pwd(mongo_pwd) {
        recording = MONGODB;
        _none = false;
        try {
            mongo::client::initialize();
            _mongo_client.connect(mongo_hostname);
            std::string errmsg;
            if (not(_mongo_username.empty() && _mongo_pwd.empty()))
                _mongo_client.auth(_mongo_database, _mongo_username, _mongo_pwd, errmsg);
            _mongo_db_c = _mongo_database + "." + _mongo_collection;
        }
        catch (const mongo::DBException &e) {
            throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " " +e.what());
        }
        
        builder["commentStyle"] = "None";
        builder["indentation"] = "";
    }


    virtual ~Statistic() {
        Json::Value show_end;
        for(unsigned int i = 0 ; i < sensor.size() ; i++) {
            Json::Value tmp = sensor[i]->finish();
            if (!tmp.empty())
                show_end[sensor[i]->name()] = tmp;
            if (sensor[i]->name() == "final") {
                if (_name_calling_class.empty())
                    show_end["final"]["nameCallingClass"] = "unknown";
                else 
                    show_end["final"]["nameCallingClass"] = _name_calling_class;
            }
        }

        if (!show_end.empty()) {
            if (recording == NONE) {
                return ;
            } else if (recording == STDOUT) {
                std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
                writer->write(show_end["final"], &std::cout);
                std::cout<<std::endl;
            } else if (recording == FILE) {
                std::stringstream ss;
                std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
                writer->write(show_end["final"], &outFile);
                outFile<<std::endl;
            } else if (recording == MONGODB) {
                mongo::BSONObj bson = mongo::fromjson(Json::writeString(builder, show_end["final"]));
                _mongo_client.insert(_mongo_db_c, bson);
            }
        }
        
        for(unsigned int i = 0 ; i < sensor.size() ; i++)
            delete sensor[i];

        sensor.clear();
    }

    void operator()(const SOL &s, std::string name_calling_class = "") {
        Json::Value tmp = this->asJson(s);
        _name_calling_class = name_calling_class;
        if (!tmp.empty()) {
            if (recording == NONE) {
                return ;
            } else if (recording == STDOUT) {
                std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
                writer->write(tmp, &std::cout);
                std::cout<<std::endl;
            } else if (recording == FILE) {
                std::stringstream ss;
                std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
                writer->write(tmp, &outFile);
                outFile<<std::endl;
            } else if (recording == MONGODB) {
                mongo::BSONObj bson = mongo::fromjson(Json::writeString(builder, tmp));
                _mongo_client.insert(_mongo_db_c, bson);
            } else {
                throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " The output Statistic does not exist.");
            }
        }
    }

    Json::Value asJson(const SOL &s) {
        Json::Value jsonValue;
        for(unsigned int i = 0 ; i < sensor.size() ; i++) {
            sensor[i]->apply(s);
            Json::Value tmp = sensor[i]->asJson();
            if (!tmp.empty())
                jsonValue[sensor[i]->name()] = tmp;
            if (sensor[i]->name() == "nameCallingClass") {
                if (_name_calling_class.empty())
                    jsonValue[sensor[i]->name()] = "unknown";
                else 
                    jsonValue[sensor[i]->name()] = _name_calling_class;
            }
        }
        return jsonValue;
    }

    void addSensor(Sensor<SOL> *s) {
        sensor.push_back(s);
    }

    protected:
        
        std::vector<Sensor<SOL> *> sensor;
        std::string _name_calling_class;

        const char* recording;
        bool _none;

        Json::StreamWriterBuilder builder;

        // file
        std::string _namefile;
        std::ofstream outFile;

        // mongodb
        mongo::DBClientConnection _mongo_client;
        std::string _mongo_hostname;
        std::string _mongo_database;
        std::string _mongo_collection;
        std::string _mongo_db_c;
        std::string _mongo_username;
        std::string _mongo_pwd;

};

#endif