# Operational Run

It is often not possible to run Balmorel optimisations for all hours in a year. You might also want to check the adequacy of capacities invested through other weather years. This guide illustrates the built-in capability of Balmorel to soft-link an investment optimisation with a operational run using rolling seasons. 

:::{warning}
It is recommended to perform a 3 step optimization. First, run an investment optimisation. Then, run a full year dispatch simulation (with less hours) that will capture the storage levels through the year. Then all seasons and hours can be run with a rolling season approach. 
:::

## Full year dispatch simulation
This section assumes that you already run an investment optimisation with Balmorel, which by default outputs a lot of .gdx files to the simex folder. The full year run is an operational run that does not allow new capacities to be built, but will enable some backup if needed. The idea is to capture the storage levels through the year, that will then be used for the rolling season run to fix the storage levels at the beginning of each season. The Set S should contain all the 52 seasons. The set T should capture well enough the dynamics of the season (recommendation: every 5 hours at least). 

In order to do the full year run, we need to make adjustments to `balopt.opt`. Follow the steps below.

Turn on import of simex-files and extra backup generation by turning on the following global variables in `balopt.opt`, i.e. append a 'yes' to them, and change the model type to RMIP:
```
$Setglobal import_results yes
$setglobal ADDTECHDEV yes
$setglobal ADDBACKUPGEN yes
$setglobal ADDTRANSDEV yes
$setglobal ADDHEATTRANSDEV yes
$setglobal ADDH2TRANSDEV yes
$Setglobal export_results yes
$setglobal SOLVETYPE RMIP
```

Turn off investment optimisation, decommissioning and Rolling Seasons by removing the appended 'yes' in front of the following global variables in `balopt.opt`:
```
$setglobal TechInvest   
$setglobal TransInvest 
$Setglobal H2TransInvest 
$setglobal DECOM 
$setglobal RollingSeasons 
```

Then, you can perform a Rolling Season run with all hours. 

## Rolling Seasons
This section assumes that you have already run an investment optimisation and dispatch simulation with Balmorel, which by default outputs a lot of .gdx files to the simex folder. These files include `simex/GKACCUMNET.gdx`, which contain the capacities of the investment optimisation and is required for an operational run.

:::{warning}
- **Simex output gets overwritten for each scenario!** 
  
    If you are running several investment optimisation scenarios, the `simex/*.gdx` files will be replaced for each finished optimisation. Thus, include a copy command (Windows: `copy`, Linux: `cp`) in your batch script to save simex outputs for each scenario.


- **No simex output?** 

    You might have turned off the `export_results` global variable in `balopt.opt`. Make sure that it is turned on: `$Setglobal export_results yes`
:::

We will need to make adjustments to `balopt.opt` in order to perform an operational run. Follow the steps below below.

Turn on rolling seasons, import of simex-files and extra backup generation by turning on the following global variables in `balopt.opt`, i.e. append a 'yes' to them:
```
$setglobal RollingSeasons yes
$Setglobal import_results yes
$setglobal ADDTECHDEV yes
$setglobal ADDBACKUPGEN yes
$setglobal ADDTRANSDEV yes
$setglobal ADDHEATTRANSDEV yes
$setglobal ADDH2TRANSDEV yes
```

Turn off investment optimisation, decommissioning and export of simex outputs by removing the appended 'yes' in front of the following global variables in `balopt.opt`:
```
$setglobal TechInvest   
$setglobal TransInvest 
$Setglobal H2TransInvest 
$setglobal DECOM 
$Setglobal export_results
```

Notice that there are a lot of other options in `balopt.opt`, e.g. on how to manage interseasonal storages. This simple approach, therefore, lets Balmorel optimise the storage level of interseasonal storages freely for each week, which is more shortsighted than reality.

