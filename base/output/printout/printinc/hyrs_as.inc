* File: HYRS_AS.INC

* Modified last time:  20120830(hr)

* This file will print
*  a table containing hydro electricity generation by season
*  a table containing hydro energy (water) inflow by season
*  a table containing storage levels for hydro with storage.


* -----------------------------------------------------------------------------

PUT hyrs_as;

* First print headings:

if ((hyrs_as.pw LT 32000),
hyrs_as.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "hyrs_at.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3 Error: in this case this file should not have been generated."/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;
PUT '"Electricity generation from water reservoirs by season (MWh)"' /;
PUT '"Hydro energy (water) inflow to water reservoirs by season (MWh)"' /;
PUT '"Storage levels at beginning of seasons for hydro with storage (MWh)"'/;
PUT '"Electricity prices (water values) by season in hydro with storage areas (Output Money/MWh)"'/;
PUT '"Electricity prices (water values) by season in hydro with storage areas (Input Money/MWh)"'/;
);

* End of headings.


* -----------------------------------------------------------------------------
* ------------------------------------------------------------------------------------

$ifi %BB2%==yes PUT '"Presently not implemented for BB2"' /;
$ifi %BB2%==yes $goto endofhyrsas
$ifi %BB3%==yes $goto endofhyrsas



* ==================================================================================

PUT / / '"Electricity generation from water reservoirs by season (MWh)"' /;

PUT /;
PUT "                    ";
LOOP(IA$SUM(IGHYRS,IAGK_Y(IA,IGHYRS)), PUT IA.TL:20;);
PUT / ;
LOOP(S, PUT S.TL:10;
LOOP(IA$SUM(IGHYRS,IAGK_Y(IA,IGHYRS)),
      ISCALAR1 = SUM(IGHYRS$IAGK_Y(IA,IGHYRS),SUM(T,IHOURSINST(S,T)*(VGE_T.L(IA,IGHYRS,S,T))));
      PUT ISCALAR1:20:1;
    );
PUT / ;
);

* ==================================================================================

PUT / / '"Hydro energy (water) inflow to water reservoirs by season (MWh)"' /;
$ifi %BB2%==yes PUT '"Presently not implemented for BB2"' /;
PUT /;
PUT "                    ";
LOOP(IA$SUM(IGHYRS,IAGK_Y(IA,IGHYRS)), PUT IA.TL:20;);
PUT / ;
LOOP(S, PUT S.TL:10;
LOOP(IA$SUM(IGHYRS,IAGK_Y(IA,IGHYRS)),
      ISCALAR1 = IHYINF_S(IA,S) * SUM(IGHYRS$IAGK_Y(IA,IGHYRS), (IGKVACCTOY(IA,IGHYRS)+IGKFX_Y(IA,IGHYRS)));  !! IGKVACCTOY only valid for BB2
      PUT ISCALAR1:20:1;
    );
PUT / ;
);



* ==================================================================================

PUT / / '"Storage levels at beginning of seasons for hydro with storage (MWh)"' /;
$ifi %BB1%==yes PUT '"Here with BB1 the end-of-year level (not shown) is the same as the beginning-of-year level"' /;
$ifi %BB2%==yes PUT '"Here with BB2 the end-of-year level (not shown) is the same as the beginning-of-year level"' /;
PUT /;
PUT "                    ";
LOOP(IA$SUM(IGHYRS,IAGK_Y(IA,IGHYRS)), PUT IA.TL:20;);
PUT / ;
LOOP(S, PUT S.TL:10;
LOOP(IA$SUM(IGHYRS,IAGK_Y(IA,IGHYRS)),
      PUT VHYRS_S.L(IA,S):20:1;
    );
PUT / ;
);


PUT / / '"Electricity prices (water values) by season in hydro with storage areas (Output Money/MWh)"' / ;
PUT "Currency: " OMONEY.TS "  with exchange rate to input currency: "  OMONEY:7:3  " ("OMONEY.TS"/EUR90), Units: "; PUT OMONEY.ts "/MWh" / /;
PUT "                    ";
LOOP(IA$SUM(IGHYRS,IAGK_Y(IA,IGHYRS)), PUT IA.TL:20;);
PUT / ;
LOOP(S, PUT S.TL:10;
LOOP(IA$SUM(IGHYRS,IAGK_Y(IA,IGHYRS)),
      PUT (QHYRSSEQ.M(IA,S)*OMONEY):20:1;
    );
PUT / ;
);




PUT / / '"Electricity prices (water values) by season in hydro with storage areas (Output Money/MWh)' / /;
PUT "                    ";
LOOP(IA$SUM(IGHYRS,IAGK_Y(IA,IGHYRS)), PUT IA.TL:20;);
PUT / ;
LOOP(S, PUT S.TL:10;
LOOP(IA$SUM(IGHYRS,IAGK_Y(IA,IGHYRS)),
      PUT (QHYRSSEQ.M(IA,S)):20:1;
    );
PUT / ;
);

$label endofhyrsas
