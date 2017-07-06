* File error1.inc

* This file is part of the Balmorel model, version 2.10 Alpha (May 2003).

* File last time modified 13-05-2003 (hrv), 20080414(hr)


* This file initiates check on the data and solution of the model.


* Output related to errors in data and solution.
* This file will contain information about errors in input data, if any:
FILE ERRORFILE         /..\LogError\errors.out/;
if ((ERRORFILE.pw LT 32000),
ERRORFILE.pw = 32000;
PUT ERRORFILE;
PUT "File errors.out: Detailed description of Balmorel errors."/;
PUT "Version:      " SYSTEM.TITLE /;
PUT "File created: " SYSTEM.DATE " " SYSTEM.TIME //;
);

* This file will contain a summary of the information in the file ERRORS.OUT,
* and about the solver status for each year of the simulation
* including the objective function value:

FILE logfile          /..\LogError\logfile.out/;
if ((logfile.pw LT 32000),
logfile.pw = 32000;
PUT logfile;
PUT "File logfile.out."/;
PUT "Version:      " SYSTEM.TITLE /;
PUT "Log created: " SYSTEM.DATE " " SYSTEM.TIME //;
);


* Initialisation of auxiliary variables:
* (No errcount1)
SCALAR ERRCOUNT2 "Error count 2" /0/;
SCALAR ERRCOUNT3 "Error count 3" /0/;
SCALAR ERRCOUNT4 "Error count 4" /0/;

* Scalar to any use:
SCALAR ERRSCALAR1 "Error count to any use";
* Subset of GGG to any use:
SET ERRSETGGG(GGG) "Subset of GGG to any use";