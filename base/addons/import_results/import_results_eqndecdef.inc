* File HYRSBB123equations.inc for the Balmorel model.
* For use with addon HYRSBB123.
* Latest revision 20170419 (hr)

$ifi %HYRSBB123%==none    $goto label_no_hydro_results_import

$ifi not %HYRSBB123%==contprice    $goto label_no_hydro_contprice
EQUATION    QWATERVOLINI(Y,AAA,S)   'Hydro energy (volume) in storage at the beginning of the seasons (MWh)' ;

* The equation QWATERVOLINI tries to force start-of-season values (MWh) for VHYRS_S.L to be equal to results from a previous run.
QWATERVOLINI(IY411,IA,S)$(SUM(IGHYRS,IAGK_HASORPOT(IY411,IA,IGHYRS)) AND (IS3(S) OR IS3(S--1)) AND SUM(ISALIAS3,VHYRS_SL(IY411,IA,ISALIAS3)))..
  VHYRS_S(IY411,IA,S) - VHYRS_SL(IY411,IA,S)
  =E=
  VHYRS_SDELTAMWHPOS(IY411,IA,S)-VHYRS_SDELTAMWHNEG(IY411,IA,S)

$include "../../base/addons/_hooks/qwatervolini.inc"
;
$label label_no_hydro_contprice

$label label_no_hydro_results_import


$ifi not %ADDELECSTORCONT%==yes    $goto label_no_intraseasonal_electricity_storage_content
EQUATION    QESTOVOLTSIMPORT(Y,AAA,G,S,T)   'Inter-seasonal Electricity storage content at the beginning of each season fixed to results in previous runs (MWh)' ;

QESTOVOLTSIMPORT(IY411,IA,IGESTOS,S,T)$(IAGK_HASORPOT(IY411,IA,IGESTOS) AND (IS3(S) OR IS3(S--1))  AND SUM((ISALIAS3,ITALIAS3)$(ORD(ITALIAS3) EQ 1),GVESTOVOLTS(IY411,IA,IGESTOS,ISALIAS3,ITALIAS3)) AND (ORD(T) EQ 1))..

VESTOVOLTS(IY411,IA,IGESTOS,S,T) - GVESTOVOLTS(IY411,IA,IGESTOS,S,T)
=E=
VESTOVOLTSDELTAMWHPOS(IY411,IA,IGESTOS,S,T) - VESTOVOLTSDELTAMWHNEG(IY411,IA,IGESTOS,S,T)

$include "../../base/addons/_hooks/qestovoltsimport.inc"
;

$label label_no_intraseasonal_electricity_storage_content



$ifi not %ADDHEATSTORCONT%==yes    $goto label_no_intraseasonal_heat_storage_content

EQUATION    QHSTOVOLTSIMPORT(Y,AAA,G,S,T)   'Inter-seasonal heat storage content at the beginning of each season fixed to results in previous runs (MWh)' ;

QHSTOVOLTSIMPORT(IY411,IA,IGHSTOS,S,T)$(IAGK_HASORPOT(IY411,IA,IGHSTOS) AND (IS3(S) OR IS3(S--1)) AND SUM((ISALIAS3,ITALIAS3)$(ORD(ITALIAS3) EQ 1),GVHSTOVOLTS(IY411,IA,IGHSTOS,ISALIAS3,ITALIAS3)) AND (ORD(T) EQ 1))..

VHSTOVOLTS(IY411,IA,IGHSTOS,S,T)   - GVHSTOVOLTS(IY411,IA,IGHSTOS,S,T)
=E=
VHSTOVOLTSDELTAMWHPOS(IY411,IA,IGHSTOS,S,T) - VHSTOVOLTSDELTAMWHNEG(IY411,IA,IGHSTOS,S,T)

$include "../../base/addons/_hooks/qhstovoltsimport.inc"
;
$label label_no_intraseasonal_heat_storage_content
