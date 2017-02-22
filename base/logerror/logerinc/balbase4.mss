* File balbase4.mss
*-------------------------------------------------------------------------------

* This file is part of the BALMOREL model, version 3.03  (xx 2014).
* File last time modified 20150302(hr), 20160810(hr).


* This file will print the model and solver status, the objective value, etc.,
* for the model BALBASE4 for each year solved

* This file will print the solver status, the objective value, etc.,
* for each year solved.


Put logfile

* ------------------------------------------------------------------------------
* General information ----------------------------------------------------------
* ------------------------------------------------------------------------------

PUT "* ------------------------------------------------------------------------------" / ;

PUT / "Since BB4 is presently in developments phase, not all addons are reimplemented for this, and those that are may be only preliminary, so be careful." ;

PUT / "* ------------------------------------------------------------------------------" / /;


* ------------------------------------------------------------------------------
* End: General information -----------------------------------------------------
* ------------------------------------------------------------------------------


* ------------------------------------------------------------------------------
* BB4 specific -----------------------------------------------------------------
* ------------------------------------------------------------------------------



* Note: The below text: "Some Balmorel errors" is a keyword for communication with the BUI. Do not change.

IF((ORD(IYALIAS) EQ 1),
IF ((ERRCOUNT2 EQ 0),
PUT "No obvious Balmorel errors detected in the input data before simulation." //
ELSE
PUT "Some Balmorel errors were detected in the input data before simulation." " See the file errors.out."//
));




IF((ORD(IYALIAS) EQ 1),
  PUT "Solver status of the BALBASE4 model" //;
  PUT CARD(IYALIAS):4:0 ", at most, models to be solved."  /;
  PUT "See details of input data in output\inputout\inputout.out (if associated option is set), and in particular for BB4 see output\inputout\BB4overview.out." //;


  PUT "Year    Model status returned     " ;
  PUT "Solver status returned          " ;
  PUT "Obj. fct. value  " ;
  PUT "Iter. used " " No of infeas" " No of nonopt"PUT /;
);

IF((ORD(IYALIAS) EQ 1),
  IF((CARD(IYALIAS) GE 1),
  PUT "        (Now to first SOLVE statement)" /;
));


* Note: The below text: "Some Balmorel errors" is a keyword for communication with the BUI. Do not change.
IF((ERRCOUNT3 GT 0),
PUT "       Some Balmorel errors were detected before optimisation of year " IYALIAS.TL:4". See the file errors.out." /;
);


PUT IYALIAS.TL:5 "  " ;
PUT$(BALBASE4.MODELSTAT EQ 1)  " Optimal                     ";
PUT$(BALBASE4.MODELSTAT EQ 2)  " Locally optimal             ";
PUT$(BALBASE4.MODELSTAT EQ 3)  " Unbounded                   ";
PUT$(BALBASE4.MODELSTAT EQ 4)  " Infeasible                  ";
PUT$(BALBASE4.MODELSTAT EQ 5)  " Locally infeasible          ";
PUT$(BALBASE4.MODELSTAT EQ 6)  " Intermediate infeasible     ";
PUT$(BALBASE4.MODELSTAT EQ 7)  " Intermediate nonoptimal     ";
PUT$(BALBASE4.MODELSTAT EQ 8)  " Integer solution            ";
PUT$(BALBASE4.MODELSTAT EQ 9)  " Intermediate non-integer    ";
PUT$(BALBASE4.MODELSTAT EQ 10) " Integer infeasible          ";
PUT$(BALBASE4.MODELSTAT EQ 12) " Error unknown               ";
PUT$(BALBASE4.MODELSTAT EQ 13) " Error no solution           ";
PUT$(BALBASE4.MODELSTAT EQ 14) " No solution returned        ";
PUT$(BALBASE4.MODELSTAT EQ 15) " Solved unique               ";
PUT$(BALBASE4.MODELSTAT EQ 16) " Solved                      ";
PUT$(BALBASE4.MODELSTAT EQ 17) " Solved singular             ";
PUT$(BALBASE4.MODELSTAT EQ 18) " Unbounded no solution       ";
PUT$(BALBASE4.MODELSTAT EQ 19) " Infeasible no solution      ";
PUT$(BALBASE4.MODELSTAT GE 20) " Error no. " BALBASE4.MODELSTAT:3:0 " ";

PUT$(BALBASE4.SOLVESTAT EQ 1)  " Normal completion           ";
PUT$(BALBASE4.SOLVESTAT EQ 2)  " Max iterations reached      ";
PUT$(BALBASE4.SOLVESTAT EQ 3)  " Resource limit reached      ";
PUT$(BALBASE4.SOLVESTAT GE 4)  " Non optimal - error no.  "
BALBASE4.SOLVESTAT:3:0 ;

PUT VOBJ.L:16:2 " ";
PUT BALBASE4.ITERUSD:11:0 " " ;
PUT BALBASE4.NUMINFES:12:0 " " ;
PUT BALBASE4.NUMNOPT:13:0 /;

* ------------------------------------------------------------------------------
* End: BB4 specific ------------------------------------------------------------
* ------------------------------------------------------------------------------


* Note: The below text: "Some Balmorel errors" is a keyword for communication with the BUI. Do not change.
IF((ERRCOUNT4 GT 0),
PUT "       Some Balmorel errors were detected after optimisation from year " IYALIAS.TL:4" in Balbase4. See the file errors.out." /;
);

IF((ORD(IYALIAS) LT CARD(IYALIAS)),
   PUT "        Model was over years ";
   LOOP(IY411, PUT IY411.TL:6;);   PUT /;
);
