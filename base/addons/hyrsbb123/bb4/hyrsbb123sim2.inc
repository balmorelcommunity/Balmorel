* File HYRSBB123sim2.inc for the Balmorel model.
* For use with addon HYRSBB123.
* Included into bb123.sim before SOLVE BALBASE3 statement, inside the loop over seasons.

* Set values relative to the possible hydro use reletive to BB1/BB2:


ISCALAR1 = 0.1; !! Positive. Defines the largest individual increment, as share of the hydro power used in the BB1/BB2 solution.
VIHYRSBB12DELTAMHW.UP(IA,IHYRSBB12DELTASET) =  IHYRSBB123G_Y(IA,IS3LOOPSET)*ISCALAR1*ORD(IHYRSBB12DELTASET)/CARD(IHYRSBB12DELTASET);   !! Increments get larger with increased hydro use
VIHYRSBB12DELTAMHW.UP(IA,IHYRSBB12DELTASET)$(ORD(IHYRSBB12DELTASET) EQ CARD(IHYRSBB12DELTASET)) = INF;                                 !! No limit, to ensure feasibility in equation QWATERVOL

* Water Values:
ISCALAR1 = 2.0; !! Positive. With e.g. 2.0 the increments (above the BB1 values) on the Water Values will be doubled for each step, to reach a maximum of 2 times the BB1 values.
ISCALAR2=POWER(1/ISCALAR1,CARD(IHYRSBB12DELTASET));
ISCALAR3=1.0;  !! Additional increase may be attained by increasing ISCALAR3 above 1.0.
LOOP(IHYRSBB12DELTASET,
   ISCALAR2=ISCALAR2*ISCALAR1;
   IHYRSBB123EXTRAVAL(IA,IS3LOOPSET,IHYRSBB12DELTASET) = IWATERVAL_Y(IA,IS3LOOPSET)*ISCALAR3*(1+ISCALAR2);
);





