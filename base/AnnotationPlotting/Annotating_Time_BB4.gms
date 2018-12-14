* Subset of year and Season
$oninline
$oneolcom

$ontext
set YYY "years "/2012*2050/;
set SSS "Seaons" /S01*S52/;
set iy411(YYY) "assigned subet of y";
set S(SSS) "Seaons" /S01,S02/;

iy411('2035')=yes;
iy411('2025')=yes;

*$include ../../base/AnnotationPlotting/Annotating_Time_BB4_Declaration.gms
$offtext
$offorder

*SET IYS_sub(YYY,SSS) "Mapping (IY411,SSS)";
IYS_sub(IY411,IS3) =  IYS(IY411,IS3);

BlockSelected(blocks) = no;
blockAssignment(blocks,IS3,YYY) =no;
blockAssignment(blocks,IS3,IY411)$(IYS_sub(IY411,IS3)) = yes;

display blockAssignment;

blockAssignmentHelper(IS3,blocks,timeHelper,YYY)$(ord(blocks)=(ord(YYY)*ord(IS3))) = yes;

display blockAssignmentHelper;

Option blockAssignmentTime < blockAssignmentHelper     ;
display blockAssignmentTime;

BlockSelected(blocks) = sum((IS3,YYY)$(IYS_sub(YYY,IS3)),blockAssignmentTime(blocks,IS3,YYY));
display BlockSelected;

annot_blockLast = card(BlockSelected) + 2;
display   annot_blockLast;

annot_blockStage(IS3,IY411) = sum(blockAssignmentTime(BlockSelected,IS3,IY411), ord(BlockSelected)) + 1;

display annot_blockStage;

$onorder

****************************************************************************************************
****************** Equatuions
****************************************************************************************************

* Objective function
QOBJ.stage = annot_blockLast;

* Electricity generation equals demand (MW)
QEEQ.stage(IY411,IR,IS3,T) = annot_blockStage(IS3,IY411);

* Heat generation equals demand (MW)
QHEQ.stage(IY411,IA,IS3,T)$(SUM(DHUSER, IDH_SUMST(IA,DHUSER))) = annot_blockStage(IS3,IY411);

* Fuel consumption rate.
QGFEQ.stage(IY411,IA,G,IS3,T)$IAGK_HASORPOT(IY411,IA,G) =annot_blockStage(IS3,IY411);

* CHP generation (back pressure) limited by Cb-line (MW)
QGCBGBPR.stage(IY411,IA,IGBPR,IS3,T)$IAGK_HASORPOT(IY411,IA,IGBPR) = annot_blockStage(IS3,IY411);

* CHP generation (extraction) limited by Cb-line (MW)
QGCBGEXT.stage(IAGK_HASORPOT(IY411,IA,IGEXT),IS3,T) = annot_blockStage(IS3,IY411);




* CHP generation (extraction) limited by Cv-line (MW)
QGCVGEXT.stage(IAGK_HASORPOT(IY411,IA,IGEXT),IS3,T)$
$ifi not %COMBTECH%==yes  1
$ifi     %COMBTECH%==yes  (NOT IGCOMB2(IGEXT))
         = annot_blockStage(IS3,IY411);

* Electric heat generation (MW)
QGGETOH.stage(IAGK_HASORPOT(IY411,IA,IGETOH),IS3,T) =annot_blockStage(IS3,IY411);

*"Hydropower with reservoir seasonal energy constraint (MW)"
*QHYRSSEQ.stage(IY411,IA,IS3)$(SUM(IGHYRS,IAGK_HASORPOT(IY411,IA,IGHYRS))) = annot_blockLast;
QHYRSSEQ.stage(IY411,IA,IS3)$(SUM(IGHYRS,IAGK_HASORPOT(IY411,IA,IGHYRS))) = annot_blockStage(IS3,IY411);

*  "Hydropower reservoir - minimum level (MWh)"
QHYRSMINVOL.stage(IY411,IA,IS3)$(HYRSDATA(IA,"HYRSMINVOL",IS3) AND SUM(IGHYRS$IAGK_HASORPOT(IY411,IA,IGHYRS),1)) =  annot_blockStage(IS3,IY411);

