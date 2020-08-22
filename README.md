# STOChastic Optimization Solver (stocos)

Stocos solves optimization problems with a large search space.  He is able to provide solutions with a good approximation. Optimization plan is described using the JSON format with in particular the following elements: the algorithms used, the problem to be solved and how to record the results of the optimization. Of course the solver can be used as liberay.


Le solver uses the following technologies:
- C++20 with boost, jsoncpp, mongoclient, json-rpc-cpp
- Json like
- Keep data in mongodb


#### Branch Master 

<p align="center">
| Intergration  |        Status |
| ------------- | ------------- |
| **Build Status Linux**  | [![CircleCI](https://circleci.com/gh/Jxtopher/stocos.svg?style=svg)](https://circleci.com/gh/Jxtopher/stocos) |
| **CodeFactor**    | [![CodeFactor](https://www.codefactor.io/repository/github/jxtopher/stocos/badge)](https://www.codefactor.io/repository/github/jxtopher/stocos) |
</p>

## Example

Stocos can be configured in two different ways:
- take a file json
- take a string json


* Solve the oneMax problem :

```bash
$ ./build/stocos -c configuration/stocos-oneMax.json
```

```bash
$ ./build/stocos -j '{ "seed": 0, "problem": { "name": "OneMax", "instance": "instances/OneMax/onemax-50.json" }, "parameter_id": 0, "OptimizationAlgorithm": { "0": { "className":"IteratedLocalSearch", "StoppingCriteria": { "budget": 100, "fitnessObjectif": 50 }, "AtomicOperation": { "className": "FlipBit", "c": 1 }, "OptimizationAlgorithm": { "className": "FirstImprovement", "StoppingCriteria": { "budget": 100, "fitnessObjectif": 50 }, "AtomicOperation": { "className": "FlipBit", "c": 1 } } }  }, "Statistic": { "recording":"stdout", "sensorNumRound" : true, "sensorSolution" : true, "sensorStopwatch" : false, "sensorFinal" : { "name" : "oneMax", "num" : 6 } } }'
```

