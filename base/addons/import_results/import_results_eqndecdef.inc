* File HYRSBB123equations.inc for the Balmorel model.
* For use with addon HYRSBB123.
* Latest revision 20170419 (hr)

$ifi %HYRSBB123%==none    $goto label_no_hydro_results_import

$ifi %HYRSBB123%==price    $goto label_hydrobb123equations

EQUATION    QWATERVOLINI(Y,AAA,S)   'Hydro energy (volume) in storage at the beginning of the seasons (MWh)' ;
EQUATION    QHYRSG(Y,AAA,S)         'Hydro energy available for this region and season';

* The equation QWATERVOLINI forces start-of-season values (MWh) for VHYRS_S.L to be equal to results from a previous run.
QWATERVOLINI(IY411,IA,S)$(SUM(IGHYRS,IAGK_HASORPOT(IY411,IA,IGHYRS)) AND (ORD(S) EQ 1) AND IS3(S))..
  VHYRS_S(IY411,IA,S)
  =E=
  VHYRS_SL(IY411,IA,S)

$include "../../base/addons/_hooks/qwatervolini.inc"
;

* The equation QHYRSG tries to limit the HYRS generation to same level as in previous runs.
QHYRSG(IY411,IA,IS3)$SUM(IGHYRS$IAGK_HASORPOT(IY411,IA,IGHYRS),1)..
      HYRSG(IY411,IA,IS3)  !! Unit: (MWh)
 =G=
      SUM(IGHYRS$IAGK_HASORPOT(IY411,IA,IGHYRS),SUM(T, IHYRST(IS3,T)*VGE_T(IY411,IA,IGHYRS,IS3,T)))
;

$label label_hydrobb123equations

$label label_no_hydro_results_import


$ifi not %ADDELECSTORCONT%==yes    $goto label_no_intraseasonal_electricity_storage_content


EQUATION    QESTOVOLTSIMPORT(Y,AAA,G,S,T)   'Inter-seasonal Electricity storage content at the beginning of first season fixed to results in previous runs (MWh)' ;

QESTOVOLTSIMPORT(IY411,IA,IGESTOS,S,T)$(IAGK_HASORPOT(IY411,IA,IGESTOS) AND (ORD(S) EQ 1) AND IS3(S)  AND SUM((ISALIAS3,ITALIAS3)$(ORD(ITALIAS3) EQ 1),GVESTOVOLTS(IY411,IA,IGESTOS,ISALIAS3,ITALIAS3)) AND (ORD(T) EQ 1))..

VESTOVOLTS(IY411,IA,IGESTOS,S,T)
=E=
GVESTOVOLTS(IY411,IA,IGESTOS,S,T)

$include "../../base/addons/_hooks/qestovoltsimport.inc"
;

$label label_no_intraseasonal_electricity_storage_content



$ifi not %ADDHEATSTORCONT%==yes    $goto label_no_intraseasonal_heat_storage_content

EQUATION    QHSTOVOLTSIMPORT(Y,AAA,G,S,T)   'Inter-seasonal heat storage content at the beginning of first season fixed to results in previous runs (MWh)' ;

QHSTOVOLTSIMPORT(IY411,IA,IGHSTOS,S,T)$(IAGK_HASORPOT(IY411,IA,IGHSTOS) AND (ORD(S) EQ 1) AND IS3(S) AND SUM((ISALIAS3,ITALIAS3)$(ORD(ITALIAS3) EQ 1),GVHSTOVOLTS(IY411,IA,IGHSTOS,ISALIAS3,ITALIAS3)) AND (ORD(T) EQ 1))..

VHSTOVOLTS(IY411,IA,IGHSTOS,S,T)
=E=
GVHSTOVOLTS(IY411,IA,IGHSTOS,S,T)

$include "../../base/addons/_hooks/qhstovoltsimport.inc"
;


$label label_no_intraseasonal_heat_storage_content
