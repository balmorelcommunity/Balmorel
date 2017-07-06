Equations
                QGEQ(s,t)                       'Gas balance at Gas Pool'
                QCONSUMPTION(i,s,t)             'Gas balance at consumption node'
                QTransEntryCap(SYSENTRY,s,t)    'Entry capacity reservation constraint'
                QTransExitCap(SYSEXIT,s,t)      'Exit capacity reservation constraint'
                QStoreVol(s,T)                  'Volumetric storage capacity reservation constraint'
                QStoreInj(s,t)                  'Injection capacity reservation constraint'
                QStoreExt(s,t)                  'Extraction capacity reservation constraint'
                QGSTOREBAL(STORE,STORETYPE,S,T) 'Gas storage balance'
                QGSFXW(STORE,STORETYPE,S)       'Net gas storage for week'
                QGSVERIGE(S,T)                  'Gas balance in Sweden'
;
ALIAS (IA, IAALIAS);


QGSVERIGE(IS3,T)   ..
     VTRANSIT('OERESUND',IS3,T)
     +sum((STORE,STORETYPE)$ICA('Sweden',STORE),
       VEXT(STORE,STORETYPE,IS3,T)
      )

  =G=
 +sum(IA$ICA('Sweden',IA),
     +sum(IGE$(IAGKN(IA,IGE) and GDATA(IGE,'GDFUEL') EQ 2),
     VGEN_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* (1-GEFFDERATE(IGE,IA)))
     )
     +sum(IGH$(IAGKN(IA,IGH) and GDATA(IGH,'GDFUEL') EQ 2),
     GDATA(IGH,'GDCV')*VGHN_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')* (1-GEFFDERATE(IGH,IA)))
     )
     +sum(IGE$(IAGK_Y(IA,IGE) and GDATA(IGE,'GDFUEL') EQ 2),
     VGE_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* (1-GEFFDERATE(IGE,IA)))
     )
     +sum(IGH$(IAGK_Y(IA,IGH) and GDATA(IGH,'GDFUEL') EQ 2),
     GDATA(IGH,'GDCV')*VGH_T(IA,IGH,IS3,T) /(GDATA(IGH,'GDFE')* (1-GEFFDERATE(IGH,IA)))
     )

*      +sum(IA$ICA('Sweden',IA),ISE_DGRES_Y('SE_S_Rural',IS3,T))
*      +sum(IA$ICA('Sweden',IA),ISE_DGOTH_Y('SE_S_Rural',IS3,T))
      +IDGRES_Y(IA,IS3,T)
      +IDGOTH_Y(IA,IS3,T)

 )
 +sum((STORE,STORETYPE)$ICA('Sweden',STORE),
      VINJ(STORE,STORETYPE,IS3,T)
      )
 +sum((STORE,STORETYPE)$ICA('Sweden',STORE),
     +  VEXT(STORE,STORETYPE,IS3,T)*GSTOREDATA(STORETYPE,'GAS')
       )
;

QGEQ(IS3,T)      ..
      sum(SOURCE,
        VSUP(SOURCE,IS3,T)
        )
     +sum((STORE,STORETYPE)$ICA('Denmark',STORE),
     +  VEXT(STORE,STORETYPE,IS3,T)
       )
     -sum((STORE,STORETYPE)$ICA('Denmark',STORE),
     +  VEXT(STORE,STORETYPE,IS3,T)*GSTOREDATA(STORETYPE,'GAS')
       )
  =G=
      sum(IA$ICA('Denmark',IA),
        VGUD(IA,IS3,T)
       )
     +sum((STORE,STORETYPE)$ICA('Denmark',STORE),
           VINJ(STORE,STORETYPE,IS3,T)
     )
     +sum(SOURCE,
       VEXP(SOURCE,IS3)
     )
     +sum(TRANSIT,
       VTRANSIT(TRANSIT,IS3,T)
     )
     ;


