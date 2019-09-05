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
SET CCCRRRAAA         All geographical entities (CCC + RRR + AAA)';
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
ACRONYMS  GCND, GBPR, GEXT, GHOB, GETOH, GHSTO, GESTO, GHSTOS, GESTOS, GHYRS, GHYRR, GWND, GSOLE, GSOLH, GWAVE;

*ACRONYMS for tech groups
* They can be used for multiple purposes
* They should generally not be changed.
* New technology types may be added only if also code specifying their properties are added.
ACRONYMS STEAMTURBINE_SUBCRITICAL, STEAMTURBINE_SUPERCRITICAL, RESERVOIR_PMP, WATERTURBINE, ENGINE_IC, BOILER, COMBINEDCYCLE, EXCESS_HEAT, ELECTRICITY_BATTERY, GEOTHERMAL,
GASTURBINE, DUMMY, HEATPUMP, PIT, WATERTANK, SOLARPV, SOLARHEATING,WINDTURBINE_ONSHORE, WINDTURBINE_OFFSHORE;

*ACRONYMS for subtech groups
* They can be used for multiple purposes
* They should generally not be changed.
* New technology types may be added only if also code specifying their properties are added.
ACRONYMS RG1,RG2,RG3,RG1_OFF1,RG2_OFF1,RG3_OFF1,RG1_OFF2,RG2_OFF2,RG3_OFF2,RG1_OFF3,RG2_OFF3,RG3_OFF3,RG1_OFF4,RG2_OFF4,RG3_OFF4,RG1_OFF5,RG2_OFF5,RG3_OFF5,AIR,EXCESSHEAT,GROUND,HUB_OFF;

* ACRONYMS for user defined fuels will be given as part of file FFF.inc

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
SET IS33(S,S)  "Mapping of S (first index) to the following S (second index)";
SET SREV(S,S)  "Mapping of S (first index) to its reverse element S (second index)";
SET SREV2(S,S) "Mapping of S (first index) to its reverse element S (second index)";;
SET TREV(T,T)  "Mapping of T (first index) to its reverse element T (second index)";;
SET TREV2(T,T) "Mapping of T (first index) to its reverse element T (second index)";;

*-------------------------------------------------------------------------------
*----- Definitions of SETS and ALIASES that are needed for data entry:
*-------------------------------------------------------------------------------

* Duplication of sets for describing electricity exchange between regions:
ALIAS (RRR,IRRRE,IRRRI);
ALIAS (IR,IRE,IRI);
* Duplication of sets for fuel.
ALIAS (FFF,IFFFALIAS);
ALIAS (FFF,IFFFALIAS2);

* Duplication of sets for seasons and hours:
ALIAS (YYY,IYYYALIAS);
ALIAS (YYY,IYYYALIAS2);
ALIAS (Y,IYALIAS);
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

*-------------------------------------------------------------------------------
*---- Annually specified generation capacities: --------------------------------
*-------------------------------------------------------------------------------

* Printing of data to the list file controlled by %ONOFFDATALISTING% and %ONOFFCODELISTING%:
%ONOFFDATALISTING%

PARAMETER GKFX(YYY,AAA,GGG)    "Capacity of exogenously given generation technologies (MW)";
* Printing of data to the list file controlled by %ONOFFDATALISTING% and %ONOFFCODELISTING%:
%ONOFFCODELISTING%

*-------------------------------------------------------------------------------
*---- End: Annually specified generation capacities ----------------------------
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
*---- Geographically specific values: -----------------------------------------
*-------------------------------------------------------------------------------

PARAMETER YVALUE(YYY)                  "Numerical value of the years labels";
PARAMETER IWEIGHTY(Y)                  "Relative weight of the individual years in Y";
PARAMETER FDATA(FFF,FDATASET)          "Fuel specific values";

PARAMETER FMAXINVEST(CCC,FFF)          "Maximum investment by country and fuel type for each year simulated (MW)";
PARAMETER FMAXINVESTNA(YYY,FFF)        "Maximum investment by year and fuel type for each year simulated (MW)(aggregated countries)"; !! not really used presently
PARAMETER GROWTHCAPCG(C,GGG)           "Maximum model generated capacity increase from one year to the next (MW)";

PARAMETER DISLOSS_E(RRR)               "Loss in electricity distribution (fraction)";
PARAMETER DISLOSS_H(AAA)               "Loss in heat distribution (fraction)";
PARAMETER DISCOST_E(RRR)               "Cost of electricity distribution (Money/MWh)";
PARAMETER DISCOST_H(AAA)               "Cost of heat distribution (Money/MWh)";
PARAMETER FKPOT(CCCRRRAAA,FFF)         "Fuel potential restriction by geography (default 0 implies irrelevant, EPS implies no potential) (MW)";
PARAMETER FGEMIN(CCCRRRAAA,FFF)        "Minimum electricity generation by fuel (default 0 implies irrelevant, EPS implies no potential) (MWh)";
PARAMETER FGEMAX(CCCRRRAAA,FFF)        "Maximum electricity generation by fuel (default 0 implies irrelevant, EPS implies no potential) (MWh)";


PARAMETER FKMIN(YYY,CCCRRRAAA,FFF)     "Minimum capacity by fuel per year (MW)"  !! not really used presently
PARAMETER FKMAX(YYY,CCCRRRAAA,FFF)     "Maximum capacity by fuel per year (MW)"  !! not really used presently
PARAMETER FKEQ(YYY,CCCRRRAAA,FFF)      "Exact capacity by fuel per year (MW)"    !! not really used presently !! According to QKMINFx it is not ELECTRICITY, so the test was changed. Also, I think "required" is ambigous.  TODO
* Aggerated countries:
PARAMETER FKMINNA(YYY,FFF)             "Minimum capacity by fuel per year (MW)"  !! not really used presently
PARAMETER FKMAXNA(YYY,FFF)             "Maximum capacity by fuel per year (MW)"  !! not really used presently
PARAMETER FKEQNA(YYY,FFF)              "Exact capacity by fuel per year (MW)"    !! not really used presently

$ifi %GMINF_DOL%==CCCRRRAAA_FFF         PARAMETER GMINF(CCCRRRAAA,FFF)             "Minimum annual (any year) fuel use by geography and fuel and (default 0 implies irrelevant, EPS implies no potential) (GJ)";
$ifi %GMINF_DOL%==YYY_CCCRRRAAA_FFF     PARAMETER GMINF(YYY,CCCRRRAAA,FFF)         "Minimum annual fuel use by year, geography and fuel and (default 0 implies irrelevant, EPS implies no potential) (GJ)";
$ifi %GMAXF_DOL%==CCCRRRAAA_FFF         PARAMETER GMAXF(CCCRRRAAA,FFF)             "Maximum annual (any year) fuel use by geography and fuel and (default 0 implies irrelevant, EPS implies no potential) (GJ)";
$ifi %GMAXF_DOL%==YYY_CCCRRRAAA_FFF     PARAMETER GMAXF(YYY,CCCRRRAAA,FFF)         "Maximum annual fuel use by year, geography and fuel and (default 0 implies irrelevant, EPS implies no potential) (GJ)";
$ifi %GEQF_DOL%==CCCRRRAAA_FFF          PARAMETER GEQF(CCCRRRAAA,FFF)              "Exact annual (any year) fuel use by geography and fuel (default 0 implies irrelevant, EPS implies no potential) (GJ)";
$ifi %GEQF_DOL%==YYY_CCCRRRAAA_FFF      PARAMETER GEQF(YYY,CCCRRRAAA,FFF)          "Exact annual fuel use by year, geography and fuel and (GJ)";
PARAMETER WTRRSFLH(AAA)                "Full load hours for hydro reservoir plants (hours)";
PARAMETER WTRRRFLH(AAA)                "Full load hours for hydro run-of-river plants (hours)";
$ifi %WNDFLH_DOL%==AAA                  PARAMETER WNDFLH(AAA)                      "Full load hours for wind power (hours)";
$ifi %WNDFLH_DOL%==AAA_GGG              PARAMETER WNDFLH(AAA,GGG)                  "Full load hours for wind power (hours)";
$ifi %SOLEFLH_DOL%==AAA                 PARAMETER SOLEFLH(AAA)                     "Full load hours for solarE power (hours)";
$ifi %SOLEFLH_DOL%==AAA_GGG             PARAMETER SOLEFLH(AAA,GGG)                 "Full load hours for solarE power (hours)";
$ifi %SOLHFLH_DOL%==AAA                 PARAMETER SOLHFLH(AAA)                     "Full load hours for solarH power (hours)";
$ifi %SOLHFLH_DOL%==AAA_GGG             PARAMETER SOLHFLH(AAA,GGG)                 "Full load hours for solarH power (hours)";
$ifi %GWAVE_DOL%==AAA                   PARAMETER WAVEFLH(AAA)                     "Full load hours for wave power";
$ifi %GWAVE_DOL%==AAA_GGG               PARAMETER WAVEFLH(AAA,GGG)                 "Full load hours for wave power";
PARAMETER HYRSMAXVOL_G(AAA,GGG)        "Reservoir capacity (MWh storage capacity / MW installed capacity)";
PARAMETER HYRSDATA(AAA,HYRSDATASET,SSS)"Data for hydro with storage ( *)";
$ontext
PARAMETER TAX_FHO(YYY,AAA,G)           "Fuel taxes on heat-only units (Money/GJ)";
PARAMETER TAX_FHO_C(FFF,CCC)           "Fuel taxes on heat-only units (Money/GJ)";
PARAMETER TAX_GH(YYY,AAA,G)            "Heat taxes on generation units (Money/GJ)";
PARAMETER TAX_FCHP_C(FFF,CCC)          "Fuel taxes on CHP units (Money/GJ)";
PARAMETER TAX_HHO_C(FFF,CCC)           "Fuel taxes on HO units (Money/GJ)";
PARAMETER TAX_F(FFF,CCC)               "Fuel taxes for heat and electricity production (Money/GJ)";
PARAMETER TAX_DE(CCC,DEUSER)           "Consumers tax on electricity consumption (Money/MWh)";
PARAMETER TAX_DH(CCC,DHUSER)           "Consumers tax on heat consumption (Money/MWh)";
$offtext

PARAMETER ANNUITYCG(CCC,GGG)           "Transforms investment in technologies into annual payment (fraction)";
PARAMETER ANNUITYCX(CCC)               "Transforms investment in transmission lines into annual payment (fraction)";

SCALAR    LIFETIME_X                   "Lifetime of transmission lines (years)";
SCALAR    DISCOUNTRATE                 "Discount rate (applied to all terms in the objective function) (fraction)";
PARAMETER GINVCOST(AAA,GGG)            "Investment cost for new technology (overwriting default value GDATA(G,'GDINVCOST0') if non-zero or EPS in data file) (MMoney/MW)";
PARAMETER GOMVCOSTO(AAA,GGG)           "Variable operating and maintenance costs relative to the output (overwriting default value GDATA(G,'GDOMVCOST0') if non-zero or EPS in data file) (Money/MWh)";
PARAMETER GOMVCOSTIN(AAA,GGG)          "Variable operating and maintenance costs relative to the input (overwriting default value GDATA(G,'GDOMVCOST0') if non-zero or EPS in data file) (Money/MWh)";
PARAMETER GOMFCOST(AAA,GGG)            "Annual fixed operating costs (overwriting default value GDATA(G,'GOMFCOST0') if non-zero or EPS in data file) (kMoney/MW)";
PARAMETER GEFFRATE(AAA,GGG)            "Fuel efficiency rating (strictly positive, typically close to 1; default/1/, use eps for 0)";
PARAMETER DEFP_BASE(RRR)               "Nominal annual average consumer electricity price (Money/MWh)";
PARAMETER DHFP_BASE(AAA)               "Nominal annual average consumer heat price (Money/MWh)";

PARAMETER DE(YYY,RRR,DEUSER)           "Annual electricity consumption (MWh)";
PARAMETER DH(YYY,AAA,DHUSER)           "Annual heat consumption (MWh)";

*---- Transmission data: -------------------------------------------------------
PARAMETER XKFX(YYY,IRRRE,IRRRI)        "Capacity of exogenously given transmission capacity between regions (MW)";
PARAMETER XINVCOST(YYY,IRRRE,IRRRI)    "Investment cost in new transmission capacity, default: INF or 0: no investment, EPS or positive: possible with stated cost (Money/MW)";
PARAMETER XCOST(IRRRE,IRRRI)           "Transmission cost between regions (Money/MWh)";
PARAMETER XLOSS(IRRRE,IRRRI)           "Transmission loss between regions (fraction)";

$ifi %XKRATE_DOL%==IRRRE_IRRRI          PARAMETER XKRATE(IRRRE,IRRRI)         "Transmission capacity rating (share; non-negative, typically close to 1; default/1/, use eps for 0)";
$ifi %XKRATE_DOL%==IRRRE_IRRRI_SSS      PARAMETER XKRATE(IRRRE,IRRRI,SSS)     "Transmission capacity rating (share; non-negative, typically close to 1; default/1/, use eps for 0)";
$ifi %XKRATE_DOL%==IRRRE_IRRRI_SSS_TTT  PARAMETER XKRATE(IRRRE,IRRRI,SSS,TTT) "Transmission capacity rating (share; non-negative, typically close to 1; default/1/, use eps for 0)";

* Fuel prices: -----------------------------------------------------------------

PARAMETER M_POL(YYY,MPOLSET,CCC)                   "Emission policy data; default for the 'LIM_' entries: 0 implies irrelevant, EPS implies no emission permitted";
PARAMETER M_POLNA(YYY,MPOLSET)                     "Emission policy data; default for the 'LIM_' entries: 0 implies irrelevant, EPS implies no emission permitted (aggregated countries)";   !! not really used presently

* Time series on (SSS,TTT):
PARAMETER WEIGHT_S(SSS)                            "Weight (relative length) of each season";
PARAMETER WEIGHT_T(TTT)                            "Weight (relative length) of each time period";
PARAMETER CHRONOHOUR(S,T)                          "Meaning/size of each time step in each season (1 means 1 hour)";

$ifi %GKRATE_DOL%==AAA_GGG_SSS     PARAMETER GKRATE(AAA,GGG,SSS)      "Capacity rating (non-negative, typically close to 1; default/1/, use eps for 0)";
$ifi %GKRATE_DOL%==AAA_GGG_SSS_TTT PARAMETER GKRATE(AAA,GGG,SSS,TTT)  "Capacity rating (non-negative, typically close to 1; default/1/, use eps for 0)";

PARAMETER DE_VAR_T(RRR,DEUSER,SSS,TTT)             "Variation in electricity demand (none~MW)";
PARAMETER DH_VAR_T(AAA,DHUSER,SSS,TTT)             "Variation in heat demand (none~MW)";
PARAMETER WTRRSVAR_S(AAA,SSS)                      "Variation of the water inflow to reservoirs (none~MW)";
PARAMETER WTRRRVAR_T(AAA,SSS,TTT)                  "Variation of generation of hydro run-of-river (none~MW)";
PARAMETER WND_VAR_T(AAA,SSS,TTT)                   "Variation of the wind generation (none~MW)"; !!
PARAMETER SOLE_VAR_T(AAA,SSS,TTT)                  "Variation of the solar generation (none~MW)"; !!
PARAMETER WAVE_VAR_T(AAA,SSS,TTT)                  "Variation of the wave generation (none~MW)"; !!
PARAMETER X3FX_VAR_T(RRR,SSS,TTT)                  "Variation in fixed exchange with 3. region (none~MW)";
PARAMETER HYPPROFILS(AAA,SSS)                      "Hydro with storage seasonal price profile (Money/MWh)";

$ifi %YIELDREQUIREMENT%==yes  PARAMETER YIELDREQ(GGG) "Differentiates yield requirements for different technologies ()"; !! () todo

** Export data
* Data for handling of annual hydro constraints in future runs:
PARAMETER HYRSG(YYY,AAA,SSS)        "Water (hydro) generation quantity of the seasons to be transferred to future runs (MWh)";
PARAMETER VHYRS_SL(YYY,AAA,SSS)       "To be saved for comparison with BB1/BB2 solution value for VHYRS_S.L (initial letter is V although declared as a parameter) (MWh)"
PARAMETER WATERVAL(YYY,AAA,SSS)     "Water value (in input Money) to be transferred to future runs (input-Money/MWh)";
* Data for handling investments in future runs:
PARAMETER GKACCUMNET(YYY,AAA,GGG) "Resulting technology capacity development at end of (ULTimo) previous (i.e., start of current) year (MW) (MWh for storage) to be transferred to future runs";
PARAMETER XKACCUMNET(YYY,IRRRE,IRRRI) "Resulting transmission capacity development at end (MISSING: minus any decommissioning of them due to lifetime expiration) this BB4, at end of previous (i.e., available at start of current) year (MW) to be transferred to future runs";

* Data for handling interseasonal storage
PARAMETER GVESTOVOLTS(YYY,AAA,GGG,SSS,TTT) "Electricity storage contents at beginning of time segment (MWh) to be transferred to future runs";
PARAMETER GVHSTOVOLTS(YYY,AAA,GGG,SSS,TTT) "Heat storage contents at beginning of time segment (MWh) to be transferred to future runs";
** End: Export data

* ------------------------------------------------------------------------------
* All remaining (cf. ... .inc above) data files af included from the following file
$ifi     exist "bb4datainc.inc" $include                   "bb4datainc.inc";
$ifi not exist "bb4datainc.inc" $include  "../../base/model/bb4datainc.inc";

* UPS! Forgot DOL! TODO
GKRATE(AAA,GGG,SSS)$((NOT IA(AAA)) OR (NOT G(GGG)) OR (NOT S(SSS))) = 0;
*GKNMAX(YYY,AAA,GGG)$((NOT Y(YYY)) OR (NOT IA(AAA))) = INF;    Presently not implemented.
GKRATE(IA,G,S)$(GKRATE(IA,G,S) EQ 1) = 0; !! Should give no reduction in size unless the data files does not exploit that default value is 1.

* The two specifications of fuel type 'FDACRONYM' and 'FDNB', have relative merits.
* Under most circumstances 'FDACRONYM' is preferable, because it is more transparent.
* If 'FDACRONYM' can be used, provide no data for 'FDNB' in datafile, and vice versa.
* Use only 'FDACRONYM' in the remaining code:
FDATA(FFF,'FDACRONYM')$(NOT FDATA(FFF,'FDACRONYM')) = FDATA(FFF,'FDNB');

* No need to continue if there are errors
$if not errorfree $abort "Balmorel processing aborted after inclusion of file bb4datainc.inc due to data errors";

* ------------------------------------------------------------------------------

IS33(S,ISALIAS) = YES$(ORD(ISALIAS) EQ (ORD(S)+1));
IS33(S,ISALIAS)$((ORD(S) EQ CARD(S)) AND (ORD(ISALIAS) EQ 1)) = YES; !! CIRCULAR ADDED


* The following sets concern combination technologies.

* (Text and assignment of technology related subsets in file dataincbb4.inc:)
* The sets:
* IGCND,IGBPR,IGEXT,IGHOB,IGETOH,IGHSTO,IGESTO,IGHSTOS,IGESTOS,IGHYRS,IGHYRR,IGWND,IGSOLE,IGSOLH,IGWAVE
* are directly extracted from GDATA(G,'GDTYPE') and are used to reference
* technology types.
*
* IGHH and IGEE are used in the balance equations and for output control.
* IGHHNOSTO and IGEENOSTO is not currently used for anything.
*
* IGNOTETOH is used for O&M cost in the objective function, in the balance
* equation, in heat storage balance equations and in various output functions.
* IGKH and IGKE are used for capacity restrictions and for certain output files.
* IGKHNOSTO and IGKENOSTO are used for output.
* IGDISPATCH is used capacity restrictions and output.
* IGKKNOWN is used to exclude investment options.
* IGKFIND is used to single out investment options.
* IGEH is used for CHP specific taxes.
* IGE and IGH are used all over.

* The sets are defined based on information in PARAMETER GDATA.

* The specifications of technology type 'GDTYPE' in GDATA may use an acronym or a number.
* Under most circumstances an acronym is preferable, the list is given above.
* If an acronym can not be used, use the numbers consistently as seen below.


   IGCND(G)    = YES$(GDATA(G,'GDTYPE') EQ GCND);
   IGBPR(G)    = YES$(GDATA(G,'GDTYPE') EQ GBPR);
   IGEXT(G)    = YES$(GDATA(G,'GDTYPE') EQ GEXT);
   IGHOB(G)    = YES$(GDATA(G,'GDTYPE') EQ GHOB);
   IGETOH(G)   = YES$(GDATA(G,'GDTYPE') EQ GETOH);
   IGHSTO(G)   = YES$(GDATA(G,'GDTYPE') EQ GHSTO);
   IGHSTOS(G)  = YES$(GDATA(G,'GDTYPE') EQ GHSTOS);
   IGESTO(G)   = YES$(GDATA(G,'GDTYPE') EQ GESTO);
   IGESTOS(G)  = YES$(GDATA(G,'GDTYPE') EQ GESTOS);
   IGHYRS(G)   = YES$(GDATA(G,'GDTYPE') EQ GHYRS);
   IGHYRR(G)   = YES$(GDATA(G,'GDTYPE') EQ GHYRR);
   IGWND(G)    = YES$(GDATA(G,'GDTYPE') EQ GWND);
   IGSOLE(G)   = YES$(GDATA(G,'GDTYPE') EQ GSOLE);
   IGSOLH(G)   = YES$(GDATA(G,'GDTYPE') EQ GSOLH);
   IGWAVE(G)   = YES$(GDATA(G,'GDTYPE') EQ GWAVE);


* Assignments of IGESTO, IGESTOS, IGHSTO and IGHSTOS may be changed if option stointers has a non-default value.
$ifi "%stointers%"=="all"  IGESTOS(IGESTO) = YES; IGHSTOS(IGHSTO) = YES;
$ifi "%stointers%"=="all"  IGESTO(IGESTO) = NO;   IGHSTO(IGHSTO) = NO;
$ifi "%stointers%"=="none" IGESTO(IGESTOS) = YES; IGHSTO(IGHSTOS) = YES;
$ifi "%stointers%"=="none" IGESTOS(IGESTOS) = NO; IGHSTOS(IGHSTOS) = NO;

