* File error4.inc

* This file is part of the Balmorel model.
* File last time modified 20080414(hr), 20120914(hr), 20150506(hr)


* This file contains check on the solution of the optimisation.
* The checks are primarily intended as help to detect reasons for infeasibility.

* Check the code below to see the exact meaning of this.


PUT ERRORFILE;

* Skip the remaining part of the file if the model did not solve properly:
$ifi %BB1%==yes IF(BALBASE1.MODELSTAT GT 2, PUT ERRORFILE "Skipped file prt3-bb2.INC" / /; PUT LOGFILE "Model did not solve properly, details not available here." / /; ELSE
$ifi %BB2%==yes IF(BALBASE2.MODELSTAT GT 2, PUT ERRORFILE "Skipped file prt3-bb2.INC" / /; PUT LOGFILE "Model did not solve properly, details not available here." / /; ELSE
$ifi %BB3%==yes IF(BALBASE3.MODELSTAT GT 2, PUT ERRORFILE "Skipped file prt3-bb2.INC" / /; PUT LOGFILE "Model did not solve properly, details not available here." / /; ELSE

PUT ERRORFILE;

PUT /"The output was investigated for obvious errors after optimisation of year " Y.TL:4 ":" /;

ERRCOUNT4=0;

* If demands are inelastic then the variables  DEF_T and DHF_T should be zero.
* If they are not, this shows that demand could not be 'satisfied'
* i.e., an indication that it is not possible to satisfy the demand.
* The inditation that demands are inelastic is that sets DEF and DHF contain
* only one element each.
* Observe that it is assumed

*-------------------------------------------------------------------------------

* Electricity:

* Electricity Demand:

LOOP((IR,S,T),
IF((VQEEQ.l(IR,S,T,'IMINUS') GT 0),
PUT"Error: Electricity demand is assumed inelastic but can not be satisfied"/;
PUT" in region "IR.TL:32 " year " Y.TL:4 " season "S.TL:8" time period "T.TL:8 " Value (MW): " VQEEQ.l(IR,S,T,'IMINUS') " Penalty size (PENALTYQ): " PENALTYQ/;
ERRCOUNT4=ERRCOUNT4+1; );
IF((VQEEQ.l(IR,S,T,'IPLUS') GT 0),
PUT"Error: Electricity demand is assumed inelastic but demand is increased"/;
PUT" in region "IR.TL:32 " year " Y.TL:4 " season "S.TL:8" time period "T.TL:8 " Value (MW): " VQEEQ.l(IR,S,T,'IPLUS') " Penalty size (PENALTYQ): " PENALTYQ/;
ERRCOUNT4=ERRCOUNT4+1; );
);

* Electricity Storage:

LOOP((IA,S,T),
IF((VQESTOVOLT.l(IA,S,T,'IMINUS') GT 0),
PUT"Error: Electricity storage demand is smaller than needed storage"/;
PUT" in region "IA.TL:32 " year " Y.TL:4 " season "S.TL:8" time period "T.TL:8 " Value (MW): " VQESTOVOLT.l(IA,S,T,'IMINUS') " Penalty size (PENALTYQ): " PENALTYQ/;
ERRCOUNT4=ERRCOUNT4+1; );
IF((VQESTOVOLT.l(IA,S,T,'IPLUS') GT 0),
PUT"Error: Electricity storage demand is greater than storage capacity"/;
PUT" in region "IA.TL:32 " year " Y.TL:4 " season "S.TL:8" time period "T.TL:8 " Value (MW): " VQESTOVOLT.l(IA,S,T,'IPLUS') " Penalty size (PENALTYQ): " PENALTYQ/;
ERRCOUNT4=ERRCOUNT4+1; );
);

*-------------------------------------------------------------------------------

* Heat:


* Heat Demand:

LOOP((IA,S,T),
IF((VQHEQ.l(IA,S,T,'IMINUS') GT 0),
PUT"Error: Heat demand is assumed inelastic but can not be satisfied"/;
PUT" in area "IA.TL:32 " year " Y.TL:4 " season "S.TL:8" time period "T.TL:8 " Value (MW): " VQHEQ.l(IA,S,T,'IMINUS') " Penalty size (PENALTYQ): " PENALTYQ/;
ERRCOUNT4=ERRCOUNT4+1; );
IF((VQHEQ.l(IA,S,T,'IPLUS') GT 0),
PUT"Error: Heat demand in urban areas is assumed inelastic but demand is increased"/;
PUT" in area "IA.TL:32 " year " Y.TL:4 " season "S.TL:8" time period "T.TL:8 " Value (MW): " VQHEQ.l(IA,S,T,'IPLUS') " Penalty size (PENALTYQ): " PENALTYQ/;
ERRCOUNT4=ERRCOUNT4+1; );
);

* Heat Storage:

LOOP((IA,S,T),
IF((VQHSTOVOLT.l(IA,S,T,'IMINUS') GT 0),
PUT"Error: Heat storage demand is smaller than needed storage"/;
PUT" in area "IA.TL:32 " year " Y.TL:4 " season "S.TL:8" time period "T.TL:8 " Value (MW): " VQHSTOVOLT.l(IA,S,T,'IMINUS') " Penalty size (PENALTYQ): " PENALTYQ/;
ERRCOUNT4=ERRCOUNT4+1; );
IF((VQHSTOVOLT.l(IA,S,T,'IPLUS') GT 0),
PUT"Error: Heat storage demand is greater than storage capacity"/;
PUT" in area "IA.TL:32 " year " Y.TL:4 " season "S.TL:8" time period "T.TL:8 " Value (MW): " VQHSTOVOLT.l(IA,S,T,'IPLUS') " Penalty size (PENALTYQ): " PENALTYQ/;
ERRCOUNT4=ERRCOUNT4+1; );
);

*------------------------------------------------------------------------------
* POLICIES - addon

$ifi not %POLICIES%==yes  $goto endPOLICIES_label
LOOP((POLAREA,POLICY)$(IPOLREQ_Y(POLAREA,POLICY) and POLTYP(POLICY,'SHAREGROSS')),
IF((VQPOLSHAREGROSS.l(POLAREA,POLICY)  GT 0),
PUT"Error: Slac variable VQPOLSHAREGROSS is greater than 0"/;
PUT" in geografy "POLAREA.TL " year " y.tl " Value (): " VQPOLSHAREGROSS.l(POLAREA,POLICY) " Penalty size (PENALTYQ): 1000*" PENALTYQ " /2"/;
PUT"";
ERRCOUNT4=ERRCOUNT4+1; );
);

LOOP((POLAREA,POLICY)$(IPOLREQ_Y(POLAREA,POLICY) and POLTYP(POLICY,'SHARENETTO')),
IF((VQPOLSHARENET.l(POLAREA,POLICY)  GT 0),
PUT"Error: Slac variable VQPOLSHARENET is greater than 0"/;
PUT" in geografy "POLAREA.TL " year " y.tl " Value (): " VQPOLSHARENET.l(POLAREA,POLICY) " Penalty size (PENALTYQ): 1000*" PENALTYQ " /2"/;
PUT"";
ERRCOUNT4=ERRCOUNT4+1; );
);

LOOP((POLAREA,POLICY)$(IPOLREQ_Y(POLAREA,POLICY) and POLTYP(POLICY,'MAXCO2')),
IF((VQPOLMAXCO2.l(POLAREA,POLICY)  GT 0),
PUT"Error: Slac variable VQPOLMAXCO2 is greater than 0"/;
PUT" in geografy "POLAREA.TL " year " y.tl " Value (): " VQPOLMAXCO2.l(POLAREA,POLICY) " Penalty size (PENALTYQ): " PENALTYQ " /2"/;
PUT"";
ERRCOUNT4=ERRCOUNT4+1; );
);

LOOP((POLAREA,POLICY)$(IPOLREQ_Y(POLAREA,POLICY) and POLTYP(POLICY,'MINPROD')),
IF((VQPOLMINPROD.l(POLAREA,POLICY)  GT 0),
PUT"Error: Slac variable VQPOLMINPROD is greater than 0"/;
PUT" in geografy "POLAREA.TL " year " y.tl " Value (): " VQPOLMINPROD.l(POLAREA,POLICY) " Penalty size (PENALTYQ): " PENALTYQ " /2"/;
PUT"";
ERRCOUNT4=ERRCOUNT4+1; );
);

LOOP((POLAREA,POLICY)$(IPOLREQ_Y(POLAREA,POLICY) and POLTYP(POLICY,'CAPTARGET')),
IF((VQPOLCAPTARGET.l(POLAREA,POLICY)  GT 0),
PUT"Error: Slac variable VQPOLCAPTARGET is greater than 0"/;
PUT" in geografy "POLAREA.TL " year " y.tl " Value (): " VQPOLCAPTARGET.l(POLAREA,POLICY) " Penalty size (PENALTYQ): " PENALTYQ " /2"/;
PUT"";
ERRCOUNT4=ERRCOUNT4+1; );
);

$label endPOLICIES_label

*------------------------------------------------------------------------------

* System Constrains - addon

$ifi not %SYSTEMCONST%==yes  $goto endSYSTEMCONST_label
LOOP((C,S,T)$(BASELOADSERVICE(C)),
IF((VQBASELOAD.l(C,S,T)  GT 0),
PUT"Error: Slac variable VQBASELOAD is greater than 0"/;
PUT" in Country "C.TL " Season " S.TL " Timestep " T.TL " Value (MW): " VQBASELOAD.l(C,S,T) " Penalty size (PENALTYQ): " PENALTYQ " /2"/;
PUT"";
ERRCOUNT4=ERRCOUNT4+1; );
);

$label endSYSTEMCONST_label

*------------------------------------------------------------------------------

* Fuel constraints:

* Fuel constrained country

LOOP((C,FFF),
IF((VQGEQCF.l(C,FFF,'IMINUS') GT 0),
PUT"Error: Fuel consuption is smaller than the requirement"/;
PUT" in country "C.TL:32 " year " Y.TL:4 " fuel "FFF.TL:16" Value (MW): " VQGEQCF.l(C,FFF,'IMINUS') " Penalty size (PENALTYQ): " PENALTYQ/;
ERRCOUNT4=ERRCOUNT4+1; );
IF((VQGEQCF.l(C,FFF,'IPLUS') GT 0),
PUT"Error: Fuel consuption is larger than the requirement"/;
PUT" in country "C.TL:32 " year " Y.TL:4 " fuel "FFF.TL:16" Value (MW): " VQGEQCF.l(C,FFF,'IPLUS') " Penalty size (PENALTYQ): " PENALTYQ/;
ERRCOUNT4=ERRCOUNT4+1; );
IF((VQGMINCF.l(C,FFF) GT 0),
PUT"Error: Fuel consuption doesnt satisfy the minimal fuel use"/;
PUT" in country "C.TL:32 " year " Y.TL:4 " fuel "FFF.TL:16" Value (MW): " VQGMINCF.l(C,FFF) " Penalty size (PENALTYQ): " PENALTYQ/;
ERRCOUNT4=ERRCOUNT4+1; );
IF((VQGMAXCF.l(C,FFF) GT 0),
PUT"Error: Fuel consuption exceeds the maximal fuel use"/;
PUT" in country "C.TL:32 " year " Y.TL:4 " fuel "FFF.TL:16" Value (MW): " VQGMAXCF.l(C,FFF) " Penalty size (PENALTYQ): " PENALTYQ/;
ERRCOUNT4=ERRCOUNT4+1; );
);

* Fuel constrained region

LOOP((IR,FFF),
IF((VQGEQRF.l(IR,FFF,'IMINUS') GT 0),
PUT"Error: Fuel consuption is smaller than the requirement"/;
PUT" in region "IR.TL:32 " year " Y.TL:4 " fuel "FFF.TL:16" Value (MW): " VQGEQRF.l(IR,FFF,'IMINUS') " Penalty size (PENALTYQ): " PENALTYQ/;
ERRCOUNT4=ERRCOUNT4+1; );
IF((VQGEQRF.l(IR,FFF,'IPLUS') GT 0),
PUT"Error: Fuel consuption is larger than the requirement"/;
PUT" in region "IR.TL:32 " year " Y.TL:4 " fuel "FFF.TL:16" Value (MW): " VQGEQRF.l(IR,FFF,'IPLUS') " Penalty size (PENALTYQ): " PENALTYQ/;
ERRCOUNT4=ERRCOUNT4+1; );
IF((VQGMINRF.l(IR,FFF) GT 0),
PUT"Error: Fuel consuption doesnt satisfy the minimal fuel use"/;
PUT" in region "IR.TL:32 " year " Y.TL:4 " fuel "FFF.TL:16" Value (MW): " VQGMINRF.l(IR,FFF) " Penalty size (PENALTYQ): " PENALTYQ/;
ERRCOUNT4=ERRCOUNT4+1; );
IF((VQGMAXRF.l(IR,FFF) GT 0),
PUT"Error: Fuel consuption exceeds the maximal fuel use"/;
PUT" in region "IR.TL:32 " year " Y.TL:4 " fuel "FFF.TL:16" Value (MW): " VQGMAXRF.l(IR,FFF) " Penalty size (PENALTYQ): " PENALTYQ/;
ERRCOUNT4=ERRCOUNT4+1; );
);

* Fuel constrained area

LOOP((IA,FFF),
IF((VQGEQAF.l(IA,FFF,'IMINUS') GT 0),
PUT"Error: Fuel consuption is smaller than the requirement"/;
PUT" in area "IA.TL:32 " year " Y.TL:4 " fuel "FFF.TL:16" Value (MW): " VQGEQAF.l(IA,FFF,'IMINUS') " Penalty size (PENALTYQ): " PENALTYQ/;
ERRCOUNT4=ERRCOUNT4+1; );
IF((VQGEQAF.l(IA,FFF,'IPLUS') GT 0),
PUT"Error: Fuel consuption is larger than the requirement"/;
PUT" in area "IA.TL:32 " year " Y.TL:4 " fuel "FFF.TL:16" Value (MW): " VQGEQAF.l(IA,FFF,'IPLUS') " Penalty size (PENALTYQ): " PENALTYQ/;
ERRCOUNT4=ERRCOUNT4+1; );
IF((VQGMINAF.l(IA,FFF) GT 0),
PUT"Error: Fuel consuption doesnt satisfy the minimal fuel use"/;
PUT" in area "IA.TL:32 " year " Y.TL:4 " fuel "FFF.TL:16" Value (MW): " VQGMINAF.l(IA,FFF) " Penalty size (PENALTYQ): " PENALTYQ/;
ERRCOUNT4=ERRCOUNT4+1; );
IF((VQGMAXAF.l(IA,FFF) GT 0),
PUT"Error: Fuel consuption exceeds the maximal fuel use"/;
PUT" in area "IA.TL:32 " year " Y.TL:4 " fuel "FFF.TL:16" Value (MW): " VQGMAXAF.l(IA,FFF) " Penalty size (PENALTYQ): " PENALTYQ/;
ERRCOUNT4=ERRCOUNT4+1; );
);


*------------------------------------------------------------------------------
$ifi %bb3%==yes  $goto bb3_label1
* Relevant for BB1 and bb22 only.
* Hydro Storage:

LOOP((IA,S),
IF((VQHYRSSEQ.l(IA,S,'IMINUS') GT 0),
PUT"Error: Hydro storage demand is smaller than needed storage"/;
PUT" in region "IA.TL:32 " year " Y.TL:4 " season "S.TL:8" Value (MW): " VQHYRSSEQ.l(IA,S,'IMINUS') " Penalty size (PENALTYQ): " PENALTYQ/;
ERRCOUNT4=ERRCOUNT4+1; );
IF((VQHYRSSEQ.l(IA,S,'IPLUS') GT 0),
PUT"Error: Hydro storage demand is greater than storage capacity"/;
PUT" in region "IA.TL:32 " year " Y.TL:4 " season "S.TL:8" Value (MW): " VQHYRSSEQ.l(IA,S,'IPLUS') " Penalty size (PENALTYQ): " PENALTYQ/;
ERRCOUNT4=ERRCOUNT4+1; );
);
$label bb3_label1



*------------------------------------------------------------------------------
*------------------------------------------------------------------------------
* The conclusion is printed:


IF ((ERRCOUNT4 EQ 0),
PUT "No obvious errors detected after optimisation of year " Y.TL:4  "." /;
ELSE
IF ((ERRCOUNT4 EQ 1),
PUT " An error was detected after optimisation of year " Y.TL:4  "." /;
ELSE
PUT ERRCOUNT4:5:0 " errors were detected after optimisation of year " Y.TL:4  "." /;
);
PUT "See the file error4.inc for details about errors."
PUT //;
);

* Skipped to here if the model did not solve properly:
$ifi %BB1%==yes  );
$ifi %BB2%==yes  );
$ifi %BB3%==yes  );

put LOGFILE /;
* Note: The below text: "Some Balmorel errors" is a keyword for communication with the BUI. Do not change.
IF ((ERRCOUNT4 EQ 0),
PUT "No obvious errors detected after optimisation of year " Y.TL:4 "." /;
ELSE
PUT "Some Balmorel errors were detected after optimisation of year " Y.TL:4  "." /;
);
PUT "See the file errors.out for details about errors."
PUT //;