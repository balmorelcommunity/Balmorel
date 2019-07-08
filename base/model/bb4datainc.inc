* Hans: søg "/*"

* File bb4datainc.inc for including data for Balmorel, model BB4.

* Data for any ID is held in a separate file, and $included here.
* The mechanism is basically the same for all IDs, viz. four lines:
*    the declaration of the ID followed by %semislash% (the declaration is identical to the one in Balmorel.gms)
*    attempt to include the file from the data folder for the present Case
*    if unsuccesfull: include the file from the data folder for the Base Case
*    %semislash%;
*
* Exceptions:
* - Acronyms: acronyms for generation technologies are found in Balmorel.gms
*             acronyms for fuels are found in the data file FFF.inc
* - Options (also for addon) are used with $ifi statements and option names
* - The IDs for geography internal sets ICA, IR and IA are assigned in this file
* - The IDs for technology internal sets (IGCND etc.) are assigned in this file


* Printing of data to the list file controlled by %ONOFFDATALISTING% and %ONOFFCODELISTING%
* (see file balgams.opt):
%ONOFFDATALISTING%


* TESTING: (indsætter datainc1 her, plus lidt kode) ----------------------------
* Geography

SET CCCRRRAAA          "All geographical entities (CCC + RRR + AAA)" %semislash%
$if     EXIST '../data/CCCRRRAAA.inc' $INCLUDE         '../data/CCCRRRAAA.inc';
$if not EXIST '../data/CCCRRRAAA.inc' $INCLUDE '../../base/data/CCCRRRAAA.inc';
%semislash%;

SET CCC(CCCRRRAAA)       "All Countries" %semislash%
$if     EXIST '../data/CCC.inc' $INCLUDE         '../data/CCC.inc';
$if not EXIST '../data/CCC.inc' $INCLUDE '../../base/data/CCC.inc';
%semislash%;

SET RRR(CCCRRRAAA)       "All regions" %semislash%
$if     EXIST '../data/RRR.inc' $INCLUDE         '../data/RRR.inc';
$if not EXIST '../data/RRR.inc' $INCLUDE '../../base/data/RRR.inc';
%semislash%;

SET AAA(CCCRRRAAA)       "All areas" %semislash%
$if     EXIST '../data/AAA.inc' $INCLUDE         '../data/AAA.inc';
$if not EXIST '../data/AAA.inc' $INCLUDE '../../base/data/AAA.inc';
%semislash%;

SET CCCRRR(CCC,RRR)      "Regions in countries" %semislash%
$if     EXIST '../data/CCCRRR.inc' $INCLUDE      '../data/CCCRRR.inc';
$if not EXIST '../data/CCCRRR.inc' $INCLUDE '../../base/data/CCCRRR.inc';
%semislash%;

SET RRRAAA(RRR,AAA)      "Areas in regions" %semislash%
$if     EXIST '../data/RRRAAA.inc' $INCLUDE         '../data/RRRAAA.inc';
$if not EXIST '../data/RRRAAA.inc' $INCLUDE '../../base/data/RRRAAA.inc';
%semislash%;

SET C(CCC)    "Countries in the simulation"  %semislash%
$if     EXIST '../data/C.inc' $INCLUDE         '../data/C.inc';
$if not EXIST '../data/C.inc' $INCLUDE '../../base/data/C.inc';

* ------------------------------------------------------------------------------
%ONOFFCODELISTING%
* (Text and assignment of geography related subsets in file dataincBB4.inc:)
* The three internal IDs: IDs ICA, IR and IA are assigned as early as possible, based on available data.
* This permits application of ICA, IR and IA rather than RRR and AAA
* in assignments in all remaining data files (to limit calculation time and storage use).
* The simple way to limit the geographical scope of the model is to specify
* in the input data the set C as a proper subset of the set CCC,
* because then the following mechanism will automatically exclude all regions
* and areas not in any country in C.
ICA(CCC,AAA) = YES$(SUM(RRR$(RRRAAA(RRR,AAA) AND CCCRRR(CCC,RRR)),1) GT 0);
IR(RRR) = YES$(SUM(C,CCCRRR(C,RRR)));
IA(AAA) = YES$(SUM(C,ICA(C,AAA)));
* (Text and assignment of geography related subsets in file dataincBB4.inc end.)
%ONOFFDATALISTING%
* ------------------------------------------------------------------------------

* ------------------------------------------------------------------------------
* No need to continue if there are errors
$if not errorfree $abort "Balmorel processing aborted after inclusion of file dataincBB4.inc due to geography related data errors";
* ------------------------------------------------------------------------------


SET YYY                "All years"  %semislash%
$if     EXIST '../data/YYY.inc' $INCLUDE      '../data/YYY.inc';
$if not EXIST '../data/YYY.inc' $INCLUDE '../../base/data/YYY.inc';
%semislash%;

SET SSS                "All seasons" %semislash%
$if     EXIST '../data/SSS.inc' $INCLUDE      '../data/SSS.inc';
$if not EXIST '../data/SSS.inc' $INCLUDE '../../base/data/SSS.inc';
%semislash%;

SET TTT                "All time periods" %semislash%
$if     EXIST '../data/TTT.inc' $INCLUDE      '../data/TTT.inc';
$if not EXIST '../data/TTT.inc' $INCLUDE '../../base/data/TTT.inc';
%semislash%;

SET DEUSER             "Electricity demand user groups. Set must include element RESE for holding demand not included in any other user group"  %semislash%
$if     EXIST '../data/DEUSER.inc' $INCLUDE         '../data/DEUSER.inc';
$if not EXIST '../data/DEUSER.inc' $INCLUDE '../../base/data/DEUSER.inc';
%semislash%;

SET DHUSER             "Heat demand user groups. Set must include element RESH for holding demand not included in any other user group"  %semislash%
$if     EXIST '../data/DEUSER.inc' $INCLUDE         '../data/DHUSER.inc';
$if not EXIST '../data/DEUSER.inc' $INCLUDE '../../base/data/DHUSER.inc';
%semislash%;

SET FFF                "Fuels"  %semislash%
$if     EXIST '../data/FFF.inc' $INCLUDE      '../data/FFF.inc';
$if not EXIST '../data/FFF.inc' $INCLUDE '../../base/data/FFF.inc';
%semislash%;

SET FDATASET           "Characteristics of fuels " %semislash%
$if     EXIST '../data/FDATASET.inc' $INCLUDE      '../data/FDATASET.inc';
$if not EXIST '../data/FDATASET.inc' $INCLUDE '../../base/data/FDATASET.inc';
%semislash%;

PARAMETER FDATA(FFF,FDATASET)    "Fuel specific values" %semislash%
$if     EXIST '../data/FDATA.inc' $INCLUDE      '../data/FDATA.inc';
$if not EXIST '../data/FDATA.inc' $INCLUDE '../../base/data/FDATA.inc';
%semislash%;

SET GGG          "All generation technologies"   %semislash%
$if     EXIST '../data/GGG.inc' $INCLUDE      '../data/GGG.inc';
$if not EXIST '../data/GGG.inc' $INCLUDE '../../base/data/GGG.inc';
%semislash%;

