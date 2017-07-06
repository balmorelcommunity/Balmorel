* File: ECON.INC

* Modified last time:

* This file will create a parameter containing economy related to heat production, transmission, etc.

*-----------------------------  PRODUCTION ------------------------------------*

* Total Electricity Generation

OHEATECON(Y,C,IR,IA,IGE,'Electricity Generation (GWh)','Production')$((not IGETOH(IGE)) and CCCRRR(C,IR) and RRRAAA(IR,IA) and (IAGK_Y(IA,IGE) or VGKN.L(IA,IGE)))=

   SUM((S,T), IHOURSINST(S,T) * VGE_T.l(IA,IGE,S,T)) / IOF1000
   +SUM((S,T), IHOURSINST(S,T) * VGEN_T.l(IA,IGE,S,T)) / IOF1000;

* Wind Power Curtailment

OHEATECON(Y,C,IR,IA,IGWND,'Planned Curtailment (GWh)','Production')$(IWND_SUMST(IA) and CCCRRR(C,IR) and RRRAAA(IR,IA) and (IAGK_Y(IA,IGWND) or VGKN.L(IA,IGWND)))=

   (SUM((S,T), IHOURSINST(S,T) * VGE_T.UP(IA,IGWND,S,T)-VGE_T.l(IA,IGWND,S,T)) / IOF1000)$IAGK_Y(IA,IGWND)
  +(SUM((S,T), IHOURSINST(S,T) * (WNDFLH(IA) * VGKN.l(IA,IGWND) * WND_VAR_T(IA,S,T) / IWND_SUMST(IA)  - VGEN_T.l(IA,IGWND,S,T))) / IOF1000)$IAGKN(IA,IGWND);


*Total Heat Generation

OHEATECON(Y,C,IR,IA,IGH,'Heat Generation (TJ)','Production')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and (IAGK_Y(IA,IGH) or VGKN.L(IA,IGH)))=

   IOF3P6 *
   (SUM((S,T), IHOURSINST(S,T) * VGH_T.L(IA,IGH,S,T))
   +SUM((S,T), IHOURSINST(S,T)*VGHN_T.L(IA,IGH,S,T))) / IOF1000;

*------------------------------- ECONOMICS ------------------------------------*


* Fuel cost

OHEATECON(Y,C,IR,IA,G,'Fuel Cost (MMONEY)','Variable Costs')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and (IAGK_Y(IA,G) or VGKN.L(IA,G)))=

    OMONEY*IOF3P6/IOF1000000*
    SUM(FFF$(GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDNB')),
                IFUELP_Y(IA,FFF)*(
                 SUM((S,T), IHOURSINST(S,T) * VGF_T.L(IA,G,S,T) )$IAGK_Y(IA,G)
$ifi %BB2%==yes                +SUM((S,T), IHOURSINST(S,T) * VGFN_T.L(IA,G,S,T))$(VGKN.L(IA,G) and IAGKN(IA,G))
                )
    )$(IGNOTETOH(G) and (not IGESTO(G)) and (not IGHSTO(G)))

* Electricity storages:
    +OMONEY*SUM((S,T), QEEQ.m(IR,S,T)*VESTOLOADT.l(IA,S,T))$IGESTO(G)
* Heat storages:
    +OMONEY*SUM((S,T), QHEQ.m(IA,S,T)*VHSTOLOADT.l(IA,S,T))$IGHSTO(G)
* Electricity to heat:
    +OMONEY*SUM((S,T), QEEQ.m(IR,S,T)*VGE_T.l(IA,G,S,T))$(IAGK_Y(IA,G) and IGETOH(G))
    +OMONEY*SUM((S,T), QEEQ.m(IR,S,T)*VGEN_T.l(IA,G,S,T))$(IAGKN(IA,G) and IGETOH(G))
;


* Varible O&M:

OHEATECON(Y,C,IR,IA,G,'Variable O&M (MMONEY)','Variable Costs')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and (IAGK_Y(IA,G) or VGKN.L(IA,G)))=

   OMONEY/IOF1000000*
   ((GOMVCOST(IA,G)*
      (SUM((S,T), IHOURSINST(S,T) * VGE_T.L(IA,G,S,T))$IAGK_Y(IA,G)
   +   SUM((S,T), IHOURSINST(S,T) * VGEN_T.L(IA,G,S,T))$VGKN.L(IA,G)))$IGE(G)

   +  (GOMVCOST(IA,G) * GDATA(G,'GDCV') *
      (SUM((S,T), IHOURSINST(S,T) * VGH_T.L(IA,G,S,T))$IAGK_Y(IA,G)
   +   SUM((S,T), IHOURSINST(S,T) * VGHN_T.L(IA,G,S,T))$VGKN.L(IA,G)))$(IGNOTETOH(G) and IGH(G))) ;



