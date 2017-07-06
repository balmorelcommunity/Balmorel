EQUATIONS
   QECOMBGLK(AAA,G,S,T)   'Combination technology, sum of production limit, electricity'
   QECOMBSLO(AAA,G,S,T)   'Combination technology, minimum share of total production, electricity'
   QECOMBSUP(AAA,G,S,T)   'Combination technology, maximum share of total production, electricity'
   QHCOMBGLK(AAA,G,S,T)   'Combination technology, sum of production limit, heat'
   QHCOMBSLO(AAA,G,S,T)   'Combination technology, minimum share of total production, heat'
   QHCOMBSUP(AAA,G,S,T)   'Combination technology, maximum share of total production, heat'
   QNECOMBGLK(AAA,G,S,T)  'New combination technology, sum of production limit, electricity'
   QNECOMBSLO(AAA,G,S,T)  'New combination technology, minimum share of total production, electricity'
   QNECOMBSUP(AAA,G,S,T)  'New combination technology, maximum share of total production, electricity'
   QNHCOMBGLK(AAA,G,S,T)  'New combination technology, sum of production limit, heat'
   QNHCOMBSLO(AAA,G,S,T)  'New combination technology, minimum share of total production, heat'
   QNHCOMBSUP(AAA,G,S,T)  'New combination technology, maximum share of total production, heat';

QECOMBGLK(IA,IGCOMB1,IS3,T)$(IAGK_Y(IA,IGCOMB1) AND IGKE(IGCOMB1)
           AND ((GDATA(IGCOMB1,'GDCOMBSK') + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2), GDATA(IGCOMB2,'GDCOMBSK'))) GT 1))..
     (IGKVACCTOY(IA,IGCOMB1) + IGKFX_Y(IA,IGCOMB1)) * GKDERATE(IA,IGCOMB1,IS3)
          =G=
     VGE_T(IA,IGCOMB1,IS3,T) + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2), VGE_T(IA,IGCOMB2,IS3,T))
;


QECOMBSLO(IA,IGKE,IS3,T)$(IAGK_Y(IA,IGKE) AND (GDATA(IGKE,'GDCOMBSLO') GT 0) AND (IGCOMB1(IGKE) OR IGCOMB2(IGKE)))..
     VGE_T(IA,IGKE,IS3,T) =G= GDATA(IGKE,'GDCOMBSLO')*(
                            (SUM(IGCOMB2$GGCOMB(IGKE,IGCOMB2), VGE_T(IA,IGCOMB2,IS3,T))
                              + VGE_T(IA,IGKE,IS3,T))$IGCOMB1(IGKE)
                            + (SUM(IGCOMB1$GGCOMB(IGCOMB1,IGKE),
                                VGE_T(IA,IGCOMB1,IS3,T)
                            + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2),
                                  VGE_T(IA,IGCOMB2,IS3,T)))
                            )$IGCOMB2(IGKE));


QECOMBSUP(IA,IGKE,IS3,T)$(IAGK_Y(IA,IGKE) AND (IGCOMB1(IGKE) OR IGCOMB2(IGKE)) AND (GDATA(IGKE,'GDCOMBSUP') LT 1))..
       GDATA(IGKE,'GDCOMBSUP')
        *(
          (SUM(IGCOMB2$GGCOMB(IGKE,IGCOMB2), VGE_T(IA,IGCOMB2,IS3,T))
            + VGE_T(IA,IGKE,IS3,T)
          )$IGCOMB1(IGKE)
          + (SUM(IGCOMB1$GGCOMB(IGCOMB1,IGKE), VGE_T(IA,IGCOMB1,IS3,T)
           + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2), VGE_T(IA,IGCOMB2,IS3,T)))
             )$IGCOMB2(IGKE)
         )
      =G=
    VGE_T(IA,IGKE,IS3,T)
;

QHCOMBGLK(IA,IGCOMB1,IS3,T)$(IAGK_Y(IA,IGCOMB1) AND IGKH(IGCOMB1)
           AND (GDATA(IGCOMB1,'GDCOMBSK') + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2), GDATA(IGCOMB1,'GDCOMBSK') GT 1)))..
    (IGKVACCTOY(IA,IGCOMB1) + IGKFX_Y(IA,IGCOMB1))*GKDERATE(IA,IGCOMB1,IS3)
        =G=
     VGH_T(IA,IGCOMB1,IS3,T) + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2), VGH_T(IA,IGCOMB2,IS3,T))
;

QHCOMBSLO(IA,IGKH,IS3,T)$(IAGK_Y(IA,IGKH) AND (IGCOMB1(IGKH) OR IGCOMB2(IGKH)) AND (GDATA(IGKH,'GDCOMBSLO') GT 0))..
     VGH_T(IA,IGKH,IS3,T)
         =G=
  GDATA(IGKH,'GDCOMBSLO')*(
    (SUM(IGCOMB2$GGCOMB(IGKH,IGCOMB2), VGH_T(IA,IGCOMB2,IS3,T))
      + VGH_T(IA,IGKH,IS3,T))$IGCOMB1(IGKH)
    + (SUM(IGCOMB1$GGCOMB(IGCOMB1,IGKH),
        VGH_T(IA,IGCOMB1,IS3,T)
    + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2),
          VGH_T(IA,IGCOMB2,IS3,T)))
    )$IGCOMB2(IGKH))
;


