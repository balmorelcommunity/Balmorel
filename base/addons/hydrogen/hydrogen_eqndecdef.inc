Equations
   QGGETOH2(AAA,G,S,T)   'Hydrogen production - existing electrolysis plant'
   QGNGETOH2(AAA,G,S,T)  'Hydrogen production - new electrolysis plant'
   QHGETOH2(AAA,G,S,T)   'Hydrogen production - existing electrolysis plant'
   QHNGETOH2(AAA,G,S,T)  'Hydrogen production - existing electrolysis plant'
   QH2STOVOL(AAA,G,S,T)      'Dynamic equation hydrogen storage - not used in BALBASE3'
   QH2STOVOL_T(AAA,G,S,T)   'Dynamic equation hydrogen storage - used in BALBASE3'
   QH2STOVOL_END(AAA,G,S,T)   'End level of hydrogen storage fixed to value found in yearly simulation - used in BALBASE3'
   QH2STOMAXCON(AAA,G,S,T)      'Maximum hydrogen storage capacity - used in BALBASE1 and BALBASE2'
   QH2STOMAXCON_T(AAA,G,S,T)      'Maximum hydrogen storage capacity - used in BALBASE3'
   QH2STOMAXLOAD(AAA,G,S,T)      'Maximum loading capacity of hydrogen storage'
   QH2STOMAXUNLD(AAA,G,S,T)      'Maximum unloading capacity of hydrogen storage'
   QH2EQ(RRR,S,T)        'Hydrogen production equal demand'
   QH2EQ_AREA(AAA,S,T)    'Hydrogen production equals demand at an areal level'
   QGCH4KNT(AAA,G,S,T)   'Hydrogen production of steam reforming plants restricted by capacity'
;


* Electrolysis plants, existing:

QGGETOH2(IAGK_Y(IA,IGETOH2),IS3,T) ..

       VGE_T(IA,IGETOH2,IS3,T) =E= VGH2_T(IA,IGETOH2,IS3,T)/GDATA(IGETOH2,'GDFE');

* Electrolysis plants, new:

QGNGETOH2(IAGKN(IA,IGETOH2),IS3,T) ..

       VGEN_T(IA,IGETOH2,IS3,T)=E= VGH2N_T(IA,IGETOH2,IS3,T)/GDATA(IGETOH2,'GDFE');


QHGETOH2(IAGK_Y(IA,IGETOH2),IS3,T)..

       VGE_T(IA,IGETOH2,IS3,T) =E=VGH_T(IA,IGETOH2,IS3,T)*GDATA(IGETOH2,'GDCB');

QHNGETOH2(IAGKN(IA,IGETOH2),IS3,T)..

        VGEN_T(IA,IGETOH2,IS3,T)=E=VGHN_T(IA,IGETOH2,IS3,T)*GDATA(IGETOH2,'GDCB');


* Hydrogen gas storage, dynamic balance for weekly time horizon:
* Start and end filling degree in each week fixed to values obtained
* from yearly simulation

QH2STOVOL_T(IAGK_Y(IA,IGH2STO),IS3,T)$(ORD(T)< CARD(T))..

    VH2STOVOL_T(IA,IGH2STO,IS3,T+1) =E= VH2STOVOL_T(IA,IGH2STO,IS3,T)
*(1-GDATA(IGH2STO,'GDSTOLOSS'))
  + VH2STOLOADT(IA,IGH2STO,IS3,T)*(1-GDATA(IGH2STO,'GDLOADLOSS'))- VGH2_T(IA,IGH2STO,IS3,T)
;

* End level of hydrogen storage in season S fixed to start level in season S+1
* Values found in yearly simulation

QH2STOVOL_END(IAGK_Y(IA,IGH2STO),IS3,T)$(ORD(T)=CARD(T))..
   VH2STOVOL_T(IA,IGH2STO,IS3,T)
*(1-GDATA(IGH2STO,'GDSTOLOSS'))
  + VH2STOLOADT(IA,IGH2STO,IS3,T)*(1-GDATA(IGH2STO,'GDLOADLOSS'))- VGH2_T(IA,IGH2STO,IS3,T)=E=IH2STOVOL_END(IA,IGH2STO,IS3)