*  "Hydropower reservoir - maximum level (MWh)"
QHYRSMAXVOL.stage(IY411,IA,IS3)$(HYRSDATA(IA,"HYRSMAXVOL",IS3) AND SUM(IGHYRS$IAGK_HASORPOT(IY411,IA,IGHYRS),1)) = annot_blockStage(IS3,IY411);

* "Regulated and unregulated hydropower production lower than capacity (MW)" !! NB:exclude hydro-run-of-river   Hans TODO
QHYMAXG.stage(IY411,IA,IS3,T)$SUM(IGHYRS,IAGK_HASORPOT(IY411,IA,IGHYRS))= annot_blockStage(IS3,IY411);

* Intra-seasonal electricty storage dynamic equation (MWh)
* OBS CHANGED TO NON-LINKING COMPARED TO BB1-BB2
QESTOVOLT.stage(IY411,IA,IGESTO,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGESTO) and ord(T)<card(T)) =  annot_blockStage(IS3,IY411);
QESTOVOLTS.stage(IY411,IA,IGESTOS,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGESTOS) and ord(T)<card(T)) =  annot_blockStage(IS3,IY411);
QESTOVOLT.stage(IY411,IA,IGESTO,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGESTO) and ord(T)=card(T)) =  annot_blockLast;
QESTOVOLTS.stage(IY411,IA,IGESTOS,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGESTOS) and ord(T)=card(T)) =  annot_blockLast;

*Intra-seasonal heat storage dynamic equation (MWh)
QHSTOVOLT.stage(IY411,IA,IGHSTO,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGHSTO) and ord(T)<card(T)) =  annot_blockStage(IS3,IY411);
QHSTOVOLTS.stage(IY411,IA,IGHSTOS,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGHSTOS) and ord(T)<card(T)) =  annot_blockStage(IS3,IY411);
QHSTOVOLT.stage(IY411,IA,IGHSTO,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGHSTO) and ord(T)=card(T)) = annot_blockLast;
QHSTOVOLTS.stage(IY411,IA,IGHSTOS,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGHSTOS) and ord(T)=card(T)) = annot_blockLast;

* "Heat storage loading less than heat production (MW)"
QHSTOLOADT.stage(IY411,IA,IGHSTO,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGHSTO))= annot_blockStage(IS3,IY411);
QHSTOLOADTS.stage(IY411,IA,IGHSTOS,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGHSTOS))=annot_blockStage(IS3,IY411);

* "Upper limit to heat storage loading (MW)"
QHSTOLOADTLIM.stage(IY411,IA,IGHSTO,IS3,T)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHSTO)) AND IAGK_HASORPOT(IY411,IA,IGHSTO))  = annot_blockStage(IS3,IY411);
QHSTOLOADTLIMS.stage(IY411,IA,IGHSTOS,IS3,T)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHSTOS)) AND IAGK_HASORPOT(IY411,IA,IGHSTOS))   = annot_blockStage(IS3,IY411);

* "Upper limit to electricity storage loading (MW)"
QESTOLOADTLIM.stage(IY411,IA,IGESTO,IS3,T)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGESTO)) AND IAGK_HASORPOT(IY411,IA,IGESTO)) =annot_blockStage(IS3,IY411);
QESTOLOADTLIMS.stage(IY411,IA,IGESTOS,IS3,T)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGESTOS)) AND IAGK_HASORPOT(IY411,IA,IGESTOS))  = annot_blockStage(IS3,IY411);

* "Heat storage output limit (MW)"
QHSTOVGHTLIM.stage(IY411,IA,IGHSTO,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGHSTO) AND SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHSTO))) = annot_blockStage(IS3,IY411);
QHSTOVGHTLIMS.stage(IY411,IA,IGHSTOS,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGHSTOS) AND SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHSTOS))) = annot_blockStage(IS3,IY411);