*---------------
* The specifications of technology type 'GDTECHGROUP' in GDATA may use an acronym or a number.
* Under most circumstances an acronym is preferable, the list is given above.
* If an acronym can not be used, use the numbers consistently as seen below.


   IWATERTANK(G)= YES$(GDATA(G,'GDTECHGROUP') EQ WATERTANK);
   IPIT(G)      = YES$(GDATA(G,'GDTECHGROUP') EQ PIT);
   IHEATPUMP(G) = YES$(GDATA(G,'GDTECHGROUP') EQ HEATPUMP);

*-------------------------

   IGHHNOSTO(G) = NO;   IGHHNOSTO(IGHOB)   = YES;  IGHHNOSTO(IGSOLH)= YES;

   IGHSTOALL(G) =       IGHSTO(G)
                         +IGHSTOS(G);

   IGHH(G)      =       IGHHNOSTO(G)
                         +IGHSTOALL(G);

   IGKHNOSTO(G)     =   IGETOH(G)
                         +IGHHNOSTO(G);

   IGKH(G)          =   IGKHNOSTO(G)
                         +IGHSTOALL(G);

   IGEENOSTO(G)     =   IGCND(G)     !! In contrast to heat related technologies above,
                         +IGHYRS(G)  !! with elec related technologies a more enumeration approach is taken
                         +IGHYRR(G)  !! for illustrative purposes
                         +IGWND(G)
                         +IGSOLE(G)
                         +IGWAVE(G);

   IGEE(G)          =   IGCND(G)
                         +IGHYRS(G)
                         +IGHYRR(G)
                         +IGWND(G)
                         +IGSOLE(G)
                         +IGWAVE(G)
                         +IGESTO(G)
                         +IGESTOS(G);

   IGESTOALL(G) =       IGESTO(G)
                         +IGESTOS(G);

   IGKE(G)          =   IGCND(G)
                         +IGBPR(G)
                         +IGEXT(G)
                         +IGESTO(G)
                         +IGESTOS(G)
                         +IGHYRS(G)
                         +IGHYRR(G)
                         +IGWND(G)
                         +IGSOLE(G)
                         +IGWAVE(G);

   IGKENOSTO(G)     =   IGKE(G)
                         -IGESTO(G)
                         -IGESTOS(G);

   IGNOTETOH(G)= NOT IGETOH(G);

   IGEH(G) = IGBPR(G)+IGEXT(G)+IGETOH(G);
   IGE(G)=IGEE(G)+IGEH(G);
   IGH(G)=IGHH(G)+IGEH(G);

$ifi not %heatsto_loading_rest%==yes $goto heat_storage_loading_lim
*Definition of ILINKSTO
ILINKSTO(IGHSTOALL,IGH)=YES;

$ifi not %heatsto2heasto_rest%==yes $goto heat_storage_to_heat_storage
*Storage are forbidden to load other storages
LOOP(IGHSTOALL,
         LOOP(IGH$(IGHSTOALL(IGH)),
                 ILINKSTO(IGHSTOALL,IGH)=NO;
         );

);
$label  heat_storage_to_heat_storage

$ifi not %watertank_loading_rest%==yes $goto watertank_loading_lim
*Water tank loading technology restriction

IGHNOWT(G) =  IGSOLH(G);

LOOP(IWATERTANK,
         LOOP(IGHNOWT,
                     ILINKSTO(IWATERTANK,IGHNOWT)=NO;
         );

);
$label  watertank_loading_lim

$label  heat_storage_loading_lim

*-----------------------

   IGDISPATCH(G)    =   IGCND(G)
                         +IGBPR(G)
                         +IGEXT(G)
                         +IGHOB(G)
                         +IGESTO(G)
                         +IGESTOS(G)
                         +IGHSTO(G)
                         +IGHSTOS(G)
                         +IGETOH(G)
                         +IGHYRS(G);

   IGKFIND(G)  = YES$(GDATA(G,'GDKVARIABL') EQ 1);
   IGKKNOWN(G) = NOT IGKFIND(G);

$ifi not %bypass%==yes   IGBYPASS(G) = NO;
$ifi %bypass%==yes       IGBYPASS(IGBPR)$GDATA(IGBPR,'GDBYPASSC') = YES;

*-------------------------------------------------------------------------------
*----- Any internal sets assignments for addon to be placed here: --------------
*-------------------------------------------------------------------------------
* NOTE: When making new generation technology types. Some add-ons may already
* be using values of GDATA(G,'GDTYPE'). Check addons referenced here to maximize
* consistency and avoid conflicts. It is encouraged to avoid using the '-' set
* operator and instead use the '+' operator for compound assignments.

$include "../../base/addons/_hooks/isetdecdef.inc"


*-------------------------------------------------------------------------------
*----- End: Any internal sets assignments for addon to be placed here ----------
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
*---- Investments: --------------------------------------------------------------
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
*---- Miscellaneous ------------------------------------------------------------
*-------------------------------------------------------------------------------

* SCALAR OMONEY specifies output currency name and its exchange rate to input currency.
* Example of declaration:  "SCALAR OMONEY "EUR07" / 1 /;".
* Since the text string holding the output currency is part of the declaration,
* the declaration is not given here in Balmorel.gms but in the included file.
* (For this reason you can not here apply the "Semislash-idea".)
* It is advised to add a comment in the data file stating what the input currency is and to which year it refers.

*-------------------------------------------------------------------------------
*----- Any parameters for addon to be placed here: -----------------------------
*-------------------------------------------------------------------------------

$include "../../base/addons/_hooks/pardeclare.inc"

$ifi %HEATTRANS%==yes $if     EXIST '../data/htrans.inc' $INCLUDE         '../data/htrans.inc';
$ifi %HEATTRANS%==yes $if not EXIST '../data/htrans.inc' $INCLUDE '../../base/data/htrans.inc';

$ifi %POLICIES%==yes   $if exist 'POLREQ.inc' $INCLUDE 'POLREQ.inc';
$ifi %POLICIES%==yes   $if not exist 'POLREQ.inc' $INCLUDE '../../base/addons/policies/data/POLREQ.inc';

$ifi %SYSTEMCOST%==yes   $if exist 'BASELOADSERVICE.inc' $INCLUDE 'BASELOADSERVICE.inc';
$ifi %SYSTEMCOST%==yes   $if not exist 'BASELOADSERVICE.inc' $INCLUDE '../../base/addons/systemcost/data/BASELOADSERVICE.inc';

* This file (if exists) contains:
* PARAMETER XHKFX(IAAAE,IAAAI)    "Initial heat transmission capacity between regions"
* PARAMETER XHINVCOST(IAAAE,IAAAI) "Investment cost in new heat transmission cap"
* PARAMETER XHCOST(IAAAE,IAAAI)    "Heat transmission cost between countries"
* PARAMETER XHLOSS(IAAAE,IAAAI)    "Heat transmission loss between regions"

* Printing of data to the list file controlled by %ONOFFDATALISTING% and %ONOFFCODELISTING%:
%ONOFFDATALISTING%

SCALAR PENALTYQ  "Penalty on violation of equation (non-negative)";

SET YMODEL "YMODEL is a set used to derive the years from Y in each Balbase4 model";
ALIAS(YMODEL, IYMODEL4)
PARAMETER YMODELDELTA(YMODEL) "Number of years between a year and the preceding year represented in model Balbase4 ('number' means difference between the ord in Y)";
* Printing of data to the list file controlled by %ONOFFDATALISTING% and %ONOFFCODELISTING%:
%ONOFFCODELISTING%

*-------------------------------------------------------------------------------
*----- End: Any parameters for addon to be placed here -------------------------
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
* End: Declaration and definition of numerical data: PARAMETERS and SCALARS
*-------------------------------------------------------------------------------

* Omit non-relevant information wrt. geography for present models. Non-exhaustive list.
DE_VAR_T(RRR,DEUSER,SSS,TTT)$(not IR(RRR)) = 0;
DE_VAR_T(RRR,DEUSER,SSS,TTT)$(not IR(RRR)) = 0;
DH_VAR_T(AAA,DHUSER,SSS,TTT)$(not IA(AAA)) = 0;
X3FX_VAR_T(RRR,SSS,TTT)$(not IR(RRR)) = 0;
WND_VAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;
SOLE_VAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;
SOLH_VAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;
WAVE_VAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;
WTRRRVAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;

*-------------------------------------------------------------------------------
* Declaration and definition of (additional) internal sets, aliases and parameters:
*-------------------------------------------------------------------------------

* Aliases relative to time:

ALIAS (S,ISALIAS);
ALIAS (T,ITALIAS);
ALIAS (Y,IYALIAS44);
ALIAS (Y,IY402);
SET IY411(Y)                "IY411 The years in current Balbase4 model";
SET IY410(Y)                "IY410 The years in the current Balbase4 model except the last year" ;
SET IY401(Y)                "IY401 The years in the current Balbase4 model except the first year" ;
SET IY411FIRST(Y)           "The first year in the current Balbase4 model";
SET IY411PREVY(Y,Y)         "For any given element in IY411 (index Y 1): the previous element in Y (index Y 2)";
SET IYFIRST(Y)              "The first year in Y";
IYFIRST(Y)$(ORD(Y) EQ 1) = YES;



*-------------------------------------------------------------------------------
* Application of default data:
*-------------------------------------------------------------------------------

* GOMVCOSTO,GOMVCOSTIN, GOMFCOST and GINVCOST are given the default values in GDATA unless non-zero values or EPS is specified in the data file:
GOMVCOSTO(IA,G)$((NOT GOMVCOSTO(IA,G)) AND (SUM(Y,GKFX(Y,IA,G)) OR AGKN(IA,G))) = GDATA(G,'GDOMVCOST0');
GOMVCOSTIN(IA,G)$((NOT GOMVCOSTIN(IA,G)) AND (SUM(Y,GKFX(Y,IA,G)) OR AGKN(IA,G))) = GDATA(G,'GDOMVCOSTIN');
GOMFCOST(IA,G)$((NOT GOMFCOST(IA,G)) AND (SUM(Y,GKFX(Y,IA,G)) OR AGKN(IA,G))) = GDATA(G,'GDOMFCOST0');
GINVCOST(IA,G)$((NOT GINVCOST(IA,G)) AND (SUM(Y,GKFX(Y,IA,G)) OR AGKN(IA,G))) = GDATA(G,'GDINVCOST0');

*-------------------------------------------------------------------------------
* End of: Application of default data
*-------------------------------------------------------------------------------

* Time aggregation:
$ifi %timeaggr%==yes  $include '../../base/addons/timeaggregation/timeaggr.inc';

* The following relates technology and fuel:
SET IGF(GGG,FFF)   "Relation between technology type and fuel type";

* Internal scalars:
SCALAR ILOOPBREAK     "Scalar used as binary number to break any loop function";
SCALAR IFIRSTYEARNEXTBB4 "First year in the next Balbase4 model";

*------------------------------------------------------------------------------
* Internal sets:

SET IAGKFX(Y,AAA,G)    "Area, technology with positive endogenous capacity current simulation year";
SET IXKN(Y,IRRRE,IRRRI)  "Pair of regions that may get new transmission capacity, yearly dependent";

* Specification of where new endogenous generation capacity may be located:

SET IAGKN(AAA,G) "Area, technology where technology may be invested based on AGKN and implicit year independent constraints from FKPOT";
SET IAGKNY(Y,AAA,G) "Area, technology where technology may be invested based on IAGKN and implicit constraint from first investment year";


SET IXK_HASORPOT(Y,IRRRE,IRRRI) "Transmission lines with existing or potentially invested capacity current year";
SET IAGK_HASORPOT(Y,AAA,G) "Technologies with existing or potentially invested capacity current year";
SET IGDECOMEXOPOT(Y,AAA,G) "Technologies with potential exogenous capacity to be decommissioned";

SET IPLUSMINUS "Violation of equation"  /IPLUS Violation of equation upwards, IMINUS  Violation of equation downwards/;
* Note: When placed on the left hand side of the equation
* the sign to the IMINUS and IPLUS terms should be - and +, respectively.
* This way the sign and the name will be intuitively consistent in equation listings.

*------------------------------------------------------------------------------
* Internal parameters and settings:
*------------------------------------------------------------------------------
*Initializing the set IGDECOMEXOPOT in case the add-on DECOM is not activated
IGDECOMEXOPOT(Y,IA,G)=0;

PARAMETER IWEIGHTY(Y)                  "Relative weight of the individual years in Y";
* Set the relative weight of the individual years in Y.
* Two ideas implemented here. Used according to option bb4weighty.
* Simple idea is to give equal weights:
$ifi "%bb4weighty%"=="same"      IWEIGHTY(Y) = 1;
* More complex weighting of the individual years (years in YYY but not in Y are shared between two nearest (first and last years double the shared weight contribution)):
$ifi "%bb4weighty%"=="shareYYY"  IWEIGHTY(Y)$(ORD(Y) EQ 1) = 1$(CARD(Y) EQ 1) + ((YVALUE(Y+1)-YVALUE(Y)-1)+1)$(CARD(Y) GT 1);
$ifi "%bb4weighty%"=="shareYYY"  IWEIGHTY(Y)$((ORD(Y) GT 1) AND (ORD(Y) LT CARD(Y))) = (YVALUE(Y) - YVALUE(Y-1) -1)/2  + (YVALUE(Y+1) - YVALUE(Y) -1)/2    +1;
$ifi "%bb4weighty%"=="shareYYY"  IWEIGHTY(Y)$((ORD(Y) EQ CARD(Y)) AND (CARD(Y) GT 1)) = ((YVALUE(Y)-YVALUE(Y-1)-1)+1);
* Unload IWEIGHTY for the output tool
execute_unload '%relpathModel%../output/temp/IWEIGHTY.gdx' IWEIGHTY;

PARAMETER IYHASANNUITYG(Y,Y,G)         "Binary parameter to establish whether the annuity of an investment of a technology made in Y (first index) should be paid in the time period Y (second index) (0,1)" ;
PARAMETER IYHASANNUITYX(Y,Y)           "Binary parameter to establish whether the annuity of an investment of a transmission line investment made in Y (first index) should be paid in the time period Y (second index) (0,1)";
PARAMETER IINVYEARG_LEFT(Y,Y,G)      "Remaining years of the lifetime of G of an investment made in Y (first index) at the beggining of Y (second index) (years)";
PARAMETER IINVYEARX_LEFT(Y,Y)        "Remaining years of the lifetime of a transmission line investment made in Y (first index) at the beggining of Y (second index) (years)";
PARAMETER IN_INV_G(Y,G)              "Number of investments made OF G within Y (fraction)";
PARAMETER IN_INV_X(Y)                "Number of investments made OF a transmission line within Y (fraction)";


*------------ Calculation of IYHASANNUITYG and IYHASANNUITYX to include/exclude the payment of the annuities---------------------
$ifi not %TechInvest%==yes  IYHASANNUITYG(IYALIAS,Y,IGKFIND)= 0;
$ifi not %TransInvest%==yes IYHASANNUITYX(IYALIAS,Y)= 0;

$ifi not %TechInvest%==yes $goto NO_TECH_INVESTMENTS
**GENERATION
LOOP(IGKFIND,
  LOOP(IYALIAS,
    LOOP(Y$(ORD(Y) EQ ORD(IYALIAS)),
      IINVYEARG_LEFT(IYALIAS,Y,IGKFIND)=GDATA(IGKFIND,'GDLIFETIME');
    );
  );
);

LOOP(IGKFIND,
  LOOP(IYALIAS,
    ILOOPBREAK=0;
    IN_INV_G(IYALIAS,IGKFIND)=ROUND(IWEIGHTY(IYALIAS)/GDATA(IGKFIND,'GDLIFETIME'));
*Correction of IN_INV_G
      IF (IN_INV_G(IYALIAS,IGKFIND) EQ 0,
        IN_INV_G(IYALIAS,IGKFIND)=1;
      );
      LOOP(Y$(ORD(Y) GE ORD(IYALIAS) AND (ILOOPBREAK EQ 0)),
*First year's annuity
        IF (ORD(Y) EQ ORD(IYALIAS),
          IYHASANNUITYG(IYALIAS,Y,IGKFIND)= 1;
          IF(IINVYEARG_LEFT(IYALIAS,Y,IGKFIND)*IN_INV_G(IYALIAS,IGKFIND) LE IWEIGHTY(Y),
            ILOOPBREAK=1;
          );
          IINVYEARG_LEFT(IYALIAS,Y+1,IGKFIND)$(ORD(Y) NE CARD(IYALIAS2))=GDATA(IGKFIND,'GDLIFETIME')*IN_INV_G(IYALIAS,IGKFIND)-IWEIGHTY(Y);
        );
*Remaining year's annuity
      IF (ORD(Y) GT ORD(IYALIAS),
        IF ( IINVYEARG_LEFT(IYALIAS,Y,IGKFIND) GT IWEIGHTY(Y) ,
          IYHASANNUITYG(IYALIAS,Y,IGKFIND)= 1;
            IINVYEARG_LEFT(IYALIAS,Y+1,IGKFIND)$(ORD(Y) NE CARD(IYALIAS2))=IINVYEARG_LEFT(IYALIAS,Y,IGKFIND)-IWEIGHTY(Y);
          );
          IF ((IINVYEARG_LEFT(IYALIAS,Y,IGKFIND) GE IWEIGHTY(IYALIAS)/2) AND (IINVYEARG_LEFT(IYALIAS,Y,IGKFIND) LE IWEIGHTY(Y)) ,  !!Assumption: if the reamining years are more ore equal than half of IWEIGHTY, then the technology is in in this snapshot
            IYHASANNUITYG(IYALIAS,Y,IGKFIND)= 1;
            ILOOPBREAK=1;
          );
          IF ((IINVYEARG_LEFT(IYALIAS,Y,IGKFIND) LT IWEIGHTY(IYALIAS)/2) AND (IINVYEARG_LEFT(IYALIAS,Y,IGKFIND) LE IWEIGHTY(Y)) , !!Assumption: if the reamining years are less than half of IWEIGHTY, then the technology is out in this snapshot
            IYHASANNUITYG(IYALIAS,Y,IGKFIND)= 0;
            ILOOPBREAK=1;
          );
        );
      );
  );
);
$label NO_TECH_INVESTMENTS

$ifi not %TransInvest%==yes $goto NO_TRANS_INVESTMENTS
** TRANSMISSION LINES
LOOP(IYALIAS,
  LOOP(Y$(ORD(Y) EQ ORD(IYALIAS)),
    IINVYEARX_LEFT(IYALIAS,Y)=LIFETIME_X;
  );
);

LOOP(IYALIAS,
  ILOOPBREAK=0;
  IN_INV_X(IYALIAS)=ROUND(IWEIGHTY(IYALIAS)/LIFETIME_X);
*Correction of inv
  IF ( IN_INV_X(IYALIAS) EQ 0,
    IN_INV_X(IYALIAS)=1;
  );
  LOOP(Y$(ORD(Y) GE ORD(IYALIAS) AND (ILOOPBREAK EQ 0)),

*First year's annuity
    IF ( ORD(Y) EQ ORD(IYALIAS),
      IYHASANNUITYX(IYALIAS,Y)= 1;
      IF(IINVYEARX_LEFT(IYALIAS,Y)*IN_INV_X(IYALIAS) LE IWEIGHTY(Y),
      ILOOPBREAK=1;
      );
      IINVYEARX_LEFT(IYALIAS,Y+1)$(ORD(Y) NE CARD(IYALIAS2))=LIFETIME_X*IN_INV_X(IYALIAS)-IWEIGHTY(Y);
    );
*Remaining year's annuity
    IF ( ORD(Y) GT ORD(IYALIAS),
      IF ( IINVYEARX_LEFT(IYALIAS,Y) GT IWEIGHTY(Y) ,
        IYHASANNUITYX(IYALIAS,Y)= 1;
        IINVYEARX_LEFT(IYALIAS,Y+1)$(ORD(Y) NE CARD(IYALIAS2))=IINVYEARX_LEFT(IYALIAS,Y)-IWEIGHTY(Y);
      );
      IF ( (IINVYEARX_LEFT(IYALIAS,Y) GE IWEIGHTY(Y)/2) AND (IINVYEARX_LEFT(IYALIAS,Y) LE IWEIGHTY(Y)) ,
        IYHASANNUITYX(IYALIAS,Y)= 1;
        ILOOPBREAK=1;
      );
      IF ( (IINVYEARX_LEFT(IYALIAS,Y) LT IWEIGHTY(Y)/2) AND (IINVYEARX_LEFT(IYALIAS,Y) LE IWEIGHTY(Y)) ,
        IYHASANNUITYX(IYALIAS,Y)= 0;
        ILOOPBREAK=1;
      );
    );
  );
);
$label NO_TRANS_INVESTMENTS
*------------ END of Calculation of the correction factor for the annuities---------------------

* Set GDCV value to one for those technologies with capacity defined on HEAT and that are not IGEXT so that their fuel consumption and O&M costs
* can be found using the same formula as for IGCND and IGEXT:
GDATA(IGBPR,'GDCV') = 1;
GDATA(IGHOB,'GDCV') = 1;
GDATA(IGETOH,'GDCV')  = 1;
GDATA(IGHSTO,'GDCV')  = 1;
GDATA(IGHSTOS,'GDCV') = 1;
GDATA(IGSOLH,'GDCV') = 1;

* Specifying the relation between technology type and fuel type in IGF:

IGF(G,FFF)=YES$(GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'));

PARAMETER IGKRATE(AAA,G,S,T)     "Capacity rating (non-negative, typically close to 1; default/1/, use eps for 0)";
* Transfer data from data file and insert default 1 as needed (Eps1-convention):
* Note that the default value is 1, this is assigned here if nothing or 0 is entered in data file.
$ifi %GKRATE_DOL%==AAA_GGG_SSS      IGKRATE(IA,G,S,T) = GKRATE(IA,G,S);
$ifi %GKRATE_DOL%==AAA_GGG_SSS_TTT  IGKRATE(IA,G,S,T) = GKRATE(IA,G,S,T);

* The following parameters contain information about CO2 and SO2 emission
* from technology G based on the fuel used and its emission data:
PARAMETER   IM_CO2(G)   "CO2 emission coefficient for fuel, fossil and renewable (kg/GJ)";
PARAMETER   IM_CO2RE(G) "CO2 emission coefficient for fuel, renewable part (kg/GJ)"; !! Hans
PARAMETER   IM_SO2(G)   "SO2 emission coefficient for fuel (kg/GJ)";
PARAMETER   IM_N2O(G)   "NO2 emission coefficient for fuel (kg/GJ)";

LOOP(FFF, !! TODO: Check forbedringen af kode som givet p\E5 SONYstick
  IM_CO2(G)$IGF(G,FFF)   = FDATA(FFF,'FDCO2');
  IM_CO2RE(G)$IGF(G,FFF) = FDATA(FFF,'FDCO2')*FDATA(FFF,'FDRE');
  IM_SO2(G)$IGF(G,FFF)   = FDATA(FFF,'FDSO2')$(GDATA(G,'GDDESO2') EQ 0) +
      (FDATA(FFF,'FDSO2')*(1-GDATA(G,'GDDESO2')))$(GDATA(G,'GDDESO2') GT 0);
  IM_N2O(G)$IGF(G,FFF)   = FDATA(FFF,'FDN2O');
);

* Further declarations relative to variations:
* Parameters holding the total weight in the (arbitrary) units of the weights
* used in input for each season and time period.
* To be used in calculations below.

PARAMETER IWEIGHSUMS          "Weight of the time of each season in S";
PARAMETER IWEIGHSUMT          "Weight of the time of each time period in T";

* The (arbitrary) units used in the input are converted to days and hours.
PARAMETER IHOURSINST(SSS,TTT)   "Length of time segment to convert the timesteps used into annual values (hours)";
PARAMETER IHYRST(SSS,TTT)       "Length of time segment to convert the timesteps used to represent correctly the change in reservoir level of equation QHYRSSEQ (hours)";

* Annual amounts as expressed in the units of the weights and demands used
* in input in the file var.inc:

PARAMETER IDE_SUMST(RRR,DEUSER) "Annual amount of nominal electricity demand (MWh)";
PARAMETER IDH_SUMST(AAA,DHUSER) "Annual amount of nominal heat demand (MWh)";
PARAMETER IX3FXSUMST(RRR)     "Annual amount of fixed electricity export to third countries relative to X3FX_VAR_T and (S,T) (MWh)";

* Sums for finding the wind and solar generated electricity generation
* as expressed in the units of the weights and demands used in input:
PARAMETER IWND_SUMST(AAA)  "Annual amount of wind generated electricity relative to WND_VAR_T and (S,T) (MWh)";
PARAMETER ISOLESUMST(AAA)  "Annual amount of solar generated electricity relative to ISOLESUMST and (S,T) (MWh)";
PARAMETER ISOLHSUMST(AAA)  "Annual amount of solar generated heat relative to ISOLHSUMST and (S,T) (MWh)";
PARAMETER IWAVESUMST(AAA)  "Annual amount of wave generated electricity relative to WND_VAR_T and (S,T) (MWh)";
PARAMETER IWTRRSSUM(AAA)   "Annual amount of hydro from reservoirs generated electricity relative to IWTRRSSUM and (S,T) (MWh)";
PARAMETER IWTRRRSUM(AAA)   "Annual amount of hydro-run-of-river generated electricity relative to IWTRRRSUM and (S,T) (MWh)";


* Demand of electricity (MW) and heat (MW) current simulation year:

* Generation capacity (MW) at the beginning of current simulation year,
* specified by GKFX and by accumulated endogeneous investments, respectively:

* Taxes differentiated by G
PARAMETER  ITAX_GF(AAA,G)   "Fuel taxes on heat-only units ()",  !! See Balmorel.gms
           ITAX_GH(AAA,G)   "Heat taxes on generation units ()", !! See Balmorel.gms
           ITAX_GE(AAA,G)   "Electricity taxes on generation units and subsidies(-) (Money/MWh)",    !! See Balmorel.gms
           ITAX_KN(AAA,G)   "Tax (neg. subsidy) for investment in electricity generation (Money/MW)"; !! See Balmorel.gms
*          ITAX_IE(AAA,G)

* Fuel use differentiated by fuel
PARAMETER  IGMAXF_Y(CCCRRRAAA,FFF) "Maximum fuel use per year (GJ)",  !! See Balmorel.gms
           IGMINF_Y(CCCRRRAAA,FFF) "Minimum fuel use per year (GJ)",  !! See Balmorel.gms
           IGEQF_Y(CCCRRRAAA,FFF)  "Exact fuel use per year (GJ)";    !! See Balmorel.gms

* Fixed exchange with third countries (MW) current simulation year:
PARAMETER IX3FX_T(Y,RRR,S,T) "Fixed export to third countries for each time segment (MW)";

* Inflow in areas each season:
* The following is used in balbase1.sim and balbase2.sim
PARAMETER IHYINF_S(AAA,SSS)  "Water inflow to hydro reservoirs in areas in each season (MWh/MW)";

* Inflow in areas each season:
* The following is used in balbase1.sim and balbase2.sim
PARAMETER IHYINF_S(AAA,SSS)  "Water inflow to hydro reservoirs in areas in each season (MWh/MW)";

PARAMETER IGROWTHCAPCG(C,G)  "Limit on growth of technology dependent on years between optimisation (MW) TODO";
*PARAMETER IGKNMAX(Y,AAA,G)   "Maximum capacity at new technologies (MW)"; !!TODO. Relevant?   Presently not implemented.


*-------------------------------------------------------------------------------
* Set the time weights depending on the model:
*-------------------------------------------------------------------------------
* The following code ensures that with time aggregation the energy content (MWh) in time series is conserved, but it does no ensure that the power (MW) is conserved.
* To get an aggregation that preserves both energy,  power and possibly more, use an addon or auxil.

$ifi not %timeseries_scaling%==usedtimesteps_timseries_scaling $goto usedtimesteps_timseries_scaling_end

*Timeseries values are scaled linearly by the following factor: scaling factor = annual energy content / sum of the energy in the used part of the timeseries
IWEIGHSUMS = SUM(S, WEIGHT_S(S));
IWEIGHSUMT = SUM(T, WEIGHT_T(T));
IHOURSINST(S,T)=IOF8760*WEIGHT_S(S)*WEIGHT_T(T)/(IWEIGHSUMS*IWEIGHSUMT);
IDE_SUMST(IR,DEUSER) = SUM((S,T), IHOURSINST(S,T)*DE_VAR_T(IR,DEUSER,S,T));
IDH_SUMST(IA,DHUSER) = SUM((S,T), IHOURSINST(S,T)*DH_VAR_T(IA,DHUSER,S,T));
IX3FXSUMST(IR)$(SUM(Y,X3FX(Y,IR)))                  = SUM((S,T), IHOURSINST(S,T)*X3FX_VAR_T(IR,S,T));
IWND_SUMST(IA)  = SUM((S,T), IHOURSINST(S,T)*WND_VAR_T(IA,S,T));
ISOLESUMST(IA) = SUM((S,T), IHOURSINST(S,T)*SOLE_VAR_T(IA,S,T));
ISOLHSUMST(IA) = SUM((S,T), IHOURSINST(S,T)*SOLH_VAR_T(IA,S,T));
IWAVESUMST(IA) = SUM((S,T), IHOURSINST(S,T)*WAVE_VAR_T(IA,S,T));
IWTRRRSUM(IA)  = SUM((S,T), IHOURSINST(S,T)*WTRRRVAR_T(IA,S,T));
IWTRRSSUM(IA) = SUM(S, (WEIGHT_S(S)/IWEIGHSUMS)*WTRRSVAR_S(IA,S));

* Calculate hydro inflow to reservoirs in MWh/MW installed capacity (new and old):

IHYINF_S(IA,S)= ((WTRRSFLH(IA) * WTRRSVAR_S(IA,S) * (WEIGHT_S(S)/IWEIGHSUMS)) / IWTRRSSUM(IA))$IWTRRSSUM(IA);

$label  usedtimesteps_timseries_scaling_end

$ifi not %timeseries_scaling%==full_timeseries_scaling $goto full_timeseries_scaling_end

*Timeseries values are scaled linearly by the following factor: scaling factor = annual energy content / sum of the energy in the full timeseries
IWEIGHSUMS = SUM(SSS, WEIGHT_S(SSS));
IWEIGHSUMT = SUM(TTT, WEIGHT_T(TTT));
IHOURSINST(SSS,TTT)=IOF8760*(WEIGHT_S(SSS)*WEIGHT_T(TTT))/(IWEIGHSUMS*IWEIGHSUMT);
IDE_SUMST(IR,DEUSER) = SUM((SSS,TTT), IHOURSINST(SSS,TTT)*DE_VAR_T(IR,DEUSER,SSS,TTT));
IDH_SUMST(IA,DHUSER) = SUM((SSS,TTT), IHOURSINST(SSS,TTT)*DH_VAR_T(IA,DHUSER,SSS,TTT));
IX3FXSUMST(IR) = SUM((SSS,TTT), IHOURSINST(SSS,TTT)*X3FX_VAR_T(IR,SSS,TTT));
IWND_SUMST(IA)=SUM((SSS,TTT), IHOURSINST(SSS,TTT)*WND_VAR_T(IA,SSS,TTT));
ISOLESUMST(IA)=SUM((SSS,TTT), IHOURSINST(SSS,TTT)*SOLE_VAR_T(IA,SSS,TTT));
ISOLHSUMST(IA)=SUM((SSS,TTT), IHOURSINST(SSS,TTT)*SOLH_VAR_T(IA,SSS,TTT));
IWAVESUMST(IA)=SUM((SSS,TTT), IHOURSINST(SSS,TTT)*WAVE_VAR_T(IA,SSS,TTT));
IWTRRRSUM(IA)=SUM((SSS,TTT),  IHOURSINST(SSS,TTT)*WTRRRVAR_T(IA,SSS,TTT));
IWTRRSSUM(IA)=SUM(SSS, (WEIGHT_S(SSS)/IWEIGHSUMS)*WTRRSVAR_S(IA,SSS));

* Calculate hydro inflow to reservoirs in MWh/MW installed capacity (new and old):

IHYINF_S(IA,S)= ((WTRRSFLH(IA) * WTRRSVAR_S(IA,S) * (WEIGHT_S(S)/IWEIGHSUMS)) / IWTRRSSUM(IA))$IWTRRSSUM(IA);

*Redefinition of time parameters so annual constraints are respected
IWEIGHSUMS = SUM(S, WEIGHT_S(S));
IWEIGHSUMT = SUM(T, WEIGHT_T(T));
IHOURSINST(SSS,TTT)=0;
IHOURSINST(S,T)=IOF8760*WEIGHT_S(S)*WEIGHT_T(T)/(IWEIGHSUMS*IWEIGHSUMT);

$label  full_timeseries_scaling_end


*Timeseries values are not scaled and match exactly the timeseries (it requires changin quite some code) !!TO DO

*Calculation of IHYRST
$ifi %HYRS_AGG%==hydro_season_agg  IHYRST(S,T)=WEIGHT_S(S)/SUM(ITALIAS, WEIGHT_T(ITALIAS));
$ifi %HYRS_AGG%==hydro_year_agg    IHYRST(S,T)=IHOURSINST(S,T);

*-------------------------------------------------------------------------------
* End of: Set the time weights depending on the model
*-------------------------------------------------------------------------------


*-------------------------------------------------------------------------------
*----- Any internal parameters for addon to be placed here: --------------------
*-------------------------------------------------------------------------------

$INCLUDE '../../base/addons/_hooks/ipardecdef.inc';

* These internal parameters and sets pertain to heat transmission.
$if %HEATTRANS% == yes $include '../../base/addons/heattrans/model/htinternal.inc';

*-------------------------------------------------------------------------------
*----- End: Any internal sets and parameters for addon to be placed here -------
*-------------------------------------------------------------------------------

*------------------------------------------------------------
*--------EXCEPTIONS: Convenient internal sets and parameters
*------------------------------------------------------------

* ----------------- Assign IAGKFX, IAGKN, IAGKNY, IAGK_HASORPOT ----------------------------------

IAGKFX(Y,IA,G) = YES$GKFX(Y,IA,G);
IAGK_HASORPOT(Y,IA,G) = YES$GKFX(Y,IA,G);

IAGKN(IA,G)=NO;
IAGKNY(Y,IA,G)=NO;

$ifi not %TechInvest%==yes $goto Technology_investments_end

* IAGKN and IAGKNY indicates when and where technologies may be invested, based on various combinations of input data.
* Initially: identical to AGKN:
IAGKN(IA,G) = AGKN(IA,G);

* Note: by definition, there should be no GGG in AGKN(aaa,GGG) with GDATA(GGG,'GDKVARIABL')=1.
* This is to be checked in error2.inc: TODO. For now, overwrite to make sure:  No new capacity if capacity is not specified to be found endogeneously:
IAGKN(IA,IGKKNOWN) = NO;

* Fuel limitations: No new capacity nor new generation if zero fuel potential.
LOOP((FFF,G)$IGF(G,FFF),
  LOOP(C$FKPOT(C,FFF), !! Default convention on FKPOT: 0 implies no restriction, 'EPS' implies zero MW.
    LOOP(IA$ICA(C,IA), IF((FKPOT(C,FFF) EQ 0), IAGKN(IA,G) = NO;); )); !! Because it is EPS
  LOOP(IR$FKPOT(IR,FFF),
    LOOP(IA$RRRAAA(IR,IA), IF((FKPOT(IR,FFF) EQ 0), IAGKN(IA,G) = NO;); )); !! Because it is EPS
  LOOP(IA$FKPOT(IA,FFF),
    IF((FKPOT(IA,FFF) EQ 0), IAGKN(IA,G) = NO;); ); !! Because it is EPS
);

IAGKNY(Y,IA,G) = IAGKN(IA,G);
IAGKNY(Y,IA,G)$(YVALUE(Y) LT GDATA(G,'GDFROMYEAR') OR (YVALUE(Y) GT GDATA(G,'GDLASTYEAR')) AND (GDATA(G,'GDLASTYEAR') GT 0) OR (YVALUE(Y) LT GINVESTSTART))=NO;

* No investment in secondary combination technologies:
$ifi %COMBTECH%==yes    IAGKNY(Y,IA,IGCOMB2)=NO;

*Update of IAGK_HASORPOT based on potential production

IAGK_HASORPOT(Y,IA,G)$IAGKNY(Y,IA,G) = YES;

*This loop makes sure that if you invest in a technology in the year Y, you can potentially use it in the future, even if you do not allow for investments on this technology in the future
LOOP(Y$(ORD(Y) NE CARD(Y)),
   LOOP(IA,
      LOOP(G$IAGKNY(Y,IA,G),
         LOOP(IYALIAS2$(ORD(IYALIAS2) GT ORD(Y)),
            IAGK_HASORPOT(IYALIAS2,IA,G)= IAGK_HASORPOT(IYALIAS2,IA,G)+IAGKNY(Y,IA,G);
       );
    );
  );
);

*---END OF COMBTECH

$ifi %COMBTECH%==yes IAGK_HASORPOT(Y,IA,IGCOMB2)$SUM(IGCOMB1$(IAGK_HASORPOT(Y,IA,IGCOMB1) and GGCOMB(IGCOMB1,IGCOMB2)),1)=YES;

$label  Technology_investments_end

* ----------------- End: Assign IAGKFX, IAGKN, IAGKNY, IAGK_HASORPOT -----------------------------


*------------------ Assign IXK_HASORPOT and IXKN based on exogenously given or potential investment  ----------------------------------

* Transmision investments is subject to control by the option TransInvest,
* therefore set a default and update if investments are intended.

IXK_HASORPOT(Y,IRE,IRI) = YES$XKFX(Y,IRE,IRI);
IXKN(Y,IRE,IRI)=NO;

$ifi not %TransInvest%==yes $goto Transmission_investments_end

IXKN(Y,IRE,IRI) = YES$(XINVCOST(Y,IRE,IRI) AND (XINVCOST(Y,IRE,IRI) LT INF) AND (XINVESTSTART LE YVALUE(Y)));

*This loop makes sure that if you invest in one line in the year Y, you can use this line in the future, even if you do not allow for investments on this line in the future
LOOP(Y$(ORD(Y) GT 1),
  LOOP(IRE,
    LOOP(IRI,
      IF ((XINVCOST(Y-1,IRE,IRI) AND (XINVCOST(Y-1,IRE,IRI) LT INF) AND (XINVESTSTART LE YVALUE(Y))),
        IXK_HASORPOT(Y,IRE,IRI)=IXKN(Y,IRE,IRI)+YES$XKFX(Y,IRE,IRI);
      );
      LOOP(IYALIAS2$((ORD(IYALIAS2) GE ORD(Y)) AND (ORD(IYALIAS2) NE CARD(IYALIAS2))),
      IXK_HASORPOT(Y+1,IRE,IRI)= IXK_HASORPOT(Y+1,IRE,IRI)+IXKN(Y,IRE,IRI);
      );
    );
  );
);

$label  Transmission_investments_end

*------------------ End: Assign IXK_HASORPOT and IXKN based on exogenously given or potential investment  ----------------------------------

*------------------------------------------------------------
*--------END of EXCEPTIONS: Convenient internal sets and parameters
*------------------------------------------------------------

Parameter STOVOLTSINIT(AAA,GGG);
*STOVOLTSINIT('South-A','pmp_hydro2')= 0.5;

*-------------------------------------------------------------------------------
* End: Internal parameters and settings
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
* Possibly write input data. Prepare output file possibilities:
*-------------------------------------------------------------------------------

* The following file contains definitions of logical file names
* and the associated names of files that may be used for printout of simulation results.
* It also contains various definitions that are useful for the production and layout of the output.

* Prepare some printing possibilities:
$INCLUDE '../../base/output/printout/printinc/print1.inc';


* The input data are subject to a certain control for "reasonable" values.
* The errors are checked by the code in the files ERRORx.INC
$INCLUDE "../../base/logerror/logerinc/error2.inc";

/*LOOP(Y$(ORD(Y) EQ 1),ISCALAR1 =  YVALUE(Y)); Hans TODO
PARAMETER IDISCOUNTFACTOR(Y) "Discount factor for weighting future years relative to the first year in Y (~)";
IDISCOUNTFACTOR(Y)$Y(Y) = power((DISCOUNTRATE+1),(ISCALAR1-YVALUE(Y)));
EXECUTE_UNLOAD "ALLTEMP.GDX"; */

* Overview of input data in text format (see the description at the top of the file inputout):
$ifi %inputdatatxt%== yes        $INCLUDE '../../base/output/printout/printinc/inputout.inc';
$ifi %inputdatatxt%== yesnosolve $INCLUDE '../../base/output/printout/printinc/inputout.inc';
$ifi %inputdatatxt%== yesnosolve $goto ENDOFMODEL
* Unload input data to gdx file:
$ifi exist '"%relpathInputdata2GDX%INPUTDATAOUT.gdx"' rm '"%relpathInputdata2GDX%INPUTDATAOUT.gdx"'
* Note that the execute_unload command will unload everything, including variables and equations.
$ifi %INPUTDATA2GDX%==yes execute_unload '%relpathInputdata2GDX%INPUTDATAOUT.gdx';
* Transfer inputdata a seperate Access file (only possible if %INPUTDATA2GDX%==yes):
$ifi %INPUTDATAGDX2MDB%==yes execute '=GDX2ACCESS "%relpathInputdata2GDX%INPUTDATAOUT.gdx"';
* Transfer to Excel, read the identifiers to be transferred from file inputdatagdx2xls.txt (only possible if %INPUTDATA2GDX%==yes):
* Note: presently not working (the relevant data is not set i file inputdatagdx2xls.txt):
* NOTWORKING (i.e. you MUST have '$setglobal INPUTDATAGDX2XLS'): Note:  GAMS version 22.7 and later have better support for this....
*$ifi %INPUTDATAGDX2XLS%==yes  execute  "GDXXRW.EXE Input=%relpathInputdata2GDX%INPUTDATAOUT.gdx  Output=%relpathInputdata2GDX%INPUTDATAOUT.xls  @%relpathModel%inputdatagdx2xls.txt";

*-------------------------------------------------------------------------------
* End: Possibly write input data, prepare output file possibilities
*-------------------------------------------------------------------------------
*-------------------------------------------------------------------------------

* A number of input data IDs contain more information than is actually used with the set-up of the model.
* To reduce use of memory space and to reduce further processing and storage of unused data
* some of the larger data IDs are here reduced by resetting unused data items to default values.

$include "../../base/addons/_hooks/reducecard.inc"

DE_VAR_T(RRR,DEUSER,SSS,TTT)$((NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
DH_VAR_T(AAA,DHUSER,SSS,TTT)$((NOT IA(AAA)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
WND_VAR_T(AAA,SSS,TTT)$((NOT IA(AAA)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
SOLE_VAR_T(AAA,SSS,TTT)$((NOT IA(AAA)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
SOLH_VAR_T(AAA,SSS,TTT)$((NOT IA(AAA)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
WTRRSVAR_S(AAA,SSS)$((NOT IA(AAA)) OR (NOT S(SSS))) = 0;
WTRRRVAR_T(AAA,SSS,TTT)$((NOT IA(AAA)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
WAVE_VAR_T(AAA,SSS,TTT)$((NOT IA(AAA)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
X3FX_VAR_T(RRR,SSS,TTT)$((NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;

*DEF_STEPS(RRR,SSS,TTT,DF_QP,DEF)$((NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;      moved to _hooks - still testing
*DEF_STEPS(IR,S,T,DF_QP,DEF)$((NOT DEF_D1(DEF) AND (NOT DEF_D2(DEF)) AND (NOT DEF_D3(DEF)) AND (NOT DEF_U1(DEF)) AND (NOT DEF_U2(DEF)) AND (NOT DEF_U3(DEF)))) = 0;
*DHF_STEPS(AAA,SSS,TTT,DF_QP,DHF)$((NOT IA(AAA)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
*DHF_STEPS(IA,S,T,DF_QP,DHF)$((NOT DHF_D1(DHF) AND (NOT DHF_D2(DHF)) AND (NOT DHF_D3(DHF)) AND (NOT DHF_U1(DHF)) AND (NOT DHF_U2(DHF)) AND (NOT DHF_U3(DHF)))) = 0;


* Discounting
* One, implicitly given in ANNUITY, represent the companies' perception of financing costs, alternatives, expectations to profit, etc.
* The other, given as DISCOUNTRATE, represents society's perception of how future years' costs and benefits shall be evaluated today.
* IDISCOUNTFACTOR gives the relative weight of years.
PARAMETER IDISCOUNTFACTOR(Y) "Discount factor for weighting future years relative to the first year in Y (~)";
LOOP(Y$(ORD(Y) EQ 1),ISCALAR1 =  YVALUE(Y));
IDISCOUNTFACTOR(Y)$Y(Y) = power((DISCOUNTRATE+1),(ISCALAR1-YVALUE(Y)));



* Transfer ID values from data files to internal parameters for domain overloaded IDs.
* Note that the default value is 1, this is assigned here if nothing or 0 is entered in data file.

PARAMETER IXKRATE(IRRRE,IRRRI,S,T)     "Transmission capacity rating (share; non-negative, typically close to 1; default/1/, use eps for 0)";
$ifi %XKRATE_DOL%==IRRRE_IRRRI         IXKRATE(IRE,IRI,S,T) = XKRATE(IRE,IRI)$XKRATE(IRE,IRI);
$ifi %XKRATE_DOL%==IRRRE_IRRRI_SSS     IXKRATE(IRE,IRI,S,T) = XKRATE(IRE,IRI,S)$XKRATE(IRE,IRI,S);
$ifi %XKRATE_DOL%==IRRRE_IRRRI_SSS_TTT IXKRATE(IRE,IRI,S,T) = XKRATE(IRE,IRI,S,T)$XKRATE(IRE,IRI,S,T);

PARAMETER IGMINF(YYY,CCCRRRAAA,FFF)         "Minimum annual fuel use by year, geography and fuel and (GJ)";
$ifi %GMINF_DOL%==CCCRRRAAA_FFF             IGMINF(Y,CCCRRRAAA,FFF) = GMINF(CCCRRRAAA,FFF);
$ifi %GMINF_DOL%==YYY_CCCRRRAAA_FFF         IGMINF(Y,CCCRRRAAA,FFF) = GMINF(Y,CCCRRRAAA,FFF);
PARAMETER IGMAXF(YYY,CCCRRRAAA,FFF)         "Minimum annual fuel use by year, geography and fuel and (GJ)";
$ifi %GMAXF_DOL%==CCCRRRAAA_FFF             IGMAXF(Y,CCCRRRAAA,FFF) = GMAXF(CCCRRRAAA,FFF);
$ifi %GMAXF_DOL%==YYY_CCCRRRAAA_FFF         IGMAXF(Y,CCCRRRAAA,FFF) = GMAXF(Y,CCCRRRAAA,FFF);
PARAMETER IGEQF(YYY,CCCRRRAAA,FFF)          "Exact annual (any year) fuel use by geography and fuel (GJ)";
$ifi %GEQF_DOL%==CCCRRRAAA_FFF              IGEQF(Y,CCCRRRAAA,FFF) = GEQF(CCCRRRAAA,FFF);
$ifi %GEQF_DOL%==YYY_CCCRRRAAA_FFF          IGEQF(Y,CCCRRRAAA,FFF) = GEQF(Y,CCCRRRAAA,FFF);

PARAMETER IGMAXFS(Y,CCCRRRAAA,FFF,S)         "Minimum annual fuel use by year, season, geography and fuel and (GJ)";
IGMAXFS(Y,CCCRRRAAA,FFF,S) = GMAXFS(Y,CCCRRRAAA,FFF,S);

* Unload input data to gdx and possibly MDB files.
* Note that this is a compile time operation, such that only the 'direct' data
* definitions (and no assignments) are reflected:
execute_unload '%relpathModel%../output/temp/1INPUT.gdx';

*------------------------------

* Begin BB4 group
* SCALAR IORD_YALIAS "The ord() (relative to Y) of the first year of the present Balbase4 model NOT IN USE";
*SCALAR IYVALUE_YALIAS "";
PARAMETER ISIMWEIGHT(YMODEL) "Weighting of the individual years in a BB4 model. Presently not in use as intended (used only in BB4overview.inc).";
PARAMETER IORD_IY(YMODEL)    "The ord of the years Y over which the present Balbase4 model is formulated (used only in BB4overview.inc).";
** End BB4 group

*-------------------------------------------------------------------------------
*  Declaration of internal parameters for holding values of dual variables:
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
*  Declaration of VARIABLES:
*-------------------------------------------------------------------------------

FREE     VARIABLE VOBJ                             "Objective function value (MMoney)"; !! Unit seems to be Money
POSITIVE VARIABLE VGE_T(Y,AAA,G,S,T)               "Electricity generation (MW)";
POSITIVE VARIABLE VGH_T(Y,AAA,G,S,T)               "Heat generation (MW)";
POSITIVE VARIABLE VGF_T(Y,AAA,G,S,T)               "Fuel consumption rate (MW), existing units";
POSITIVE VARIABLE VX_T(Y,IRRRE,IRRRI,S,T)          "Electricity export from region IRRRE to IRRRI (MW)";
POSITIVE VARIABLE VGKN(Y,AAA,G)                    "New generation capacity (MW);  for storages (MWh) ";
POSITIVE VARIABLE VXKN(Y,IRRRE,IRRRI)              "New electricity transmission capacity (MW)";
POSITIVE VARIABLE VGHYPMS_T(Y,AAA,S,T)             "Contents of pumped hydro storage (MWh)";
POSITIVE VARIABLE VHYRS_S(Y,AAA,S)                 "Hydro energy equivalent at the start of the season (MWh)";
POSITIVE VARIABLE VESTOLOADT(Y,AAA,G,S,T)          "Intra-seasonal electricity storage loading (MW)";
POSITIVE VARIABLE VESTOLOADTS(Y,AAA,G,S,T)         "Inter-seasonal electricity storage loading (MW)";
POSITIVE VARIABLE VHSTOLOADT(Y,AAA,G,S,T)          "Intra-seasonal heat storage loading (MW)";
POSITIVE VARIABLE VHSTOLOADTS(Y,AAA,G,S,T)         "Inter-seasonal heat storage loading (MW)";
POSITIVE VARIABLE VESTOVOLT(Y,AAA,G,S,T)           "Electricity storage contents at beginning of time segment (MWh)";
POSITIVE VARIABLE VESTOVOLTS(Y,AAA,G,S,T)          "Electricity storage contents at beginning of time segment (MWh)";
POSITIVE VARIABLE VHSTOVOLT(Y,AAA,G,S,T)           "Heat storage contents at beginning of time segment (MWh)";
POSITIVE VARIABLE VHSTOVOLTS(Y,AAA,G,S,T)          "Heat storage contents at beginning of time segment (MWh)";
POSITIVE VARIABLE VGKNACCUMNET(Y,AAA,G)            "Accumulated new investments this BB4, at end of (ULTimo) previous (i.e., start of current) year (MW)";
POSITIVE VARIABLE VGKNACCUMGROSS(Y,AAA,G)          "Accumulated new investments this BB4, at end of previous (i.e., available at start of current) year (MW)";
POSITIVE VARIABLE VXKNACCUMNET(Y,IRRRE,IRRRI)      "Accumulated new transmission investments (MISSING: minus any decommissioning of them due to lifetime expiration) this BB4, at end of previous (i.e., available at start of current) year (MW)";

*-------------------------------------------------------------------------------
*----- Any variables, and possibly equations, for addon to be placed here: -----

$include "../../base/addons/_hooks/vardeclare.inc"

*-------------------------------------------------------------------------------
*----- End: Any variables, and possibly equations, for addon to be placed here:
*-------------------------------------------------------------------------------

* Note that intervals for variables may be set later (as .lo, .up  and/or .fx).

*-------------------------------------------------------------------------------
*  End: Declaration of VARIABLES
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
*  Declaration and definition of EQUATIONS:
*-------------------------------------------------------------------------------

* Equation declarations:

* Hans: reconsider if Y is to be everywhere TODO

EQUATIONS
   QOBJ                     "Objective function"
   QEEQ(Y,RRR,S,T)          "Electricity generation equals demand (MW)"
   QHEQ(Y,AAA,S,T)          "Heat generation equals demand (MW)"
   QGFEQ(Y,AAA,G,S,T)       "Calculate fuel consumption, existing units (MW)"
   QGFNEQ(Y,AAA,G,S,T)      "Calculate fuel consumption, new units NOT IMPLEMENTED (MW)"

   QGCBGBPR(Y,AAA,G,S,T)         "CHP generation (back pressure) limited by Cb-line (MW)"
   QGCBGBPRBYPASS1(Y,AAA,G,S,T)  "CHP generation (back pressure) with bypass limited by Cb-line (MW)"
   QGCBGBPRBYPASS2(Y,AAA,G,S,T)  "CHP generation (back pressure) with bypass limited by BYPC-line (MW)"
   QGCBGEXT(Y,AAA,G,S,T)         "CHP generation (extraction) limited by Cb-line (MW)"
   QGCVGEXT(Y,AAA,G,S,T)         "CHP generation (extraction) limited by Cv-line (MW)"
   QGGETOH(Y,AAA,G,S,T)          "Electric heat generation (MW)"

   QHYRSSEQ(Y,AAA,S)        "Hydropower with reservoir seasonal energy constraint (MW)"
   QHYRSMINVOL(Y,AAA,S)     "Hydropower reservoir - minimum level (MWh)"
   QHYRSMAXVOL(Y,AAA,S)     "Hydropower reservoir - maximum level (MWh)"
   QHYMAXG(Y,AAA,S,T)       "Regulated and unregulated hydropower production lower than capacity (MW)" !! NB:exclude hydro-run-of-river   Hans TODO
   QHYMINRS(Y,AAA,G,S)      "Hydropower reservoir - minimum level (MWh)"

   QESTOVOLT(Y,AAA,G,S,T)     "Intra-seasonal electricty storage dynamic equation (MWh)"
   QESTOVOLTS(Y,AAA,G,S,T)    "Inter-seasonal electricty storage dynamic equation (MWh)"
   QESTOVOLTSINIT(Y,AAA,G,S,T) "Inter-seasonal electricty storage level on initial timestep  (MWh)"
   QHSTOVOLT(Y,AAA,G,S,T)     "Intra-seasonal heat storage dynamic equation (MWh)"
   QHSTOVOLTS(Y,AAA,G,S,T)    "Inter-seasonal heat storage dynamic equation (MWh)"

   QHSTOLOADT(Y,AAA,G,S,T)    "Intra-seasonal Heat storage loading less than heat production from allowed technologies (MW)"
   QHSTOLOADTLIM(Y,AAA,G,S,T) "Intra-seasonal Upper limit to heat storage loading (MW)"
   QESTOLOADTLIM(Y,AAA,G,S,T) "Intra-seasonal Upper limit to electricity storage loading (MW)"
   QHSTOVOLTLIM(Y,AAA,G,S,T)  "Intra-seasonal Heat storage capacity limit (MWh)"
   QESTOVOLTLIM(Y,AAA,G,S,T)  "Intra-seasonal Electricity storage capacity limit (MWh)"
   QHSTOVGHTLIM(Y,AAA,G,S,T)"Intra-seasonal Heat storage output limit (MW)"
   QESTOVGETLIM(Y,AAA,G,S,T)"Intra-seasonal Electricity storage output limit (MW)"
   QHSTOLOADTS(Y,AAA,G,S,T)    "Inter-seasonal Heat storage loading less than heat production from allowed technologies (MW)"
   QHSTOLOADTLIMS(Y,AAA,G,S,T) "Inter-seasonal Upper limit to heat storage loading (MW)"
   QESTOLOADTLIMS(Y,AAA,G,S,T) "Inter-seasonal Upper limit to electricity storage loading (MW)"
   QHSTOVOLTLIMS(Y,AAA,G,S,T)  "Inter-seasonal Heat storage capacity limit (MWh)"
   QESTOVOLTLIMS(Y,AAA,G,S,T)  "Inter-seasonal Electricity storage capacity limit (MWh)"
   QHSTOVGHTLIMS(Y,AAA,G,S,T)"Inter-seasonal Heat storage output limit (MW)"
   QESTOVGETLIMS(Y,AAA,G,S,T)"Inter-seasonal Electricity storage output limit (MW)"

   QKEFUELC(Y,C,FFF)        "Maximum electricty capacity by year, country and fuel (MW)"
   QKEFUELR(Y,RRR,FFF)      "Maximum electricty capacity by year, region and fuel (MW)"
   QKEFUELA(Y,AAA,FFF)      "Maximum electricty capacity by year, area and fuel (MW)"

   QKTECHGROUPC(Y,C,TECH_GROUP)   "Maximum capacity by year, country and technology group (MW)"
   QKTECHGROUPR(Y,RRR,TECH_GROUP) "Maximum capacity by year, region and technology group (MW)"
   QKTECHGROUPA(Y,AAA,TECH_GROUP) "Maximum capacity by year, area and technology group (MW)"

   QKSUBTECHGROUPC(Y,C,TECH_GROUP,SUBTECH_GROUP)   "Maximum capacity by year, country and subtechnology group (MW)"
   QKSUBTECHGROUPR(Y,RRR,TECH_GROUP,SUBTECH_GROUP) "Maximum capacity by year, region and subtechnology group (MW)"
   QKSUBTECHGROUPA(Y,AAA,TECH_GROUP,SUBTECH_GROUP) "Maximum capacity by year, area and subtechnology group (MW)"

   QGMINFUELC(Y,C,FFF)      "Minimum electricity generation year, country and fuel (MWh)"
   QGMAXFUELC(Y,C,FFF)      "Maximum electricity generation year, country and fuel (MWh)"
   QGMINFUELR(Y,RRR,FFF)    "Minimum electricity generation by year, region and fuel (MWh)"
   QGMAXFUELR(Y,RRR,FFF)    "Maximum electricity generation by year, region and fuel (MWh)"
   QGMINFUELA(Y,AAA,FFF)    "Minimum electricity generation by year, area and fuel (MWh)"
   QGMAXFUELA(Y,AAA,FFF)    "Maximum electricity generation by year, area and fuel (MWh)"

   QGMINCF(Y,C,FFF)         "Minimum fuel use by year, country and fuel (GJ)"
   QGMAXCF(Y,C,FFF)         "Maximum fuel use by year, country and fuel (GJ)"
   QGEQCF(Y,C,FFF)          "Exact fuel use by year, country and fuel (GJ)"
   QGMINRF(Y,RRR,FFF)       "Minimum fuel use by year, region and fuel  (GJ)"
   QGMAXRF(Y,RRR,FFF)       "Maximum fuel use by year, region and fuel  (GJ)"
   QGEQRF(Y,RRR,FFF)        "Exact fuel use by year, region and fuel (GJ)"
   QGMINAF(Y,AAA,FFF)       "Minimum fuel use by year, area and fuel (GJ)"
   QGMAXAF(Y,AAA,FFF)       "Maximum fuel use by year, area and fuel (GJ)"
   QGEQAF(Y,AAA,FFF)        "Exact fuel use by year, area and fuel (GJ)"
   QKMINFC(Y,C,FFF)         "Minimum capacity by year, country and fuel (MW)" !! renamed from QKMAXFC(Y,C,FFF), similar with others below  Hans
   QKMAXFC(Y,C,FFF)         "Maximum capacityby year, country and fuel (MW)"
   QKEQFC(Y,C,FFF)          "Exact capacity by year, country and fuel (MW)"
   QKMINFR(Y,RRR,FFF)       "Minimum capacity by year, region and fuel (MW)"
   QKMAXFR(Y,RRR,FFF)       "Maximum capacity by year, region and fuel (MW)"
   QKEQFR(Y,RRR,FFF)        "Exact capacity by year, region and fuel (MW)"
   QKMINFA(Y,AAA,FFF)       "Minimum capacity by year, area and fuel (MW)"  !! renamed from QKMAXFC(Y,C,FFF), similar with others below   Hans
   QKMAXFA(Y,AAA,FFF)       "Maximum capacity by year, area and fuel (MW)"
   QKEQFA(Y,AAA,FFF)        "Exact capacity by year, area and fuel (MW)"
   QKMINFNA(Y,FFF)          "Minimum capacity by year and fuel constraint (aggregated countries) (MW)"
   QKMAXFNA(Y,FFF)          "Maximum capacity by year and fuel constraint (aggregated countries) (MW)"
   QKEQFNA(Y,FFF)           "Exact capacity by year and fuel constraint (aggregated countries) (MW)"

   QGMAXCFS(Y,C,FFF,S)      "Maximum fuel use by year, season, country and fuel (GJ)"
   QGMAXRFS(Y,RRR,FFF,S)    "Maximum fuel use by year, season, region and fuel  (GJ)"
   QGMAXAFS(Y,AAA,FFF,S)    "Maximum fuel use by year, season, area and fuel    (GJ)"

   QLIMCO2(Y,C)             "Limit on annual CO2-emission by year and country (kg/MW)"
   QLIMSO2(Y,C)             "Limit on annual SO2 emission by year and country (kg/MW)"
   QLIMNOX(Y,C)             "Limit on annual NOx emission by year and country (kg/MW)"

   QLIMCO2NA(Y)             "Limit on annual CO2-emission by year (aggregated countries) (kg/MW)"

   QHYFXRW(Y,RRR,S)         "Hydro with reservoir available for this region and season (MWh)"
   QHYFXCW(Y,C,S)           "Hydro with reservoir available for this country and season (MWh)"
   QBASELOAD(Y,C,S,T)       "Minimum production for baseload service providers (MW)"

*   QRESDE(Y,RRR,S,T)        "Reserve requirement proportional with demand (MW)"
*   QRESWI(Y,RRR,S,T)        "Reserve requirement proportional with wind power (MW)"

   QMAXINVESTCF(Y,C,FFF)    "Maximal investment by country and fuel during one simulated year (MW)"
   QMAXINVESTGROWTHCG(Y,C,G)"Maximum model generated capacity increase from one year to the next (MW)"
   QMAXINVESTNAF(Y,FFF)     "Maximal investment by aggerated countries and fuel during one simulated year (MW)"


*Balbase4: ---------------------------------------------------------------------
QGKNACCUMNET(Y,AAA,G)             "Accumulated new investments minus decommissioning of previous investments due to lifetime expiration available at beginning of next year (MW)"
QGKNACCUMGROSS(Y,AAA,G)           "Accumulated new investments available at beginning of next year (MW)"
QGKE_UP(Y,AAA,G,S,T)              "Capacity constraint on electricity generation (MW)"
QGKH_UP(Y,AAA,G,S,T)              "Capacity constraint on heat generation (MW)"
QGKE_LO(Y,AAA,G,FFF,S,T)          "Minimum capacity usage constraint on electricity generation capacity (MW)"
QGKH_LO(Y,AAA,G,FFF,S,T)          "Minimum capacity usage constraint on heat generation capacity (MW)"
QEGKCOMB1UP(Y,AAA,G,S,T)          "capacity constraint on electricity - combination (MW)"
QEGKCOMB2UP(Y,AAA,G,S,T)          "capacity constraint on electricity - combination (MW)"
QHGKCOMB1UP(Y,AAA,G,S,T)          "capacity constraint on heat - combination (MW)"
QHGKCOMB2UP(AAA,G,G,Y,S,T)        "capacity constraint on heat - combination (MW)"
QHYRRDISPATCH(Y,AAA,G,S,T)        "Hydro run on river can not be dispatched (MW)"
QWNDDISPATCH(Y,AAA,G,S,T)         "Wind power can not be dispatched (MW)"
QSOLEDISPATCH(Y,AAA,G,S,T)        "Solar electricity generation can not be dispatched (MW)"
QSOLHDISPATCH(Y,AAA,G,S,T)        "Solar heat generation can not be dispatched (MW)"
QWAVEDISPATCH(Y,AAA,G,S,T)        "Wave electricity generation can not be dispatched (MW)"
QXKN(Y,IRRRE,IRRRI)               "New transmission investment  - NOT IMPLEMENTED PRESENTLYT (MW)"
QXKNACCUMNET(Y,IRRRE,IRRRI)       "Accumulated new transmission investments available at beginning of next year (MW)"
QXKNACCUMGROSS(Y,IRRRE,IRRRI)     "Accumulated new transmission investments available at beginning of next year (MW)"
QXK_UP(Y,IRRRE,IRRRI,S,T)         "Capacity constraint on electricity transmission (MW)"
QXINVSYMMETRY(Y,IRRRE,IRRRI)      "Transmission investments are set symetric(MW)"


*-------------------------------------------------------------------------------
*----- Any equations declarations for addon to be placed here: -----------------
*-------------------------------------------------------------------------------


*-------------------------------------------------------------------------------
*----- End: Any equations declarations for addon to be placed here -------------
*-------------------------------------------------------------------------------
;

* Equation definitions:
*----- The objective function QOBJ: --------------------------------------------

* "Objective function"
QOBJ ..

   VOBJ =E=

SUM(Y$IY411(Y),
* Objective equation of years and with weighting of years that are in Y but not in YYY
IOF1_ * IDISCOUNTFACTOR(Y) * IWEIGHTY(Y) * (

* Cost of fuel consumption during the year:
     SUM((IAGK_HASORPOT(Y,IA,G),FFF)$(IGF(G,FFF)),
                 FUELPRICE(Y,IA,FFF) * IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGF_T(Y,IA,G,IS3,T)))


* Operation and maintainance cost:

   + SUM(IAGK_HASORPOT(Y,IA,IGKE), GOMVCOSTO(IA,IGKE) * SUM((IS3,T), IHOURSINST(IS3,T)*VGE_T(Y,IA,IGKE,IS3,T)))

   + SUM(IAGK_HASORPOT(Y,IA,IGKH), GOMVCOSTO(IA,IGKH) * SUM((IS3,T), IHOURSINST(IS3,T)*GDATA(IGKH,'GDCV')*(VGH_T(Y,IA,IGKH,IS3,T))))

   + SUM(IAGK_HASORPOT(Y,IA,G), GOMVCOSTIN(IA,G) * SUM((IS3,T), IHOURSINST(IS3,T)*VGF_T(Y,IA,G,IS3,T)))

    + IOF1000*(SUM((IA,G)$IAGK_HASORPOT(Y,IA,G),(VGKNACCUMNET(Y,IA,G)$(IAGK_HASORPOT(Y,IA,G) AND IAGKN(IA,G)) + GKFX(Y,IA,G)$IAGKFX(Y,IA,G))*GOMFCOST(IA,G)))


*  Hydro with storage seasonal price profile:

   + SUM((IA,IGHYRS)$IAGK_HASORPOT(Y,IA,IGHYRS), SUM((IS3,T), HYPPROFILS(IA,IS3)* IHOURSINST(IS3,T)
     * VGE_T(Y,IA,IGHYRS,IS3,T)))


* Transmission cost:

   + SUM((IRE,IRI)$IXK_HASORPOT(Y,IRE,IRI),
       SUM((IS3,T), IHOURSINST(IS3,T) * (VX_T(Y,IRE,IRI,IS3,T) * XCOST(IRE,IRI))))


* Investment costs, new generation and storage capacity:
*
*   The ANNUITY of the investment cost relative to VGKN is to be taken every remaining year in the present BB4 model,
*   discounted back to the first year in the present BB4 model, this latter is represented by factor IY4GINVCOSTWEIGHT below.
*   Discounting further back from first year in the present BB4 model to the first year in Y is handled by the factor IDISCOUNTFACTOR(Y) above.
*   The relative weight of the years is represented by   TODO: sammenlign med SONYstick:
   + IOF1000000*(SUM((IA,G)$IAGKNY(Y,IA,G), VGKN(Y,IA,G)*GINVCOST(IA,G)*(SUM(C$ICA(C,IA),ANNUITYCG(C,G)))*SUM(IYALIAS2$(ORD(IYALIAS2) EQ ORD(Y)),IYHASANNUITYG(Y,IYALIAS2,G))))

* Investment costs, generation and storage capacity invested in previous years
   + IOF1000000*(SUM((IYALIAS2,IA,G)$(IAGKNY(IYALIAS2,IA,G) AND (ORD(IYALIAS2) LT ORD(Y))), VGKN(IYALIAS2,IA,G)*GINVCOST(IA,G)*(SUM(C$ICA(C,IA),ANNUITYCG(C,G)))*IYHASANNUITYG(IYALIAS2,Y,G)))

* Investment costs, new transmission capacity
* (the average of the annuities for the two countries in question is used for international transmission):
* TODO: sammenlign med SONYstick:
    + SUM((IRE,IRI)$IXKN(Y,IRI,IRE),IOF05*VXKN(Y,IRE,IRI)*XINVCOST(Y,IRE,IRI)*
      (IOF05* (SUM(C$CCCRRR(C,IRE),ANNUITYCX(C))+SUM(C$CCCRRR(C,IRI),ANNUITYCX(C))))*SUM(IYALIAS2$(ORD(IYALIAS2) EQ ORD(Y)),IYHASANNUITYX(IYALIAS2,Y)))

*Investment costs, transmission capacity invested in previous years
    + SUM((IYALIAS2,IRE,IRI)$(IXKN(IYALIAS2,IRI,IRE) AND (ORD(IYALIAS2) LT ORD(Y))),IOF05*VXKN(IYALIAS2,IRE,IRI)*XINVCOST(IYALIAS2,IRE,IRI)*
      (IOF05* (SUM(C$CCCRRR(C,IRE),ANNUITYCX(C))+SUM(C$CCCRRR(C,IRI),ANNUITYCX(C))))*IYHASANNUITYX(IYALIAS2,Y))



* Emission taxes

    + SUM(C, SUM((IA,G)$(ICA(C,IA) AND IAGK_HASORPOT(Y,IA,G)), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_CO2(G)*IOF0001) * IOF3P6 * VGF_T(Y,IA,G,IS3,T)) * M_POL(Y,"TAX_CO2",C)))

    + SUM(C, SUM((IA,G)$(ICA(C,IA) AND IAGK_HASORPOT(Y,IA,G)), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_SO2(G)*IOF0001) * IOF3P6 * VGF_T(Y,IA,G,IS3,T)) * M_POL(Y,"TAX_SO2",C)))

    + SUM(C, SUM((IA,G)$(ICA(C,IA) AND IAGK_HASORPOT(Y,IA,G)), SUM((IS3,T), IHOURSINST(IS3,T) * (GDATA(G,'GDNOX')*IOF0000001) * IOF3P6 * VGF_T(Y,IA,G,IS3,T)) * M_POL(Y,"TAX_NOX",C)))


* Add-on objective function contributions

$include "../../base/addons/_hooks/qobj.inc";

* This file contains Heat transmission induced additions to the objective function.
$ifi %HEATTRANS%==yes $include "../../base/addons/heattrans/model/htcosts.inc";


)
)

;

*----- End: The objective function QOBJ ----------------------------------------

*--------------------------Balance equations for electricity and heat ----------


* "Electricity generation equals demand (MW)"
QEEQ(IY411,IR,IS3,T) ..

      SUM(IA$RRRAAA(IR,IA), SUM(IGE$(IAGK_HASORPOT(IY411,IA,IGE) AND IGNOTETOH(IGE)),VGE_T(IY411,IA,IGE,IS3,T)))
    - SUM(IA$RRRAAA(IR,IA), SUM(IGETOH$IAGK_HASORPOT(IY411,IA,IGETOH), VGE_T(IY411,IA,IGETOH,IS3,T)))
    + SUM(IRE$IXK_HASORPOT(IY411,IRE,IR), VX_T(IY411,IRE,IR,IS3,T)*(1-XLOSS(IRE,IR)))
    - SUM(IA$RRRAAA(IR,IA),SUM(IGESTO$IAGK_HASORPOT(IY411,IA,IGESTO),VESTOLOADT(IY411,IA,IGESTO,IS3,T)))
    - SUM(IA$RRRAAA(IR,IA),SUM(IGESTOS$IAGK_HASORPOT(IY411,IA,IGESTOS),VESTOLOADTS(IY411,IA,IGESTOS,IS3,T)))

    =E=
      IX3FX_T(IY411,IR,IS3,T)
    + (   (SUM(DEUSER, ((DE(IY411,IR,DEUSER) * DE_VAR_T(IR,DEUSER,IS3,T)) / IDE_SUMST(IR,DEUSER))$(IDE_SUMST(IR,DEUSER) GT 0))
      )/(1-DISLOSS_E(IR)))
      + SUM(IRI$IXK_HASORPOT(IY411,IR,IRI),VX_T(IY411,IR,IRI,IS3,T))


$include "../../base/addons/_hooks/qeeq.inc"
;

* "Heat generation equals demand (MW)"
QHEQ(IY411,IA,IS3,T)$(SUM(DHUSER, IDH_SUMST(IA,DHUSER))) ..
   + SUM(IGBPR$IAGK_HASORPOT(IY411,IA,IGBPR),VGH_T(IY411,IA,IGBPR,IS3,T))
   + SUM(IGEXT$IAGK_HASORPOT(IY411,IA,IGEXT),VGH_T(IY411,IA,IGEXT,IS3,T))
   + SUM(IGHH$IAGK_HASORPOT(IY411,IA,IGHH),VGH_T(IY411,IA,IGHH,IS3,T))
   + SUM(IGETOH$IAGK_HASORPOT(IY411,IA,IGETOH),VGH_T(IY411,IA,IGETOH,IS3,T))
   - SUM(IGHSTO$IAGK_HASORPOT(IY411,IA,IGHSTO),VHSTOLOADT(IY411,IA,IGHSTO,IS3,T))
   - SUM(IGHSTOS$IAGK_HASORPOT(IY411,IA,IGHSTOS),VHSTOLOADTS(IY411,IA,IGHSTOS,IS3,T))
    =E=
     (SUM(DHUSER, ((DH(IY411,IA,DHUSER) * DH_VAR_T(IA,DHUSER,IS3,T)) / IDH_SUMST(IA,DHUSER))$(IDH_SUMST(IA,DHUSER) GT 0))
         )/(1-DISLOSS_H(IA))
* Adds heat transmission if selected in the gas add-on
$ifi %HEATTRANS%==yes $include "../../base/addons/heattrans/model/htheatbalance.inc";

$include "../../base/addons/_hooks/qheq.inc"
;


* Fuel consumption rate.
QGFEQ(IY411,IA,G,IS3,T)$IAGK_HASORPOT(IY411,IA,G) ..
     VGF_T(IY411,IA,G,IS3,T)
  =E=
   ( (VGE_T(IY411,IA,G,IS3,T)/(GDATA(G,'GDFE')*(1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G))))$(IGNOTETOH(G) AND IGE(G))
    +(GDATA(G,'GDCV')*VGH_T(IY411,IA,G,IS3,T)/(GDATA(G,'GDFE')*(1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G))))$IGH(G)
    )$(NOT IGBYPASS(G))

+  ( ((GDATA(G,'GDCB')*((VGH_T(IY411,IA,G,IS3,T)*GDATA(G,'GDBYPASSC') + VGE_T(IY411,IA,G,IS3,T))/(GDATA(G,'GDCB') + GDATA(G,'GDBYPASSC')))/(GDATA(G,'GDFE')*(1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G)))))
   + ((GDATA(G,'GDCV')*((VGH_T(IY411,IA,G,IS3,T)*GDATA(G,'GDBYPASSC') + VGE_T(IY411,IA,G,IS3,T))/(GDATA(G,'GDCB') + GDATA(G,'GDBYPASSC')))/(GDATA(G,'GDFE')*(1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G)))))
   )$IGBYPASS(G)
$include "../../base/addons/_hooks/qgfeq.inc"
;

*------ Generation technologies" electricity/heat operating area: --------------

* Back pressure units:
* "CHP generation (back pressure) limited by Cb-line (MW)"
QGCBGBPR(IY411,IA,IGBPR,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGBPR) AND (NOT IGBYPASS(IGBPR))) ..
      VGE_T(IY411,IA,IGBPR,IS3,T) =E= VGH_T(IY411,IA,IGBPR,IS3,T) * GDATA(IGBPR,'GDCB');

QGCBGBPRBYPASS1(IY411,IA,IGBPR,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGBPR) AND IGBYPASS(IGBPR)) ..
  VGE_T(IY411,IA,IGBPR,IS3,T) =L= VGH_T(IY411,IA,IGBPR,IS3,T) * GDATA(IGBPR,'GDCB');

QGCBGBPRBYPASS2(IY411,IA,IGBPR,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGBPR) AND IGBYPASS(IGBPR))..
  VGE_T(IY411,IA,IGBPR,IS3,T) =L=
   (1+(GDATA(IGBPR,'GDBYPASSC')/GDATA(IGBPR,'GDCB')))*(
      GKFX(IY411,IA,IGBPR)$IAGKFX(IY411,IA,IGBPR)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGBPR)$IGDECOMEXOPOT(IY411,IA,IGBPR)
      + VGKNACCUMNET(IY411,IA,IGBPR)$(IAGK_HASORPOT(IY411,IA,IGBPR) AND IAGKN(IA,IGBPR))
      )*(1$(NOT GEFFRATE(IA,IGBPR))+GEFFRATE(IA,IGBPR)) - VGH_T(IY411,IA,IGBPR,IS3,T) * GDATA(IGBPR,'GDBYPASSC');

* Extraction units:

* "CHP generation (extraction) limited by Cb-line (MW)"
QGCBGEXT(IAGK_HASORPOT(IY411,IA,IGEXT),IS3,T) ..
   VGE_T(IY411,IA,IGEXT,IS3,T) =G= VGH_T(IY411,IA,IGEXT,IS3,T) * GDATA(IGEXT,"GDCB");


* "CHP generation (extraction) limited by Cv-line (MW)"
QGCVGEXT(IAGK_HASORPOT(IY411,IA,IGEXT),IS3,T)$
$ifi not %COMBTECH%==yes  1 ..
$ifi     %COMBTECH%==yes  (NOT IGCOMB2(IGEXT)) ..
* This will have a value if not a combination technology
     (GKFX(IY411,IA,IGEXT)$IAGKFX(IY411,IA,IGEXT)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGEXT)$IGDECOMEXOPOT(IY411,IA,IGEXT)
      + VGKNACCUMNET(IY411,IA,IGEXT)$(IAGK_HASORPOT(IY411,IA,IGEXT) AND IAGKN(IA,IGEXT))
     )*(1$(NOT IGKRATE(IA,IGEXT,IS3,T)) + IGKRATE(IA,IGEXT,IS3,T))
         - VGH_T(IY411,IA,IGEXT,IS3,T) * GDATA(IGEXT,'GDCV')

$ifi %COMBTECH%==yes  * This will have a value in case of a combination technology. !!TODO
$ifi %COMBTECH%==yes    + SUM(IGCOMB2$GGCOMB(IGEXT,IGCOMB2), VGH_T(IY411,IA,IGCOMB2,IS3,T) * GDATA(IGCOMB2,"GDCV"))$IGCOMB1(IGEXT)   !!TODO
    =G=
   VGE_T(IY411,IA,IGEXT,IS3,T)
$ifi %COMBTECH%==yes  * Add secondary generation if combination technologies are used     !!TODO
$ifi %COMBTECH%==yes  + SUM(IGCOMB2$GGCOMB(IGEXT,IGCOMB2), VGE_T(IY411,IA,IGCOMB2,IS3,T))$IGCOMB1(IGEXT)  !!TODO
;


* Electric heat pumps:

* "Electric heat generation (MW)"
QGGETOH(IAGK_HASORPOT(IY411,IA,IGETOH),IS3,T) ..
       VGE_T(IY411,IA,IGETOH,IS3,T) =E= VGH_T(IY411,IA,IGETOH,IS3,T) / GDATA(IGETOH,'GDFE');


*--------- Dispatchable generation technologies" operating area: ---------------


*-------------- Hydropower with reservoirs: ------------------------------------
*
* Hydro reservoir content - dynamic seasonal equation

* TODO eventually: linking between years in BB4
* "Hydropower with reservoir seasonal energy constraint (MWh)"
QHYRSSEQ(IY411,IA,S)$(SUM(IGHYRS,IAGK_HASORPOT(IY411,IA,IGHYRS)) AND IS3(S))..
      VHYRS_S(IY411,IA,S)
       +  IHYINF_S(IA,S) * (
      SUM(IGHYRS,
        GKFX(IY411,IA,IGHYRS)$IAGKFX(IY411,IA,IGHYRS)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGHYRS)$IGDECOMEXOPOT(IY411,IA,IGHYRS)
       +VGKNACCUMNET(IY411,IA,IGHYRS)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHYRS))
        )
         )
         -SUM(IGHYRS$IAGK_HASORPOT(IY411,IA,IGHYRS),SUM(T,IHYRST(S,T)*(VGE_T(IY411,IA,IGHYRS,S,T))))

      =G=  VHYRS_S(IY411,IA,S++1)

$include "../../base/addons/_hooks/qhyrsseq.inc"
;

* "Hydropower reservoir - minimum level (MWh)"
QHYRSMINVOL(IY411,IA,S)$(HYRSDATA(IA,"HYRSMINVOL",S) AND SUM(IGHYRS$IAGK_HASORPOT(IY411,IA,IGHYRS),1) AND IS3(S))..
     VHYRS_S(IY411,IA,S)  =G=  HYRSDATA(IA,"HYRSMINVOL",S)*
       SUM(IGHYRS,   HYRSMAXVOL_G(IA,IGHYRS)*(
         GKFX(IY411,IA,IGHYRS)$IAGKFX(IY411,IA,IGHYRS)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGHYRS)$IGDECOMEXOPOT(IY411,IA,IGHYRS)
        +VGKNACCUMNET(IY411,IA,IGHYRS)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHYRS))
        ))
$include "../../base/addons/_hooks/qhyrsminvol.inc"
;

* "Hydropower reservoir - maximum level (MWh)"
QHYRSMAXVOL(IY411,IA,S)$(HYRSDATA(IA,"HYRSMAXVOL",S) AND SUM(IGHYRS$IAGK_HASORPOT(IY411,IA,IGHYRS),1) AND IS3(S))..
       HYRSDATA(IA,"HYRSMAXVOL",S) *
       SUM(IGHYRS,  HYRSMAXVOL_G(IA,IGHYRS)*(
         GKFX(IY411,IA,IGHYRS)$IAGKFX(IY411,IA,IGHYRS)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGHYRS)$IGDECOMEXOPOT(IY411,IA,IGHYRS)
        +VGKNACCUMNET(IY411,IA,IGHYRS)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHYRS))
        ))
       =G= VHYRS_S(IY411,IA,S)
