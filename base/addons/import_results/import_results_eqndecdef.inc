* File HYRSBB123equations.inc for the Balmorel model.
* For use with addon HYRSBB123.
* Latest revision 20170419 (hr)

$ifi %HYRSBB123%==none    $goto label_no_hydro_results_import

EQUATION    QWATERVOLINI(Y,AAA,S)   'Hydro energy (volume) in storage at the beginning of the seasons (MWh)' ;

* The equation QWATERVOLINI tries to force start-of-season values (MWh) for VHYRS_S.L to be equal to results from a previous run.
QWATERVOLINI(IY411,IA,S)$(SUM(IGHYRS,IAGK_HASORPOT(IY411,IA,IGHYRS)) AND IS3(S-1) AND SUM(ISALIAS3,VHYRS_SL(IY411,IA,ISALIAS3))
$ifi %HYRSBB123%==contprice   AND NOT(IS3(S))
)..
  VHYRS_S(IY411,IA,S) - VHYRS_SL(IY411,IA,S)
  =E=
$ifi %HYRSBB123%==contprice  VHYRS_SDELTAMWHPOS(IY411,IA,S)-VHYRS_SDELTAMWHNEG(IY411,IA,S)
$ifi %HYRSBB123%==cont       0
;

$label label_no_hydro_results_import


$ifi %ADDELECSTORCONT%==none    $goto label_no_intraseasonal_electricity_storage_content
EQUATION    QESTOVOLTSIMPORT(Y,AAA,G,S,T)   'Inter-seasonal Electricity storage content at the beginning of each season fixed to results in previous runs (MWh)' ;

QESTOVOLTSIMPORT(IY411,IA,IGESTOS,S,T)$(IAGK_HASORPOT(IY411,IA,IGESTOS) AND IS3(S-1) AND SUM((ISALIAS3,ITALIAS3)$(ORD(ITALIAS3) EQ 1),GVESTOVOLTS(IY411,IA,IGESTOS,ISALIAS3,ITALIAS3)) AND (ORD(T) EQ 1)
$ifi %ADDELECSTORCONT%==contprice    AND NOT(IS3(S))
)..

VESTOVOLTS(IY411,IA,IGESTOS,S,T) - GVESTOVOLTS(IY411,IA,IGESTOS,S,T)
=E=
$ifi %ADDELECSTORCONT%==contprice  VESTOVOLTSDELTAMWHPOS(IY411,IA,IGESTOS,S,T) - VESTOVOLTSDELTAMWHNEG(IY411,IA,IGESTOS,S,T)
$ifi %ADDELECSTORCONT%==cont       0
;

$label label_no_intraseasonal_electricity_storage_content



$ifi %ADDHEATSTORCONT%==none    $goto label_no_intraseasonal_heat_storage_content

EQUATION    QHSTOVOLTSIMPORT(Y,AAA,G,S,T)   'Inter-seasonal heat storage content at the beginning of each season fixed to results in previous runs (MWh)' ;

QHSTOVOLTSIMPORT(IY411,IA,IGHSTOS,S,T)$( IAGK_HASORPOT(IY411,IA,IGHSTOS) AND IS3(S-1) AND SUM((ISALIAS3,ITALIAS3)$(ORD(ITALIAS3) EQ 1),GVHSTOVOLTS(IY411,IA,IGHSTOS,ISALIAS3,ITALIAS3)) AND (ORD(T) EQ 1)
$ifi %ADDHEATSTORCONT%==contprice  AND NOT(IS3(S)) 
)..

VHSTOVOLTS(IY411,IA,IGHSTOS,S,T)   - GVHSTOVOLTS(IY411,IA,IGHSTOS,S,T)
=E=
$ifi %ADDHEATSTORCONT%==contprice VHSTOVOLTSDELTAMWHPOS(IY411,IA,IGHSTOS,S,T) - VHSTOVOLTSDELTAMWHNEG(IY411,IA,IGHSTOS,S,T)
$ifi %ADDHEATSTORCONT%==cont      0
;
$label label_no_intraseasonal_heat_storage_content
