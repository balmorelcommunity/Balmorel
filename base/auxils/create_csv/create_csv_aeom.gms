
* Set the full path for the input data to be used
$setglobal inputdata       "../../base/auxils/create_csv/input"
*!option set the full path like e.g.    C:/Balmorel/base/data
* Note: use double quotes around and no termination slash or backslash
* Note: the folder must exist

* Set the full path for the output data generated
$setglobal outputdata   "../../base/auxils/create_csv/output"

*Set the scenario name for input file
$setglobal input_name  "all_endofmodel"

*Set the scenario name for output files
$setglobal scenario_name  "2023_oct"


*Create CSV from MainResults.gdx
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/WND_VAR_T_%scenario_name%.csv symb=WND_VAR_T format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/SOLE_VAR_T_%scenario_name%.csv symb=SOLE_VAR_T format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/SOLH_VAR_T_%scenario_name%.csv symb=SOLH_VAR_T format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/DE_VAR_T_%scenario_name%.csv symb=DE_VAR_T format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/DH_VAR_T_%scenario_name%.csv symb=DH_VAR_T format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/DH_VAR_T_INDIVHEATING_%scenario_name%.csv symb=DH_VAR_T_INDIVHEATING format=csv