$include "../../base/addons/_hooks/qhyrsmaxvol.inc"
;



* "Regulated and unregulated hydropower production lower than capacity (MW)"
QHYMAXG(IY411,IA,IS3,T)$SUM(IGHYRS,IAGK_HASORPOT(IY411,IA,IGHYRS))..
      SUM(IGHYRS$IAGK_HASORPOT(IY411,IA,IGHYRS),VGE_T(IY411,IA,IGHYRS,IS3,T))
      =L=
      SUM(IGHYRS,
         (GKFX(IY411,IA,IGHYRS)$IAGKFX(IY411,IA,IGHYRS)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGHYRS)$IGDECOMEXOPOT(IY411,IA,IGHYRS)
         +VGKNACCUMNET(IY411,IA,IGHYRS)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHYRS))
         )*(1$(NOT IGKRATE(IA,IGHYRS,IS3,T)) + IGKRATE(IA,IGHYRS,IS3,T))
       )
$include "../../base/addons/_hooks/qhymaxg.inc"
;

*------------ Short term heat and electricity storages:-------------------------

* "Electricty storage dynamic equation (MWh)"
QESTOVOLT(IY411,IA,IGESTO,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGESTO))..
    VESTOVOLT(IY411,IA,IGESTO,IS3,T++1) =E= VESTOVOLT(IY411,IA,IGESTO,IS3,T)
  + CHRONOHOUR(IS3,T)*
    (VESTOLOADT(IY411,IA,IGESTO,IS3,T)
  - SUM(IAGK_HASORPOT(IY411,IA,IGESTO), VGE_T(IY411,IA,IGESTO,IS3,T)/GDATA(IGESTO,'GDFE'))
  )