;

* Maximum content, hydrogen gas storage - used in bb1 and bb2:
*Hydrogen storage is modelled as a inter-seasonal storage that can be used with a T resolutions

QH2STOMAXCON(IA,IGH2STO,S,T)$(IAGK_Y(IA,IGH2STO) OR IAGKN(IA,IGH2STO))..
   (IGKVACCTOY(IA,IGH2STO)+IGKFX_Y(IA,IGH2STO))$IAGK_Y(IA,IGH2STO)
   + VGKN(IA,IGH2STO)$IAGKN(IA,IGH2STO)
    =G= VH2STOVOL_T(IA,IGH2STO,S,T)
;

* Maximum content, hydrogen gas storage - used in bb3:

QH2STOMAXCON_T(IA,IGH2STO,IS3,T)$IAGK_Y(IA,IGH2STO)..
   IGKVACCTOY(IA,IGH2STO)+IGKFX_Y(IA,IGH2STO) =G= VH2STOVOL_T(IA,IGH2STO,IS3,T)
;

* Maximum loading, hydrogen gas storage:
QH2STOMAXLOAD(IA,IGH2STO,IS3,T)$(IAGK_Y(IA,IGH2STO) OR IAGKN(IA,IGH2STO))..
   ((IGKVACCTOY(IA,IGH2STO)+IGKFX_Y(IA,IGH2STO))/GDATA(IGH2STO,'GDSTOHLOAD'))$IAGK_Y(IA,IGH2STO)
   + (VGKN(IA,IGH2STO)/GDATA(IGH2STO,'GDSTOHLOAD'))$IAGKN(IA,IGH2STO)
    =G= VH2STOLOADT(IA,IGH2STO,IS3,T)
;

* Maximum unloading, hydrogen gas storage:
QH2STOMAXUNLD(IA,IGH2STO,IS3,T)$(IAGK_Y(IA,IGH2STO) OR IAGKN(IA,IGH2STO))..
   ((IGKVACCTOY(IA,IGH2STO)+IGKFX_Y(IA,IGH2STO))/GDATA(IGH2STO,'GDSTOHUNLD'))$IAGK_Y(IA,IGH2STO)
   + (VGKN(IA,IGH2STO)/GDATA(IGH2STO,'GDSTOHUNLD'))$IAGKN(IA,IGH2STO)
    =G=
   VGH2_T(IA,IGH2STO,IS3,T)$IAGK_Y(IA,IGH2STO)+
   VGH2N_T(IA,IGH2STO,IS3,T)$IAGKN(IA,IGH2STO)
;

* Hydrogen gas storage, dynamic balance for yearly time horizon:
* Hydrogen gas storage modelled as start level being equal to end level for each year

QH2STOVOL(IA,IGH2STO,S,T)$(IAGK_Y(IA,IGH2STO) OR IAGKN(IA,IGH2STO))..

    VH2STOVOL_T(IA,IGH2STO,S,T+1)
    +SUM(ITALIAS$(ORD(ITALIAS)=1),VH2STOVOL_T(IA,IGH2STO,S++1,ITALIAS)$(ORD(T)=CARD(T)))
    =E=
     VH2STOVOL_T(IA,IGH2STO,S,T)*(1-GDATA(IGH2STO,'GDSTOLOSS'))
    +(VH2STOLOADT(IA,IGH2STO,S,T)*(1-GDATA(IGH2STO,'GDLOADLOSS'))
    -((VGH2_T(IA,IGH2STO,S,T))$IAGK_Y(IA,IGH2STO)+(VGH2N_T(IA,IGH2STO,S,T))$IAGKN(IA,IGH2STO)))
    *(IHOURSINST(S,T)*(CARD(S)/CARD(SSS))*(1/CYCLES(T)));
;

* Hydrogen production equal demand on region level:
* Prod + OutputStorage - InputStorage = DemandTransport + DemandPower+DemandBioRefinery (other exogenous demand)