* "Electricity storage output limit (MW)"
QESTOVGETLIM.stage(IY411,IA,IGESTO,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGESTO) AND SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGESTO))) = annot_blockStage(IS3,IY411);
QESTOVGETLIMS.stage(IY411,IA,IGESTOS,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGESTOS) AND SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGESTOS))) = annot_blockStage(IS3,IY411);

* "Heat storage capacity limit (MWh)"
QHSTOVOLTLIM.stage(IY411,IA,IGHSTO,IS3,T)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHSTO)) AND IAGK_HASORPOT(IY411,IA,IGHSTO)) =  annot_blockStage(IS3,IY411);
QHSTOVOLTLIMS.stage(IY411,IA,IGHSTOS,IS3,T)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHSTOS)) AND IAGK_HASORPOT(IY411,IA,IGHSTOS)) =  annot_blockStage(IS3,IY411);

* "Electricity storage capacity limit (MWh)"
QESTOVOLTLIM.stage(IY411,IA,IGESTO,IS3,T)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGESTO)) AND IAGK_HASORPOT(IY411,IA,IGESTO))      =  annot_blockStage(IS3,IY411);
QESTOVOLTLIMS.stage(IY411,IA,IGESTOS,IS3,T)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGESTOS)) AND IAGK_HASORPOT(IY411,IA,IGESTOS))      =  annot_blockStage(IS3,IY411);

* "Capacity constraint on electricity transmission (MW)"
QXK_UP.stage(IY411,IRE,IRI,IS3,T)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IXKN(Y,IRE,IRI)) = annot_blockStage(IS3,IY411);

* "Capacity constraint on electricity generation (MW)"
QGKE_UP.stage(IY411,IA,IGDISPATCH(IGKENOSTO),IS3,T)$(IAGK_HASORPOT(IY411,IA,IGKENOSTO) AND SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGKENOSTO)))   =  annot_blockStage(IS3,IY411);
* "Minimum capacity usage constraint on electricity generation capacity (MW)"
QGKE_LO.stage(IY411,IA,IGDISPATCH(IGKENOSTO),FFF,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGKENOSTO) AND SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGKENOSTO)) and IGF(IGKENOSTO,FFF) and GKF_LO(FFF)>0)= annot_blockStage(IS3,IY411);

*  "Capacity constraint on heat generation (MW)"
QGKH_UP.stage(IY411,IA,IGDISPATCH(IGKHNOSTO),IS3,T)$(IAGK_HASORPOT(IY411,IA,IGKHNOSTO) AND SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGKHNOSTO)))  =  annot_blockStage(IS3,IY411);

* "Hydro run on river can not be dispatched (MW)"
QHYRRDISPATCH.stage(IY411,IA,IGHYRR,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGHYRR) AND SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHYRR)) AND IWTRRRSUM(IA))  =  annot_blockStage(IS3,IY411);

* "Wind power can not be dispatched (MW)"
QWNDDISPATCH.stage(IY411,IA,IGWND,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGWND) AND SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGWND)) AND IWND_SUMST(IA))  =  annot_blockStage(IS3,IY411);

* "Solar electricity generation can not be dispatched (MW)"
QSOLEDISPATCH.stage(IY411,IA,IGSOLE,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGSOLE) AND SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGSOLE)) AND ISOLESUMST(IA))  = annot_blockStage(IS3,IY411);
QSOLHDISPATCH.stage(IY411,IA,IGSOLH,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGSOLH) AND SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGSOLH)) AND ISOLHSUMST(IA))  = annot_blockStage(IS3,IY411);
QWAVEDISPATCH.stage(IY411,IA,IGWAVE,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGWAVE) AND SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGWAVE)) AND IWAVESUMST(IA))  = annot_blockStage(IS3,IY411);

** ADDED DUE TO NEW BALMOREL VERSION


* "Maximum fuel use by year, country and fuel (GJ)"
QGMAXCF.stage(IY411,C,FFF)$IGMAXF(IY411,C,FFF)  = annot_blockLast  ;



*QSTEPWISEPRICE_GFTOSTEP.stage(IY411,C,FFF) = sum(IS3,annot_blockStage(IS3,IY411));
*QLIMITSFORFUELS_GMAXCF.stage(IY411,C,FFF) = sum(IS3,annot_blockStage(IS3,IY411));


