* File heattrans_decdef.inc for the Balmorel model. For use with addon heattrans.
* Latest revision 20181014(hr)

EQUATIONS
QXHK_UP(Y,IAAAE,IAAAI,S,T)          "Heat transmission capacity constraint (MW)"
QXHKNACCUMNET(Y,IAAAE,IAAAI)        "NOT FINISHED, TODO, Accumulated new heat transmission investments available at beginning of next year (MW)"
*QXHKNACCUMGROSS(Y,IAAAE,IAAAI)      "Accumulated new heat transmission investments available at beginning of next year (MW)"
QXHINVSYMMETRY(Y,IAAAE,IAAAI)        "Heat Transmission investments are set symetric(MW)"
QXHKMAX(Y,IAAAE,IAAAI)               "Maximum heat transmission capacity between areas"
QXHGETOH(Y,IAAAE,IAAAI,GGG,SSS,TTT) "Linking heat pump heat generation to exported heat in heat transmission pipe in order to reach required temperature at importing Area (-)"
;

*"Heat transmission capacity constraint (MW)"
QXHK_UP(IY411,IAE,IAI,IS3,T)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IXHKN(Y,IAE,IAI))..
   (  XHKFX(IY411,IAE,IAI)
      + VXHKNACCUMNET(IY411,IAE,IAI)
    )
     =G=  VXH_T(IY411,IAE,IAI,IS3,T)
;

*"NOT FINISHED, TODO, Accumulated new heat transmission investments available at beginning of next year (MW)"
QXHKNACCUMNET(IY411,IAE,IAI)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IXHKN(Y,IAE,IAI))..
  VXHKNACCUMNET(IY411,IAE,IAI)  !! End of this year's VXHKNACCUMNET (available at beginning of next year)'
     =E=
  SUM(IY402$IY411PREVY(IY411,IY402), VXHKNACCUMNET(IY402,IAE,IAI)$SUM(Y$(YVALUE(Y) LT YVALUE(IY411)),IXHKN(Y,IAE,IAI))) + VXHKN(IY411,IAE,IAI)$IXHKN(IY411,IAE,IAI)  !! VXHKNVACCUMNET available at end of previous(i.e., start of this) year PLUS investment during this year

;


* "Transmission investments are set symetric(MW)"
QXHINVSYMMETRY(IY411,IAE,IAI)$IXHKN(IY411,IAE,IAI)..
   VXHKN(IY411,IAE,IAI)
         =E=
   VXHKN(IY411,IAI,IAE)
;

*"Maximum heat transmission capacity between areas"
QXHKMAX(IY411,IAE,IAI)$XHMAXK(IY411,IAE,IAI)..
    XHMAXK(IY411,IAE,IAI)
     =G=
    (  XHKFX(IY411,IAE,IAI)
    + VXHKNACCUMNET(IY411,IAE,IAI)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IXHKN(Y,IAE,IAI))
    )
;



*$ontext
*to be checked
QXHGETOH(IY411,IAE,IAI,IGETOH,IS3,T)$(IXHK_HASORPOT(IY411,IAE,IAI) AND XHGETOH(IGETOH) AND (IAGK_HASORPOT(IY411,IAI,IGETOH) OR IAGK_HASORPOT(IY411,IAE,IGETOH)))..
     VGH_T(IY411,IAI,IGETOH,IS3,T)$(IAGK_HASORPOT(IY411,IAI,IGETOH) AND XHTEMPLIFT(IAE,IAI))               !! If IGETOH is located at importing Area IAI
*   + VGH_T(IY411,IAE,IGETOH,IS3,T)$(IAGK_HASORPOT(IY411,IAE,IGETOH) AND XHTEMPLIFT(IAE,IAI))               !! If IGETOH is located at exporting Area IAE
     =E=
    (XHTEMPLIFT(IAE,IAI) * VXH_T(IY411,IAE,IAI,IS3,T))$IAGK_HASORPOT(IY411,IAI,IGETOH)                     !! If IGETOH is located at importing Area IAI
*   +(XHTEMPLIFT(IAE,IAI) * VXH_T(IY411,IAE,IAI,IS3,T))$IAGK_HASORPOT(IY411,IAE,IGETOH)                     !! If IGETOH is located at exporting Area IAE
;
*$offtext
