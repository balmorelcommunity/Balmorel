* File BalmorelBB4.inc for handling the Balbase4 model in Balmorel.
* First version 2009(hr) based on DTU Master project by Jesper Felstedt &QHYDROGEN_ Morten Middelboe Pedersen under supervision by Hans Ravn.
* Present version 20150428(hr), 20150430(Weiming), 20151217(hr), 20160810(hr), 20170419 (Juan and hr).
* Thanks to Weiming Xiong, Andreas von Recklinghausen and others for good contributions.

* The model is still under development.
* It will be available from www.balmorel.com under open source conditions.


* Efforts have been made to make a good model.
* However, most probably the model is incomplete and subject to errors.
* It is distributed with the idea that it will be usefull anyway,
* and with the purpose of getting the essential feedback,
* which in turn will permit the development of improved versions
* to the benefit of other user.
* Hopefully it will be applied in that spirit.

* All GAMS code of the Balmorel model is distributed under ICS license,
* see the license file in the base/model folder.


*-------------------------------------------------------------------------------
*-------------------------------------------------------------------------------
* Declarations and inclusion of data files:
*-------------------------------------------------------------------------------
*-------------------------------------------------------------------------------


*-------------------------------------------------------------------------------
*---- User defined SETS and ACRONYMS needed for data entry: --------------------
*-------------------------------------------------------------------------------

* Declarations: ----------------------------------------------------------------

* SETS:
* Geography related:
SET CCCRRRAAA         All geographical entities (CCC + RRR + AAA);
SET CCC(CCCRRRAAA)    "All Countries";
SET C(CCC)            "Countries in the simulation";
SET RRR(CCCRRRAAA)    "All regions";
SET AAA(CCCRRRAAA)    "All areas";
SET CCCRRR(CCC,RRR)   "Regions in countries";
SET RRRAAA(RRR,AAA)   "Areas in regions";
* The following three internal geography related sets are assigned in bb4datainc.inc:
SET IR(RRR)           "Regions in the simulation";
SET IA(AAA)           "Areas in the simulation";
SET ICA(CCC,AAA)      "Assignment of areas to countries in the simulation";
* Time related:
SET YYY               "All years";
SET SSS               "All seasons";
SET TTT               "All time periods";
SET Y(YYY)            "Years in the simulation";
SET S(SSS)            "Seasons in the simulation";
SET T(TTT)            "Time periods within the season in the simulation";
SET TWORKDAY(TTT)     "Time segments, T, in workdays";
SET TWEEKEND(TTT)     "Time segments, T, in weekends";
* Technology and fuel related:
SET GGG               "All generation technologies";
SET GDATASET          "Generation technology data";
SET FFF               "Fuels";
SET FDATASET          "Characteristics of fuels";
SET HYRSDATASET       "Characteristics of hydro reservoirs";
SET G(GGG)            "Generation technologies in the simulation";
SET AGKN(AAA,GGG)     "Areas for possible location of new technologies";
* Demand related:
SET DEUSER            "Electricity demand user groups. Set must include element RESE for holding demand not included in any other user group";
SET DHUSER            "Heat demand user groups. Set must include element RESH for holding demand not included in any other user group";
SET DF_QP             "Quantity and price information for elastic demands";
SET DEF               "Steps in elastic electricity demand";
SET DEF_D1(DEF)       "Downwards steps in elastic el. demand, relative data format";
SET DEF_U1(DEF)       "Upwards steps in elastic el. demand, relative data format";
SET DEF_D2(DEF)       "Downwards steps in elastic el. demand, absolute Money and MW-incremental data format";
SET DEF_U2(DEF)       "Upwards steps in elastic el. demand, absolute Money and MW-incremental data format";
SET DEF_D3(DEF)       "Downwards steps in elastic el. demand, absolute Money and fraction of nominal demand data format";
SET DEF_U3(DEF)       "Upwards steps in elastic el. demand, absolute Money and fraction of nominal demand data format";
SET DHF               "Steps in elastic heat demand";
SET DHF_D1(DHF)       "Downwards steps in elastic heat demand, relative data format";
SET DHF_U1(DHF)       "Upwards steps in elastic heat demand, relative data format";
SET DHF_D2(DHF)       "Downwards steps in elastic heat demand, absolute Money and MW-incremental data format";
SET DHF_U2(DHF)       "Upwards steps in elastic heat demand, absolute Money and MW-incremental data format";
SET DHF_D3(DHF)       "Downwards steps in elastic heat demand, absolute Money and fraction of nominal demand data format";
SET DHF_U3(DHF)       "Upwards steps in elastic heat demand, absolute Money and fraction of nominal demand data format";

