SET YREF(YYY) /2005/;
* YREF=yes$Y;
SET SREF(SSS) /S23/;
*SREF=YES$S;

SET T2(TTT)
/
T001*T005
/;
ALIAS(TTT,TTT2);
ALIAS(S,SLOOP);

PARAMETER NRSEGMENTS(T2)
/
T001     15
T002     25
T003     30
T004     28
T005     70
$ontext
T001     15
T002     15
T003     15
T004     15
T005     15
T006     15
T007     15
T008     15
T009     15
T010     15
T011     18

T001      1
T002      1
T003      2
T004      3
T005      5
T006      8
T007      13
T008      21
T009      34
T010      55
T011      25
$offtext
/;


BINARY VARIABLE VT2TTT(T2,TTT);

FREE VARIABLE VDIST;

EQUATIONS
         QDIST
         QROW(TTT)
         QNRSEGMENTS(T2)
;
QROW(TTT)            .. SUM(T2,VT2TTT(T2,TTT))=E= 1;
QNRSEGMENTS(T2)     .. SUM(TTT,VT2TTT(T2,TTT))=E= NRSEGMENTS(T2);
$ontext
QDIST..
VDIST =E=
*     SUM((YREF,SREF), (  SUM(IR$IDE_SUMST(IR),DE(YREF,IR)/IDE_SUMST(IR)*SUM((T2,TTT2),(DE_VAR_T(IR,SREF,TTT2))*VT2TTT(T2,TTT2)/NRSEGMENTS(T2)))
*                                                  -SUM(TTT,SUM(IR$IDE_SUMST(IR),DE(YREF,IR)*(DE_VAR_T(IR,SREF,TTT)/IDE_SUMST(IR)))))**2 )
IOF0000001*
     SUM((YREF,SREF), SUM(TTT,POWER(  SUM(IR$IDE_SUMST(IR),DE(YREF,IR)/IDE_SUMST(IR)*SUM((T2,TTT2),(DE_VAR_T(IR,SREF,TTT2))*VT2TTT(T2,TTT2)/NRSEGMENTS(T2)))
                                                  -SUM(IR$IDE_SUMST(IR),DE(YREF,IR)*(DE_VAR_T(IR,SREF,TTT)/IDE_SUMST(IR))),2 )))

    +SUM((YREF,SREF), POWER(  SUM(IA$IDH_SUMST(IA),DH(YREF,IA)*(DH_VAR_T(IA,SREF,TTT)/IDH_SUMST(IA))*VT2TTT(T2,TTT)/NRSEGMENTS(T2)
                                                  -DH(YREF,IA)*(DH_VAR_T(IA,SREF,TTT)/IDH_SUMST(IA))),2 ))
    +SUM((YREF,SREF), POWER(  SUM(IR$IX3FXSUMST(IR),   X3FX(YREF,IR)*(X3FX_VAR_T(IR,SREF,TTT)/IX3FXSUMST(IR))*VT2TTT(T2,TTT)/SUM(TTT2,VT2TTT(T2,TTT))
                                  -X3FX(YREF,IR)*(X3FX_VAR_T(IR,SREF,TTT)/IX3FXSUMST(IR))),2 ))
    +SUM((YREF,SREF), POWER( SUM((IGWND,IA)$IWND_SUMST(IA),((WNDFLH(IA) * (GKFX(YREF,IA,IGWND))* WND_VAR_T(IA,SREF,TTT)) / IWND_SUMST(IA))*VT2TTT(T2,TTT)/SUM(TTT2,VT2TTT(T2,TTT))
                                -((WNDFLH(IA) * (GKFX(YREF,IA,IGWND))* WND_VAR_T(IA,SREF,TTT)) / IWND_SUMST(IA))),2 ))
    +SUM((YREF,SREF), POWER( SUM((IGHYRR,IA)$IWTRRRSUM(IA),((WTRRRFLH(IA) * (GKFX(YREF,IA,IGHYRR))* WTRRRVAR_T(IA,SREF,TTT)) / IWTRRRSUM(IA))*VT2TTT(T2,TTT)/SUM(TTT2,VT2TTT(T2,TTT))
                                -((WTRRRFLH(IA) * (GKFX(YREF,IA,IGHYRR))* WTRRRVAR_T(IA,SREF,TTT)) / IWTRRRSUM(IA))),2 ))
    +SUM((YREF,SREF), POWER( SUM((IGSOLE,IA)$ISOLESUMST(IA),((SOLEFLH(IA) * (GKFX(YREF,IA,IGSOLE))* SOLE_VAR_T(IA,SREF,TTT)) / ISOLESUMST(IA))*VT2TTT(T2,TTT)/SUM(TTT2,VT2TTT(T2,TTT))
                                -((SOLEFLH(IA) * (GKFX(YREF,IA,IGSOLE))* SOLE_VAR_T(IA,SREF,TTT)) / ISOLESUMST(IA))),2 ))
