* File error1.inc

* This file is part of the Balmorel model.

* File last time modified 13-05-2003 (hrv), 20080414(hr), 20120914(hr), 20160824(hr)


* This file initiates check on the data and solution of the model.


* Output related to errors in data and solution.
* This file will contain information about errors in input data, if any:
FILE errorfile         /..\logerror\errors.out/;
if ((ERRORFILE.pw LT 32000),
ERRORFILE.pw = 32000;
PUT ERRORFILE;
PUT "File errors.out: Detailed description of Balmorel errors."/;
PUT "Version:      " SYSTEM.TITLE /;
PUT "The applied GAMS release is " (system.gamsrelease):5 " and the applied GAMS version is " (system.gamsversion):6 /;
PUT "File created: " SYSTEM.DATE " " SYSTEM.TIME //;
);

* This file will contain a summary of the information in the file ERRORS.OUT,
* and about the solver status for each year of the simulation
* including the objective function value:

FILE logfile          /..\logerror\logfile.out/;
if ((logfile.pw LT 32000),
logfile.pw = 32000;
PUT logfile;
PUT "File logfile.out."/;
PUT "Version:      " SYSTEM.TITLE /;
PUT "The applied GAMS release is " (system.gamsrelease):5 " and the applied GAMS version is " (system.gamsversion):6 /;
PUT "Log created: " SYSTEM.DATE " " SYSTEM.TIME //;
);


* ------------------------------------------------------------------------------
* Include information on applied models, addons and options
put "* ------------------------------------------------------------------------------" /;
*put "The following addons are applied in the present model instance"/;
*$ifi     exist '..\addons\hellolog.inc'  $include  'hellolog.inc';
*$ifi not exist 'hellolog.inc'  $include  '../../base/addons/hellolog.inc'
$include "../../base/addons/_hooks/hellolog.inc"
put "* ------------------------------------------------------------------------------" /;
* ------------------------------------------------------------------------------


* Initialisation of auxiliary variables:
* (No errcount1)
SCALAR ERRCOUNT2 "Error count 2" /0/;
SCALAR ERRCOUNT3 "Error count 3" /0/;
SCALAR ERRCOUNT4 "Error count 4" /0/;

* Scalar to any use:
SCALAR ERRSCALAR1 "Error count to any use";