$ifi not %MR%==yes QCONSUMPTION(IA,IS3,T)$ICA('Denmark',IA)    ..
$ifi %MR%==yes  QCONSUMPTION(IA,IS3,T)$(ICA('Denmark',IA) and not NOTMR(IA))    ..

       VGUD(IA,IS3,T)
  =G=
         IDGRES_Y(IA,IS3,T)
     +   IDGOTH_Y(IA,IS3,T)
     +sum(IGE$(IAGKN(IA,IGE) and GDATA(IGE,'GDFUEL') EQ 2),
     VGEN_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* (1-GEFFDERATE(IGE,IA)))
     )
     +sum(IGH$(IAGKN(IA,IGH) and GDATA(IGH,'GDFUEL') EQ 2),
     GDATA(IGH,'GDCV')*VGHN_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')* (1-GEFFDERATE(IGH,IA)))
     )
     +sum(IGE$(IAGK_Y(IA,IGE) and GDATA(IGE,'GDFUEL') EQ 2),
     VGE_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* (1-GEFFDERATE(IGE,IA)))
     )
     +sum(IGH$(IAGK_Y(IA,IGH) and GDATA(IGH,'GDFUEL') EQ 2),
     GDATA(IGH,'GDCV')*VGH_T(IA,IGH,IS3,T) /(GDATA(IGH,'GDFE')* (1-GEFFDERATE(IGH,IA)))
     )
$ifi %MR%==yes  +SUM((IAALIAS,G)$MR2CENTRAL(IA,IAALIAS,G),
$ifi %MR%==yes       +(
$ifi %MR%==yes       VGEN_T(IAALIAS,G,IS3,T)/(GDATA(G,'GDFE')* (1-GEFFDERATE(G,IA)))
$ifi %MR%==yes       )$(IGE(G) and IAGKN(IAALIAS,G) and GDATA(G,'GDFUEL') EQ 2)
$ifi %MR%==yes       +(
$ifi %MR%==yes       GDATA(G,'GDCV')*VGHN_T(IAALIAS,G,IS3,T)/(GDATA(G,'GDFE')* (1-GEFFDERATE(G,IAALIAS)))
$ifi %MR%==yes       )$(IGH(G) and IAGKN(IAALIAS,G) and GDATA(G,'GDFUEL') EQ 2)
$ifi %MR%==yes       +(
$ifi %MR%==yes       VGE_T(IAALIAS,G,IS3,T)/(GDATA(G,'GDFE')* (1-GEFFDERATE(G,IAALIAS)))
$ifi %MR%==yes       )$(IGE(G) and IAGK_Y(IAALIAS,G) and GDATA(G,'GDFUEL') EQ 2)
$ifi %MR%==yes       +(
$ifi %MR%==yes       GDATA(G,'GDCV')*VGH_T(IAALIAS,G,IS3,T) /(GDATA(G,'GDFE')* (1-GEFFDERATE(G,IAALIAS)))
$ifi %MR%==yes       )$(IGH(G) and IAGK_Y(IAALIAS,G) and GDATA(G,'GDFUEL') EQ 2)
$ifi %MR%==yes  )

$ifi %HEATING%==yes + sum(HEAT$HEATMR(HEAT,IA), VGX(IA,HEAT,IS3,T))
      ;

QTransEntryCap(SYSENTRY,IS3,T)     ..
$ifi %bb3%== yes    ITC_EN_Y(SYSENTRY)
$ifi %bb3%== yes +  ITC_EN_M(SYSENTRY,IS3,T)
$ifi %bb3%== yes +  sum(DAY$DAYT(DAY,T), VTC_EN_D(SYSENTRY,IS3,DAY))
$ifi %bb1%== yes VTC_EN_Y(SYSENTRY)
$ifi %bb1%== yes + sum(IMONTH$MONTHSSS(IMONTH,IS3), VTC_EN_M(SYSENTRY,IMONTH))
$ifi %bb2%== yes VTC_EN_Y(SYSENTRY)
$ifi %bb2%== yes + sum(IMONTH$MONTHSSS(IMONTH,IS3), VTC_EN_M(SYSENTRY,IMONTH))
      +  VTC_EN_W(SYSENTRY,IS3)
      +  VTC_EN_FLEX(SYSENTRY,IS3,T)
  =G=
       (VSUP('Nybro',IS3,T)-VEXP('Nybro',IS3))$(SAMEAS(SYSENTRY,'Nybro'))
      +VSUP('Ellund',IS3,T)$(SAMEAS(SYSENTRY,'Ellund')) ;