SET GDATASET     "Generation technology data" %semislash%
$if     EXIST '../data/GDATASET.inc' $INCLUDE      '../data/GDATASET.inc';
$if not EXIST '../data/GDATASET.inc' $INCLUDE '../../base/data/GDATASET.inc';
%semislash%;

SET TECH_GROUP     "Technology Groups" %semislash%
$if     EXIST '../data/TECH_GROUP.inc' $INCLUDE      '../data/TECH_GROUP.inc';
$if not EXIST '../data/TECH_GROUP.inc' $INCLUDE '../../base/data/TECH_GROUP.inc';
%semislash%;

PARAMETER TECH_GROUP_VALUE(TECH_GROUP)         "Technology Groups value" %semislash%
$if     EXIST '../data/TECH_GROUP_VALUE.inc' $INCLUDE      '../data/TECH_GROUP_VALUE.inc';
$if not EXIST '../data/TECH_GROUP_VALUE.inc' $INCLUDE '../../base/data/TECH_GROUP_VALUE.inc';
%semislash%;

SET SUBTECH_GROUP     "SubTechnology Groups" %semislash%
$if     EXIST '../data/SUBTECH_GROUP.inc' $INCLUDE      '../data/SUBTECH_GROUP.inc';
$if not EXIST '../data/SUBTECH_GROUP.inc' $INCLUDE '../../base/data/SUBTECH_GROUP.inc';
%semislash%;

PARAMETER SUBTECH_GROUP_VALUE(SUBTECH_GROUP)         "Technology Groups value" %semislash%
$if     EXIST '../data/SUBTECH_GROUP_VALUE.inc' $INCLUDE      '../data/SUBTECH_GROUP_VALUE.inc';
$if not EXIST '../data/SUBTECH_GROUP_VALUE.inc' $INCLUDE '../../base/data/SUBTECH_GROUP_VALUE.inc';
%semislash%;

SET G(GGG)    "Generation technologies in the simulation"  %semislash%
$if     EXIST '../data/G.inc' $INCLUDE         '../data/G.inc';
$if not EXIST '../data/G.inc' $INCLUDE '../../base/data/G.inc';
%semislash%;


*-------------------------------------------------------------------------------
*----- Any declarations and definitions of sets, aliases and acronyms for addon:
*-------------------------------------------------------------------------------

$include "../../base/addons/_hooks/acronyms.inc"
$include "../../base/addons/_hooks/setdeclare.inc"
$include "../../base/addons/_hooks/setdefine.inc"

* Duplication of sets for describing possible heat exchange between areas (option HEATTRANS).
$ifi %HEATTRANS%==yes ALIAS (AAA,IAAAE,IAAAI);
$ifi %HEATTRANS%==yes ALIAS (IA,IAE,IAI);

*-------------------------------------------------------------------------------
* End: Any declarations and definitions of sets, aliases and acronyms for addon
*-------------------------------------------------------------------------------

PARAMETER GDATA(GGG,GDATASET)    "Technologies characteristics" %semislash%
$if     EXIST '../data/GDATA.inc' $INCLUDE         '../data/GDATA.inc';
$if not EXIST '../data/GDATA.inc' $INCLUDE '../../base/data/GDATA.inc';


*This could be placed more elegantly elsewhere
*-------------------------------------------------------------------------------
*------------- Any GDATA additions for addon to be placed here: ----------------
*-------------------------------------------------------------------------------
$include "../../base/addons/_hooks/gdataadditions.inc"


* ------------------------------------------------------------------------------
%ONOFFCODELISTING%

* (Text and assignment of technology related subsets in file dataincbb4.inc end.)
%ONOFFDATALISTING%
* ------------------------------------------------------------------------------

* ------------------------------------------------------------------------------
* No need to continue if there are errors
$if not errorfree $abort "Balmorel processing aborted after inclusion of file dataincBB4.inc due to technology related data errors";
* ------------------------------------------------------------------------------

PARAMETER HYRSMAXVOL_G(AAA,GGG) "Reservoir capacity (MWh storage capacity / MW installed capacity)"  %semislash%
$if     EXIST '../data/HYRSMAXVOL_G.inc' $INCLUDE         '../data/HYRSMAXVOL_G.inc';
$if not EXIST '../data/HYRSMAXVOL_G.inc' $INCLUDE '../../base/data/HYRSMAXVOL_G.inc';
%semislash%;

SET HYRSDATASET  "Characteristics of hydro reservoirs" %semislash%
$if     EXIST '../data/HYRSDATASET.inc' $INCLUDE      '../data/HYRSDATASET.inc';
$if not EXIST '../data/HYRSDATASET.inc' $INCLUDE '../../base/data/HYRSDATASET.inc';
%semislash%;

SET DF_QP  "Quantity and price information for elastic demands" %semislash%
$if     EXIST '../data/DF_QP.inc' $INCLUDE      '../data/DF_QP.inc';
$if not EXIST '../data/DF_QP.inc' $INCLUDE '../../base/data/DF_QP.inc';
%semislash%;

SET MPOLSET  "Emission and other policy data"   %semislash%
$if     EXIST '../data/MPOLSET.inc' $INCLUDE      '../data/MPOLSET.inc';
$if not EXIST '../data/MPOLSET.inc' $INCLUDE '../../base/data/MPOLSET.inc';
%semislash%;

$onmulti
SET AGKN(AAA,GGG)   "Areas for possible location of new technologies"   %semislash%
$if     EXIST '../data/AGKN.inc' $INCLUDE         '../data/AGKN.inc';
$if not EXIST '../data/AGKN.inc' $INCLUDE '../../base/data/AGKN.inc';
%semislash%;
$offmulti

SET Y(YYY)    "Years in the simulation"   %semislash%
$if     EXIST '../data/Y.inc' $INCLUDE      '../data/Y.inc';
$if not EXIST '../data/Y.inc' $INCLUDE '../../base/data/Y.inc';
%semislash%;

* Aliases relative to Y moved here for strong convenience:
ALIAS (Y,IYALIAS);
ALIAS (Y,IYALIAS2);

SET S(SSS)    "Seasons in the simulation"   %semislash%
$if     EXIST '../data/S.inc' $INCLUDE      '../data/S.inc';
$if not EXIST '../data/S.inc' $INCLUDE '../../base/data/S.inc';
%semislash%;

* Calculation of reverse indexed sets
SREV(S,S+(card(S)-2*ord(S)+1)) = YES;
SREV2(S,S+(card(S)-2*ord(S)+1)) = YES;

SET T(TTT)    "Time periods within the season in the simulation"  %semislash%
$if     EXIST '../data/T.inc' $INCLUDE         '../data/T.inc';
$if not EXIST '../data/T.inc' $INCLUDE '../../base/data/T.inc';
%semislash%;

TREV(T,T+(card(T)-2*ord(T)+1)) = YES;
TREV2(T,T+(card(T)-2*ord(T)+1)) = YES;

