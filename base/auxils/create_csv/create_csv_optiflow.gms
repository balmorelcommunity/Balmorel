
* Set the full path for the input data to be used
$setglobal inputdata       "../../base/auxils/create_csv/input"
*!option set the full path like e.g.    C:/Balmorel/base/data
* Note: use double quotes around and no termination slash or backslash
* Note: the folder must exist

* Set the full path for the output data generated
$setglobal outputdata   "../../base/auxils/create_csv/output"

*Set the scenario name for input file
$setglobal input_name  "Optiflow_MainResults"

*Set the scenario name for output files
$setglobal scenario_name  "Test"


*Create CSV from MainResults.gdx
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/VFLOW_%scenario_name%.csv symb=VFLOW format=csv
