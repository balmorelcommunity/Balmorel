* File error4.inc

* This file is part of the Balmorel model, version 2.13 Alpha (xxx 2006).
* File last time modified 20080414(hr)


* This file contains check on the solution of the optimisation.
* The checks are primarily intended as help to detect reasons for infeasibility.

* Check the code below to see the exact meaning of this.


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
PUT" in region "IA.TL:32 " year " Y.TL:4 " season "S.TL:8" time period "T.TL:8 " Value (MW): " VQHEQ.l(IA,S,T,'IMINUS') " Penalty size (PENALTYQ): " PENALTYQ/;
ERRCOUNT4=ERRCOUNT4+1; );
IF((VQHEQ.l(IA,S,T,'IPLUS') GT 0),
PUT"Error: Heat demand in urban areas is assumed inelastic but demand is increased"/;
PUT" in region "IA.TL:32 " year " Y.TL:4 " season "S.TL:8" time period "T.TL:8 " Value (MW): " VQHEQ.l(IA,S,T,'IPLUS') " Penalty size (PENALTYQ): " PENALTYQ/;
ERRCOUNT4=ERRCOUNT4+1; );
);

* Heat Storage:

LOOP((IA,S,T),
IF((VQHSTOVOLT.l(IA,S,T,'IMINUS') GT 0),
PUT"Error: Heat storage demand is smaller than needed storage"/;
PUT" in region "IA.TL:32 " year " Y.TL:4 " season "S.TL:8" time period "T.TL:8 " Value (MW): " VQHSTOVOLT.l(IA,S,T,'IMINUS') " Penalty size (PENALTYQ): " PENALTYQ/;
ERRCOUNT4=ERRCOUNT4+1; );
IF((VQHSTOVOLT.l(IA,S,T,'IPLUS') GT 0),
PUT"Error: Heat storage demand is greater than storage capacity"/;
PUT" in region "IA.TL:32 " year " Y.TL:4 " season "S.TL:8" time period "T.TL:8 " Value (MW): " VQHSTOVOLT.l(IA,S,T,'IPLUS') " Penalty size (PENALTYQ): " PENALTYQ/;
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