PARAMETER YVALUE(YYY)   "Numerical value of the years labels"  %semislash%
$if     EXIST '../data/YVALUE.inc' $INCLUDE      '../data/YVALUE.inc';
$if not EXIST '../data/YVALUE.inc' $INCLUDE '../../base/data/YVALUE.inc';
%semislash%;

*SET DAYTYPE       "Types of days within the week, typically workdays/weekend" %semislash%
*$if     EXIST '../data/DAYTYPE.inc' $INCLUDE         '../data/DAYTYPE.inc';
*$if not EXIST '../data/DAYTYPE.inc' $INCLUDE '../../base/data/DAYTYPE.inc';
*%semislash%

SET TWORKDAY(TTT)   "Time segments, T, in workdays"  %semislash%
$if     EXIST '../data/TWORKDAY.inc' $INCLUDE         '../data/TWORKDAY.inc';
$if not EXIST '../data/TWORKDAY.inc' $INCLUDE '../../base/data/TWORKDAY.inc';
%semislash%

SET TWEEKEND(TTT)   "Time segments, T, in weekends"   %semislash%
$if     EXIST '../data/TWEEKEND.inc' $INCLUDE         '../data/TWEEKEND.inc';
$if not EXIST '../data/TWEEKEND.inc' $INCLUDE '../../base/data/TWEEKEND.inc';
%semislash%
                                      /* todos
SET ECONSET         "Set for econ"  %semislash%
$if     EXIST '../data/ECONSET.inc' $INCLUDE         '../data/ECONSET.inc';
$if not EXIST '../data/ECONSET.inc' $INCLUDE '../../base/data/ECONSET.inc';
%semislash%

SET ECONSETCATEGORY "Set for econ"  %semislash%
$if     EXIST '../data/ECONSETCATEGORY.inc' $INCLUDE         '../data/ECONSETCATEGORY.inc';
$if not EXIST '../data/ECONSETCATEGORY.inc' $INCLUDE '../../base/data/ECONSETCATEGORY.inc';
%semislash%                            */


*-------------------------------------------------------------------------------
*----- Any declarations and definitions of sets, aliases and acronyms for addon:
*-------------------------------------------------------------------------------

$ifi not %dflexquant%==yes $goto dflexquantend
* ------------------------------------------------------------------------------
SET DEF  "Steps in elastic electricity demand"  %semislash%
$if     EXIST '../data/DEF.inc' $INCLUDE      '../data/DEF.inc';
$if not EXIST '../data/DEF.inc' $INCLUDE '../../base/data/DEF.inc';
%semislash%;

SET DEF_D1(DEF)   "Downwards steps in elastic el. demand, relative data format" %semislash%
$if     EXIST '../data/DEF_D1.inc' $INCLUDE      '../data/DEF_D1.inc';
$if not EXIST '../data/DEF_D1.inc' $INCLUDE '../../base/data/DEF_D1.inc';
%semislash%;

SET DEF_U1(DEF)   "Upwards steps in elastic el. demand, relative data format" %semislash%
$if     EXIST '../data/DEF_U1.inc' $INCLUDE      '../data/DEF_U1.inc';
$if not EXIST '../data/DEF_U1.inc' $INCLUDE '../../base/data/DEF_U1.inc';
%semislash%;

SET DEF_D2(DEF)   "Downwards steps in elastic el. demand, absolute Money and MW-incremental data format"%semislash%
$if     EXIST '../data/DEF_D2.inc' $INCLUDE      '../data/DEF_D2.inc';
$if not EXIST '../data/DEF_D2.inc' $INCLUDE '../../base/data/DEF_D2.inc';
%semislash%;

SET DEF_U2(DEF)   "Upwards steps in elastic el. demand, absolute Money and MW-incremental data format" %semislash%
$if     EXIST '../data/DEF_U2.inc' $INCLUDE      '../data/DEF_U2.inc';
$if not EXIST '../data/DEF_U2.inc' $INCLUDE '../../base/data/DEF_U2.inc';
%semislash%;

SET DEF_D3(DEF)   "Downwards steps in elastic el. demand, absolute Money and fraction of nominal demand data format" %semislash%
$if     EXIST '../data/DEF_D3.inc' $INCLUDE      '../data/DEF_D3.inc';
$if not EXIST '../data/DEF_D3.inc' $INCLUDE '../../base/data/DEF_D3.inc';
%semislash%;

SET DEF_U3(DEF)   "Upwards steps in elastic el. demand, absolute Money and fraction of nominal demand data format" %semislash%
$if     EXIST '../data/DEF_U3.inc' $INCLUDE      '../data/DEF_U3.inc';
$if not EXIST '../data/DEF_U3.inc' $INCLUDE '../../base/data/DEF_U3.inc';
%semislash%;

PARAMETER DEF_STEPS(RRR,DEUSER,SSS,TTT,DF_QP,DEF)         "Elastic electricity demands"   %semislash%
$if     EXIST '../data/DEF_STEPS.inc' $INCLUDE      '../data/DEF_STEPS.inc';
$if not EXIST '../data/DEF_STEPS.inc' $INCLUDE '../../base/data/DEF_STEPS.inc';
%semislash%;

SET DHF  "Steps in elastic heat demand" %semislash%
$if     EXIST '../data/DHF.inc' $INCLUDE      '../data/DHF.inc';
$if not EXIST '../data/DHF.inc' $INCLUDE '../../base/data/DHF.inc';
%semislash%;

SET DHF_D1(DHF)    "Downwards steps in elastic heat demand, relative data format" %semislash%
$if     EXIST '../data/DHF_D1.inc' $INCLUDE      '../data/DHF_D1.inc';
$if not EXIST '../data/DHF_D1.inc' $INCLUDE '../../base/data/DHF_D1.inc';
%semislash%;

SET DHF_U1(DHF)    "Upwards steps in elastic heat demand, relative data format" %semislash%
$if     EXIST '../data/DHF_U1.inc' $INCLUDE      '../data/DHF_U1.inc';
$if not EXIST '../data/DHF_U1.inc' $INCLUDE '../../base/data/DHF_U1.inc';
%semislash%;

SET DHF_D2(DHF)    "Downwards steps in elastic heat demand, absolute Money and MW-incremental data format" %semislash%
$if     EXIST '../data/DHF_D2.inc' $INCLUDE      '../data/DHF_D2.inc';
$if not EXIST '../data/DHF_D2.inc' $INCLUDE '../../base/data/DHF_D2.inc';
%semislash%;

SET DHF_U2(DHF)    "Upwards steps in elastic heat demand, absolute Money and MW-incremental data format" %semislash%
$if     EXIST '../data/DHF_U2.inc' $INCLUDE      '../data/DHF_U2.inc';
$if not EXIST '../data/DHF_U2.inc' $INCLUDE '../../base/data/DHF_U2.inc';
%semislash%;

SET DHF_D3(DHF)    "Downwards steps in elastic heat demand, absolute Money and fraction of nominal demand data format" %semislash%
$if     EXIST '../data/DHF_D3.inc' $INCLUDE      '../data/DHF_D3.inc';
$if not EXIST '../data/DHF_D3.inc' $INCLUDE '../../base/data/DHF_D3.inc';
%semislash%;

