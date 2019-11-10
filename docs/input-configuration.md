

## Graine aléatoire

```json
"seed": 0,
```


## Problème

name -> nom du problème
instance -> chemin du fichier décrivant l'instance

```json
"problem": {
    "name": "OneMax",
    "instance": "instances/OneMax/onemax-50.json"
}
```

## Statistique

### stdout
```json
"Statistic": {
    "recording":"stdout",
    "sensorNameCallingClass": true,
    "sensorNumRound" : true,
    "sensorSolution" : true,
    "sensorFitness": true,
    "sensorStopwatch" : false,
    "sensorFinal" : {
        "name" : "TSP",
        "num" : 0
    }
}
```

### stdout none
```json
"Statistic": {
    "recording":"none"
}
```

### stdout file

```json
"Statistic": {
    "recording":"file",
    "namefile":"toto.txt",
    "sensorNameCallingClass": true,
    "sensorNumRound" : true,
    "sensorSolution" : true,
    "sensorFitness": true,
    "sensorStopwatch" : false,
    "sensorFinal" : {
        "name" : "TSP",
        "num" : 0
    }
}
```

### stdout mongodb
```json
"Statistic": {
    "recording":"mongodb",
    "hostname":"localhost",
    "database": "db",
    "collection": "c",
    "sensorNameCallingClass": true,
    "sensorNumRound" : true,
    "sensorSolution" : true,
    "sensorFitness": true,
    "sensorStopwatch" : false,
    "sensorExperience" : {
         "name" : "oneMax",
         "num" : 6
    },
    "sensorFinal" : {
        "name" : "TSP",
        "num" : 0
    }
}
```