SET MPOLSET           "Emission and other policy data";
SET ECONSET           "Set for econ"  !! todo
SET ECONSETCATEGORY   "Set for econ"  !! todo

* Internal set IGGGALIAS may be used in the $included data files:
ALIAS(GGG,IGGGALIAS);
* Internal set IGALIAS may be used in the $included data files:
ALIAS(G,IGALIAS);
* Set CCCRRRAAAALIAS may be used in the $included data files:
ALIAS(CCCRRRAAA,CCCRRRAAAALIAS);

* ACRONYMS:
* ACRONYMS for technology types
* Each of the following ACRONYMS symbolise a technology type.
* They correspond in a one-to-one way with the internal sets IGCND, IGBRP etc. below.
* They should generally not be changed.
* New technology types may be added only if also code specifying their properties are added.
ACRONYMS  GCND, GBPR, GEXT, GHOB, GETOH, GHSTO, GESTO, GHSTOS, GESTOS, GHYRS, GHYRR, GWND, GSOLE, GSOLH, GWAVE, GHS;

* ACRONYMS for user defined fuels will be given as part of file FFF.inc
* ACRONYMS for other purposes are defined in ACRONYMS.inc

*-------------------------------------------------------------------------------
*----- Definitions of SETS and ACRONYMS that are given in the $included files:
*-------------------------------------------------------------------------------
* Printing of data to the list file controlled by %ONOFFDATALISTING% and %ONOFFCODELISTING%
* (see file balgams.opt):


* Printing of data to the list file controlled by %ONOFFDATALISTING% and %ONOFFCODELISTING%
* (see file balgams.opt):
%ONOFFCODELISTING%

*-------------------------------------------------------------------------------
*--- End: Definitions of SETS and ACRONYMS that are given in the $included files
*-------------------------------------------------------------------------------

SET IS3(S)     "Balbase3: present season simulated; other models: identical to S";
SET IS3_NEXT(S) "Present seasons and  next season not simulated; if rolling seasons not activated  identical to S";
SET IS3_ONLYNEXT(S) "Next season not simulated; if rolling seasons not activated identical to S";
SET IS33(S,S)  "Mapping of S (first index) to the following S (second index)";

*-------------------------------------------------------------------------------
*----- Definitions of SETS and ALIASES that are needed for data entry:
*-------------------------------------------------------------------------------

* Duplication of sets for describing electricity exchange between regions:
ALIAS (C,IC);
ALIAS (RRR,IRRRE,IRRRI);
ALIAS (IR,IRE,IRI);
ALIAS (IA,IAE,IAI);
* Duplication of sets for fuel.
ALIAS (FFF,IFFFALIAS);
ALIAS (FFF,IFFFALIAS2);

* Duplication of sets for seasons and hours:
ALIAS (YYY,IYYYALIAS);
ALIAS (YYY,IYYYALIAS2);
ALIAS (Y,IYALIAS);
ALIAS (Y,IYALIAS2);
ALIAS (SSS,ISSSALIAS);
ALIAS (TTT,ITTTALIAS);
ALIAS (S,ISALIAS,ISALIAS2,ISALIAS3,IS3LOOPSET);
ALIAS (T,ITALIAS,ITALIAS2,ITALIAS3);


*-------------------------------------------------------------------------------
*----- End: Definitions of SETS and ALIASES that are needed for data entry:
*-------------------------------------------------------------------------------


