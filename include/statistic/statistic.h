///
/// @file statistic.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef STATISTIC_H
#define STATISTIC_H

#include <fstream>
#include <iostream>
#include <string>

#include <jsoncpp/json/json.h>
#include <mongo/client/dbclient.h>

#include "sensor.h"

namespace stocos {

template<class SOL>
class Statistic : private std::vector<Sensor<SOL>*> {
  public:
	static constexpr const char* NONE = "none";
	static constexpr const char* STDOUT = "stdout";
	static constexpr const char* FILE = "file";
	static constexpr const char* MONGODB = "mongodb";

	Statistic(bool none = false);
	///
	/// @brief Enrengistre les données dans un fichier
	///
	/// @param namefile name of the output file
	///
	Statistic(const std::string& namefile);

	Statistic(const std::string& mongo_hostname, const std::string& mongo_database,
			  const std::string& mongo_collection, const std::string& mongo_username = "",
			  const std::string& mongo_pwd = "");

	virtual ~Statistic();

	void operator()(const SOL& s, std::string name_calling_class = "");

	Json::Value asJson(const SOL& s);

	void addSensor(Sensor<SOL>* s);

  protected:
	std::string _name_calling_class;

	const char* recording;
	bool _none;

	Json::StreamWriterBuilder builder;
	Json::Value show_before;

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

} // namespace stocos
#endif