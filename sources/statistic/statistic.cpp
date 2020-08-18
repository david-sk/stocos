///
/// @file statistic.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///
#include <statistic/statistic.h>

namespace stocos {

template<class SOL>
Statistic<SOL>::Statistic(bool none) : _none(none) {
	if(none)
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
template<class SOL>
Statistic<SOL>::Statistic(const std::string& namefile) : _namefile(namefile) {
	recording = FILE;
	_none = false;
	outFile.open(_namefile);

	builder["commentStyle"] = "None";
	builder["indentation"] = "";
}

template<class SOL>
Statistic<SOL>::Statistic(const std::string& mongo_hostname, const std::string& mongo_database,
			const std::string& mongo_collection, const std::string& mongo_username,
			const std::string& mongo_pwd)
	: _mongo_hostname(mongo_hostname), _mongo_database(mongo_database),
		_mongo_collection(mongo_collection), _mongo_username(mongo_username),
		_mongo_pwd(mongo_pwd) {
	recording = MONGODB;
	_none = false;
	try {
		mongo::client::initialize();
		_mongo_client.connect(mongo_hostname);
		std::string errmsg;
		if(not(_mongo_username.empty() && _mongo_pwd.empty()))
			_mongo_client.auth(_mongo_database, _mongo_username, _mongo_pwd, errmsg);
		_mongo_db_c = _mongo_database + "." + _mongo_collection;
	} catch(const mongo::DBException& e) {
		throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
									" " + e.what());
	}

	builder["commentStyle"] = "None";
	builder["indentation"] = "";
}

template<class SOL>
Statistic<SOL>::~Statistic() {
	Json::Value show_end;
	for(unsigned int i = 0; i < this->size(); i++) {
		Json::Value tmp = (*this)[i]->finish();
		if(!tmp.empty()) show_end[(*this)[i]->name()] = tmp;
		if((*this)[i]->name() == "final") {
			if(_name_calling_class.empty())
				show_end["final"]["nameCallingClass"] = "unknown";
			else
				show_end["final"]["nameCallingClass"] = _name_calling_class;
		}
	}

	if(!show_end.empty()) {
		if(recording == NONE) {
			return;
		} else if(recording == STDOUT) {
			std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
			writer->write(show_end["final"], &std::cout);
			std::cout << std::endl;
		} else if(recording == FILE) {
			std::stringstream ss;
			std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
			writer->write(show_end["final"], &outFile);
			outFile << std::endl;
			outFile.close();
		} else if(recording == MONGODB) {
			mongo::BSONObj bson =
				mongo::fromjson(Json::writeString(builder, show_end["final"]));
			_mongo_client.insert(_mongo_db_c, bson);
		}
	}

	// for(unsigned int i = 0; i < this->size(); i++) delete this[i];
	for(Sensor<SOL>* sensor : *this) delete sensor;

	this->clear();
}

template<class SOL>
void Statistic<SOL>::operator()(const SOL& s, std::string name_calling_class) {
	Json::Value tmp = this->asJson(s);
	if(!tmp["round"].empty())
		show_before["round"] = tmp["round"];
	else
		tmp.removeMember("round");
	if(show_before != tmp) {
		_name_calling_class = name_calling_class;
		if(!tmp.empty()) {
			if(recording == NONE) {
				return;
			} else if(recording == STDOUT) {
				std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
				writer->write(tmp, &std::cout);
				std::cout << std::endl;
			} else if(recording == FILE) {
				std::stringstream ss;
				std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
				writer->write(tmp, &outFile);
				outFile << std::endl;
			} else if(recording == MONGODB) {
				mongo::BSONObj bson = mongo::fromjson(Json::writeString(builder, tmp));
				_mongo_client.insert(_mongo_db_c, bson);
			} else {
				throw std::runtime_error(std::string{} + __FILE__ + ":" +
											std::to_string(__LINE__) +
											" The output Statistic does not exist.");
			}
		}
		show_before = tmp;
	} else {
		if(recording == STDOUT && !tmp["round"].empty()) {
			std::cout << "round:" << tmp["round"] << "\r";
			std::cout.flush();
		}
	}
}

template<class SOL>
Json::Value Statistic<SOL>::asJson(const SOL& s) {
	Json::Value jsonValue;
	for(unsigned int i = 0; i < this->size(); i++) {
		(*this)[i]->apply(s);
		Json::Value tmp = (*this)[i]->asJson();
		if(!tmp.empty()) jsonValue[(*this)[i]->name()] = tmp;
		if((*this)[i]->name() == "nameCallingClass") {
			if(_name_calling_class.empty())
				jsonValue[(*this)[i]->name()] = "unknown";
			else
				jsonValue[(*this)[i]->name()] = _name_calling_class;
		}
	}
	return jsonValue;
}

template<class SOL>
void Statistic<SOL>::addSensor(Sensor<SOL>* s) {
	this->push_back(s);
}

template class Statistic<Solution<int>>;
template class Statistic<SolutionArray<double, double>>;
template class Statistic<SolutionArray<double, bool>>;
template class Statistic<SolutionArray<int, bool>>;
template class Statistic<SolutionArray<unsigned int, bool>>;
template class Statistic<SolutionArray<double, unsigned int>>;
template class Statistic<SolutionArray<unsigned int, unsigned int>>;

} // namespace stocos