* Fixed O&M:

OHEATECON(Y,C,IR,IA,G,'Fixed O&M (MMONEY)','Fixed Costs')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and (IAGK_Y(IA,G) or VGKN.L(IA,G)))=

   OMONEY/IOF1000*
   ((IGKFX_Y(IA,G)+VGKN.L(IA,G)
$ifi %DECOMPEFF%==yes -VDECOM.l(IA,G)
     +IGKVACCTOY(IA,G))*GOMFCOST(IA,G));


* Emission taxes CO2:

OHEATECON(Y,C,IR,IA,G,'CO2 Cost (MMONEY)','Variable Costs')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and (IAGK_Y(IA,G) or VGKN.L(IA,G)))=

   OMONEY/IOF1000000*IM_CO2(G)*IOF0001*IOF3P6*( ITAX_CO2_Y(C)
$ifi %CO2CAP%==yes
$ifi not %BB3%==yes + SUM(CCC_CO2CAP$CCC_CO2CAPC(CCC_CO2CAP,C),QCO2CAP.m(CCC_CO2CAP)*IOF1000000)
)*
    ( SUM((S,T), IHOURSINST(S,T) * VGF_T.L(IA,G,S,T))$IAGK_Y(IA,G)
$ifi %BB2%==yes   +  SUM((S,T), IHOURSINST(S,T) * VGFN_T.L(IA,G,S,T))$(VGKN.L(IA,G) and IAGKN(IA,G))

   );


* Emission taxes Other:

OHEATECON(Y,C,IR,IA,G,'Other Emission Taxes (MMONEY)','Taxes and Subsidies')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and (IAGK_Y(IA,G) or VGKN.L(IA,G)))=

    OMONEY/IOF1000000*(
       IM_SO2(G)*IOF0001*IOF3P6*ITAX_SO2_Y(C)*
             ( SUM((S,T), IHOURSINST(S,T) * VGF_T.L(IA,G,S,T))$IAGK_Y(IA,G)
$ifi %BB2%==yes             + SUM((S,T), IHOURSINST(S,T) * VGFN_T.L(IA,G,S,T))$(VGKN.L(IA,G) and IAGKN(IA,G))
              )

       +(GDATA(G,'GDNOX')*IOF0000001)*IOF3P6*ITAX_NOX_Y(C)*
             ( SUM((S,T), IHOURSINST(S,T)* VGF_T.L(IA,G,S,T))$IAGK_Y(IA,G)
$ifi %BB2%==yes             + SUM((S,T), IHOURSINST(S,T)* VGFN_T.L(IA,G,S,T))$(VGKN.L(IA,G) and IAGKN(IA,G))
             )
    );


* Fuel taxes

OHEATECON(Y,C,IR,IA,G,'Fuel Taxes (MMONEY)','Taxes and Subsidies')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and (IAGK_Y(IA,G) or VGKN.L(IA,G)) and (not IGESTO(G)) and (not IGHSTO(G)))=
* More fuel taxes on technology types. (now included in the sums below)
    OMONEY/IOF1000000*
    ((SUM((FFF,S,T)$(GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDNB')),
      IHOURSINST(S,T) * (TAX_F(FFF,C)+ITAX_GF(IA,G)) * IOF3P6 * VGF_T.L(IA,G,S,T)))$IAGK_Y(IA,G)

    + SUM((FFF,S,T)$(GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDNB')),
      IHOURSINST(S,T) * (TAX_F(FFF,C)+ITAX_GF(IA,G)) * IOF3P6 * VGFN_T.L(IA,G,S,T))$(VGKN.L(IA,G) and IAGKN(IA,G))
    );


* Electricity taxes

OHEATECON(Y,C,IR,IA,IGE,'Electricity Taxes (MMONEY)','Taxes and Subsidies')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and (IAGK_Y(IA,IGE) or VGKN.L(IA,IGE)) and ITAX_GE(IA,IGE))=


   OMONEY/IOF1000000*
   (SUM((S,T),
      ITAX_GE(IA,IGE)*IHOURSINST(S,T)  * VGE_T.L(IA,IGE,S,T))$IAGK_Y(IA,IGE)


   + SUM((S,T),
      ITAX_GE(IA,IGE)*IHOURSINST(S,T)  * VGEN_T.L(IA,IGE,S,T))$VGKN.L(IA,IGE)

   );


* Heat tax

OHEATECON(Y,C,IR,IA,IGH,'Heat Tax (MMONEY)','Taxes and Subsidies')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and (IAGK_Y(IA,IGH) or VGKN.L(IA,IGH)) and ITAX_GH(IA,IGH))=


   OMONEY/IOF1000000*
   (SUM((S,T),
      ITAX_GH(IA,IGH)*IOF3P6*VGH_T.L(IA,IGH,S,T)*IHOURSINST(S,T))$IAGK_Y(IA,IGH)


   + SUM((S,T),
      ITAX_GH(IA,IGH)*IOF3P6*VGHN_T.L(IA,IGH,S,T)*IHOURSINST(S,T))$VGKN.L(IA,IGH)

   );

