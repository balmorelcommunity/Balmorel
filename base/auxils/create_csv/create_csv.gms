
* Set the full path for the input data to be used
$setglobal inputdata       "../../base/auxils/create_csv/input"
*!option set the full path like e.g.    C:/Balmorel/base/data
* Note: use double quotes around and no termination slash or backslash
* Note: the folder must exist

* Set the full path for the output data generated
$setglobal outputdata   "../../base/auxils/create_csv/output"

*Set the scenario name for input file
$setglobal input_name  "MainResults_2030"

*Set the scenario name for output files
$setglobal scenario_name  "ProjectBased_2030_full"


*Create CSV from MainResults.gdx
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/CapacityGeneration_%scenario_name%.csv symb=G_CAP_YCRAF format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/CapacityStorage_%scenario_name%.csv symb=G_STO_YCRAF format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/ProductionHourly_%scenario_name%.csv symb=PRO_YCRAGFST format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/ProductionYearly_%scenario_name%.csv symb=PRO_YCRAGF format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/FuelConsumptionHourly_%scenario_name%.csv symb=F_CONS_YCRAST format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/FuelConsumptionYearly_%scenario_name%.csv symb=F_CONS_YCRA format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/CapacityElectricityTransmission_%scenario_name%.csv symb=X_CAP_YCR format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/FlowElectricityHourly_%scenario_name%.csv symb=X_FLOW_YCRST format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/FlowElectricityYearly_%scenario_name%.csv symb=X_FLOW_YCR format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/EconomyGeneration_%scenario_name%.csv symb=ECO_G_YCRAG format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/EconomyElectricityTransmission_%scenario_name%.csv symb=ECO_X_YCR format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/ObjectiveFunction_%scenario_name%.csv symb=OBJ_YCR format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/PriceElectricityYearly_%scenario_name%.csv symb=EL_PRICE_YCR format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/PriceElectricityHourly_%scenario_name%.csv symb=EL_PRICE_YCRST format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/PriceHeatYearly_%scenario_name%.csv symb=H_PRICE_YCRA format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/PriceHeatHourly_%scenario_name%.csv symb=H_PRICE_YCRAST format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/DemandElectricityHourly_%scenario_name%.csv symb=EL_DEMAND_YCRST format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/DemandElectricityYearly_%scenario_name%.csv symb=EL_DEMAND_YCR format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/DemandHeatHourly_%scenario_name%.csv symb=H_DEMAND_YCRAST format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/DemandHeatYearly_%scenario_name%.csv symb=H_DEMAND_YCRA format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/EmissionsYearly_%scenario_name%.csv symb=EMI_YCRAG format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/CurtailmentHourly_%scenario_name%.csv symb=CURT_YCRAGFST format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/CurtailmentYearly_%scenario_name%.csv symb=CURT_YCRAGF format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/BalanceElectricityHourly_%scenario_name%.csv symb=EL_BALANCE_YCRST format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/BalanceHeatHourly_%scenario_name%.csv symb=H_BALANCE_YCRAST format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/CapacityHeatTransmission_%scenario_name%.csv symb=XH_CAP_YCA format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/FlowHeatHourly_%scenario_name%.csv symb=XH_FLOW_YCAST format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/FlowHeatYearly_%scenario_name%.csv symb=XH_FLOW_YCA format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/EconomyHeatTransmission_%scenario_name%.csv symb=ECO_XH_YCRA format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/CapacityH2Transmission_%scenario_name%.csv symb=XH2_CAP_YCR format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/FlowH2Hourly_%scenario_name%.csv symb=XH2_FLOW_YCRST format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/FlowH2Yearly_%scenario_name%.csv symb=XH2_FLOW_YCR format=csv
$call gdxdump %inputdata%/%input_name%.gdx output=%outputdata%/EconomyH2Transmission_%scenario_name%.csv symb=ECO_XH2_YCR format=csv


