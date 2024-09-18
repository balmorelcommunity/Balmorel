# Scenario Setup
Lets start by learning how to execute Balmorel using a small test scenario. Create a new folder in the level of the base folder, a new data and model folder inside of this and copy and paste the Balmorel.gms and cplex.op4 folder from base/model. If you want to call this scenario "test_run" the folder structure should now look like the following:
```bash
Balmorel
├── base
├── test_run
│   ├── data 
│   └── model
│       ├── cplex.op4
│       └── Balmorel.gms
└── simex
``` 

This is how to setup different scenarios in Balmorel. The framework will first attempt to look for files in the test_run, and then in the base folder if the required file did not exist. This means you do not have to copy paste all of the data in base/data everytime you make a new scenario, but can simply add the *changed* data. We will do this below.  

## Prepare Scenario Data
Lets decrease the temporal resolution significantly, so Balmorel will solve within a minute and we can verify our setup. We can do this by creating a new T.inc file in test_run/data. In GAMS Studio, press File/New..., find the test_run/data folder and save as type "GAMS Include files (*.inc)". Copy and paste the contents to this file below:
```gams
SET T(TTT)  'Time periods within a season in the simulation'
/
T001, T005, T009, T013, T017, T021
/;
```
This corresponds to selecting hours 00:00, 04:00, 08:00, 12:00, 16:00 and 20:00 on a monday.

Now, create a new S.inc file in test_run/data with the following content:
```gams
SET S(SSS)  'Seasons in the simulation'
/  
S14
/; 
```
This corresponds to selecting week 14 in a year.

We are now ready to run Balmorel, see the next page.