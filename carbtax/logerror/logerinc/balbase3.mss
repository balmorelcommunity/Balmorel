* File balbase3.mss
*-------------------------------------------------------------------------------

* This file is part of the BALMOREL model.
* File last time modified 2005.11.20 (hr), 20080414(hr), 20120914(hr), 20150304(hr)


* This file will print the model and solver status, the objective value, etc.,
* for the model BALBASE3 for each season solved



Put logfile;

* Note: The below text: "Some Balmorel errors" is a keyword for communication with the BUI. Do not change.
IF((ORD(Y) EQ 1),
IF ((ERRCOUNT2 EQ 0),
PUT "No obvious Balmorel errors detected in the input data before simulation."
ELSE
PUT "Some Balmorel errors were detected in the input data before simulation." " See the file errors.out." //;
));


IF(((ORD(Y) EQ 1) AND (ORD(IS3LOOPSET) EQ 1)),
  PUT "Solver status of the BALBASE3 model each season in the simulation" //;
     PUT CARD(Y):4:0 " years and " CARD(IS3LOOPSET):4:0 " seasons to be simulated."  //;

  PUT "Year Season   Model status returned     " ;
  PUT "Solver status returned          " ;
  PUT "Obj. fct. value  " ;
  PUT "Iter. used " " No of infeas" " No of nonopt"PUT /;

  PUT "              (now to first SOLVE statement)" /;

);

/*
IF((ORD(IS3LOOPSET) EQ 1),
  IF((CARD(IS3LOOPSET) GE 1),
  PUT "              (now to first SOLVE statement)" /;
));
*/

* Note: The below text: "Some Balmorel errors" is a keyword for communication with the BUI. Do not change.
IF((ERRCOUNT3 GT 0),
PUT "       Some Balmorel errors were detected before optimisation of year " Y.TL:4". See the file errors.out." /;
);


PUT Y.TL:5 "  " IS3LOOPSET.TL:6 ;
PUT$(BALBASE3.MODELSTAT EQ 1)  " Optimal                     ";
PUT$(BALBASE3.MODELSTAT EQ 2)  " Locally optimal             ";
PUT$(BALBASE3.MODELSTAT EQ 3)  " Unbounded                   ";
PUT$(BALBASE3.MODELSTAT EQ 4)  " Infeasible                  ";
PUT$(BALBASE3.MODELSTAT EQ 5)  " Locally infeasible          ";
PUT$(BALBASE3.MODELSTAT EQ 6)  " Intermediate infeasible     ";
PUT$(BALBASE3.MODELSTAT EQ 7)  " Intermediate nonoptimal     ";
PUT$(BALBASE3.MODELSTAT EQ 8)  " Integer solution            ";
PUT$(BALBASE3.MODELSTAT EQ 9)  " Intermediate non-integer    ";
PUT$(BALBASE3.MODELSTAT EQ 10) " Integer infeasible          ";
PUT$(BALBASE3.MODELSTAT EQ 12) " Error unknown               ";
PUT$(BALBASE3.MODELSTAT EQ 13) " Error no solution           ";
PUT$(BALBASE3.MODELSTAT EQ 14) " No solution returned        ";
PUT$(BALBASE3.MODELSTAT EQ 15) " Solved unique               ";
PUT$(BALBASE3.MODELSTAT EQ 16) " Solved                      ";
PUT$(BALBASE3.MODELSTAT EQ 17) " Solved singular             ";
PUT$(BALBASE3.MODELSTAT EQ 18) " Unbounded no solution       ";
PUT$(BALBASE3.MODELSTAT EQ 19) " Infeasible no solution      ";
PUT$(BALBASE3.MODELSTAT GE 20) " Error no. " BALBASE3.MODELSTAT:3:0 ", consult GAMS documentation for details about MODELSTAT." /;

PUT$(BALBASE3.SOLVESTAT EQ 1)  " Normal completion           ";
PUT$(BALBASE3.SOLVESTAT EQ 2)  " Max iterations reached      ";
PUT$(BALBASE3.SOLVESTAT EQ 3)  " Resource limit reached      ";
PUT$(BALBASE3.SOLVESTAT GE 4)  " Solver quit or terminated - error no.  " BALBASE3.SOLVESTAT:3:0 ", consult GAMS documentation for details about SOLVESTAT." /;
;

PUT VOBJ.L:16:2 " ";
PUT BALBASE3.ITERUSD:11:0 " " ;
PUT BALBASE3.NUMINFES:12:0 " " ;
PUT BALBASE3.NUMNOPT:13:0 /;



* Note: The below text: "Some Balmorel errors" is a keyword for communication with the BUI. Do not change.
IF((ERRCOUNT4 GT 0),
PUT "       Some Balmorel errors were detected after optimisation of year " Y.TL:4". See the file errors.out." /;
);

IF(((ORD(IS3LOOPSET) LT CARD(IS3LOOPSET)) OR (ORD(Y) LT CARD(Y))),
  PUT "              (now to next SOLVE statement)" /;
);
