* File: eflex_rst.inc as modifed for the year simulation

* Modified last time: 08-02-2005 by (peme)

* NB: The file is NOT finished!


* This file will print a table containing the amount of flexible consumption activated
* by (R,S,T).
* The output will not print nicely if CARD(T) is large.

* -----------------------------------------------------------------------------

PUT eflex_rst;


* First print headings:

if ((eflex_rst.PW LT 32000),
eflex_rst.PW = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "eflex_rst.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;

PUT "* Amount of flexible electricity consumption activated for each S and T" /;
);

* End of headings.

* -----------------------------------------------------------------------------

PUT / '*Scenario ' SC.TL:0:5 ' simulating year ' SCYVALUE(SC):4:0 ;
PUT ' as a hydrological ';
IF((SCHYDNWY(SC) EQ 1),
PUT  'wet year.';
);
IF((SCHYDNWY(SC) EQ 2),
PUT  'normal year.';
);
IF((SCHYDNWY(SC) EQ 3),
PUT  'dry year.';
);

IF((sum((SCG,SCA),SCGKFX(SCG,SCA,SC)) GT 0),
PUT ' with an extra capacity of '
);

Loop((SCG,SCA)$SCGKFX(SCG,SCA,SC),
   PUT SCGKFX(SCG,SCA,SC):0:0 ' MW ' SCG.TL:0 ' in area ' SCA.TL:0;
);

$ontext
IF((SUM((SCRE,SCRI),SCXKINI(SCRE,SCRI,SC)) GT 0),
PUT  '.'/ '*The transmission between '
);
Loop((SCRE,SCRI)$(SCXKINI(SCRE,SCRI,SC) AND (ORD(SCRE) LE ORD(SCRI))),
   PUT SCRE.TL:0 ' and ' SCRI.TL:0 ' is equal to ' SCXKINI(SCRE,SCRI,SC):4:0 ' MW';
);
$offtext
IF((SCM_POL('TAX_CO2',SC) GT 0),
PUT  '.'/ '*The CO2 tax has value 'SCM_POL('TAX_CO2',SC):0:2 ' EUR90/t CO2' ;
);

PUT //;

PUT '                      ';
LOOP(IR,
  eflex_rst.LJ = 2;
  PUT IR.TL:12 ;
);
PUT /;

LOOP(T$ISTT(T),
  eflex_rst.LJ = 1;
  LOOP(S$ISTS(S),
    PUT SC.TL:5 '.' S.TL:3 '.' T.TL:3 '.'
    LOOP(IR,
      PUT SUM(DEF_D3,VDEF_T.l(IR,S,T,DEF_D3)):12:4;
    );
    PUT/;
  );
);
*PUT '  '/;