QTransExitCap(SYSEXIT,IS3,T)      ..
$ifi %bb3%== yes    ITC_EX_Y(SYSEXIT)
$ifi %bb3%== yes +  ITC_EX_M(SYSEXIT,IS3,T)
$ifi %bb3%== yes +  sum(DAY$DAYT(DAY,T), VTC_EX_D(SYSEXIT,IS3,DAY))
$ifi %bb1%== yes VTC_EX_Y(SYSEXIT)
$ifi %bb1%== yes + sum(IMONTH$MONTHSSS(IMONTH,IS3), VTC_EX_M(SYSEXIT,IMONTH))
$ifi %bb2%== yes VTC_EX_Y(SYSEXIT)
$ifi %bb2%== yes + sum(IMONTH$MONTHSSS(IMONTH,IS3), VTC_EX_M(SYSEXIT,IMONTH))
      +  VTC_EX_W(SYSEXIT,IS3)
      +  VTC_EX_FLEX(SYSEXIT,IS3,T)
  =G=

      sum(IA$ICA('Denmark',IA),
         VGUD(IA,IS3,T)
       )$(SAMEAS(SYSEXIT,'DK-EXIT'))
      +
          VEXP('Ellund',IS3)$(SAMEAS(SYSEXIT,'Ellund'))
*      +   VEXP('Oeresund',IS3)$(SAMEAS(SYSEXIT,'Oeresund'))
      +   VTRANSIT('Oeresund',IS3,T)$(SAMEAS(SYSEXIT,'Oeresund'))
;

QStoreVol(IS3,T)         ..
       sum(SCON,
         VSC(SCON)*SCONDATA(SCON,'VOLCAP')
       )
*$ifi %bb2%==yes +SUM((STORE,STORETYPE),VGINVSTORE(STORE,STORETYPE)$STOREINV(STORE, STORETYPE)
*$ifi %bb2%==yes -VGINVSTORE.l(STORE,STORETYPE)$STOREINV(STORE, STORETYPE))
  =G=  sum((STORE,STORETYPE),
         VSTOCK(STORE,STORETYPE,IS3,T)
       );

QStoreInj(IS3,T)         ..
       sum(SCON,
$ifi %bb1%== yes VSC(SCON)
$ifi %bb2%== yes VSC(SCON)
$ifi %bb3%== yes ISC(SCON)
         *SCONDATA(SCON,'INJCAP')*SCONDATA(SCON,'VOLCAP')
       )
*$ifi %bb2%==yes +SUM((STORE,STORETYPE),VGINVINJ(STORE,STORETYPE)$STOREINV(STORE, STORETYPE)
*$ifi %bb2%==yes +(GSTOREDATA(STORETYPE,'INJEFFECT')*VGINVSTORE(STORE,STORETYPE))$STOREINV(STORE, STORETYPE)
*$ifi %bb2%==yes -VGINVINJ.l(STORE,STORETYPE)$STOREINV(STORE, STORETYPE)
*$ifi %bb2%==yes -(GSTOREDATA(STORETYPE,'INJEFFECT')*VGINVSTORE.l(STORE,STORETYPE))$STOREINV(STORE, STORETYPE))
  =G=
       sum((STORE,STORETYPE),
         VINJ(STORE,STORETYPE,IS3,T)
       );

QStoreExt(IS3,T)         ..
       sum(SCON,
$ifi %bb1%== yes VSC(SCON)
$ifi %bb2%== yes VSC(SCON)
$ifi %bb3%== yes ISC(SCON)
         *SCONDATA(SCON,'EXTCAP')*SCONDATA(SCON,'VOLCAP')
       )
*$ifi %bb2%==yes +SUM((STORE,STORETYPE),VGINVEXT(STORE,STORETYPE)$STOREINV(STORE, STORETYPE)
*$ifi %bb2%==yes +(GSTOREDATA(STORETYPE,'EXTEFFECT')*VGINVSTORE(STORE,STORETYPE))$STOREINV(STORE, STORETYPE)
*$ifi %bb2%==yes -VGINVEXT.l(STORE,STORETYPE)$STOREINV(STORE, STORETYPE)
*$ifi %bb2%==yes -(GSTOREDATA(STORETYPE,'EXTEFFECT')*VGINVSTORE.l(STORE,STORETYPE))$STOREINV(STORE, STORETYPE))
  =G=
       sum((STORE,STORETYPE),
         VEXT(STORE,STORETYPE,IS3,T)
       );

QGSTOREBAL(STORE,STORETYPE,S,T)..
       VSTOCK(STORE,STORETYPE,S,T)
        +IHOURSINST(S,T)*(VINJ(STORE,STORETYPE,S,T)-VEXT(STORE,STORETYPE,S,T))
