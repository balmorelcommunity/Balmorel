* File error2.inc

* This file is part of the Balmorel model.

* File last time modified 17-05-2002 (rus), 2005.07.31 (hr), 2005.12.17 (hr), 20080414(hr), 20120319(hr), 20120914(hr), 20150312(hr), 20150503(hr), 20150519(hr), 20150703(hr), 20160407(hr), 20160826(hr), 20170328(hr)
* Note: The comments below in this file are not updated to reflect the file strucutre introduced with Balmorel version 3.xx.


* This file contains check on input data.
* This file should be included into the Balmorel.gms file
* immediately before the SOLVE statement.
* The checks are not necessarily 'logical', rather they check for
* 'reasonable' values (e.g., that most efficiencies are between 0 and 1),
* and values that for the present model must be within certain ranges.
* Some checks are performed on the full extension in dimensions of geography, time and technology
* while others only on what is includd in the present model delimited to C, Y, S, T and G.

* Check the code below to see the exact meaning of this.



PUT ERRORFILE;

PUT / "The input data was investigated for obvious errors.";
PUT / "Investigation is only performed for data that are to be included in the model."//;

* Subset of GGG to any use:
SET ERRSETGGG(GGG) "Subset of GGG to any use";



*------------------------------------------------------------------------------
* Parameter YVALUE(YYY) holds the numerical value of each year.
* The following checks only relates to the 'distance' between years, not that the first year's YVALUE is correct.
ISCALAR1 = ERRCOUNT2;
LOOP(YYY$(ORD(YYY) EQ 1), ISCALAR2 = YVALUE(YYY););
LOOP(YYY,
  IF((YVALUE(YYY) NE ((ORD(YYY)-1) + ISCALAR2)),
    PUT "Error: Parameter YVALUE(YYY) holds the numerical value of each year, check for year " YYY.TL:4 /;
    ERRCOUNT2 = ERRCOUNT2 +1;
  );
);
IF((ISCALAR1 LT ERRCOUNT2),
  PUT /;
);
*------------------------------------------------------------------------------


*------------------------------------------------------------------------------
*--- DATA IN THE FILE sets.inc:-------------------------------------------------

*-------- set GGCOMB -----------------------------------------------------------


*-------- sets TWORKDAY and TWEEKEND -------------------------------------------

SET ICHECKWDAY(TTT);
ICHECKWDAY(TTT)=  TWORKDAY(TTT) * TWEEKEND(TTT);
IF((CARD( ICHECKWDAY ) GT 0 ),
PUT "The classification of the elements of SET TTT into TWORKDAY(TTT) and TWEEKEND(TTT)"/;
PUT "    should be mutually exclusive, it is not, the elements " ;
loop(TTT$ICHECKWDAY(TTT), put  TTT.tl:12);
PUT"  are in both TWORKDAY   and  TWEEKEND."//;
ERRCOUNT2=ERRCOUNT2+1;
);
ICHECKWDAY(TTT)=NO;
ICHECKWDAY(TTT)= TTT(ttt)- TWORKDAY(TTT)-TWEEKEND(TTT);
IF((card(ICHECKWDAY) GT 0),
PUT "The classification of the elements of SET TTT into TWORKDAY(TTT) and TWEEKEND(TTT)"/;
PUT "    should be exhaustive, it is not, the elements " ;
loop(TTT$ICHECKWDAY(TTT), put  TTT.tl:12);
PUT"  are neither in TWORKDAY nor in TWEEKEND."//;
ERRCOUNT2=ERRCOUNT2+1;
);


*-------------------------------------------------------------------------------
*--- DATA IN THE FILE trans.inc:------------------------------------------------


*---TABLE XCOST AND TABLE XLOSS-------------------------------------------------
* Unreasonable results of the optimization may be found
* if there are neither cost nor loss associated with electrical transmission.
* Therefore for all (non-diagonal) entries there should be a positive number
* in either TABLE XCOST or in TABLE XLOSS.

ISCALAR1 = ERRCOUNT2;
LOOP((IRRRE,IRRRI)$((ORD(IRRRE) NE ORD(IRRRI)) ),
IF((XCOST(IRRRE,IRRRI) + XLOSS(IRRRE,IRRRI) EQ 0),
PUT "Both XCOST and XLOSS are zero for region pair (";
PUT IRRRE.TL:32"," IRRRI.TL:32")."    " (Not really an error - but may be inconvenient due to possible non-unique solutions for transmission.)" /;
ERRCOUNT2=ERRCOUNT2+1; );
);
IF((ISCALAR1 LT ERRCOUNT2),  PUT "#" /; );
*---END TABLE XCOST AND TABLE XLOSS---------------------------------------------


*-------------------------------------------------------------------------------
*---DATA IN THE FILE var.inc:---------------------------------------------------

ISCALAR1 = ERRCOUNT2;
* The values in WEIGHT_S(S) and WEIGHT_T(T) must all be positive
LOOP(S,
IF((WEIGHT_S(S) LE 0),
PUT " The parameter WEIGHT_S(S) must be positive for all S, it is not for " S.TL:32/;
ERRCOUNT2=ERRCOUNT2+1; );
);

LOOP(T,
IF((WEIGHT_T(T) LE 0),
PUT " The parameter WEIGHT_T(T) must be positive for all T, it is not for " T.TL:32/;
ERRCOUNT2=ERRCOUNT2+1; );
);
ISCALAR1 = ERRCOUNT2; IF((ISCALAR1 LT ERRCOUNT2),  PUT "#"/; );

* Hans 20171030 - demand dependent on user groups added.
ISCALAR1 = ERRCOUNT2;
IF((NOT DEUSER('RESE')),
  PUT "Set DEUSER should have element RESE indicating electricity demand not included in any other user group ('residual electricity demand')" /;
ERRCOUNT2=ERRCOUNT2+1; );

IF((NOT DHUSER('RESH')),
  PUT "Set DHUSER should have element RESH indicating heat demand not included in any other user group ('residual heat demand')" /;
ERRCOUNT2=ERRCOUNT2+1; );
IF((ISCALAR1 LT ERRCOUNT2), PUT "#"/; );


* Hans 20150225; rev. 20171030 (demand user groups):
ISCALAR1 = ERRCOUNT2;
* There must be values in variation file DE_VAR_T if DE is positive.
LOOP(RRR,
 LOOP(DEUSER,
  IF((SUM(YYY,DE(YYY,RRR,DEUSER))),  !! DE is positive for some YYY
    IF((IDE_SUMST(RRR,DEUSER) EQ 0), !! Checking IDE_SUMST rather than DE_VAR_T (easier and OK if basic code is correct)
      PUT "Electricity demand variation DE_VAR_T must have positive values for all RRR and user groups with positive demand DE, it seems not to have for " RRR.TL:32 ", User group "  DEUSER.TE(DEUSER):12;
      IF((NOT IR(RRR)), PUT " - Region is not in model";);  !! Hans 20150519(hr)
      PUT /;
      ERRCOUNT2=ERRCOUNT2+1;
););););
IF((ISCALAR1 LT ERRCOUNT2), PUT "#"/; );

ISCALAR1 = ERRCOUNT2;
* There must be values in variation file DH_VAR_T if DH is positive.
LOOP(AAA,
 LOOP(DHUSER,
  IF((SUM(YYY,DH(YYY,AAA,DHUSER))),  !! DH is positive for some YYY
    IF((IDH_SUMST(AAA,DHUSER) EQ 0), !! Checking IDE_SUMST rather than DH_VAR_T (easier and OK if basic code is correct)
      PUT "Heat demand variation DH_VAR_T must have positive values for all AAA and user groups with positive demand DH, it seems not to have for " AAA.TL:32", User group "  DHUSER.TE(DHUSER):12;
      IF((NOT IA(AAA)), PUT " - Area is not in model";);  !! Hans 20150519(hr)
      PUT /;
      ERRCOUNT2=ERRCOUNT2+1;
););););
IF((ISCALAR1 LT ERRCOUNT2), PUT "#"/; );


ISCALAR1 = ERRCOUNT2;
* There must be values in variation file X3FX_VAR_T if X3FX is positive.
LOOP(RRR,
  IF((SUM(YYY,X3FX(YYY,RRR))),   !! X3FX is positive for some YYY
    IF((IX3FXSUMST(RRR) EQ 0), !! Checking IX3FXSUMST rather than X3FX_VAR_T (easier and OK if basic code is correct)
      PUT "Electricity third regions variation X3FX_VAR_T must have positive values for all RRR, it seems not to have for " RRR.TL:32 /;
      ERRCOUNT2=ERRCOUNT2+1;
);););
IF((ISCALAR1 LT ERRCOUNT2), PUT "#"/; );

