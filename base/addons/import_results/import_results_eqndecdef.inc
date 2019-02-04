* File HYRSBB123equations.inc for the Balmorel model.
* For use with addon HYRSBB123.
* Latest revision 20170419 (hr)

$ifi %HYRSBB123%==none    $goto label_no_hydro_results_import

$ifi %HYRSBB123%==price    $goto label_hydrobb123equations

EQUATION    QWATERVOLINI(Y,AAA,S)   'Hydro energy (volume) in storage at the beginning of each season (MWh)' ;


* The equation QWATERINI forces start-of-season values (MWh) for VHYRS_S.L to be equal to results from a previous run.
* Note that VHYRS_S is declared as a positive variable, therefore it is elsewhere artificially assured that IHYRSBB123VOLINI is non-negative.

QWATERVOLINI(IY411,IA,IS3)$(SUM(IGHYRS,IAGK_HASORPOT(IY411,IA,IGHYRS)))..
  VHYRS_S(IY411,IA,IS3)
  =E=
  VHYRS_SL(IY411,IA,IS3)
;


$ontext
*TODO:


QWATERVOLINI(IY411,IA,IS3)$IHYRSBB123G_Y(IY411,IA,IS3)..
 VHYRS_S(IY411,IA,IS3)
 =E=
 IHYRSBB123VOLINI(IY411,IA,IS3);

* The equation QHYRSG tries to limit the HYRS generation to same level as in BB1/BB2.
* The equation will not be infeasible since VIHYRSBB12DELTAMHW.UP is INF for the last element wrt. IHYRSBB12DELTASET.
QHYRSG(IY411IA,IS3)$IHYRSBB123G_Y(IY411,IA,IS3)..
      IHYRSBB123G_Y(IY411,IA,IS3)  !! Unit: (MWh)
$ifi %HYRSBB123%==quantprice  + IHYRSBB123DELTAVOL(IY411,IA)   + SUM(IHYRSBB12DELTASET, VIHYRSBB12DELTAMHW(IY411,IA,IHYRSBB12DELTASET))
 =G=
      SUM(IGHYRS$IAGK_HASORPOT(IY411,IA,IGHYRS), SUM(T,IHOURSINST(IS3,T)*VGE_T(IY411,IA,IGHYRS,IS3,T)))
;

$offtext

$label label_hydrobb123equations

$label label_no_hydro_results_import


$ifi not %ADDELECSTORCONT%==yes    $goto label_no_intraseasonal_electricity_storage_content


EQUATION    QVESTOVOLTS(Y,AAA,G,S,T)   'Intra-seasonal Electricity storage content at the beginning of each season fixed to results in previous runs (MWh)' ;

QVESTOVOLTS(IY411,IA,IGESTOS,S,T)$(IAGK_HASORPOT(IY411,IA,IGESTOS) AND GVESTOVOLTS(IY411,IA,IGESTOS,S,T) AND (ORD(T) EQ 1))..

VESTOVOLTS(IY411,IA,IGESTOS,S,T)
=E=
GVESTOVOLTS(IY411,IA,IGESTOS,S,T)
;

$label label_no_intraseasonal_electricity_storage_content



$ifi not %ADDHEATSTORCONT%==yes    $goto label_no_intraseasonal_heat_storage_content

EQUATION    QVHSTOVOLTS(Y,AAA,G,S,T)   'Intra-seasonal Heat storage content at the beginning of each season fixed to results in previous runs (MWh)' ;

QVHSTOVOLTS(IY411,IA,IGHSTOS,S,T)$(IAGK_HASORPOT(IY411,IA,IGHSTOS) AND GVHSTOVOLTS(IY411,IA,IGHSTOS,S,T) AND (ORD(T) EQ 1))..

VHSTOVOLTS(IY411,IA,IGHSTOS,S,T)
=E=
GVHSTOVOLTS(IY411,IA,IGHSTOS,S,T)
;


$label label_no_intraseasonal_heat_storage_content