QHCOMBSUP(IA,IGKH,IS3,T)$(IAGK_Y(IA,IGKH) AND (IGCOMB1(IGKH) OR IGCOMB2(IGKH)) AND (GDATA(IGKH,'GDCOMBSUP') LT 1))..
      GDATA(IGKH,'GDCOMBSUP')*(
                            (SUM(IGCOMB2$GGCOMB(IGKH,IGCOMB2), VGH_T(IA,IGCOMB2,IS3,T))
                              + VGH_T(IA,IGKH,IS3,T))$IGCOMB1(IGKH)

                            +( SUM(IGCOMB1$GGCOMB(IGCOMB1,IGKH),
                                  VGH_T(IA,IGCOMB1,IS3,T)
                              +SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2),
                                  VGH_T(IA,IGCOMB2,IS3,T)))
                              )$IGCOMB2(IGKH))
      =G=
         VGH_T(IA,IGKH,IS3,T)
;


QNECOMBGLK(IA,IGCOMB1,IS3,T)$
            (IAGKN(IA,IGCOMB1) AND IGKE(IGCOMB1)
            AND (GDATA(IGCOMB1,'GDCOMBSK') + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2), GDATA(IGCOMB1,'GDCOMBSK') GT 1)))..
     VGKN(IA,IGCOMB1)*GKDERATE(IA,IGCOMB1,IS3)
         =G=
     VGEN_T(IA,IGCOMB1,IS3,T) + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2), VGEN_T(IA,IGCOMB2,IS3,T))
;


QNECOMBSLO(IA,IGKE,IS3,T)$(IAGKN(IA,IGKE) AND (IGCOMB1(IGKE) OR IGCOMB2(IGKE)) AND (GDATA(IGKE,'GDCOMBSLO') GT 0))..
     VGEN_T(IA,IGKE,IS3,T) =G= GDATA(IGKE,'GDCOMBSLO')*(
                            (SUM(IGCOMB2$GGCOMB(IGKE,IGCOMB2), VGEN_T(IA,IGCOMB2,IS3,T))
                              + VGEN_T(IA,IGKE,IS3,T))$IGCOMB1(IGKE)
                            + (SUM(IGCOMB1$GGCOMB(IGCOMB1,IGKE),
                                VGEN_T(IA,IGCOMB1,IS3,T)
                            + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2),
                                  VGEN_T(IA,IGCOMB2,IS3,T)))
                            )$IGCOMB2(IGKE));


QNECOMBSUP(IA,IGKE,IS3,T)$(IAGKN(IA,IGKE) AND (IGCOMB1(IGKE) OR IGCOMB2(IGKE)) AND (GDATA(IGKE,'GDCOMBSUP') LT 1))..
          GDATA(IGKE,'GDCOMBSUP')*(
             (SUM(IGCOMB2$GGCOMB(IGKE,IGCOMB2), VGEN_T(IA,IGCOMB2,IS3,T))
               + VGEN_T(IA,IGKE,IS3,T))$IGCOMB1(IGKE)
             + (SUM(IGCOMB1$GGCOMB(IGCOMB1,IGKE),
                 VGEN_T(IA,IGCOMB1,IS3,T)
             + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2),
                   VGEN_T(IA,IGCOMB2,IS3,T)))
             )$IGCOMB2(IGKE))
        =G=
          VGEN_T(IA,IGKE,IS3,T)
;


QNHCOMBGLK(IA,IGCOMB1,IS3,T)$(IAGKN(IA,IGCOMB1) AND IGKH(IGCOMB1)
            AND (GDATA(IGCOMB1,'GDCOMBSK') + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2), GDATA(IGCOMB1,'GDCOMBSK') GT 1)))..
     VGKN(IA,IGCOMB1)*GKDERATE(IA,IGCOMB1,IS3)
  =G=
     VGHN_T(IA,IGCOMB1,IS3,T) + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2), VGHN_T(IA,IGCOMB2,IS3,T))
     ;


QNHCOMBSLO(IA,IGKH,IS3,T)$(IAGKN(IA,IGKH) AND (IGCOMB1(IGKH) OR IGCOMB2(IGKH)) AND (GDATA(IGKH,'GDCOMBSLO') GT 0))..
     VGHN_T(IA,IGKH,IS3,T)
                         =G=
     GDATA(IGKH,'GDCOMBSLO')*(
        (SUM(IGCOMB2$GGCOMB(IGKH,IGCOMB2), VGHN_T(IA,IGCOMB2,IS3,T))
          + VGHN_T(IA,IGKH,IS3,T))$IGCOMB1(IGKH)
        + (SUM(IGCOMB1$GGCOMB(IGCOMB1,IGKH),
            VGHN_T(IA,IGCOMB1,IS3,T)
        + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2),
              VGHN_T(IA,IGCOMB2,IS3,T)))
        )$IGCOMB2(IGKH))
;


QNHCOMBSUP(IA,IGKH,IS3,T)$(IAGKN(IA,IGKH) AND (IGCOMB1(IGKH) OR IGCOMB2(IGKH)) AND (GDATA(IGKH,'GDCOMBSUP') LT 1))..
         GDATA(IGKH,'GDCOMBSUP')*(
          (SUM(IGCOMB2$GGCOMB(IGKH,IGCOMB2), VGH_T(IA,IGCOMB2,IS3,T))
            + VGHN_T(IA,IGKH,IS3,T))$IGCOMB1(IGKH)
          + (SUM(IGCOMB1$GGCOMB(IGCOMB1,IGKH),
              VGHN_T(IA,IGCOMB1,IS3,T)
          + SUM(IGCOMB2$GGCOMB(IGCOMB1,IGCOMB2),
                VGHN_T(IA,IGCOMB2,IS3,T)))
          )$IGCOMB2(IGKH))
           =G=
         VGHN_T(IA,IGKH,IS3,T)
;