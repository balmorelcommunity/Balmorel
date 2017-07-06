* File: dfp_calib.inc
* Rev 2.14

* Used for calibration of demand functions for electricty and heat,
* more specifically, the tables DEFP_CALIB and DHFP_CALIB are generated.

PUT dfp_calib;

dfp_calib.PW = 255;




* First print headings:

if ((dfp_calib.pw LT 32000),
dfp_calib.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "dfp_calib.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;


PUT "This file was created as part of the calibration proces" /;
PUT "for the Balmorel model. "  /;
PUT "The tables below (or some modification thereof) and their associated text "/;
PUT "could replace the existing similar tables in the file DEFP_CALIB.inc." /;
PUT "The following table was calculated for " Y.TL ///;
PUT "* PARAMETER DEFP_CALIB is used to calibrate the price side "/;
PUT "* of the electricity demand function" /;
PUT "* in order to get consumptions consistent for a base year."/;
PUT "* Unit: Money/MWh."/;
PUT "* Table DEFP_CALIB was created in " SYSTEM.TITLE  /;
PUT "* "SYSTEM.DATE " " SYSTEM.TIME //;
);

IF((CARD(S)*CARD(T) LE 16),
* The following format assumes a small number of time segments.
PUT "TABLE DEFP_CALIB(RRR,SSS,TTT)"/;
PUT  "               ";
LOOP(S,
  LOOP(T, PUT  S.TL:2 "." T.TL:2 "     ";
 );); PUT /;
LOOP(IR,
  PUT IR.TL:10 ;
  LOOP(S,
  LOOP(T, PUT
       ((IOF1_*QEEQ.M(IR,S,T)/(IDAYSIN_S(S)*IHOURSIN24(T)))/(1-DISLOSS_E(IR))
       + SUM(C$CCCRRR(C,IR),TAX_DE(C)) + DISCOST_E(IR) - DEFP_BASE(IR)
       - DEFP_CALIB(IR,S,T)):10:4;
  );); PUT /;
); PUT  ";" ;

ELSE
* This NOT revised 2.14:

* The following format accomodates a larger number of time segments.
PUT "TABLE DEFP_CALIB(RRR,SSS,TTT)"/;
PUT  "              ""               ";
LOOP(T,  PUT T.TL:10 ); PUT /;
LOOP(IR,
LOOP(S,
  PUT IR.TL:10 "." S.TL:10 ;
LOOP(T, PUT  ((IOF1_*QEEQ.M(IR,S,T)/(IDAYSIN_S(S)*IHOURSIN24(T)))/(1-DISLOSS_E(IR))
       + SUM(C$CCCRRR(C,IR),TAX_DE(C)) + DISCOST_E(IR) - DEFP_BASE(IR)
       - DEFP_CALIB(IR,S,T)):10:4;
     ); PUT /;
 ););  PUT  ";" ;

);

PUT //////;








PUT "* PARAMETER DHFP_CALIB is used to calibrate the price side "/;
PUT "* of the heat demand function" /;
PUT "* in order to get consumptions consistent for a base year."/;
PUT "* Unit: Money/MWh."/;
PUT "* Table DHFP_CALIB was created in " SYSTEM.TITLE  /;
PUT "* "SYSTEM.DATE " " SYSTEM.TIME //;
PUT "* NOTE: The calibration code for heat has not been made, " /;
PUT "* because presently heat demand is assumed inelastic." //;