*-------------------------------------------------------------------------------
* The choice of model made in the balopt.opt fil is checked here,
* and basic sets concerning time within the year are reconstructed accordingly if needed:

$ifi %bb3%==yes $KILL T
$ifi %bb3%==yes SET T(TTT)          /T001*T168/;
$ifi %bb3%==yes $KILL TWORKDAY
$ifi %bb3%==yes $KILL TWEEKEND
$ifi %bb3%==yes SET TWORKDAY(TTT)   /T001*T120/;
$ifi %bb3%==yes SET TWEEKEND(TTT)   /T121*T168/;
*-------------------------------------------------------------------------------


*------------------------------------------------------------------------------
* End: Declaration of internal sets
*------------------------------------------------------------------------------


*------------------------------------------------------------------------------
* Declaration and definition of numerical data: PARAMETERS and SCALARS:
*------------------------------------------------------------------------------


*------------------------------------------------------------------------------
*---- Technology data: ---------------------------------------------------------
*------------------------------------------------------------------------------
PARAMETER GDATA(GGG,GDATASET)    "Technologies characteristics";


*-------------------------------------------------------------------------------
* Definitions of internal sets relative to technologies,
* The sets are defined based on information in PARAMETER GDATA.

* The following are convenient internal subsets of generation technologies:

SET IGCND(G)               "Condensing technologies";                           !! Corresponding to acronym GCND
SET IGBPR(G)               "Back pressure technologies";                        !! Corresponding to acronym GBPR
SET IGEXT(G)               "Extraction technologies";                           !! Corresponding to acronym GEXT
SET IGHOB(G)               "Heat-only boilers";                                 !! Corresponding to acronym GHOB
SET IGHS(G)				   "Heat savings";										!! Corresponding to acronym GHS
SET IGETOH(G)              "Electric heaters, heatpumps, electrolysis plants";  !! Corresponding to acronym GETOH
SET IGHSTO(G)              "Intra-seasonal heat storage technologies";          !! Corresponding to acronym GHSTO
SET IGHSTOS(G)             "Inter-seasonal heat storage technologies";          !! Corresponding to acronym GHSTOS
SET IGHSTOALL(G)           "All heat storage technologies (intra- plus inter-seasonal)";
SET IGESTO(G)              "Intra-seasonal electricity storage technologies";   !! Corresponding to acronym GESTO
SET IGESTOS(G)             "Inter-seasonal electricity storage technologies";   !! Corresponding to acronym GESTOS
SET IGESTOALL(G)           "All electricity storage technologies (intra- plus inter-seasonal)";
SET IGHYRS(G)              "Hydropower with reservoir";                         !! Corresponding to acronym GHYRS
SET IGHYRR(G)              "Hydropower run-of-river no reservoir";              !! Corresponding to acronym GHYRR
SET IGWND(G)               "Wind power technologies";                           !! Corresponding to acronym GWND
SET IGSOLE(G)              "Solar electrical power technologies";               !! Corresponding to acronym GSOLE
SET IGSOLH(G)              "Solar heat technologies";                           !! Corresponding to acronym GSOLH
SET IGVRE(G)                            "VRE technologies";
SET IGWAVE(G)              "Wave power technologies";                           !! Corresponding to acronym GWAVE
SET IGHH(G)                "Technologies generating heat-only";
SET IGHHNOSTO(G)           "Technologies generating heat-only, except storage";
SET IGNOTETOH(G)           "Technologies excluding electric heaters, heat pumps,electrolysis plants";
SET IGKH(G)                "Technologies with capacity specified on heat";
SET IGKHNOSTO(G)           "Technologies with capacity specified on heat, except storage";
SET IGKE(G)                "Technologies with capacity specified on electricity";
SET IGKENOSTO(G)           "Technologies with capacity specified on electricity, except storage";
SET IGDISPATCH(G)          "Dispatchable technologies";
SET IGEE(G)                "Technologies generating electricity only";
SET IGEENOSTO(G)           "Technologies generating electricity only, except storage (but includes hydro)";
SET IGKKNOWN(G)            "Technoloies for which the capacity is specified by the user";
SET IGKFIND(G)             "Technologies for which the capacity is found by algorithm as endogenous investments";
SET IGEH(G)                "Technologies generating electricity and heat";
SET IGE(G)                 "Technologies generating electricity";
SET IGH(G)                 "Technologies generating heat";
SET IGBYPASS(G)            "Technologies that may apply turbine bypass mode (subject to option bypass)";
SET IWATERTANK(G)          "Water tank intra-seasonal LARGE heat storage technology"; !! Corresponding to acronym WATERTANK
SET IPIT(G)                "Pit inter-seasonal heat storage technology";        !! Corresponding to acronym PIT
SET IHEATPUMP(G)           "Heatpump technology";                               !! Corresponding to acronym HEATPUMP
SET IHEATPUMPAIR(G)        "Air source heat pump technolgy";         !! Corresponding to acronym HEATPUMP_AIR
SET IHEATPUMPEXCESSHEAT(G) "Excess heat source heat pump technolgy"; !! Corresponding to acronym HEATPUMP_EXCESSHEAT
SET IHEATPUMPGROUND(G)     "Ground source heat pump technolgy";      !! Corresponding to acronym HEATPUMP_GROUND
SET IGHNOWT(G)             "Technologies that are not allowed to load specifically water tanks";
SET ILINKSTO(G,G)          "1st set: Heat storage, 2nd set: technologies allowed to load the storage";