SET DHF_U3(DHF)    "Upwards steps in elastic heat demand, absolute Money and fraction of nominal demand data format" %semislash%
$if     EXIST '../data/DHF_U3.inc' $INCLUDE      '../data/DHF_U3.inc';
$if not EXIST '../data/DHF_U3.inc' $INCLUDE '../../base/data/DHF_U3.inc';
%semislash%;

PARAMETER DHF_STEPS(AAA,DHUSER,SSS,TTT,DF_QP,DHF)         "Elastic heat demands"   %semislash%
$if     EXIST '../data/DHF_STEPS.inc' $INCLUDE      '../data/DHF_STEPS.inc';
$if not EXIST '../data/DHF_STEPS.inc' $INCLUDE '../../base/data/DHF_STEPS.inc';
%semislash%;
* ------------------------------------------------------------------------------
$label dflexquantend

$ifi %DEFPCALIB%==yes PARAMETER DEFP_CALIB(RRR,SSS,TTT)                  "Calibrate the price side of electricity demand"   %semislash%
$ifi %DEFPCALIB%==yes $if     EXIST '../data/DEFP_CALIB.inc' $INCLUDE      '../data/DEFP_CALIB.inc';
$ifi %DEFPCALIB%==yes $if not EXIST '../data/DEFP_CALIB.inc' $INCLUDE '../../base/data/DEFP_CALIB.inc';
$ifi %DEFPCALIB%==yes %semislash%;

$ifi %DHFPCALIB%==yes PARAMETER DHFP_CALIB(AAA,SSS,TTT)                  "Calibrate the price side of heat demand"   %semislash%
$ifi %DHFPCALIB%==yes $if     EXIST '../data/DHFP_CALIB.inc' $INCLUDE      '../data/DHFP_CALIB.inc';
$ifi %DHFPCALIB%==yes $if not EXIST '../data/DHFP_CALIB.inc' $INCLUDE '../../base/data/DHFP_CALIB.inc';
$ifi %DHFPCALIB%==yes %semislash%;

*-------------------------------------------------------------------------------
*--- End: Any declarations and definitions of sets, aliases and acronyms for addon
*-------------------------------------------------------------------------------



PARAMETER GKFX(YYY,AAA,GGG)    "Capacity of existing generation technologies (MW)" %semislash%
$if     EXIST '../data/GKFX.inc' $INCLUDE      '../data/GKFX.inc';
$if not EXIST '../data/GKFX.inc' $INCLUDE '../../base/data/GKFX.inc';
%semislash%;


PARAMETER FMAXINVEST(CCC,FFF)   "Maximum investment (MW) by fuel type for each year simulated"    %semislash%
$if     EXIST '../data/FMAXINVEST.inc' $INCLUDE      '../data/FMAXINVEST.inc';
$if not EXIST '../data/FMAXINVEST.inc' $INCLUDE '../../base/data/FMAXINVEST.inc';
%semislash%;

/*  todo
PARAMETER FMAXINVESTNA(YYY,FFF)   "Maximum investment (MW) by fuel type for each year simulated(aggregated countries)"    %semislash%
$if     EXIST '../data/FMAXINVESTNA.inc' $INCLUDE      '../data/FMAXINVESTNA.inc';
$if not EXIST '../data/FMAXINVESTNA.inc' $INCLUDE '../../base/data/FMAXINVESTNA.inc';
%semislash%;   */   FMAXINVESTNA(YYY,FFF) = 0;

/*  todo
PARAMETER GROWTHCAPCG(C,GGG)    "Maximum model generated capacity increase (MW) from one year to the next"   %semislash%
$if     EXIST '../data/GROWTHCAPCG.inc' $INCLUDE         '../data/GROWTHCAPCG.inc';
$if not EXIST '../data/GROWTHCAPCG.inc' $INCLUDE '../../base/data/GROWTHCAPCG.inc';
%semislash%;   */   GROWTHCAPCG(C,GGG)  = INF;

PARAMETER DISLOSS_E(RRR)    "Loss in electricity distribution (fraction)"   %semislash%
$if     EXIST '../data/DISLOSS_E.inc' $INCLUDE      '../data/DISLOSS_E.inc';
$if not EXIST '../data/DISLOSS_E.inc' $INCLUDE '../../base/data/DISLOSS_E.inc';
%semislash%;

PARAMETER DISLOSS_H(AAA)    "Loss in heat distribution (fraction)"  %semislash%
$if     EXIST '../data/DISLOSS_H.inc' $INCLUDE      '../data/DISLOSS_H.inc';
$if not EXIST '../data/DISLOSS_H.inc' $INCLUDE '../../base/data/DISLOSS_H.inc';
%semislash%;

PARAMETER DISCOST_E(RRR)    "Cost of electricity distribution (Money/MWh)"  %semislash%
$if     EXIST '../data/DISCOST_E.inc' $INCLUDE      '../data/DISCOST_E.inc';
$if not EXIST '../data/DISCOST_E.inc' $INCLUDE '../../base/data/DISCOST_E.inc';
%semislash%;

PARAMETER DISCOST_H(AAA)    "Cost of heat distribution (Money/MWh)"     %semislash%
$if     EXIST '../data/DISCOST_H.inc' $INCLUDE      '../data/DISCOST_H.inc';
$if not EXIST '../data/DISCOST_H.inc' $INCLUDE '../../base/data/DISCOST_H.inc';
%semislash%;

PARAMETER FKPOT(CCCRRRAAA,FFF)    "Fuel potential restricted by geography (MW)"   %semislash%
$if     EXIST '../data/FKPOT.inc' $INCLUDE      '../data/FKPOT.inc';
$if not EXIST '../data/FKPOT.inc' $INCLUDE '../../base/data/FKPOT.inc';
%semislash%;

PARAMETER TECHGROUPKPOT(CCCRRRAAA,TECH_GROUP)    "Technology group capacity restriction by geography (MW)"   %semislash%
$if     EXIST '../data/TECHGROUPKPOT.inc' $INCLUDE      '../data/TECHGROUPKPOT.inc';
$if not EXIST '../data/TECHGROUPKPOT.inc' $INCLUDE '../../base/data/TECHGROUPKPOT.inc';
%semislash%;

PARAMETER SUBTECHGROUPKPOT(CCCRRRAAA,TECH_GROUP,SUBTECH_GROUP)    "Subtechnology group capacity restriction by geography (MW)"   %semislash%
$if     EXIST '../data/SUBTECHGROUPKPOT.inc' $INCLUDE      '../data/SUBTECHGROUPKPOT.inc';
$if not EXIST '../data/SUBTECHGROUPKPOT.inc' $INCLUDE '../../base/data/SUBTECHGROUPKPOT.inc';
%semislash%;

/* Todo
PARAMETER FKMIN(YYY,CCCRRRAAA,FFF)    "Capacity restricted by geography (MW)"   %semislash%
$if     EXIST '../data/FKMIN.inc' $INCLUDE      '../data/FKMIN.inc';
$if not EXIST '../data/FKMIN.inc' $INCLUDE '../../base/data/FKMIN.inc';
%semislash%;  */     FKMIN(YYY,CCCRRRAAA,FFF)=0;

