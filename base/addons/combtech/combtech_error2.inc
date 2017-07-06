* File comberr2.inc for the Balmorel model.
* Checking input for the combtech addon.
* Writing to ERRORFILE.
* Last revision  20160816(hr)
* There are todo's

PUT ERRORFILE /"&" / "Now checking input data for addon combtech." /;
ISCALAR5 = ERRCOUNT2;
                  display "combtrech_error2.inc", iscalar1;

*-------- set GGCOMB -----------------------------------------------------------

LOOP(IGCOMB2,
ERRSCALAR1 = 0;
LOOP(G,
  IF((GGCOMB(G,IGCOMB2)),
  ERRSCALAR1 = ERRSCALAR1 + 1;
))
IF((ERRSCALAR1 GT 1),
  PUT "Each secondary combination technology should be associated with at most one primary technology,"
      " but technology " IGCOMB2.TL:32 " is associated with more than one. " /;
  ERRCOUNT2=ERRCOUNT2+1;
));

*-------------------------------------------------------------------------------
*--- Data in GDATA: ------------------------------------------------------------

* CHECK DOCUMENTATION: MISSING THAT ALL IN A COMBECH SHOULD BE SAME TYPE ?    TODO

* GDCOMB should be between 0 and 2:
LOOP(G,
IF((GDATA(G,'GDCOMB') LT 0) OR (2 LT GDATA(G,'GDCOMB')),
  PUT "Error in table GDATA:" /;
  PUT "   The GDCOMB-value for technology " G.TL:32    " is not between 0 and 2."/;
  ERRCOUNT2=ERRCOUNT2+1;
));


* A technologi can only have a GDCOMB-value differet from 0 if it belongs to the set IGDISPATCH - IGHSTOALL:   CHECK DOCUMENTATION AND REMAINING CODE
LOOP(G$(NOT IGDISPATCH(G)),
  IF((GDATA(G,'GDCOMB') GT 0),
    PUT "Error in table GDATA:" /;
    PUT "   The technology " G.TL:32 "is not allowed as a combination technology but the GDCOMB-value is not 0."/;
    ERRCOUNT2=ERRCOUNT2+1;
));
LOOP(G$IGHSTOALL(G),
  IF((GDATA(G,'GDCOMB') GT 0),
    PUT "Error in table GDATA:" /;
    PUT "   The technology " G.TL:32 "is not allowed as a combination technology but the GDCOMB-value is not 0."/;
    ERRCOUNT2=ERRCOUNT2+1;
));


* GDCOMBGSHAREK1 should be between 0 and 1:
LOOP(G,
  IF((GDATA(G,'GDCOMBGSHAREK1') LT 0) OR (1 LT GDATA(G,'GDCOMBGSHAREK1')),
    PUT "Error in table GDATA:" /;
    PUT "   The GDCOMBGSHAREK-value for technology " G.TL:32   " is not between 0 and 1."/;
    ERRCOUNT2=ERRCOUNT2+1;
));


* GDCOMBGSHARELO should be between 0 and 1:
LOOP(G,
  IF((GDATA(G,'GDCOMBGSHARELO') LT 0) OR (1 LT GDATA(G,'GDCOMBGSHARELO')),
    PUT "Error in table GDATA:" /;
    PUT "   The GDCOMBGSHARELO-value for technology " G.TL:32   " is not between 0 and 1."/;
    ERRCOUNT2=ERRCOUNT2+1;
));


* GDCOMBGSHAREUP should be between 0 and 1:
LOOP(G,
  IF((GDATA(G,'GDCOMBGSHAREUP') LT 0) OR (1 LT GDATA(G,'GDCOMBGSHAREUP')),
    PUT "Error in table GDATA:" /;
    PUT "   The GDCOMBGSHAREUP-value for technology " G.TL:32   " is not between 0 and 1."/;
    ERRCOUNT2=ERRCOUNT2+1;
));


