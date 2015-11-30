* Definitions of equations regarding district heating

Equations
            QDHFV(AAA,IAAAI,S,T)  'Transmission into adjacent area limited by invested capacity (MW)'
            QGH_IND(AAA,G,S,T)    'Generation on individual technologies must follow demand (MW)'
            QGHN_IND(AAA,G,S,T)   'Generation on individual new technologies must follow demand (MW)'
;

* Setting production by transmissioncapacity and demand variation
* Consider making this an less-than-constraint
QDHFV(IA,IAI,IS3,T)$AINDN(IA,IAI) ..
    VDHFV(IA,IAI,IS3,T)
         =L=
    SUM(STEPP,VIHFV(IA,IAI,STEPP))*DH_VAR_T(IAI,IS3,T)/IDH_SUMST(IAI)
;

QGH_IND(IA,IGH,IS3,T)$(AIND(IA) and IAGK_Y(IA,IGH) and (GDATA(IGH,'GDCOMB') < 2)) ..
            VGH_IND(IA,IGH)*DH_VAR_T(IA,IS3,T)/IDH_SUMST(IA)
* Slack and surplus
           +VQGH_IND(IA,IGH,IS3,T,'IPLUS')
           -VQGH_IND(IA,IGH,IS3,T,'IMINUS')
                 =E=
            VGH_T(IA,IGH,IS3,T)
$ifi %COMBINATION%==yes + SUM(IGCOMB2$GGCOMB(IGH,IGCOMB2), VGH_T(IA,IGCOMB2,IS3,T)) $ IGCOMB1(IGH)
;

QGHN_IND(IA,IGH,IS3,T)$(AIND(IA) and IAGKN(IA,IGH) and (GDATA(IGH,'GDCOMB') < 2))  ..
            VGHN_IND(IA,IGH)*DH_VAR_T(IA,IS3,T)/IDH_SUMST(IA)
* Slack and surplus
           +VQGHN_IND(IA,IGH,IS3,T,'IPLUS')
           -VQGHN_IND(IA,IGH,IS3,T,'IMINUS')
                 =E=
            VGHN_T(IA,IGH,IS3,T)
$ifi %COMBINATION%==yes + SUM(IGCOMB2$GGCOMB(IGH,IGCOMB2), VGHN_T(IA,IGCOMB2,IS3,T)) $ IGCOMB1(IGH)
;

