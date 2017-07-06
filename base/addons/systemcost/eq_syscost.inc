* Addon for securing that System Constraints are forfilled

Equations

QBASELOAD(C,S,T)       'Minimum production for baseload service providers (MW)'
;

QBASELOAD(C,IS3,T)$(BASELOADSERVICE(C) > 0) ..
      SUM(IAGK_Y(IA,IGE)$(ICA(C,IA) AND IGEBASE(IGE)), VGE_T(IA,IGE,IS3,T))
    + SUM(IAGKN(IA,IGE)$(ICA(C,IA) AND IGEBASE(IGE)), VGEN_T(IA,IGE,IS3,T))

                 +VQBASELOAD(C,IS3,T)
         =G=
                 BASELOADSERVICE(C)
;