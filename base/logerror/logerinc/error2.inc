* File error2.inc

* This file is part of the Balmorel model, version 2.12 Alpha (July 2005).

* File last time modified 17-05-2002 (rus), 2005.07.31 (hr), 2005.12.17 (hr), 20080414(hr).


* This file contains check on input data.
* This file should be included into the Balmorel.gms file
* immediately before the SOLVE statement.
* The checks are not necessarily 'logical', rather they check for
* 'reasonable' values (e.g., that most efficiencies are between 0 and 1),
* and values that for the present model must be within certain ranges.

* Check the code below to see the exact meaning of this.



PUT ERRORFILE;

PUT / "The input data was investigated for obvious errors: "//;




*------------------------------------------------------------------------------
*--- DATA IN THE FILE sets.inc:-------------------------------------------------

*-------- set GGCOMB -----------------------------------------------------------

$ifi not %COMBTECH%==yes $goto error2_combtech_label1
LOOP(IGCOMB2,
ERRSCALAR1 = 0;
LOOP(G,
IF((GGCOMB(G,IGCOMB2)),
ERRSCALAR1 = ERRSCALAR1 + 1;
))
IF((ERRSCALAR1 GT 1),
PUT "Each secondary combination technology should be associated with at most one primary technology,"
    " but technology " IGCOMB2.TL:32" is associated with more than one. " /;
ERRCOUNT2=ERRCOUNT2+1;
));
$label error2_combtech_label1

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


LOOP((IRRRE,IRRRI)$((ORD(IRRRE) NE ORD(IRRRI)) ),
IF((XCOST(IRRRE,IRRRI) + XLOSS(IRRRE,IRRRI) EQ 0),
PUT "Both XCOST and XLOSS are zero for region pair (";
PUT IRRRE.TL:32"," IRRRI.TL:32")."    "(Not really an error - but may be inconvenient due to possible non-unique solutions for transmission.)" /;
ERRCOUNT2=ERRCOUNT2+1; );
);
*---END TABLE XCOST AND TABLE XLOSS---------------------------------------------







*-------------------------------------------------------------------------------
*---DATA IN THE FILE var.inc:---------------------------------------------------

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
LOOP((Y,IR),
IF( (X3FX(Y,IR) NE 0),
IF( (SUM(S, IDAYSIN_S(S)*SUM(T, IHOURSIN24(T)*X3FX_VAR_T(IR,S,T))  ) EQ 0),
PUT "The tables X3_VAR_T and X3FX contain information ";
PUT " such that a net import or export is not possible for region " IR.TL:32/;
ERRCOUNT2=ERRCOUNT2+1; );
););
*---END TABLE X3_VAR_T AND TABLE X3FX-------------------------------------------

*---END OF DATA IN THE FILE var.inc---------------------------------------------
*-------------------------------------------------------------------------------





*-------------------------------------------------------------------------------
*--- DATA IN THE FILE geogr.inc: -----------------------------------------------




*---DEFP_BASE AND DHFP_BASE: ---------------------------------------------------
LOOP (IR,
IF ((DEFP_BASE(IR) LE 0),
PUT "Error in table DEFP_BASE: DEFP_BASE is not positive everywhere." /;
ERRCOUNT2=ERRCOUNT2+1;
););
LOOP (IA,
IF ((DHFP_BASE(IA) LE 0),
PUT "Error in table DHFP_BASE: DHFP_BASE is not positive everywhere." /;
ERRCOUNT2=ERRCOUNT2+1;
););


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



*---SET DEF_D1 AND DEF_U1-------------------------------------------------------
*---END TABLE DEF_STEPS AND DEF_STEPS-------------------------------------------


*--- END OF DATA IN THE FILE goegr.inc -----------------------------------------
*-------------------------------------------------------------------------------








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

LOOP(G,
IF((GDATA(G,'GDTYPE') EQ GSOLH),
PUT "Error in table GDATA:" /;
PUT "   The GDTYPE-value for technology " G.TL:32  " is GHSOL, however, this technology type is not yet implemented."/;
ERRCOUNT2=ERRCOUNT2+1;
));
/*   Hans: this is not valid with acronyms
LOOP(G,
IF((GDATA(G,'GDTYPE') GE 12),
PUT "Error in table GDATA:" /;
PUT "   The GDTYPE-value for technology " G.TL:32  " is 12 or greater, however, this is illegal. ACRONYMS should be used. "/;
ERRCOUNT2=ERRCOUNT2+1;
));
*/



