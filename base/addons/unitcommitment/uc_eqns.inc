* File uc_eqns.inc
* Unit commitment add-on to Balmorel.
* Implemented by Hans Ravn 2006-2007.
* Revised and enhanced by Lars Bregnsbæk 2011.

* Equations


EQUATION  QUCMINVGF(AAA,G,S,T)   'Unit commitment: Fuel consumption above minimum (of units online)';
EQUATION  QUCMINVGFN(AAA,G,S,T)  'Unit commitment: Fuel consumption above minimum (of units online), new units';
EQUATION  QUCMAXVGF(AAA,G,S,T)   'Unit commitment: Fuel consumption below maximum (of units online)';
EQUATION  QUCMAXVGFN(AAA,G,S,T)  'Unit commitment: Fuel consumption below maximum (of units online), new units';
EQUATION  QUCSTARTQ(AAA,G,S,T)   'Unit commitment: on-off logic';
EQUATION  QUCSTARTQN(AAA,G,S,T)  'Unit commitment: on-off logic, new units';
EQUATION  QUCTEST                'Unit commitment: limit the number of commitments within a model run; for test purpose only';

* QUCTEST is for test purpose only, comment out otherwise in the model definition.
* QUCTEST limits the number of commitments within a model run.
* The number on the right hand side is hard coded, may be adopted to the case at hand.
QUCTEST$(CARD(IGUC) GT 0)..
  SUM((IA,IGUC)$IAGK_Y(IA,IGUC), SUM((IS3,T), VUCU(IA,IGUC,IS3,T) )) =L= 20
;

$ifi %UnitCmin%==yes    EQUATION  QUCUT(AAA,G,S,T)      'Unit commitment: Number of unit startups respecting minimum off time and plant capacity.';
$ifi %UnitCmin%==yes    EQUATION  QUCUTN(AAA,G,S,T)     'Unit commitment: Number of unit startups respecting minimum off time and plant capacity, new units.';
$ifi %UnitCmin%==yes    EQUATION  QUCDT(AAA,G,S,T)      'Unit commitment: Number of unit shutdowns respecting minimum on time and number of units on.';
$ifi %UnitCmin%==yes    EQUATION  QUCDTN(AAA,G,S,T)     'Unit commitment: Number of unit shutdowns respecting minimum on time and number of units on, new units.';

$ifi %UnitCramp%==yes   EQUATION  QUCRAMPU(AAA,G,S,T)   'Unit commitment: Unit up-ramping below unit up-gradient for unit on and below minimum fuel consumption during unit startup.';
$ifi %UnitCramp%==yes   EQUATION  QUCRAMPUN(AAA,G,S,T)  'Unit commitment: Unit up-ramping below unit up-gradient for unit on and below minimum fuel consumption during unit startup, new units.';
$ifi %UnitCramp%==yes   EQUATION  QUCRAMPD(AAA,G,S,T)   'Unit commitment: Unit down-ramping below unit down-gradient for unit on and below minimum fuel consumption during unit shutdown.';
$ifi %UnitCramp%==yes   EQUATION  QUCRAMPDN(AAA,G,S,T)  'Unit commitment: Unit down-ramping below unit down-gradient for unit on and below minimum fuel consumption during unit shutdown, new units.';

* System constraints
EQUATION         QUCMRUN(RRR,S,T)       'Must run unit: A number of units within a region must run at all time';
EQUATION         QNMINUSONE(RRR,S,T)    'Must run unit: Must run units must have upregulation capacity to satisfy N-1';


*============================================================================================================



QUCMINVGF(IA,IGUC,IS3,T)$IAGK_Y(IA,IGUC)..  !! 'Unit commitment: Fuel consumption above minimum (of units online)'
   VGF_T(IA,IGUC,IS3,T)
$ifi %COMBTECH%==yes + sum(IGCOMB2$GGCOMB(IGUC,IGCOMB2),VGF_T(IA,IGCOMB2,IS3,T))$IGCOMB1(IGUC)
    =G=
