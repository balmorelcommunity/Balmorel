* File: hp_at.INC

* Modified last time: 2005.11.18 (hr), 20060328(hr), 20080305(hr)

* This file will print a table containing the marginal heat generation
* price by (A,S,T). This quantity is here derives as the marginal
* value (shadow price) to equation QHEQ.
* The output will not print nicely if CARD(T) is large.

* -----------------------------------------------------------------------------


PUT hp_at;

* First print headings:

if ((hp_at.pw LT 32000),
hp_at.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "hp_at.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

PUT "Heat price for each (S,T)." /;
PUT "Currency: " OMONEY.TS "  with exchange rate to input currency: "  OMONEY:7:3  " ("OMONEY.TS"/EUR90)." /;
PUT "Units: "; PUT OMONEY.ts "/MWh" //;
);

* End of file headings.
* ------------------------------------------------------------------------------------
* ------------------------------------------------------------------------------------

* -----------------------------------------------------------------------------
* ------------------------------------------------------------------------------
* Horisontal printing of labels (S,T):
$if not %printSThorisontal% == yes $goto printSThorisontal_label1

LOOP(IA,
hp_aT.LJ = 2;
  PUT  Y.TL:6:0 "   "; PUT IA.TL:12;
hp_aT.LJ = 1;
LOOP(T, PUT T.TL:12 ); PUT /;
  LOOP(S,
    PUT "         " S.TL:12  ;
      LOOP(T,
        IF(IDH_T_Y(IA,S,T),
           PUT (OMONEY*IOF1_*QHEQ.M(IA,S,T)/IHOURSINST(S,T)):12:4;
        ELSE
           PUT " '(No gen.)'";
          )
       )PUT /; )

) PUT //;

* ------------------------------------------------------------------------------
* Vertical printing of labels (S,T):
$label printSThorisontal_label1
$if %printSThorisontal% == yes $goto printSThorisontal_label2

hp_aT.LJ = 2;
PUT  Y.TL:6:0 "                    ";
LOOP(IA,    PUT IA.TL:12; ); PUT /;



  LOOP((S,T),
    PUT S.TL:12 T.TL:12 ;
      LOOP(IA,
        IF(IDH_T_Y(IA,S,T),
           PUT (OMONEY*IOF1_*QHEQ.M(IA,S,T)/IHOURSINST(S,T)):12:4;
        ELSE
           PUT " '(No gen.)'";
          )
       ) PUT /; )

*)
PUT //;


$label printSThorisontal_label2
