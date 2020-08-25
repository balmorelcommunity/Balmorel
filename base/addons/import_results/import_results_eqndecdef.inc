* Equations for addon import results used in seasonal rolling horizon model definition
* Latest revision 20200720 (jgb)

$ifi not %HYRSBB123%==cont    $goto label_no_hydro_results_import

EQUATION    QWATERVOLINI(Y,AAA,S)   'Hydro energy (volume) in storage at the beginning of the seasons (MWh)' ;
QWATERVOLINI(IY411,IA,S)$(SUM(IGHYRS,IAGK_HASORPOT(IY411,IA,IGHYRS)) AND IVHYRS_SL(IY411,IA) AND (IS3(S) OR IS3(S--1)))..
  VHYRS_S(IY411,IA,S) - VHYRS_SL(IY411,IA,S)
  =E=
   0
;

$label label_no_hydro_results_import


$ifi not %ADDESTOVOLTS%==cont    $goto label_no_intraseasonal_electricity_storage_content
EQUATION    QESTOVOLTSIMPORT(Y,AAA,G,S,T)   'Inter-seasonal Electricity storage content at the beginning of each season fixed to results in previous runs (MWh)' ;
QESTOVOLTSIMPORT(IY411,IA,IGESTOS,S,T)$(IAGK_HASORPOT(IY411,IA,IGESTOS) AND IESTOVOLTS(IY411,IA,IGESTOS) AND (ORD(T) EQ 1) AND (IS3(S) OR IS3(S--1)))..
   VESTOVOLTS(IY411,IA,IGESTOS,S,T) - ESTOVOLTS(IY411,IA,IGESTOS,S,T)
=E=
    0
;

$label label_no_intraseasonal_electricity_storage_content

$ifi not %ADDHSTOVOLTS%==cont    $goto label_no_interseasonal_heat_storage_content
EQUATION    QHSTOVOLTSIMPORT(Y,AAA,G,S,T)   'Inter-seasonal heat storage content at the beginning of each season fixed to results in previous runs (MWh)' ;
QHSTOVOLTSIMPORT(IY411,IA,IGHSTOS,S,T)$(IAGK_HASORPOT(IY411,IA,IGHSTOS) AND IHSTOVOLTS(IY411,IA,IGHSTOS) AND (ORD(T) EQ 1) AND (IS3(S) OR IS3(S--1)))..
   VHSTOVOLTS(IY411,IA,IGHSTOS,S,T)   - HSTOVOLTS(IY411,IA,IGHSTOS,S,T)
=E=
    0
;
$label label_no_interseasonal_heat_storage_content

$ifi not %HYDROGEN%==yes          $goto label_no_interseasonal_hydrogen_storage_content
$ifi not %ADDH2STOVOLTS%==cont    $goto label_no_interseasonal_hydrogen_storage_content
EQUATION    QH2STOVOLTSIMPORT(Y,AAA,G,S,T)   'Inter-seasonal hydrogen storage content at the beginning of each season fixed to results in previous runs (MWh)' ;
QH2STOVOLTSIMPORT(IY411,IA,IHYDROGEN_GH2STO,S,T)$(IAGK_HASORPOT(IY411,IA,IHYDROGEN_GH2STO) AND IH2STOVOLTS(IY411,IA,IHYDROGEN_GH2STO) AND (ORD(T) EQ 1) AND (IS3(S) OR IS3(S--1)))..
   VHYDROGEN_STOVOL_T(IY411,IA,IHYDROGEN_GH2STO,S,T)   - H2STOVOLTS(IY411,IA,IHYDROGEN_GH2STO,S,T)
=E=
    0
;
$label label_no_interseasonal_hydrogen_storage_content

$ifi not %HYDROGEN%==yes               $goto label_no_interseasonal_biomethane_storage_content
$ifi not %ADDBIOMETHSTOVOLTS%==cont    $goto label_no_interseasonal_biomethane_storage_content
EQUATION    QBIOMETHSTOVOLTSIMPORT(Y,S,T)   'Inter-seasonal biomethane storage content at the beginning of each season fixed to results in previous runs (MWh)' ;
QBIOMETHSTOVOLTSIMPORT(IY411,S,T)$(IBIOMETHSTOVOLTS(IY411) AND (ORD(T) EQ 1) AND (IS3(S) OR IS3(S--1)))..
   VBIOMETHSTOVOLTS(IY411,S,T)   - BIOMETHSTOVOLTS(IY411,S,T)
=E=
    0
;
$label label_no_interseasonal_biomethane_storage_content

$ifi not %ADDESTOVOLT%==cont    $goto label_no_interseasonal_electricity_storage_content
EQUATION    QESTOVOLTIMPORT(Y,AAA,G,S,T)   'Inter-seasonal Electricity storage content at the beginning of each season fixed to results in previous runs (MWh)' ;
QESTOVOLTIMPORT(IY411,IA,IGESTO,S,T)$(IAGK_HASORPOT(IY411,IA,IGESTO) AND IS3(S) AND IESTOVOLT(IY411,IA,IGESTO) AND (ORD(T) EQ 1))..
VESTOVOLT(IY411,IA,IGESTO,S,T) - ESTOVOLT(IY411,IA,IGESTO,S,T)
=E=
0
;

$label label_no_interseasonal_electricity_storage_content


$ifi not %ADDHSTOVOLT%==cont    $goto label_no_intraseasonal_heat_storage_content
EQUATION    QHSTOVOLTIMPORT(Y,AAA,G,S,T)   'Inter-seasonal heat storage content at the beginning of each season fixed to results in previous runs (MWh)' ;
QHSTOVOLTIMPORT(IY411,IA,IGHSTO,S,T)$(IAGK_HASORPOT(IY411,IA,IGHSTO) AND IS3(S) AND IHSTOVOLT(IY411,IA,IGHSTO) AND (ORD(T) EQ 1))..
VHSTOVOLT(IY411,IA,IGHSTO,S,T)   - HSTOVOLT(IY411,IA,IGHSTO,S,T)
=E=
0
;
$label label_no_intraseasonal_heat_storage_content


$ifi not %HYRSBB123%==price    $goto label_no_hydro_price
EQUATION QHYRSSEQCURT(Y,AAA,S) 'Hydro curtailment equation (MWh)';

QHYRSSEQCURT(IY411,IA,S)$(SUM(IGHYRS,IAGK_HASORPOT(IY411,IA,IGHYRS)) AND IS3(S) AND NOT(ORD(S) EQ CARD(S)))..
      VHYRS_S(IY411,IA,S)
       +  IHYINF_S(IA,S) * (
      SUM(IGHYRS,
        GKFX(IY411,IA,IGHYRS)$IAGKFX(IY411,IA,IGHYRS)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGHYRS)$IGDECOMEXOPOT(IY411,IA,IGHYRS)
       +VGKNACCUMNET(IY411,IA,IGHYRS)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHYRS))
        )
         )
         -SUM(IGHYRS$IAGK_HASORPOT(IY411,IA,IGHYRS),SUM(T,IHYRST(S,T)*(VGE_T(IY411,IA,IGHYRS,S,T)+VHYRS_CURT(IY411,IA,IGHYRS,S,T))))
       =E=
       VHYRS_S(IY411,IA,S++1)
;

$label label_no_hydro_price