* OBS NO SEASON!!

*"Transmission investments are set symetric(MW)"
*QXINVSYMMETRY.stage(IY411,IRE,IRI)$IXKN(IY411,IRE,IRI)= annot_blockLast;



*QXKNACCUMNET.stage(IY411,IRE,IRI)$IXKN(IY411,IRE,IRI)  =   sum(blockAssignmentTime(BlockSelected,IS3,IY411),ord(BlockSelected)) + 1;
* "Transmission investments are set symetric(MW)"  : OBS NO S
*
*QGKNACCUMGROSS.stage(IY411,IA,IGKFIND)$IAGKN(IA,IGKFIND)=  sum(blockAssignmentTime(BlockSelected,IS3,IY411),ord(BlockSelected)) + 1;
* "NOT FINISHED Accumulated new investments minus decommissioning of previous investments due to lifetime expiration available at beginning of next year (MW)"
*QGKNACCUMNET.stage(IY411,IA,IGKFIND)$IAGKN(IA,IGKFIND)  = card(BlockSelected) + 2;


$ontext
* OBS NO SEASON DEPENDENCE   AND NOT ANNOTATED BEFORE
QKEFUELC.stage(IY411,C,FFF)$FKPOT(C,FFF) =  annot_blockStage(IS3,IY411);
QKEFUELR.stage(IY411,IR,FFF)$FKPOT(IR,FFF) = annot_blockStage(IS3,IY411);
QKEFUELA.stage(IY411,IA,FFF)$FKPOT(IA,FFF) =  annot_blockStage(IS3,IY411);
QGMINFUELC.stage(IY411,C,FFF)$FGEMIN(C,FFF) =  annot_blockStage(IS3,IY411);
QGMAXFUELC.stage(IY411,C,FFF)$FGEMAX(C,FFF) =  annot_blockStage(IS3,IY411);
QGMINFUELR.stage(IY411,IR,FFF)$FGEMIN(IR,FFF) =  annot_blockStage(IS3,IY411);
QGMAXFUELR.stage(IY411,IR,FFF)$FGEMAX(IR,FFF) =  annot_blockStage(IS3,IY411);
QGMINFUELA.stage(IY411,IA,FFF)$FGEMIN(IA,FFF) = annot_blockStage(IS3,IY411);
QGMAXFUELA.stage(IY411,IA,FFF)$FGEMAX(IA,FFF) =  annot_blockStage(IS3,IY411);
QGMINCF.stage(IY411,C,FFF)$IGMINF(IY411,C,FFF) =  annot_blockStage(IS3,IY411);
QGMAXCF.stage(IY411,C,FFF)$IGMAXF(IY411,C,FFF) =  annot_blockStage(IS3,IY411);
QGEQCF.stage(IY411,C,FFF)$IGEQF(IY411,C,FFF) =  annot_blockStage(IS3,IY411);
QGMINRF.stage(IY411,IR,FFF)$IGMINF(IY411,IR,FFF) =  annot_blockStage(IS3,IY411);
QGMAXRF.stage(IY411,IR,FFF)$IGMAXF(IY411,IR,FFF) =  annot_blockStage(IS3,IY411);
QGEQRF.stage(IY411,IR,FFF)$IGEQF(IY411,IR,FFF) =  annot_blockStage(IS3,IY411);
QGMINAF.stage(IY411,IA,FFF)$IGMINF(IY411,IA,FFF) = annot_blockStage(IS3,IY411);
QGMAXAF.stage(IY411,IA,FFF)$IGMAXF(IY411,IA,FFF) =  annot_blockStage(IS3,IY411);
QGEQAF.stage(IY411,IA,FFF)$IGEQF(IY411,IA,FFF) =  annot_blockStage(IS3,IY411);
QKMINFC.stage(IY411,C,FFF)$FKMIN(IY411,C,FFF) =  annot_blockStage(IS3,IY411);
QKMAXFC.stage(IY411,C,FFF)$FKMAX(IY411,C,FFF) =  annot_blockStage(IS3,IY411);
QKEQFC.stage(IY411,C,FFF)$FKEQ(IY411,C,FFF) =  annot_blockStage(IS3,IY411);
QKMINFR.stage(IY411,IR,FFF)$FKMIN(IY411,IR,FFF) =  annot_blockStage(IS3,IY411);
QKMAXFR.stage(IY411,IR,FFF)$FKMAX(IY411,IR,FFF) =  annot_blockStage(IS3,IY411);
QKEQFR.stage(IY411,IR,FFF)$FKEQ(IY411,IR,FFF) =  annot_blockStage(IS3,IY411);
QKMINFNA.stage(IY411,FFF)$FKMINNA(IY411,FFF) =  annot_blockStage(IS3,IY411);
QKMAXFNA.stage(IY411,FFF)$FKMAXNA(IY411,FFF) =  annot_blockStage(IS3,IY411);
QKEQFNA.stage(IY411,FFF)$FKEQNA(IY411,FFF) =  annot_blockStage(IS3,IY411);
QLIMCO2.stage(IY411,C)$(M_POL(IY411,'LIM_CO2',C) AND (M_POL(IY411,'LIM_CO2',C) LT INF)) =   annot_blockStage(IS3,IY411);
QLIMSO2.stage(IY411,C)$(M_POL(IY411,"LIM_SO2",C) AND (M_POL(IY411,"LIM_SO2",C) LT INF)) =   annot_blockStage(IS3,IY411);
QLIMNOX.stage(IY411,C)$(M_POL(IY411,'LIM_NOX',C) AND (M_POL(IY411,'LIM_NOX',C) LT INF)) =   annot_blockStage(IS3,IY411);
QLIMCO2NA.stage(IY411)$(M_POLNA(IY411,'LIM_CO2') AND (M_POLNA(IY411,'LIM_CO2') LT INF))  =  annot_blockStage(IS3,IY411);
*QMAXINVESTCF.stage(IY411,C,FFF)$(FMAXINVEST(C,FFF) AND (FMAXINVEST(C,FFF) LT INF))  =  sum(blockAssignmentTime(BlockSelected,IS3,IY411),ord(BlockSelected)) + 1;
*QMAXINVESTNAF.stage(IY411,FFF)$(FMAXINVESTNA(IY411,FFF) AND (FMAXINVESTNA(IY411,FFF) LT INF)) =  sum(blockAssignmentTime(BlockSelected,IS3,IY411),ord(BlockSelected)) + 1;
$offtext
****************************************************************************************************
****************** Variables
****************************************************************************************************
* Objective function value (MMoney)
VOBJ.stage =  1;

