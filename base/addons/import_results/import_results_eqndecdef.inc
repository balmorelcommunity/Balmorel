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


$ifi %ADDESTOVOLTS%==none    $goto label_no_intraseasonal_electricity_storage_content
EQUATION    QESTOVOLTSIMPORT(Y,AAA,G,S,T)   'Inter-seasonal Electricity storage content at the beginning of each season fixed to results in previous runs (MWh)' ;

QESTOVOLTSIMPORT(IY411,IA,IGESTOS,S,T)$(IAGK_HASORPOT(IY411,IA,IGESTOS) AND IS3(S-1) AND SUM((ISALIAS3,ITALIAS3)$(ORD(ITALIAS3) EQ 1),ESTOVOLTS(IY411,IA,IGESTOS,ISALIAS3,ITALIAS3)) AND (ORD(T) EQ 1)
$ifi %ADDESTOVOLTS%==contprice    AND NOT(IS3(S))
)..

VESTOVOLTS(IY411,IA,IGESTOS,S,T) - ESTOVOLTS(IY411,IA,IGESTOS,S,T)
=E=
$ifi %ADDESTOVOLTS%==contprice  VESTOVOLTSDELTAMWHPOS(IY411,IA,IGESTOS,S,T) - VESTOVOLTSDELTAMWHNEG(IY411,IA,IGESTOS,S,T)
$ifi %ADDESTOVOLTS%==cont       0
;

$label label_no_intraseasonal_electricity_storage_content



$ifi %ADDHSTOVOLTS%==none    $goto label_no_interseasonal_heat_storage_content

EQUATION    QHSTOVOLTSIMPORT(Y,AAA,G,S,T)   'Inter-seasonal heat storage content at the beginning of each season fixed to results in previous runs (MWh)' ;

QHSTOVOLTSIMPORT(IY411,IA,IGHSTOS,S,T)$( IAGK_HASORPOT(IY411,IA,IGHSTOS) AND IS3(S-1) AND SUM((ISALIAS3,ITALIAS3)$(ORD(ITALIAS3) EQ 1),HSTOVOLTS(IY411,IA,IGHSTOS,ISALIAS3,ITALIAS3)) AND (ORD(T) EQ 1)
$ifi %ADDHSTOVOLTS%==contprice  AND NOT(IS3(S))
)..

VHSTOVOLTS(IY411,IA,IGHSTOS,S,T)   - HSTOVOLTS(IY411,IA,IGHSTOS,S,T)
=E=
$ifi %ADDHSTOVOLTS%==contprice VHSTOVOLTSDELTAMWHPOS(IY411,IA,IGHSTOS,S,T) - VHSTOVOLTSDELTAMWHNEG(IY411,IA,IGHSTOS,S,T)
$ifi %ADDHSTOVOLTS%==cont      0
;
$label label_no_interseasonal_heat_storage_content

$ifi %ADDESTOVOLT%==none    $goto label_no_interseasonal_electricity_storage_content
EQUATION    QESTOVOLTIMPORT(Y,AAA,G,S,T)   'Inter-seasonal Electricity storage content at the beginning of each season fixed to results in previous runs (MWh)' ;

QESTOVOLTIMPORT(IY411,IA,IGESTO,S,T)$(IAGK_HASORPOT(IY411,IA,IGESTO) AND IS3(S) AND SUM((ISALIAS3,ITALIAS3)$(ORD(ITALIAS3) EQ 1),ESTOVOLT(IY411,IA,IGESTO,ISALIAS3,ITALIAS3)) AND (ORD(T) EQ 1)
$ifi %ADDESTOVOLT%==contprice    AND NOT(IS3(S))
)..

VESTOVOLTS(IY411,IA,IGESTO,S,T) - ESTOVOLTS(IY411,IA,IGESTO,S,T)
=E=
$ifi %ADDESTOVOLT%==contprice  VESTOVOLTDELTAMWHPOS(IY411,IA,IGESTO,S,T) - VESTOVOLTSDELTAMWHNEG(IY411,IA,IGESTO,S,T)
$ifi %ADDESTOVOLT%==cont       0
;

$label label_no_interseasonal_electricity_storage_content


$ifi %ADDHSTOVOLT%==none    $goto label_no_intraseasonal_heat_storage_content

EQUATION    QHSTOVOLTIMPORT(Y,AAA,G,S,T)   'Inter-seasonal heat storage content at the beginning of each season fixed to results in previous runs (MWh)' ;

QHSTOVOLTIMPORT(IY411,IA,IGHSTO,S,T)$( IAGK_HASORPOT(IY411,IA,IGHSTO) AND IS3(S) AND SUM((ISALIAS3,ITALIAS3)$(ORD(ITALIAS3) EQ 1),HSTOVOLT(IY411,IA,IGHSTO,ISALIAS3,ITALIAS3)) AND (ORD(T) EQ 1)
$ifi %ADDHSTOVOLT%==contprice  AND NOT(IS3(S))
)..

VHSTOVOLT(IY411,IA,IGHSTO,S,T)   - HSTOVOLT(IY411,IA,IGHSTO,S,T)
=E=
$ifi %ADDHSTOVOLT%==contprice VHSTOVOLTDELTAMWHPOS(IY411,IA,IGHSTO,S,T) - VHSTOVOLTDELTAMWHNEG(IY411,IA,IGHSTO,S,T)
$ifi %ADDHSTOVOLT%==cont      0
;
$label label_no_intraseasonal_heat_storage_content