$ifi %GAS%==yes     +SUM((YREF,SREF), POWER(  SUM(IA$IDGRES_SUMVAR(IA),DGRES(YREF,IA)*(DGRES_VAR(IA,SREF,TTT)/IDGRES_SUMVAR(IA))*VT2TTT(T2,TTT)/SUM(TTT2,VT2TTT(T2,TTT))
$ifi %GAS%==yes                                                   -DGRES(YREF,IA)*(DGRES_VAR(IA,SREF,TTT)/IDGRES_SUMVAR(IA))),2 ))
$ifi %GAS%==yes     +SUM((YREF,SREF), POWER(  SUM(IA$IDGOTH_SUMVAR(IA),DGOTH(YREF,IA)*(DGOTH_VAR(IA,SREF,TTT)/IDGOTH_SUMVAR(IA))*VT2TTT(T2,TTT)/SUM(TTT2,VT2TTT(T2,TTT))
$ifi %GAS%==yes                                                   -DGOTH(YREF,IA)*(DGOTH_VAR(IA,SREF,TTT)/IDGOTH_SUMVAR(IA))),2 ))
* Her kunne tilføjes variationer for sveriges andet gasforbrug
;
$offtext

* ----
variable QUAD_DE(yref,SSS,ttt),
         QUAD_DH(yref,SSS,ttt),
         QUAD_X3(yref,SSS,ttt),
         QUAD_WND(yref,SSS,ttt),
         QUAD_WTRRR(yref,SSS,ttt),
         QUAD_ISOLE(yref,SSS,ttt)
$ifi %GAS%==yes         QUAD_DGRES(yref,SSS,ttt),
$ifi %GAS%==yes         QUAD_DGOTH(yref,SSS,ttt)
;
equation defQUAD_DE(yref,SSS,ttt),
         defQUAD_DH(yref,SSS,ttt),
         defQUAD_X3(yref,SSS,ttt),
         defQUAD_WND(yref,SSS,ttt),
         defQUAD_WTRRR(yref,SSS,ttt),
         defQUAD_ISOLE(yref,SSS,ttt)
$ifi %GAS%==yes         defQUAD_DGRES(yref,SSS,ttt),
$ifi %GAS%==yes         defQUAD_DGOTH(yref,SSS,ttt)
;

QDIST.. VDIST =E= 1e-3*IOF0000001*SUM((YREF,SREF,TTT), sqr(QUAD_DE(yref,sref,ttt)))
                 +1e-3*IOF0000001*SUM((YREF,SREF,TTT), sqr(QUAD_DH(yref,sref,ttt)))
                 +1e-3*IOF0000001*SUM((YREF,SREF,TTT), sqr(QUAD_X3(yref,sref,ttt)))
                 +1e-3*IOF0000001*SUM((YREF,SREF,TTT), sqr(QUAD_WND(yref,sref,ttt)))
                 +1e-3*IOF0000001*SUM((YREF,SREF,TTT), sqr(QUAD_WTRRR(yref,sref,ttt)))
                 +1e-3*IOF0000001*SUM((YREF,SREF,TTT), sqr(QUAD_ISOLE(yref,sref,ttt)))
$ifi %GAS%==yes  +1e-3*IOF0000001*SUM((YREF,SREF,TTT), sqr(QUAD_DGRES(yref,sref,ttt)))
$ifi %GAS%==yes  +1e-3*IOF0000001*SUM((YREF,SREF,TTT), sqr(QUAD_DGOTH(yref,sref,ttt)))
;


defQUAD_DE(yref,sref,ttt)                            ..  QUAD_DE(yref,sref,ttt) =e= SUM(IR$IDE_SUMST(IR), DE(YREF,IR)/IDE_SUMST(IR)*
                                                         (SUM((T2,TTT2), DE_VAR_T(IR,SREF,TTT2)/NRSEGMENTS(T2)*VT2TTT(T2,TTT2))   - DE_VAR_T(IR,SREF,TTT) )) ;