* Fuel consumption at minimum load is defined by Fmin = [ Emin (1-F0) +Emax*F0 ]/FE
  (
* Emin
   VUCON(IA,IGUC,IS3,T)*GDATA(IGUC,'GDUCGMIN')*GDATA(IGUC,'GDUCUNITSIZE')*(1-GDATA(IGUC,'GDUCF0'))
* Emax
   +VUCON(IA,IGUC,IS3,T)*GDATA(IGUC,'GDUCUNITSIZE')*GDATA(IGUC,'GDUCF0')
* FE
   )*(1+(1/GDATA(IGUC,'GDCB'))$IGBPR(IGUC))/(1$( IGESTO(IGUC)) + GDATA(IGUC,'GDSTOHUNLD')$IGESTO(IGUC))
       /(GDATA(IGUC,'GDFE')*GEFFRATE(IA,IGUC))
;

QUCMAXVGF(IA,IGUC,IS3,T)$IAGK_Y(IA,IGUC)..    !! 'Unit commitment: Fuel consumption below maximum (of units online)'
   VUCON(IA,IGUC,IS3,T) * GDATA(IGUC,'GDUCUNITSIZE') * (1+(1/GDATA(IGUC,'GDCB'))$IGBPR(IGUC)) / (1$(NOT IGESTO(IGUC)) + GDATA(IGUC,'GDSTOHUNLD')$IGESTO(IGUC))
         /(GDATA(IGUC,'GDFE')*GEFFRATE(IA,IGUC))
    =G=
   VGF_T(IA,IGUC,IS3,T)
$ifi %COMBTECH%==yes + sum(IGCOMB2$GGCOMB(IGUC,IGCOMB2),VGF_T(IA,IGCOMB2,IS3,T))$IGCOMB1(IGUC)
;

QUCMINVGFN(IA,IGUC,IS3,T)$IAGKN(IA,IGUC)..   !! 'Unit commitment: Fuel consumption above minimum (of units online), new units'
   VGFN_T(IA,IGUC,IS3,T)
$ifi %COMBTECH%==yes + sum(IGCOMB2$GGCOMB(IGUC,IGCOMB2),VGFN_T(IA,IGCOMB2,IS3,T))$IGCOMB1(IGUC)
    =G=
* Fuel consumption at minimum load is defined by Fmin = [ Emin (1-F0) +Emax*F0 ]/FE
  (
* Emin
   VUCONN(IA,IGUC,IS3,T)*GDATA(IGUC,'GDUCGMIN')*GDATA(IGUC,'GDUCUNITSIZE')*(1-GDATA(IGUC,'GDUCF0'))
* Emax
   +VUCONN(IA,IGUC,IS3,T)*GDATA(IGUC,'GDUCUNITSIZE')*GDATA(IGUC,'GDUCF0')
* FE
   )*(1+(1/GDATA(IGUC,'GDCB'))$IGBPR(IGUC))/(1$(NOT IGESTO(IGUC)) + GDATA(IGUC,'GDSTOHUNLD')$IGESTO(IGUC))
       /(GDATA(IGUC,'GDFE')*GEFFRATE(IA,IGUC))
;

QUCMAXVGFN(IA,IGUC,IS3,T)$IAGKN(IA,IGUC)..    !! 'Unit commitment: Fuel consumption below maximum (of units online), new units'
   VUCONN(IA,IGUC,IS3,T) * GDATA(IGUC,'GDUCUNITSIZE') * (1+(1/GDATA(IGUC,'GDCB'))$IGBPR(IGUC)) / (1$(NOT IGESTO(IGUC)) + GDATA(IGUC,'GDSTOHUNLD')$IGESTO(IGUC))
         /(GDATA(IGUC,'GDFE')*GEFFRATE(IA,IGUC))
   =G=
   VGFN_T(IA,IGUC,IS3,T)
