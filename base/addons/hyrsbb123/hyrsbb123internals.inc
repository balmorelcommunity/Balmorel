* The three parameters WATERVOLINI, WATERVAL and VHYRS_SLare declared as standard in the Balmorel model.
* Additional declaration and definitions for HYRSBB123 only are given here.

* In BB3 the following set and parameters are used to control the use of hydro with storage, conditioned by HYRSBB123:

SET       IHYRSBB12DELTASET           "Increase steps of hydro generation above BB1 level" / IHYRSBB123G1*IHYRSBB123G5  /;

PARAMETER IHYRSBB123G_Y(AAA,SSS)      "Water (hydro) generation quantity of the seasons transferred from model BB1/BB2 for use in model Balbase3 (MWh)";
PARAMETER IWATERVAL_Y(AAA,SSS)        "Water value (in input Money) transferred from model BB1/BB2 for use in model Balbase3 (MWh)";
PARAMETER IHYRSBB123BB3GACCUM(AAA)    "The amount of water used so far during present year during BB3 solutions (MWh)";
PARAMETER IHYRSBB123BB12GACCUM(AAA)   "The amount of water used so far during present year according to BB1/BB2 solution (MWh)";
PARAMETER IHYRSBB123DELTAVOL(AAA)     "Amount of additional hydro energy (relative to BB1/BB2) pre-allocated this season (may be negative) in model BB3 (MWh)";
PARAMETER IHYRSBB123VOLINI(AAA,S)     "Initial storage level (MWh)";
PARAMETER IHYRSBB123EXTRAVAL(AAA,S,IHYRSBB12DELTASET);


* Test that Card(S) is equal to Card(SSS):
IF((CARD(S) NE CARD(SSS)),
*   PUT ERRORFILE "Warning from addon hyrsbb123, file hyrsbb123sim3.inc:"/;
*   PUT "Card(S) is not equal to Card(SSS), it must be." /;
    DISPLAY "Warning from addon hyrsbb123, file hyrsbb123sim3.inc:";
    DISPLAY "Card(S) is not equal to Card(SSS), it must be." ;
);


$label label_hydrobb123internals