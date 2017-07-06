* File: ex_ry.inc

* Modified last time: 10-06-2002 (rus), 16-02-2004 (ld), 20060328(hr)

* This file will print the annual electricity export from each region,
* plus the transmission losses.



* -----------------------------------------------------------------------------

PUT ex_ry;

* First print headings:

if ((ex_ry.pw LT 32000),
ex_ry.pw = 32000;
PUT "Version:              " SYSTEM.TITLE /;
PUT "File name:            ex_ry.out" /;
PUT "Time-stamp:          '" SYSTEM.DATE " " SYSTEM.TIME "'" /;
PUT "Case-identification: '" OCASEID.TS "'" //;

PUT "Annual electricity export and import by region" //;

PUT "Units: GWh" //;

);

* End of file headings.
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

ex_ry.LJ = 1;
PUT Y.TL:4:0; PUT "        " ; LOOP(IR, PUT IR.TL:12) ; PUT /;
ex_ry.LJ = 2;

PUT "Export      " ; LOOP(IR, PUT ((EX1qRY(IR))*IOF0001):12:0) ; PUT /;
PUT "Import      " ; LOOP(IR, PUT ((EX2qRY(IR))*IOF0001):12:0) ; PUT /;
PUT "Losses      " ; LOOP(IR, PUT ((EXLqRY(IR))*IOF0001):12:0) ; PUT //;