$ifi %COMBTECH%==yes + sum(IGCOMB2$GGCOMB(IGUC,IGCOMB2),VGFN_T(IA,IGCOMB2,IS3,T))$IGCOMB1(IGUC)
;

QUCSTARTQ(IA,IGUC,IS3,T)$IAGK_Y(IA,IGUC)..   !! 'Unit commitment: on-off logic'
   VUCU(IA,IGUC,IS3,T) - VUCD(IA,IGUC,IS3,T)
    =E=
   VUCON(IA,IGUC,IS3,T) - VUCON(IA,IGUC,IS3,T--1)
;

QUCSTARTQN(IA,IGUC,IS3,T)$IAGKN(IA,IGUC)..    !! 'Unit commitment: on-off logic, new units'
   VUCUN(IA,IGUC,IS3,T) - VUCDN(IA,IGUC,IS3,T)
    =E=
   VUCONN(IA,IGUC,IS3,T) - VUCONN(IA,IGUC,IS3,T--1)
;

*============================================================================================================

*============================================================================================================
$ifi not %UnitCmin%==yes $goto UnitC_end_min

QUCUT(IAGK_Y(IA,IGUC),IS3,T)$GDATA(IGUC,'GDUCUTMIN') ..
* units start up at t
         SUM(IUCT$(ORD(IUCT) LE GDATA(IGUC,'GDUCUTMIN')), VUCU(IA,IGUC,IS3,T--(ORD(IUCT)-1)))
*   forsøg        +VUCON(IA,IGUC,IS3,T--GDATA(IGUC,'GDUCUTMIN'))
         =L=
         VUCON(IA,IGUC,IS3,T)
;

QUCDT(IAGK_Y(IA,IGUC),IS3,T)$GDATA(IGUC,'GDUCDTMIN') ..
* units shut down at t
         SUM(IUCT$(ORD(IUCT) LE GDATA(IGUC,'GDUCDTMIN')), VUCD(IA,IGUC,IS3,T--(ORD(IUCT)-1)))
         =L=
         CEIL((IGKFX_Y(IA,IGUC) + IGKVACCTOY(IA,IGUC)) / GDATA(IGUC,'GDUCUNITSIZE'))-VUCON(IA,IGUC,IS3,T)
;


QUCUTN(IAGKN(IA,IGUC),IS3,T)$GDATA(IGUC,'GDUCDTMIN') ..
* units start up at t
         VUCUN(IA,IGUC,IS3,T)
         =L=
* units off at t-1
         VGKN(IA,IGUC) / GDATA(IGUC,'GDUCUNITSIZE')+(1-0.001)
         - VUCONN(IA,IGUC,IS3,T--1)
* units have been off for less than minimum off time
         - SUM(IUCT$(( ORD(IUCT) LE GDATA(IGUC,'GDUCDTMIN'))),VUCDN(IA,IGUC,IS3,T--(ORD(IUCT)-1)))
;

QUCDTN(IAGKN(IA,IGUC),IS3,T)$GDATA(IGUC,'GDUCUTMIN') ..
* units shut down at t
         VUCDN(IA,IGUC,IS3,T)
         =L=
* units on at t-1
         VUCONN(IA,IGUC,IS3,T--1)
* units have been on for less than minimum on time
         - SUM(IUCT$((ORD(IUCT) LE GDATA(IGUC,'GDUCUTMIN'))),VUCUN(IA,IGUC,IS3,T--(ORD(IUCT)-1)))
;


$label  UnitC_end_min
*============================================================================================================


*============================================================================================================
$ifi not %UnitCramp%==yes $goto UnitC_end_ramp

