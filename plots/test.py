#!/usr/bin/env python
#-*- coding: utf-8 -*-
# Python 3.7

#
# @Author: Jxtopher
# @License: *
# @Date: 2018-08-04
# @Version: V1
# @Purpose: Exemple d'utitlisation de mongodb
#

import pymongo
import plot

def show(collection):
    for i in collection.find({}):
        print(i)

def query_group(collection):
    _query = [{"$group":
              {"_id": "$round",
              "averageValue" :{"$avg": {"$arrayElemAt": ["$Solution.fitness", 0 ]}},
              "stdDev": { "$stdDevSamp": {"$arrayElemAt": ["$Solution.fitness", 0 ]} }
              }
             }, {"$sort":{"_id":1}}]
    results = collection.aggregate(_query)
    return list(results)

if __name__ == '__main__':
    ## Connexion
    client = pymongo.MongoClient()
    db = client["db"]
    collection = db["c"]

    # show(collection)
    data = query_group(collection)

    # Plot
    p = plot.Linesplot()
    p.add(data, name_x= "_id", name_y="averageValue")
    p.legend(xlabel="round", ylabel="fitness")
    p.tofile()
#     query_serach(collection)