/*
PARAMETER FKMAX(YYY,CCCRRRAAA,FFF)    "Capacity by geography (MW)"   %semislash%
$if     EXIST '../data/FKMAX.inc' $INCLUDE      '../data/FKMAX.inc';
$if not EXIST '../data/FKPOT.inc' $INCLUDE '../../base/data/FKMAX.inc';
%semislash%;*/   FKMAX(YYY,CCCRRRAAA,FFF)=0;

/*
PARAMETER FKEQ(YYY,CCCRRRAAA,FFF)    "Capacity by geography (MW)"   %semislash%
$if     EXIST '../data/FKEQ.inc' $INCLUDE      '../data/FKEQ.inc';
$if not EXIST '../data/FKEQ.inc' $INCLUDE '../../base/data/FKEQ.inc';
%semislash%; */    FKEQ(YYY,CCCRRRAAA,FFF)=0;

/*
PARAMETER FKMINNA(YYY,FFF)    "Capacity restricted by geography (MW)"   %semislash%
$if     EXIST '../data/FKMINNA.inc' $INCLUDE      '../data/FKMINNA.inc';
$if not EXIST '../data/FKMINNA.inc' $INCLUDE '../../base/data/FKMINNA.inc';
%semislash%; */ FKMINNA(YYY,FFF)=0;

/*PARAMETER FKMAXNA(YYY,FFF)    "Capacity restricted by geography (MW)"   %semislash%
$if     EXIST '../data/FKMAXNA.inc' $INCLUDE      '../data/FKMAXNA.inc';
$if not EXIST '../data/FKPOT.inc' $INCLUDE '../../base/data/FKMAXNA.inc';
%semislash%;*/ FKMAXNA(YYY,FFF) =0;

/*
PARAMETER FKEQNA(YYY,FFF)    "Capacity restricted by geography (MW)"   %semislash%
$if     EXIST '../data/FKEQNA.inc' $INCLUDE      '../data/FKEQNA.inc';
$if not EXIST '../data/FKEQNA.inc' $INCLUDE '../../base/data/FKEQNA.inc';
%semislash%; */  FKEQNA(YYY,FFF)=0;

PARAMETER FGEMIN(CCCRRRAAA,FFF)    "Minimum electricity generation by fuel (MWh)"  %semislash%
$if     EXIST '../data/FGEMIN.inc' $INCLUDE      '../data/FGEMIN.inc';
$if not EXIST '../data/FGEMIN.inc' $INCLUDE '../../base/data/FGEMIN.inc';
%semislash%;

PARAMETER FGEMAX(CCCRRRAAA,FFF)     "Maximum electricity generation by fuel (MWh)"   %semislash%
$if     EXIST '../data/FGEMAX.inc' $INCLUDE      '../data/FGEMAX.inc';
$if not EXIST '../data/FGEMAX.inc' $INCLUDE '../../base/data/FGEMAX.inc';
%semislash%;

$ifi %GMINF_DOL%==CCCRRRAAA_FFF      PARAMETER GMINF(CCCRRRAAA,FFF)             'Minimum fuel use (GJ) per year' %semislash%
$ifi %GMINF_DOL%==YYY_CCCRRRAAA_FFF  PARAMETER GMINF(YYY,CCCRRRAAA,FFF)         'Minimum fuel use (GJ) per year' %semislash%
$if     EXIST '../data/GMINF.inc' $INCLUDE      '../data/GMINF.inc';
$if not EXIST '../data/GMINF.inc' $INCLUDE '../../base/data/GMINF.inc';
%semislash%;

$ifi %GMAXF_DOL%==CCCRRRAAA_FFF      PARAMETER GMAXF(CCCRRRAAA,FFF)             'Maximum fuel use (GJ) per year' %semislash%
$ifi %GMAXF_DOL%==YYY_CCCRRRAAA_FFF  PARAMETER GMAXF(YYY,CCCRRRAAA,FFF)         'Maximum fuel use (GJ) per year' %semislash%
$if     EXIST '../data/GMAXF.inc' $INCLUDE      '../data/GMAXF.inc';
$if not EXIST '../data/GMAXF.inc' $INCLUDE '../../base/data/GMAXF.inc';
%semislash%;

$ifi %GEQF_DOL%==CCCRRRAAA_FFF       PARAMETER GEQF(CCCRRRAAA,FFF)              'Required fuel use (GJ) per year' %semislash%
$ifi %GEQF_DOL%== YYY_CCCRRRAAA_FFF  PARAMETER GEQF(YYY,CCCRRRAAA,FFF)          'Required fuel use (GJ) per year' %semislash%
$if     EXIST '../data/GEQF.inc' $INCLUDE      '../data/GEQF.inc';
$if not EXIST '../data/GEQF.inc' $INCLUDE '../../base/data/GEQF.inc';
%semislash%;

PARAMETER GMAXFS(YYY,CCCRRRAAA,FFF,SSS)         'Maximum fuel use (GJ) per year and season' %semislash%
$if     EXIST '../data/GMAXFS.inc' $INCLUDE      '../data/GMAXFS.inc';
$if not EXIST '../data/GMAXFS.inc' $INCLUDE '../../base/data/GMAXFS.inc';
%semislash%;

* Maximum capacity at new technologies. Presently not implemented.
*PARAMETER GKNMAX(YYY,AAA,GGG)   "Maximum capacity at new technologies (MW)"  %semislash%
*$if     EXIST '../data/GKNMAX.inc' $INCLUDE      '../data/GKNMAX.inc';
*$if not EXIST '../data/GKNMAX.inc' $INCLUDE '../../base/data/GKNMAX.inc';
*%semislash%;


PARAMETER WTRRSFLH(AAA)    "Full load hours for hydro reservoir plants (hours)"  %semislash%
$if     EXIST '../data/WTRRSFLH.inc' $INCLUDE      '../data/WTRRSFLH.inc';
$if not EXIST '../data/WTRRSFLH.inc' $INCLUDE '../../base/data/WTRRSFLH.inc';
%semislash%;

PARAMETER WTRRRFLH(AAA)    "Full load hours for hydro run-of-river plants (hours)"  %semislash%
$if     EXIST '../data/WTRRRFLH.inc' $INCLUDE      '../data/WTRRRFLH.inc';
$if not EXIST '../data/WTRRRFLH.inc' $INCLUDE '../../base/data/WTRRRFLH.inc';
%semislash%;

$ifi %WNDFLH_DOL%==AAA               PARAMETER WNDFLH(AAA)         "Full load hours for wind power (hours)"  %semislash%
$ifi %WNDFLH_DOL%==AAA_GGG           PARAMETER WNDFLH(AAA,GGG)     "Full load hours for wind power (hours)"  %semislash%
$if     EXIST '../data/WNDFLH.inc' $INCLUDE      '../data/WNDFLH.inc';
$if not EXIST '../data/WNDFLH.inc' $INCLUDE '../../base/data/WNDFLH.inc';
%semislash%;