=G=   VSTOCK(STORE,STORETYPE,S,T+1)$(ord(T)<card(T))
      +SUM(ITALIAS$(ord(ITALIAS)=1),VSTOCK(STORE,STORETYPE,S++1,ITALIAS))$(ord(T)=card(T))
;

QGSFXW(STORE,STORETYPE,IS3)     ..
     sum(T,IHOURSINST(IS3,T)*
       (VEXT(STORE,STORETYPE,IS3,T)
       -VINJ(STORE,STORETYPE,IS3,T)
     )
       )
     =G=
       IGSFXW(STORE,STORETYPE,IS3)
       ;

EQUATIONS
         QGSUPPLY_MAX(SOURCE,S,T)         'Supply limit at supply node'
         QGEXP_MAX(SOURCE,S)              'Export limit at supply node'
         QGTRANSIT_MAX(TRANSIT,S,T)       'Transit limit'
         QGINJ_MAX(STORE,STORETYPE,S,T)   'Injection limit at storage node'
         QGEXT_MAX(STORE,STORETYPE,S,T)   'Extraction limit at storage node'
         QGSTORE_MAX(STORE,STORETYPE,S,T) 'Storage limit at storage node'
         QGDEV_MAX(SYSEXIT,S,T)           'Delivery limit at exit point or zone'
         ;

QGTRANSIT_MAX(TRANSIT(AAA),IS3,T) ..
            SUM(SOURCE(AAA), IEXP_MAX(SOURCE)
            +sum(NGINV,EXPEFFECT(NGINV,SOURCE)*VGINFINV(NGINV)))
            =G=
            VTRANSIT(TRANSIT,IS3,T);


QGSUPPLY_MAX(SOURCE,IS3,T) ..
            ISUPPLY_MAX(SOURCE)
            +sum(NGINV,SUPEFFECT(NGINV,SOURCE)*VGINFINV(NGINV))
            =G=
            VSUP(SOURCE,IS3,T);

QGEXP_MAX(SOURCE,IS3) ..
            IEXP_MAX(SOURCE)
            +sum(NGINV,EXPEFFECT(NGINV,SOURCE)*VGINFINV(NGINV))
            +sum((C,GNETSTEPS), GNET_EXP_EFFECT(C,SOURCE)*VGNETINV(C,GNETSTEPS))
            =G=
            1.21*VEXP(SOURCE,IS3);

QGDEV_MAX(SYSEXIT,IS3,T)$(IDEV_MAX(SYSEXIT) > 0) ..
            IDEV_MAX(SYSEXIT)
$ifi %BB2%==yes            +sum(NGINV,DEVEFFECT(NGINV,SYSEXIT)*VGINFINV(NGINV))
            +sum((C,GNETSTEPS), GNET_DEV_EFFECT(C,SYSEXIT)*VGNETINV(C,GNETSTEPS))
            =G=
                 1.21*sum(IA$ICA('Denmark',IA),
                         VGUD(IA,IS3,T)
                 )$(SAMEAS(SYSEXIT,'DK-EXIT'))
            ;


QGINJ_MAX(STORE,STORETYPE,IS3,T)..
             IINJ_MAX(STORE,STORETYPE)
            +VGINVINJ(STORE,STORETYPE)$STOREINV(STORE, STORETYPE)
            +(GSTOREDATA(STORETYPE,'INJEFFECT')*VGINVSTORE(STORE,STORETYPE))$STOREINV(STORE, STORETYPE)
          =G=
            VINJ(STORE,STORETYPE,IS3,T)
            ;

QGEXT_MAX(STORE,STORETYPE,IS3,T)..
             IEXT_MAX(STORE,STORETYPE)
            +VGINVEXT(STORE,STORETYPE)$STOREINV(STORE, STORETYPE)
            +(GSTOREDATA(STORETYPE,'EXTEFFECT')*VGINVSTORE(STORE,STORETYPE))$STOREINV(STORE, STORETYPE)
          =G=
            VEXT(STORE,STORETYPE,IS3,T)
            ;

QGSTORE_MAX(STORE,STORETYPE,IS3,T)..
             ISTORE_MAX(STORE,STORETYPE)
            +VGINVSTORE(STORE,STORETYPE)$STOREINV(STORE, STORETYPE)
          =G=
            VSTOCK(STORE,STORETYPE,IS3,T)
            ;