* Electricity generation (MW), existing units
VGE_T.stage(IY411,IA,G,IS3,T)$IAGK_HASORPOT(IY411,IA,G) = annot_blockStage(IS3,IY411);
*VGE_T.stage(IY411,IA,G,IS3,T) = annot_blockStage(IS3,IY411);


* Heat generation (MW), existing units
VGH_T.stage(IY411,IA,G,IS3,T)$IAGK_HASORPOT(IY411,IA,G) = annot_blockStage(IS3,IY411);
*VGH_T.stage(IY411,IA,G,IS3,T) = annot_blockStage(IS3,IY411);

* Fuel consumption rate (MW), existing units
VGF_T.stage(IY411,IA,G,IS3,T)$IAGK_HASORPOT(IY411,IA,G) = annot_blockStage(IS3,IY411);

* Electricity export from region IRRRE to IRRRI (MW)
*VX_T.stage(IY411,IRRRE,IRRRI,IS3,T)$(sum((IA,G),IAGK_HASORPOT(IY411,IA,G))) = annot_blockStage(IS3,IY411);
VX_T.stage(IY411,IRE,IRI,IS3,T)$(IXK_HASORPOT(IY411,IRE,IRI)) = annot_blockStage(IS3,IY411);

* "New electricity transmission capacity (MW)";
*VXKN.stage(IY411,IRRRE,IRRRI)$(sum((IA,G),IAGK_HASORPOT(IY411,IA,G)))  = 1;
VXKN.stage(IY411,IRE,IRI)$(IXK_HASORPOT(IY411,IRE,IRI))  = 1;

