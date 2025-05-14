* Flexible demand add-on. Added by Mathias Berg Rosendal

* Yearly demand has to be met in every region
EQUATION QFLEXDEMAND_YR(Y,RRR,FLEXUSER)    'Annual demand has to be met in each region (MWh)';

QFLEXDEMAND_YR(IY411,IR,FLEXUSER)$FLEXYDEMAND(IY411,IR,FLEXUSER)..
   SUM((IS3,T),
      VFLEXDEMAND_T(FLEXUSER,IY411,IR,IS3,T)*IHOURSINST(IS3,T))
=E=
FLEXYDEMAND(IY411,IR,FLEXUSER)
;

* Seasonal demand has to be met in every region 
EQUATION QFLEXDEMAND_SR(Y,SSS,RRR,FLEXUSER)    'Seasonal demand has to be met in each region (MWh)';
QFLEXDEMAND_SR(IY411,IS3,IR,FLEXUSER)$FLEXSDEMAND(IY411,IS3,IR,FLEXUSER)..
   SUM(T,
      VFLEXDEMAND_T(FLEXUSER,IY411,IR,IS3,T)*WEIGHT_S(IS3)/IWEIGHSUMT)
=E=
FLEXSDEMAND(IY411,IS3,IR,FLEXUSER)
;

* Make demand flat within a season by equating terms with each other
EQUATION QINFLEXDEM_T(FLEXUSER, YYY, RRR, SSS, TTT) 'Flatten demand within a season';
QINFLEXDEM_T(FLEXUSER, IY411, IR, IS3, T)$(ord(T) > 1)..
   VFLEXDEMAND_T(FLEXUSER,IY411,IR,IS3,T) 
   =E=
   VFLEXDEMAND_T(FLEXUSER,IY411,IR,IS3,T++1)
; 

* Limit maximum flexible consumption
VFLEXDEMAND_T.UP(FLEXUSER,Y,RRR,S,T) = FLEXMAXLIMIT(FLEXUSER, RRR, S, T);
