* File print1.inc.

* File last time modified 27-09-2002 (rus) , 05-08-2003 (sns), hr 20110920, hr 20121001, 20141121(hr), 20160203(hr), 20161208(hr).

* This file is part of the Balmorel model, version 3.03 ()

* -----------------------------------------------------------------------------
* Contents:

* This file contains definitions of logical file names
* and the associated names of files
* that may be used for printout of simulation results.
* It also contains definitions of various sets etc. that is useful for the
* production and alyout of the output.

* The individual output file is used by the print code that is contained in
* the $included files in the print2.inc file, which is called in the end of
* the Balmorel.gms file.

* -----------------------------------------------------------------------------

* SETS, PARAMETERS, ect.  useful for the production of the output.


* The following is used for identification of your case if OCASEID was not previously declared:
SCALAR OCASEID "Balmorel Demo-example - default CASE identification";

* Enter here the currency used in data input:
SCALAR OIMONEY "EUR90" /1/;                     !! Input currency name in the text field. The numerical value is not used.
* Leave this default information:
$if not declared OIMONEY SCALAR OIMONEY "Unknown" /1/;  !! Input currency name in the text field in case of no information. The numerical value is not used.

PARAMETER OCARDSETA;  /* To hold the number of areas in the simulation */
OCARDSETA=0;
LOOP(IA, OCARDSETA=OCARDSETA+1);

PARAMETER OCARDSETR;  /* To hold the number of regions in the simulation */
OCARDSETR=0;
LOOP(IR, OCARDSETR=OCARDSETR+1);

PARAMETER OSCALAR1, OSCALAR2, OSCALAR3; /* Various general counters */

* For printing: OTLW, OTLG, OTL1, OTLCRA for specifying more general field widths in printing.
* (O=Output, TLW=TextLabelWidth)
* Note that the text strings (OTLW.ts) must contain the same number of blanks as the value indicates,
* if you want to use this text string to privide empty space of same width as a ".TL:OTLW" provides.
* Present choice: 32, consistent with the maximal length of identifiers and labels in GAMS before version 22.7.
* From GAMS version 22.7 this was increased to 64.
* The advantage, depending on circumstances, of using the same values for all SETS
* is homegenity (nice columns) in the output, the disadvantage is the potential superfluous space.

* More set individual values are held in the following scalars.
*
SCALAR OTLW     "                                " /32/; !! Default.
SCALAR OTLWCRA  "                                " /32/; !! Specific for SET CCCRRRAAA. The value is checked below.
SCALAR OTLWY    "    " /4/;                              !! Specific for SET YYY and Y. It is assumed that any element in YYY is represented by four characters (e.g. 2050).
SCALAR OTLWS    "    " /3/;                              !! Specific for SET SSS and S. It is assumed that any element in SSS is represented by four characters (e.g. S52).
SCALAR OTLWT    "    " /4/;                              !! Specific for SET TTT and T. It is assumed that any element in TTT is represented by four characters (e.g. T168).
SCALAR OTLWG    "                                                                " /64/; !! Specific for SET GGG and G. The value is checked below.
* Check consistency between the required width and the length of the (all ' ') text string:
ISCALAR1 = SMAX(GGG, CARD(GGG.TL));                      !! Find the required width.
IF((ISCALAR1 GT OTLWG),   DISPLAY INFODISPLAY, "The length of an element in GGG is larger than assumed by OTLWG, this will prevent nice printfile output. Please ensure consistency in file base\printout\printinc\print1.inc"; );
ISCALAR2 = SMAX(CCCRRRAAA, CARD(CCCRRRAAA.TL));          !! Assign precisely the required width.
IF((ISCALAR2 GT OTLWCRA), DISPLAY INFODISPLAY, "The length of an element in CCCRRRAAA is larger than assumed by OTLWCRA, this will prevent nice printfile output. Please ensure consistency in file base\printout\printinc\print1.inc"; );

ALIAS(S,OALIASS);
ALIAS(T,OALIAST);

* -----------------------------------------------------------------------
* The following three blocks of code, (A), (B) and (C) must be consistent
* with respect to files (folder, number, names, descriptions).
* -----------------------------------------------------------------------
* Block (A):
* Declare files for printing to:

* Key figures
FILE bal_1      /"../output/printout/%CASEID%-bal_1.out"/;

