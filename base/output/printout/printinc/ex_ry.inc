* File: ex_ry.inc

* Modified last time: 10-06-2002 (rus), 16-02-2004 (ld), 20060328(hr)

* This file will print the annual electricity export from each region,
* plus the transmission losses.



* -----------------------------------------------------------------------------

PUT ex_ry;

* First print headings:

if ((ex_ry.pw LT 32000),
ex_ry.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "ex_ry.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

PUT "Annual electricity export and import by region" //;

PUT "Units: GWh" //;

);

* End of file headings.
* ------------------------------------------------------------------------------------

* -----------------------------------------------------------------------------

ex_ry.LJ = 1;
PUT Y.TL:4:0; PUT "        " ; LOOP(IR, PUT IR.TL:12) ; PUT /;
ex_ry.LJ = 2;

PUT "Export      " ; LOOP(IR, PUT ((EX1qRY(IR))*IOF0001):12:0) ; PUT /;
PUT "Import      " ; LOOP(IR, PUT ((EX2qRY(IR))*IOF0001):12:0) ; PUT /;
PUT "Losses      " ; LOOP(IR, PUT ((EXLqRY(IR))*IOF0001):12:0) ; PUT //;