QH2EQ(IR,IS3,T)..
   SUM(IAGK_Y(IA,IGETOH2)$(RRRAAA(IR,IA)),VGH2_T(IA,IGETOH2,IS3,T)) +
   SUM(IAGKN(IA,IGETOH2) $(RRRAAA(IR,IA)),VGH2N_T(IA,IGETOH2,IS3,T)) +
   SUM(IAGK_Y(IA,IGCH4TOH2)$(RRRAAA(IR,IA)),VGH2_T(IA,IGCH4TOH2,IS3,T)) +
   SUM(IAGKN(IA,IGCH4TOH2) $(RRRAAA(IR,IA)),VGH2N_T(IA,IGCH4TOH2,IS3,T)) +
   SUM(IAGK_Y(IA,IGH2STO)$(RRRAAA(IR,IA)),VGH2_T(IA,IGH2STO,IS3,T)) +
   SUM(IAGKN(IA,IGH2STO) $(RRRAAA(IR,IA)),VGH2N_T(IA,IGH2STO,IS3,T))
   - SUM((IA,IGH2STO)$(RRRAAA(IR,IA) AND (IAGK_Y(IA,IGH2STO) OR IAGKN(IA,IGH2STO))),VH2STOLOADT(IA,IGH2STO,IS3,T))
   =E=
$ifi %TSP%==yes $INCLUDE '../../base/addons/Transport/TSPH2Demand.inc'
$ifi Not %TSP%==yes   IDH2_REGION_T_Y(IR,IS3,T)+ SUM(IA$RRRAAA(IR,IA),IDH2_AREA_T_Y(IA,IS3,T))
   + SUM(IAGK_Y(IA,IGH2FUEL) $(RRRAAA(IR,IA)),VGE_T(IA,IGH2FUEL,IS3,T)/GDATA(IGH2FUEL,'GDFE'))
   + SUM(IAGKN(IA,IGH2FUEL) $(RRRAAA(IR,IA)),VGEN_T(IA,IGH2FUEL,IS3,T)/GDATA(IGH2FUEL,'GDFE'))
*        + SUM(DH2F_U,VDH2F_T(IR,IS3,T,DH2F_U) )
*        - SUM(DH2F_D,VDH2F_T(IR,IS3,T,DH2F_D) )
*         - VQH2EQ(IR,IS3,T,'IMINUS') + VQH2EQ(IR,IS3,T,'IPLUS')
;

* Hydrogen production from steam reforming restricted by capacity
QGCH4KNT(IAGKN(IA,IGCH4TOH2),IS3,T) ..
  VGKN(IA,IGCH4TOH2)*GKRATE(IA,IGCH4TOH2,IS3)
   =G= VGH2N_T(IA,IGCH4TOH2,IS3,T)
;



* Hydrogen production equal demand on area level:
* Prod + OutputStorage - InputStorage = DemandTransport + DemandPower

QH2EQ_AREA(IA,IS3,T)$(IDH2_AREA_T_Y(IA,IS3,T))..
   SUM(IGETOH2$IAGK_Y(IA,IGETOH2),VGH2_T(IA,IGETOH2,IS3,T)) +
   SUM(IGETOH2$IAGKN(IA,IGETOH2),VGH2N_T(IA,IGETOH2,IS3,T)) +
   SUM(IGH2STO$IAGK_Y(IA,IGH2STO) ,VGH2_T(IA,IGH2STO,IS3,T)) +
   SUM(IGH2STO$IAGKN(IA,IGH2STO),VGH2N_T(IA,IGH2STO,IS3,T))
   - SUM(IGH2STO$(IAGK_Y(IA,IGH2STO) OR IAGKN(IA,IGH2STO)),VH2STOLOADT(IA,IGH2STO,IS3,T))
   =G=
   IDH2_AREA_T_Y(IA,IS3,T)
*        + SUM(DH2F_U,VDH2F_T(IA,IS3,T,DH2F_U) )
*        - SUM(DH2F_D,VDH2F_T(IA,IS3,T,DH2F_D) )
*        - VQH2EQ(IA,IS3,T,'IMINUS') + VQH2EQ(IA,IS3,T,'IPLUS')
;

