* Latest revision 20180418 (hr)
* Coming to here from files for individual equations in folder  base/_addons/_hooks


$ifi %equation%==qeeq             - VQEEQ(IY411,IR,IS3,T,'IMINUS') + VQEEQ(IY411,IR,IS3,T,'IPLUS')
$ifi %equation%==qheq             + VQHEQ(IY411,IA,IS3,T,'IPLUS') - VQHEQ(IY411,IA,IS3,T,'IMINUS')
$ifi %equation%==qhyrsseq         + VQHYRSSEQ(IY411,IA,S,'IPLUS') - VQHYRSSEQ(IY411,IA,S,'IMINUS')
$ifi %equation%==qhyrsminvol      - VQHYRSMINVOL(IY411,IA,S,'IPLUS')
$ifi %equation%==qhyrsmaxvol      - VQHYRSMAXVOL(IY411,IA,S,'IMINUS')
$ifi not %reduced_vqdebug%==yes  $ifi %equation%==qhymaxg          + VQHYMAXG(IY411,IA,IS3,T,'IMINUS')
$ifi not %reduced_vqdebug%==yes  $ifi %equation%==qgfeq            - VQGFEQ(IY411,IA,G,IS3,T,'IPLUS') + VQGFEQ(IY411,IA,G,IS3,T,'IMINUS')
$ifi not %reduced_vqdebug%==yes  $ifi %equation%==qestovolt        - VQESTOVOLT(IY411,IA,IGESTO,IS3,T,'IPLUS') + VQESTOVOLT(IY411,IA,IGESTO,IS3,T,'IMINUS')
$ifi %equation%==qestovolts       - VQESTOVOLTS(IY411,IA,IGESTOS,S,T,'IPLUS') + VQESTOVOLTS(IY411,IA,IGESTOS,S,T,'IMINUS')
$ifi not %reduced_vqdebug%==yes  $ifi %equation%==qhstovolt        - VQHSTOVOLT(IY411,IA,IGHSTO,IS3,T,'IPLUS') + VQHSTOVOLT(IY411,IA,IGHSTO,IS3,T,'IMINUS')
$ifi %equation%==qhstovolts       - VQHSTOVOLTS(IY411,IA,IGHSTOS,S,T,'IPLUS') + VQHSTOVOLTS(IY411,IA,IGHSTOS,S,T,'IMINUS')
$ifi not %reduced_vqdebug%==yes  $ifi %equation%==qkefuelc         + VQKFUEL(IY411,C,FFF)
$ifi not %reduced_vqdebug%==yes  $ifi %equation%==qkefuelr         + VQKFUEL(IY411,IR,FFF)
$ifi not %reduced_vqdebug%==yes  $ifi %equation%==qkefuela         + VQKFUEL(IY411,IA,FFF)
$ifi not %reduced_vqdebug%==yes  $ifi %equation%==qgeqcf           + VQGEQF(IY411,C,FFF,'IPLUS') -  VQGEQF(IY411,C,FFF,'IMINUS')
$ifi not %reduced_vqdebug%==yes  $ifi %equation%==qgeqrf           + VQGEQF(IY411,IR,FFF,'IPLUS') - VQGEQF(IY411,IR,FFF,'IMINUS')
$ifi not %reduced_vqdebug%==yes  $ifi %equation%==qgeqaf           + VQGEQF(IY411,IA,FFF,'IPLUS') - VQGEQF(IY411,IA,FFF,'IMINUS')
$ifi not %reduced_vqdebug%==yes  $ifi %equation%==qktechgroupc     + VQKTECHGROUP(IY411,C,TECH_GROUP)
$ifi not %reduced_vqdebug%==yes  $ifi %equation%==qktechgroupr     + VQKTECHGROUP(IY411,IR,TECH_GROUP)
$ifi not %reduced_vqdebug%==yes  $ifi %equation%==qktechgroupa     + VQKTECHGROUP(IY411,IA,TECH_GROUP)
$ifi not %reduced_vqdebug%==yes  $ifi %equation%==qxk_up           + VQXK_UP(IY411,IRE,IRI,IS3,T,'IMINUS')- VQXK_UP(IY411,IRE,IRI,IS3,T,'IPLUS')
$ifi not %reduced_vqdebug%==yes  $ifi %equation%==qgknaccumnet     + VQGKNACCUMNET(IY411,IA,IGKFIND,'IPLUS') - VQGKNACCUMNET(IY411,IA,IGKFIND,'IMINUS')
$ifi not %reduced_vqdebug%==yes  $ifi %equation%==qxknaccumnet     + VQXKNACCUMNET(IY411,IRE,IRI,'IPLUS') - VQXKNACCUMNET(IY411,IRE,IRI,'IMINUS')
$ifi not %reduced_vqdebug%==yes  $ifi %equation%==qgke_up          + VQGKE_UP(IY411,IA,IGKENOSTO,IS3,T,'IMINUS')- VQGKE_UP(IY411,IA,IGKENOSTO,IS3,T,'IPLUS')
$ifi not %reduced_vqdebug%==yes  $ifi %equation%==qgkh_up          + VQGKH_UP(IY411,IA,IGKHNOSTO,IS3,T,'IMINUS')- VQGKH_UP(IY411,IA,IGKHNOSTO,IS3,T,'IPLUS')
$ifi not %reduced_vqdebug%==yes  $ifi %equation%==qucmaxvgf        - VQUCMAXVGF(IY411,IA,IGUC,IS3,T,'IPLUS')
$ifi not %reduced_vqdebug%==yes  $ifi %equation%==qucminvgf        - VQUCMINVGF(IY411,IA,IGUC,IS3,T,'IPLUS')
$ifi %equation%==qucut            - VQUCUT(IY411,IA,IGUC,S,T,'IPLUS') + VQUCUT(IY411,IA,IGUC,S,T,'IMINUS')
$ifi %equation%==qucdt            - VQUCDT(IY411,IA,IGUC,S,T,'IPLUS') + VQUCDT(IY411,IA,IGUC,S,T,'IMINUS')
$ifi not %reduced_vqdebug%==yes  $ifi %equation%==qucstartq        - VQUCSTARTQ(IY411,IA,IGUC,S,T,'IPLUS') + VQUCSTARTQ(IY411,IA,IGUC,S,T,'IMINUS')
$ifi not %reduced_vqdebug%==yes  $ifi %equation%==qucstartq_stoload_intra        - VQUCSTARTQ_STOLOAD_INTRA(IY411,IA,IGUC,S,T,'IPLUS') + VQUCSTARTQ_STOLOAD_INTRA(IY411,IA,IGUC,S,T,'IMINUS')
$ifi not %reduced_vqdebug%==yes  $ifi %equation%==qucstartq_stoload_inter        - VQUCSTARTQ_STOLOAD_INTER(IY411,IA,IGUC,S,T,'IPLUS') + VQUCSTARTQ_STOLOAD_INTER(IY411,IA,IGUC,S,T,'IMINUS')
$ifi %equation%==qucrampu         - VQUCRAMPU(IY411,IA,IGUC,S,T,'IPLUS') + VQUCRAMPU(IY411,IA,IGUC,S,T,'IMINUS')
$ifi %equation%==qucrampd         - VQUCRAMPD(IY411,IA,IGUC,S,T,'IPLUS') + VQUCRAMPD(IY411,IA,IGUC,S,T,'IMINUS')
$ifi not %reduced_vqdebug%==yes  $ifi %equation%==qucvucon_existing  - VQUCVUCON_EXISTING(IY411,IA,IGUC,IS3,T,'IPLUS') + VQUCVUCON_EXISTING(IY411,IA,IGUC,IS3,T,'IMINUS')
$ifi not %reduced_vqdebug%==yes  $ifi %equation%==qucvucon_existing_stoload  - VQUCVUCON_EXISTING_STOLOAD(IY411,IA,IGUC,IS3,T,'IPLUS') + VQUCVUCON_EXISTING_STOLOAD(IY411,IA,IGUC,IS3,T,'IMINUS')
$ifi %equation%==qmbgh_t           - VQBMGH_T(IY411,IA,IGEH,IS3,'IPLUS') + VQBMGH_T(IY411,IA,IGEH,IS3,'IMINUS')
$ifi %equation%==qhydrogen_eq_area        - VHYDROGEN_QH2EQ(IY411,IA,IS3,T,'IMINUS') + VHYDROGEN_QH2EQ(IY411,IA,IS3,T,'IPLUS')
$ifi %equation%==qhydrogen_eq             - VHYDROGEN_QH2EQ(IY411,IR,IS3,T,'IMINUS') + VHYDROGEN_QH2EQ(IY411,IR,IS3,T,'IPLUS')
$ifi %equation%==qhydrogen_stovol        + VQHYDROGEN_STOVOL(IY411,IA,IHYDROGEN_GH2STO,S,T,'IMINUS') - VQHYDROGEN_STOVOL(IY411,IA,IHYDROGEN_GH2STO,S,T,'IPLUS')
$ifi %equation%==qbiomethane_stovolts    + VQBIOMETHANE_STOVOLTS(IY411,S,T,'IMINUS') - VQBIOMETHANE_STOVOLTS(IY411,S,T,'IPLUS')
$ifi %equation%==qtranspeakdemand        + VQTRANSPEAKDEMAND(IY411,IR,IS3,T,'IMINUS') - VQTRANSPEAKDEMAND(IY411,IR,IS3,T,'IPLUS')
$ifi %equation%==qhyrsseqcurt            + VQHYRSSEQCURT(IY411,IA,S,'IPLUS') - VQHYRSSEQCURT(IY411,IA,S,'IMINUS')