*  "Accumulated new investments (MISSING: minus any decommissioning of them due to lifetime expiration) this BB4, at end of (ULTimo) previous (i.e., start of current) year (MW)";
VGKNACCUMNET.stage(IY411,IA,G)$IAGK_HASORPOT(IY411,IA,G) =  1;

* "Accumulated new transmission investments (MISSING: minus any decommissioning of them due to lifetime expiration) this BB4, at end of previous (i.e., available at start of current) year (MW)";
*VXKNACCUMNET.stage(IY411,IRRRE,IRRRI)$(sum((IA,G),IAGK_HASORPOT(IY411,IA,G)))  =  1;
VXKNACCUMNET.stage(IY411,IRE,IRI)$(IXK_HASORPOT(IY411,IRE,IRI))  =  1;

*  "New generation capacity (MW)";  !! se kommentarer til YYY  i bb4.sim Hans TODO
VGKN.stage(IY411,IA,G)$IAGK_HASORPOT(IY411,IA,G)  = 1;

*"Hydro energy equivalent at the start of the season (MWh)"
*VHYRS_S.stage(IY411,IA,IS3)$(sum(G,IAGK_HASORPOT(IY411,IA,G))) = annot_blockStage(IS3,IY411);
VHYRS_S.stage(IY411,IA,IS3)$(sum(G,IAGK_HASORPOT(IY411,IA,G))) = 1;

*  "Intra-seasonal electricity storage loading (MW)";
VESTOLOADT.stage(IY411,IA,G,IS3,T)$IAGK_HASORPOT(IY411,IA,G) = annot_blockStage(IS3,IY411);
VESTOLOADTS.stage(IY411,IA,G,IS3,T)$IAGK_HASORPOT(IY411,IA,G) = annot_blockStage(IS3,IY411);

*   "Intra-seasonal heat storage loading (MW)";
VHSTOLOADT.stage(IY411,IA,G,IS3,T)$IAGK_HASORPOT(IY411,IA,G)  = annot_blockStage(IS3,IY411);
VHSTOLOADTS.stage(IY411,IA,G,IS3,T)$IAGK_HASORPOT(IY411,IA,G)  = annot_blockStage(IS3,IY411);

*  "Electricity storage contents at beginning of time segment (MWh)";
VESTOVOLT.stage(IY411,IA,IGESTO,IS3,T)$IAGK_HASORPOT(IY411,IA,IGESTO)    =  annot_blockStage(IS3,IY411);
VESTOVOLTS.stage(IY411,IA,IGESTOS,IS3,T)$IAGK_HASORPOT(IY411,IA,IGESTOS)   =  annot_blockStage(IS3,IY411);

*  "Heat storage contents at beginning of time segment (MWh)";
VHSTOVOLT.stage(IY411,IA,IGHSTO,IS3,T)$IAGK_HASORPOT(IY411,IA,IGHSTO)   =  annot_blockStage(IS3,IY411);
VHSTOVOLTS.stage(IY411,IA,IGHSTOS,IS3,T)$IAGK_HASORPOT(IY411,IA,IGHSTOS)  =  annot_blockStage(IS3,IY411);

*VESTOVOLT.stage(IY411,IA,IGESTO,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGESTO) and ord(T)<card(T)) =  annot_blockStage(IS3,IY411);
*VESTOVOLTS.stage(IY411,IA,IGESTOS,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGESTOS) and ord(T)<card(T)) =  annot_blockStage(IS3,IY411);
*VESTOVOLT.stage(IY411,IA,IGESTO,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGESTO) and ord(T)=card(T)) =  annot_blockLast;
*VESTOVOLTS.stage(IY411,IA,IGESTOS,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGESTOS) and ord(T)=card(T)) =  annot_blockLast;