$ifi %SOLEFLH_DOL%==AAA              PARAMETER SOLEFLH(AAA)        "Full load hours for solar power (hours)"  %semislash%
$ifi %SOLEFLH_DOL%==AAA_GGG          PARAMETER SOLEFLH(AAA,GGG)    "Full load hours for solar power (hours)"  %semislash%
$if     EXIST '../data/SOLEFLH.inc' $INCLUDE      '../data/SOLEFLH.inc';
$if not EXIST '../data/SOLEFLH.inc' $INCLUDE '../../base/data/SOLEFLH.inc';
%semislash%;


$ifi %SOLHFLH_DOL%==AAA       PARAMETER SOLHFLH(AAA)        "Full load hours for solar power (hours)"  %semislash%
$ifi %SOLHFLH_DOL%==AAA_GGG   PARAMETER SOLHFLH(AAA,GGG)    "Full load hours for solar power (hours)"  %semislash%
$if     EXIST '../data/SOLHFLH.inc' $INCLUDE      '../data/SOLHFLH.inc';
$if not EXIST '../data/SOLHFLH.inc' $INCLUDE '../../base/data/SOLHFLH.inc';
%semislash%;

$ifi %GWAVE_DOL%==AAA          PARAMETER WAVEFLH(AAA)        "Full load hours for wave power (hours)"  %semislash%
$ifi %GWAVE_DOL%==AAA_GGG      PARAMETER WAVEFLH(AAA,GGG)    "Full load hours for wave power (hours)"  %semislash%
$if     EXIST '../data/WAVEFLH.inc' $INCLUDE      '../data/WAVEFLH.inc';
$if not EXIST '../data/WAVEFLH.inc' $INCLUDE '../../base/data/WAVEFLH.inc';
%semislash%;

PARAMETER HYRSDATA(AAA,HYRSDATASET,SSS)    "Data for hydro with storage"  %semislash%
$if     EXIST '../data/HYRSDATA.inc' $INCLUDE         '../data/HYRSDATA.inc';
$if not EXIST '../data/HYRSDATA.inc' $INCLUDE '../../base/data/HYRSDATA.inc';
%semislash%;

SCALAR DISCOUNTRATE "Discount rate by country (fraction)" !! Hans "by Country"?
$if     EXIST '../data/DISCOUNTRATE.inc' $INCLUDE         '../data/DISCOUNTRATE.inc';
$if not EXIST '../data/DISCOUNTRATE.inc' $INCLUDE '../../base/data/DISCOUNTRATE.inc';
%semislash%;

SCALAR    LIFETIME_X               "Lifetime of transmission lines (years)";   %semislash%
$if     EXIST '../data/LIFETIME_X.inc' $INCLUDE         '../data/LIFETIME_X.inc';
$if not EXIST '../data/LIFETIME_X.inc' $INCLUDE '../../base/data/LIFETIME_X.inc';
%semislash%;

PARAMETER ANNUITYCG(CCC,GGG)       "Transforms investment in technologies into annual payment (fraction)";      %semislash%
$if     EXIST '../data/ANNUITYCG.inc' $INCLUDE         '../data/ANNUITYCG.inc';
$if not EXIST '../data/ANNUITYCG.inc' $INCLUDE '../../base/data/ANNUITYCG.inc';
%semislash%;

PARAMETER ANNUITYCX(CCC)                 "Transforms investment in transmission lines into annual payment (fraction)";       %semislash%
$if     EXIST '../data/ANNUITYCX.inc' $INCLUDE         '../data/ANNUITYCX.inc';
$if not EXIST '../data/ANNUITYCX.inc' $INCLUDE '../../base/data/ANNUITYCX.inc';
%semislash%;

PARAMETER GINVCOST(AAA,GGG)    "Investment cost for new technology (MMoney/MW)"  %semislash%
$if     EXIST '../data/GINVCOST.inc' $INCLUDE         '../data/GINVCOST.inc';
$if not EXIST '../data/GINVCOST.inc' $INCLUDE '../../base/data/GINVCOST.inc';
%semislash%;

PARAMETER GOMVCOSTO(AAA,GGG)    "Variable operating and maintenance costs relative to the output(Money/MWh)"  %semislash%
$if     EXIST '../data/GOMVCOSTO.inc' $INCLUDE         '../data/GOMVCOSTO.inc';
$if not EXIST '../data/GOMVCOSTO.inc' $INCLUDE '../../base/data/GOMVCOSTO.inc';
%semislash%;

PARAMETER GOMVCOSTIN(AAA,GGG)    "Variable operating and maintenance costs relative to the input(Money/MWh)"  %semislash%
$if     EXIST '../data/GOMVCOSTIN.inc' $INCLUDE         '../data/GOMVCOSTIN.inc';
$if not EXIST '../data/GOMVCOSTIN.inc' $INCLUDE '../../base/data/GOMVCOSTIN.inc';
%semislash%;

PARAMETER GOMFCOST(AAA,GGG)    "Annual fixed operating costs (kMoney/MW)"  %semislash%
$if     EXIST '../data/GOMFCOST.inc' $INCLUDE         '../data/GOMFCOST.inc';
$if not EXIST '../data/GOMFCOST.inc' $INCLUDE '../../base/data/GOMFCOST.inc';
%semislash%;

PARAMETER GEFFRATE(AAA,GGG)    "Fuel efficiency rating (strictly positive, typically close to 1; default/1/, use eps for 0)"  %semislash%
$if     EXIST '../data/GEFFRATE.inc' $INCLUDE         '../data/GEFFRATE.inc';
$if not EXIST '../data/GEFFRATE.inc' $INCLUDE '../../base/data/GEFFRATE.inc';
%semislash%;

PARAMETER DEFP_BASE(RRR)    "Nominal annual average consumer electricity price (Money/MWh)"  %semislash%
$if     EXIST '../data/DEFP_BASE.inc' $INCLUDE         '../data/DEFP_BASE.inc';
$if not EXIST '../data/DEFP_BASE.inc' $INCLUDE '../../base/data/DEFP_BASE.inc';
%semislash%;

PARAMETER DHFP_BASE(AAA)    "Nominal annual average consumer heat price (Money/MWh)"  %semislash%
$if     EXIST '../data/DHFP_BASE.inc' $INCLUDE         '../data/DHFP_BASE.inc';
$if not EXIST '../data/DHFP_BASE.inc' $INCLUDE '../../base/data/DHFP_BASE.inc';
%semislash%;

PARAMETER GKF_LO(FFF)    "Minimum capacity usage on new capacity for fuel (%)"  %semislash%
$if     EXIST '../data/GKF_LO.inc' $INCLUDE         '../data/GKF_LO.inc';
$if not EXIST '../data/GKF_LO.inc' $INCLUDE '../../base/data/GKF_LO.inc';
%semislash%;

*-------------------------------------------------------------------------------
*---- End: Geographically specific values --------------------------------------
*-------------------------------------------------------------------------------