* GDCOMBGSHARELO should be less than or equal to GDCOMBGSHAREUP:
LOOP(G,
  IF((GDATA(G,'GDCOMBGSHAREUP') LT GDATA(G,'GDCOMBGSHARELO')),
    PUT "Error in table GDATA:" /;
    PUT "   The GDCOMBGSHAREUP-value for technology " G.TL:32   " is lower than the GDCOMBGSHAREUP-value."/;
    ERRCOUNT2=ERRCOUNT2+1;
));


* Sum of GDCOMBGSHARELO for combinations technologies, should not exceed 1:
LOOP(G$IGCOMB1(G),
IF(((GDATA(G,'GDCOMBGSHARELO') + sum(IGGGALIAS$GGCOMB(G,IGGGALIAS),GDATA(IGGGALIAS,'GDCOMBGSHARELO'))) GT 1),
  PUT "Error in table GDATA:" /;
  PUT "   The sum of GDCOMBGSHARELO-values for combination technology " G.TL:32  "exceeds one."/;
  ERRCOUNT2=ERRCOUNT2+1;
));

* GDOMFCOST0 and GDINVCOST0 values af secondary technologies should be 0:
LOOP(G$IGCOMB2(G),
  IF((GDATA(G,'GDINVCOST0') NE 0),
    PUT "Error in table GDATA:" /;
    PUT "   The GDINVCOST0-values for secondary combinationtechnology " G.TL:32    "is "GDATA(G,'GDINVCOST0'):3", but should be 0."/;   !! 20160614
    ERRCOUNT2=ERRCOUNT2+1;
  )
  IF((GDATA(G,'GDOMFCOST0') NE 0),
    PUT "Error in table GDATA:" /;
    PUT "   The GDOMFCOST0-values for secondary combination technology " G.TL:32    "is "GDATA(G,'GDOMFCOST0'):3", but should be 0."/;
    ERRCOUNT2=ERRCOUNT2+1;
  )
);


* Secondary technologies should have the same GDFROMYEAR, GDLIFETIME and GDKVARIABL values as the primary technology:
LOOP(G$IGCOMB1(G),
LOOP(IGGGALIAS$GGCOMB(G,IGGGALIAS),
  IF((GDATA(G,'GDFROMYEAR') NE GDATA(IGGGALIAS,'GDFROMYEAR')),
    PUT "Error in table GDATA:" /;
    PUT "   The GDFROMYEAR-value for secondary combination technology " IGGGALIAS.TL:32   "is different from primary technology " G.TL:32/;
    ERRCOUNT2=ERRCOUNT2+1;
  )
  IF((GDATA(G,'GDLIFETIME') NE GDATA(IGGGALIAS,'GDLIFETIME')),
    PUT "Error in table GDATA:" /;
    PUT "   The GDLIFETIME-value for secondary combination technology " IGGGALIAS.TL:32   "is different from primary technology " G.TL:32/;
    ERRCOUNT2=ERRCOUNT2+1;
  )
  IF((GDATA(G,'GDKVARIABL') NE GDATA(IGGGALIAS,'GDKVARIABL')),
  PUT "Error in table GDATA:" /;
  PUT "   The GDKVARIABL-value for secondary combination technology " IGGGALIAS.TL:32   "is different from primary technology " G.TL:32/;
  ERRCOUNT2=ERRCOUNT2+1;
  )
););


$ontext   The present 2016 version allows investments.
* There should be no capacity for secondary combination technologies:

LOOP((Y,IA,IGCOMB2),
  IF((GKFX(Y,IA,IGCOMB2) GT 0),
  PUT "Error in table GKFX:" /;
  PUT "   There should be no capacity for secondary combination technologies, " /;
  PUT "   in area "IA.TL:32 " technology " IGCOMB2.TL:32 " has a capacity of " GKFX(Y,IA,IGCOMB2):4:0" MW" /;
  ERRCOUNT2=ERRCOUNT2+1;
));
$offtext

IF((ISCALAR5 EQ ERRCOUNT2),
       PUT  "Finished checking input data for addon Combtech, no obvious errors found, total number of observed errors is unchanged at " ERRCOUNT2:4:0   /;
ELSE   PUT  "Finished checking input data for addon Combtech, total number of observed errors is now " ERRCOUNT2:4:0   /;);
PUT "#" /;