* Electricity generation
FILE eg_cy      /"../output/printout/eg_cy.out"/;
FILE eg_gfcy    /"../output/printout/eg_gfcy.out"/;
FILE eg_gat     /"../output/printout/eg_gat.out"/;
FILE ego_cy     /"../output/printout/ego_cy.out"/;
FILE egn_cy     /"../output/printout/egn_cy.out"/;
FILE ezgo_cy    /"../output/printout/ezgo_cy.out"/;
FILE ezgn_cy    /"../output/printout/ezgn_cy.out"/;

* Electricity storage:
FILE esto_at    /"../output/printout/esto_at.out"/;
FILE esto2_at   /"../output/printout/esto2_at.out"/;
FILE hyrs_as    /"../output/printout/hyrs_as.out"/;
* Heat generation
FILE hg_cy      /"../output/printout/hg_cy.out"/;
FILE hgo_cy     /"../output/printout/hgo_cy.out"/;
FILE hgn_cy     /"../output/printout/hgn_cy.out"/;

* Heat storage:
FILE hsto_at    /"../output/printout/hsto_at.out"/;
FILE hsto2_at   /"../output/printout/hsto2_at.out"/;

* Import - Export
FILE ex_ry      /"../output/printout/ex_ry.out"/;
FILE exk_ry     /"../output/printout/exk_ry.out"/;
FILE xbottle    /"../output/printout/xbottle.out"/;

* Fuel consumption
FILE ehf_gcy    /"../output/printout/ehf_gcy.out"/;
FILE ehf_gry    /"../output/printout/ehf_gry.out"/;
FILE ehf_gay    /"../output/printout/ehf_gay.out"/;
FILE ehf_fcy    /"../output/printout/ehf_fcy.out"/;
FILE f_fcy      /"../output/printout/f_fcy.out"/;

* Prices
FILE ep_ry      /"../output/printout/ep_ry.out"/;
FILE ep_rt      /"../output/printout/ep_rt.out"/;
FILE EPNXT_RY   /"../output/printout/epnxt_ry.out"/;
FILE epnxt_rt   /"../output/printout/epnxt_rt.out"/;

FILE hp_ay      /"../output/printout/hp_ay.out"/;
FILE hp_at      /"../output/printout/hp_at.out"/;

* Emissions
FILE mco2_cy    /"../output/printout/mco2_cy.out"/;
FILE mso2_cy    /"../output/printout/mso2_cy.out"/;
FILE mnox_cy    /"../output/printout/mnox_cy.out"/;
FILE ehmco2qrt  /"../output/printout/ehmco2qrt.out"/;

*Weiming
* Electricity generation
FILE eg_yat      /"../output/printout/eg_yat.out"/;
PARAMETER OEG_YAT(Y,Y,AAA,G,S,T) "Electricicy generations by Areas and (S,T) (GWh)";
FILE eg_yr      /"../output/printout/eg_yr.out"/;
PARAMETER OEG_YR(Y,Y,RRR,G) "Electricicy generations by Regions(GWh)";
FILE eg_yc     /"../output/printout/eg_yc.out"/;
PARAMETER OEG_YC(Y,Y,CCC,G) "Electricicy generations by Countries(GWh)";
FILE eg_yna     /"../output/printout/eg_yna.out"/;
PARAMETER OEG_YNA(Y,Y,G) "Electricicy generations by all countries(GWh)";
FILE eg_ynaf     /"../output/printout/eg_ynaf.out"/;
PARAMETER OEG_YNAF(Y,Y,G) "Electricicy generations by all countries by fuel(GWh)";

* Prices
FILE ep_yrt      /"../output/printout/ep_yrt.out"/;
PARAMETER OEP_YRT(Y,Y,RRR,S,T) "Electricicy prices by Regions and (S,T) (Money/Mwh)";
FILE ep_yr      /"../output/printout/ep_yr.out"/;
PARAMETER OEP_YR(Y,Y,RRR) "Electricicy prices by Regions and year (Money/Mwh)";
FILE ep_yc      /"../output/printout/ep_yc.out"/;
PARAMETER OEP_YC(Y,Y,C) "Electricicy prices by Countries and year (Money/Mwh)";
FILE ep_yna      /"../output/printout/ep_yna.out"/;
PARAMETER OEP_YNA(Y,Y) "Electricicy prices by all the countries and year (Money/Mwh)";
FILE hp_yat     /"../output/printout/hp_yat.out"/;
PARAMETER OHP_YAT(Y,Y,AAA,S,T) "Heat prices by Regions and (S,T) (Money/Mwh)";
FILE hp_ya     /"../output/printout/hp_ya.out"/;
PARAMETER OHP_YA(Y,Y,AAA) "Heat prices by Regions and year(Money/Mwh)";
FILE hp_yc     /"../output/printout/hp_yc.out"/;
PARAMETER OHP_YC(Y,Y,CCC) "Heat prices by Countries and year(Money/Mwh)";
FILE hp_yna     /"../output/printout/hp_yna.out"/;
PARAMETER OHP_YNA(Y,Y) "Heat prices by aggregated countries and year(Money/Mwh)";