*Intra-seasonal heat storage dynamic equation (MWh)
*VHSTOVOLT.stage(IY411,IA,IGHSTO,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGHSTO)    and ord(T)<card(T)) =  annot_blockStage(IS3,IY411);
*VHSTOVOLTS.stage(IY411,IA,IGHSTOS,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGHSTOS)  and ord(T)<card(T)) =  annot_blockStage(IS3,IY411);
*VHSTOVOLT.stage(IY411,IA,IGHSTO,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGHSTO)    and ord(T)=card(T)) = annot_blockLast;
*VHSTOVOLTS.stage(IY411,IA,IGHSTOS,IS3,T)$(IAGK_HASORPOT(IY411,IA,IGHSTOS)  and ord(T)=card(T)) = annot_blockLast;

*  'Feasibility in intra-seasonal electricity storage equation QESTOVOLT (MWh)';
*VQESTOVOLT.stage(IY411,IA,IS3,T,IPLUSMINUS)  =  annot_blockStage(IS3,IY411);
* 'Feasibility in inter-seasonal electricity storage equation QESTOVOLTS (MWh)';
*VQESTOVOLTS.stage(IY411,IA,IS3,T,IPLUSMINUS) =  annot_blockStage(IS3,IY411);
*  'Feasibility in intra-seasonal heat storage equation VQHSTOVOLT (MWh)';
*VQHSTOVOLT.stage(IY411,IA,IS3,T,IPLUSMINUS)  = annot_blockStage(IS3,IY411);
*  'Feasibility in inter-seasonal heat storage equation VQHSTOVOLTS (MWh)';
*VQHSTOVOLTS.stage(IY411,IA,IS3,T,IPLUSMINUS) = annot_blockStage(IS3,IY411);
*  "Feasibility in electricity generation capacity accumulation (MW)";
*VQGKNACCUMNET.stage(IY411,IA,G,IPLUSMINUS)=  annot_blockStage(IS3,IY411);
* Feasibility in electricity balance equation QEEQ (MW)
*VQEEQ.stage(IY411,IR,IS3,T,IPLUSMINUS) = annot_blockStage(IS3,IY411);
* Feasibility in heat balance equation QHEQ (MW)
*VQHEQ.stage(IY411,IA,IS3,T,IPLUSMINUS) = annot_blockStage(IS3,IY411);
* Feasibility in intra-seasonal heat storage equation VQHSTOVOLT (MWh)
*VQHSTOVOLTS.stage(IY411,IA,IS3,T,IPLUSMINUS) = annot_blockStage(IS3,IY411);
* Feasibility in Transmission capacity constraint (MW)
*VQXK_UP.stage(IY411,IRRRE,IRRRI,IS3,T,IPLUSMINUS) = annot_blockStage(IS3,IY411);
*    "Feasibility in electricity generation limited by capacity (MW)";
*VQGKE_UP.stage(IY411,IA,G,IS3,T,IPLUSMINUS) =annot_blockStage(IS3,IY411);
*    "Feasibility in electricity generation limited by capacity (MW)";
*VQGKH_UP.stage(IY411,IA,G,IS3,T,IPLUSMINUS) = annot_blockStage(IS3,IY411);
* Feasibility in electricity balance equation QEEQ (MW)
*VQEEQ.stage(IY411,IR,IS3,T,IPLUSMINUS) =  annot_blockStage(IS3,IY411);
* Feasibility in heat balance equation QHEQ (MW)
*VQHEQ.stage(IY411,IA,IS3,T,IPLUSMINUS) = annot_blockStage(IS3,IY411);
*   "Feasibility of QHYRSMAXVOL (MWh)";
*VQHYRSMAXVOL.stage(IY411,IA,IS3,IPLUSMINUS)  =  annot_blockStage(IS3,IY411);
* "Feasibility of QHYMAXG (MW)";
*VQHYMAXG.stage(IY411,IA,IS3,T,IPLUSMINUS)  =  annot_blockStage(IS3,IY411);
*VQHYRSSEQ.stage(IY411,IA,IS3,IPLUSMINUS) = annot_blockStage(IS3,IY411);
*VQHYRSMINMAXVOL.stage(IY411,IA,IS3,IPLUSMINUS)  =annot_blockStage(IS3,IY411);