$if not %COMBTECH%==yes $goto error2_combtech_label2
* GDCOMB should be between 0 and 2:
LOOP(G,
IF((GDATA(G,'GDCOMB') LT 0) OR (2 LT GDATA(G,'GDCOMB')),
PUT "Error in table GDATA:" /;
PUT "   The GDCOMB-value for technology " G.TL
    " is not between 0 and 2."/;
ERRCOUNT2=ERRCOUNT2+1;
));


* A technologi can only have a GDCOMB-value differet from 0 if it belongs to
* the set IGDISPATCH - IGESTO - IGHSTO:
LOOP(G$(NOT IGDISPATCH(G)),
IF((GDATA(G,'GDCOMB') GT 0),
PUT "Error in table GDATA:" /;
PUT "   The technology " G.TL:32 "is not allowed as a combination technology"
    " but the GDCOMB-value is not 0."/;
ERRCOUNT2=ERRCOUNT2+1;
));
LOOP(G$(IGESTO(G) OR IGESTO(G)),
IF((GDATA(G,'GDCOMB') GT 0),
PUT "Error in table GDATA:" /;
PUT "   The technology " G.TL:32 "is not allowed as a combination technology"
    " but the GDCOMB-value is not 0."/;
ERRCOUNT2=ERRCOUNT2+1;
));


* GDCOMBSK should be between 0 and 1:
LOOP(G,
IF((GDATA(G,'GDCOMBSK') LT 0) OR (1 LT GDATA(G,'GDCOMBSK')),
PUT "Error in table GDATA:" /;
PUT "   The GDCOMBSK-value for technology " G.TL
    " is not between 0 and 1."/;
ERRCOUNT2=ERRCOUNT2+1;
));


* GDCOMBSLO should be between 0 and 1:
LOOP(G,
IF((GDATA(G,'GDCOMBSLO') LT 0) OR (1 LT GDATA(G,'GDCOMBSLO')),
PUT "Error in table GDATA:" /;
PUT "   The GDCOMBSLO-value for technology " G.TL
    " is not between 0 and 1."/;
ERRCOUNT2=ERRCOUNT2+1;
));


* GDCOMBSUP should be between 0 and 1:
LOOP(G,
IF((GDATA(G,'GDCOMBSUP') LT 0) OR (1 LT GDATA(G,'GDCOMBSUP')),
PUT "Error in table GDATA:" /;
PUT "   The GDCOMBSUP-value for technology " G.TL
    " is not between 0 and 1."/;
ERRCOUNT2=ERRCOUNT2+1;
));


* GDCOMBSLO should be less than or equal to GDCOMBSUP:
LOOP(G,
IF((GDATA(G,'GDCOMBSUP') LT GDATA(G,'GDCOMBSLO')),
PUT "Error in table GDATA:" /;
PUT "   The GDCOMBSUP-value for technology " G.TL
    " is lower than the GDCOMBSUP-value."/;
ERRCOUNT2=ERRCOUNT2+1;
));


* Sum of GDCOMBSLO for combinations technologies, should not exceed 1:
LOOP(G$IGCOMB1(G),
IF(((GDATA(G,'GDCOMBSLO') + sum(IGGGALIAS$GGCOMB(G,IGGGALIAS),GDATA(IGGGALIAS,'GDCOMBSLO'))) GT 1),
PUT "Error in table GDATA:" /;
PUT "   The sum of GDCOMBSLO-values for combination technology " G.TL
    "exceeds one."/;
ERRCOUNT2=ERRCOUNT2+1;
));

* GDOMFCOST0 and GDINVCOST0 values af secondary technologies should be 0:
LOOP(G$IGCOMB2(G),
IF((GDATA(G,'GDINVCOST0') NE 0),
PUT "Error in table GDATA:" /;
PUT "   The GDINVCOST0-values for secondary combinatio ntechnology " G.TL
    "is "GDATA(G,'GDINVCOST0'):3", but should be 0."/;
ERRCOUNT2=ERRCOUNT2+1;
)
IF((GDATA(G,'GDOMFCOST0') NE 0),
PUT "Error in table GDATA:" /;
PUT "   The GDOMFCOST0-values for secondary combination technology " G.TL
    "is "GDATA(G,'GDOMFCOST0'):3", but should be 0."/;
ERRCOUNT2=ERRCOUNT2+1;
)
);


