* File: f_fcy.inc
* This file is part of the Balmorel model.

* Modified last time: 01-02-2002 by (rus), 16-02-2004 (ld), 20060328(hr), 200804xx(hr), 20110508(hr), 20150512(hr)

* This file will print a table containing annual net electricity generation from all technologies in each country.
* (Incl. the negative electricity generation for heat pumps)


* -----------------------------------------------------------------------------

PUT f_fcy;

* First print headings:

if ((f_fcy.pw LT 32000),
f_fcy.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "f_fcy.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

$ifi %BB1%==yes PUT / "Annual fuel use by fuel type and country. Annual electricity and heat output by fuel type and country. Output/input relation." //;
$ifi %BB2%==yes PUT / "Annual fuel use by fuel type and country. Annual electricity and heat output by fuel type and country. Old plus new technologies. Output/input relation." //;
$ifi %BB3%==yes PUT / "Annual fuel use by fuel type and country. Annual electricity and heat output by fuel type and country. Output/input relation." //;

*PUT "(Incl. negative electricity generation for heat pumps)" /;
PUT "Units: GWh" //;
);

* End of file headings.
* ------------------------------------------------------------------------------------

* -----------------------------------------------------------------------------


* Two parts, completely independent, so you may comment out one of them.

* ==== Part 1: no distinction between electricity and heat ===

PUT "Left half: fuel input. Right half: output in form of electricity plus heat:"//;

f_fcy.LJ = 2;
PUT Y.TL:OTLW:0;

f_fcy.LJ = 1;
*                                                                      |<------ OTLW characters ----->|                        |<------ OTLW characters ----->|
LOOP(C, PUT  "%PRINTSEPARATOR%" C.TL:OTLW) ;   PUT "%PRINTSEPARATOR%" "                             Sum";
LOOP(C, PUT  "%PRINTSEPARATOR%" C.TL:OTLW) ;   PUT "%PRINTSEPARATOR%" "                             Sum"  "%PRINTSEPARATOR%"  "                    Output/input" /;
f_fcy.LJ = 2;