*-------------------------------------------------------------------------------
*---- Annual electricity demand : ---------------------------------------------
*-------------------------------------------------------------------------------
PARAMETER DE(YYY,RRR,DEUSER)    "Annual electricity consumption (MWh)" %semislash%
$if     EXIST '../data/DE.inc' $INCLUDE         '../data/DE.inc';
$if not EXIST '../data/DE.inc' $INCLUDE '../../base/data/DE.inc';
%semislash%;


*-------------------------------------------------------------------------------
*---- Annual heat demand: -----------------------------------------------------
*-------------------------------------------------------------------------------
PARAMETER DH(YYY,AAA,DHUSER)    "Annual heat consumption (MWh)"  %semislash%
$if     EXIST '../data/DH.inc' $INCLUDE         '../data/DH.inc';
$if not EXIST '../data/DH.inc' $INCLUDE '../../base/data/DH.inc';
%semislash%;



*-------------------------------------------------------------------------------
*---- Transmission data: ------------------------------------------------------
*-------------------------------------------------------------------------------
PARAMETER XINVCOST(YYY,IRRRE,IRRRI)  "Investment cost in new transmission capacity, default: INF or 0: no investment, EPS or positive: possible with stated cost (Money/MW)"    %semislash%
$if     EXIST '../data/XINVCOST.inc' $INCLUDE         '../data/XINVCOST.inc';
$if not EXIST '../data/XINVCOST.inc' $INCLUDE '../../base/data/XINVCOST.inc';
%semislash%;

PARAMETER XKFX(YYY,IRRRE,IRRRI)  "Capacity of exogenously given transmission capacity between regions (MW)"   %semislash%
$if     EXIST '../data/XKFX.inc' $INCLUDE         '../data/XKFX.inc';
$if not EXIST '../data/XKFX.inc' $INCLUDE '../../base/data/XKFX.inc';
%semislash%;

PARAMETER XCOST(IRRRE,IRRRI)      "Transmission cost between regions (Money/MWh)"   %semislash%
$if     EXIST '../data/XCOST.inc' $INCLUDE         '../data/XCOST.inc';
$if not EXIST '../data/XCOST.inc' $INCLUDE '../../base/data/XCOST.inc';
%semislash%;

PARAMETER XLOSS(IRRRE,IRRRI)      "Transmission loss between regions (fraction)"  %semislash%
$if     EXIST '../data/XLOSS.inc' $INCLUDE         '../data/XLOSS.inc';
$if not EXIST '../data/XLOSS.inc' $INCLUDE '../../base/data/XLOSS.inc';
%semislash%;

$ifi %XKRATE_DOL%==IRRRE_IRRRI          PARAMETER XKRATE(IRRRE,IRRRI)         "Transmission capacity rating (share; non-negative, typically close to 1; default/1/, use eps for 0)";
$ifi %XKRATE_DOL%==IRRRE_IRRRI_SSS      PARAMETER XKRATE(IRRRE,IRRRI,SSS)     "Transmission capacity rating (share; non-negative, typically close to 1; default/1/, use eps for 0)";
$ifi %XKRATE_DOL%==IRRRE_IRRRI_SSS_TTT  PARAMETER XKRATE(IRRRE,IRRRI,SSS,TTT) "Transmission capacity rating (share; non-negative, typically close to 1; default/1/, use eps for 0)";
$if     EXIST '../data/XKRATE.inc' $INCLUDE         '../data/XKRATE.inc';
$if not EXIST '../data/XKRATE.inc' $INCLUDE '../../base/data/XKRATE.inc';
%semislash%;

PARAMETER XMAXINV(IRRRE,IRRRI)   "Max investment in transmission capacity between two regions for each simulated year (each 5th year)"  %semislash%
$if     EXIST '../data/XMAXINV.inc' $INCLUDE         '../data/XMAXINV.inc';
$if not EXIST '../data/XMAXINV.inc' $INCLUDE '../../base/data/XMAXINV.inc';
%semislash%;


*-------------------------------------------------------------------------------
* Annually specified fuel prices: ---------------------------------------------
*-------------------------------------------------------------------------------

PARAMETER FUELPRICE(YYY,AAA,FFF)                   "Fuel prices (Money/GJ)"   %semislash%
$if     EXIST '../data/FUELPRICE.inc' $INCLUDE      '../data/FUELPRICE.inc';
$if not EXIST '../data/FUELPRICE.inc' $INCLUDE '../../base/data/FUELPRICE.inc';
%semislash%;


*-------------------------------------------------------------------------------
*---- Emission policy data: ---------------------------------------------------
*-------------------------------------------------------------------------------

PARAMETER M_POL(YYY,MPOLSET,CCC)    "Emission policy data"   %semislash%
$if     EXIST '../data/M_POL.inc' $INCLUDE         '../data/M_POL.inc';
$if not EXIST '../data/M_POL.inc' $INCLUDE '../../base/data/M_POL.inc';
%semislash%;

/*
PARAMETER M_POLNA(YYY,MPOLSET)    "Emission policy data"   %semislash%
$if     EXIST '../data/M_POLNA.inc' $INCLUDE         '../data/M_POLNA.inc';
$if not EXIST '../data/M_POLNA.inc' $INCLUDE '../../base/data/M_POLNA.inc';
%semislash%;  */    M_POLNA(YYY,MPOLSET)=0;

*-------------------------------------------------------------------------------
*---- Seasonal and daily variations: ------------------------------------------
*-------------------------------------------------------------------------------


* DISSE FILER INDHOLDER NaSTEN ALLESAMMEN KODE, CONDITIONALS, ETC! Skal revideres!

PARAMETER WEIGHT_S(SSS)                            "Weight (relative length) of each season"    %semislash%
$if     EXIST '../data/WEIGHT_S.inc' $INCLUDE      '../data/WEIGHT_S.inc';
$if not EXIST '../data/WEIGHT_S.inc' $INCLUDE '../../base/data/WEIGHT_S.inc';
%semislash%;

PARAMETER WEIGHT_T(TTT)                            "Weight (relative length) of each time period"   %semislash%
$if     EXIST '../data/WEIGHT_T.inc' $INCLUDE         '../data/WEIGHT_T.inc';
$if not EXIST '../data/WEIGHT_T.inc' $INCLUDE '../../base/data/WEIGHT_T.inc';
%semislash%;

PARAMETER CHRONOHOUR(S,T) 'Meaning/size of each time step in each season (1 means 1 hour)'  %semislash%
$if     EXIST '../data/CHRONOHOUR.inc' $INCLUDE         '../data/CHRONOHOUR.inc';
$if not EXIST '../data/CHRONOHOUR.inc' $INCLUDE '../../base/data/CHRONOHOUR.inc';
%semislash%;

PARAMETER GKRATE(AAA,GGG,SSS)                       "Capacity rating (non-negative, typically close to 1; default/1/, use eps for 0)" %semislash%
$if     EXIST '../data/GKRATE.inc' $INCLUDE         '../data/GKRATE.inc';
$if not EXIST '../data/GKRATE.inc' $INCLUDE '../../base/data/GKRATE.inc';
%semislash%;

