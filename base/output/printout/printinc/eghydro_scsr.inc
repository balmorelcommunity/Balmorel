* File: eghydro_scsr.inc

* Modified last time: 01-02-2002 by (rus), 20060328(hr)

* This file will print a table containing annnual net electricity generation
* from all hydrotechnologies in each region for each scenario.

* -----------------------------------------------------------------------------

PUT eghydro_scsr;

if ((eghydro_scsr.PW LT 32000),
eghydro_scsr.PW = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "eghydro_scsrt.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT '*"Electricity production MWh on waterpower units during each season"'//;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   /;
);

* End of headings.
* ------------------------------------------------------------------------------------
* If scenarios (i.e., more than base case) print scenario heading:
IF((CARD(SCENARIO) GT 1),
PUT /"*==============================================================================="/;
PUT "*       "   SCENARIO.TL "      " SCENARIO.TE(SCENARIO) /;
PUT "*==============================================================================="//;
);
* End of scenario heading
* ------------------------------------------------------------------------------------

* -----------------------------------------------------------------------------

eghydro_scsr.LJ = 2;

* The following include production for water only

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

* In the following printstatement it is neccescary that the scenarioloops includes
* the first scenario in the SET SC.

*PEME print the region headings in week.sim to avoid that the scenarioloops
* should include the first scenario in the SET sc.
$ontext
IF((ORD(SC) EQ 1),
*PUT 'PARAMETER HYFXRW(SC,WWW,R)'/;
  PUT '                    ';
  LOOP(IR,
    PUT IR.TL:12
  );
  PUT /;
);
$offtext

LOOP((S,WforPrint)$(ORD(WforPrint) EQ ORD(S)),
  PUT SC.TL:5 '.' WforPrint.TL:6;
  LOOP(IR,
    PUT ( sum(IWATER(G),EGqRS(IR,G,S))):12:0 ;
  );
  PUT /;
);
