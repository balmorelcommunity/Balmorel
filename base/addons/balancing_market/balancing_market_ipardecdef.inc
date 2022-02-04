*Balancing market introduced by Juan Gea-Bermudez and Polyneikis Kanellas

PARAMETER IGE_T_DOWN_FORCED(Y,AAA,G,S,T) 'Down re-dispatch of the commited electricity dispatch forced with respect to previous runs';
PARAMETER IGH_T_DOWN_FORCED(Y,AAA,G,S,T) 'Down re-dispatch of the commited heat dispatch forced with respect to previous runs';
$ifi %HYDROGEN%==yes   PARAMETER IGH2_T_DOWN_FORCED(Y,AAA,G,S,T) 'Down re-dispatch of the commited H2 dispatch forced with respect to previous runs';
$ifi %HYDROGEN%==yes   PARAMETER IGBIOMETHANE_T_DOWN_FORCED(Y,AAA,G,S,T) 'Down re-dispatch of the commited biomethane dispatch forced with respect to previous runs';

$ifi not %BALANCINGRUNPURPOSE%==TSOREDISPATCH $goto NO_TSOREDISPATCH
$ifi %FORCEDDOWNREDISPATCH%==yes $goto NO_FORCEDDOWNREDISPATCH
*----Calculation of forced down re-dispatch-----
*Initializating parameters
IGE_T_DOWN_FORCED(Y,IA,G,S,T)=0;
IGH_T_DOWN_FORCED(Y,IA,G,S,T)=0;
$ifi %HYDROGEN%==yes IGH2_T_DOWN_FORCED(Y,IA,G,S,T)=0;
$ifi %HYDROGEN%==yes IGBIOMETHANE_T_DOWN_FORCED(Y,IA,G,S,T)=0;


*----Due to forecast errors----
*Wind
LOOP((Y,IA,IGWND,S,T)$GE_T(Y,IA,IGWND,S,T),
IGE_T_DOWN_FORCED(Y,IA,IGWND,S,T)=-MIN(0,
$ifi %WNDFLH_DOL%==AAA (WNDFLH(IA) * (
$ifi %WNDFLH_DOL%==AAA_GGG     (WNDFLH(IA,IGWND) * (
            GKFX(Y,IA,IGWND)
                 )  * WND_VAR_T(IA,S,T) * (1$(NOT IGKRATE(IA,IGWND,S,T)) + IGKRATE(IA,IGWND,S,T))) / IWND_SUMST(IA)
- GE_T(Y,IA,IGWND,S,T))
);

*Solar PV
LOOP((Y,IA,IGSOLE,S,T)$GE_T(Y,IA,IGSOLE,S,T),
IGE_T_DOWN_FORCED(Y,IA,IGSOLE,S,T)=-MIN(0,
$ifi %SOLEFLH_DOL%==AAA         (SOLEFLH(IA) * (
$ifi %SOLEFLH_DOL%==AAA_GGG     (SOLEFLH(IA,IGSOLE) * (
            GKFX(Y,IA,IGSOLE)
                 )  * SOLE_VAR_T(IA,S,T) * (1$(NOT IGKRATE(IA,IGSOLE,S,T)) + IGKRATE(IA,IGSOLE,S,T))) / ISOLESUMST(IA)
- GE_T(Y,IA,IGSOLE,S,T))
);



*Hydro run of river
LOOP((Y,IA,IGHYRR,S,T)$GE_T(Y,IA,IGHYRR,S,T),
IGE_T_DOWN_FORCED(Y,IA,IGHYRR,S,T)=-MIN(0,
           (WTRRRFLH(IA) * (
             GKFX(Y,IA,IGHYRR)
                 )  * WTRRRVAR_T(IA,S,T) * (1$(NOT IGKRATE(IA,IGHYRR,S,T)) + IGKRATE(IA,IGHYRR,S,T))) / IWTRRRSUM(IA)
- GE_T(Y,IA,IGHYRR,S,T))
);

*Wave energy
LOOP((Y,IA,IGWAVE,S,T)$GE_T(Y,IA,IGWAVE,S,T),
IGE_T_DOWN_FORCED(Y,IA,IGWAVE,S,T)=-MIN(0,
           (WAVEFLH(IA) * (
             GKFX(Y,IA,IGWAVE)
                 )  * WAVE_VAR_T(IA,S,T) * (1$(NOT IGKRATE(IA,IGWAVE,S,T)) + IGKRATE(IA,IGWAVE,S,T))) / IWAVESUMST(IA)
- GE_T(Y,IA,IGWAVE,S,T))
);

*Solar heating
LOOP((Y,IA,IGSOLH,S,T)$GH_T(Y,IA,IGSOLH,S,T),
IGH_T_DOWN_FORCED(Y,IA,IGSOLH,S,T)=-MIN(0,
$ifi %SOLHFLH_DOL%==AAA         (SOLHFLH(IA) * (
$ifi %SOLHFLH_DOL%==AAA_GGG     (SOLHFLH(IA,IGH) * (
            GKFX(Y,IA,IGSOLH)
                 )  * SOLH_VAR_T(IA,S,T) * (1$(NOT IGKRATE(IA,IGSOLH,S,T)) + IGKRATE(IA,IGSOLH,S,T))) / ISOLHSUMST(IA)
- GH_T(Y,IA,IGSOLH,S,T))
);

$ONTEXT
*---Due to ramping limits---- TO BE FINISHED
*Condensing units
LOOP((Y,IA,IGCND,S,T)$(GE_T(Y,IA,IGCND,S,T) AND IGUC(IGCND) AND (1 GT CHRONOHOUR(S,T)*GDATA(IGCND,'GDUCRAMPU'))
$ifi not %SEASONALLINKUC%==yes AND (NOT (ORD(S) EQ 1 AND (ORD(T) EQ 1)))
$ifi %SEASONALLINKUC%==yes AND (NOT (ORD(T) EQ 1))
AND IGE_T_DOWN_FORCED(Y,IA,IGCND,S,T) AND GDATA(IGUC,'GDUCRAMPU'))=-MIN(0,
(GE_T(Y,IA,IGCND,S,T)
$ifi not %SEASONALLINKUC%==yes -GE_T(Y,IA,IGCND,S,T-1)
$ifi %SEASONALLINKUC%==yes  +GE_T(IY411,IA,IGCND,S-1,T--1)$(ORD(T) EQ 1) + GE_T(IY411,IA,IGCND,S,T-1)$(NOT (ORD(T) EQ 1))
)/NUMBEROFT -RAMPINGLIMIT
);
$OFFTEXT

$label NO_FORCEDDOWNREDISPATCH
$label NO_TSOREDISPATCH
