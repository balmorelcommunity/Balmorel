* File: eg3_CY.INC

* Modified last time: 01-02-2002 by (rus), 20060328(hr)

* This file will print a table containing annnual net electricity generation
* from all technologies in each country.
* (Incl. the negative electricity generation for heat pumps)


* -----------------------------------------------------------------------------

PUT EG3_CY;

if ((EG3_CY.PW LT 32000),
EG3_CY.PW = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "eg3_cy.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT '"Electricity production (GWh and MW) "'//;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;
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

eg3_CY.LJ = 2;
PUT Y.TL:6:0; PUT "                        ";

eg3_CY.LJ = 1;
LOOP(C, PUT C.TL:12) ;PUT "      NORDEL" PUT /;

eg3_CY.LJ = 2;

* The following include production for all fueltypes
/*
PUT "TOTAL       " ; LOOP(C, PUT ( sum(G,EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,G),EGqCY(C,G)/1000)):12:0 ; PUT //;

PUT "IMPORT      " ; LOOP(C, PUT ( EX2qCY(C)/1000):12:0 ; ); PUT ( SUM(C,EX2qCY(C)/1000)):12:0 ; PUT /;
PUT "NUCLEAR     " ; LOOP(C, PUT ( sum(INUCLEAR(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,INUCLEAR(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "NAT_GAS     " ; LOOP(C, PUT ( sum(INAT_GAS(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,INAT_GAS(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "COAL        " ; LOOP(C, PUT ( sum(ICOAL(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,ICOAL(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "LIGNITE     " , LOOP(C, PUT ( sum(ILIGNITE(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,ILIGNITE(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "FUELOIL     " ; LOOP(C, PUT ( sum(IFUELOIL(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,IFUELOIL(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "LIGHTOIL    " ; LOOP(C, PUT ( sum(ILIGHTOIL(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,ILIGHTOIL(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "ORIMULSION  " ; LOOP(C, PUT ( sum(IORIMULSION(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,IORIMULSION(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "SHALE       " ; LOOP(C, PUT ( sum(ISHALE(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,ISHALE(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "PEAT        " ; LOOP(C, PUT ( sum(IPEAT(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,IPEAT(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;

PUT "STRAW       " ; LOOP(C, PUT ( sum(ISTRAW(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,ISTRAW(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "WOOD        " ; LOOP(C, PUT ( sum(IWOOD(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,IWOOD(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "WOOD_WASTE  " ; LOOP(C, PUT ( sum(IWOOD_WASTE(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,IWOOD_WASTE(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "WIND        " ; LOOP(C, PUT ( sum(IWIND(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,IWIND(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "WATER       " ; LOOP(C, PUT ( sum(IWATER(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,IWATER(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "SUN         " ; LOOP(C, PUT ( sum(ISUN(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,ISUN(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;

PUT "EXPORT(-)   " ; LOOP(C, PUT ( EX3qCY(C)/1000+EX1qCY(C)/1000):12:0 ; ); PUT ( SUM(C,EX1qCY(C)/1000)):12:0 ; PUT ///;
*PUT "3 COUNTRIES " ; LOOP(C, PUT ( EX3qCY(C)/1000+EX1qCY(C)/1000):12:0 ; ); PUT ( SUM(C,EX1qCY(C)/1000)):12:0 ; PUT ///;
*/

* The following include production for NORDEL fueltypes

PUT "TOTAL                       " ; LOOP(C, PUT ( sum(G,EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,G),EGqCY(C,G)/1000)):12:0 ; PUT //;
PUT "NORDIC IMPORT               " ; LOOP(C, PUT ( EX2qCY(C)/1000):12:0 ; ); PUT ( SUM(C,EX2qCY(C)/1000)):12:0 ; PUT /;
PUT "ELECTRIC                    " ; LOOP(C, PUT ( sum(IELECTRIC(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,IELECTRIC(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "MUNI_WASTE                  " ; LOOP(C, PUT ( sum(IMUNI_WASTE(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,IMUNI_WASTE(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "BIOMASS                     " ; LOOP(C, PUT ( sum(IBIOMASS(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,IBIOMASS(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "NAT_GAS                     " ; LOOP(C, PUT ( sum(INAT_GAS(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,INAT_GAS(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "OIL                         " ; LOOP(C, PUT ( sum(IOIL(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,IOIL(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "COAL                        " ; LOOP(C, PUT ( sum(ICOAL(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,ICOAL(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "PEAT                        " ; LOOP(C, PUT ( sum(IPEAT(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,IPEAT(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "NUCLEAR                     " ; LOOP(C, PUT ( sum(INUCLEAR(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,INUCLEAR(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "WATER                       " ; LOOP(C, PUT ( sum(IWATER(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,IWATER(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "WIND                        " ; LOOP(C, PUT ( sum(IWIND(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,IWIND(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "NORDIC EXPORT               " ; LOOP(C, PUT ( -EX2qCY(C)/1000):12:0 ; ); PUT ( -SUM(C,EX2qCY(C)/1000)):12:0 ; PUT /;
PUT "EXCHANGE WITH THIRD COUNTRIES:             " ; PUT /;
PUT "NETTO IMPORT FIXED          " ; LOOP(C, PUT ( EX3qCY(C)/1000):12:0 ; ); PUT ( SUM(C,EX3qCY(C)/1000)):12:0 ; PUT /;
PUT "EXPORT PRICE DEPENDENT      " ; LOOP(C, PUT ( EX3qCY_Ex_P(C)/1000):12:0 ; ); PUT ( SUM(C,EX3qCY_Ex_P(C)/1000)):12:0 ; PUT /;
PUT "IMPORT PRICE DEPENDENT      " ; LOOP(C, PUT ( EX3qCY_Im_P(C)/1000):12:0 ; ); PUT ( SUM(C,EX3qCY_Im_P(C)/1000)):12:0 ; PUT /;
PUT "NET IMPORT PRICE DEPENDENT  " ; LOOP(C, PUT ( (EX3qCY_Im_P(C)-EX3qCY_Ex_P(C))/1000):12:0 ; ); PUT ( SUM(C,(EX3qCY_Im_P(C)-EX3qCY_Ex_P(C))/1000)):12:0 ; PUT ///;