*Weiming: averaged electricity price
FILE aep_yna     /"../output/printout/aep_yna.out"/;
PARAMETER OAEP_YNA(Y,Y) "Averaged electricity prices by aggregated countries and year(Money/Mwh)";

*FILE egwater_rs /"../output/printout/egwater_rs.out"/; TODO (hr)

* Investments in technology:
FILE gkn_yag     /"../output/printout/gkn_yag.out"/;
* No need for parameter, using VGKNACCUMNET directly.
* PARAMETER OGKN_YYAG(Y,Y,AAA,GGG)       "New endogenous generation capacity each BB4 (debugging only) (MW)";             !! Mainly for debugging.
* PARAMETER OGKNACCUMNET_YYAG(Y,Y,AAA,G) "New endogenous accumulated generation capacity each BB4 (debugging only) (MW)"; !! Mainly for debugging.

FILE gkn_ynaf     /"../output/printout/gkn_ynaf.out"/;
PARAMETER OGKN_YNAF(Y,Y,FFF) "New endogenous accumulated capacity by aggregated Countries by fuel(MW)";

* Total capacity in technology
FILE gk_yag     /"../output/printout/gk_yag.out"/;
PARAMETER OGK_YAG(Y,Y,AAA,G) "Electricity capacity by Area(MW)";
FILE gk_ycg     /"../output/printout/gk_ycg.out"/;
PARAMETER OGK_YCG(Y,Y,CCC,G) "Electricity capacity by Countries(MW)";
FILE gk_ynag     /"../output/printout/gk_ynag.out"/;
PARAMETER OGK_YNAG(Y,Y,G) "Electricity capacity by aggregated Countries(MW)";
FILE gk_ynaf     /"../output/printout/gk_ynaf.out"/;
PARAMETER OGK_YNAF(Y,Y,FFF) "Electricity capacity by aggregated Countries by fuel(MW)";

* Emissions
FILE mco2_yc    /"../output/printout/mco2_yc.out"/;
FILE mco2_yna    /"../output/printout/mco2_yna.out"/;
FILE mpco2_yc    /"../output/printout/mpco2_yc.out"/;
FILE mpco2_yna    /"../output/printout/mpco2_yna.out"/;

*Demand
FILe de_yc     /"../output/printout/de_yc.out"/;
FILe de_yna     /"../output/printout/de_yna.out"/;


* Calibration
$ifi %DEFPCALIB%==yes FILE dfp_calib  /"../output/printout/dfp_calib.out"/;


* -----------------------------------------------------------------------
* Block (B):
* Delete all existing printout files before printing any new ones:
execute "rm  ../output/printout/*.*";

* -----------------------------------------------------------------------
* Block (C):
* Make overview file of all potential printout files
* (not neccessarily all or any will be made on present run,
* this will depend on option PRINTFILES) :

FILE printoutoverview /"../output/printout/printoutoverview.out"/;
printoutoverview.pw = 32000;
PUT printoutoverview;
PUT "Version:              " SYSTEM.TITLE /;
PUT "File name:            printoutoverview.out" /;
PUT "Time-stamp:          '" SYSTEM.DATE " " SYSTEM.TIME "'" /;
PUT "Case-identification: '" OCASEID.TS "'" //;


$ifi %PRINTFILES%==yes PUT "Option PRINTFILES was set at yes, therefore some files will be printed."/;
$ifi %PRINTFILES%==yes PUT "Which files that are printed will depend on additional options' settings."/;
$ifi not %PRINTFILES%==yes PUT "Option PRINTFILES was not set at yes, therefore no further files will be printed."/;


PUT /"Overview of potential printout files with indication of content:"//;

* The following list of files must be consitent with the file declarations above,
* and the descriptions must be consistent with the contents of the corresponding files.
$if %BB4%==yes $goto doBB4

