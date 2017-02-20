* BB4overview.inc
* Created 200906xx (hr), 20150513(hr), last revised 20160810(hr).
*
* This file will print a short overview of input data characteristics of the BalBase4 model in Balmorel.


*FILE BB4overview /..\output\inputout\BB4overview.out/;
FILE BB4overview /..\logerror\BB4overview.out/;
put BB4overview "Overview of input data characteristics of the BalBase4 model in Balmorel.   " system.date "  " system.time /;
put "General overview of input data may be found in inputout.out" /;
put "The information printed here is valid only if the input is consistent, please verify this, e.g. see the errors.out file first." / / ;


put "Years to be represented in models are subsets of Y: "; LOOP(Y, PUT Y.TL:6 ); PUT / /;


IF((CARD(YMODEL) GT 1),
  PUT "Each Balbase4 model will have " (Card(YMODEL)):3:0 " years (implied by set YMODEL)."/ /;
  PUT "The number of years between a year and the preceding year represented in model Balbase4 (parameter YMODELDELTA) ('number' derived from ord(Y)):"  /;
  PUT "YMODELDELTA:    0";
  LOOP(YMODEL$(1 LT ORD(YMODEL)), PUT (YMODELDELTA(YMODEL)):3:0;);  PUT / /;
ELSE
  PUT "There is only one year in each Balbase4 model." PUT / /;
);

* hans: pt er dette blot kopi fra BB4.sim (med undtagelse af Check), skal internaliseres! 

* Calculate simweights for each simyear:
ALIAS(YMODEL, IYMODEL3);
LOOP(YMODEL,
  ISIMWEIGHT(YMODEL) = SUM(IYMODEL3$(ORD(IYMODEL3) <= ORD(YMODEL)), YMODELDELTA(IYMODEL3))
);

*Calculate ord() for each simyear
IORD_IY(YMODEL) = 0;
LOOP(YMODEL,
IORD_IY(YMODEL) = ISIMWEIGHT(YMODEL);
$ifi not yes==yes  IORD_IY(YMODEL) = SUM(IYMODEL3$(ORD(IYMODEL3) <= ORD(YMODEL)), YMODELDELTA(IYMODEL3))  !!  TODO!
);




* Checks:
ISCALAR1=1;
IF((CARD(YMODEL) > CARD(Y)),
ISCALAR1=0;
PUT "ERROR in YMODELDELTA for BB4: (CARD(YMODEL) > CARD(Y)). No Balbase4 model will be generated" / /;
);
IF((SUM(YMODEL,YMODELDELTA(YMODEL)) > CARD(Y)-1),
ISCALAR1=0;
      put "ERROR in YMODELDELTA for BB4: The number of model years (cf. YMODEL) and the distance (cf. YMODELDELTA) between them in Balbase4 is so large that no Balbase4 model will be generated."/;
);


IF(ISCALAR1,
ISCALAR3 = 0;
IFIRSTYEARNEXTBB4 = SUM(Y$(ORD(Y) EQ 1), YVALUE(Y));

* The following main loop, its $conditions and the assignments within the loop must be identical to what is found in the .sim file for Balbase4
*LOOP(IYALIAS$(((CARD(IYALIAS)-ORD(IYALIAS) GE (SUM(YMODEL$(ORD(YMODEL) GT 1), YMODELDELTA(YMODEL)))) AND (YVALUE(IYALIAS) GE IFIRSTYEARNEXTBB4))), !! ud test
LOOP(IYALIAS$(CARD(IYALIAS)-ORD(IYALIAS) GE (SUM(YMODEL$(ORD(YMODEL) GT 1), YMODELDELTA(YMODEL)))),

ISCALAR1 = 0;
LOOP(YMODEL,
  ISCALAR1 = ISCALAR1 + YMODELDELTA(YMODEL)$(ORD(YMODEL) GT 1);
  LOOP(IYALIAS44$(ORD(IYALIAS44) EQ (ORD(IYALIAS)+ISCALAR1)), IORD_IY(YMODEL) = ORD(IYALIAS44); );
);

IY411(Y) = NO;
LOOP((YMODEL, Y)$(IORD_IY(YMODEL) = ORD(Y)), IY411(Y)=yes;);

*YMODELDELTA('') = 2;

ISCALAR1 = 1;
LOOP(IY411$(ISCALAR1 EQ 1), ISCALAR2 = YVALUE(IY411); ISCALAR1 = 0;);
LOOP(IY402$(YVALUE(IY402) EQ ISCALAR2), IFIRSTYEARNEXTBB4 = ISCALAR2 + SUM(YMODEL$(ORD(YMODEL) EQ 1), YMODELDELTA(YMODEL)););

*ISCALAR1 = 1;  !! test  alternativ
*LOOP(IY411$(ISCALAR1 EQ 1), IFIRSTYEARNEXTBB4 = YVALUE(IY411); ISCALAR1 = 0;);  !! test  alternativ
*IFIRSTYEARNEXTBB4 = ISCALAR2;  !! test
*PUT "Next FIRSTYEAR  ", IFIRSTYEARNEXTBB4  "  eller? " IY411.ts;  !! test
*PUT "  Using YMODELDELTA from YMODEL " ,  (SUM(YMODEL$(ORD(YMODEL) EQ 1), YMODELDELTA(YMODEL)))   /     ;    !! test


ISCALAR3 = ISCALAR3 +1;
PUT "Balbase4 model number " ISCALAR3:2:0 " is formulated over the years: ";  LOOP(IY411, PUT IY411.TL:6); PUT / /;



); !! Main loop

IF((ISCALAR2 EQ 1),
  PUT "There is one BB4 model."//;
ELSE
  PUT "There are " ISCALAR3:2:0" BB4 models."//;
);
);

IF((CARD(AGKN) EQ 0),
  PUT "The model is run without endogenous investments in generation technologies." / /;
ELSE
  PUT "The model is run with endogenous investments in generation technologies." / /;
);
$ontext  Subject to option TransInvest - TODO
IF((CARD(XKN) EQ 0),
  PUT "The model is run without endogenous investments in transmission capacities." / /;
ELSE
  PUT "The model is run with endogenous investments in transmission capacities." / /;
);
$offtext

PUT "More information to be found in files logerror\logfile.out and logerror\errors.out." /;
putclose  BB4overview;