QUCRAMPU(IAGK_Y(IA,IGUC),IS3,T)..
* up gradient at t
      VGF_T(IA,IGUC,IS3,T) - VGF_T(IA,IGUC,IS3,T--1)
         =L=
     (
* units under start up have an expanded gradient
         GDATA(IGUC,'GDUCGMIN')*VUCU(IA,IGUC,IS3,T)
* up gradient of units on at t excluding units under start up
        + GDATA(IGUC,'GDUCRAMPU')*(VUCON(IA,IGUC,IS3,T) - VUCU(IA,IGUC,IS3,T))
* scale unit input capacity
     )*(GDATA(IGUC,'GDUCUNITSIZE')*(1+(1/GDATA(IGUC,'GDCB'))$IGBPR(IGUC))/(1$(NOT IGESTO(IGUC)) + GDATA(IGUC,'GDSTOHUNLD')$IGESTO(IGUC))
       /(GDATA(IGUC,'GDFE')*GEFFRATE(IA,IGUC)))
;

QUCRAMPUN(IAGKN(IA,IGUC),IS3,T)..
* up gradient at t
      VGFN_T(IA,IGUC,IS3,T) - VGFN_T(IA,IGUC,IS3,T--1)
         =L=
     (
* units under start up have an exspanded gradient
         GDATA(IGUC,'GDUCGMIN')*VUCUN(IA,IGUC,IS3,T)
* up gradient of units on at t excluding units under start up
        + GDATA(IGUC,'GDUCRAMPU')*(VUCONN(IA,IGUC,IS3,T) - VUCUN(IA,IGUC,IS3,T))
* scale unit input capacity
     )*(GDATA(IGUC,'GDUCUNITSIZE')*(1+(1/GDATA(IGUC,'GDCB'))$IGBPR(IGUC))/(1$(NOT IGESTO(IGUC)) + GDATA(IGUC,'GDSTOHUNLD')$IGESTO(IGUC))
       /(GDATA(IGUC,'GDFE')*GEFFRATE(IA,IGUC)))
;

QUCRAMPD(IAGK_Y(IA,IGUC),IS3,T)..
* down gradient at t
       VGF_T(IA,IGUC,IS3,T--1) - VGF_T(IA,IGUC,IS3,T)
         =L=
     (
* units under shut down have an expanded gradient
         GDATA(IGUC,'GDUCGMIN')*VUCD(IA,IGUC,IS3,T)
* up gradient of units on at t excluding units under shutdown
        + GDATA(IGUC,'GDUCRAMPD')*VUCON(IA,IGUC,IS3,T)
* scale unit input capacity
     )*(GDATA(IGUC,'GDUCUNITSIZE')*(1+(1/GDATA(IGUC,'GDCB'))$IGBPR(IGUC))/(1$(NOT IGESTO(IGUC)) + GDATA(IGUC,'GDSTOHUNLD')$IGESTO(IGUC))
       /(GDATA(IGUC,'GDFE')*GEFFRATE(IA,IGUC)))
;

QUCRAMPDN(IAGKN(IA,IGUC),IS3,T)..
* down gradient at t
       VGFN_T(IA,IGUC,IS3,T--1) - VGFN_T(IA,IGUC,IS3,T)
         =L=
     (
* units under shut down have an expanded gradient
         GDATA(IGUC,'GDUCGMIN')*VUCDN(IA,IGUC,IS3,T)
* up gradient of units on at t excluding units under shutdown
        + GDATA(IGUC,'GDUCRAMPD')*VUCONN(IA,IGUC,IS3,T)
* scale unit input capacity
     )*(GDATA(IGUC,'GDUCUNITSIZE')*(1+(1/GDATA(IGUC,'GDCB'))$IGBPR(IGUC))/(1$(NOT IGESTO(IGUC)) + GDATA(IGUC,'GDSTOHUNLD')$IGESTO(IGUC))
       /(GDATA(IGUC,'GDFE')*GEFFRATE(IA,IGUC)))
;

$label  UnitC_end_ramp

*============================================================================================================
* System constraints
*============================================================================================================
