* File HYRSBB123equations.inc for the Balmorel model.
* For use with addon HYRSBB123.
* Latest revision 20170419 (hr)

$ifi %HYRSBB123%==price    $goto label_hydrobb123equations

* Equations not verified for BB4!

EQUATION    QWATERVOLINI(Y,AAA,S)   'Hydro energy (volume) in storage at the beginning of season in model Balbase3 (MWh)' ;
EQUATION    QHYRSG(Y,AAA,S)         'Hydro energy available for this region and season in model Balbase3 (MWh)';

* The equation QWATERVOLINI atttempts to achieve start-of-season values (MWh) for VHYRS_S.L that are comparable for those from BB1/BB2.
* Note that VHYRS_S is declared as a positive variable, therefore it is elsewhere artificially assured that IHYRSBB123VOLINI is non-negative.

TODO:


QWATERVOLINI(IY411,IA,IS3)$IHYRSBB123G_Y(IY411,IA,IS3)..  VHYRS_S(IY411,IA,IS3) =E= IHYRSBB123VOLINI(IY411,IA,IS3);

* The equation QHYRSG tries to limit the HYRS generation to same level as in BB1/BB2.
* The equation will not be infeasible since VIHYRSBB12DELTAMHW.UP is INF for the last element wrt. IHYRSBB12DELTASET.
QHYRSG(IA,IS3)$IHYRSBB123G_Y(IA,IS3)..
      IHYRSBB123G_Y(IY411,IA,IS3)  !! Unit: (MWh)
$ifi %HYRSBB123%==quantprice  + IHYRSBB123DELTAVOL(IY411,IA)   + SUM(IHYRSBB12DELTASET, VIHYRSBB12DELTAMHW(IY411,IA,IHYRSBB12DELTASET))
 =G=
      SUM(IGHYRS$IAGK_HASORPOT(IY411,IA,IGHYRS), SUM(T,IHOURSINST(IS3,T)*VGE_T(IY411,IA,IGHYRS,IS3,T)))
;


$label label_hydrobb123equations
