* File print1.inc.

* File last time modified 27-09-2002 (rus) , 05-08-2003 (sns), hr 20110920, hr 20121001, 20141121(hr).

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

SCALAR OIMONEY "EUR90" /1/;  !! Input currency name in the text field (e.g., "EUR90"). The numerical value is not used.

PARAMETER OCARDSETA;  /* To hold the number of areas in the simulation */
OCARDSETA=0;
LOOP(IA, OCARDSETA=OCARDSETA+1);

PARAMETER OCARDSETR;  /* To hold the number of regions in the simulation */
OCARDSETR=0;
LOOP(IR, OCARDSETR=OCARDSETR+1);

PARAMETER OSCALAR1, OSCALAR2, OSCALAR3; /* Various general counters */

* For printing: OTLW, OTLW1, OTLG, OTL1, OTLCRA for specifying more general field widths in printing:
* (O=Output, TLW=TextLabelWidth)
* Note that the text strings (OTLW.ts) must contain the same number of blanks as the value indicates,
* if you want to use this text string to privide empty space of same width as a ".TL:OTLW" provides.
* Present choice: 32, consistent with the maximal length of identifiers and labels in GAMS before version 22.7.
* From GAMS version 22.7 this was increased to 64.
* The advantage, depending on circumstances, of using the same values for all SETS
* is homegenity (nice columns) in the output, the disadvantage is the potential superfluous space.

* More set individual values are held in
*
SCALAR OTLW     "                                " /32/;
*SCALAR OTLW1   "    " /4/;                              !! OTLW1 is meant for text labels that are known to be that 'small' in Balmorel. Presently not in use.
SCALAR OTLWG    "                                " /0/;  !! Note: For set GGG specifically. The value is set below
SCALAR OTLWY    "    " /4/;                              !! Note: For set Y specifically.
SCALAR OTLWCRA  "                                " /0/;  !! Note: For set CCCRRRAAA specifically. The value is set below
OTLWG   = SMAX(GGG, CARD(GGG.TL));
OTLWCRA = SMAX(CCCRRRAAA, CARD(CCCRRRAAA.TL));

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
FILE EHMCO2qRT  /"../output/printout/EHMCO2qRT.out"/;   

*FILE egwater_rs /"../output/printout/egwater_rs.out"/; TODO (hr)

* Investments in technology:
FILE gkn_ag     /"../output/printout/gkn_ag.out"/;

* Calibration
$ifi %DEFPCALIB%==yes FILE dfp_calib  /"../output/printout/dfp_calib.out"/;


* -----------------------------------------------------------------------
* Block (B):
* Delete all existing printout files before printing any new ones:
execute 'rm  "../output/printout/*.*';

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

PUT "bal_1.out       "'"Energy balance by year and country"'/;
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