$include "../../base/addons/_hooks/qestovolt.inc"
;

* "Inter-seasonal electricty storage dynamic equation (MWh)"
QESTOVOLTS(IY411,IA,IGESTOS,S,T)$(IAGK_HASORPOT(IY411,IA,IGESTOS) AND IS3(S))..
    VESTOVOLTS(IY411,IA,IGESTOS,S,T)*(1-GDATA(IGESTOS,'GDSTOLOSS'))
  + CHRONOHOUR(S,T)*
  (VESTOLOADTS(IY411,IA,IGESTOS,S,T)*(1-GDATA(IGESTOS,'GDLOADLOSS'))
  - SUM(IAGK_HASORPOT(IY411,IA,IGESTOS), VGE_T(IY411,IA,IGESTOS,S,T)/GDATA(IGESTOS,'GDFE'))
  )
    =E=
VESTOVOLTS(IY411,IA,IGESTOS,S,T+1)+SUM(ITALIAS$(ORD(ITALIAS) EQ 1),VESTOVOLTS(IY411,IA,IGESTOS,S++1,ITALIAS)$(ORD(T) EQ CARD(T)))

$include "../../base/addons/_hooks/qestovolts.inc"
;

* "Inter-seasonal electricty storage level on initial timestep  (MWh)"
QESTOVOLTSINIT(IY411,IA,IGESTOS,S,T)$(IAGK_HASORPOT(IY411,IA,IGESTOS) AND ORD(S) EQ 1 AND ORD(T) EQ 1)..
         VESTOVOLTS(IY411,IA,IGESTOS,S,T)
         =G=
         (STOVOLTSINIT(IA,IGESTOS)*(
      GKFX(IY411,IA,IGESTOS)$IAGKFX(IY411,IA,IGESTOS)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGESTOS)$IGDECOMEXOPOT(IY411,IA,IGESTOS)
      + VGKNACCUMNET(IY411,IA,IGESTOS)$(IAGK_HASORPOT(IY411,IA,IGESTOS) AND IAGKN(IA,IGESTOS))
      )*(1$(NOT GEFFRATE(IA,IGESTOS))+GEFFRATE(IA,IGESTOS)))$(IYFIRST(IY411))
         + SUM((ISALIAS,ITALIAS)$(IY401(IY411) AND ORD(ISALIAS) EQ 1 AND ORD(ITALIAS) EQ 1),VESTOVOLTS(IY411,IA,IGESTOS,ISALIAS,ITALIAS))
;

* "Heat storage dynamic equation (MWh)"
QHSTOVOLT(IY411,IA,IGHSTO,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGHSTO))..
    VHSTOVOLT(IY411,IA,IGHSTO,IS3,T)
  + CHRONOHOUR(IS3,T)*
  (VHSTOLOADT(IY411,IA,IGHSTO,IS3,T)
  - SUM(IAGK_HASORPOT(IY411,IA,IGHSTO), VGH_T(IY411,IA,IGHSTO,IS3,T)/GDATA(IGHSTO,'GDFE')) )
    =E= VHSTOVOLT(IY411,IA,IGHSTO,IS3,T++1)