*-------------------------------------------------------------------------------
*----- Any internal sets assignments for addon to be placed here: --------------
*-------------------------------------------------------------------------------
* NOTE: When making new generation technology types. Some add-ons may already
* be using values of GDATA(G,'GDTYPE'). Check addons referenced here to maximize
* consistency and avoid conflicts. It is encouraged to avoid using the '-' set
* operator and instead use the '+' operator for compound assignments.
* NOTE: isetdecdef.inc is loaded later


*-------------------------------------------------------------------------------
*----- End: Any internal sets assignments for addon to be placed here ----------
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
*---- End: Technology data -----------------------------------------------------
*-------------------------------------------------------------------------------

* Printing of data to the list file controlled by %ONOFFDATALISTING% and %ONOFFCODELISTING%:
%ONOFFDATALISTING%

PARAMETER GKFX(YYY,AAA,GGG)    "Capacity of exogenously given generation technologies (MW except for storages, where it is MWh)";
* Printing of data to the list file controlled by %ONOFFDATALISTING% and %ONOFFCODELISTING%:
%ONOFFCODELISTING%

*-------------------------------------------------------------------------------
*---- Declaration of parameters for "export_results"  -----------------------------------------------
*-------------------------------------------------------------------------------
* Data for handling of annual hydro constraints in future runs:
PARAMETER HYRSG(YYY,AAA,SSS)        "Water (hydro) generation quantity of the seasons to be transferred to future runs (MWh)";
PARAMETER VHYRS_SL(YYY,AAA,SSS)       "To be saved for comparison with BB1/BB2 solution value for VHYRS_S.L (initial letter is V although declared as a parameter) (MWh)";
PARAMETER WATERVAL(YYY,AAA,SSS)     "Water value (in input Money) to be transferred to future runs (input-Money/MWh)";
PARAMETER VHYRS_STL(YYY,AAA,SSS,TTT)  "Hourly hydro storage level (MWh)";
* Data for handling investments in future runs:
PARAMETER GKACCUMNET(YYY,AAA,GGG) "Resulting technology capacity development at end of (ULTimo) previous (i.e., start of current) year (MW) (MWh for storage) to be transferred to future runs";
PARAMETER XKACCUMNET(YYY,IRRRE,IRRRI) "Resulting transmission capacity development at end (MISSING: minus any decommissioning of them due to lifetime expiration) this BB4, at end of previous (i.e., available at start of current) year (MW) to be transferred to future runs";