* Secondary technologies should have the same GDFROMYEAR, GDLIFETIME and GDKVARIABL values as the primary technology:
LOOP(G$IGCOMB1(G),
LOOP(IGGGALIAS$GGCOMB(G,IGGGALIAS),
IF((GDATA(G,'GDFROMYEAR') NE GDATA(IGGGALIAS,'GDFROMYEAR')),
PUT "Error in table GDATA:" /;
PUT "   The GDFROMYEAR-value for secondary combination technology " IGGGALIAS.TL
    "is different from primary technology " G.TL/;
ERRCOUNT2=ERRCOUNT2+1;
)
IF((GDATA(G,'GDLIFETIME') NE GDATA(IGGGALIAS,'GDLIFETIME')),
PUT "Error in table GDATA:" /;
PUT "   The GDLIFETIME-value for secondary combination technology " IGGGALIAS.TL
    "is different from primary technology " G.TL/;
ERRCOUNT2=ERRCOUNT2+1;
)
IF((GDATA(G,'GDKVARIABL') NE GDATA(IGGGALIAS,'GDKVARIABL')),
PUT "Error in table GDATA:" /;
PUT "   The GDKVARIABL-value for secondary combination technology " IGGGALIAS.TL
    "is different from primary technology " G.TL/;
ERRCOUNT2=ERRCOUNT2+1;
)
)
);

$label error2_combtech_label2

* Ranges for fuel efficiencies are technology specific.
* However, all fuel efficiencies are positive:
LOOP(G,
IF((GDATA(G,'GDFE') LT 0.1),
PUT "Error in table GDATA:" /;
PUT "   The fuel efficiency for technology " G.TL:32
PUT " is very small (" GDATA(G,'GDFE'):10:5 ")." /;
ERRCOUNT2=ERRCOUNT2+1;
));

* Ranges for fuel efficiencies are technology specific.
* Heatpumps: a reasonable range is expected to be 0.8 to 5:
LOOP(IGETOH,
IF( (GDATA(IGETOH,'GDFE') LT 0.8) OR (5 LT GDATA(IGETOH,'GDFE')),
PUT "Possible error in table GDATA:" /;
PUT "   The fuel efficiency for technology " IGETOH.TL:32
PUT " is very small or very large (" GDATA(IGETOH,'GDFE'):10:5 ")." /;
ERRCOUNT2=ERRCOUNT2+1;
));

* Total fuel efficiency on extraction units should not exceed 100% in back pressure mode
LOOP(IGEXT,
IF((1 LT (GDATA(IGEXT,'GDFE')*((GDATA(IGEXT,'GDCB')+1)/(GDATA(IGEXT,'GDCB')+GDATA(IGEXT,'GDCV'))))),
PUT "Possible error in table GDATA:" /;
PUT "   The fuel efficiency for technology " IGEXT.TL:32
PUT " exceeds 100% in back pressure mode (value: "
   (GDATA(IGEXT,'GDFE')*((GDATA(IGEXT,'GDCB')+1)/(GDATA(IGEXT,'GDCB')+GDATA(IGEXT,'GDCV')))):10:5 ")." /;
ERRCOUNT2=ERRCOUNT2+1; );
);

* GDCB-values should be nonnegative for IGEXT:
LOOP(IGEXT,
IF( ((GDATA(IGEXT,'GDCB') LT 0)),
PUT "Error in table GDATA:" /;
PUT "   The GDCB-values for technology " IGEXT.TL:32 " is negative."  /;
ERRCOUNT2=ERRCOUNT2+1;
));


* GDSTOHLOAD-values should be positive for heat storages:
LOOP(IGHSTO,
IF( ((GDATA(IGHSTO,'GDSTOHLOAD') LE 0)),
PUT "Error in table GDATA:" /;
PUT "   The GDSTOHLOAD-values for technology " IGHSTO.TL:32 " is not positive ("GDATA(IGHSTO,'GDSTOHLOAD'):10:5")."  /;
ERRCOUNT2=ERRCOUNT2+1;
));
* GDSTOHUNLD-values should be positive for heat storages:
LOOP(IGHSTO,
IF( ((GDATA(IGHSTO,'GDSTOHUNLD') LE 0)),
PUT "Error in table GDATA:" /;
PUT "   The GDSTOHUNLD-values for technology " IGHSTO.TL:32 " is not positive ("GDATA(IGHSTO,'GDSTOHUNLD'):10:5")."  /;
ERRCOUNT2=ERRCOUNT2+1;
));

