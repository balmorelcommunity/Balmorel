* Equations for addon import results used in seasonal rolling horizon model definition
* Latest revision 20200720 (jgb)

$ifi not %HYRSBB123%==cont    $goto label_no_hydro_results_import

EQUATION    QWATERVOLINI(Y,AAA,S)   'Hydro energy (volume) in storage at the beginning of the seasons (MWh)' ;
QWATERVOLINI(IY411,IA,S)$(SUM(IGHYRS,IAGK_HASORPOT(IY411,IA,IGHYRS)) AND IVHYRS_SL(IY411,IA) AND (NOT(IS3(S)) AND IS3(S-1)))..
  VHYRS_S(IY411,IA,S) - VHYRS_SL(IY411,IA,S)
  =E=
   0
;

EQUATION    QWATERVOLINI_LAST(Y,AAA,SSS)   'Hydro energy (volume) in storage at the beginning of the next season not included in run (MWh)' ;
QWATERVOLINI_LAST(IY411,IA,SSS)$(SUM(IGHYRS,IAGK_HASORPOT(IY411,IA,IGHYRS)) AND IVHYRS_SL(IY411,IA) AND (SUM(S$(IS3(S) AND ORD(S) EQ CARD(S)),ICOUNTSSS(S)) EQ ICOUNTSSS(SSS--1)))..
  VHYRS_S(IY411,IA,SSS) - VHYRS_SL(IY411,IA,SSS)
  =E=
   0
;

$label label_no_hydro_results_import


$ifi not %ADDESTOVOLTS%==cont    $goto label_no_intraseasonal_electricity_storage_content
EQUATION    QESTOVOLTSIMPORT(Y,AAA,G,S,T)   'Inter-seasonal Electricity storage content at the beginning of last season in run fixed to results in previous runs (MWh)' ;
QESTOVOLTSIMPORT(IY411,IA,IGESTOS,S,T)$(IAGK_HASORPOT(IY411,IA,IGESTOS) AND IESTOVOLTS(IY411,IA,IGESTOS) AND (ORD(T) EQ 1) AND (NOT(IS3(S)) AND IS3(S-1)))..
   VESTOVOLTS(IY411,IA,IGESTOS,S,T) - ESTOVOLTS(IY411,IA,IGESTOS,S,T)
=E=
    0
;

EQUATION  QESTOVOLTSIMPORT_LAST(Y,AAA,G,SSS,T) 'Inter-seasonal Electricity storage content at the beginning of the next season not included in the run in case not all elements in SSS are used based on previous result (MWh)' ;
QESTOVOLTSIMPORT_LAST(IY411,IA,IGESTOS,SSS,T)$(IAGK_HASORPOT(IY411,IA,IGESTOS) AND IESTOVOLTS(IY411,IA,IGESTOS) AND (ORD(T) EQ 1) AND (SUM(S$(IS3(S) AND ORD(S) EQ CARD(S)),ICOUNTSSS(S)) EQ ICOUNTSSS(SSS--1))
$ifi not %RollingSeasons%==yes AND NOT(CARD(SSS) EQ CARD(S))
)..
   VESTOVOLTS(IY411,IA,IGESTOS,SSS,T) - ESTOVOLTS(IY411,IA,IGESTOS,SSS,T)
=E=
    0
;
$label label_no_intraseasonal_electricity_storage_content

$ifi not %ADDHSTOVOLTS%==cont    $goto label_no_interseasonal_heat_storage_content
EQUATION    QHSTOVOLTSIMPORT(Y,AAA,G,S,T)   'Inter-seasonal heat storage content at the beginning of last season in run fixed to results in previous runs (MWh)' ;
QHSTOVOLTSIMPORT(IY411,IA,IGHSTOS,S,T)$(IAGK_HASORPOT(IY411,IA,IGHSTOS) AND IHSTOVOLTS(IY411,IA,IGHSTOS) AND (ORD(T) EQ 1) AND (NOT(IS3(S)) AND IS3(S-1)))..
   VHSTOVOLTS(IY411,IA,IGHSTOS,S,T) - HSTOVOLTS(IY411,IA,IGHSTOS,S,T)