$include "../../base/addons/_hooks/qhstovolt.inc"
;

*  "Inter-seasonal heat storage dynamic equation (MWh)"
QHSTOVOLTS(IY411,IA,IGHSTOS,S,T)$(IAGK_HASORPOT(IY411,IA,IGHSTOS) AND IS3(S))..
    VHSTOVOLTS(IY411,IA,IGHSTOS,S,T)
  + CHRONOHOUR(S,T)*
  (VHSTOLOADTS(IY411,IA,IGHSTOS,S,T)
  - SUM(IAGK_HASORPOT(IY411,IA,IGHSTOS), VGH_T(IY411,IA,IGHSTOS,S,T)/GDATA(IGHSTOS,'GDFE'))
  )
    =E=
VHSTOVOLTS(IY411,IA,IGHSTOS,S,T+1)+SUM(ITALIAS$(ORD(ITALIAS) EQ 1),VHSTOVOLTS(IY411,IA,IGHSTOS,S++1,ITALIAS)$(ORD(T) EQ CARD(T)))

$include "../../base/addons/_hooks/qhstovolts.inc"
;


* "Intra-seasonal Heat storage loading less than heat production from allowed technologies (MW)"
QHSTOLOADT(IY411,IA,IGHSTO,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGHSTO))..
   SUM(IGH$(IAGK_HASORPOT(IY411,IA,IGH) AND ILINKSTO(IGHSTO,IGH)), VGH_T(IY411,IA,IGH,IS3,T))
         =G=
   VHSTOLOADT(IY411,IA,IGHSTO,IS3,T)
;

* "Inter-seasonal Heat storage loading less than heat production from allowed technologies (MW)"
QHSTOLOADTS(IY411,IA,IGHSTOS,S,T)$(IAGK_HASORPOT(IY411,IA,IGHSTOS) AND IS3(S))..
   SUM(IGH$(IAGK_HASORPOT(IY411,IA,IGH) AND ILINKSTO(IGHSTOS,IGH)), VGH_T(IY411,IA,IGH,S,T))
         =G=
   VHSTOLOADTS(IY411,IA,IGHSTOS,S,T)
;


* "Upper limit to heat storage loading (MW)"
QHSTOLOADTLIM(IY411,IA,IGHSTO,IS3,T)$((SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHSTO)) OR IGDECOMEXOPOT(IY411,IA,IGHSTO)) AND IAGK_HASORPOT(IY411,IA,IGHSTO))..
* Existing, accumulated new previous capacity and new investment this year
* Complement to assigning VHSTOLOADT.UP for the case with endogenous IGHSTO investments.
     ((GKFX(IY411,IA,IGHSTO)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGHSTO)$IGDECOMEXOPOT(IY411,IA,IGHSTO)
       )/GDATA(IGHSTO,'GDSTOHLOAD')
      + VGKNACCUMNET(IY411,IA,IGHSTO)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHSTO))/GDATA(IGHSTO,'GDSTOHLOAD')
     )*(1$(NOT IGKRATE(IA,IGHSTO,IS3,T)) + IGKRATE(IA,IGHSTO,IS3,T))
         =G=
   VHSTOLOADT(IY411,IA,IGHSTO,IS3,T)
;


* "Upper limit to heat storage loading (MW)"
QHSTOLOADTLIMS(IY411,IA,IGHSTOS,S,T)$((SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHSTOS)) OR IGDECOMEXOPOT(IY411,IA,IGHSTOS)) AND IAGK_HASORPOT(IY411,IA,IGHSTOS) AND IS3(S))..
* Existing, accumulated new previous capacity and new investment this year
* Complement to assigning VHSTOLOADTS.UP for the case with endogenous IGHSTOS investments.
     ((GKFX(IY411,IA,IGHSTOS)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGHSTOS)$IGDECOMEXOPOT(IY411,IA,IGHSTOS)
)/GDATA(IGHSTOS,'GDSTOHLOAD')
      + VGKNACCUMNET(IY411,IA,IGHSTOS)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHSTOS))/GDATA(IGHSTOS,'GDSTOHLOAD')
     )*(1$(NOT IGKRATE(IA,IGHSTOS,S,T)) + IGKRATE(IA,IGHSTOS,S,T))
         =G=
   VHSTOLOADTS(IY411,IA,IGHSTOS,S,T)
;


* "Upper limit to electricity storage loading (MW)"
QESTOLOADTLIM(IY411,IA,IGESTO,IS3,T)$((SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGESTO)) OR IGDECOMEXOPOT(IY411,IA,IGESTO)) AND IAGK_HASORPOT(IY411,IA,IGESTO))..
* Existing, accumulated new previous capacity and new investment this year.
* Complement to assigning VESTOLOADT.UP for the case with endogenous IGESTO investments.
     ((GKFX(IY411,IA,IGESTO)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGESTO)$IGDECOMEXOPOT(IY411,IA,IGESTO)
)/GDATA(IGESTO,"GDSTOHLOAD")
      + VGKNACCUMNET(IY411,IA,IGESTO)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGESTO))/GDATA(IGESTO,"GDSTOHLOAD")
     ) * (1$(NOT IGKRATE(IA,IGESTO,IS3,T)) + IGKRATE(IA,IGESTO,IS3,T))

         =G=
   VESTOLOADT(IY411,IA,IGESTO,IS3,T)
;

* "Upper limit to electricity storage loading (MW)"
QESTOLOADTLIMS(IY411,IA,IGESTOS,S,T)$((SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGESTOS)) OR IGDECOMEXOPOT(IY411,IA,IGESTOS)) AND IAGK_HASORPOT(IY411,IA,IGESTOS) AND IS3(S))..
* Existing, accumulated new previous capacity and new investment this year.
* Complement to assigning VESTOLOADTS.UP for the case with endogenous IGESTOS investments.
     ((GKFX(IY411,IA,IGESTOS)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGESTOS)$IGDECOMEXOPOT(IY411,IA,IGESTOS)
)/GDATA(IGESTOS,"GDSTOHLOAD")
      + VGKNACCUMNET(IY411,IA,IGESTOS)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGESTOS))/GDATA(IGESTOS,"GDSTOHLOAD")
     ) * (1$(NOT IGKRATE(IA,IGESTOS,S,T)) + IGKRATE(IA,IGESTOS,S,T))

         =G=
   VESTOLOADTS(IY411,IA,IGESTOS,S,T)
;



* "Intra-seasonal Heat storage output limit (MW)"
QHSTOVGHTLIM(IY411,IA,IGHSTO,IS3,T)$((SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHSTO)) OR IGDECOMEXOPOT(IY411,IA,IGHSTO)) AND IAGK_HASORPOT(IY411,IA,IGHSTO))..
* Existing, accumulated new previous capacity and new investment this year limit storage output
     (   (GKFX(IY411,IA,IGHSTO)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGHSTO)$IGDECOMEXOPOT(IY411,IA,IGHSTO)
)/GDATA(IGHSTO,"GDSTOHUNLD")
      + VGKNACCUMNET(IY411,IA,IGHSTO)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHSTO))/GDATA(IGHSTO,"GDSTOHUNLD")
     )*(1$(NOT IGKRATE(IA,IGHSTO,IS3,T)) + IGKRATE(IA,IGHSTO,IS3,T))
         =G=
   VGH_T(IY411,IA,IGHSTO,IS3,T)
;


* "Inter-seasonal Heat storage output limit (MW)"
QHSTOVGHTLIMS(IY411,IA,IGHSTOS,S,T)$((SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHSTOS)) OR IGDECOMEXOPOT(IY411,IA,IGHSTOS)) AND IAGK_HASORPOT(IY411,IA,IGHSTOS) AND IS3(S))..
* Existing, accumulated new previous capacity and new investment this year limit storage output
     (   (GKFX(IY411,IA,IGHSTOS)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGHSTOS)$IGDECOMEXOPOT(IY411,IA,IGHSTOS)
)/GDATA(IGHSTOS,"GDSTOHUNLD")
      + VGKNACCUMNET(IY411,IA,IGHSTOS)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHSTOS))/GDATA(IGHSTOS,"GDSTOHUNLD")
     )*(1$(NOT IGKRATE(IA,IGHSTOS,S,T)) + IGKRATE(IA,IGHSTOS,S,T))
         =G=
   VGH_T(IY411,IA,IGHSTOS,S,T)
;


* "Intra-seasonal Electricity storage output limit (MW)"
QESTOVGETLIM(IY411,IA,IGESTO,IS3,T)$((SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGESTO)) OR IGDECOMEXOPOT(IY411,IA,IGESTO)) AND IAGK_HASORPOT(IY411,IA,IGESTO))..
* Existing, accumulated new previous capacity and new investment this year limit storage output
     (   (GKFX(IY411,IA,IGESTO)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGESTO)$IGDECOMEXOPOT(IY411,IA,IGESTO)
)/GDATA(IGESTO,"GDSTOHUNLD")
      + VGKNACCUMNET(IY411,IA,IGESTO)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGESTO))/GDATA(IGESTO,"GDSTOHUNLD")
     ) * (1$(NOT IGKRATE(IA,IGESTO,IS3,T)) + IGKRATE(IA,IGESTO,IS3,T))
         =G=
   VGE_T(IY411,IA,IGESTO,IS3,T)
;

QESTOVGETLIMS(IY411,IA,IGESTOS,S,T)$((SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGESTOS)) OR IGDECOMEXOPOT(IY411,IA,IGESTOS)) AND IAGK_HASORPOT(IY411,IA,IGESTOS) AND IS3(S))..
* Existing, accumulated new previous capacity and new investment this year limit storage output
     (   (GKFX(IY411,IA,IGESTOS)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGESTOS)$IGDECOMEXOPOT(IY411,IA,IGESTOS)
)/GDATA(IGESTOS,"GDSTOHUNLD")
      + VGKNACCUMNET(IY411,IA,IGESTOS)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGESTOS))/GDATA(IGESTOS,"GDSTOHUNLD")
     ) * (1$(NOT IGKRATE(IA,IGESTOS,S,T)) + IGKRATE(IA,IGESTOS,S,T))
         =G=
   VGE_T(IY411,IA,IGESTOS,S,T)
;


* "Heat storage capacity limit (MWh)"
QHSTOVOLTLIM(IY411,IA,IGHSTO,IS3,T)$((SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHSTO)) OR IGDECOMEXOPOT(IY411,IA,IGHSTO)) AND IAGK_HASORPOT(IY411,IA,IGHSTO))..
* Existing, accumulated new previous capacity and new investment this year
     GKFX(IY411,IA,IGHSTO)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGHSTO)$IGDECOMEXOPOT(IY411,IA,IGHSTO)
   + VGKNACCUMNET(IY411,IA,IGHSTO)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHSTO))
         =G=
  VHSTOVOLT(IY411,IA,IGHSTO,IS3,T)
;

* "Heat storage capacity limit (MWh)"
QHSTOVOLTLIMS(IY411,IA,IGHSTOS,S,T)$((SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHSTOS)) OR IGDECOMEXOPOT(IY411,IA,IGHSTOS)) AND IAGK_HASORPOT(IY411,IA,IGHSTOS) AND IS3(S))..
* Existing, accumulated new previous capacity and new investment this year
     GKFX(IY411,IA,IGHSTOS)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGHSTOS)$IGDECOMEXOPOT(IY411,IA,IGHSTOS)
   + VGKNACCUMNET(IY411,IA,IGHSTOS)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHSTOS))
         =G=
  VHSTOVOLTS(IY411,IA,IGHSTOS,S,T)
;

* "Inter-seasonal Electricity storage capacity limit (MWh)"
QESTOVOLTLIM(IY411,IA,IGESTO,IS3,T)$((SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGESTO)) OR IGDECOMEXOPOT(IY411,IA,IGESTO)) AND IAGK_HASORPOT(IY411,IA,IGESTO))..
* Existing or accumulated capacity
   GKFX(IY411,IA,IGESTO)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGESTO)$IGDECOMEXOPOT(IY411,IA,IGESTO)
   + VGKNACCUMNET(IY411,IA,IGESTO)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGESTO))
         =G=
  VESTOVOLT(IY411,IA,IGESTO,IS3,T)
;

QESTOVOLTLIMS(IY411,IA,IGESTOS,S,T)$((SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGESTOS)) OR IGDECOMEXOPOT(IY411,IA,IGESTOS)) AND IAGK_HASORPOT(IY411,IA,IGESTOS) AND IS3(S))..
* Existing or accumulated capacity
   GKFX(IY411,IA,IGESTOS)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGESTOS)$IGDECOMEXOPOT(IY411,IA,IGESTOS)
   + VGKNACCUMNET(IY411,IA,IGESTOS)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGESTOS))
         =G=
  VESTOVOLTS(IY411,IA,IGESTOS,S,T)
;


*---------- Fuel restrictions --------------------------------------------------

* "Maximum electricty capacity by year, country and fuel (MW)"
QKEFUELC(IY411,C,FFF)$FKPOT(C,FFF).. !! EPS convention on FKPOT: 0 implies no restriction, "EPS" implies zero MW.
    SUM((IA,G)$(IAGKFX(IY411,IA,G) AND IGF(G,FFF) AND ICA(C,IA)),
    GKFX(IY411,IA,G)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
    )
      +SUM(IAGK_HASORPOT(IY411,IA,G)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G)) AND IGF(G,FFF) AND ICA(C,IA)), VGKNACCUMNET(IY411,IA,G))
      =L=  FKPOT(C,FFF)
$include "../../base/addons/_hooks/qkefuelc.inc"
;

* "Maximum electricty capacity by year, region and fuel (MW)"
QKEFUELR(IY411,IR,FFF)$FKPOT(IR,FFF).. !! EPS convention on FKPOT: 0 implies no restriction, "EPS" implies zero MW.
    SUM((IA,G)$(IAGKFX(IY411,IA,G) AND IGF(G,FFF) AND RRRAAA(IR,IA)),
    GKFX(IY411,IA,G)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
    )
      +SUM(IAGK_HASORPOT(IY411,IA,G)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G)) AND IGF(G,FFF) AND RRRAAA(IR,IA)), VGKNACCUMNET(IY411,IA,G))
      =L=  FKPOT(IR,FFF)
$include "../../base/addons/_hooks/qkefuelr.inc"
;

* "Maximum electricty capacity by year, area and fuel (MW)"
QKEFUELA(IY411,IA,FFF)$FKPOT(IA,FFF).. !! EPS convention on FKPOT: 0 implies no restriction, "EPS" implies zero MW.
    SUM(G$(IAGKFX(IY411,IA,G) AND IGF(G,FFF)),
    GKFX(IY411,IA,G)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
    )
      +SUM(IAGK_HASORPOT(IY411,IA,G)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G)) AND IGF(G,FFF)), VGKNACCUMNET(IY411,IA,G))
      =L=  FKPOT(IA,FFF)
$include "../../base/addons/_hooks/qkefuela.inc"
;

*---------- Fuel restrictions - end --------------------------------------------
*--- Electricity generation restrictions by fuel -------------------------------

* "Minimum electricity generation year, country and fuel (MWh)"
QGMINFUELC(IY411,C,FFF)$FGEMIN(C,FFF)..
    SUM(IAGK_HASORPOT(IY411,IA,IGE)$(IGF(IGE,FFF) AND ICA(C,IA)),SUM((IS3,T),IHOURSINST(IS3,T)*VGE_T(IY411,IA,IGE,IS3,T)*(1$(NOT GEFFRATE(IA,IGE))+GEFFRATE(IA,IGE))))
      =G= FGEMIN(C,FFF);

* "Maximum electricity generation year, country and fuel (MWh)"
QGMAXFUELC(IY411,C,FFF)$FGEMAX(C,FFF)..
    SUM(IAGK_HASORPOT(IY411,IA,IGE)$(IGF(IGE,FFF) AND ICA(C,IA)),SUM((IS3,T),IHOURSINST(IS3,T)*VGE_T(IY411,IA,IGE,IS3,T)*(1$(NOT GEFFRATE(IA,IGE))+GEFFRATE(IA,IGE))))
      =L= FGEMAX(C,FFF);

* "Minimum electricity generation by year, region and fuel (MWh)"
QGMINFUELR(IY411,IR,FFF)$FGEMIN(IR,FFF)..
    SUM(IAGK_HASORPOT(IY411,IA,IGE)$(IGF(IGE,FFF) AND RRRAAA(IR,IA)),SUM((IS3,T),IHOURSINST(IS3,T)*VGE_T(IY411,IA,IGE,IS3,T)*(1$(NOT GEFFRATE(IA,IGE))+GEFFRATE(IA,IGE))))
      =G= FGEMIN(IR,FFF);

* "Maximum electricity generation by year, region and fuel (MWh)"
QGMAXFUELR(IY411,IR,FFF)$FGEMAX(IR,FFF)..
    SUM(IAGK_HASORPOT(IY411,IA,IGE)$(IGF(IGE,FFF) AND RRRAAA(IR,IA)),SUM((IS3,T),IHOURSINST(IS3,T)*VGE_T(IY411,IA,IGE,IS3,T)*(1$(NOT GEFFRATE(IA,IGE))+GEFFRATE(IA,IGE))))
      =L= FGEMAX(IR,FFF);

* "Minimum electricity generation by year, area and fuel (MWh)"
QGMINFUELA(IY411,IA,FFF)$FGEMIN(IA,FFF)..
    SUM(IAGK_HASORPOT(IY411,IA,IGE)$IGF(IGE,FFF),SUM((IS3,T),IHOURSINST(IS3,T)*VGE_T(IY411,IA,IGE,IS3,T)*(1$(NOT GEFFRATE(IA,IGE))+GEFFRATE(IA,IGE))))
                =G= FGEMIN(IA,FFF);

* "Maximum electricity generation by year, area and fuel (MWh)"
QGMAXFUELA(IY411,IA,FFF)$FGEMAX(IA,FFF)..
    SUM(IAGK_HASORPOT(IY411,IA,IGE)$IGF(IGE,FFF),SUM((IS3,T),IHOURSINST(IS3,T)*VGE_T(IY411,IA,IGE,IS3,T)*(1$(NOT GEFFRATE(IA,IGE))+GEFFRATE(IA,IGE))))
      =L= FGEMAX(IA,FFF);


*--- Fuel use restrictions by fuel--------------------------------------------

* "Minimum fuel use by year, country and fuel (GJ)"
QGMINCF(IY411,C,FFF)$IGMINF(IY411,C,FFF)..
    SUM(IAGK_HASORPOT(IY411,IA,G)$(IGF(G,FFF) AND ICA(C,IA)), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGF_T(IY411,IA,G,IS3,T)))
    =G= IGMINF(IY411,C,FFF);

* "Maximum fuel use by year, country and fuel (GJ)"
QGMAXCF(IY411,C,FFF)$IGMAXF(IY411,C,FFF)..
    SUM(IAGK_HASORPOT(IY411,IA,G)$(IGF(G,FFF) AND ICA(C,IA)), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGF_T(IY411,IA,G,IS3,T)))
    =L= IGMAXF(IY411,C,FFF);

* "Exact fuel use by year, country and fuel (GJ)"
QGEQCF(IY411,C,FFF)$IGEQF(IY411,C,FFF)..
    SUM(IAGK_HASORPOT(IY411,IA,G)$(IGF(G,FFF) AND ICA(C,IA)), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGF_T(IY411,IA,G,IS3,T)))
    =E= IGEQF(IY411,C,FFF)
$include "../../base/addons/_hooks/qgeqcf.inc"
;

* "Minimum fuel use by year, region and fuel  (GJ)"
QGMINRF(IY411,IR,FFF)$IGMINF(IY411,IR,FFF)..
    SUM(IAGK_HASORPOT(IY411,IA,G)$(IGF(G,FFF) AND RRRAAA(IR,IA)), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGF_T(IY411,IA,G,IS3,T)))
    =G= IGMINF(IY411,IR,FFF);

* "Maximum fuel use by year, region and fuel constraint (GJ)"
QGMAXRF(IY411,IR,FFF)$IGMAXF(IY411,IR,FFF)..
    SUM(IAGK_HASORPOT(IY411,IA,G)$(IGF(G,FFF) AND RRRAAA(IR,IA)), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGF_T(IY411,IA,G,IS3,T)))
    =L= IGMAXF(IY411,IR,FFF);

* "Exact fuel use by year, region and fuel (GJ)"
QGEQRF(IY411,IR,FFF)$IGEQF(IY411,IR,FFF)..
    SUM(IAGK_HASORPOT(IY411,IA,G)$(IGF(G,FFF) AND RRRAAA(IR,IA)), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGF_T(IY411,IA,G,IS3,T)))
    =E= IGEQF(IY411,IR,FFF)
$include "../../base/addons/_hooks/qgeqrf.inc"
;

* "Minimum fuel use by year, area and fuel (GJ)"
QGMINAF(IY411,IA,FFF)$IGMINF(IY411,IA,FFF)..
    SUM(IAGK_HASORPOT(IY411,IA,G)$(IGF(G,FFF)), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGF_T(IY411,IA,G,IS3,T)))
    =G= IGMINF(IY411,IA,FFF);

* "Maximum fuel use by year, area and fuel (GJ)"
QGMAXAF(IY411,IA,FFF)$IGMAXF(IY411,IA,FFF)..
    SUM(IAGK_HASORPOT(IY411,IA,G)$(IGF(G,FFF)), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGF_T(IY411,IA,G,IS3,T)))
    =L= IGMAXF(IY411,IA,FFF);

* "Exact fuel use by year, area and fuel (GJ)"
QGEQAF(IY411,IA,FFF)$IGEQF(IY411,IA,FFF)..
    SUM(IAGK_HASORPOT(IY411,IA,G)$(IGF(G,FFF)), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGF_T(IY411,IA,G,IS3,T)))
    =E= IGEQF(IY411,IA,FFF)
$include "../../base/addons/_hooks/qgeqaf.inc"
;