* Income from sale of electricity

OHEATECON(Y,C,IR,IA,G,'Elec Sales (MMONEY)','Electricity Sales')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and (IAGK_Y(IA,G) or VGKN.L(IA,G)) and IGE(G))=

   OMONEY*
   (SUM((S,T), (VGE_T.L(IA,G,S,T)+VGEN_T.L(IA,G,S,T))*QEEQ.M(IR,S,T)))*(1-2$(IGETOH(G)));




* Marginal Heat Value

OHEATECON(Y,C,IR,IA,IGH,'Marginal Heat Value (MMONEY)','Heat Costs')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and (IAGK_Y(IA,IGH) or VGKN.L(IA,IGH)))=

   OMONEY*
   (SUM((S,T), VGH_T.L(IA,IGH,S,T)*QHEQ.M(IA,S,T))$IAGK_Y(IA,IGH)
   +SUM((S,T), VGHN_T.L(IA,IGH,S,T)*QHEQ.M(IA,S,T))$VGKN.L(IA,IGH)
   );

*Capital Cost

OHEATECON(Y,C,IR,IA,G,'Capital Cost (MMONEY)','Fixed Costs')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and (IAGK_Y(IA,G) or VGKN.L(IA,G)))=

   OMONEY*
   (GINVCOST(IA,G)*ANNUITYC(C)*(IGKFX_Y(IA,G)+VGKN.L(IA,G)
$ifi %DECOMPEFF%==yes -VDECOM.l(IA,G)
    +IGKVACCTOY(IA,G)));





*-------------------------- FUEL CONSUMPTION ----------------------------------*


* Total fuel consumption (TJ)
OHEATECON(Y,C,IR,IA,G,'Fuel Consumption (TJ)','Fuel Consumption')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and (IAGK_Y(IA,G) or VGKN.L(IA,G)))=
      (  SUM((S,T), IHOURSINST(S,T) *  VGF_T.l(IA,G,S,T))$IAGK_Y(IA,G)
        +SUM((S,T), IHOURSINST(S,T) * VGFN_T.l(IA,G,S,T))$VGKN.L(IA,G)   )*IOF3P6/IOF1000
;


OHEATECON(Y,C,IR,IA,G,'Fuel premium (MMONEY)','Variable Costs')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and (IAGK_Y(IA,G) or VGKN.L(IA,G)))=
   OMONEY*SUM(FFF$(GDATA(G,'GDFUEL')=FDATA(FFF,'FDNB')),

      OHEATECON(Y,C,IR,IA,G,'Fuel Consumption (TJ)','Fuel Consumption')*IOF1000*
       (0
$ifi not %BB3%==yes        -(QGMINCF.m(C,FFF) )$GMINF(Y,C,FFF)
$ifi not %BB3%==yes        +(QGMAXCF.m(C,FFF) )$GMAXF(Y,C,FFF)
$ifi not %BB3%==yes        +(QGEQCF.m(C,FFF)  )$GEQF(Y,C,FFF)
$ifi not %BB3%==yes        -(QGMINRF.m(IR,FFF))$GMINF(Y,IR,FFF)
$ifi not %BB3%==yes        +(QGMAXRF.m(IR,FFF))$GMAXF(Y,IR,FFF)
$ifi not %BB3%==yes        +(QGEQRF.m(IR,FFF) )$GEQF(Y,IR,FFF)
$ifi not %BB3%==yes        -(QGMINAF.m(IA,FFF))$GMINF(Y,IA,FFF)
$ifi not %BB3%==yes        +(QGMAXAF.m(IA,FFF))$GMAXF(Y,IA,FFF)
$ifi not %BB3%==yes        +(QGEQAF.m(IA,FFF) )$GEQF(Y,IA,FFF)
        )
   )
