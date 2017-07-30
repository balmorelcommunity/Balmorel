* File hycompprint3.INC.
* This file is part of the new welfare calculation module for the Balmorel model.
* This is an add on for hydrogen
* Author: Lars Bregnbæk
* Revision: 1.0 LB

* This file contains routines for handling of intermediate information that may
* be usefull output.


*===============================================================================
*                Overview
*===============================================================================



*===============================================================================
*                Overview end
*===============================================================================

* Revenue from sale of hydrogen. Hydrogen storage assets are assumed owned by hydrogen generators.
         h2_rev(Y,C)          =eps+   OMONEY*SUM((IR,S,T)$CCCRRR(C,IR),
                                                     IOF1000000*QHYDROGEN_EQ.m(IR,S,T)*(
                                                           SUM(IAGK_Y(IA,IHYDROGEN_GETOH2)$RRRAAA(IR,IA),VHYDROGEN_GH2_T.l(IA,IHYDROGEN_GETOH2,S,T))
                                                          +SUM(IAGKN(IA,IHYDROGEN_GETOH2) $RRRAAA(IR,IA),VHYDROGEN_GH2N_T.l(IA,IHYDROGEN_GETOH2,S,T))
                                                          +SUM(IAGK_Y(IA,IHYDROGEN_GCH4TOH2)$RRRAAA(IR,IA),VHYDROGEN_GH2_T.l(IA,IHYDROGEN_GCH4TOH2,S,T))
                                                          +SUM(IAGKN(IA,IHYDROGEN_GCH4TOH2) $RRRAAA(IR,IA),VHYDROGEN_GH2N_T.l(IA,IHYDROGEN_GCH4TOH2,S,T))
                                                          +SUM(IAGK_Y(IA,IHYDROGEN_GH2STO)$RRRAAA(IR,IA),VHYDROGEN_GH2_T.l(IA,IHYDROGEN_GH2STO,S,T))
                                                          +SUM(IAGKN(IA,IHYDROGEN_GH2STO) $RRRAAA(IR,IA),VHYDROGEN_GH2N_T.l(IA,IHYDROGEN_GH2STO,S,T))
                                                          -SUM((IA,IHYDROGEN_GH2STO)$((IAGK_Y(IA,IHYDROGEN_GH2STO) or IAGKN(IA,IHYDROGEN_GH2STO)) and RRRAAA(IR,IA)),VHYDROGEN_STOLOADT.l(IA,IHYDROGEN_GH2STO,S,T))
                                                         )
                                                         )/IOF1000000;

* Cost of hydrogen as fuel for district heating.
         h2_ehfuelC(Y,C)     =eps+   OMONEY*SUM((IR,S,T)$CCCRRR(C,IR),
                                               IOF1000000*QHYDROGEN_EQ.m(IR,S,T)*(
                                                    +SUM(IAGK_Y(IA,IHYDROGEN_GH2FUEL)$RRRAAA(IR,IA),VGE_T.l(IA,IHYDROGEN_GH2FUEL,S,T)/GDATA(IHYDROGEN_GH2FUEL,'GDFE'))
                                                    +SUM(IAGKN(IA,IHYDROGEN_GH2FUEL)$RRRAAA(IR,IA),VGEN_T.l(IA,IHYDROGEN_GH2FUEL,S,T)/GDATA(IHYDROGEN_GH2FUEL,'GDFE'))
                                                         )
                                                         );