* GDSTOHLOAD-values should be positive for electricity storages:
LOOP(IGESTO,
IF( ((GDATA(IGESTO,'GDSTOHLOAD') LE 0)),
PUT "Error in table GDATA:" /;
PUT "   The GDSTOHLOAD-values for technology " IGESTO.TL:32 " is not positive ("GDATA(IGESTO,'GDSTOHLOAD'):10:5")."  /;
ERRCOUNT2=ERRCOUNT2+1;
));
* GDSTOHUNLD-values should be positive for electricity storages:
LOOP(IGESTO,
IF( ((GDATA(IGESTO,'GDSTOHUNLD') LE 0)),
PUT "Error in table GDATA:" /;
PUT "   The GDSTOHUNLD-values for technology " IGESTO.TL:32 " is not positive ("GDATA(IGESTO,'GDSTOHUNLD'):10:5")."  /;
ERRCOUNT2=ERRCOUNT2+1;
));

* GDCB-values should be positive for electricity storages:
LOOP(IGESTO,
IF( ((GDATA(IGESTO,'GDCB') LE 0)),
PUT "Error in table GDATA:" /;
PUT "   The GDCB-values for electricity storage " IGESTO.TL:32 " is not positive ("GDATA(IGESTO,'GDCB'):10:5"). (Remember you may use INF.)"  /;
ERRCOUNT2=ERRCOUNT2+1;
));



/*  Hans: this is not valid with acronyms
* GDFUEL should be between 1 and CARD(FFF):
* ... but, of course, not necessarily ... If you deliberately
* chose numbers outside the indicated range, just change the check,
* or comment it out.
LOOP(G,
IF((GDATA(G,'GDFUEL') LT 0) OR (CARD(FFF) LT GDATA(G,'GDFUEL')),
PUT "Error in table GDATA:" /;
PUT "   The GDFUEL-values for technology " G.TL:32
    " is  not between 0 and " CARD(FFF):2"."/;
ERRCOUNT2=ERRCOUNT2+1;
));
*/
*------



* The value in GDKVARIABL should be 0 or 1:
LOOP(G,
IF (((GDATA(G,'GDKVARIABL') NE 0) AND (GDATA(G,'GDKVARIABL') NE 1)),
PUT "Error in table GDATA:" /;
PUT "   GDKVARIABL should be 0 or 1 but is not so for technology " G.TL:32 /;
ERRCOUNT2=ERRCOUNT2+1;
); );

/* Hans 12345: commented out, but have not checked that the code (e.g. in QHYRS) works:
* The value in GDKVARIABL should (presently) be 0 for IGHYRS:
LOOP(IGHYRS,
IF (((GDATA(IGHYRS,'GDKVARIABL') NE 0)),
PUT "Error in table GDATA:" /;
PUT "   GDKVARIABL should (presently) be 0 for long term electricity storages, but is not so for technology " IGHYRS.TL:32 /;
ERRCOUNT2=ERRCOUNT2+1;
); );
*/


*---END TABLE GDATA-------------------------------------------------------------

*--- END OF DATA IN THE FILE tech.inc ------------------------------------------
*-------------------------------------------------------------------------------



*-------------------------------------------------------------------------------
*--- DATA IN THE FILE FUELP_Y.INC:----------------------------------------------

* Some of the fuels shold have a positive price:
* Observe that this check is dependent on the specific value used for FDNB
* and therefore heavily user dependent.
LOOP((Y,IA,FFF)$(
   (FDATA(FFF,"FDNB") EQ 1) OR
   (FDATA(FFF,"FDNB") EQ 1) OR   /*just examples*/
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



*-------------------------------------------------------------------------------
*--- DATA IN THE FILE gkfx.inc:-------------------------------------------------

* Probably it is an error if there for some of the countries in C
* is positive capacity for some technologies i GGG but not in G:
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


* There should only be one heat storage technology in any area:

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
))


