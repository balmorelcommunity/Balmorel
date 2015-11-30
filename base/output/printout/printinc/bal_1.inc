* File: bal_1.inc

* Modified last time: 29-05-2002 by (rus), 2003.08.07 (hrv), 16-02-2004 (ld), 20060328(hr)

* This file will print a table containing a energy balance for each country




* -----------------------------------------------------------------------------

PUT bal_1;

* First print file headings:

if ((bal_1.pw LT 32000),
bal_1.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "bal_1.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;

PUT "Energy balance" //;
PUT "Units: GWh" //;




);

* End of file headings.

bal_1.LJ = 1;
PUT "Energy balance for "PUT Y.TL:4:0; PUT "                          " ; LOOP(C, PUT C.TL:12) ;PUT /;
bal_1.LJ = 2;

PUT "Total electricity generation (excl. heat pumps)  " ; LOOP(C, PUT ( EZGqCY(C)*IOF0001):12:0 ; ); PUT /;
PUT " - from old technologies                         " ; LOOP(C, PUT ( EZGOqCY(C)*IOF0001):12:0 ; ); PUT /;
PUT " - from new technologies                         " ; LOOP(C, PUT ( EZGNqCY(C)*IOF0001):12:0 ; ); PUT /;
PUT "Consumption for heat pumps                       " ; LOOP(C, PUT (-EZG13qCY(C)*IOF0001):12:0 ; )PUT /;       /*sarah*/
PUT " - from old technologies                         " ; LOOP(C, PUT (-EZGO13qCY(C)*IOF0001):12:0 ; )PUT /;       /*sarah*/
PUT " - from new technologies                         " ; LOOP(C, PUT (-EZGN13qCY(C)*IOF0001):12:0 ; )PUT /;       /*sarah*/
PUT "Export(-) & import (+) with third countries      " ; LOOP(C, PUT ( EX3qCY(C)*IOF0001):12:0 ; )PUT /;
PUT "Export to other countries                        " ; LOOP(C, PUT ( EX1qCY(C)*IOF0001):12:0 ; )PUT /;
PUT "Import from other countries                      " ; LOOP(C, PUT ( EX2qCY(C)*IOF0001):12:0 ; )PUT /;
PUT "Transmission loss                                " ; LOOP(C, PUT ( EXLqCY(C)*IOF0001):12:0 ; )PUT /;
PUT "Distribution loss                                " ; LOOP(C, PUT ( ELqCY(C)*IOF0001):12:0 ; )PUT /;
PUT "Electricity demand                               " ; LOOP(C, PUT ( EDqCY(C)*IOF0001):12:0 ; ); PUT //;

PUT "Total heat generation                            " ; LOOP(C, PUT ( HZGqCY(C)*IOF0001):12:0 ; ); PUT /;
PUT " - from old technologies                         " ; LOOP(C, PUT ( HZGOqCY(C)*IOF0001):12:0 ; ); PUT /;
PUT " - from new technologies                         " ; LOOP(C, PUT ( HZGNqCY(C)*IOF0001):12:0 ; ); PUT /;
PUT "Distribution loss                                " ; LOOP(C, PUT ( HLqCY(C)*IOF0001):12:0 ; )PUT /;
PUT "Heat demand                                      " ; LOOP(C, PUT ( HDqCY(C)*IOF0001):12:0 ; ); PUT //;

* PUT "Heat consumption                      " ; LOOP((IA,S,T, DHF), PUT ( VDHF_T.L(IA,S,T,DHF):12:0 ; PUT //;