PUT "bal_1.out       "'"Energy balance by year and country"'/;                                    !!  TODO: incomplete list (?)
PUT "eg_cy.out       "'"Annual net electricity generation, old and new technologies"'/;
PUT "eg_gfcy.out     "'"Annual net electricity generation"'/;
PUT "eg_gat.out      "'"Electricity production on units during each time segment"'/;
PUT "ego_cy.out      "'"Annual net electricity generation from old technologies"'/;
PUT "egn_cy.out      "'"Annual net electricity generation at new technologies"'/;
PUT "ezgo_cy.out     "'"Total annual electricity generation from old technologies"'/;
PUT "ezgn_cy.out     "'"Total annual electricity generation from new technologies"'/;
PUT "esto_at.out     "'"Short term electricity storage contents, loading and unloading"'/;
PUT "esto2_at.out    "'"Short term electricity storage contents at the beginning of each time segment"'/;
PUT "hyrs_as.out     "'"Hydro power with storage: Inflow, generation, storage level, water values"'/;
PUT "hg_cy.out       "'"Annual heat generation and heat taken from heat storage"'/;
PUT "hgo_cy.out      "'"Annual heat generation from existing technologies"'/;
PUT "hgn_cy.out      "'"Annual heat generation from new technologies"'/;
PUT "hsto_at.out     "'"Short term heat storage contents, loading and unloading"'/;
PUT "hsto2_at.out    "'"Short term heat storage contents at the beginning of each time segment"'/;
PUT "ex_ry.out       "'"Annual electricity export and import by region"'/;
PUT "exk_ry.out      "'"Transmission capacities (old plus new) by the end of the year"'/;
PUT "xbottle.out     "'"Bottle neck information for electricity transmission"'/;
PUT "ehf_gcy.out     "'"Annual fuel consumption by technologies and countries"'/;
PUT "ehf_gry.out     "'"Annual fuel consumption by technologies and regions"'/;
PUT "ehf_gay.out     "'"Annual fuel consumption by technologies and areas"'/;
PUT "ehf_fcy.out     "'"Annual fuel consumption by fuels and countries"'/;
PUT "f_fcy.out       "'"Annual fuel use by fuel type and country. Annual electricity and heat output by fuel type and country. Output/input relation."'/;
PUT "ep_ry.out       "'"Annual weighted average electricity price"'/;
PUT "ep_rt.out       "'"Electricity generation price by teme segment"'/;
PUT "epnxt_ry.out    "'"Marginal electricity generation cost of the next unit"'/;
PUT "epnxt_rt.out    "'"Marginal electricity generation cost of the next unit"'/;
PUT "hp_ay.out       "'"Annual average heat prices"'/;
PUT "hp_at.out       "'"Heat generation price by time segment"'/;
PUT "mco2_cy.out     "'"Annual CO2 emissions"'/;
PUT "mso2_cy.out     "'"Annual SO2 emissions"'/;
PUT "mnox_cy.out     "'"Annual NOx emissions"'/;
*PUT "egwater_rs.out  "'""'/;   TODO (hr)
*PUT "gkn_ag.out      "'""'/;   TODO (hr)
PUT "dfp_calib.out   "'"Used for calibration of demand functions for electricty and heat"'/;

$label doBB4
$if not %BB4%==yes $goto doneBB4


* This is a bad place, but ...
PARAMETER IDE_T(Y,RRR,DEUSER,S,T) "Nominal hourly electricity demand (MW)";
PARAMETER IDH_T(Y,AAA,DHUSER,S,T) "Nominal hourly heat demand (MW)";
IDE_T(Y,IR,DEUSER,S,T) = ((DE(Y,IR,DEUSER) * DE_VAR_T(IR,DEUSER,S,T)) / IDE_SUMST(IR,DEUSER))$(IDE_SUMST(IR,DEUSER) GT 0);
IDH_T(Y,IA,DHUSER,S,T) = ((DH(Y,IA,DHUSER) * DH_VAR_T(IA,DHUSER,S,T)) / IDH_SUMST(IA,DHUSER))$(IDH_SUMST(IA,DHUSER) GT 0);
* Testing an idea:
PARAMETER DE__YCU(Y,C,DEUSER) "Electricicy consumption by Year, Country and user group (Mwh)";
PARAMETER EP__YRT(Y,RRR,S,T)  "Electricicy prices by Year, Region and (S,T) (Money/Mwh)";


