* File: priceadd_sc.inc containing the marginal value of equation FIXED_TRANS
* in the year-model used as price add to the price interface in the week model

* Modified last time: 09-02-2005 by (peme)

* The output will not print nicely if CARD(T) is large.

* -----------------------------------------------------------------------------

PUT priceadd_sc;

$ontext
* First print headings:
if ((priceadd_sc.PW LT 32000),
priceadd_sc.PW = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "priceadd_sc.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

PUT "* Marginal value FIXED_TRANS" /;
);

* End of headings.

* -----------------------------------------------------------------------------

   IF((sum((SCG,SCA),SCGKFX(SCG,SCA,SC)) GT 0),
      PUT ' with an extra capacity of '
   );

   Loop((SCG,SCA)$SCGKFX(SCG,SCA,SC),
      PUT SCGKFX(SCG,SCA,SC):0:0 ' MW ' SCG.TL:0 ' in area ' SCA.TL:0;
   );

   IF((SUM((SCRE,SCRI),SCXKINI(SCRE,SCRI,SC)) GT 0),
      PUT  '.'/ 'The transmission between '
   );
   Loop((SCRE,SCRI)$(SCXKINI(SCRE,SCRI,SC) AND (ORD(SCRE) LE ORD(SCRI))),
      PUT SCRE.TL:0 ' and ' SCRI.TL:0 ' is equal to ' SCXKINI(SCRE,SCRI,SC):4:0 ' MW';
   );

   IF((SCM_POL('TAX_CO2',SC) GT 0),
      PUT  '.'/ 'The CO2 tax has value 'SCM_POL('TAX_CO2',SC):0:2 ' EUR90/t CO2' ;
   );

PUT //;
$offtext

Loop(X3VSTEP,
   PUT SC.TL:6,(1e6*FIXED_TRANS.M):0:4/;
);
