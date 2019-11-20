* Ancilliary services by Juan Gea Bermúdez 2019.

EQUATION QASSECRES  "Ancilliary services: hourly secondary reserve requirement (MW)";
EQUATION QASTERRES  "Ancilliary services: hourly tertiary reserve requirement (MW)";


QASSECRES(IY411,IR,IS3,T)$SECONDARY_RESERVES(IY411,IR)..
        SUM((IASG,IA)$(IAGK_HASORPOT(IY411,IA,IASG) AND RRRAAA(IR,IA)),VASSECRES_T(IY411,IA,IASG,IS3,T))
         =E=
        SECONDARY_RESERVES(IY411,IR)
;

QASTERRES(IY411,IR,IS3,T)$TERTIARY_RESERVES(IY411,IR)..
        SUM((IASG,IA)$(IAGK_HASORPOT(IY411,IA,IASG) AND RRRAAA(IR,IA)),VASTERRES_T(IY411,IA,IASG,IS3,T))
         =E=
        TERTIARY_RESERVES(IY411,IR)
;