* "Maximum fuel use by year, season, country and fuel (GJ)"
QGMAXCFS(IY411,C,FFF,IS3)$IGMAXFS(IY411,C,FFF,IS3)..
    SUM(IAGK_HASORPOT(IY411,IA,G)$(IGF(G,FFF) AND ICA(C,IA)), IOF3P6 * SUM(T, WEIGHT_S(IS3)/IWEIGHSUMT * VGF_T(IY411,IA,G,IS3,T)))
    =L= IGMAXFS(IY411,C,FFF,IS3);

* "Maximum fuel use by year, season, region and fuel (GJ)"
QGMAXRFS(IY411,IR,FFF,IS3)$IGMAXFS(IY411,IR,FFF,IS3)..
    SUM(IAGK_HASORPOT(IY411,IA,G)$(IGF(G,FFF) AND RRRAAA(IR,IA)), IOF3P6 * SUM(T, WEIGHT_S(IS3)/IWEIGHSUMT * VGF_T(IY411,IA,G,IS3,T)))
    =L= IGMAXFS(IY411,IR,FFF,IS3);

* "Maximum fuel use by year, season, area and fuel (GJ)"
QGMAXAFS(IY411,IA,FFF,IS3)$IGMAXFS(IY411,IA,FFF,IS3)..
    SUM(IAGK_HASORPOT(IY411,IA,G)$(IGF(G,FFF)), IOF3P6 * SUM(T, WEIGHT_S(IS3)/IWEIGHSUMT * VGF_T(IY411,IA,G,IS3,T)))
    =L= IGMAXFS(IY411,IA,FFF,IS3);



*--- Capacity restrictions by fuel--------------------------------------------

* "Minimum capacity by year, country and fuel (MW)" !! renamed from QKMAXFC(Y,C,FFF), similar with others below  Hans
QKMINFC(IY411,C,FFF)$FKMIN(IY411,C,FFF).. !! EPS convention on FKPOT: 0 implies no restriction, "EPS" implies zero MW.
    SUM((IA,G)$(IAGKFX(IY411,IA,G) AND IGF(G,FFF) AND ICA(C,IA)),
    GKFX(IY411,IA,G)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
    )
      +SUM(IAGK_HASORPOT(IY411,IA,G)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G)) AND IGF(G,FFF) AND ICA(C,IA)), VGKNACCUMNET(IY411,IA,G))
      =G=  FKMIN(IY411,C,FFF);

* "Maximum capacityby year, country and fuel (MW)"
QKMAXFC(IY411,C,FFF)$FKMAX(IY411,C,FFF).. !! EPS convention on FKPOT: 0 implies no restriction, "EPS" implies zero MW.
    SUM((IA,G)$(IAGKFX(IY411,IA,G) AND IGF(G,FFF) AND ICA(C,IA)),
    GKFX(IY411,IA,G)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
    )
      +SUM(IAGK_HASORPOT(IY411,IA,G)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G)) AND IGF(G,FFF) AND ICA(C,IA)), VGKNACCUMNET(IY411,IA,G))
      =L=  FKMAX(IY411,C,FFF);

* "Exact capacity by year, country and fuel (MW)"
QKEQFC(IY411,C,FFF)$FKEQ(IY411,C,FFF).. !! EPS convention on FKPOT: 0 implies no restriction, "EPS" implies zero MW.
    SUM((IA,G)$(IAGKFX(IY411,IA,G) AND IGF(G,FFF) AND ICA(C,IA)),
    GKFX(IY411,IA,G)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
    )
      +SUM(IAGK_HASORPOT(IY411,IA,G)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G)) AND IGF(G,FFF) AND ICA(C,IA)), VGKNACCUMNET(IY411,IA,G))
      =E=  FKEQ(IY411,C,FFF);

* "Minimum capacity by year, region and fuel (MW)"
QKMINFR(IY411,IR,FFF)$FKMIN(IY411,IR,FFF).. !! EPS convention on FKPOT: 0 implies no restriction, "EPS" implies zero MW.
    SUM((IA,G)$(IAGKFX(IY411,IA,G) AND IGF(G,FFF) AND RRRAAA(IR,IA)),
    GKFX(IY411,IA,G)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
)
      +SUM(IAGK_HASORPOT(IY411,IA,G)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G)) AND IGF(G,FFF) AND RRRAAA(IR,IA)), VGKNACCUMNET(IY411,IA,G))
      =G=  FKMIN(IY411,IR,FFF);

* "Maximum capacity by year, region and fuel (MW)"
QKMAXFR(IY411,IR,FFF)$FKMAX(IY411,IR,FFF).. !! EPS convention on FKPOT: 0 implies no restriction, "EPS" implies zero MW.
    SUM((IA,G)$(IAGKFX(IY411,IA,G) AND IGF(G,FFF) AND RRRAAA(IR,IA)),
    GKFX(IY411,IA,G)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
    )
      +SUM(IAGK_HASORPOT(IY411,IA,G)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G)) AND IGF(G,FFF) AND RRRAAA(IR,IA)), VGKNACCUMNET(IY411,IA,G))
      =L=  FKMAX(IY411,IR,FFF);

* "Exact capacity by year, region and fuel (MW)"
QKEQFR(IY411,IR,FFF)$FKEQ(IY411,IR,FFF).. !! EPS convention on FKPOT: 0 implies no restriction, "EPS" implies zero MW.
    SUM((IA,G)$(IAGKFX(IY411,IA,G) AND IGF(G,FFF) AND RRRAAA(IR,IA)),
    GKFX(IY411,IA,G)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
    )
      +SUM(IAGK_HASORPOT(IY411,IA,G)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G)) AND IGF(G,FFF) AND RRRAAA(IR,IA)), VGKNACCUMNET(IY411,IA,G))
      =E=  FKEQ(IY411,IR,FFF);

* "Minimum capacity by year, area and fuel (MW)"  !! renamed from QKMAXFC(Y,C,FFF), similar with others below   Hans
QKMINFNA(IY411,FFF)$FKMINNA(IY411,FFF).. !! 0 implies no restriction, "EPS" implies zero MW.
     SUM(C,
          SUM((IA,G)$(IAGKFX(IY411,IA,G) AND IGF(G,FFF) AND ICA(C,IA)),
          GKFX(IY411,IA,G)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
     )
           +SUM(IAGK_HASORPOT(IY411,IA,G)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G)) AND IGF(G,FFF) AND ICA(C,IA)), VGKNACCUMNET(IY411,IA,G))
         )
      =G=  FKMINNA(IY411,FFF);


* "Maximum capacity by year, area and fuel (MW)"
QKMAXFNA(IY411,FFF)$FKMAXNA(IY411,FFF).. !! 0 implies no restriction, "EPS" implies zero MW.
     SUM(C,
         (  SUM((IA,G)$(IAGKFX(IY411,IA,G) AND IGF(G,FFF) AND ICA(C,IA)),
            GKFX(IY411,IA,G)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
            )
            +SUM(IAGK_HASORPOT(IY411,IA,G)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G)) AND IGF(G,FFF) AND ICA(C,IA)), VGKNACCUMNET(IY411,IA,G))
         ))
      =L=  FKMAXNA(IY411,FFF);

*  "Exact capacity by year, area and fuel (MW)"
QKEQFNA(IY411,FFF)$FKEQNA(IY411,FFF).. !! 0 implies no restriction, "EPS" implies zero MW.
     SUM(C,
         (  SUM((IA,G)$(IAGKFX(IY411,IA,G) AND IGF(G,FFF) AND ICA(C,IA)),
            GKFX(IY411,IA,G)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
            )
            +SUM(IAGK_HASORPOT(IY411,IA,G)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G)) AND IGF(G,FFF) AND ICA(C,IA)), VGKNACCUMNET(IY411,IA,G))
         ))
      =E=  FKEQNA(IY411,FFF);



*--- Capacity restrictions by Technology Group--------------------------------------------

* "Maximum capacity by year, country and technology group (MW)"
QKTECHGROUPC(IY411,C,TECH_GROUP)$TECHGROUPKPOT(C,TECH_GROUP).. !! EPS convention on TECHGROUPKPOT: 0 implies no restriction, "EPS" implies zero MW.
    SUM((IA,G)$(IAGKFX(IY411,IA,G) AND (GDATA(G,'GDTECHGROUP') EQ TECH_GROUP_VALUE(TECH_GROUP)) AND ICA(C,IA)),
    GKFX(IY411,IA,G)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
    )
      +SUM(IAGK_HASORPOT(IY411,IA,G)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G)) AND (GDATA(G,'GDTECHGROUP') EQ TECH_GROUP_VALUE(TECH_GROUP)) AND ICA(C,IA)), VGKNACCUMNET(IY411,IA,G))
      =L=  TECHGROUPKPOT(C,TECH_GROUP)
$include "../../base/addons/_hooks/qktechgroupc.inc"
;

* "Maximum capacity by year, region and technology group (MW)"
QKTECHGROUPR(IY411,IR,TECH_GROUP)$TECHGROUPKPOT(IR,TECH_GROUP).. !! EPS convention on TECHGROUPKPOT: 0 implies no restriction, "EPS" implies zero MW.
    SUM((IA,G)$(IAGKFX(IY411,IA,G) AND (GDATA(G,'GDTECHGROUP') EQ TECH_GROUP_VALUE(TECH_GROUP)) AND RRRAAA(IR,IA)),
    GKFX(IY411,IA,G)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
    )
      +SUM(IAGK_HASORPOT(IY411,IA,G)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G)) AND (GDATA(G,'GDTECHGROUP') EQ TECH_GROUP_VALUE(TECH_GROUP)) AND RRRAAA(IR,IA)), VGKNACCUMNET(IY411,IA,G))
      =L=  TECHGROUPKPOT(IR,TECH_GROUP)
$include "../../base/addons/_hooks/qktechgroupr.inc"
;

* "Maximum capacity by year, area and technology group (MW)"
QKTECHGROUPA(IY411,IA,TECH_GROUP)$TECHGROUPKPOT(IA,TECH_GROUP).. !! EPS convention on TECHGROUPKPOT: 0 implies no restriction, "EPS" implies zero MW.
    SUM(G$(IAGKFX(IY411,IA,G) AND (GDATA(G,'GDTECHGROUP') EQ TECH_GROUP_VALUE(TECH_GROUP))),
    GKFX(IY411,IA,G)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
    )
      +SUM(IAGK_HASORPOT(IY411,IA,G)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G)) AND (GDATA(G,'GDTECHGROUP') EQ TECH_GROUP_VALUE(TECH_GROUP))), VGKNACCUMNET(IY411,IA,G))
      =L=  TECHGROUPKPOT(IA,TECH_GROUP)
$include "../../base/addons/_hooks/qktechgroupa.inc"
;

*--- End of Capacity restrictions by Technology Group--------------------------------------------

*--- Capacity restrictions by Sub Technology Group--------------------------------------------

* "Maximum capacity by year, country and subtechnology group (MW)"
QKSUBTECHGROUPC(IY411,C,TECH_GROUP,SUBTECH_GROUP)$SUBTECHGROUPKPOT(C,TECH_GROUP,SUBTECH_GROUP).. !! EPS convention on SUBTECHGROUPKPOT: 0 implies no restriction, "EPS" implies zero MW.
    SUM((IA,G)$(IAGKFX(IY411,IA,G) AND GDATA(G,'GDTECHGROUP') EQ TECH_GROUP_VALUE(TECH_GROUP) AND GDATA(G,'GDSUBTECHGROUP') EQ SUBTECH_GROUP_VALUE(SUBTECH_GROUP) AND ICA(C,IA)),
    GKFX(IY411,IA,G)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
    )
      +SUM(IAGK_HASORPOT(IY411,IA,G)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G)) AND GDATA(G,'GDTECHGROUP') EQ TECH_GROUP_VALUE(TECH_GROUP) AND GDATA(G,'GDSUBTECHGROUP') EQ SUBTECH_GROUP_VALUE(SUBTECH_GROUP) AND ICA(C,IA)), VGKNACCUMNET(IY411,IA,G))
      =L=  SUBTECHGROUPKPOT(C,TECH_GROUP,SUBTECH_GROUP)
;

* "Maximum capacity by year, region and subtechnology group (MW)"
QKSUBTECHGROUPR(IY411,IR,TECH_GROUP,SUBTECH_GROUP)$SUBTECHGROUPKPOT(IR,TECH_GROUP,SUBTECH_GROUP).. !! EPS convention on SUBTECHGROUPKPOT: 0 implies no restriction, "EPS" implies zero MW.
    SUM((IA,G)$(IAGKFX(IY411,IA,G) AND GDATA(G,'GDTECHGROUP') EQ TECH_GROUP_VALUE(TECH_GROUP) AND GDATA(G,'GDSUBTECHGROUP') EQ SUBTECH_GROUP_VALUE(SUBTECH_GROUP) AND RRRAAA(IR,IA)),
    GKFX(IY411,IA,G)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
    )
      +SUM(IAGK_HASORPOT(IY411,IA,G)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G)) AND GDATA(G,'GDTECHGROUP') EQ TECH_GROUP_VALUE(TECH_GROUP) AND GDATA(G,'GDSUBTECHGROUP') EQ SUBTECH_GROUP_VALUE(SUBTECH_GROUP) AND RRRAAA(IR,IA)), VGKNACCUMNET(IY411,IA,G))
      =L=  SUBTECHGROUPKPOT(IR,TECH_GROUP,SUBTECH_GROUP)
;

* "Maximum capacity by year, area and subtechnology group (MW)"
QKSUBTECHGROUPA(IY411,IA,TECH_GROUP,SUBTECH_GROUP)$SUBTECHGROUPKPOT(IA,TECH_GROUP,SUBTECH_GROUP).. !! EPS convention on SUBTECHGROUPKPOT: 0 implies no restriction, "EPS" implies zero MW.
    SUM(G$(IAGKFX(IY411,IA,G) AND GDATA(G,'GDTECHGROUP') EQ TECH_GROUP_VALUE(TECH_GROUP) AND GDATA(G,'GDSUBTECHGROUP') EQ SUBTECH_GROUP_VALUE(SUBTECH_GROUP)),
    GKFX(IY411,IA,G)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
    )
      +SUM(IAGK_HASORPOT(IY411,IA,G)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G)) AND GDATA(G,'GDTECHGROUP') EQ TECH_GROUP_VALUE(TECH_GROUP) AND GDATA(G,'GDSUBTECHGROUP') EQ SUBTECH_GROUP_VALUE(SUBTECH_GROUP)), VGKNACCUMNET(IY411,IA,G))
      =L=  SUBTECHGROUPKPOT(IA,TECH_GROUP,SUBTECH_GROUP)
;

*--- End of Capacity restrictions by Technology Group--------------------------------------------



*----------- Transmission (MW):------------------------------------------------

* Electricity transmission is limited by transmission capacity:

QXK_UP(IY411,IRE,IRI,IS3,T)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IXKN(Y,IRE,IRI))..
* Complement to assigning VX_T.UP for the case with endogenous transmission investments.

    (1$(NOT IXKRATE(IRE,IRI,IS3,T))+IXKRATE(IRE,IRI,IS3,T))*(
        XKFX(IY411,IRE,IRI)
      + VXKNACCUMNET(IY411,IRE,IRI)
    )
     =G=  VX_T(IY411,IRE,IRI,IS3,T)
$include "../../base/addons/_hooks/qxk_up.inc"
;

* Accumulated endogenous transmission investments during present BB4 model -----
* Note that it is assumed that there are no endogenous decommissioning
* of previous endogenous investment (cf. QGKACCUMNET).

QXKNACCUMNET(IY411,IRE,IRI)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IXKN(Y,IRE,IRI))..
  VXKNACCUMNET(IY411,IRE,IRI)  !! End of this year's VXKNACCUMNET (available at beginning of next year)'
     =E=
  SUM(IY402$IY411PREVY(IY411,IY402), VXKNACCUMNET(IY402,IRE,IRI)$SUM(Y$(YVALUE(Y) LT YVALUE(IY411)),IXKN(Y,IRE,IRI))) + VXKN(IY411,IRE,IRI)$IXKN(IY411,IRE,IRI)  !! VXKNVACCUMNET available at end of previous(i.e., start of this) year PLUS investment during this year
$include "../../base/addons/_hooks/qxknaccumnet.inc"
;

* "Transmission investments are set symetric(MW)"
QXINVSYMMETRY(IY411,IRE,IRI)$IXKN(IY411,IRE,IRI)..
   VXKN(IY411,IRI,IRE)
         =E=
   VXKN(IY411,IRE,IRI)
;



*------------ Emissions: ------------------------------------------------------

* "Limit on annual CO2-emission by year and country (kg/MW)"
QLIMCO2(IY411,C)$(M_POL(IY411,'LIM_CO2',C) AND (M_POL(IY411,'LIM_CO2',C) LT INF))..
      SUM((IA,G)$(IAGK_HASORPOT(IY411,IA,G) AND ICA(C,IA)), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_CO2(G) * IOF0001) * IOF3P6 * VGF_T(IY411,IA,G,IS3,T)))
      =L= M_POL(IY411,'LIM_CO2',C);

* "Limit on annual SO2 emission by year and country (kg/MW)"
QLIMSO2(IY411,C)$(M_POL(IY411,'LIM_SO2',C) AND (M_POL(IY411,'LIM_SO2',C) LT INF))..
      SUM((IA,G)$(IAGK_HASORPOT(IY411,IA,G) AND ICA(C,IA)), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_SO2(G) * IOF0001) * IOF3P6 * VGF_T(IY411,IA,G,IS3,T)))
       =L= M_POL(IY411,'LIM_SO2',C);

* "Limit on annual NOx emission by year and country (kg/MW)"
QLIMNOX(IY411,C)$(M_POL(IY411,'LIM_NOX',C) AND (M_POL(IY411,'LIM_NOX',C) LT INF))..
     SUM((IA,G)$(IAGK_HASORPOT(IY411,IA,G) AND ICA(C,IA)), SUM((IS3,T), IHOURSINST(IS3,T) * (GDATA(G,'GDNOX') * IOF0000001) * IOF3P6 * VGF_T(IY411,IA,G,IS3,T)))
      =L= M_POL(IY411,'LIM_NOX',C);

* "Limit on annual CO2-emission by year (aggregated countries) (kg/MW)"
QLIMCO2NA(IY411)$(M_POLNA(IY411,'LIM_CO2') AND (M_POLNA(IY411,'LIM_CO2') LT INF))..
      SUM(C,
         SUM((IA,G)$(IAGK_HASORPOT(IY411,IA,G) AND ICA(C,IA)), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_CO2(G) * IOF0001) * IOF3P6 * VGF_T(IY411,IA,G,IS3,T)))
         )
      =L= M_POLNA(IY411,'LIM_CO2');

* "Maximal investment by country and fuel during one simulated year (MW)"
QMAXINVESTCF(IY411,C,FFF)$(FMAXINVEST(C,FFF) AND (FMAXINVEST(C,FFF) LT INF)) ..
         FMAXINVEST(C,FFF)
 =G=
         SUM((IAGKNY(IY411,IA,G))$(ICA(C,IA) and IGF(G,FFF)), VGKN(IY411,IA,G))
;

* "Maximal investment by aggerated countries and fuel during one simulated year (MW)"
QMAXINVESTNAF(IY411,FFF)$(FMAXINVESTNA(IY411,FFF) AND (FMAXINVESTNA(IY411,FFF) LT INF)) ..
         FMAXINVESTNA(IY411,FFF)
 =G=
        SUM(C,
         SUM((IAGKNY(IY411,IA,G))$(ICA(C,IA) and IGF(G,FFF)), VGKN(IY411,IA,G))
           )
;


*-------------------------------------------------------------------------------
* Accumulated new endogenous gross generation capacity investments during present BB4 model
*-------------------------------------------------------------------------------

* Accumulated endogenous transmission investments during present BB4 model -----

* "Accumulated new investments available at beginning of next year (MW)"
QGKNACCUMGROSS(IY411,IA,IGKFIND)$IAGKN(IA,IGKFIND)..
* VGKNACCUMGROSS at end of this year (available at beginning of next year):
   VGKNACCUMGROSS(IY411,IA,IGKFIND)
     =E=
* VGKVACCGROSS available at start of this year PLUS investment during this year:
   SUM(IY402$IY411PREVY(IY411,IY402), VGKNACCUMGROSS(IY402,IA,IGKFIND))$(NOT IYFIRST(IY411))
 + VGKN(IY411,IA,IGKFIND)$IAGKNY(IY411,IA,IGKFIND)
$include "../../base/addons/_hooks/qgknaccumgross.inc"
;

*-------------------------------------------------------------------------------
* Accumulated new endogenous net generation capacity investments during present BB4 model
*-------------------------------------------------------------------------------


QGKNACCUMNET(IY411,IA,IGKFIND)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGKFIND))..
* VGKNACCUMNET at end of this year (available at beginning of next year):
   VGKNACCUMNET(IY411,IA,IGKFIND)
     =E=
* VGKVACCUMNET available at end of previous (i.e., start of this) year PLUS investment during this year (missing: MINUS decommissioning due to lifetime expirence):
   SUM(IY402$IY411PREVY(IY411,IY402), VGKNACCUMNET(IY402,IA,IGKFIND)$SUM(Y$(YVALUE(Y) LT YVALUE(IY411)),IAGKNY(Y,IA,IGKFIND)))$(NOT IYFIRST(IY411))
 + VGKN(IY411,IA,IGKFIND)$IAGKNY(IY411,IA,IGKFIND)

$include "../../base/addons/_hooks/qgknaccumnet.inc";

*-------------------------------------------------------------------------------
*---------- Capacity constraint on technologies wiht endogenous investment -----
*-------------------------------------------------------------------------------

