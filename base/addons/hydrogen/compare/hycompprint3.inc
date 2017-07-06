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
                                                     IOF1000000*QH2EQ.m(IR,S,T)*(
                                                           SUM(IAGK_Y(IA,IGETOH2)$RRRAAA(IR,IA),VGH2_T.l(IA,IGETOH2,S,T))
                                                          +SUM(IAGKN(IA,IGETOH2) $RRRAAA(IR,IA),VGH2N_T.l(IA,IGETOH2,S,T))
                                                          +SUM(IAGK_Y(IA,IGCH4TOH2)$RRRAAA(IR,IA),VGH2_T.l(IA,IGCH4TOH2,S,T))
                                                          +SUM(IAGKN(IA,IGCH4TOH2) $RRRAAA(IR,IA),VGH2N_T.l(IA,IGCH4TOH2,S,T))
                                                          +SUM(IAGK_Y(IA,IGH2STO)$RRRAAA(IR,IA),VGH2_T.l(IA,IGH2STO,S,T))
                                                          +SUM(IAGKN(IA,IGH2STO) $RRRAAA(IR,IA),VGH2N_T.l(IA,IGH2STO,S,T))
                                                          -SUM((IA,IGH2STO)$((IAGK_Y(IA,IGH2STO) or IAGKN(IA,IGH2STO)) and RRRAAA(IR,IA)),VH2STOLOADT.l(IA,IGH2STO,S,T))
                                                         )
                                                         )/IOF1000000;

* Cost of hydrogen as fuel for district heating.
         h2_ehfuelC(Y,C)     =eps+   OMONEY*SUM((IR,S,T)$CCCRRR(C,IR),
                                               IOF1000000*QH2EQ.m(IR,S,T)*(
                                                    +SUM(IAGK_Y(IA,IGH2FUEL)$RRRAAA(IR,IA),VGE_T.l(IA,IGH2FUEL,S,T)/GDATA(IGH2FUEL,'GDFE'))
                                                    +SUM(IAGKN(IA,IGH2FUEL)$RRRAAA(IR,IA),VGEN_T.l(IA,IGH2FUEL,S,T)/GDATA(IGH2FUEL,'GDFE'))
                                                         )
                                                         );


