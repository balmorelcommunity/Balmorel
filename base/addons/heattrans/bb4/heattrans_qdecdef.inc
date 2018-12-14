* File heattrans_decdef.inc for the Balmorel model. For use with addon heattrans.
* Latest revision 20181014(hr)

$LOG "TODO for addon heattrans in %system.incname%";

EQUATIONS
QXHK_UP(Y,IAAAE,IAAAI,S,T)          "Heat transmission capacity constraint (MW)"
QXHK(Y,IAAAE,IAAAI)                 "New transmission investment  - NOT IMPLEMENTED PRESENTLYT (MW)"                                        !! NOT IMPLEMENETED
QXHKNACCUMNET(Y,IAAAE,IAAAI)        "NOT FINISHED, TODO, Accumulated new transmission investments available at beginning of next year (MW)" !! NOT IMPLEMENETED
QXHKNACCUMGROSS(Y,IAAAE,IAAAI)      "Accumulated new transmission investments available at beginning of next year (MW)"                     !! NOT IMPLEMENETED
QXHGETOH(Y,IAAAE,IAAAI,GGG,SSS,TTT) "Linking heat pump heat generation to exported heat in heat transmission pipe in order to reach required temperature at importing Area (-)";


QXHGETOH(IY411,IAE,IAI,IGETOH,IS3,T)$(IXHK_HASORPOT(IY411,IAE,IAI) AND XHGETOH(IGETOH) AND (IAGK_HASORPOT(IY411,IAI,IGETOH) OR IAGK_HASORPOT(IY411,IAE,IGETOH)))..
     VGH_T(IY411,IAI,IGETOH,IS3,T)$(IAGK_HASORPOT(IY411,IAI,IGETOH) AND XHTEMPLIFT(IAE,IAI))               !! If IGETOH is located at importing Area IAI
*   + VGH_T(IY411,IAE,IGETOH,IS3,T)$(IAGK_HASORPOT(IY411,IAE,IGETOH) AND XHTEMPLIFT(IAE,IAI))               !! If IGETOH is located at exporting Area IAE
     =E=
    (XHTEMPLIFT(IAE,IAI) * VXH_T(IY411,IAE,IAI,IS3,T))$IAGK_HASORPOT(IY411,IAI,IGETOH)                     !! If IGETOH is located at importing Area IAI
*   +(XHTEMPLIFT(IAE,IAI) * VXH_T(IY411,IAE,IAI,IS3,T))$IAGK_HASORPOT(IY411,IAE,IGETOH)                     !! If IGETOH is located at exporting Area IAE
;