PUT  "Doing BB4, printing for this model is not properly developed yet, the following will be unconditionally printed": /;
PUT  "ep_yrt.out     "'"Electricicy prices by Year, Regions and (S,T) (Money/Mwh)"' /;
PUT  "ep_yr.out      "'"Electricicy prices by Year, Regions and year (Money/Mwh)"'  /;
PUT  "ep_yc.out      "'"Electricicy prices by Year, Countries and year (Money/Mwh)"'  /;
PUT  "ep_yna.out     "'"Electricicy prices by Year, aggregated countries and year (Money/Mwh)"'  /;

PUT  "aep_yna.out      "'"Averaged electricicy prices by aggregated countries and year (Money/Mwh)"'  /;


PUT  "hp_yat.out     "'"Heat prices by Year, Region and (S,T) (Money/Mwh)"' /;
PUT  "hp_ya.out      "'"Heat prices by Year and Region (Money/Mwh)"'  /;
PUT  "hp_yc.out      "'"Heat prices by Year and Country (Money/Mwh)"'  /;
PUT  "hp_yna.out     "'"Heat prices by Year, aggregated countries (Money/Mwh)"'  /;  !! TODO check text

PUT  "gkn_yag.out    "'"Endogenous investments for each Area and technology, all years in all BB4 models"' /;
PUT  "gkn_ynaf.out   "'"Endogenous investments for aggregated countries and fuel type, all years in all BB4 models"' /;
PUT  "gk_yag.out     "'"Capacity for each Area and technology, all years in all BB4 models"' /;
PUT  "gk_ycg.out     "'"Capacity for each Country and technology, all years in all BB4 models"' /;
PUT  "gk_ynag.out    "'"Capacity for aggregated countries and technology, all years in all BB4 models"' /;
PUT  "gk_ynaf.out    "'"Capacity for aggregated countries and fuel, all years in all BB4 models"' /;

PUT  "eg_yat.out     "'"Electricicy generations by Year, Areas and (S,T) (GWh)"'   /;
PUT  "eg_yr.out      "'"Electricicy generations by Year, Regions (GWh)"'   /;
PUT  "eg_yc.out      "'"Electricicy generations by Year, Countries (GWh)"'   /;
PUT  "eg_yna.out     "'"Electricicy generations by Year, countries (GWh)"'   /;
PUT  "eg_ynaf.out    "'"Electricicy generations by Year, countries by fuel(GWh)"'   /;

PUT  "mco2_yc.out     "'"Annual CO2 emissions by country"'   /;                  !! TODO text
PUT  "mco2_yna.out    "'"Total Annual CO2 emissions(aggregated)"' /;             !! TODO text
PUT  "mpco2_yc.out    "'" CO2 shadow price by country"'      /;                  !! TODO text
PUT  "mpco2_yna.out   "'" CO2 shadow price (aggregated)"'      /;               !! TODO text

PUT  "de_yc.out       "'" Electricity demand by Year and country"'      /;
PUT  "de_yna.out      "'" Electricity demand by aggregated country"'      /;    !! TODO text

$ifi %DEFPCALIB%==yes  PUT "dfp_calib.out   "'"Used for calibration of demand functions for electricty and heat"'/;



$label doneBB4

PUT /"The naming of the printout files is made according to the following idea:" / ;

PUT "The first letter(s) indicate(s) the subject of the output files. "/;
PUT "Then there is an underscore followed by letters which indicate the level of detail."/;
PUT " C, R or A indicates the geographical level of detail. "/;
PUT " Y, S or T indicates the level of time segments. "/;
PUT " G indicates that information for each particular technology is available. "/;
PUT " Z is used to summarise over the following letters."/;
PUT "If there are no letters to identify the geographic level  "/;
PUT "the file contains information for all countries that are simulated in Balmorel. "/;
PUT "If there is no letter to identify the time segments  "/;
PUT "the file contains information for the whole time span that is simulated in Balmorel."/ /;

PUT "In summary, the content of the output files are indicated by the following letters used in the file names: "/;
PUT " E: Electricity                          "/;
PUT " H: Heat                                 "/;
PUT " F: Fuels                                "/;
PUT " M: Emissions (MCO2, MSO2 and MNOx)      "/;
PUT " G: Generation                           "/;
PUT " D: Demand                               "/;
PUT " P: Prices                               "/;
PUT " K: Capacity                             "/;
PUT " X: Transmission                         "/;
PUT " O: Old (exogenously specified) plants   "/;
PUT " N: New plants                           "/;
PUT " C: Country                              "/;
PUT " R: Region                               "/;
PUT " A: Area                                 "/;
PUT " Y: Year                                 "/;
PUT " S: Season                               "/;
PUT " T: Time period within season            "/;
PUT " Z: Summation                            "/;
