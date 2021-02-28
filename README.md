# STOChastic Optimization Solver (stocos)

Stocos solves optimization problems with a large search space.  It is able to provide solutions with a good approximation. The optimization plan is described using the JSON format with in particular the following elements: the algorithms used, the problem to be solved and how to record the results of the optimization. Of course the solver can be used as library.


The solver uses the following technologies:
- C++20 with boost, jsoncpp, mongoclient, json-rpc-cpp
- Json like
- Keep data in mongodb


#### Branch Master 

| Integration   |        Status |
| ------------- | ------------- |
| **Build Status Linux**  | [![CircleCI](https://circleci.com/gh/Jxtopher/stocos.svg?style=svg)](https://circleci.com/gh/Jxtopher/stocos) |
| **CodeFactor**    | [![CodeFactor](https://www.codefactor.io/repository/github/jxtopher/stocos/badge)](https://www.codefactor.io/repository/github/jxtopher/stocos) |


## Example

Stocos can be configured in two different ways:
- with a json file
- with a json string


* Solving the oneMax problem:

```bash
$ ./build/stocos -c configuration/stocos-oneMax.json
```

```bash
$ ./build/stocos -j '{ "seed": 0, "problem": { "name": "OneMax", "instance": "instances/OneMax/onemax-50.json" }, "parameter_id": 0, "Optimization": { "0": { "className":"IteratedLocalSearch", "StoppingCriteria": { "budget": 100, "fitnessObjectif": 50 }, "AtomicOperation": { "className": "FlipBit", "c": 1 }, "Optimization": { "className": "FirstImprovement", "StoppingCriteria": { "budget": 100, "fitnessObjectif": 50 }, "AtomicOperation": { "className": "FlipBit", "c": 1 } } }  }, "Statistic": { "recording":"stdout", "sensorNumRound" : true, "sensorSolution" : true, "sensorStopwatch" : false, "sensorFinal" : { "name" : "oneMax", "num" : 6 } } }'
```

