* File errorBB4 to the Balmorel model.
* This is for addon BB4.
* Created 20081103 (hr).
put ERRORFILE;

* Set YMODEL and parameter YMODELDELTA must be consistent.
* Note that the following checks implicitly assures that all elements in YMODEL are given appropriate values,
* and further that no values can be assigned to elements in YMODELDELTA.
LOOP(YMODEL,
   IF ((ORD(YMODEL) = 1) AND (YMODELDELTA(YMODEL) NE 0),
      put ERRORFILE;
      put "ERROR in YMODELDELTA(" YMODEL.tl ") for BB4: value must be 0."/;
      ERRCOUNT2=ERRCOUNT2+1;
   );
   IF ((ORD(YMODEL) GT 1) AND (YMODELDELTA(YMODEL) <= 0),
      put ERRORFILE;
      put "ERROR in YMODELDELTA(" YMODEL.tl ") for BB4: value must be greater than 0."/;
      ERRCOUNT2=ERRCOUNT2+1;
   );
);

IF((CARD(YMODEL) GT CARD(Y)),
      put ERRORFILE;
      put "ERROR in YMODEL for BB4: (CARD(YMODEL) > CARD(Y)). No Balbase4 model will be generated"/;
      ERRCOUNT2=ERRCOUNT2+1;
);

IF((SUM(YMODEL,YMODELDELTA(YMODEL)) GT CARD(Y)-1),
      put ERRORFILE;
      put "ERROR in YMODELDELTA for BB4: The number of model years (cf. YMODEL) and the distance (cf. YMODELDELTA) between them in Balbase4 "/;
      put "is so large that with the number of elements in Y no Balbase4 model will be generated."/;
      ERRCOUNT2=ERRCOUNT2+1;
);


PUT "BB4: Presently there are only rudimentaty checks on the solution - TODO"//;

$ontext
/*  TODP      CHECK THESE VQs: (not all are necessarily used, and there may be others)

POSITIVE VARIABLE VQEEQ(Y,RRR,S,T,IPLUSMINUS)      'Feasibility in electricity generation equals demand equation QEEQ';
POSITIVE VARIABLE VQHEQ(Y,AAA,S,T,IPLUSMINUS)      'Feasibility in heat balance QHEQ';
POSITIVE VARIABLE VQESTOVOLT(Y,AAA,S,T,IPLUSMINUS) 'Feasibility in electricity storage equation QESTOVOLT';
POSITIVE VARIABLE VQHSTOVOLT(Y,AAA,S,T,IPLUSMINUS) 'Feasibility in heat storage equation VQHSTOVOLT';
POSITIVE VARIABLE VQHYRSSEQ(Y,AAA,S,IPLUSMINUS)    'Feasibility of QHYRSSEQ';

$ifi %BB4%==yes DISPLAY   VQGKVACCTOY(Y,AAA,G,YMODEL,IPLUSMINUS)      'Feasibility in new capacity constraint 1'
$ifi %BB4%==yes DISPLAY   VQGKVACCTOT(Y,AAA,G,YMODEL,IPLUSMINUS)      'Feasibility in new capacity constraint 2'
$ifi %BB4%==yes DISPLAY   VQEGKUP(AAA,G,S,T,IPLUSMINUS)               'Feasibility in capacity constraint on electricity'
$ifi %BB4%==yes DISPLAY   VQHGKUP(AAA,G,S,T,IPLUSMINUS)               'Feasibility in capacity constraint on heat'
$ifi %BB4%==yes DISPLAY   VQEGKCOMB1UP(AAA,G,S,T,IPLUSMINUS)          'Feasibility in capacity constraint on electricity'
$ifi %BB4%==yes DISPLAY   VQEGKCOMB2UP(AAA,G,S,T,IPLUSMINUS)          'Feasibility in capacity constraint on electricity combination'
$ifi %BB4%==yes DISPLAY   VQHGKCOMB1UP(AAA,G,S,T,IPLUSMINUS)          'Feasibility in capacity constraint on heat'
$ifi %BB4%==yes DISPLAY   VQHGKCOMB2UP(AAA,G,G,Y,S,T,IPLUSMINUS)      'Feasibility in capacity constraint on heat combination'
$ifi %BB4%==yes DISPLAY   VQHYRRDISP(AAA,G,S,T,IPLUSMINUS)            'Feasibility in Hydro run on river can not be dispatched'
$ifi %BB4%==yes DISPLAY   VQWNDDISP(AAA,G,S,T,IPLUSMINUS)             'Feasibility in wind power can not be dispatched'
$ifi %BB4%==yes DISPLAY   VQSOLDISP(AAA,G,S,T,IPLUSMINUS)             'Feasibility in sol can not be dispatched'
$ifi %BB4%==yes DISPLAY   VQXKN(Y,IRRRE,IRRRI,YMODEL,IPLUSMINUS)      'Feasibility in new transmission investment - NOT IMPLEMENTED PRESENTLYT'
$ifi %BB4%==yes DISPLAY   VQVGKNINT(AAA, G, Y, YMODEL,IPLUSMINUS)     'Feasibility in - NOT IMPLEMENTED PRESENTLYT '
$ifi %BB4%==yes DISPLAY   VQVXKNINT(IRRRE,IRRRI,Y, YMODEL,IPLUSMINUS) 'Feasibility in - NOT IMPLEMENTED PRESENTLYT '
*/
$offtext  