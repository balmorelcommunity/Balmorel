* File HYRSBB123sim3.inc for the Balmorel model.
* For use with addon HYRSBB123.
* Included into bb123.sim after SOLVE BALBASE3 statement, inside the loop over seasons.


* Update accumulated hydro amounts used:

IHYRSBB123BB3GACCUM(IA)  = IHYRSBB123BB3GACCUM(IA)  + SUM(IGHYRS, SUM(T, (IHOURSINST(IS3LOOPSET,T) * VGE_T.L(IA,IGHYRS,IS3LOOPSET,T))$IAGK_Y(IA,IGHYRS) ));
IHYRSBB123BB12GACCUM(IA) = IHYRSBB123BB12GACCUM(IA) + HYRSG(Y,IA,IS3LOOPSET);


*hydroinflow(ia,IS3LOOPSET) =  IHYINF_S(IA,IS3LOOPSET) * SUM(IGHYRS$IAGK_Y(IA,IGHYRS), (IGKVACCTOY(IA,IGHYRS)+IGKFX_Y(IA,IGHYRS)));
*hydroinflow(ia,s) =           IHYINF_S(IA,S)          * SUM(IGHYRS$IAGK_Y(IA,IGHYRS), (IGKVACCTOY(IA,IGHYRS)+IGKFX_Y(IA,IGHYRS)));


* Set volume deviation relative to BB1/BB2for the next season:
* The following adjustment distributes the hydro energy deviation evenly over the remaining seasons.
* It may need adaptation to specific circumstancs, and may also be generally improved. But it is simple.
* Todo: if S and SSS are different then a correction might be needed (not implemented). So for now: make sure that S and SSS are identical, see file hyrsbb123internals.inc.
IHYRSBB123DELTAVOL(IA) = ((IHYRSBB123BB12GACCUM(IA) - IHYRSBB123BB3GACCUM(IA))/(CARD(IS3LOOPSET)+1 - ORD(IS3LOOPSET)))$IHYRSBB123G_Y(IA,IS3LOOPSET);

DISPLAY "FØR UPDATE I SIM3", IHYRSBB123VOLINI ;
* IHYRSBB123VOLINI: next season initial volume level.
* With equation QWATERVOLINI it will make VHYRS_S.L = IHYRSBB123VOLINI, which will be part of the information generated through positive savepoint value.
IHYRSBB123VOLINI(IA,IS3LOOPSET+1) = ( IHYRSBB123VOLINI(IA,IS3LOOPSET)
       + IHYINF_S(IA,IS3LOOPSET)*SUM(IGHYRS,  IGKFX_Y(IA,IGHYRS))
       - SUM(IGHYRS, SUM(T, (IHOURSINST(IS3LOOPSET,T) * VGE_T.L(IA,IGHYRS,IS3LOOPSET,T))$IAGK_Y(IA,IGHYRS) )) )$IHYRSBB123G_Y(IA,IS3LOOPSET);
* Since variable VHYRS_S is declared as positive it will create infeasibilities if IHYRSBB123VOLINI were negative, therefore correct if negative.
ISCALAR1 = SMIN(IA,IHYRSBB123VOLINI(IA,IS3LOOPSET+1));
IF((ISCALAR1 < 0),
   DISPLAY INFODISPLAY, "Warning: SMIN(IA,IS3LOOPSET+1) is negative " ;
   PUT ERRORFILE "Warning from addon hyrsbb123, file hyrsbb123sim3.inc:"/;
   PUT " BB3 simulation would like to have negative hydro storage volume after simulation of Season ", IS3LOOPSET.TL:4, ", most negative value would be ", ISCALAR1:6:0 /;
   PUT "   Hydro starage levels were artificially increased by that amount."//;
);


IHYRSBB123VOLINI(IA,IS3LOOPSET+1) = MAX(0,IHYRSBB123VOLINI(IA,IS3LOOPSET+1));

