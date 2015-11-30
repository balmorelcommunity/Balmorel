* BB4overview.inc
* Created 200906xx (hr).
*
* This file will print a short overview of input data characteristics of the BalBase4 model in Balmorel.


FILE BB4overview /..\output\inputout\BB4overview.out/;
put BB4overview "Overview of input data characteristics of the BalBase4 model in Balmorel.   " system.date "  " system.time /;
put "General overview of input data may be found in inputout.out" /;
put "The information printed here is valid only if the input is consistent, please verify this, e.g. see the errors.out file first." / / ;


put "Years to be represented in models, set Y: "; LOOP(Y, PUT Y.TL:6 ); PUT / /;

put "Each Balbase4 model will have " (Card(SIMYEARS)):3:0 " years (implied by set SIMYEARS)."/ /;

put "The number of years between a year and the preceding year represented in model Balbase4 (as specified in parameter SIMDELTA) ('number' means ord's in Y):" ;
loop(SIMYEARS, PUT (SIMDELTA(SIMYEARS)):3:0;); PUT / /;

put "igen: ";
loop(SIMYEARS,  put SIMYEARS.tl: 15  ; PUT (SIMDELTA(SIMYEARS)):3:0 "   "; ); PUT / /;



* hans: pt er dette blot kopi fra BB4.sim (med undtagelse af Check), skal internaliseres!

* Calculate simweights for each simyear:
ALIAS(SIMYEARS, SIMYEARS3);
LOOP(SIMYEARS,
SIMWEIGHT(SIMYEARS) = SUM(SIMYEARS3$(ORD(SIMYEARS3) <= ORD(SIMYEARS)), SIMDELTA(SIMYEARS3))
);

*Calculate ord() for each simyear
ORD_IY(SIMYEARS) = 0;
LOOP(SIMYEARS,
ORD_IY(SIMYEARS) = SIMWEIGHT(SIMYEARS);
$ifi not yes==yes  ORD_IY(SIMYEARS) = SUM(SIMYEARS3$(ORD(SIMYEARS3) <= ORD(SIMYEARS)), SIMDELTA(SIMYEARS3))
);


* Checks:
ISCALAR1=1;
IF((CARD(SIMYEARS) > CARD(Y)),
ISCALAR1=0;
PUT "ERROR in SIMDELTA for BB4: (CARD(SIMYEARS) > CARD(Y)). No Balbase4 model will be generated" / /;
);
IF((SUM(SIMYEARS,SIMDELTA(SIMYEARS)) > CARD(Y)-1),
ISCALAR1=0;
      put "ERROR in SIMDELTA for BB4: The number of model years (cf. SIMYEARS) and the distance (cf. SIMDELTA) between them in Balbase4 is so large that no Balbase4 model will be generated."/;
);


IF(ISCALAR1,
LOOP(YALIAS$((CARD(YALIAS)-ORD(YALIAS) GE (SUM(SIMYEARS, SIMDELTA(SIMYEARS))))),

* -----------------------------------------------------------------------------
* Calculate ORD_IY, and subsets of Y:
* IY411: the years in the present Balbase4 model
* IY410: IY411 except last year.
* IY401: IY411 except first year.
* IY4FIRST(YALIAS): first year in IY411;
* -----------------------------------------------------------------------------

ORD_YALIAS = ORD(YALIAS);  /* The present first-year's ord() in set YALIAS */
YVALUE_YALIAS = YVALUE(YALIAS);

LOOP(SIMYEARS,
   IF((ORD_IY(SIMYEARS) + 1 <= CARD(Y)-(CARD(SIMYEARS)-ORD(SIMYEARS))),
     ORD_IY(SIMYEARS) = ORD_IY(SIMYEARS) + 1;
   ELSE
     ORD_IY(SIMYEARS) = CARD(Y)-(CARD(SIMYEARS)-ORD(SIMYEARS))
   );
);

IY411(Y) = NO;
LOOP((SIMYEARS, Y)$(ORD_IY(SIMYEARS) = ORD(Y)),
   IY411(Y)=yes;
);
IY410(Y) = NO;
LOOP((SIMYEARS, Y)$((ORD_IY(SIMYEARS) = ORD(Y)) AND (ORD(SIMYEARS) < CARD(SIMYEARS))),
   IY410(Y)=yes;
);
IY401(Y) = NO;
LOOP((SIMYEARS, Y)$((ORD_IY(SIMYEARS) = ORD(Y)) AND (ORD(SIMYEARS) > 1)),
   IY401(Y)=yes;
);

IY4FIRST(Y)=IY411(Y)-IY401(Y);

* Print:
PUT "Balbase4 model number " (ord(YALIAS)):2:0 " is formulated over the following years: ";  LOOP(IY411, PUT IY411.TL:6); PUT / /;

);
);


putclose  BB4overview;
