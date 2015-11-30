Equations
        QXHK(IAAAE,IAAAI,S,T)  'Heat transmission capacity constraint'
;


*----------- Heat transmission (MW):------------------------------------------------

* Heat transmission is limited by transmission capacity:

QXHK(IAE,IAI,S,T)$(IXHKINI_Y(IAE,IAI) OR IXHKN(IAI,IAE) OR IXHKN(IAE,IAI))..
      IXHKINI_Y(IAE,IAI)
      + VXHKN(IAE,IAI)$(IXHKN(IAE,IAI) OR IXHKN(IAI,IAE))+ VXHKN(IAI,IAE)$(IXHKN(IAE,IAI) OR IXHKN(IAI,IAE))
   =G=
      VXH_T(IAE,IAI,S,T)
;