PARAMETER DE_VAR_T(RRR,DEUSER,SSS,TTT)                    "Variation in electricity demand"   %semislash%
$if     EXIST '../data/DE_VAR_T.inc' $INCLUDE      '../data/DE_VAR_T.inc';
$if not EXIST '../data/DE_VAR_T.inc' $INCLUDE '../../base/data/DE_VAR_T.inc';
%semislash%;

PARAMETER DH_VAR_T(AAA,DHUSER,SSS,TTT)                    "Variation in heat demand"   %semislash%
$if     EXIST '../data/DH_VAR_T.inc' $INCLUDE      '../data/DH_VAR_T.inc';
$if not EXIST '../data/DH_VAR_T.inc' $INCLUDE '../../base/data/DH_VAR_T.inc';
%semislash%;

PARAMETER WTRRSVAR_S(AAA,SSS)                      "Variation of the water inflow to reservoirs"   %semislash%
$if     EXIST '../data/WTRRSVAR_S.inc' $INCLUDE      '../data/WTRRSVAR_S.inc';
$if not EXIST '../data/WTRRSVAR_S.inc' $INCLUDE '../../base/data/WTRRSVAR_S.inc';
%semislash%;

PARAMETER WTRRRVAR_T(AAA,SSS,TTT)                  "Variation of generation of hydro run-of-river"    %semislash%
$if     EXIST '../data/WTRRRVAR_T.inc' $INCLUDE      '../data/WTRRRVAR_T.inc';
$if not EXIST '../data/WTRRRVAR_T.inc' $INCLUDE '../../base/data/WTRRRVAR_T.inc';
%semislash%;

PARAMETER WND_VAR_T(AAA,SSS,TTT)                   "Variation of the wind generation"    %semislash%
$if     EXIST '../data/WND_VAR_T.inc' $INCLUDE      '../data/WND_VAR_T.inc';
$if not EXIST '../data/WND_VAR_T.inc' $INCLUDE '../../base/data/WND_VAR_T.inc';
%semislash%;

PARAMETER SOLE_VAR_T(AAA,SSS,TTT)                  "Variation of the solarE generation"   %semislash%
$if     EXIST '../data/SOLE_VAR_T.inc' $INCLUDE      '../data/SOLE_VAR_T.inc';
$if not EXIST '../data/SOLE_VAR_T.inc' $INCLUDE '../../base/data/SOLE_VAR_T.inc';
%semislash%;

PARAMETER SOLH_VAR_T(AAA,SSS,TTT)                  "Variation of the solarH generation"   %semislash%
$if     EXIST '../data/SOLH_VAR_T.inc' $INCLUDE      '../data/SOLH_VAR_T.inc';
$if not EXIST '../data/SOLH_VAR_T.inc' $INCLUDE '../../base/data/SOLH_VAR_T.inc';
%semislash%;

PARAMETER WAVE_VAR_T(AAA,SSS,TTT)                  "Variation of the solarH generation"   %semislash%
$if     EXIST '../data/WAVE_VAR_T.inc' $INCLUDE      '../data/WAVE_VAR_T.inc';
$if not EXIST '../data/WAVE_VAR_T.inc' $INCLUDE '../../base/data/WAVE_VAR_T.inc';
%semislash%;

PARAMETER X3FX(YYY,RRR)                "Annual net electricity export to third regions (MWh)";  %semislash%
$if     EXIST '../data/WAVE_VAR_T.inc' $INCLUDE      '../data/X3FX.inc';
$if not EXIST '../data/WAVE_VAR_T.inc' $INCLUDE '../../base/data/X3FX.inc';
%semislash%;

PARAMETER X3FX_VAR_T(RRR,SSS,TTT)                  "Variation in fixed exchange with 3. region"   %semislash%
$if     EXIST '../data/X3FX_VAR_T.inc' $INCLUDE      '../data/X3FX_VAR_T.inc';
$if not EXIST '../data/X3FX_VAR_T.inc' $INCLUDE '../../base/data/X3FX_VAR_T.inc';
%semislash%;

PARAMETER HYPPROFILS(AAA,SSS)                      "Hydro with storage seasonal price profile"   %semislash%
$if     EXIST '../data/HYPPROFILS.inc' $INCLUDE      '../data/HYPPROFILS.inc';
$if not EXIST '../data/HYPPROFILS.inc' $INCLUDE '../../base/data/HYPPROFILS.inc';
%semislash%;


$ifi %bb3%==yes WEIGHT_T(T)=1;


$ifi %YIELDREQUIREMENT%==yes  PARAMETER YIELDREQ(GGG)  "Differentiates yield requirements for different technologies"   %semislash%
$ifi %YIELDREQUIREMENT%==yes  $if     EXIST '../data/YIELDREQ.inc' $INCLUDE      '../data/YIELDREQ.inc';
$ifi %YIELDREQUIREMENT%==yes  $if not EXIST '../data/YIELDREQ.inc' $INCLUDE '../../base/data/YIELDREQ.inc';
$ifi %YIELDREQUIREMENT%==yes  %semislash%;


$ifi not %BB4%==yes $goto label_BB4_1
$ifi %BB4%==yes SET YMODEL "YMODEL is a set used to derive the years from Y in each Balbase4 model";
$ifi %BB4%==yes PARAMETER YMODELDELTA(YMODEL) "The number of years between two consequtive years in a BB4 model";
$if     EXIST '../data/YMODEL.inc' $INCLUDE         '../data/YMODEL.inc';
$if not EXIST '../data/YMODEL.inc' $INCLUDE '../../base/data/YMODEL.inc';
$if     EXIST '../data/YMODELDELTA.inc' $INCLUDE         '../data/YMODELDELTA.inc';
$if not EXIST '../data/YMODELDELTA.inc' $INCLUDE '../../base/data/YMODELDELTA.inc';
$label label_BB4_1


*-------------------------------------------------------------------------------
*---- Miscellaneous ------------------------------------------------------------
*-------------------------------------------------------------------------------

* SCALAR OMONEY specifies output currency name and its exchange rate to input currency.
* Example of declaration:  'SCALAR OMONEY "EUR07" / 1.389 /;'.
* Since the text string holding the output currency is part of the declaration,
* the declaration is not given here in Balmorel.gms but in the included file.
* (For this reason you can not here apply the 'Semislash-idea'.)
* It is advised to add a comment in the data file stating what the input currency is and to which year it refers.

$if     EXIST '../data/OMONEY.inc' $INCLUDE         '../data/OMONEY.inc';
$if not EXIST '../data/OMONEY.inc' $INCLUDE '../../base/data/OMONEY.inc';


SCALAR PENALTYQ  "Penalty on violation of equation"  %semislash%
$if     EXIST '../data/PENALTYQ.inc' $INCLUDE         '../data/PENALTYQ.inc';
$if not EXIST '../data/PENALTYQ.inc' $INCLUDE '../../base/data/PENALTYQ.inc';
%semislash%;

*-------------------------------------------------------------------------------
*----- Any declarations and definitions of parameters:
*-------------------------------------------------------------------------------
*$include "../../base/addons/_hooks/pardeclare.inc"
$include "../../base/addons/_hooks/pardefine.inc"


