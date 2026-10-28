# Operational Run

It is often not possible to run Balmorel optimisations for all hours in a year. You might also want to check the adequacy of capacities invested through other weather years. This guide illustrates the built-in capability of Balmorel to soft-link an investment optimisation with a operational run using rolling seasons. 

:::{warning}
It is recommended to perform a 3 step optimization. 

First, run an investment optimisation with export results enabled in balopt.opt: `$setglobal export_results yes`. 

Then, run a full year dispatch simulation (with less hours) that will capture the storage levels through the year. Then all seasons and hours can be run with a rolling season approach. 

- **Simex output gets overwritten for each scenario!** 
  
    If you are running several investment optimisations in the same scenario folder, the `simex/*.gdx` files will be replaced for each finished optimisation. Thus, include a copy command (Windows: `copy`, Linux: `cp`) in your batch script to save simex outputs for each of these sub-scenario runs.


- **No simex output?** 

    You might have turned off the `export_results` global variable in `balopt.opt`. Make sure that it is turned on: `$Setglobal export_results yes`
:::

## Investment Optimisation

This is the default execution of Balmorel, but you will need to change one thing in balopt.opt: Enable export_results to ensure that the necessary files are generated in the scenario/simex folder 

```
$setglobal export_results yes
```

Besides generation, storage and transmission capacities, this exports the invested demand response capacity (`DEMANDRESPONSE` addon) and EV charging infrastructure (`EV` addon). Both are only exported by runs with `TechInvest`, so the operational runs below never overwrite them.


## Full year dispatch simulation
This section assumes that you already run an investment optimisation with Balmorel with `$setglobal export_results yes` in balopt.opt, which outputs a lot of .gdx files to the simex folder. The full year run is an operational run that does not allow new capacities to be built, but will enable some backup if needed. The idea is to capture the storage levels through the year, that will then be used for the rolling season run to fix the storage levels at the beginning of each season. The Set S should contain all the 52 seasons. The set T should capture well enough the dynamics of the season (recommendation: every 5 hours at least). 

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
This section assumes that you have already run the dispatch simulation with Balmorel, which outputs .gdx files to the simex folder. These files include `simex/GKACCUMNET.gdx`, which contain the capacities of the investment optimisation and is required for an operational run and `simex/H2STOVOLTS.gdx`, containing inter-seasonal hydrogen storage levels.

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

To start each week from the storage levels, fuel use and transport demand of the full year run, import them as well:
```
$setglobal HYRSBB123 cont
$Setglobal ADDESTOVOLTS cont
$Setglobal ADDHSTOVOLTS cont
$Setglobal ADDESTOVOLT cont
$Setglobal ADDHSTOVOLT cont
$Setglobal ADDH2STOVOLTS cont
$Setglobal ADDBIOMETHSTOVOLTS cont
$setglobal ADDMAXFUELUSES yes
$setglobal ADDSEASONALTRANSPORTDEMAND yes
```

Without these, Balmorel optimises the level of interseasonal storages freely for each week, which is more shortsighted than reality. Use `$Setglobal ADDEVSTOS cont` too if EVs are modelled as interseasonal storage (`EV_INTERSEASONAL`).

### CO2 limits
The annual CO2 limit in `EMI_POLNA` cannot be enforced when one week is solved at a time. Instead, every run that is not a rolling run writes its net CO2 emissions per week to `simex/EMI_POLNA_S.gdx` (with `OUTPUT_SUMMARY`, on by default), and the rolling run limits each week to that value, so the weeks add up to the annual limit. Run the full year run right before the rolling run, with the same seasons and season weights. The rolling run stops with an error if `EMI_POLNA_S.gdx` has no weekly emissions for a year with a CO2 limit.

## Other options for operational runs
- **Unit commitment:** `$setglobal UnitComm yes` also works with `SOLVETYPE` `RMIP` or `LP`. The number of existing units is then GKFX divided by the unit size, and ramping is limited by the ramp rate on available capacity. `$setglobal PLANNED_MAINTENANCE yes` in the full year run optimises planned maintenance, and `$setglobal ADDPLANNEDMAINTENANCE yes` imports it in the rolling run.
- **Backup generation:** `ADDBACKUPGEN` adds expensive backup electricity, hydrogen and biomethane generation in the first area of every region, and backup heat in every area with heat demand.
- **Finding infeasibilities:** with capacities fixed, an operational run can be infeasible. `$setglobal vqdebug yes` adds penalised slack variables to the balance equations and CO2 limits, so the run solves and shows where it fails. `$setglobal EV_infeas yes` does the same for the EV state of charge.
- **Demand response:** with `DEMANDRESPONSE`, `ADDTECHDEV` fixes the demand response capacity from the investment run.
- **EVs:** the EV charging infrastructure from the investment run is fixed, and charging beyond it is penalised. `EV_normalization` is only needed when T does not cover all hours, so it can be turned off in the rolling run. Interseasonal EVs are linked from one week to the next, while intraseasonal EVs are cyclic within each week.