ISCALAR1 = ERRCOUNT2;
* Hans 20150302:
* There must be values in variation file WND_VAR_T if GKFX is positive or investments are allowed.
LOOP((AAA,IGWND),
  IF(((SUM(YYY,GKFX(YYY,AAA,IGWND))) OR (AGKN(AAA,IGWND))),  !! GKFX is positive for wind power for some YYY or investments are allowed
    IF((IWND_SUMST(AAA) EQ 0), !! Checking SUMST rather than VAR_T (easier and OK if basic code is correct)
      PUT "Wind power variation WND_VAR_T must have positive values for all AAA with positive wind power capacity or potential investments, it seems not to have for " AAA.TL:32 IGWND.TL:32 /;
      ERRCOUNT2=ERRCOUNT2+1;
);););
IF((ISCALAR1 LT ERRCOUNT2), PUT "#"/; );

ISCALAR1 = ERRCOUNT2;
* There must be values in variation file SOLE_VAR_T if GKFX is positive or investments are allowed.
LOOP((AAA,IGSOLE),
  IF(((SUM(YYY,GKFX(YYY,AAA,IGSOLE))) OR (AGKN(AAA,IGSOLE))),  !! GKFX is positive for wind power for some YYY or investments are allowed
    IF((ISOLESUMST(AAA) EQ 0), !! Checking SUMST rather than VAR_T (easier and OK if basic code is correct)
      PUT "Solar power variation SOLE_VAR_T must have positive values for all AAA with positive solar power capacity or potential investments, it seems not to have for " AAA.TL:32 IGSOLE.TL:32 /;
      ERRCOUNT2=ERRCOUNT2+1;
);););
IF((ISCALAR1 LT ERRCOUNT2), PUT "#"/; );

ISCALAR1 = ERRCOUNT2;
* There must be values in variation file SOLH_VAR_T if GKFX is positive or investments are allowed.
LOOP((AAA,IGSOLH),
  IF(((SUM(YYY,GKFX(YYY,AAA,IGSOLH))) OR (AGKN(AAA,IGSOLH))),  !! GKFX is positive for wind power for some YYY or investments are allowed
    IF((ISOLHSUMST(AAA) EQ 0), !! Checking SUMST rather than VAR_T (easier and OK if basic code is correct)
      PUT "Solar heat variation SOLH_VAR_T must have positive values for all AAA with positive solar heat capacity or potential investments, it seems not to have for " AAA.TL:32 IGSOLH.TL:32 /;
      ERRCOUNT2=ERRCOUNT2+1;
);););
IF((ISCALAR1 LT ERRCOUNT2), PUT "#"/; );

ISCALAR1 = ERRCOUNT2;
* There must be values in variation file SOLE_VAR_T if GKFX is positive or investments are allowed.
LOOP((AAA,IGWAVE),
  IF(((SUM(YYY,GKFX(YYY,AAA,IGWAVE))) OR (AGKN(AAA,IGWAVE))),  !! GKFX is positive for wind power for some YYY or investments are allowed
    IF((IWAVESUMST(AAA) EQ 0), !! Checking SUMST rather than VAR_T (easier and OK if basic code is correct)
      PUT "Wave power variation SOLE_VAR_T must have positive values for all AAA with positive wave power capacity or potential investments, it seems not to have for " AAA.TL:32 IGWAVE.TL:32 /;
      ERRCOUNT2=ERRCOUNT2+1;
);););
IF((ISCALAR1 LT ERRCOUNT2), PUT "#"/; );

ISCALAR1 = ERRCOUNT2;
* There must be values in variation file WTRRRVAR_T if GKFX is positive or investments are allowed.
LOOP((AAA,IGHYRR),
  IF(((SUM(YYY,GKFX(YYY,AAA,IGHYRR))) OR (AGKN(AAA,IGHYRR))),  !! GKFX is positive for wind power for some YYY or investments are allowed
    IF((IWTRRRSUM(AAA) EQ 0), !! Checking SUMST rather than VAR_T (easier and OK if basic code is correct)
      PUT "Hydro run-of-river power variation WTRRRVAR_T must have positive values for all AAA with positive hydro ror power capacity or potential investments, it seems not to have for " AAA.TL:32 IGHYRR.TL:32 /;
      ERRCOUNT2=ERRCOUNT2+1;
);););
IF((ISCALAR1 LT ERRCOUNT2), PUT "#"/; );

ISCALAR1 = ERRCOUNT2;
* There must be values in variation file WTRRSVAR_T if GKFX is positive or investments are allowed.
LOOP((AAA,IGHYRS),
  IF(((SUM(YYY,GKFX(YYY,AAA,IGHYRS))) OR (AGKN(AAA,IGHYRS))),  !! GKFX is positive for wind power for some YYY or investments are allowed
    IF((IWTRRSSUM(AAA) EQ 0), !! Checking SUMST rather than VAR_T (easier and OK if basic code is correct)
      PUT "Hydro with storage power variation WTRRSVAR_T must have positive values for all AAA with positive hydro storage power capacity or potential investments, it seems not to have for " AAA.TL:32 IGHYRS.TL:32 /;
      ERRCOUNT2=ERRCOUNT2+1;
);););
IF((ISCALAR1 LT ERRCOUNT2), PUT "#"/;);

* Check reasonable consistency between the FLHs calculated from the input variation profile over (SSS,TTT) (the whole year) and over (S,T) (the time segments selected).
* For the calculation and check to make sense is must be assumed that DE_VAR_T and DH_VAR_T are given for a whole year, i.e., CARD(SSS)*CARD(TTT) = 8760 ('whole' year).
* It is also assumed that the weights of the segments is in such full-year case the same for all (SSS,TTT), i.e., the corresponding IHOURSINST(SSS,TTT) are the same for all time segments.
* It is important that the present file is included into Balmorel.gms before any elimination of values in the _VAR_T parameters (by setting non-used values to 0).
ISCALAR4=0.1; !! Serves as check value, the quotient should not be more than ISCALAR4 from 1
ISCALAR1=ERRCOUNT2;
* Electricity demand profile DE_VAR_T:
LOOP(IR,
 LOOP(DEUSER$(SMAX(Y,DE(Y,IR,DEUSER))),
  IF((IDE_SUMST(IR,DEUSER) EQ 0),
    PUT "Error: There is positive electicity demand DE but no demand profile DE_VAR_T: Region "  IR.TL:OTLWCRA ", user group " DEUSER.TE(DEUSER):12 /;
    ERRCOUNT2=ERRCOUNT2+1;
  ELSE
    ISCALAR3=(SUM((S,T), IHOURSINST(S,T)*DE_VAR_T(IR,DEUSER,S,T)))/SMAX((S,T),DE_VAR_T(IR,DEUSER,S,T));   !! To become FLH1: the one used.
    ISCALAR5 = (SUM((SSS,TTT), DE_VAR_T(IR,DEUSER,SSS,TTT)))/SMAX((SSS,TTT),DE_VAR_T(IR,DEUSER,SSS,TTT)); !! To become FLH2: as should be. Assuming all IHOURSINST(SSS,TTT) are 1.
    ISCALAR2 = ISCALAR3/ISCALAR5;
    IF((ABS(ISCALAR2-1) GT ISCALAR4),
*     Problem: the quotient is more than ISCALAR4 from 1:
      PUT "Possible Error: The Full Load Hours calculated on (S,T) from the variation profile DE_VAR_T ";  !! FLH1
      PUT "is not close to the Full Load Hours calculated on (SSS,TTT) for region "IR.TL:OTLWCRA ", user group " DEUSER.TL:12 ": "  ISCALAR3:4:0" against " ISCALAR5:4:0;  !! FLH2
      IF((ISCALAR3 GT ISCALAR5) or 1,
        PUT ": The electricity demand variation DE_VAR_T(,,S,T) appears mostly to be closer to the peak than expected from DE_VAR_T(,,SSS,TTT)." /;
      ELSE
        PUT ": The electricity demand variation DE_VAR_T(,,S,T) appears mostly to be more far from the peak than expected from DE_VAR_T(,,SSS,TTT)." /;
      );
      ERRCOUNT2=ERRCOUNT2+1;
););););
IF((ISCALAR1 LT ERRCOUNT2),
PUT "   The above check on reasonable consistency between the FLHs calculated from the input variation profile over (SSS,TTT) (the whole year) and over (S,T) (the time segments selected):"/;
PUT "   For the calculation and check to make sense is must be assumed that DE_VAR_T and DH_VAR_T are given for a whole year, i.e., CARD(SSS)*CARD(TTT) = 8736 ('whole' year)."/;
PUT "   It is also assumed that the weights of the segments is in such full-year case the same for all (SSS,TTT), i.e., the corresponding IHOURSINST(SSS,TTT) are the same for all time segments."/;
PUT "   The above check on Full Load Hours FLH was made with a tolerance on the quotient of " ISCALAR4:5:3"." /;
PUT "   CARD(S)*CARD(T) is " (CARD(S)*CARD(T)):4:0 ", if this number is much smaller than " (CARD(SSS)*CARD(TTT)):4:0 " this may be the explanation, e.g. if the S and T selected do not contain DE_VAR_T or DH_VAR_T values that are representative for the whole year."/;
PUT "#"/;
);

