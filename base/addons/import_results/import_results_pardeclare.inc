* The three parameters WATERVOLINI, WATERVAL and VHYRS_SLare declared as standard in the Balmorel model.
* Additional declaration and definitions for HYRSBB123 only are given here.

$ifi %HYRSBB123%==none    $goto label_no_hydro_results_import

PARAMETER IHYRSBB123G_Y(Y,AAA,SSS)      "Water (hydro) generation quantity of the seasons transferred from model BB1/BB2 for use in model Balbase3 (MWh)";
PARAMETER IWATERVAL_Y(Y,AAA,SSS)        "Water value (in input Money) transferred from model BB1/BB2 for use in model Balbase3 (MWh)";
PARAMETER IHYRSBB123BB3GACCUM(Y,AAA)    "The amount of water used so far during present year during BB3 solutions (MWh)";
PARAMETER IHYRSBB123BB12GACCUM(Y,AAA)   "The amount of water used so far during present year according to BB1/BB2 solution (MWh)";
PARAMETER IHYRSBB123DELTAVOL(Y,AAA)     "Amount of additional hydro energy (relative to BB1/BB2) pre-allocated this season (may be negative) in model BB3 (MWh)";
PARAMETER IHYRSBB123VOLINI(Y,AAA,S)     "Initial storage level (MWh)";
PARAMETER IHYRSBB123EXTRAVAL(Y,AAA,S,IHYRSBB12DELTASET);


* Test that Card(S) is equal to Card(SSS):
IF((CARD(S) NE CARD(SSS)),
*   PUT ERRORFILE "Warning from addon hyrsbb123, file hyrsbb123sim3.inc:"/;
*   PUT "Card(S) is not equal to Card(SSS), it must be." /;
    DISPLAY "Warning from addon hyrsbb123, file hyrsbb123sim3.inc:";
    DISPLAY "Card(S) is not equal to Card(SSS), it must be." ;
);

$label label_no_hydro_results_import

