* Flexible demand add-on. Added by Mathias Berg Rosendal

* Yearly demand has to be met in every region
EQUATION  QFLEXDEMAND_YR(Y,RRR,FLEXUSER)    'Annual transport demand has to be met in each region (MWh)';

QFLEXDEMAND_YR(IY411,IR,FLEXUSER)$FLEXYDEMAND(IY411,IR,FLEXUSER)..
   SUM((IS3,T),
      VFLEXDEMAND_T(FLEXUSER,IY411,IR,IS3,T)*IHOURSINST(IS3,T))
=E=
FLEXYDEMAND(IY411,IR,FLEXUSER)
;

* Seasonal demand has to be met in every region 
EQUATION  QFLEXDEMAND_SR(Y,SSS,RRR,FLEXUSER)    'Annual transport demand has to be met in each region (MWh)';
QFLEXDEMAND_SR(IY411,IS3,IR,FLEXUSER)$FLEXSDEMAND(IY411,IS3,IR,FLEXUSER)..
   SUM(T,
      VFLEXDEMAND_T(FLEXUSER,IY411,IR,IS3,T)*WEIGHT_S(IS3)/IWEIGHSUMT)
=E=
FLEXSDEMAND(IY411,IS3,IR,FLEXUSER)
;