* Heat demand profile DH_VAR_T:
ISCALAR1=ERRCOUNT2;
LOOP(IA,
LOOP(DHUSER$(SMAX(Y,DH(Y,IA,DHUSER))),
  IF((IDH_SUMST(IA,DHUSER) EQ 0),
    PUT "Error: There is positive heat demand DH but no demand profile DH_VAR_T: Area "  IA.TL:OTLWCRA ", user group " DHUSER.TE(DHUSER):12 /;
    ERRCOUNT2=ERRCOUNT2+1;
  ELSE
    ISCALAR3=(SUM((S,T), IHOURSINST(S,T)*DH_VAR_T(IA,DHUSER,S,T)))/SMAX((S,T),DH_VAR_T(IA,DHUSER,S,T));   !! To become FLH1: the one used.
    ISCALAR5 = (SUM((SSS,TTT), DH_VAR_T(IA,DHUSER,SSS,TTT)))/SMAX((SSS,TTT),DH_VAR_T(IA,DHUSER,SSS,TTT)); !! To become FLH2: as should be. Assuming all IHOURSINST(SSS,TTT) are 1.
    ISCALAR2 = ISCALAR3/ISCALAR5;
    IF((ABS(ISCALAR2-1) GT ISCALAR4),
*     Problem: the quotient is more than ISCALAR4 from 1:
      PUT "Possible Error: The Full Load Hours calculated on (S,T) from the variation profile DH_VAR_T ";
      PUT "is not close to the Full Load Hours calculated on (SSS,TTT) for area   "IA.TL:OTLWCRA ", user group " DHUSER.TL:12 ": "  ISCALAR3:4:0" against " ISCALAR5:4:0;
      IF((ISCALAR3 GT ISCALAR5),
        PUT ": The heat demand variation DH_VAR_T,,S,T) appears mostly to be closer to the peak than expected from DH_VAR_T(,,SSS,TTT)." /;
      ELSE
        PUT ": The heat demand variation DH_VAR_T(,,S,T) appears mostly to be more far from the peak than expected from DH_VAR_T(,,SSS,TTT)." /;
      );
      ERRCOUNT2=ERRCOUNT2+1;
););););
IF((ISCALAR1 LT ERRCOUNT2),
PUT "   The above check on reasonable consistency between the FLHs calculated from the input variation profile over (SSS,TTT) (the whole year) and over (S,T) (the time segments selected):"/;
PUT "   For the calculation and check to make sense is must be assumed that DE_VAR_T and DH_VAR_T are given for a whole year, i.e., CARD(SSS)*CARD(TTT) = 8736 ('whole' year)."/;
PUT "   It is also assumed that the weights of the segments is in such full-year case the same for all (SSS,TTT), i.e., the corresponding IHOURSINST(SSS,TTT) are the same for all time segments."/;
PUT "   The above check on Full Load Hours FLH was made with a tolerance on the quotient of " ISCALAR4:5:3"." /;
PUT "   CARD(S)*CARD(T) is " (CARD(S)*CARD(T)):4:0 ", if this number is much smaller than " (CARD(SSS)*CARD(TTT)):4:0 " this may be the explanation, e.g. if the S and T selected do not contain DE_VAR_T or DH_VAR_T values that are representative for the whole year."/;
PUT "#"/;
);


* Check reasonable consistency between the Full Load Hours calculated from the input variation profile and the input FLH value
ISCALAR4=0.1; /* Serves as check value, the quotient should not be more than ISCALAR4 from 1 */
ISCALAR1=ERRCOUNT2;
* WTRRSFLH:
LOOP(IA, LOOP(IGHYRS$(SMAX(Y,GKFX(Y,IA,IGHYRS))
$ifi %BB2%==yes  OR GDATA(IGHYRS,'GDKVARIABL')
),
IF(((WTRRSFLH(IA) EQ 0) AND (IWTRRSSUM(IA) EQ 0)),
* No problem, agreement.
ELSE
  IF((((WTRRSFLH(IA) NE 0) AND (IWTRRSSUM(IA) EQ 0)) OR ((WTRRSFLH(IA) EQ 0) AND (IWTRRSSUM(IA) NE 0))),
    PUT "Possible Error: WTRRSFLH is "WTRRSFLH(IA) "  while IWTRRSSUM is "IWTRRSSUM(IA)" (i.e., no proper VAR_T profile)  for area "IA.TL:OTLWCRA /;
    ERRCOUNT2=ERRCOUNT2+1;
  ELSE
    ISCALAR2=(SUM(T,(IOF24*WEIGHT_T(T)/IWEIGHSUMT))*IWTRRSSUM(IA))/SMAX(S,WTRRSVAR_S(IA,S));
    IF((ABS((WTRRSFLH(IA)/ISCALAR2)-1) GT ISCALAR4),
*     Problem: the quotient is more than ISCALAR4 from 1:
      PUT "Possible Error: The Full Load Hours calculated on (S,T) from the variation profile given by WTRRSVAR_S ";
      PUT "is not close to the value given in WTRRSFLH for area "IA.TL:OTLWCRA ": "  (ISCALAR2):4:0" against " WTRRSFLH(IA):4:0 ;
      IF((ISCALAR2 GT (WTRRSFLH(IA))),
      /*  PUT ": The technology appears more attractive than expected from WTRRSFLH." /;
      ELSE
        PUT ": The technology appears less attractive than expected from WTRRSFLH." /;  */
        PUT ": The generation profile in the simulation appears mostly to be closer  to the (lower) peak than expected from WTRRSVAR_S(AAA,SSS,TTT)." /;
      ELSE
        PUT ": The generation profile in the simulation appears mostly to be further from the (higher) peak than expected from WTRRSVAR_S(AAA,SSS,TTT)." /;
      );
      ERRCOUNT2=ERRCOUNT2+1;
)))));
IF((ISCALAR1 LT ERRCOUNT2),
  PUT "   The above check on Full Load Hours FLH was made with a tolerance on the quotient of " ISCALAR4:5:3 /;
  PUT "   CARD(S)*CARD(T) is " (CARD(S)*CARD(T)):4:0 ", if this number is much smaller than " (CARD(SSS)*CARD(TTT)):4:0 " this may be the explanation, e.g. if the S and T selected do not contain VAR_T values that are representative for the whole year."/;
  PUT "#"/;
);

* WTRRRFLH:
ISCALAR1=ERRCOUNT2;
LOOP(IA, LOOP(IGHYRR$(SMAX(Y,GKFX(Y,IA,IGHYRR))
$ifi %BB2%==yes OR GDATA(IGHYRR,'GDKVARIABL')
),
IF(((WTRRRFLH(IA) EQ 0) AND (IWTRRRSUM(IA) EQ 0)),
ELSE
  IF((((WTRRRFLH(IA) NE 0) AND (IWTRRRSUM(IA) EQ 0)) OR ((WTRRRFLH(IA) EQ 0) AND (IWTRRRSUM(IA) NE 0))),
    PUT "Possible Error: WTRRRFLH is "WTRRRFLH(IA) "  while IWTRRRSUM is "IWTRRRSUM(IA)" (i.e., no proper VAR_T profile)  for area "IA.TL:OTLWCRA /;
    ERRCOUNT2=ERRCOUNT2+1;
  ELSE
    ISCALAR2=(SUM((S,T), IHOURSINST(S,T)*WTRRRVAR_T(IA,S,T)))/SMAX((S,T),WTRRRVAR_T(IA,S,T));
    IF((ABS((WTRRRFLH(IA)/ISCALAR2)-1) GT ISCALAR4),
      PUT "Possible Error: The Full Load Hours calculated on (S,T) from the variation profile given by WTRRRVAR_S ";
      PUT "is not close to the value given in WTRRRFLH for area "IA.TL:OTLWCRA ": "  (IWTRRRSUM(IA)/(SMAX((S,T),WTRRRVAR_T(IA,S,T)))):4:0 " against " WTRRRFLH(IA):4:0;
      IF((ISCALAR2 GT (WTRRRFLH(IA))),
       /* PUT ": The technology appears more attractive than expected from WTRRRFLH." /;
      ELSE
        PUT ": The technology appears less attractive than expected from WTRRRFLH." /; */
        PUT ": The generation profile in the simulation appears mostly to be closer  to the (lower) peak than expected from WTRRRVAR_T(AAA,SSS,TTT)." /;
      ELSE
        PUT ": The generation profile in the simulation appears mostly to be further from the (higher) peak than expected from WTRRRVAR_T(AAA,SSS,TTT)." /;
      );
      ERRCOUNT2=ERRCOUNT2+1;
)))));
IF((ISCALAR1 LT ERRCOUNT2),
  PUT "   The above check on Full Load Hours FLH was made with a tolerance on the quotient of " ISCALAR4:5:3 /;
  PUT "   CARD(S)*CARD(T) is " (CARD(S)*CARD(T)):4:0 ", if this number is much smaller than " (CARD(SSS)*CARD(TTT)):4:0 " this may be the explanation, e.g. if the S and T selected do not contain VAR_T values that are representative for the whole year."/;
  PUT "#"/;
);