=E=
    0
;

EQUATION  QHSTOVOLTSIMPORT_LAST(Y,AAA,G,SSS,T) 'Inter-seasonal heat storage content at the beginning of the next season not included in the run in case not all elements in SSS are used based on previous result (MWh)' ;
QHSTOVOLTSIMPORT_LAST(IY411,IA,IGHSTOS,SSS,T)$(IAGK_HASORPOT(IY411,IA,IGHSTOS) AND IHSTOVOLTS(IY411,IA,IGHSTOS) AND (ORD(T) EQ 1) AND (SUM(S$(IS3(S) AND ORD(S) EQ CARD(S)),ICOUNTSSS(S)) EQ ICOUNTSSS(SSS--1))
$ifi not %RollingSeasons%==yes AND NOT(CARD(SSS) EQ CARD(S))
)..
   VHSTOVOLTS(IY411,IA,IGHSTOS,SSS,T) - HSTOVOLTS(IY411,IA,IGHSTOS,SSS,T)
=E=
    0
;
$label label_no_interseasonal_heat_storage_content

$ifi not %HYDROGEN%==yes          $goto label_no_interseasonal_hydrogen_storage_content
$ifi not %ADDH2STOVOLTS%==cont    $goto label_no_interseasonal_hydrogen_storage_content
EQUATION    QH2STOVOLTSIMPORT(Y,AAA,G,S,T)   'Inter-seasonal hydrogen storage content at the beginning of last season in run fixed to results in previous runs (MWh)' ;
QH2STOVOLTSIMPORT(IY411,IA,IHYDROGEN_GH2STO,S,T)$(IAGK_HASORPOT(IY411,IA,IHYDROGEN_GH2STO) AND IH2STOVOLTS(IY411,IA,IHYDROGEN_GH2STO)  AND (ORD(T) EQ 1) AND (NOT(IS3(S)) AND IS3(S-1)))..
   VHYDROGEN_STOVOL_T(IY411,IA,IHYDROGEN_GH2STO,S,T)   - H2STOVOLTS(IY411,IA,IHYDROGEN_GH2STO,S,T)
=E=
    0
;

EQUATION   QH2STOVOLTSIMPORT_LAST(Y,AAA,G,SSS,T)   'Inter-seasonal hydrogen storage content at the beginning of the next each season not included in the run in case not all elements in SSS are used based on previous runs (MWh)' ;
QH2STOVOLTSIMPORT_LAST(IY411,IA,IHYDROGEN_GH2STO,SSS,T)$(IAGK_HASORPOT(IY411,IA,IHYDROGEN_GH2STO) AND IH2STOVOLTS(IY411,IA,IHYDROGEN_GH2STO)  AND (ORD(T) EQ 1) AND (SUM(S$(IS3(S) AND ORD(S) EQ CARD(S)),ICOUNTSSS(S)) EQ ICOUNTSSS(SSS--1))
$ifi not %RollingSeasons%==yes AND NOT(CARD(SSS) EQ CARD(S))
)..
  VHYDROGEN_STOVOL_T(IY411,IA,IHYDROGEN_GH2STO,SSS,T)   - H2STOVOLTS(IY411,IA,IHYDROGEN_GH2STO,SSS,T)
=E=
    0
;
$label label_no_interseasonal_hydrogen_storage_content

$ifi not %HYDROGEN%==yes               $goto label_no_interseasonal_biomethane_storage_content
$ifi not %ADDBIOMETHSTOVOLTS%==cont    $goto label_no_interseasonal_biomethane_storage_content
EQUATION    QBIOMETHSTOVOLTSIMPORT(Y,S,T)    'Inter-seasonal biomethane storage content at the beginning of last season in run fixed to results in previous runs (MWh)' ;
QBIOMETHSTOVOLTSIMPORT(IY411,S,T)$(IBIOMETHSTOVOLTS(IY411)  AND (ORD(T) EQ 1) AND (NOT(IS3(S)) AND IS3(S-1)))..
   VBIOMETHSTOVOLTS(IY411,S,T)   - BIOMETHSTOVOLTS(IY411,S,T)