LOOP(FFF,
PUT  FFF.TL:OTLW "%PRINTSEPARATOR%";
* Fuel Input: ------------------

ISCALAR2=0;
LOOP(C,
ISCALAR1=SUM(IA$ICA(C,IA),
      SUM((IS3,T), IHOURSINST(IS3,T)*(
             SUM(IGE$(IGF(IGE,FFF) AND IAGK(IA,IGE)),    VGE_T.L(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')*(1$(NOT GEFFRATE(IA,IGE))+GEFFRATE(IA,IGE))) )
            +SUM(IGH$(IGF(IGH,FFF) AND IAGK(IA,IGH)),    GDATA(IGH,'GDCV')*VGH_T.L(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*(1$(NOT GEFFRATE(IA,IGH))+GEFFRATE(IA,IGH))))
            +SUM(IGE$(IGF(IGE,FFF) AND AGKN(IA,IGE)),    VGEN_T.L(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')*(1$(NOT GEFFRATE(IA,IGE))+GEFFRATE(IA,IGE))))
            +SUM(IGH$(IGF(IGH,FFF) AND AGKN(IA,IGH)),    GDATA(IGH,'GDCV')*VGHN_T.L(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*(1$(NOT GEFFRATE(IA,IGH))+GEFFRATE(IA,IGH))))
)));
PUT (ISCALAR1*IOF0001):OTLW:0  "%PRINTSEPARATOR%";
ISCALAR2=ISCALAR2+ISCALAR1;
);
PUT (ISCALAR2*IOF0001):OTLW:0 "%PRINTSEPARATOR%";

* Electricity plus heat output: ------------------


ISCALAR3=0;
LOOP(C,
ISCALAR1=SUM(IA$ICA(C,IA),
      SUM((IS3,T), IHOURSINST(IS3,T)*(
             SUM(IGE$IGF(IGE,FFF),    VGE_T.L(IA,IGE,IS3,T)  )
            +SUM(IGH$IGF(IGH,FFF),    GDATA(IGH,'GDCV')*VGH_T.L(IA,IGH,IS3,T) )
            +SUM(IGE$IGF(IGE,FFF),    VGEN_T.L(IA,IGE,IS3,T) )
            +SUM(IGH$IGF(IGH,FFF),    GDATA(IGH,'GDCV')*VGHN_T.L(IA,IGH,IS3,T) )
)));
PUT (ISCALAR1*IOF0001):OTLW:0 "%PRINTSEPARATOR%";
ISCALAR3=ISCALAR3+ISCALAR1;
);
PUT (ISCALAR3*IOF0001):OTLW:0   "%PRINTSEPARATOR%";
PUT$(ISCALAR2 GT 0) (ISCALAR3/ISCALAR2):OTLW:3 ; /* 'EFFICIENCY' */
PUT   /;
);


* ==== Part 2: distinction between electricity and heat ===


PUT / / "Left half: fuel input. Right half: output in form of electricity and heat, respectively:"//;


PUT /;
f_fcy.LJ = 2;
PUT Y.TL:OTLW:0;

f_fcy.LJ = 1;
*                                                                      |<------ OTLW characters ----->|                        |<------ OTLW characters ----->|
LOOP(C, PUT  "%PRINTSEPARATOR%" C.TL:OTLW) ;   PUT "%PRINTSEPARATOR%" "                             Sum";
LOOP(C, PUT  "%PRINTSEPARATOR%" C.TL:OTLW) ;   PUT "%PRINTSEPARATOR%" "                             Sum"  "%PRINTSEPARATOR%"  "                    Output/input" /;


f_fcy.LJ = 2;

LOOP(FFF,
PUT FFF.TL:OTLW  "%PRINTSEPARATOR%";
* Fuel Input: ------------------
ISCALAR2=0;   /* To become sum over countries */
LOOP(C,
ISCALAR1=SUM(IA$ICA(C,IA),
      SUM((IS3,T), IHOURSINST(IS3,T)*(
             SUM(IGE$(IGF(IGE,FFF) AND IAGK(IA,IGE)), VGE_T.L(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')*(1$(NOT GEFFRATE(IA,IGE))+GEFFRATE(IA,IGE))) )
            +SUM(IGH$(IGF(IGH,FFF) AND IAGK(IA,IGH)), GDATA(IGH,'GDCV')*VGH_T.L(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*(1$(NOT GEFFRATE(IA,IGH))+GEFFRATE(IA,IGH))))
            +SUM(IGE$(IGF(IGE,FFF) AND AGKN(IA,IGE)), VGEN_T.L(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')*(1$(NOT GEFFRATE(IA,IGE))+GEFFRATE(IA,IGE))))
            +SUM(IGH$(IGF(IGH,FFF) AND AGKN(IA,IGH)), GDATA(IGH,'GDCV')*VGHN_T.L(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*(1$(NOT GEFFRATE(IA,IGH))+GEFFRATE(IA,IGH))))
)));
PUT (ISCALAR1*IOF0001):OTLW:0  "%PRINTSEPARATOR%";
ISCALAR2=ISCALAR2+ISCALAR1;
);
PUT (ISCALAR2*IOF0001):OTLW:0 "%PRINTSEPARATOR%";

* Electricity and heat output: ------------------

*put "      ";
ISCALAR3=0;
LOOP(C,
ISCALAR1=SUM(IA$ICA(C,IA),
      SUM((IS3,T), IHOURSINST(IS3,T)*(
             SUM(IGE$IGF(IGE,FFF),    VGE_T.L(IA,IGE,IS3,T)  )
            +SUM(IGH$IGF(IGH,FFF),    GDATA(IGH,'GDCV')*VGH_T.L(IA,IGH,IS3,T) )
            +SUM(IGE$IGF(IGE,FFF),    VGEN_T.L(IA,IGE,IS3,T) )
            +SUM(IGH$IGF(IGH,FFF),    GDATA(IGH,'GDCV')*VGHN_T.L(IA,IGH,IS3,T) )
)));
PUT (ISCALAR1*IOF0001):OTLW:0  "%PRINTSEPARATOR%";
ISCALAR3=ISCALAR3+ISCALAR1;
);
PUT (ISCALAR3*IOF0001):OTLW:0  "%PRINTSEPARATOR%";
PUT$(ISCALAR2 GT 0) (ISCALAR3/ISCALAR2):OTLW:3   /* 'EFFICIENCY' */
PUT /;

*    |<------ OTLW characters ----->|                                      |<------ OTLW characters ----->|                                  |<------ OTLW characters ----->|
PUT "       Electricity              ";   LOOP(C, PUT  "%PRINTSEPARATOR%" "                               -") ;     PUT  "%PRINTSEPARATOR%" "                               -"  "%PRINTSEPARATOR%";
ISCALAR3=0;
LOOP(C,
ISCALAR1=SUM(IA$ICA(C,IA),
      SUM((IS3,T), IHOURSINST(IS3,T)*(
             SUM(IGE$IGF(IGE,FFF),    VGE_T.L(IA,IGE,IS3,T)  )
*            +SUM(IGH$IGF(IGH,FFF),    GDATA(IGH,'GDCV')*VGH_T.L(IA,IGH,IS3,T) )
            +SUM(IGE$IGF(IGE,FFF),    VGEN_T.L(IA,IGE,IS3,T) )
*            +SUM(IGH$IGF(IGH,FFF),    GDATA(IGH,'GDCV')*VGHN_T.L(IA,IGH,IS3,T) )
)))
PUT (ISCALAR1*IOF0001):OTLW:0  "%PRINTSEPARATOR%";
ISCALAR3=ISCALAR3+ISCALAR1;
);
PUT PUT (ISCALAR3*IOF0001):OTLW:0   "%PRINTSEPARATOR%" /;
*    |<------ OTLW characters ----->|                                       |<------ OTLW characters ----->|             |<------ OTLW characters ----->|
PUT "       Heat                     ";    LOOP(C, PUT "%PRINTSEPARATOR%"  "                               -") ;    PUT  "%PRINTSEPARATOR%" "                               -"  "%PRINTSEPARATOR%";
ISCALAR3=0;
LOOP(C,
ISCALAR1=SUM(IA$ICA(C,IA),
      SUM((IS3,T), IHOURSINST(IS3,T)*(
*             SUM(IGE$IGF(IGE,FFF),    VGE_T.L(IA,IGE,IS3,T)  )
            +SUM(IGH$IGF(IGH,FFF),    GDATA(IGH,'GDCV')*VGH_T.L(IA,IGH,IS3,T) )
*            +SUM(IGE$IGF(IGE,FFF),    VGEN_T.L(IA,IGE,IS3,T) )
            +SUM(IGH$IGF(IGH,FFF),    GDATA(IGH,'GDCV')*VGHN_T.L(IA,IGH,IS3,T) )
)))
PUT (ISCALAR1*IOF0001):OTLW:0  "%PRINTSEPARATOR%";
ISCALAR3=ISCALAR3+ISCALAR1;
);
PUT  (ISCALAR3*IOF0001):OTLW:0  "%PRINTSEPARATOR%" /;


);

PUT /;







*PUT "TOTAL       " ; LOOP(C, PUT ( sum(ignotetoh,EGqCY(C,ignotetoh)*IOF0001) + sum(igetoh,-EGqCY(C,igetoh)*IOF0001)):OTLW:0 ; ); PUT //;          /*sarah*/
