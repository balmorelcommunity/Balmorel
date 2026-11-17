* File: mco2_yna.inc

* Modified last time: 20150422(Weiming)

* This file prints the national CO2 emission values



* -----------------------------------------------------------------------------

PUT mco2_yna;

* First print headings:

if ((mco2_yna.pw LT 32000),
mco2_yna.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "mco2_yna.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
$ifi %BB4%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE4"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

PUT "Annual CO2 emissions" //;

PUT "Units: Million tonnes" //;

);

* End of file headings.
* ------------------------------------------------------------------------------------

* -----------------------------------------------------------------------------
LOOP(IY411FIRST,
PUT "BB4 model starting year "  IY411FIRST.TL:4 "..............................:" //;
mco2_yna.LJ = 1;
PUT "YEAR        " ; PUT /;
mco2_yna.LJ = 2;
  LOOP(IY411,PUT IY411.TL ;

OSCALAR1=0;
OSCALAR1=SUM(C,
       IOF0000001*SUM(IA$ICA(C,IA),
                     (  SUM(IGE,
                             SUM((S,T),IHOURSINST(S,T)*(IM_CO2(IGE)*IOF0001)*IOF3P6*VGE_T.L(IY411,IA,IGE,S,T)/GDATA(IGE,'GDFE')*GEFFRATE(IA,IGE))
                           )

                      + SUM(IGH,
                             SUM((S,T),IHOURSINST(S,T)*(IM_CO2(IGH)*IOF0001)*IOF3P6*GDATA(IGH,'GDCV')*VGH_T.L(IY411,IA,IGH,S,T)/GDATA(IGH,'GDFE')*GEFFRATE(IA,IGH))

                           )
                      )
                   )
       )

PUT OSCALAR1:OTLWCRA:2; PUT /;

  )PUT /;
)



$ontext
mco2_cy.LJ = 2;


ISCALAR1=0;
ISCALAR2=0;

PUT Y.TL:4:0; PUT "    ";
LOOP(C,

ISCALAR1= (
               SUM((IA,G,S,T)$((IAGK_Y(IA,G) or IAGKN(IA,G)) and ICA(C,IA)), IHOURSINST(S,T) * (IM_CO2(G)/IOF1000) * IOF3P6 *
                  VGF_T.l(IA,G,S,T)$IAGK_Y(IA,G)
                 +VGF_T.l(IA,G,S,T)$(VGKN.l(IA,G) and IAGKN(IA,G)) )
         );


 PUT ISCALAR1:12:0 ;
 ISCALAR2=ISCALAR2+ISCALAR1;
);
 PUT ISCALAR2:12:0 /;


*PUT "CO2 max level (ton)        " ; LOOP(C, PUT LIM_CO2_Y(C):12:0 ); PUT /;
*PUT "CO2 shadowprice (USD/ton)  " ; LOOP(C, PUT QLIMCO2.M(C):12:0 ); PUT /;

$offtext