=E=
    0
;

EQUATION    QBIOMETHSTOVOLTSIMPORT_LAST(Y,SSS,T)   'Inter-seasonal biomethane storage content at the beginning of the next each season not included in the run in case not all elements in SSS are used based on previous runs (MWh)' ;
QBIOMETHSTOVOLTSIMPORT_LAST(IY411,SSS,T)$(IBIOMETHSTOVOLTS(IY411)  AND (ORD(T) EQ 1) AND (SUM(S$(IS3(S) AND ORD(S) EQ CARD(S)),ICOUNTSSS(S)) EQ ICOUNTSSS(SSS--1))
$ifi not %RollingSeasons%==yes AND NOT(CARD(SSS) EQ CARD(S))
)..
   VBIOMETHSTOVOLTS(IY411,SSS,T)   - BIOMETHSTOVOLTS(IY411,SSS,T)
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
QHYRSSEQCURT(IY411,IA,S)$(SUM(IGHYRS,IAGK_HASORPOT(IY411,IA,IGHYRS)) AND IS3(S))..
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

$ifi   not  %HYRSBB123%==none   +(-VHYRS_S(IY411,IA,S++1)+SUM(SSS$(ICOUNTSSS(S) EQ ICOUNTSSS(SSS)),VHYRS_S(IY411,IA,SSS++1)))$(CARD(S) EQ ORD(S))

;


EQUATION QHYRSMINVOL_LAST(Y,AAA,SSS) 'Hydropower reservoir - minimum level in next season not included in the model (MWh)';
QHYRSMINVOL_LAST(IY411,IA,SSS)$(HYRSDATA(IA,"HYRSMINVOL",SSS) AND SUM(IGHYRS,IAGK_HASORPOT(IY411,IA,IGHYRS)) AND IVHYRS_SL(IY411,IA) AND (SUM(S$(IS3(S) AND ORD(S) EQ CARD(S)),ICOUNTSSS(S)) EQ ICOUNTSSS(SSS--1))
$ifi not %RollingSeasons%==yes AND NOT(CARD(SSS) EQ CARD(S))
)..
     VHYRS_S(IY411,IA,SSS)  =G=  HYRSDATA(IA,"HYRSMINVOL",SSS)*
       SUM(IGHYRS,   HYRSMAXVOL_G(IA,IGHYRS)*(
         GKFX(IY411,IA,IGHYRS)$IAGKFX(IY411,IA,IGHYRS)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGHYRS)$IGDECOMEXOPOT(IY411,IA,IGHYRS)
        +VGKNACCUMNET(IY411,IA,IGHYRS)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHYRS))
        ))
;

EQUATION QHYRSMAXVOL_LAST(Y,AAA,SSS) 'Hydropower reservoir - maximum level in next season not included in the model (MWh)';
QHYRSMAXVOL_LAST(IY411,IA,SSS)$(HYRSDATA(IA,"HYRSMAXVOL",SSS) AND SUM(IGHYRS,IAGK_HASORPOT(IY411,IA,IGHYRS)) AND IVHYRS_SL(IY411,IA) AND (SUM(S$(IS3(S) AND ORD(S) EQ CARD(S)),ICOUNTSSS(S)) EQ ICOUNTSSS(SSS--1))
$ifi not %RollingSeasons%==yes AND NOT(CARD(SSS) EQ CARD(S))
)..
       HYRSDATA(IA,"HYRSMAXVOL",SSS) *
       SUM(IGHYRS,  HYRSMAXVOL_G(IA,IGHYRS)*(
         GKFX(IY411,IA,IGHYRS)$IAGKFX(IY411,IA,IGHYRS)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGHYRS)$IGDECOMEXOPOT(IY411,IA,IGHYRS)
        +VGKNACCUMNET(IY411,IA,IGHYRS)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHYRS))
        ))
       =G= VHYRS_S(IY411,IA,SSS)