defQUAD_DH(yref,sref,ttt)                            ..  QUAD_DH(yref,sref,ttt) =e= SUM(IA$IDH_SUMST(IA), DH(YREF,IA)/IDH_SUMST(IA)*
                                                         (SUM((T2,TTT2), DH_VAR_T(IA,SREF,TTT2)/NRSEGMENTS(T2)*VT2TTT(T2,TTT2))   - DH_VAR_T(IA,SREF,TTT)));

defQUAD_X3(yref,sref,ttt)                            ..  QUAD_X3(yref,sref,ttt) =e= SUM(IR$IX3FXSUMST(IR), X3FX(YREF,IR)/IX3FXSUMST(IR)*
                                                         (SUM((T2,TTT2), X3FX_VAR_T(IR,SREF,TTT2)/NRSEGMENTS(T2)*VT2TTT(T2,TTT2))  -X3FX_VAR_T(IR,SREF,TTT)));

defQUAD_WND(yref,sref,ttt)                           ..  QUAD_WND(yref,sref,ttt) =e=SUM((IGWND,IA)$IWND_SUMST(IA),WNDFLH(IA) *GKFX(YREF,IA,IGWND)/ IWND_SUMST(IA)*
                                                         (SUM((T2,TTT2), WND_VAR_T(IA,SREF,TTT2)/NRSEGMENTS(T2)*VT2TTT(T2,TTT2))   -WND_VAR_T(IA,SREF,TTT)));

defQUAD_WTRRR(yref,sref,ttt)                         ..  QUAD_WTRRR(yref,sref,ttt) =e=SUM((IGHYRR,IA)$IWTRRRSUM(IA),WTRRRFLH(IA) *GKFX(YREF,IA,IGHYRR)/ IWTRRRSUM(IA)*
                                                         (SUM((T2,TTT2), WTRRRVAR_T(IA,SREF,TTT2)/NRSEGMENTS(T2)*VT2TTT(T2,TTT2))  -WTRRRVAR_T(IA,SREF,TTT)));

defQUAD_ISOLE(yref,sref,ttt)                         ..  QUAD_ISOLE(yref,sref,ttt) =e=SUM((IGSOLE,IA)$ISOLESUMST(IA),SOLEFLH(IA) *GKFX(YREF,IA,IGSOLE)/ ISOLESUMST(IA)*
                                                         (SUM((T2,TTT2), SOLE_VAR_T(IA,SREF,TTT2)/NRSEGMENTS(T2)*VT2TTT(T2,TTT2))  -SOLE_VAR_T(IA,SREF,TTT)));

$ifi %GAS%==yes         defQUAD_DGRES(yref,sref,ttt) ..  QUAD_DGRES(yref,sref,ttt) =e= SUM(IA$IDGRES_SUMVAR(IA),DGRES(YREF,IA)/IDGRES_SUMVAR(IA)*
$ifi %GAS%==yes                                          (SUM((T2,TTT2), DGRES_VAR(IA,SREF,TTT2)/NRSEGMENTS(T2)*VT2TTT(T2,TTT2))   -DGRES_VAR(IA,SREF,TTT)));
$ifi %GAS%==yes         defQUAD_DGOTH(yref,sref,ttt) ..  QUAD_DGOTH(yref,sref,ttt) =e= SUM(IA$IDGOTH_SUMVAR(IA),DGOTH(YREF,IA)/IDGOTH_SUMVAR(IA)*
$ifi %GAS%==yes                                          (SUM((T2,TTT2), DGOTH_VAR(IA,SREF,TTT2)/NRSEGMENTS(T2)*VT2TTT(T2,TTT2))   -DGOTH_VAR(IA,SREF,TTT)));

* ----


MODEL ASSIGNMENTS
/
                 QDIST
                 QROW
                 QNRSEGMENTS
                 defQUAD_DE
                 defQUAD_DH
                 defQUAD_X3
                 defQUAD_WND
                 defQUAD_WTRRR
                 defQUAD_ISOLE
$ifi %GAS%==yes  defQUAD_DGRES
$ifi %GAS%==yes  defQUAD_DGOTH
/;
*VT2TTT.l(T2,TTT)=1;
OPTION MIQCP=cplex;
SET OT2TTT(S,T2,TTT);
LOOP(SLOOP,
     SREF(S) = no;
     SREF(S) = yes$(ord(SLOOP)=ord(S));
     SOLVE ASSIGNMENTS using MIQCP MINIMIZING VDIST;
     OT2TTT(SLOOP,T2,TTT)=yes$VT2TTT.l(T2,TTT);
);
execute_unload 'TIMERES.gdx', OT2TTT;