* Helpers for development and checking (search also bb4.sim):
Set help_IAGK_HASORPOT_complement(y,aaa,g) "Checking only, cf BB4.sim";
set help_IAGK_HASORPOT_complement_intersection(y,aaa,g) "Checking only, cf BB4.sim";
SET help_QGKE_UP_generated_E(y,aaa,g) "Checking only, cf BB4.sim";
SET help_QGKH_UP_generated_H(y,aaa,g) "Checking only, cf BB4.sim";
SET help_VGE_T_UP_generated_E(y,aaa,g) "Checking only, cf BB4.sim";
SET help_VGH_T_UP_generated_H(y,aaa,g) "Checking only, cf BB4.sim";
SET help_QGKE_UP_VGE_T_UP_intersection_E(y,aaa,g) "Checking only, cf BB4.sim";
SET help_QGKH_UP_VGH_T_UP_intersection_H(y,aaa,g) "Checking only, cf BB4.sim";
SET help_QGKE_UP_VGE_T_UP_sum_E(y,aaa,g) "Checking only, cf BB4.sim";
SET help_QGKH_UP_VGH_T_UP_sum_H(y,aaa,g) "Checking only, cf BB4.sim";

* For (IA,IGKE) with IGKE in IGDISPATCH(IGKE) and not in IAGKN nor IGDECOMEXOPOT assignment of VGE_T.UP is done in BB4.sim.
QGKE_UP(IY411,IA,IGDISPATCH(IGKENOSTO),IS3,T)$(IAGK_HASORPOT(IY411,IA,IGKENOSTO) AND (SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGKENOSTO)) OR IGDECOMEXOPOT(IY411,IA,IGKENOSTO)))..
* Complement to assigning VGE_T.UP for the case with endogenous IGKENOSTO investments.
        VGE_T(IY411,IA,IGKENOSTO,IS3,T) =L=
        (GKFX(IY411,IA,IGKENOSTO)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGKENOSTO)$IGDECOMEXOPOT(IY411,IA,IGKENOSTO)
        +VGKNACCUMNET(IY411,IA,IGKENOSTO)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGKENOSTO)))*(1$(NOT IGKRATE(IA,IGKENOSTO,IS3,T)) + IGKRATE(IA,IGKENOSTO,IS3,T))
$include "../../base/addons/_hooks/qgke_up.inc"
;

* For (IA,IGKH) with IGKH in IGDISPATCH(IGKH) and not in IAGKN nor IGDECOMEXOPOT assignment of VGH_T.UP is done in BB4.sim.
QGKH_UP(IY411,IA,IGDISPATCH(IGKHNOSTO),IS3,T)$(IAGK_HASORPOT(IY411,IA,IGKHNOSTO) AND (SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGKHNOSTO)) OR IGDECOMEXOPOT(IY411,IA,IGKHNOSTO)))..
* Complement to assigning VGH_T.UP for the case with endogenous IGKHNOSTO investments.
        VGH_T(IY411,IA,IGKHNOSTO,IS3,T) =L=
        (GKFX(IY411,IA,IGKHNOSTO)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGKHNOSTO)$IGDECOMEXOPOT(IY411,IA,IGKHNOSTO)
       +VGKNACCUMNET(IY411,IA,IGKHNOSTO)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGKHNOSTO)))*(1$(NOT IGKRATE(IA,IGKHNOSTO,IS3,T)) + IGKRATE(IA,IGKHNOSTO,IS3,T))
$include "../../base/addons/_hooks/qgkh_up.inc"
;


* Minimum capacity usage constraint on electricity generation capacity (MW) (not including exogeneous capacity)
QGKE_LO(IY411,IA,IGDISPATCH(IGKENOSTO),FFF,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGKENOSTO) AND SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGKENOSTO)) and IGF(IGKENOSTO,FFF) and GKF_LO(FFF)>0)..
        VGE_T(IY411,IA,IGKENOSTO,IS3,T) + (VGH_T(IY411,IA,IGKENOSTO,IS3,T) * GDATA(IGKENOSTO,'GDCV'))$(IGEXT(IGKENOSTO))=G=
        GKF_LO(FFF)*(
       +(VGKNACCUMNET(IY411,IA,IGKENOSTO)*(1$(NOT IGKRATE(IA,IGKENOSTO,IS3,T)) + IGKRATE(IA,IGKENOSTO,IS3,T)) )
         )
;

* Minimum capacity usage constraint on heat generation capacity (MW) (not including exogeneous capacity)
QGKH_LO(IY411,IA,IGDISPATCH(IGKHNOSTO),FFF,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGKHNOSTO) AND SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGKHNOSTO)) and IGF(IGKHNOSTO,FFF) and GKF_LO(FFF)>0)..
        VGH_T(IY411,IA,IGKHNOSTO,IS3,T) =G=
        GKF_LO(FFF)*(
       +(VGKNACCUMNET(IY411,IA,IGKHNOSTO)*(1$(NOT IGKRATE(IA,IGKHNOSTO,IS3,T)) + IGKRATE(IA,IGKHNOSTO,IS3,T)))
         )
;


*-------------------------------------------------------------------------------
* Power from hydro-run-of-river, wind, solar, wave can not be dispatched
*-------------------------------------------------------------------------------

*---- Generation existing capacity, hydro-run-of-river technologies ------------

QHYRRDISPATCH(IY411,IA,IGHYRR,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGHYRR) AND (SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHYRR)) OR IGDECOMEXOPOT(IY411,IA,IGHYRR)) AND IWTRRRSUM(IA))..

          VGE_T(IY411,IA,IGHYRR,IS3,T)

$ifi     %VRESHUTDOWN%==yes  =L=
$ifi not %VRESHUTDOWN%==yes  =E=
         (WTRRRFLH(IA) * (
           GKFX(IY411,IA,IGHYRR)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGHYRR)$IGDECOMEXOPOT(IY411,IA,IGHYRR)
        +  VGKNACCUMNET(IY411,IA,IGHYRR)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHYRR))
                          ) * WTRRRVAR_T(IA,IS3,T) * (1$(NOT IGKRATE(IA,IGHYRR,IS3,T)) + IGKRATE(IA,IGHYRR,IS3,T))) / IWTRRRSUM(IA)

;


*---- Generation on windpower technologies -------------------------------------

QWNDDISPATCH(IY411,IA,IGWND,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGWND) AND (SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGWND)) OR IGDECOMEXOPOT(IY411,IA,IGWND)) AND IWND_SUMST(IA))..
         VGE_T(IY411,IA,IGWND,IS3,T)

$ifi     %VRESHUTDOWN%==yes  =L=
$ifi not %VRESHUTDOWN%==yes  =E=

$ifi %WNDFLH_DOL%==AAA         (WNDFLH(IA) * (
$ifi %WNDFLH_DOL%==AAA_GGG     (WNDFLH(IA,IGWND) * (
            GKFX(IY411,IA,IGWND)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGWND)$IGDECOMEXOPOT(IY411,IA,IGWND)
         + VGKNACCUMNET(IY411,IA,IGWND)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGWND))
                 )  * WND_VAR_T(IA,IS3,T) * (1$(NOT IGKRATE(IA,IGWND,IS3,T)) + IGKRATE(IA,IGWND,IS3,T))) / IWND_SUMST(IA)
;


*---- Generation on solar electricity and heat technologies --------------------

QSOLEDISPATCH(IY411,IA,IGSOLE,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGSOLE) AND (SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGSOLE)) OR IGDECOMEXOPOT(IY411,IA,IGSOLE)) AND ISOLESUMST(IA))..

       VGE_T(IY411,IA,IGSOLE,IS3,T)

$ifi     %VRESHUTDOWN%==yes  =L=
$ifi not %VRESHUTDOWN%==yes  =E=

$ifi %SOLEFLH_DOL%==AAA       (SOLEFLH(IA) * (
$ifi %SOLEFLH_DOL%==AAA_GGG   (SOLEFLH(IA,IGSOLE) * (
            GKFX(IY411,IA,IGSOLE)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGSOLE)$IGDECOMEXOPOT(IY411,IA,IGSOLE)
         + VGKNACCUMNET(IY411,IA,IGSOLE)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGSOLE))
                 )  * SOLE_VAR_T(IA,IS3,T) * (1$(NOT IGKRATE(IA,IGSOLE,IS3,T)) + IGKRATE(IA,IGSOLE,IS3,T))) / ISOLESUMST(IA)
;

QSOLHDISPATCH(IY411,IA,IGSOLH,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGSOLH) AND (SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGSOLH)) OR IGDECOMEXOPOT(IY411,IA,IGSOLH)) AND ISOLHSUMST(IA))..
         VGH_T(IY411,IA,IGSOLH,IS3,T)

$ifi     %VRESHUTDOWN%==yes  =L=
$ifi not %VRESHUTDOWN%==yes  =E=

$ifi %SOLHFLH_DOL%==AAA       (SOLHFLH(IA) * (
$ifi %SOLHFLH_DOL%==AAA_GGG   (SOLHFLH(IA,IGSOLH) * (

          GKFX(IY411,IA,IGSOLH)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGSOLH)$IGDECOMEXOPOT(IY411,IA,IGSOLH)
     + VGKNACCUMNET(IY411,IA,IGSOLH)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGSOLH))
                            ) * SOLH_VAR_T(IA,IS3,T) * (1$(NOT IGKRATE(IA,IGSOLH,IS3,T)) + IGKRATE(IA,IGSOLH,IS3,T)))/ ISOLHSUMST(IA)
;

* Wave technology
QWAVEDISPATCH(IY411,IA,IGWAVE,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGWAVE) AND (SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGWAVE)) OR IGDECOMEXOPOT(IY411,IA,IGWAVE)) AND IWAVESUMST(IA))..
         VGE_T(IY411,IA,IGWAVE,IS3,T)

$ifi     %VRESHUTDOWN%==yes  =L=
$ifi not %VRESHUTDOWN%==yes  =E=

$ifi %GWAVE_DOL%==AAA       (WAVEFLH(IA) * (
$ifi %GWAVE_DOL%==AAA_GGG   (WAVEFLH(IA,IGWAVE) * (

         GKFX(IY411,IA,IGWAVE)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGWAVE)$IGDECOMEXOPOT(IY411,IA,IGWAVE)
     + VGKNACCUMNET(IY411,IA,IGWAVE)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGWAVE))
                          )* WAVE_VAR_T(IA,IS3,T) * (1$(NOT IGKRATE(IA,IGWAVE,IS3,T)) + IGKRATE(IA,IGWAVE,IS3,T))) / IWAVESUMST(IA)
;

*-------------------------------------------------------------------------------
*----- Any equations for addon to be placed here: ------------------------------
*-------------------------------------------------------------------------------

$include "../../base/addons/_hooks/eqndecdef.inc"

* These add-on equations pertain to targets for wind power.
$ifi not %WINDTARGET%==yes $goto end_windtarget_eq
$ifi EXIST "wndtargetdata.inc" $include "wndtargetdata.inc";
$label end_windtarget_eq

* These add-on equations pertain to heat transmission.
$ifi %HEATTRANS%==yes $include "../../base/addons/heattrans/model/htequations.inc";

*-------------------------------------------------------------------------------
*----- End: Any equations for addon to be placed here. -------------------------
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
*  End: Declaration and definition of EQUATIONS
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
* Definition of the models:
*-------------------------------------------------------------------------------

MODEL BALBASE4  "Balmorel model with endogeneous investments"
/
*--- Objective function --------------------------------------------------------
                                QOBJ
*--- Balance equations ---------------------------------------------------------
                                QEEQ
                                QHEQ
                                QGFEQ
*--- Feasible generation region ------------------------------------------------
                                QGCBGBPR
$ifi %bypass%==yes              QGCBGBPRBYPASS1
$ifi %bypass%==yes              QGCBGBPRBYPASS2
                                QGCBGEXT
                                QGCVGEXT
                                QGGETOH

*--- Hydro reservior restrictions ----------------------------------------------

                                QHYRSSEQ
                                QHYRSMINVOL
                                QHYRSMAXVOL
                                QHYMAXG

*--- Storage restrictions ------------------------------------------------------
                                QESTOVOLT
                                QESTOVOLTS
*                                QESTOVOLTSINIT
                                QHSTOVOLT
                                QHSTOVOLTS

$ifi %heatsto_loading_rest%==yes QHSTOLOADT
$ifi %heatsto_loading_rest%==yes QHSTOLOADTS

*--- Transmission capacity (listed in QXKE_UP) -----------------------------------------------------

$ifi %TransInvest%==yes         QXKNACCUMNET
$ifi %TransInvest%==yes         QXINVSYMMETRY
$ifi %TransInvest%==yes         QXK_UP

*--- Electricity generation restrictions by fuel -------------------------------
                                QGMINFUELC
                                QGMAXFUELC
                                QGMINFUELR
                                QGMAXFUELR
*                                QGMINFUELA TODO
*                                QGMAXFUELA TODO
*--- Fuel consumption restrictions ---------------------------------------------
                                QGMINCF
                                QGMAXCF
                                QGEQCF
                                QGMINRF
                                QGMAXRF
                                QGEQRF

                                QGMAXCFS
                                QGMAXRFS
                                QGMAXAFS

*                                QGMINAF TODO
*                                QGMAXAF TODO
*                                QGEQAF  TODO

*--- Emissions restrictions ----------------------------------------------------
                                QLIMCO2
                                QLIMSO2
                                QLIMNOX
                                QLIMCO2NA


*---------------------------------------------------------------
$ifi not %TechInvest%==yes $ifi not %DECOM%==yes  $goto NO_TECH_INVESTMENTS_NO_DECOMMISSIONING
*--- Investment and decommissioning related equations ----------

*--- Storage restrictions ------------------------------------------------------
                                 QESTOLOADTLIM
                                 QESTOLOADTLIMS
                                 QHSTOLOADTLIM
                                 QHSTOLOADTLIMS

                                 QESTOVOLTLIM
                                 QESTOVOLTLIMS
                                 QHSTOVOLTLIM
                                 QHSTOVOLTLIMS

                                 QESTOVGETLIM
                                 QESTOVGETLIMS
                                 QHSTOVGHTLIM
                                 QHSTOVGHTLIMS
*--- Capacity constraints on generation (MW) -----------------------------------
*                                QGKNACCUMGROSS   NOT RELEVANT
                                 QGKNACCUMNET

                                 QGKE_UP
                                 QGKH_UP
                                 QGKE_LO
                                 QGKH_LO

                                 QHYRRDISPATCH
                                 QWNDDISPATCH
                                 QSOLEDISPATCH
                                 QSOLHDISPATCH
                                 QWAVEDISPATCH
*--- Potential capacity restrictions per technology group ------------------------------------------------
                                 QKTECHGROUPC
                                 QKTECHGROUPR
                                 QKTECHGROUPA
*--- Potential capacity restrictions per subtechnology group ------------------------------------------------
                                 QKSUBTECHGROUPC
                                 QKSUBTECHGROUPR
                                 QKSUBTECHGROUPA
*--- Fuel potential restrictions ------------------------------------------------
                                 QKEFUELC
                                 QKEFUELR
                                 QKEFUELA
*--- Fuel capacity restrictions per year ------------------------------------------------
                                 QKMINFC
                                 QKMAXFC
                                 QKEQFC
                                 QKMINFR
                                 QKMAXFR
                                 QKEQFR
                                 QKMINFNA
                                 QKMAXFNA
                                 QKEQFNA
*                                QKMINFA  TODO
*                                QKMAXFA  TODO
*                                QKEQFA   TODO
*--- Investment restrictions----------------------------------------------------
                                 QMAXINVESTNAF

$label  NO_TECH_INVESTMENTS_NO_DECOMMISSIONING
*---------------------------------------------------------------
*--- End: Investment and decommissioning related equations ----------



*----- Any equations for addon to be placed here: ------------------------------

$include "../../base/addons/_hooks/balbase4.inc"


$ontext
*TODO
*--- Operational restrictions --------------------------------------------------
*                               QGE2LEVEL

*--- Investment restricitions --------------------------------------------------
                                QMAXINVESTCF
*                               QMAXINVESTGROWTHCG

$ifi %FOSSILTARGET%==yes QFOSSILTARGET
$ifi %RENEWTARGET%==yes QRENEW
$ifi %HEATTRANS%==yes $include "../../base/addons/heattrans/model/htbb1.inc";

$offtext

/;

* Scale the model: only equation QOBJ is really badly scaled:
BALBASE4.SCALEOPT=1;
QOBJ.SCALE=IOF1000000;

*-------------------------------------------------------------------------------
*----- Any further models to be defined here:
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
*----- End: Any further models to be defined here
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
*----- End of definition of models ---------------------------------------------
*-------------------------------------------------------------------------------

$include "../../base/addons/_hooks/error2.inc"
$INCLUDE  "../../base/addons/BB4/errorBB4.inc";

* The following file contains definitions of a number of temporary parameters
* and sets that may be used for printout of simulation results.
$ifi %PRINTFILES%==yes $INCLUDE "../../base/output/printout/printinc/print2.inc";

* The following file contains file and parameter definitions for the economic
* output module.
$ifi %ECONOMIC%==yes $INCLUDE "../../base/processing/economic/eco_def.inc";


*-------------------------------------------------------------------------------
* Control of formats for variable and equation listing:   VIRKER IKKE , \D8V!
$ifi not %displaylistformat% == yes $goto label_Notdisplaylistformat
OPTION QOBJ:8:0:1;
OPTION QEEQ:8:0:1;
OPTION QHEQ:8:0:1;
OPTION  vgen_t
:3:0:1 ; !! ,   VGKVACCGROSS:3:0:1 ;
$label label_Notdisplaylistformat
*-------------------------------------------------------------------------------
*-------------------------------------------------------------------------------
$ifi %CREATETIME%==yes $INCLUDE "../../base/model/createtime.inc";
$ifi %CREATETIME%==yes $goto ENDOFMODEL
* Here the model to be solved/simulated is included:


$INCLUDE "../../base/addons/BB4/BB4overview.inc";

*-------------------------------------------------------------------------------

$ifi     exist 'Balmorelbb4.sim'  $include                  'Balmorelbb4.sim';
$ifi not exist 'Balmorelbb4.sim'  $include '../../base/model/Balmorelbb4.sim';


*-------------------------------------------------------------------------------

$ifi not %export_results%==yes $goto result_export
*------------------------------------------------------------------------------
*                GENERATE INPUT FILES FOR FUTURE RUNS FROM RESULTS OF THIS RUN
*------------------------------------------------------------------------------

* For hydro with reservoir save the following, to be used in future runs by addon "import_results":

HYRSG(Y,IA,S)$SUM(IGHYRS,IAGK_HASORPOT(Y,IA,IGHYRS)) = SUM(IGHYRS$IAGK_HASORPOT(Y,IA,IGHYRS),SUM(T, IHOURSINST(S,T)*VGE_T.L(Y,IA,IGHYRS,S,T)));
VHYRS_SL(Y,IA,S)  = VHYRS_S.L(Y,IA,S);
WATERVAL(Y,IA,S)  = QHYRSSEQ.M(Y,IA,S);

execute_unload  "../../simex/HYRSG.gdx", HYRSG;
execute_unload  "../../simex/VHYRS_SL.gdx", VHYRS_SL;
execute_unload  "../../simex/WATERVAL.gdx", WATERVAL;

* For runs with investments and/or decommissionning save the following, to be used in future runs by addon "import_results":
XKACCUMNET(Y,IRE,IRI)=XKFX(Y,IRE,IRI)
$ifi %TransInvest%==yes +VXKNACCUMNET.L(Y,IRE,IRI)
;
GKACCUMNET(Y,IA,G)= GKFX(Y,IA,G)
$ifi %DECOM%==yes       -VDECOM_EXO_ACCUM.L(Y,IA,G)
$ifi %TechInvest%==yes  +VGKNACCUMNET.L(Y,IA,G)
;
*Modification of GKFX values in case they are negative or extremely small (sometimes there can be issues with the decimals)
GKACCUMNET(Y,IA,G)$(GKACCUMNET(Y,IA,G) LT 0)= 0;

execute_unload  "../../simex/XKACCUMNET.gdx", XKACCUMNET;
execute_unload  "../../simex/GKACCUMNET.gdx", GKACCUMNET;

* For runs with interseasonal storages save the following, to be used in future runs by addon "import_results":
*Initial energy storage volumen at the beginning of each week

GVESTOVOLTS(Y,IA,IGESTOS,S,T)$(ORD(T) EQ 1)=VESTOVOLTS.L(Y,IA,IGESTOS,S,T);
GVHSTOVOLTS(Y,IA,IGHSTOS,S,T)$(ORD(T) EQ 1)=VHSTOVOLTS.L(Y,IA,IGHSTOS,S,T);

*Correction of seasonal values to avoid infeasibilities due to decimal errors by substracting a very small number to the storage levels

GVESTOVOLTS(Y,IA,IGESTOS,S,T)$((ORD(T) EQ 1) AND GVESTOVOLTS(Y,IA,IGESTOS,S,T) AND (GKACCUMNET(Y,IA,IGESTOS) LE VESTOVOLTS.L(Y,IA,IGESTOS,S,T)))=GVESTOVOLTS(Y,IA,IGESTOS,S,T)-0.000000001;
GVHSTOVOLTS(Y,IA,IGHSTOS,S,T)$((ORD(T) EQ 1) AND GVHSTOVOLTS(Y,IA,IGHSTOS,S,T) AND (GKACCUMNET(Y,IA,IGHSTOS) LE VESTOVOLTS.L(Y,IA,IGHSTOS,S,T)))=GVHSTOVOLTS(Y,IA,IGHSTOS,S,T)-0.000000001;

execute_unload  "../../simex/GVESTOVOLTS.gdx", GVESTOVOLTS;
execute_unload  "../../simex/GVHSTOVOLTS.gdx", GVHSTOVOLTS;

*------------------------------------------------------------------------------
*                END: GENERATE INPUT FILES FOR FUTURE RUNS FROM RESULTS OF THIS RUN
*------------------------------------------------------------------------------
$label  result_export



*$ifi %MAKEINVEST%==yes execute_unload "../../base/data/GKVACCDECOM.gdx", GKVACCDECOM;

*$ifi %X3V%==yes $INCLUDE "../../base/addons/x3v/bb4/x3vgdx.inc";
*--- End: Results which can be transfered between simulations are placed here --

DISPLAY INFODISPLAY , "For BB4: see at the end of the logfile: <case>/logerror/logfile.out." ;
*----- End of file:------------------------------------------------------------
$label endoffile