;
$label label_no_hydro_price

$ifi not %ADDESTOVOLTS%==price    $goto no_estovolts_price
EQUATION QESTOVOLTLIMS_LAST(Y,AAA,G,SSS,T) 'Inter-seasonal Electricity storage capacity limit for next season not included in the model (MWh)' ;
QESTOVOLTLIMS_LAST(IY411,IA,IGESTOS,SSS,T)$(IAGK_HASORPOT(IY411,IA,IGESTOS) AND IESTOVOLTS(IY411,IA,IGESTOS) AND (ORD(T) EQ 1) AND (SUM(S$(IS3(S) AND ORD(S) EQ CARD(S)),ICOUNTSSS(S)) EQ ICOUNTSSS(SSS--1))
$ifi not %RollingSeasons%==yes AND NOT(CARD(SSS) EQ CARD(S))
)..
* Existing or accumulated capacity
   GKFX(IY411,IA,IGESTOS)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGESTOS)$IGDECOMEXOPOT(IY411,IA,IGESTOS)
   + VGKNACCUMNET(IY411,IA,IGESTOS)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGESTOS))
         =G=
  VESTOVOLTS(IY411,IA,IGESTOS,SSS,T)
;

$label no_estovolts_price

$ifi not %ADDHSTOVOLTS%==price    $goto no_hstovolts_price
EQUATION QHSTOVOLTLIMS_LAST(Y,AAA,G,SSS,T) 'Inter-seasonal heat storage capacity limit for next season not included in the model (MWh)' ;
QHSTOVOLTLIMS_LAST(IY411,IA,IGHSTOS,SSS,T)$(IAGK_HASORPOT(IY411,IA,IGHSTOS) AND IHSTOVOLTS(IY411,IA,IGHSTOS) AND (ORD(T) EQ 1) AND (SUM(S$(IS3(S) AND ORD(S) EQ CARD(S)),ICOUNTSSS(S)) EQ ICOUNTSSS(SSS--1))
$ifi not %RollingSeasons%==yes AND NOT(CARD(SSS) EQ CARD(S))
)..
* Existing or accumulated capacity
   GKFX(IY411,IA,IGHSTOS)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGHSTOS)$IGDECOMEXOPOT(IY411,IA,IGHSTOS)
   + VGKNACCUMNET(IY411,IA,IGHSTOS)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHSTOS))
         =G=
  VHSTOVOLTS(IY411,IA,IGHSTOS,SSS,T)
;

$label no_hstovolts_price


$ifi not %HYDROGEN%==yes           $goto label_no_interseasonal_hydrogen_storage_price
$ifi not %ADDH2STOVOLTS%==price    $goto label_no_interseasonal_hydrogen_storage_price
EQUATION  QHYDROGEN_STOMAXCON_LAST(Y,AAA,G,SSS,T) 'Upper bound to hydrogen storage for the last season not included in this run from previous results (MWh)';
QHYDROGEN_STOMAXCON_LAST(IY411,IA,IHYDROGEN_GH2STO,SSS,T)$(IAGK_HASORPOT(IY411,IA,IHYDROGEN_GH2STO) AND IH2STOVOLTS(IY411,IA,IHYDROGEN_GH2STO)  AND (ORD(T) EQ 1) AND (SUM(S$(IS3(S) AND ORD(S) EQ CARD(S)),ICOUNTSSS(S)) EQ ICOUNTSSS(SSS--1))
$ifi not %RollingSeasons%==yes AND NOT(CARD(SSS) EQ CARD(S))
)..
     GKFX(IY411,IA,IHYDROGEN_GH2STO)
   + VGKNACCUMNET(IY411,IA,IHYDROGEN_GH2STO)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IHYDROGEN_GH2STO))
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IHYDROGEN_GH2STO)$IGDECOMEXOPOT(IY411,IA,IHYDROGEN_GH2STO)
    =G=
   VHYDROGEN_STOVOL_T(IY411,IA,IHYDROGEN_GH2STO,SSS,T)
;
$label label_no_interseasonal_hydrogen_storage_price