* WNDFLH:
$ifi %WNDFLH_DOL%==AAA_GGG $goto LABEL_WNDFLH_ERROR
ISCALAR1=ERRCOUNT2;
**LOOP(IA, LOOP(IGWND$(SMAX(Y,GKFX(Y,IA,IGWND))  TODO TODO: possibly frevise, then use sag idea elsewhere (WTRRRVAR_T etc.) to avoid writing an AAA several times
LOOP(IA$(SUM((Y,IGWND), GKFX(Y,IA,IGWND))
$ifi %BB2%==yes OR ( (SUM(IGWND$GDATA(IGWND,'GDKVARIABL'),1)) AND (SUM(IGWND$AGKN(IA,IGWND),1)))
),
IF(((WNDFLH(IA) EQ 0) AND (IWND_SUMST(IA) EQ 0)),
ELSE
  IF((((WNDFLH(IA) NE 0) AND (IWND_SUMST(IA) EQ 0)) OR ((WNDFLH(IA) EQ 0) AND (IWND_SUMST(IA) NE 0))),
    PUT "Possible Error: WNDFLH is "WNDFLH(IA) "  while IWND_SUMST is "IWND_SUMST(IA)" (i.e., no proper VAR_T profile) for area "IA.TL:OTLWCRA /;
    ERRCOUNT2=ERRCOUNT2+1;
  ELSE
    ISCALAR2=(SUM((S,T), IHOURSINST(S,T)*WND_VAR_T(IA,S,T)))/(SMAX((S,T),WND_VAR_T(IA,S,T)));
    IF((ABS((WNDFLH(IA)/ISCALAR2)-1) GT ISCALAR4),
      PUT "Possible Error: The Full Load Hours calculated on (S,T) from the variation profile given by WND_VAR_T  ";
      PUT "is not close to the value given in WNDFLH   for area "IA.TL:OTLWCRA ": "  (IWND_SUMST(IA)/(SMAX((S,T),WND_VAR_T(IA,S,T)))):4:0 " against " WNDFLH(IA):4:0;
      IF((ISCALAR2 GT (WNDFLH(IA))),
        PUT ": The generation profile in the simulation appears mostly to be closer  to the (lower) peak than expected from WND_VAR_T(AAA,SSS,TTT)." /;
      ELSE
        PUT ": The generation profile in the simulation appears mostly to be further from the (higher) peak than expected from WND_VAR_T(AAA,SSS,TTT)." /;
      );
      ERRCOUNT2=ERRCOUNT2+1;
))));
IF((ISCALAR1 LT ERRCOUNT2),
  PUT "   The above check on Full Load Hours FLH was made with a tolerance on the quotient of " ISCALAR4:5:3 /;
  PUT "   CARD(S)*CARD(T) is " (CARD(S)*CARD(T)):4:0 ", if this number is much smaller than " (CARD(SSS)*CARD(TTT)):4:0 " this may be the explanation, e.g. if the S and T selected do not contain VAR_T values that are representative for the whole year."/;
  PUT "#"/;
);
$LABEL LABEL_WNDFLH_ERROR

* SOLEFLH:
$ifi %SOLEFLH_DOL%==AAA_GGG $goto LABEL_SOLEFLH_ERROR
ISCALAR1=ERRCOUNT2;
LOOP(IA, LOOP(IGSOLE$(SMAX(Y,GKFX(Y,IA,IGSOLE))
$ifi %BB2%==yes OR GDATA(IGSOLE,'GDKVARIABL')
),
IF(((SOLEFLH(IA) EQ 0) AND (ISOLESUMST(IA) EQ 0)),
ELSE
  IF((((SOLEFLH(IA) NE 0) AND (ISOLESUMST(IA) EQ 0)) OR ((SOLEFLH(IA) EQ 0) AND (ISOLESUMST(IA) NE 0))),
    PUT "Possible Error: SOLEFLH is "SOLEFLH(IA) "  while ISOLESUMST is "ISOLESUMST(IA)" (i.e., no proper VAR_T profile)  for area "IA.TL:OTLWCRA /;
    ERRCOUNT2=ERRCOUNT2+1;
  ELSE
    ISCALAR2=(SUM((S,T), IHOURSINST(S,T)*SOLE_VAR_T(IA,S,T)))/SMAX((S,T),SOLE_VAR_T(IA,S,T));
    IF((ABS((SOLEFLH(IA)/ISCALAR2)-1) GT ISCALAR4),
      PUT "Possible Error: The Full Load Hours calculated on (S,T) from the variation profile given by SOLEVAR_S  ";
      PUT "is not close to the value given in SOLEFLH  for area "IA.TL:OTLWCRA ": "  (ISOLESUMST(IA)/(SMAX((S,T),SOLE_VAR_T(IA,S,T)))):4:0 " against " SOLEFLH(IA):4:0;
      IF((ISCALAR2 GT (SOLEFLH(IA))),
       /* PUT ": The technology appears more attractive than expected from SOLEFLH." /;
      ELSE
        PUT ": The technology appears less attractive than expected from SOLEFLH." /;   */
        PUT ": The generation profile in the simulation appears mostly to be closer  to the (lower) peak than expected from SOLE_VAR_T(AAA,SSS,TTT)." /;
      ELSE
        PUT ": The generation profile in the simulation appears mostly to be further from the (higher) peak than expected from SOLE_VAR_T(AAA,SSS,TTT)." /;
      );
      ERRCOUNT2=ERRCOUNT2+1;
)))));
IF((ISCALAR1 LT ERRCOUNT2),
  PUT "   The above check on Full Load Hours FLH was made with a tolerance on the quotient of " ISCALAR4:5:3 /;
  PUT "   CARD(S)*CARD(T) is " (CARD(S)*CARD(T)):4:0 ", if this number is much smaller than " (CARD(SSS)*CARD(TTT)):4:0 " this may be the explanation, e.g. if the S and T selected do not contain VAR_T values that are representative for the whole year."/;
  PUT "#"/;
);
$LABEL LABEL_SOLEFLH_ERROR

* SOLHFLH:
$ifi %SOLHFLH_DOL%==AAA_GGG $goto LABEL_SOLHFLH_ERROR
ISCALAR1=ERRCOUNT2;
LOOP(IA, LOOP(IGSOLH$(SMAX(Y,GKFX(Y,IA,IGSOLH))
$ifi %BB2%==yes OR GDATA(IGSOLH,'GDKVARIABL')
),
IF(((SOLHFLH(IA) EQ 0) AND (ISOLHSUMST(IA) EQ 0)),
ELSE
  IF((((SOLHFLH(IA) NE 0) AND (ISOLHSUMST(IA) EQ 0)) OR ((SOLHFLH(IA) EQ 0) AND (ISOLHSUMST(IA) NE 0))),
    PUT "Possible Error: SOLHFLH is "SOLHFLH(IA) "  while ISOLHSUMST is "ISOLHSUMST(IA)" (i.e., no proper VAR_T profile)  for area "IA.TL:OTLWCRA /;
    ERRCOUNT2=ERRCOUNT2+1;
  ELSE
    ISCALAR2=(SUM((S,T), IHOURSINST(S,T)*SOLH_VAR_T(IA,S,T)))/SMAX((S,T),SOLH_VAR_T(IA,S,T));
    IF((ABS((SOLHFLH(IA)/ISCALAR2)-1) GT ISCALAR4),
      PUT "Possible Error: The Full Load Hours calculated on (S,T) from the variation profile given by SOLHVAR_S ";
      PUT "is not close to the value given in SOLHFLH for area "IA.TL:OTLWCRA ": "  (ISOLHSUMST(IA)/(SMAX((S,T),SOLH_VAR_T(IA,S,T)))):4:0 " against " SOLHFLH(IA):4:0;
      IF((ISCALAR2 GT (SOLHFLH(IA))),
      /*  PUT ": The technology appears more attractive than expected from SOLHFLH." /;
      ELSE
        PUT ": The technology appears less attractive than expected from SOLHFLH." /;  */
        PUT ": The generation profile in the simulation appears mostly to be closer  to the (lower) peak than expected from SOLH_VAR_T(AAA,SSS,TTT)." /;
      ELSE
        PUT ": The generation profile in the simulation appears mostly to be further from the (higher) peak than expected from SOLH_VAR_T(AAA,SSS,TTT)." /;
      );
      ERRCOUNT2=ERRCOUNT2+1;
)))));
IF((ISCALAR1 LT ERRCOUNT2),
  PUT "   The above check on Full Load Hours FLH was made with a tolerance on the quotient of " ISCALAR4:5:3 /;
  PUT "   CARD(S)*CARD(T) is " (CARD(S)*CARD(T)):4:0 ", if this number is much smaller than " (CARD(SSS)*CARD(TTT)):4:0 " this may be the explanation, e.g. if the S and T selected do not contain VAR_T values that are representative for the whole year."/;
  PUT "#"/;
);
$LABEL LABEL_SOLHFLH_ERROR

* WAVEFLH:
$ifi %GWAVE_DOL%==AAA_GGG $goto LABEL_GWAVE_ERROR

ISCALAR1=ERRCOUNT2;
LOOP(IA, LOOP(IGWAVE$(SMAX(Y,GKFX(Y,IA,IGWAVE))
$ifi %BB2%==yes OR GDATA(IGWAVE,'GDKVARIABL')
),
IF(((WAVEFLH(IA) EQ 0) AND (IWAVESUMST(IA) EQ 0)),
ELSE
  IF((((WAVEFLH(IA) NE 0) AND (IWAVESUMST(IA) EQ 0)) OR ((WAVEFLH(IA) EQ 0) AND (IWAVESUMST(IA) NE 0))),
    PUT "Possible Error: WAVEFLH is "WAVEFLH(IA) "  while IWAVESUMST is "IWAVESUMST(IA)" (i.e., no proper VAR_T profile)  for area "IA.TL:OTLWCRA /;
    ERRCOUNT2=ERRCOUNT2+1;
  ELSE
    ISCALAR2=(SUM((S,T), IHOURSINST(S,T)*WAVE_VAR_T(IA,S,T)))/SMAX((S,T),WAVE_VAR_T(IA,S,T));
    IF((ABS((WAVEFLH(IA)/ISCALAR2)-1) GT ISCALAR4),
      PUT "Possible Error: The Full Load Hours calculated on (S,T) from the variation profile given by WAVEVAR_S ";
      PUT "is not close to the value given in WAVEFLH for area "IA.TL:OTLWCRA ": "  (IWAVESUMST(IA)/(SMAX((S,T),WAVE_VAR_T(IA,S,T)))):4:0 " against " WAVEFLH(IA):4:0;
      IF((ISCALAR2 GT (WAVEFLH(IA))),
      /*  PUT ": The technology appears more attractive than expected from WAVEFLH." /;
      ELSE
        PUT ": The technology appears less attractive than expected from WAVEFLH." /;      */
        PUT ": The generation profile in the simulation appears mostly to be closer  to the (lower) peak than expected from WAVE_VAR_T(AAA,SSS,TTT)." /;
      ELSE
        PUT ": The generation profile in the simulation appears mostly to be further from the (higher) peak than expected from WAVE_VAR_T(AAA,SSS,TTT)." /;
      );
      ERRCOUNT2=ERRCOUNT2+1;
)))));
IF((ISCALAR1 LT ERRCOUNT2),
  PUT "   The above check on Full Load Hours FLH was made with a tolerance on the quotient of " ISCALAR4:5:3 /;
  PUT "   CARD(S)*CARD(T) is " (CARD(S)*CARD(T)):4:0 ", if this number is much smaller than " (CARD(SSS)*CARD(TTT)):4:0 " this may be the explanation, e.g. if the S and T selected do not contain VAR_T values that are representative for the whole year."/;
  PUT "#"/;
);
$LABEL LABEL_GWAVE_ERROR

$ontext

*---TABLE WATR_VAR_S------------------------------------------------------------
* The variation profile specified in TABLE WATR_VAR_S must contain
* nonnegative values and the sum over the time segments (S) must be positive
* if hydro power is an option in the region:
LOOP(R,
IF( (MAX_POT_R('WATER',R) GE 0 ),
IF( (SUM(S,WATR_VAR_S(R,S)) EQ 0),
PUT " The table WATR_VAR_S contains no positive elements for (S) in region " R.TL:32/;
ERRCOUNT2=ERRCOUNT2+1; );
););
*---END TABLE WATR_VAR_S--------------------------------------------------------


*---TABLE PWND_VAR_T------------------------------------------------------------
* The variation profile specified in TABLE PWND_VAR_T must contain
* nonnegative values and the sum over the time segments (S,T) must be positive:
LOOP(FPOTSETR,
IF( (FPOTR('WIND',FPOTSETR) GE 0 ),
IF( (SUM((S,T),PWND_VAR_T(FPOTSETR,S,T)) EQ 0),
PUT " The table PWND_VAR_T contains no positive elements for";
PUT " (S,T) in region " FPOTSETR.TL:32/;
ERRCOUNT2=ERRCOUNT2+1; );
););
*---TABLE PWND_VAR_T------------------------------------------------------------


*---TABLE PSOL_VAR_T------------------------------------------------------------
* 20000900: uheldigt,at 'SUN' optraeder ....
* The variation profile specified in TABLE PSOL_VAR_T must contain
* nonnegative values and the sum over the time segments (S,T) must be positive:
LOOP(R,
IF( (MAX_POT_R('SUN',R) GE 0 ),
IF( (SUM((S,T),PSOL_VAR_T(R,S,T)) EQ 0),
PUT " The table PSOL_VAR_T contains no positive elements for (S,T) in region " R.TL:32/;
ERRCOUNT2=ERRCOUNT2+1; );
););
*---TABLE PSOL_VAR_T------------------------------------------------------------

$offtext


*---TABLE X3_VAR_T AND TABLE X3FX-----------------------------------------------
* The variation profile specified in TABLE X3_VAR_T must contain
* values such that the sum over the time segments (S,T) must be positive
* if a net import or export is specified by X3FX:
ISCALAR1=ERRCOUNT2;
LOOP((Y,IR),
IF( (X3FX(Y,IR) NE 0),
IF( (SUM(S, (IOF365*WEIGHT_S(S)/IWEIGHSUMS)*SUM(T,(IOF24*WEIGHT_T(T)/IWEIGHSUMT)*X3FX_VAR_T(IR,S,T))  ) EQ 0),
PUT "The tables X3_VAR_T and X3FX contain information ";
PUT " such that a net import or export is not possible for region " IR.TL:32/;
ERRCOUNT2=ERRCOUNT2+1; );
););
IF((ISCALAR1 LT ERRCOUNT2),PUT "#"/;);
*---END TABLE X3_VAR_T AND TABLE X3FX-------------------------------------------

*---END OF DATA IN THE FILE var.inc---------------------------------------------
*-------------------------------------------------------------------------------




*---DEFP_BASE AND DHFP_BASE: ---------------------------------------------------
$ifi not %dflex%==yes $goto dflexend
ISCALAR1=ERRCOUNT2;
*IF((CARD(DEF) GT 0),  20150519(hr) replaced by next
IF(((CARD(DEF_D1)+CARD(DEF_U1)+CARD(DEF_D2)+CARD(DEF_U2)+CARD(DEF_D3)+CARD(DEF_U3)) GT 0),
LOOP(IR,
IF ((DEFP_BASE(IR) LE 0),
PUT "Error in table DEFP_BASE: DEFP_BASE is not positive everywhere." /;
ERRCOUNT2=ERRCOUNT2+1;
);););
*IF((CARD(DHF) GT 0),  20150519(hr) replaced by next
IF(((CARD(DHF_D1)+CARD(DHF_U1)+CARD(DHF_D2)+CARD(DHF_U2)+CARD(DHF_D3)+CARD(DHF_U3)) GT 0),
LOOP (IA,
IF ((DHFP_BASE(IA) LE 0),
PUT "Error in table DHFP_BASE: DHFP_BASE is not positive everywhere." /;
ERRCOUNT2=ERRCOUNT2+1;
);););


*---SET DEF_DSTEPS AND DEF_USTEPS-----------------------------------------------

*---TABLE DEF_ELAST AND DHF_ELAST-----------------------------------------------
* Electricity:
IF((CARD(DEF_D1)+CARD(DEF_U1) GT 0),
* If demand is elastic,
* the price levels of the steps must be positive:
LOOP((IR,S,T), LOOP(DEF$(DEF_D1(DEF) or DEF_U1(DEF)),
IF ((IDEFP_T(IR,S,T,DEF) LE 0),
PUT "Error: All IDEFP_T should be positive but are not, region "IR.tl" Time " s.TL  t.TL" step " DEF.TL "  value " IDEFP_T(IR,S,T,DEF) /;
ERRCOUNT2=ERRCOUNT2+1;
););););

IF((CARD(DEF_D2)+CARD(DEF_U2) GT 0),
* If demand is elastic,
* the user's intention probably is that the price levels of the steps should be positive;
* however, it is possible to calculate also with zero or negative values:
LOOP((IR,S,T), LOOP(DEF$(DEF_D2(DEF) or DEF_U2(DEF)),
IF ((IDEFP_T(IR,S,T,DEF) LE 0),
PUT "Possible error: Some IDEFP_T are negative - is this intentional?" /;
ERRCOUNT2=ERRCOUNT2+1;
););););

* Heat:
IF((CARD(DHF_D1)+CARD(DHF_U1) GT 0),
* If demand is elastic,
* The price levels of the steps must be positive, except the last one:
LOOP((IA,S,T), LOOP(DHF$(DHF_D1(DHF) or DHF_U1(DHF)),
IF ((IDHFP_T(IA,S,T,DHF) LE 0),
PUT "Error: All IDHFP_T should be positive but are not, area " IA.tl " Time " s.TL t.TL " step " DHF.TL /;
ERRCOUNT2=ERRCOUNT2+1;
););););

* Electricity: The sequence of values DEF_QUANT should be increasing:
LOOP((IR,S,T,DEF_D1)
  $((1 LT ORD(DEF_D1)) AND (ORD(DEF_D1) LT CARD(DEF_D1))),
IF(  (DEF_STEPS(IR,S,T,'DF_QUANT',DEF_D1+1)
     -DEF_STEPS(IR,S,T,'DF_QUANT',DEF_D1) LT 0),
PUT "Error in table DEF_STEPS:" /;
PUT "   The sequence of values DEF_QUANT is not increasing everywhere." /;
ERRCOUNT2=ERRCOUNT2+1;
););
LOOP((IR,S,T,DEF_D1)
  $(ORD(DEF_D1) EQ CARD(DEF_D1)),
IF(  (1- DEF_STEPS(IR,S,T,'DF_QUANT',DEF_D1) LT 0),
PUT "Error in table DEF_STEPS:" /;
PUT "   The sequence of values DEF_QUANT is not increasing everywhere." /;
ERRCOUNT2=ERRCOUNT2+1;
););
LOOP((IR,S,T,DEF_U1)
  $((ORD(DEF_U1) EQ 1)),
IF(  (DEF_STEPS(IR,S,T,'DF_QUANT',DEF_U1)-1 LT 0),
PUT "Error in table DEF_STEPS:" /;
PUT "   The sequence of values DEF_QUANT is not increasing everywhere." /;
ERRCOUNT2=ERRCOUNT2+1;
););
LOOP((IR,S,T,DEF_U1)
  $((1 LT ORD(DEF_U1)) AND (ORD(DEF_U1) LT CARD(DEF_U1))),
IF((DEF_STEPS(IR,S,T,'DF_QUANT',DEF_U1)
  -DEF_STEPS(IR,S,T,'DF_QUANT',DEF_U1-1) LT 0),
PUT "Error in table DEF_STEPS:" /;
PUT "   The sequence of values DEF_QUANT is not increasing everywhere." /;
ERRCOUNT2=ERRCOUNT2+1;
););

* Heat: The sequence of values DHF_QUANT should be increasing:
LOOP((IA,S,T,DHF_D1)$((1 LT ORD(DHF_D1)) AND (ORD(DHF_D1) LT CARD(DHF_D1))),
IF(  (DHF_STEPS(IA,S,T,'DF_QUANT',DHF_D1+1)
     -DHF_STEPS(IA,S,T,'DF_QUANT',DHF_D1) LT 0),
PUT "Error in table DHF_STEPS:" /;
PUT "   The sequence of values DHF_QUANT is not increasing everywhere." /;
ERRCOUNT2=ERRCOUNT2+1;
););
LOOP((IA,S,T,DHF_D1)$(ORD(DHF_D1) EQ CARD(DHF_D1)),
IF(  (1- DHF_STEPS(IA,S,T,'DF_QUANT',DHF_D1) LT 0),
PUT "Error in table DHF_STEPS:" /;
PUT "   The sequence of values DHF_QUANT is not increasing everywhere." /;
ERRCOUNT2=ERRCOUNT2+1;
););
LOOP((IA,S,T,DHF_U1)
  $((ORD(DHF_U1) EQ 1)),
IF(  (DHF_STEPS(IA,S,T,'DF_QUANT',DHF_U1)-1 LT 0),
PUT "Error in table DHF_STEPS:" /;
PUT "   The sequence of values DHF_QUANT is not increasing everywhere." /;
ERRCOUNT2=ERRCOUNT2+1;
););
LOOP((IA,S,T,DHF_U1)$((1 LT ORD(DHF_U1)) AND (ORD(DHF_U1) LT CARD(DHF_U1))),
IF((DHF_STEPS(IA,S,T,'DF_QUANT',DHF_U1)
  -DHF_STEPS(IA,S,T,'DF_QUANT',DHF_U1-1) LT 0),
PUT "Error in table DHF_STEPS:" /;
PUT "   The sequence of values DHF_QUANT is not increasing everywhere." /;
ERRCOUNT2=ERRCOUNT2+1;
););

IF((CARD(DHF_U2) + CARD(DHF_D2) + CARD(DHF_U3) + CARD(DHF_D3)GT 0),
PUT "Error in relation to  DHF_STEPS:" /;
PUT "   Use of steps in formats 2 and 3, DHF_U2, DHF_D2, DHF_U3, DHF_D3, have not been fully implemented. " /;
PUT "       Do it youself, or try contact through www.Balmorel.com."/;
ERRCOUNT2=ERRCOUNT2+1;
);
IF((ISCALAR1 LT ERRCOUNT2),PUT "#"/;);


*---SET DEF_D1 AND DEF_U1-------------------------------------------------------
$label dflexend
*---END TABLE DEF_STEPS AND DEF_STEPS-------------------------------------------






*-------------------------------------------------------------------------------
*--- DATA IN THE FILE tech.inc:-------------------------------------------------

*---TABLE GDATA-----------------------------------------------------------------

/*  Hans: this is not valid with acronyms
* GDTYPE should be between 1 and 11:
LOOP(G,
IF((GDATA(G,'GDTYPE') LT 1) OR (11 LT GDATA(G,'GDTYPE')),
PUT "Error in table GDATA:" /;
PUT "   The GDTYPE-values for technology " G.TL
    " is  not between 1 and 11."/;
ERRCOUNT2=ERRCOUNT2+1;
));
*/

/*   Hans 20150519 ud
LOOP(G,
IF((GDATA(G,'GDTYPE') EQ GSOLH),
PUT "Error in table GDATA:" /;
PUT "   The GDTYPE-value for technology " G.TL:32  " is GHSOL, however, this technology type is not yet implemented."/;
ERRCOUNT2=ERRCOUNT2+1;
));
*/
/*   Hans: this is not valid with acronyms
LOOP(G,
IF((GDATA(G,'GDTYPE') GE 12),
PUT "Error in table GDATA:" /;
PUT "   The GDTYPE-value for technology " G.TL:32  " is 12 or greater, however, this is illegal. ACRONYMS should be used. "/;
ERRCOUNT2=ERRCOUNT2+1;
));
*/



* Check if acronyms have been entered for each element in FFF.
* The acronym text string should equal the text string of the corresponding element in FFF.
* The check is not complete, cf. the error messages.
ISCALAR1=ERRCOUNT2;
ISCALAR1 = 0;
LOOP(FFF,
  ISCALAR2 = 0;
  LOOP(GGG$(ISCALAR2 EQ 0),
    IF((FDATA(FFF,'FDACRONYM') EQ GDATA(GGG,'GDFUEL')), ISCALAR2 = 1;  ISCALAR1 = ISCALAR1 + 1;);
  );
  IF((ISCALAR2 EQ 0), PUT "                Found no GGG using fuel "FFF.TL:15 " as specified in GDATA(GGG,'FDACRONYM')"/; );
);
ISCALAR3 = CARD(FFF);
IF((CARD(FFF) EQ ISCALAR1),
*  put "All elements in fuel set FFF have a corresponding acronym,"/; No need to do
ELSE
  PUT "Possible Error: Not all elements in fuel set FFF are used in a GGG - OR - some element in fuel set FFF does not have a corresponding acronym."/;
  PUT "                Acronyms should be entered in data file FFF.inc, after the final '/;', and must be made as an exact copy of the elements in the set FFF, preceded by the keyword ACRONYM and terminated by ';'." / /;
);
IF((ISCALAR1 LT ERRCOUNT2),PUT "#"/;);





* Ranges for fuel efficiencies are technology specific.
* However, all fuel efficiencies are positive:
ISCALAR1=ERRCOUNT2;
LOOP(G,
IF((GDATA(G,'GDFE') LT 0.1),
PUT "Error in table GDATA:" ;
PUT "   The fuel efficiency for technology " G.TL:32
PUT " is very small (" GDATA(G,'GDFE'):10:5 ")." /;
ERRCOUNT2=ERRCOUNT2+1;
));
IF((ISCALAR1 LT ERRCOUNT2),PUT "#"/;);

* Ranges for fuel efficiencies are technology specific.
* Heatpumps: a reasonable range is expected to be 0.8 to 5:
ISCALAR1=ERRCOUNT2;
LOOP(IGETOH,
IF( (GDATA(IGETOH,'GDFE') LT 0.8) OR (5 LT GDATA(IGETOH,'GDFE')),
PUT "Possible error in table GDATA:" /;
PUT "   The fuel efficiency for technology " IGETOH.TL:32
PUT " is very small or very large (" GDATA(IGETOH,'GDFE'):10:5 ")." /;
ERRCOUNT2=ERRCOUNT2+1;
));
IF((ISCALAR1 LT ERRCOUNT2),PUT "#"/;);

* Total fuel efficiency on extraction units should not exceed 100% in back pressure mode
ISCALAR1=ERRCOUNT2;
LOOP(IGEXT,
IF((1 LT (GDATA(IGEXT,'GDFE')*((GDATA(IGEXT,'GDCB')+1)/(GDATA(IGEXT,'GDCB')+GDATA(IGEXT,'GDCV'))))),
PUT "Possible error in table GDATA:" ;
PUT "   The fuel efficiency for technology " IGEXT.TL:32 " type GEXT "
PUT " exceeds 100% in back pressure mode (value: "
   (GDATA(IGEXT,'GDFE')*((GDATA(IGEXT,'GDCB')+1)/(GDATA(IGEXT,'GDCB')+GDATA(IGEXT,'GDCV')))):10:5 ")." /;
ERRCOUNT2=ERRCOUNT2+1; );
);
IF((ISCALAR1 LT ERRCOUNT2),PUT "#"/;);

* GDCB-values should be nonnegative for IGEXT:
ISCALAR1=ERRCOUNT2;
LOOP(IGEXT,
IF( ((GDATA(IGEXT,'GDCB') LT 0)),
PUT "Error in table GDATA:" ;
PUT "   The GDCB-values for technology " IGEXT.TL:4 " is negative."  /;
ERRCOUNT2=ERRCOUNT2+1;
));
IF((ISCALAR1 LT ERRCOUNT2),PUT "#"/;);


* GDSTOHLOAD-values should be positive for heat storages:
ISCALAR1=ERRCOUNT2;
LOOP(IGHSTO,
IF( ((GDATA(IGHSTO,'GDSTOHLOAD') LE 0)),
PUT "Error in table GDATA:" ;
PUT "   The GDSTOHLOAD-values for technology " IGHSTO.TL:32 " is not positive ("GDATA(IGHSTO,'GDSTOHLOAD'):10:5")."  /;
ERRCOUNT2=ERRCOUNT2+1;
));
IF((ISCALAR1 LT ERRCOUNT2),PUT "#"/;);

* GDSTOHUNLD-values should be positive for heat storages:
ISCALAR1=ERRCOUNT2;
LOOP(IGHSTO,
IF( ((GDATA(IGHSTO,'GDSTOHUNLD') LE 0)),
PUT "Error in table GDATA:" ;
PUT "   The GDSTOHUNLD-values for technology " IGHSTO.TL:32 " is not positive ("GDATA(IGHSTO,'GDSTOHUNLD'):10:5")."  /;
ERRCOUNT2=ERRCOUNT2+1;
));
IF((ISCALAR1 LT ERRCOUNT2),PUT "#"/;);

* GDSTOHLOAD-values should be positive for electricity storages:
ISCALAR1=ERRCOUNT2;
LOOP(IGESTO,
IF( ((GDATA(IGESTO,'GDSTOHLOAD') LE 0)),
PUT "Error in table GDATA:" ;
PUT "   The GDSTOHLOAD-values for technology " IGESTO.TL:32 " is not positive ("GDATA(IGESTO,'GDSTOHLOAD'):10:5")."  /;
ERRCOUNT2=ERRCOUNT2+1;
));
IF((ISCALAR1 LT ERRCOUNT2),PUT "#"/;);

* GDSTOHUNLD-values should be positive for electricity storages:
ISCALAR1=ERRCOUNT2;
LOOP(IGESTO,
IF( ((GDATA(IGESTO,'GDSTOHUNLD') LE 0)),
PUT "Error in table GDATA:" ;
PUT "   The GDSTOHUNLD-values for technology " IGESTO.TL:32 " is not positive ("GDATA(IGESTO,'GDSTOHUNLD'):10:5")."  /;
ERRCOUNT2=ERRCOUNT2+1;
));
IF((ISCALAR1 LT ERRCOUNT2),PUT "#"/;);

* GDLIFETIME should be a positive integer
ISCALAR5 = 3; !! Maximum number of error messages
* Is there a value:
ISCALAR1=ERRCOUNT2;
LOOP(G$((NOT GDATA(G,'GDLIFETIME')) AND (ERRCOUNT2 LT (ISCALAR1+ISCALAR5))),
PUT "Error in table GDATA:" ;
PUT "   The GDLIFETIME value for technology "   G.TL:32 " must be a positive integer - it has no value."   /;
ERRCOUNT2=ERRCOUNT2+1;
);
IF((ISCALAR1 LT ERRCOUNT2),PUT "#"/;);
* Is it positive and integer:
ISCALAR1=ERRCOUNT2;
LOOP(G$((GDATA(G,'GDLIFETIME')) AND (ERRCOUNT2 LT (ISCALAR1+ISCALAR5))),
IF(((MOD(GDATA(G,'GDLIFETIME'),1) NE 0) OR (GDATA(G,'GDLIFETIME') LT 0)),
PUT "Error in table GDATA:" ;
PUT "   The GDLIFETIME value for technology "   G.TL:32 " must be a positive integer, value is " GDATA(G,'GDLIFETIME') "."   /;
ERRCOUNT2=ERRCOUNT2+1;
););

IF((ISCALAR1 LT ERRCOUNT2),PUT "#"/;);



/*
* GDCB-values should be positive for electricity storages:
LOOP(IGESTO,
IF( ((GDATA(IGESTO,'GDCB') LE 0)),
PUT "Error in table GDATA:" ;
PUT "   The GDCB-values for electricity storage " IGESTO.TL:32 " type GESTO" " is not positive ("GDATA(IGESTO,'GDCB'):10:5"). (Remember you may use INF.)";
IF((SUM(IA$IAGK(IA,IGESTO), 1)), PUT "    - The technology has installed capacity in a simulation year ";); !! (20150519(hr))
PUT /;
ERRCOUNT2=ERRCOUNT2+1;
));
*/


/*  Hans: this is not valid with acronyms
* GDFUEL should be between 1 and CARD(FFF):
* ... but, of course, not necessarily ... If you deliberately
* chose numbers outside the indicated range, just change the check,
* or comment it out.
LOOP(G,
IF((GDATA(G,'GDFUEL') LT 0) OR (CARD(FFF) LT GDATA(G,'GDFUEL')),
PUT "Error in table GDATA:" ;
PUT "   The GDFUEL-values for technology " G.TL:32
    " is  not between 0 and " CARD(FFF):2"."/;
ERRCOUNT2=ERRCOUNT2+1;
));
*/
*------



* The value in GDKVARIABL should be 0 or 1:
ISCALAR1=ERRCOUNT2;
LOOP(G,
IF (((GDATA(G,'GDKVARIABL') NE 0) AND (GDATA(G,'GDKVARIABL') NE 1)),
PUT "Error in table GDATA:" ;
PUT "   GDKVARIABL should be 0 or 1 but is not so for technology " G.TL:32 /;
ERRCOUNT2=ERRCOUNT2+1;
); );
IF((ISCALAR1 LT ERRCOUNT2),PUT "#"/;);

/* Hans 12345: commented out, but have not checked that the code (e.g. in QHYRS) works:
* The value in GDKVARIABL should (presently) be 0 for IGHYRS:
ISCALAR1=ERRCOUNT2;
LOOP(IGHYRS,
IF (((GDATA(IGHYRS,'GDKVARIABL') NE 0)),
PUT "Error in table GDATA:" ;
PUT "   GDKVARIABL should (presently) be 0 for long term electricity storages, but is not so for technology " IGHYRS.TL:32 /;
ERRCOUNT2=ERRCOUNT2+1;
); );
IF((ISCALAR1 LT ERRCOUNT2),PUT "#"/;);
*/


*---END TABLE GDATA-------------------------------------------------------------

*--- END OF DATA IN THE FILE tech.inc ------------------------------------------
*-------------------------------------------------------------------------------


/*
*-------------------------------------------------------------------------------
*--- DATA IN THE FILE FUELP_Y.INC:----------------------------------------------

* Some of the fuels shold have a positive price:
* Observe that this check is dependent on the specific value used for FDNB
* and therefore heavily user dependent.
LOOP((Y,IA,FFF)$(
   (FDATA(FFF,"FDNB") EQ 1) OR
   (FDATA(FFF,"FDNB") EQ 1) OR   just examples
   (FDATA(FFF,"FDNB") EQ 1) OR
   (FDATA(FFF,"FDNB") EQ 1)
   ),
IF((FUELPRICE(Y,IA,FFF) EQ 0),
PUT "Error in table FUELPRICE:" /;
PUT "   FUELPRICE should be positive but is not so for fuel " FFF.TL:32 /;
ERRCOUNT2=ERRCOUNT2+1;
); );

*--- END OF DATA IN THE FILE FUELP_Y.INC:---------------------------------------
*-------------------------------------------------------------------------------
*/


*-------------------------------------------------------------------------------
*--- DATA IN THE FILE gkfx.inc:-------------------------------------------------

* Probably it is an error if there for some of the countries in C
* is positive capacity for some technologies i GGG but not in G:
ISCALAR1=ERRCOUNT2;
ERRSETGGG(GGG)=YES;
ERRSETGGG(G)=NO;
*DISPLAY ERRSETGGG;
LOOP(Y,
LOOP(IA,
LOOP(ERRSETGGG,
IF((GKFX(Y,IA,ERRSETGGG) GT 0),
PUT "Error (table GKFX, set G and set GGG):" /;
PUT "   The technology " ERRSETGGG.TL:32 " has the positive capacity " GKFX(Y,IA,ERRSETGGG):10:0 " specified in GKFX "/;
PUT "   for area " IA.TL:32 " in the year " Y.TL:32 /;
PUT "   However, this technology is not included in the set G." /;
ERRCOUNT2=ERRCOUNT2+1;
 )
)));
IF((ISCALAR1 LT ERRCOUNT2),PUT "#"/;);

* There should only be one heat storage technology in any area:
ISCALAR1=ERRCOUNT2;
LOOP((Y,IA),
ERRSCALAR1=0;
LOOP(IGHSTO,
IF((GKFX(Y,IA,IGHSTO) GT 0),
ERRSCALAR1=ERRSCALAR1+1);
);
IF((ERRSCALAR1 GT 1),
PUT "Error in table GKFX:" /;
PUT "   There should be at most one heat storage technology in any area, " /;
PUT "   in area "IA.TL:32 " there are " errscalar1:4:0 /;
ERRCOUNT2=ERRCOUNT2+1;
));
IF((ISCALAR1 LT ERRCOUNT2),PUT "#"/;);


*--- END OF DATA IN THE FILE gkfx.incr:-----------------------------------------
*-------------------------------------------------------------------------------




*-------------------------------------------------------------------------------
*--- DATA IN THE FILE x3.inc:---------------------------------------------------

$ifi not %X3V%==yes $goto X3V_error2_label1
*---TABLE X3VPIM AND TABLE X3VPEX-----------------------------------------------
$ontext
* The places in set X3VPLACE0 should not be in a simulated region,
* i.e. the set RX3VSUBSTI(IR,X3VPLACE) should be empty:
LOOP(RX3VSUBSTI(IR,X3VPLACE),
PUT "Price dependent electricity echange with places outside the simulated geographical scope"/;
PUT "   is specified between region " IR.TL:32 " and the element " X3VPLACE.TL:32 " in the set X3VPLACE ." /;
PUT "   Maybe you would like to revise the set RX3VSUBSTI."/;
ERRCOUNT2=ERRCOUNT2+1;
);
$offtext


* The prices for price dependent import from third places should be weakly decreasing:
ISCALAR1=ERRCOUNT2;
LOOP((Y,IR,X3VPLACE,S,T)$(X3VX(IR,X3VPLACE)),
*LOOP((X3VPLACE)$(X3VX(IR,X3VPLACE)),
LOOP(X3VSTEP0$((X3VSTEP(X3VSTEP0)) AND (ORD(X3VSTEP0) LE (CARD(X3VSTEP0)-1))),
IF((X3VPIM(Y,IR,X3VPLACE,X3VSTEP0,S,T) LT X3VPIM(Y,IR,X3VPLACE,X3VSTEP0+1,S,T)),
PUT "The prices for price dependent import from third places should be weakly increasing"/;
PUT "   this is not so for " Y.TL:32 IR.TL:32 X3VPLACE.TL:32 S.TL:32 T.TL:32 X3VSTEP0.TL:32 " to next step. Prices: "
        X3VPIM(Y,IR,X3VPLACE,X3VSTEP0,S,T) X3VPIM(Y,IR,X3VPLACE,X3VSTEP0+1,S,T) /;
ERRCOUNT2=ERRCOUNT2+1;
)));
IF((ISCALAR1 LT ERRCOUNT2),PUT "#"/;);

ISCALAR1=ERRCOUNT2;
* The prices for price dependent export to third places should be weakly increasing:
LOOP((Y,IR,X3VPLACE,S,T)$(X3VX(IR,X3VPLACE)),
*LOOP((X3VPLACE)$(X3VX(IR,X3VPLACE)),
LOOP(X3VSTEP0$((X3VSTEP(X3VSTEP0)) AND (ORD(X3VSTEP0) LE (CARD(X3VSTEP0)-1))),
IF((X3VPEX(Y,IR,X3VPLACE,X3VSTEP0,S,T) GT X3VPEX(Y,IR,X3VPLACE,X3VSTEP0+1,S,T)),
PUT "The prices for price dependent export from third places should be weakly decreasing"/;
PUT "   this is not so for " Y.TL:32 IR.TL:32 X3VPLACE.TL:32 S.TL:32 T.TL:32 X3VSTEP0.TL:32 " to next step. Prices: "
        X3VPEX(Y,IR,X3VPLACE,X3VSTEP0,S,T) X3VPEX(Y,IR,X3VPLACE,X3VSTEP0+1,S,T) /;
ERRCOUNT2=ERRCOUNT2+1;
)));
IF((ISCALAR1 LT ERRCOUNT2),PUT "#"/;);

* The prices for price dependent export to third places should be greater than or equal to
* the prices for price dependent import from third places:
ISCALAR1=ERRCOUNT2;
LOOP((Y,IR,X3VPLACE,S,T)$X3VX(IR,X3VPLACE),
*LOOP((X3VPLACE)$(IST(S,T) and X3VX(IR,X3VPLACE)),
LOOP(X3VSTEP,
IF((X3VPEX(Y,IR,X3VPLACE,X3VSTEP,S,T) LT X3VPIM(Y,IR,X3VPLACE,X3VSTEP,S,T)),
PUT "The prices for price dependent export from third places should be greater than or equal to the prices for price dependent import from third places"/;
PUT "   this is not so for " Y.TL:32 IR.TL:32 X3VPLACE.TL:32 S.TL:32 T.TL:32 ", import and exprot prices are " X3VPIM(Y,IR,X3VPLACE,X3VSTEP,S,T)   X3VPEX(Y,IR,X3VPLACE,X3VSTEP,S,T) /;
ERRCOUNT2=ERRCOUNT2+1;
)));
IF((ISCALAR1 LT ERRCOUNT2),PUT "#"/;);

*---END OF TABLE X3VPIM AND TABLE X3VPEX----------------------------------------
$label X3V_error2_label1


*-------------------------------------------------------------------------------
* Combination of investment possibilities and other data.

$ifi not %BB2%==yes $goto IAGKN_error3_label1

* If wind power investment is possible then IWND_SUMST must be positive:
ISCALAR1=ERRCOUNT2;
LOOP((IA,IGWND)$IAGKN(IA,IGWND),
  IF((IWND_SUMST(IA) LE 0),
  PUT "Error: Investment in wind power is posible in area " IA.tl:OTLW " for technlogy " IGWND.tl:OTLW ", however, the wind profile is not initialised (IWND_SUMST is zero)."/;
  ERRCOUNT2=ERRCOUNT2+1;);
);
IF((ISCALAR1 LT ERRCOUNT2),PUT "#"/;);

* If solarE power investment is possible then ISOLESUMST must be positive:
ISCALAR1=ERRCOUNT2;
LOOP((IA,IGSOLE)$IAGKN(IA,IGSOLE),
  IF((ISOLESUMST(IA) LE 0),
  PUT "Error: Investment in solar power is posible in area " IA.tl:OTLW " for technlogy " IGSOLE.tl:OTLW ", however, the solar profile is not initialised (ISOLESUMST is zero)."/;
  ERRCOUNT2=ERRCOUNT2+1;);
);
IF((ISCALAR1 LT ERRCOUNT2),PUT "#"/;);

* If hydro run-of-river investment is possible then IWTRRRSUM must be positive:
ISCALAR1=ERRCOUNT2;
LOOP((IA,IGHYRR)$IAGKN(IA,IGHYRR),
  IF((IWTRRRSUM(IA) LE 0),
  PUT "Error: Investment in  hydro run-of-river is posible in area " IA.tl:OTLW " for technlogy " IGHYRR.tl:OTLW ", however, the hydro profile is not initialised (IWTRRRSUM is zero)."/;
  ERRCOUNT2=ERRCOUNT2+1;);
);
IF((ISCALAR1 LT ERRCOUNT2),PUT "#"/;);

* If hydro with reservoir power investment is possible then IWTRRSSUM must be positive:
ISCALAR1=ERRCOUNT2;
LOOP((IA,IGHYRS)$IAGKN(IA,IGHYRS),
  IF((IWTRRSSUM(IA) LE 0),
  PUT "Error: Investment in hydro with reservoir power is posible in area " IA.tl:OTLW " for technlogy " IGHYRS.tl:OTLW ", however, the hydro profile is not initialised (IWTRRSSUM is zero)."/;
  ERRCOUNT2=ERRCOUNT2+1;);
);
IF((ISCALAR1 LT ERRCOUNT2),PUT "#"/;);
$label IAGKN_error3_label1
* ------------------------------------------------------------------------------


*-------------------------------------------------------------------------------
*-------------------------------------------------------------------------------
*-------------------------------------------------------------------------------
* The conclusion is printed to error file and to log file:
PUT /;
IF ((ERRCOUNT2 EQ 0),
PUT "No obvious errors detected in the input data before simulation."
ELSE
IF ((ERRCOUNT2 EQ 1),
PUT "An error was detected in the input data before simulation." /;
PUT "See the file error2.inc for details about the error."
ELSE
PUT ERRCOUNT2:5:0 " errors were detected in the input data before simulation." /;
PUT "See the file error2.inc for details about the error."
));
PUT //;

put LOGFILE;
* Note: The below text: "Some Balmorel errors" is a keyword for communication with the BUI. Do not change.
PUT /;
PUT "* ------------------------------------------------------------------------------" / ;
IF ((ERRCOUNT2 EQ 0),
PUT "No obvious errors detected in the input data before simulation."
ELSE
PUT "Some Balmorel errors were detected in the input data before simulation." /;
PUT "See the file errors.out for details about the error."
);
PUT / "* ------------------------------------------------------------------------------" / ;
PUT //;

$label endoffile
