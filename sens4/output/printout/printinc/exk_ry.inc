* File: exk_ry.inc

* Modified last time: 01-02-2002 (rus), 16-02-2004 (ld),20060328(hr)

* This file will print the transmission capacities between each region




* -----------------------------------------------------------------------------

PUT exk_ry;

* First print headings:

if ((exk_ry.pw LT 32000),
exk_ry.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "exk_ry.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   /;

PUT "Transmission capacities (old plus new) by the end of the year"  //;

PUT "Units: MW" //;

);

* End of file headings.
* ------------------------------------------------------------------------------------

* -----------------------------------------------------------------------------

exk_ry.LJ = 1;
PUT Y.TL:4:0; PUT "        " ; LOOP(IR, PUT IR.TL:12); PUT  /;
exk_ry.LJ = 2;

LOOP(IRE,
  PUT  IRE.TL:12 ;
  LOOP(IRI, PUT (IXKINI_Y(IRE,IRI)+VXKN.L(IRI,IRE)+VXKN.L(IRE,IRI)):12:2); PUT /;
);

PUT /;