$ifi not %equation%==qobj  $goto endoffile

* -- Objective function --------------------------------------------------------
$ifi %equation%==qobj


* Infeasibility penalties:
   + PENALTYQ*(
$ifi %BB1%==yes    +SUM((IA,IS3)$SUM(IGHYRS,IAGKFX(IA,IGHYRS)),(VQHYRSSEQ(IA,IS3,'IMINUS')+VQHYRSSEQ(IA,IS3,'IPLUS')))

$ifi %BB2%==yes       +SUM((IA,IS3)$SUM(IGHYRS,IAGKFX(IA,IGHYRS)),(VQHYRSSEQ(IA,IS3,'IMINUS')+VQHYRSSEQ(IA,IS3,'IPLUS')))
$ifi %BB1%==yes    +SUM((IA,IS3)$SUM(IGHYRS,IAGKFX(IA,IGHYRS)),(VQHYRSMINMAXVOL(IA,IS3,'IMINUS')+VQHYRSMINMAXVOL(IA,IS3,'IPLUS')))
$ifi %BB2%==yes    +SUM((IA,IS3)$SUM(IGHYRS,IAGKFX(IA,IGHYRS)),(VQHYRSMINMAXVOL(IA,IS3,'IMINUS')+VQHYRSMINMAXVOL(IA,IS3,'IPLUS')))
* BB4:

$ifi not %reduced_vqdebug%==yes    +SUM((IA,IGHSTO,IS3,T)$IAGK_HASORPOT(Y,IA,IGHSTO), (VQHSTOVOLT(Y,IA,IGHSTO,IS3,T,'IMINUS')+VQHSTOVOLT(Y,IA,IGHSTO,IS3,T,'IPLUS')))
$ifi not %reduced_vqdebug%==yes    +SUM((IA,IGESTO,IS3,T)$IAGK_HASORPOT(Y,IA,IGESTO), (VQESTOVOLT(Y,IA,IGESTO,IS3,T,'IMINUS')+VQESTOVOLT(Y,IA,IGESTO,IS3,T,'IPLUS')))
                                    +SUM((IA,IGHSTOS,IS3,T)$(IAGK_HASORPOT(Y,IA,IGHSTOS)), (VQHSTOVOLTS(Y,IA,IGHSTOS,IS3,T,'IMINUS')+VQHSTOVOLTS(Y,IA,IGHSTOS,IS3,T,'IPLUS')))
                                    +SUM((IA,IGESTOS,IS3,T)$(IAGK_HASORPOT(Y,IA,IGESTOS)), (VQESTOVOLTS(Y,IA,IGESTOS,IS3,T,'IMINUS')+VQESTOVOLTS(Y,IA,IGESTOS,IS3,T,'IPLUS')))
                                    +SUM((IR,IS3,T), (VQEEQ(Y,IR,IS3,T,'IMINUS')+VQEEQ(Y,IR,IS3,T,'IPLUS')))
     +SUM((IA,IS3,T)$(SUM(DHUSER, IDH_SUMST(IA,DHUSER))
$ifi  %HEATTRANS%==yes OR SUM(IAE,IXHK_HASORPOT(Y,IAE,IA)) OR SUM(IAI,IXHK_HASORPOT(Y,IA,IAI))
     ), (VQHEQ(Y,IA,IS3,T,'IMINUS')+VQHEQ(Y,IA,IS3,T,'IPLUS')))
$ifi not %reduced_vqdebug%==yes     +SUM((IA,G,IS3,T)$IAGK_HASORPOT(Y,IA,G), (VQGFEQ(Y,IA,G,IS3,T,'IMINUS')+VQGFEQ(Y,IA,G,IS3,T,'IPLUS')))
                                    +SUM((IA,IS3)$(SUM(IGHYRS,IAGK_HASORPOT(Y,IA,IGHYRS))),(VQHYRSSEQ(Y,IA,IS3,'IMINUS')+VQHYRSSEQ(Y,IA,IS3,'IPLUS')))
                                    +SUM((IA,IS3_NEXT)$(HYRSDATA(IA,"HYRSMINVOL",IS3_NEXT) AND SUM(IGHYRS$IAGK_HASORPOT(Y,IA,IGHYRS),1)),(VQHYRSMINVOL(Y,IA,IS3_NEXT,'IPLUS')))
                                    +SUM((IA,IS3_NEXT)$(HYRSDATA(IA,"HYRSMAXVOL",IS3_NEXT) AND SUM(IGHYRS$IAGK_HASORPOT(Y,IA,IGHYRS),1)),(VQHYRSMAXVOL(Y,IA,IS3_NEXT,'IMINUS')))
$ifi not %reduced_vqdebug%==yes    +SUM((IA,IS3,T)$(SUM(IGHYRS,IAGK_HASORPOT(Y,IA,IGHYRS)) OR SUM(IGHYRR,IAGK_HASORPOT(Y,IA,IGHYRR))), VQHYMAXG(Y,IA,IS3,T,'IMINUS'))

$ifi not %reduced_vqdebug%==yes   +SUM((IA,IGKFIND)$(IAGK_HASORPOT(Y,IA,IGKFIND) AND IAGKN(IA,IGKFIND)), (VQGKNACCUMNET(Y,IA,IGKFIND,"IPLUS")+VQGKNACCUMNET(Y,IA,IGKFIND,"IMINUS")))
$ifi not %reduced_vqdebug%==yes    +SUM((IRE,IRI)$SUM(IYALIAS2$(YVALUE(IYALIAS2) LE YVALUE(Y)),IXKN(IYALIAS2,IRE,IRI)), VQXKNACCUMNET(Y,IRE,IRI,"IPLUS")+VQXKNACCUMNET(Y,IRE,IRI,"IMINUS"))

$ifi not %reduced_vqdebug%==yes    +SUM((IA,IGDISPATCH(IGKENOSTO),IS3,T)$(IAGK_HASORPOT(Y,IA,IGKENOSTO) AND (IAGKN(IA,IGKENOSTO) OR IGDECOMEXOPOT(Y,IA,IGKENOSTO))), (VQGKE_UP(Y,IA,IGKENOSTO,IS3,T,'IMINUS')+VQGKE_UP(Y,IA,IGKENOSTO,IS3,T,'IPLUS')))
$ifi not %reduced_vqdebug%==yes    +SUM((IA,IGDISPATCH(IGKHNOSTO),IS3,T)$(IAGK_HASORPOT(Y,IA,IGKHNOSTO) AND (IAGKN(IA,IGKHNOSTO) OR IGDECOMEXOPOT(Y,IA,IGKHNOSTO))), (VQGKH_UP(Y,IA,IGKHNOSTO,IS3,T,'IMINUS')+VQGKH_UP(Y,IA,IGKHNOSTO,IS3,T,'IPLUS')))
$ifi not %reduced_vqdebug%==yes    +SUM((IRE,IRI,IS3,T)$IXK_HASORPOT(Y,IRE,IRI), (VQXK_UP(Y,IRE,IRI,IS3,T,'IMINUS')+VQXK_UP(Y,IRE,IRI,IS3,T,'IPLUS')))

$ifi not %reduced_vqdebug%==yes    +SUM((C,FFF)$FKPOT(C,FFF),   VQKFUEL(Y,C,FFF))
$ifi not %reduced_vqdebug%==yes    +SUM((IR,FFF)$FKPOT(IR,FFF), VQKFUEL(Y,IR,FFF))
$ifi not %reduced_vqdebug%==yes    +SUM((IA,FFF)$FKPOT(IA,FFF), VQKFUEL(Y,IA,FFF))

$ifi not %reduced_vqdebug%==yes    +SUM((C,FFF)$IGEQF(Y,C,FFF),   VQGEQF(Y,C,FFF,"IPLUS") + VQGEQF(Y,C,FFF,"IMINUS"))
$ifi not %reduced_vqdebug%==yes    +SUM((IR,FFF)$IGEQF(Y,IR,FFF), VQGEQF(Y,IR,FFF,"IPLUS") + VQGEQF(Y,IR,FFF,"IMINUS"))
$ifi not %reduced_vqdebug%==yes    +SUM((IA,FFF)$IGEQF(Y,IA,FFF), VQGEQF(Y,IA,FFF,"IPLUS") + VQGEQF(Y,IA,FFF,"IMINUS"))

$ifi not %reduced_vqdebug%==yes    +SUM((C,TECH_GROUP)$TECHGROUPKPOT(C,TECH_GROUP),   VQKTECHGROUP(Y,C,TECH_GROUP))
$ifi not %reduced_vqdebug%==yes    +SUM((IR,TECH_GROUP)$TECHGROUPKPOT(IR,TECH_GROUP), VQKTECHGROUP(Y,IR,TECH_GROUP))
$ifi not %reduced_vqdebug%==yes    +SUM((IA,TECH_GROUP)$TECHGROUPKPOT(IA,TECH_GROUP), VQKTECHGROUP(Y,IA,TECH_GROUP))

$ifi not %reduced_vqdebug%==yes $ifi %UnitComm%==yes       +SUM((IA,IGUC,IS3,T)$IAGK_HASORPOT(Y,IA,IGUC), VQUCMAXVGF(Y,IA,IGUC,IS3,T,'IPLUS'))
$ifi not %reduced_vqdebug%==yes $ifi %UnitComm%==yes       +SUM((IA,IGUC,IS3,T)$(IAGK_HASORPOT(Y,IA,IGUC) AND GDATA(IGUC,'GDUCGMIN')), VQUCMINVGF(Y,IA,IGUC,IS3,T,'IPLUS'))
$ifi not %reduced_vqdebug%==yes $ifi %UnitComm%==yes       +SUM((IA,IGUC,IS3_NEXT,T)$(IAGK_HASORPOT(Y,IA,IGUC)), (VQUCSTARTQ(Y,IA,IGUC,IS3_NEXT,T,'IMINUS')+VQUCSTARTQ(Y,IA,IGUC,IS3_NEXT,T,'IPLUS')))
$ifi %UnitComm%==yes       +SUM((IA,IGUC,IS3_NEXT,T)$(IAGK_HASORPOT(Y,IA,IGUC) AND(GDATA(IGUC,'GDUCUTMIN') GT CHRONOHOUR(IS3_NEXT,T))), (VQUCUT(Y,IA,IGUC,IS3_NEXT,T,'IMINUS')+VQUCUT(Y,IA,IGUC,IS3_NEXT,T,'IPLUS')))
$ifi %UnitComm%==yes       +SUM((IA,IGUC,IS3_NEXT,T)$(IAGK_HASORPOT(Y,IA,IGUC) AND (GDATA(IGUC,'GDUCDTMIN') GT CHRONOHOUR(IS3_NEXT,T))), (VQUCDT(Y,IA,IGUC,IS3_NEXT,T,'IMINUS')+VQUCDT(Y,IA,IGUC,IS3_NEXT,T,'IPLUS')))
$ifi not %reduced_vqdebug%==yes $ifi %UnitComm%==yes       +SUM((IA,IGUC,IS3,T)$(IAGK_HASORPOT(Y,IA,IGUC) AND (IGESTO(IGUC) OR IGHSTO(IGUC))), (VQUCSTARTQ_STOLOAD_INTRA(Y,IA,IGUC,IS3,T,'IMINUS')+VQUCSTARTQ_STOLOAD_INTRA(Y,IA,IGUC,IS3,T,'IPLUS')))
$ifi not %reduced_vqdebug%==yes $ifi %UnitComm%==yes       +SUM((IA,IGUC,IS3,T)$(IAGK_HASORPOT(Y,IA,IGUC) AND (IGESTOS(IGUC) OR IGHSTOS(IGUC))), (VQUCSTARTQ_STOLOAD_INTER(Y,IA,IGUC,IS3,T,'IMINUS')+VQUCSTARTQ_STOLOAD_INTER(Y,IA,IGUC,IS3,T,'IPLUS')))
$ifi %UnitComm%==yes   $ifi not %STEPWISE_RAMPING_UC%==no_ramping +SUM((IA,IGUC,IS3_NEXT,T)$(IAGK_HASORPOT(Y,IA,IGUC) AND GDATA(IGUC,'GDUCRAMPU') LT CHRONOHOUR(IS3_NEXT,T)), (VQUCRAMPU(Y,IA,IGUC,IS3_NEXT,T,'IMINUS')+VQUCRAMPU(Y,IA,IGUC,IS3_NEXT,T,'IPLUS')))
$ifi %UnitComm%==yes   $ifi not %STEPWISE_RAMPING_UC%==no_ramping +SUM((IA,IGUC,IS3_NEXT,T)$(IAGK_HASORPOT(Y,IA,IGUC) AND GDATA(IGUC,'GDUCRAMPD') LT CHRONOHOUR(IS3_NEXT,T)), (VQUCRAMPD(Y,IA,IGUC,IS3_NEXT,T,'IMINUS')+VQUCRAMPD(Y,IA,IGUC,IS3_NEXT,T,'IPLUS')))

$ifi not %reduced_vqdebug%==yes $ifi %UnitComm%==yes  $ifi %PLANNED_MAINTENANCE%==yes  +SUM((IA,IGUC,IS3,T)$(IAGK_HASORPOT(Y,IA,IGUC) AND NOT(IAGKN(IA,IGUC)) AND NOT(IGDECOMEXOPOT(Y,IA,IGUC))
$ifi not %reduced_vqdebug%==yes $ifi %UnitComm%==yes  $ifi %PLANNED_MAINTENANCE%==yes $ifi not %ADDPLANNEDMAINTENANCE%==yes AND IGPLANMAINT(IGUC)
$ifi not %reduced_vqdebug%==yes $ifi %UnitComm%==yes  $ifi %PLANNED_MAINTENANCE%==yes $ifi     %ADDPLANNEDMAINTENANCE%==yes AND UCONMAINT(Y,IA,IGUC,IS3)
$ifi not %reduced_vqdebug%==yes $ifi %UnitComm%==yes  $ifi %PLANNED_MAINTENANCE%==yes ), (VQUCVUCON_EXISTING(Y,IA,IGUC,IS3,T,'IMINUS')+VQUCVUCON_EXISTING(Y,IA,IGUC,IS3,T,'IPLUS')))

$ifi not %reduced_vqdebug%==yes $ifi %UnitComm%==yes  $ifi %PLANNED_MAINTENANCE%==yes  +SUM((IA,IGUC,IS3,T)$(IAGK_HASORPOT(Y,IA,IGUC) AND NOT(IAGKN(IA,IGUC)) AND NOT(IGDECOMEXOPOT(Y,IA,IGUC)) AND (IGESTOALL(IGUC) OR IGHSTOALL(IGUC))
$ifi not %reduced_vqdebug%==yes $ifi %UnitComm%==yes  $ifi %PLANNED_MAINTENANCE%==yes $ifi not %ADDPLANNEDMAINTENANCE%==yes AND IGPLANMAINT(IGUC)
$ifi not %reduced_vqdebug%==yes $ifi %UnitComm%==yes  $ifi %PLANNED_MAINTENANCE%==yes $ifi     %ADDPLANNEDMAINTENANCE%==yes AND UCONMAINT(Y,IA,IGUC,IS3)
$ifi not %reduced_vqdebug%==yes $ifi %UnitComm%==yes  $ifi %PLANNED_MAINTENANCE%==yes ), (VQUCVUCON_EXISTING_STOLOAD(Y,IA,IGUC,IS3,T,'IMINUS')+VQUCVUCON_EXISTING_STOLOAD(Y,IA,IGUC,IS3,T,'IPLUS')))

$ifi %BalancingMarket%==yes $ifi %NOHEATMARKET%==yes   +SUM((IA,IGEH,IS3)$IAGK_HASORPOT(Y,IA,IGEH), (VQBMGH_T(Y,IA,IGEH,IS3,'IMINUS')+VQBMGH_T(Y,IA,IGEH,IS3,'IPLUS')))

$ifi %HYDROGEN%==yes    + SUM((IR,IS3,T),(VHYDROGEN_QH2EQ(Y,IR,IS3,T,'IMINUS')+VHYDROGEN_QH2EQ(Y,IR,IS3,T,'IPLUS')))
$ifi %HYDROGEN%==yes    + SUM((IA,IS3,T)$HYDROGEN_DH2(Y,IA),(VHYDROGEN_QH2EQ(Y,IA,IS3,T,'IMINUS')+VHYDROGEN_QH2EQ(Y,IA,IS3,T,'IPLUS')))
$ifi %HYDROGEN%==yes    + SUM((IA,IHYDROGEN_GH2STO,IS3,T)$IAGK_HASORPOT(Y,IA,IHYDROGEN_GH2STO),VQHYDROGEN_STOVOL(Y,IA,IHYDROGEN_GH2STO,IS3,T,'IMINUS') + VQHYDROGEN_STOVOL(Y,IA,IHYDROGEN_GH2STO,IS3,T,'IPLUS'))
$ifi %HYDROGEN%==yes    + SUM((IS3,T)$(SUM((IA,IGBIOMETHANE),IAGK_HASORPOT(Y,IA,IGBIOMETHANE)) AND SUM((IA,IHYDROGEN_GH2TOBIOMETH),IAGK_HASORPOT(Y,IA,IHYDROGEN_GH2TOBIOMETH))),VQBIOMETHANE_STOVOLTS(Y,IS3,T,'IMINUS') + VQBIOMETHANE_STOVOLTS(Y,IS3,T,'IPLUS'))

$ifi %TRANSPORT%==yes   +SUM((IR,IS3,T)$SUM(RRR,TRANSDEMAND_Y(Y,RRR)), (VQTRANSPEAKDEMAND(Y,IR,IS3,T,'IMINUS')+VQTRANSPEAKDEMAND(Y,IR,IS3,T,'IPLUS')))
$ifi %import_results%==yes  $ifi %HYRSBB123%==price   +SUM((IA,IS3)$(SUM(IGHYRS,IAGK_HASORPOT(Y,IA,IGHYRS))),(VQHYRSSEQCURT(Y,IA,IS3,'IMINUS')+VQHYRSSEQCURT(Y,IA,IS3,'IPLUS')))


)
* -- Objective function End ----------------------------------------------------


$label  endoffile
