* File print1.inc.

* File last time modified 27-09-2002 (rus) , 05-08-2003 (sns), hr 20110920

* This file is part of the Balmorel model, version 3.02 (November 2011)

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


* The following is used for identification of your case:
SCALAR OCASEID "Balmorel Demo-example." ;



PARAMETER OCARDSETA;  /* To hold the number of areas in the simulation */
OCARDSETA=0;
LOOP(IA, OCARDSETA=OCARDSETA+1);

PARAMETER OCARDSETR;  /* To hold the number of regions in the simulation */
OCARDSETR=0;
LOOP(IR, OCARDSETR=OCARDSETR+1);

PARAMETER OSCALAR1, OSCALAR2, OSCALAR3; /* Various general counters */

* For printing: OTLW, OTLW1, OTLG, OTL1 for specifying field widths in printing:
* Note that the text strings (OTLW.ts etc.) must contain the same number of blanks as the value indicates.
* Present choice: 32, consistent with the maximal length of identifiers and labels in GAMS before version 22.7.
* OTLW1 is meant for text labels that are known to be 'small', e.g. for years Y that are four characters long.
*
SCALAR OTLW  "                                " /32/;
SCALAR OTLW1 "    " /4/;
SCALAR OTLG  "                                " /32/;
SCALAR OTL1  "    " /4/;


ALIAS(S,OALIASS);
ALIAS(T,OALIAST);





* -----------------------------------------------------------------------
* Calibration
FILE dfp_calib  /"../output/printout/dfp_calib.out"/;

* -----------------------------------------------------------------------

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

FILE EGWATER_RS /"../output/printout/EGWATER_RS.OUT"/;

* Investments in technology:
* FILE gkn_ag     /"../output/printout/GKN_AG.OUT"/;   Not possible presently, will come ..