;



*----------------------------- EMISSIONS -------------------------------------*


OHEATECON(Y,C,IR,IA,G,'CO2 Emissions (kilotons)','Emissions')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and (IAGK_Y(IA,G) or VGKN.L(IA,G)))=

    IOF0001*IM_CO2(G)*IOF0001*IOF3P6*
      ( SUM((S,T), IHOURSINST(S,T) * VGF_T.L(IA,G,S,T))$IAGK_Y(IA,G)
$ifi %BB2%==yes      + SUM((S,T), IHOURSINST(S,T) * VGFN_T.L(IA,G,S,T))$(VGKN.L(IA,G) and IAGKN(IA,G))
      )
;


OHEATECON(Y,C,IR,IA,G,'SO2 Emissions (tons)','Emissions')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and (IAGK_Y(IA,G) or VGKN.L(IA,G)))=

    IM_SO2(G)*IOF0001*IOF3P6*
      ( SUM((S,T), IHOURSINST(S,T) * VGF_T.L(IA,G,S,T))$IAGK_Y(IA,G)
$ifi %BB2%==yes           + SUM((S,T), IHOURSINST(S,T) * VGFN_T.L(IA,G,S,T))$(VGKN.L(IA,G) and IAGKN(IA,G))
      )
    ;

OHEATECON(Y,C,IR,IA,G,'NOX Emissions (tons)','Emissions')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and (IAGK_Y(IA,G) or VGKN.L(IA,G)))=

    + (GDATA(G,'GDNOX')*IOF0000001)*IOF3P6*
       ( SUM((S,T), IHOURSINST(S,T) * VGF_T.L(IA,G,S,T))$IAGK_Y(IA,G)
$ifi %BB2%==yes            + SUM((S,T), IHOURSINST(S,T) * VGFN_T.L(IA,G,S,T))$(VGKN.L(IA,G) and IAGKN(IA,G))
       )    ;

OHEATECON(Y,C,IR,IA,G,'Capacity rent (MMONEY)','Variable Costs')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and VGKN.L(IA,G))=
 OMONEY*(
   -VGKN.L(IA,G)*VGKN.m(IA,G)
   +SUM(FFF$(GDATA(G,'GDFUEL')=FDATA(FFF,'FDNB')),

       VGKN.L(IA,G)*(0
$ifi %BB2%==yes        -(QKFUELC.m(C,FFF)  )$FKPOT(C,FFF)
$ifi %BB2%==yes        -(QKFUELR.m(IR,FFF) )$FKPOT(IR,FFF)
$ifi %BB2%==yes        -(QKFUELA.m(IA,FFF) )$FKPOT(IA,FFF)
        )
   ))
;


OHEATECON(Y,C,IR,IA,G,'Tax on investments (MMONEY)','Fixed Costs')$(ITAX_KN(IA,G) and CCCRRR(C,IR) and RRRAAA(IR,IA) and VGKN.L(IA,G))  =

      OMONEY*VGKN.l(IA,G)*ITAX_KN(IA,G)*ANNUITYC(C)

;


OHEATECON(Y,C,IR,IA,IGKE(G),'Installed Power Capacity (MW)','Capacity')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and (IAGK_Y(IA,IGKE) or VGKN.L(IA,IGKE)
$ifi %ADDINVESTBB2%==yes or GKCAPDIFFBB2(Y,IA,G)$IGREFURB(G)
         ))=
         ((IGKVACCTOY(IA,IGKE) + IGKFX_Y(IA,IGKE))/(1+(-1+GDATA(IGKE,'GDSTOHUNLD'))$IGESTO(G) ))$IAGK_Y(IA,IGKE)
        +( VGKN.L(IA,IGKE)/(1+(-1+GDATA(IGKE,'GDSTOHUNLD'))$IGESTO(G))                        )$IAGKN(IA,IGKE)
$ifi %ADDINVESTBB2%==yes         - GKCAPDIFFBB2(Y,IA,G)$IGREFURB(G)
;


