#!/usr/bin/env python
#-*- coding: utf-8 -*-
# Python 3.7

#
# @Author: *
# @License: *
# @Date: *
# @Version: *
# @Purpose: *
#




import json
import pymongo
import os.path
import logging
import numpy as np

import plot
from callprocess import parallelExecution, worker

class Experiments:
    def __init__(self, name_of_experience : str, path_stocos_binary : str, configuration : dict, database : str, collection : str):
        self._name_of_experience = name_of_experience
        self._path_stocos_binary = path_stocos_binary
        self._configuration = configuration
        self._database = database
        self._collection = collection
        self._configuration["Statistic"]["database"] = self._database
        self._configuration["Statistic"]["collection"]= self._collection
        self.check()

    def load(self, configuration : dict):
        self._configuration = configuration
        self._configuration["Statistic"]["database"] = self._database
        self._configuration["Statistic"]["collection"]= self._collection

    def check(self) :
        ## Check existing path stocos
        if not(os.path.exists(self._path_stocos_binary)):
            raise RuntimeError(__file__ + ":" + "100" +"[-] Path file stocos " + self._path_stocos_binary + " does not exist")

        ## Check existing path problem instance
        if not(os.path.exists(self._configuration["problem"]["instance"])):
            raise RuntimeError(__file__ + ":" + "44" +"[-] Path file instance problem "+ self._configuration["problem"]["instance"] +" does not exist")

        ## Check existing collection in database
        client = pymongo.MongoClient() # host="host",port=3622, connectTimeoutMS=500
        db = client[self._database]
        collection = db[self._collection]

        # if collection.count_documents({}) != 0:
        #     raise RuntimeError("[-] Collection alerady exist")

    # def run(self,  number_of_experiments : int = 100, outfile : str = "output.pdf"):
    #     list_of_experiments = self.preProcessing(number_of_experiments, self._name_of_experience)
    #     print(self.callProcessing(list_of_experiments))
    #     self.postProcessing(outfile)

    def preProcessing(self, number_of_experiments : int, name_of_experience : str) -> list:
        if not(os.path.exists(self._path_stocos_binary)):
            raise RuntimeError(__file__ + ":" + "128" +"[-] File does not exsit")

        list_of_experiments : list = []
        for i in range(0, number_of_experiments):
            self._configuration["seed"] = i
            self._configuration["Statistic"]["sensorFinal"]["name"] = name_of_experience
            self._configuration["Statistic"]["sensorFinal"]["num"] = i
            list_of_experiments = list_of_experiments + [self._path_stocos_binary + " -j \'" + json.dumps(self._configuration) +"\'"]

        return list_of_experiments

    def callProcessing(self, list_of_experiments : list):
        return parallelExecution(list_of_experiments, 6, worker, "", True)

    def postProcessing(self, outfile : str = "output.pdf"):
        ## Connexion
        client = pymongo.MongoClient() # host="host",port=3622, connectTimeoutMS=500
        db = client[self._database]
        collection = db[self._collection]

        ## query in database
        _query = [{"$group":
                {"_id": "$experience.name",
                "averageValue" :{"$avg": "$round"},
                "stdDev": {"$stdDevSamp": "$round" },
                "N": { "$sum": 1  }
                }
                }, {"$sort":{"_id":1}}]
        data = list(collection.aggregate(_query))
        
        for i in range(0, len(data)):
            data[i]['confidenceInterval'] = 1.96 * (data[i]['stdDev'] / np.sqrt(data[i]['N'])) 

        
        print(data)


        ## Plot
        p = plot.Linesplot()
        p.add(data, name_x= "_id", name_y="averageValue", name_e="confidenceInterval", line = False, size = 6)
        p.legend(xlabel="round", ylabel="fitness")
        p.tofile(outfile)

if __name__ == '__main__':
    number_of_experiments : int = 100

    with open('stocos-oneMax.json', 'r') as myfile:
        data=myfile.read()

    # print(data)
    # data = '{"a": 10}'
    # print(data)
    obj = json.loads(data)
    e = Experiments(name_of_experience = "OneMax", path_stocos_binary = "../../build/stocos-Release", configuration = obj, database = "oneMax-cmp-algo", collection = "N1000")

    # Experience 
    print("> ILS")
    obj["parameter_id"] = 0
    e.load(obj)
    list_of_experiments = e.preProcessing(number_of_experiments, name_of_experience = "ILS")
    e.callProcessing(list_of_experiments)

    # # Experience 
    # print("> EA")
    # obj["parameter_id"] = 1
    # e.load(obj)
    # list_of_experiments = e.preProcessing(number_of_experiments, name_of_experience = "EA")
    # e.callProcessing(list_of_experiments)

    # Experience 
    print("> TS")
    obj["parameter_id"] = 2
    e.load(obj)
    list_of_experiments = e.preProcessing(number_of_experiments, name_of_experience = "TS")
    e.callProcessing(list_of_experiments)

    # Experience 
    print("> OPL")
    obj["parameter_id"] = 3
    e.load(obj)
    list_of_experiments = e.preProcessing(number_of_experiments, name_of_experience = "OPL")
    e.callProcessing(list_of_experiments)

    # Experience
    print("> FI")
    obj["parameter_id"] = 5
    e.load(obj)
    list_of_experiments = e.preProcessing(number_of_experiments, name_of_experience = "FI")
    e.callProcessing(list_of_experiments)

    # Plot
    print("> Plot")
    e.postProcessing()