* Data for handling storage
PARAMETER ESTOVOLTS(YYY,AAA,GGG,SSS,TTT) "Inter-seasonal Electricity storage contents at beginning of time segment (MWh) to be transferred to future runs (MWh)";
PARAMETER HSTOVOLTS(YYY,AAA,GGG,SSS,TTT) "Inter-seasonal Heat storage contents at beginning of time segment (MWh) to be transferred to future runs (MWh)";
PARAMETER ESTOVOLT(YYY,AAA,GGG,SSS,TTT) "Intra-seasonal Electricity storage contents at beginning of time segment (MWh) to be transferred to future runs (MWh)";
PARAMETER HSTOVOLT(YYY,AAA,GGG,SSS,TTT) "Intra-seasonal Heat storage contents at beginning of time segment (MWh) to be transferred to future runs (MWh)";
PARAMETER ESTOLOADT(YYY,AAA,GGG,SSS,TTT) "Intra-seasonal electricity storage loading to be transferred to future runs (MW)";
PARAMETER ESTOLOADTS(YYY,AAA,GGG,SSS,TTT) "Inter-seasonal electricity storage loading to be transferred to future runs (MW)";;
PARAMETER HSTOLOADT(YYY,AAA,GGG,SSS,TTT)  "Intra-seasonal heat storage loading to be transferred to future runs (MW)";
PARAMETER HSTOLOADTS(YYY,AAA,GGG,SSS,TTT) "Inter-seasonal heat storage loading to be transferred to future runs (MW)";
PARAMETER ESTOVOLTSVAL(YYY,AAA,GGG,SSS,TTT) "Inter-seasonal Electricity storage content  value (in input money) to be transferred to future runs (input-Money/MWh)";
PARAMETER HSTOVOLTSVAL(YYY,AAA,GGG,SSS,TTT) "Inter-seasonal Heat storage content value (in input money) to be transferred to future runs (input-Money/MWh)";
PARAMETER ESTOVOLTVAL(YYY,AAA,GGG,SSS,TTT) "Intra-seasonal Electricity storage content  value (in input money) to be transferred to future runs (input-Money/MWh)";
PARAMETER HSTOVOLTVAL(YYY,AAA,GGG,SSS,TTT) "Intra-seasonal Heat storage content value (in input money) to be transferred to future runs (input-Money/MWh)";

* Data for handling remaining energy dispatch
PARAMETER  DE_T(YYY,RRR,SSS,TTT)                 "Electricity demand (MW) to be transferred to future runs";
PARAMETER  DH_T(YYY,AAA,SSS,TTT)                 "Heat demand (MW) to be transferred to future runs";
PARAMETER  GE_T(YYY,AAA,GGG,SSS,TTT)               "Electricity generation (MW)  to be transferred to future runs";
PARAMETER  GH_T(YYY,AAA,GGG,SSS,TTT)               "Heat generation (MW)  to be transferred to future runs";
PARAMETER  GF_T(YYY,AAA,GGG,SSS,TTT)               "Fuel consumption rate (MW), existing units  to be transferred to future runs";
PARAMETER  X_T(YYY,IRRRE,IRRRI,SSS,TTT)          "Electricity export from region IRRRE to IRRRI to be transferred to future runs (MW)";

*Fuel use
PARAMETER F_T(YYY,CCCRRRAAA,FFF,SSS,TTT) "Aggregated fuel use by year, season, T, geography and fuel to b transferred to future runs (GJ)"

*Fuel price
PARAMETER FUELPRICE_EXC(YYY,AAA,FFF)             "Fuel prices to be transferred to future runs(Money/GJ)";

*-------------------------------------------------------------------------------
*---- End: Declaration of parameters for "export_results"  -----------------------------------------------
*-------------------------------------------------------------------------------

* All remaining (cf. ... .inc above) data files af included from the following file
$ifi     exist "bb4datainc.inc" $include                   "bb4datainc.inc";
$ifi not exist "bb4datainc.inc" $include  "../../base/model/bb4datainc.inc";

* Save GDATA as csv, because it has string values that are converted to large integers
execute_unload 'GDATA.gdx', GDATA;
$call gdxdump GDATA.gdx output=GDATA.csv symb=GDATA format=csv