OHEATECON(Y,C,IR,IA,IGH(G),'Installed Heat Capacity (MW)','Capacity')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and (IAGK_Y(IA,IGH) or VGKN.L(IA,IGH)))=
       ( ((IGKVACCTOY(IA,IGH) + IGKFX_Y(IA,IGH))/(1+(-1+GDATA(IGH,'GDSTOHUNLD'))$IGHSTO(IGH) )   )$IAGK_Y(IA,IGH)
        +(VGKN.L(IA,IGH)/(1+(-1+GDATA(IGH,'GDSTOHUNLD'))$IGHSTO(IGH) ) )$IAGKN(IA,IGH))$IGKH(IGH)

      +( ((IGKVACCTOY(IA,IGH) + IGKFX_Y(IA,IGH))$IAGK_Y(IA,IGH)
         + VGKN.L(IA,IGH)$IAGKN(IA,IGH))/GDATA(IGH,'GDCB')  )$IGBPR(IGH)

      +( ((IGKVACCTOY(IA,IGH) + IGKFX_Y(IA,IGH))$IAGK_Y(IA,IGH)
         + VGKN.L(IA,IGH)$IAGKN(IA,IGH))/(GDATA(IGH,'GDCB')+ GDATA(IGH,'GDCV')) )$IGEXT(IGH)
;

OHEATECON(Y,C,IR,IA,IGKE,'Full Load Hours - Electricity','Utilisation')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and (IAGK_Y(IA,IGKE) or VGKN.L(IA,IGKE)))=
 IOF1000*( OHEATECON(Y,C,IR,IA,IGKE,'Electricity Generation (GWh)','Production')
          /OHEATECON(Y,C,IR,IA,IGKE,'Installed Power Capacity (MW)','Capacity'))$OHEATECON(Y,C,IR,IA,IGKE,'Installed Power Capacity (MW)','Capacity')
;

OHEATECON(Y,C,IR,IA,IGH,'Full Load Hours - Heat' ,'Utilisation')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and (IAGK_Y(IA,IGH) or VGKN.L(IA,IGH)))=
 IOF1000*( OHEATECON(Y,C,IR,IA,IGH,'Heat Generation (TJ)','Production')/IOF3P6
       /OHEATECON(Y,C,IR,IA,IGH,'Installed Heat Capacity (MW)','Capacity') )$OHEATECON(Y,C,IR,IA,IGH,'Installed Heat Capacity (MW)','Capacity');


*------------------------------ START-UPS ------------------------------------*

$ifi not %UnitComm%==yes $goto end_econ_UC

* Number of start-ups
OHEATECON(Y,C,IR,IA,IGUC,'No. start-ups','Unit Commitment')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and (IAGK_Y(IA,IGUC) or IAGKN(IA,IGUC)))=
  ( SUM((S,T), VUCU.L(IA,IGUC,S,T))$IAGK_Y(IA,IGUC)
  +SUM((S,T), VUCUN.L(IA,IGUC,S,T))$IAGKN(IA,IGUC)
                                         )*
$ifi  %BB3%==yes                         1
$ifi not %BB3%==yes                      52/CARD(S)
;

* Start-up costs (added shutdown costs)
OHEATECON(Y,C,IR,IA,IGUC,'Start-up costs (MMoney)','Unit Commitment')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and (IAGK_Y(IA,IGUC) or IAGKN(IA,IGUC)))=
  ( (SUM((S,T), (VUCU.L(IA,IGUC,S,T)*GDATA(IGUC,'GDUCUCOST')+VUCD.L(IA,IGUC,S,T)*GDATA(IGUC,'GDUCDCOST'))*GDATA(IGUC,'GDUCUNITSIZE')) * OMONEY/IOF1000000  )$IAGK_Y(IA,IGUC)
  +(SUM((S,T), (VUCUN.L(IA,IGUC,S,T)*GDATA(IGUC,'GDUCUCOST')+VUCDN.L(IA,IGUC,S,T)*GDATA(IGUC,'GDUCDCOST'))*GDATA(IGUC,'GDUCUNITSIZE')) * OMONEY/IOF1000000)$IAGKN(IA,IGUC)
                                         )*
$ifi  %BB3%==yes                         1
$ifi not %BB3%==yes                      52/CARD(S)
;

$label end_econ_UC

*------------------------------------
$ifi %RESERVES%==yes  $include '../../base/addons/reserves/reserves_econ.inc';

