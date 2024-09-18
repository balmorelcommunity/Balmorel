# Scenario Setup
Lets start by learning how to execute Balmorel using a small test scenario. Create a new folder in the level of the base folder, a new data and model folder inside of this and copy and paste the Balmorel.gms, balopt.opt and cplex.op4 folder from base/model. If you want to call this scenario "test_run" the folder structure should now look like the following:
```bash
Balmorel
├── base
├── test_run
│   ├── data 
│   └── model
│       ├── cplex.op4
│       ├── balopt.opt
│       └── Balmorel.gms
└── simex
``` 
Lets decrease the temporal resolution significantly, so Balmorel will solve within a minute and we can verify our setup. We can do this by creating a new T.inc file in test_run/data, with the following contents:
```GAMS
SET T(TTT)  'Time periods within a season in the simulation'
/
T001, T005, T009, T013, T017, T021
/;
```
This corresponds to selecting hours 00:00, 04:00, 08:00, 12:00, 16:00 and 20:00 on a monday.

Now, create a new S.inc file in test_run/data with the following content:
```GAMS
SET S(SSS)  'Seasons in the simulation'
/  
S14
/; 
```
This corresponds to selecting week 14 in a year.



To setup Balmorel in GAMS Studio, you can drag and drop the Balmorel.gms into GAMS Studio to create a correctly setup project.
 