* There should be no capacity for secondary combination technologies:
$if not %COMBTECH%==yes $goto error2_combtech_label3
LOOP((Y,IA,IGCOMB2),
IF((GKFX(Y,IA,IGCOMB2) GT 0),
PUT "Error in table GKFX:" /;
PUT "   There should be no capacity for secondary combination technologies, " /;
PUT "   in area "IA.TL:32 " technology " IGCOMB2.TL:32 " has a capacity of " GKFX(Y,IA,IGCOMB2):4:0" MW" /;
ERRCOUNT2=ERRCOUNT2+1;
));
$label error2_combtech_label3

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
LOOP((Y,IR,X3VPLACE,S,T)$(X3VX(IR,X3VPLACE)),
*LOOP((X3VPLACE)$(X3VX(IR,X3VPLACE)),
LOOP(X3VSTEP0$((X3VSTEP(X3VSTEP0)) AND (ORD(X3VSTEP0) LE (CARD(X3VSTEP0)-1))),
IF((X3VPIM(Y,IR,X3VPLACE,X3VSTEP0,S,T) LT X3VPIM(Y,IR,X3VPLACE,X3VSTEP0+1,S,T)),
PUT "The prices for price dependent import from third places should be weakly increasing"/;
PUT "   this is not so for " Y.TL:32 IR.TL:32 X3VPLACE.TL:32 S.TL:32 T.TL:32 X3VSTEP0.TL:32 " to next step. Prices: "
        X3VPIM(Y,IR,X3VPLACE,X3VSTEP0,S,T) X3VPIM(Y,IR,X3VPLACE,X3VSTEP0+1,S,T) /;
ERRCOUNT2=ERRCOUNT2+1;
)));

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


* The prices for price dependent export to third places should be greater than or equal to
* the prices for price dependent import from third places:

LOOP((Y,IR,X3VPLACE,S,T)$X3VX(IR,X3VPLACE),
*LOOP((X3VPLACE)$(IST(S,T) and X3VX(IR,X3VPLACE)),
LOOP(X3VSTEP,
IF((X3VPEX(Y,IR,X3VPLACE,X3VSTEP,S,T) LT X3VPIM(Y,IR,X3VPLACE,X3VSTEP,S,T)),
PUT "The prices for price dependent export from third places should be greater than or equal to the prices for price dependent import from third places"/;
PUT "   this is not so for " Y.TL:32 IR.TL:32 X3VPLACE.TL:32 S.TL:32 T.TL:32 ", import and exprot prices are " X3VPIM(Y,IR,X3VPLACE,X3VSTEP,S,T)   X3VPEX(Y,IR,X3VPLACE,X3VSTEP,S,T) /;
ERRCOUNT2=ERRCOUNT2+1;
)));


*---END OF TABLE X3VPIM AND TABLE X3VPEX----------------------------------------
$label X3V_error2_label1


*-------------------------------------------------------------------------------
* Combination of investment possibilities and other data.

$ifi not %BB2%==yes $goto IAGKN_error3_label1

* If wind power investment is possible then IWND_SUMST must be positive:
LOOP((IA,IGWND)$IAGKN(IA,IGWND),
  IF((IWND_SUMST(IA) LE 0),
  PUT "Error: Investment in wind power is posible in area " IA.tl:OTLW " for technlogy " IGWND.tl:OTLW ", however, the wind profile is not initialised (IWND_SUMST is zero)."/;
  ERRCOUNT2=ERRCOUNT2+1;);
);

* If solarE power investment is possible then ISOLESUMST must be positive:
LOOP((IA,IGSOLE)$IAGKN(IA,IGSOLE),
  IF((ISOLESUMST(IA) LE 0),
  PUT "Error: Investment in solar power is posible in area " IA.tl:OTLW " for technlogy " IGSOLE.tl:OTLW ", however, the solar profile is not initialised (ISOLESUMST is zero)."/;
  ERRCOUNT2=ERRCOUNT2+1;);
);

* If hydro run-of-river investment is possible then IWTRRRSUM must be positive:
LOOP((IA,IGHYRR)$IAGKN(IA,IGHYRR),
  IF((IWTRRRSUM(IA) LE 0),
  PUT "Error: Investment in  hydro run-of-river is posible in area " IA.tl:OTLW " for technlogy " IGHYRR.tl:OTLW ", however, the hydro profile is not initialised (IWTRRRSUM is zero)."/;
  ERRCOUNT2=ERRCOUNT2+1;);
);

* If hydro with reservoir power investment is possible then IWTRRSSUM must be positive:
LOOP((IA,IGHYRS)$IAGKN(IA,IGHYRS),
  IF((IWTRRSSUM(IA) LE 0),
  PUT "Error: Investment in hydro with reservoir power is posible in area " IA.tl:OTLW " for technlogy " IGHYRS.tl:OTLW ", however, the hydro profile is not initialised (IWTRRSSUM is zero)."/;
  ERRCOUNT2=ERRCOUNT2+1;);
);

$label IAGKN_error3_label1
* ------------------------------------------------------------------------------


*-------------------------------------------------------------------------------
*-------------------------------------------------------------------------------
*-------------------------------------------------------------------------------
* The conclusion is printed:
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
IF ((ERRCOUNT2 EQ 0),
PUT "No obvious errors detected in the input data before simulation."
ELSE
PUT "Some Balmorel errors were detected in the input data before simulation." /;
PUT "See the file errors.out for details about the error."
);
PUT //;
