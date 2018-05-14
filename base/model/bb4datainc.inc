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

SET CCCRRRAAA          'All geographical entities (CCC + RRR + AAA)' %semislash%
$if     EXIST '../data/CCCRRRAAA.inc' $INCLUDE         '../data/CCCRRRAAA.inc';
$if not EXIST '../data/CCCRRRAAA.inc' $INCLUDE '../../base/data/CCCRRRAAA.inc';
%semislash%;

SET CCC(CCCRRRAAA)       'All Countries' %semislash%
$if     EXIST '../data/CCC.inc' $INCLUDE         '../data/CCC.inc';
$if not EXIST '../data/CCC.inc' $INCLUDE '../../base/data/CCC.inc';
%semislash%;

SET RRR(CCCRRRAAA)       'All regions' %semislash%
$if     EXIST '../data/RRR.inc' $INCLUDE         '../data/RRR.inc';
$if not EXIST '../data/RRR.inc' $INCLUDE '../../base/data/RRR.inc';
%semislash%;

SET AAA(CCCRRRAAA)       'All areas' %semislash%
$if     EXIST '../data/AAA.inc' $INCLUDE         '../data/AAA.inc';
$if not EXIST '../data/AAA.inc' $INCLUDE '../../base/data/AAA.inc';
%semislash%;

SET CCCRRR(CCC,RRR)      'Regions in countries' %semislash%
$if     EXIST '../data/CCCRRR.inc' $INCLUDE      '../data/CCCRRR.inc';
$if not EXIST '../data/CCCRRR.inc' $INCLUDE '../../base/data/CCCRRR.inc';
%semislash%;

SET RRRAAA(RRR,AAA)      'Areas in regions' %semislash%
$if     EXIST '../data/RRRAAA.inc' $INCLUDE         '../data/RRRAAA.inc';
$if not EXIST '../data/RRRAAA.inc' $INCLUDE '../../base/data/RRRAAA.inc';
%semislash%;

SET C(CCC)    'Countries in the simulation'  %semislash%
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


SET YYY                'All years'  %semislash%
$if     EXIST '../data/YYY.inc' $INCLUDE      '../data/YYY.inc';
$if not EXIST '../data/YYY.inc' $INCLUDE '../../base/data/YYY.inc';
%semislash%;

SET SSS                'All seasons' %semislash%
$if     EXIST '../data/SSS.inc' $INCLUDE      '../data/SSS.inc';
$if not EXIST '../data/SSS.inc' $INCLUDE '../../base/data/SSS.inc';
%semislash%;

SET TTT                'All time periods' %semislash%
$if     EXIST '../data/TTT.inc' $INCLUDE      '../data/TTT.inc';
$if not EXIST '../data/TTT.inc' $INCLUDE '../../base/data/TTT.inc';
%semislash%;

SET DEUSER             'Electricity demand user groups. Set must include element RESE for holding demand not included in any other user group'  %semislash%
$if     EXIST '../data/DEUSER.inc' $INCLUDE         '../data/DEUSER.inc';
$if not EXIST '../data/DEUSER.inc' $INCLUDE '../../base/data/DEUSER.inc';
%semislash%;

SET DHUSER             'Heat demand user groups. Set must include element RESH for holding demand not included in any other user group'  %semislash%
$if     EXIST '../data/DEUSER.inc' $INCLUDE         '../data/DHUSER.inc';
$if not EXIST '../data/DEUSER.inc' $INCLUDE '../../base/data/DHUSER.inc';
%semislash%;

SET FFF                'Fuels'  %semislash%
$if     EXIST '../data/FFF.inc' $INCLUDE      '../data/FFF.inc';
$if not EXIST '../data/FFF.inc' $INCLUDE '../../base/data/FFF.inc';
%semislash%;

SET FDATASET           'Characteristics of fuels ' %semislash%
$if     EXIST '../data/FDATASET.inc' $INCLUDE      '../data/FDATASET.inc';
$if not EXIST '../data/FDATASET.inc' $INCLUDE '../../base/data/FDATASET.inc';
%semislash%;

PARAMETER FDATA(FFF,FDATASET)    'Fuel specific values'  %semislash%
$if     EXIST '../data/FDATA.inc' $INCLUDE      '../data/FDATA.inc';
$if not EXIST '../data/FDATA.inc' $INCLUDE '../../base/data/FDATA.inc';
%semislash%;

SET GGG                'All generation technologies'   %semislash%
$if     EXIST '../data/GGG.inc' $INCLUDE      '../data/GGG.inc';
$if not EXIST '../data/GGG.inc' $INCLUDE '../../base/data/GGG.inc';
%semislash%;

SET GDATASET           'Generation technology data' %semislash%
$if     EXIST '../data/GDATASET.inc' $INCLUDE      '../data/GDATASET.inc';
$if not EXIST '../data/GDATASET.inc' $INCLUDE '../../base/data/GDATASET.inc';
%semislash%;

SET G(GGG)    'Generation technologies in the simulation'  %semislash%
$if     EXIST '../data/G.inc' $INCLUDE         '../data/G.inc';
$if not EXIST '../data/G.inc' $INCLUDE '../../base/data/G.inc';
%semislash%;


*-------------------------------------------------------------------------------
*----- Any declarations and definitions of sets, aliases and acronyms for addon:
*-------------------------------------------------------------------------------

$include "../../base/addons/_hooks/acronyms.inc"
$include "../../base/addons/_hooks/setdeclare.inc"
$include "../../base/addons/_hooks/setdefine.inc"


* Addon AGKNDISC: discrete size investment in technologies:
$ifi %AGKNDISC%==yes $include  "../../base/addons/bb4/agkndisc/agkndiscdeclarations.inc";


* Duplication of sets for describing possible heat exchange between areas (option HEATTRANS).
$ifi %HEATTRANS%==yes ALIAS (AAA,IAAAE,IAAAI);
$ifi %HEATTRANS%==yes ALIAS (IA,IAE,IAI);


$ifi not %HYRSBB123%==none   $include "../../base/addons/hyrsbb123/hyrsbb123internals.inc";

*-------------------------------------------------------------------------------
* End: Any declarations and definitions of sets, aliases and acronyms for addon
*-------------------------------------------------------------------------------

PARAMETER GDATA(GGG,GDATASET)    'Technologies characteristics' %semislash%
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

PARAMETER HYRSMAXVOL_G(AAA,GGG) 'Reservoir capacity (MWh storage capacity / MW installed capacity)'  %semislash%
$if     EXIST '../data/HYRSMAXVOL_G.inc' $INCLUDE         '../data/HYRSMAXVOL_G.inc';
$if not EXIST '../data/HYRSMAXVOL_G.inc' $INCLUDE '../../base/data/HYRSMAXVOL_G.inc';
%semislash%;

SET HYRSDATASET  'Characteristics of hydro reservoirs' %semislash%
$if     EXIST '../data/HYRSDATASET.inc' $INCLUDE      '../data/HYRSDATASET.inc';
$if not EXIST '../data/HYRSDATASET.inc' $INCLUDE '../../base/data/HYRSDATASET.inc';
%semislash%;

SET DF_QP  'Quantity and price information for elastic demands' %semislash%
$if     EXIST '../data/DF_QP.inc' $INCLUDE      '../data/DF_QP.inc';
$if not EXIST '../data/DF_QP.inc' $INCLUDE '../../base/data/DF_QP.inc';
%semislash%;

SET MPOLSET  'Emission and other policy data'   %semislash%
$if     EXIST '../data/MPOLSET.inc' $INCLUDE      '../data/MPOLSET.inc';
$if not EXIST '../data/MPOLSET.inc' $INCLUDE '../../base/data/MPOLSET.inc';
%semislash%;

$onmulti
SET AGKN(AAA,GGG)   'Areas for possible location of new technologies'   %semislash%
$if     EXIST '../data/AGKN.inc' $INCLUDE         '../data/AGKN.inc';
$if not EXIST '../data/AGKN.inc' $INCLUDE '../../base/data/AGKN.inc';
%semislash%;

$offmulti
SET Y(YYY)    'Years in the simulation'   %semislash%
$if     EXIST '../data/Y.inc' $INCLUDE      '../data/Y.inc';
$if not EXIST '../data/Y.inc' $INCLUDE '../../base/data/Y.inc';
%semislash%;

SET S(SSS)    'Seasons in the simulation'   %semislash%
$if     EXIST '../data/S.inc' $INCLUDE      '../data/S.inc';
$if not EXIST '../data/S.inc' $INCLUDE '../../base/data/S.inc';
%semislash%;

SET T(TTT)    'Time periods within the season in the simulation'  %semislash%
$if     EXIST '../data/T.inc' $INCLUDE         '../data/T.inc';
$if not EXIST '../data/T.inc' $INCLUDE '../../base/data/T.inc';
%semislash%;

*SET DAYTYPE       'Types of days within the week, typically workdays/weekend' %semislash%
*$if     EXIST '../data/DAYTYPE.inc' $INCLUDE         '../data/DAYTYPE.inc';
*$if not EXIST '../data/DAYTYPE.inc' $INCLUDE '../../base/data/DAYTYPE.inc';
*%semislash%

SET TWORKDAY(TTT)   'Time segments, T, in workdays'  %semislash%
$if     EXIST '../data/TWORKDAY.inc' $INCLUDE         '../data/TWORKDAY.inc';
$if not EXIST '../data/TWORKDAY.inc' $INCLUDE '../../base/data/TWORKDAY.inc';
%semislash%

SET TWEEKEND(TTT)   'Time segments, T, in weekends'   %semislash%
$if     EXIST '../data/TWEEKEND.inc' $INCLUDE         '../data/TWEEKEND.inc';
$if not EXIST '../data/TWEEKEND.inc' $INCLUDE '../../base/data/TWEEKEND.inc';
%semislash%
                                      /* todos
SET ECONSET         'Set for econ'  %semislash%
$if     EXIST '../data/ECONSET.inc' $INCLUDE         '../data/ECONSET.inc';
$if not EXIST '../data/ECONSET.inc' $INCLUDE '../../base/data/ECONSET.inc';
%semislash%

SET ECONSETCATEGORY 'Set for econ'  %semislash%
$if     EXIST '../data/ECONSETCATEGORY.inc' $INCLUDE         '../data/ECONSETCATEGORY.inc';
$if not EXIST '../data/ECONSETCATEGORY.inc' $INCLUDE '../../base/data/ECONSETCATEGORY.inc';
%semislash%                            */




*-------------------------------------------------------------------------------
*----- Any declarations and definitions of sets, aliases and acronyms for addon:
*-------------------------------------------------------------------------------


$ifi not %X3V%==yes $goto X3V_label1

$if     EXIST '../data/X3VPLACE0.inc' $INCLUDE      '../data/X3VPLACE0.inc';
$if not EXIST '../data/X3VPLACE0.inc' $INCLUDE      '../../base/data/X3VPLACE0.inc';

$if     EXIST '../data/X3VPLACE.inc' $INCLUDE      '../data/X3VPLACE.inc';
$if not EXIST '../data/X3VPLACE.inc' $INCLUDE      '../../base/data/X3VPLACE.inc';

$if     EXIST '../data/X3VSTEP0.inc' $INCLUDE      '../data/X3VSTEP0.inc';
$if not EXIST '../data/X3VSTEP0.inc' $INCLUDE      '../../base/data/X3VSTEP0.inc';

$if     EXIST '../data/X3VSTEP.inc' $INCLUDE      '../data/X3VSTEP.inc';
$if not EXIST '../data/X3VSTEP.inc' $INCLUDE      '../../base/data/X3VSTEP.inc';

$if     EXIST '../data/X3VX.inc' $INCLUDE      '../data/X3VX.inc';
$if not EXIST '../data/X3VX.inc' $INCLUDE      '../../base/data/X3VX.inc';
*$ifi %X3V%==yes   $INCLUDE '../../base/addons/X3V/data/X3VSETS.inc';
$label X3V_label1


* Addon AGKNDISC: discrete size investment in technologies:
$ifi not %AGKNDISC%==yes  $goto label_AGKNDISC1

SET AGKNDISC_AG(AAA,GGG)   'Areas for possible location of discrete capacity investments in technologies' %semislash%
$if     EXIST '../data/AGKNDISCAG.inc' $INCLUDE         '../data/AGKNDISC_AG.inc';
$if not EXIST '../data/AGKNDISCAG.inc' $INCLUDE '../../base/data/AGKNDISC_AG.inc';
%semislash%

SET AGKNDISCSIZESET    'Set of possible sizes for discrete capacity investments in technologies' %semislash%
$if     EXIST '../data/AGKNDISCSIZESET.inc' $INCLUDE         '../data/AGKNDISCSIZESET.inc';
$if not EXIST '../data/AGKNDISCSIZESET.inc' $INCLUDE '../../base/data/AGKNDISCSIZESET.inc';
%semislash%

SET AGKNDISCDATASET    'Technology investment data types for discrete capacity size investments' %semislash%
$if     EXIST '../data/AGKNDISCDATASET.inc' $INCLUDE         '../data/AGKNDISCDATASET.inc';
$if not EXIST '../data/AGKNDISCDATASET.inc' $INCLUDE '../../base/data/AGKNDISCDATASET.inc';
%semislash%

PARAMETER AGKNDISCDATA(GGG,AGKNDISCSIZESET,AGKNDISCDATASET) 'Technology investment data for discrete capacity size investments' %semislash%
$if     EXIST '../data/AGKNDISCDATA.inc' $INCLUDE         '../data/AGKNDISCDATA.inc';
$if not EXIST '../data/AGKNDISCDATA.inc' $INCLUDE '../../base/data/AGKNDISCDATA.inc';
%semislash%

$label label_AGKNDISC1
* End: Addon AGKNDISC: discrete size investment in technologies.

$ifi not %dflexquant%==yes $goto dflexquantend
* ------------------------------------------------------------------------------
SET DEF  'Steps in elastic electricity demand'  %semislash%
$if     EXIST '../data/DEF.inc' $INCLUDE      '../data/DEF.inc';
$if not EXIST '../data/DEF.inc' $INCLUDE '../../base/data/DEF.inc';
%semislash%;

SET DEF_D1(DEF)   'Downwards steps in elastic el. demand, relative data format' %semislash%
$if     EXIST '../data/DEF_D1.inc' $INCLUDE      '../data/DEF_D1.inc';
$if not EXIST '../data/DEF_D1.inc' $INCLUDE '../../base/data/DEF_D1.inc';
%semislash%;

SET DEF_U1(DEF)   'Upwards steps in elastic el. demand, relative data format' %semislash%
$if     EXIST '../data/DEF_U1.inc' $INCLUDE      '../data/DEF_U1.inc';
$if not EXIST '../data/DEF_U1.inc' $INCLUDE '../../base/data/DEF_U1.inc';
%semislash%;

SET DEF_D2(DEF)   'Downwards steps in elastic el. demand, absolute Money and MW-incremental data format'%semislash%
$if     EXIST '../data/DEF_D2.inc' $INCLUDE      '../data/DEF_D2.inc';
$if not EXIST '../data/DEF_D2.inc' $INCLUDE '../../base/data/DEF_D2.inc';
%semislash%;

SET DEF_U2(DEF)   'Upwards steps in elastic el. demand, absolute Money and MW-incremental data format' %semislash%
$if     EXIST '../data/DEF_U2.inc' $INCLUDE      '../data/DEF_U2.inc';
$if not EXIST '../data/DEF_U2.inc' $INCLUDE '../../base/data/DEF_U2.inc';
%semislash%;

SET DEF_D3(DEF)   'Downwards steps in elastic el. demand, absolute Money and fraction of nominal demand data format' %semislash%
$if     EXIST '../data/DEF_D3.inc' $INCLUDE      '../data/DEF_D3.inc';
$if not EXIST '../data/DEF_D3.inc' $INCLUDE '../../base/data/DEF_D3.inc';
%semislash%;

SET DEF_U3(DEF)   'Upwards steps in elastic el. demand, absolute Money and fraction of nominal demand data format' %semislash%
$if     EXIST '../data/DEF_U3.inc' $INCLUDE      '../data/DEF_U3.inc';
$if not EXIST '../data/DEF_U3.inc' $INCLUDE '../../base/data/DEF_U3.inc';
%semislash%;

PARAMETER DEF_STEPS(RRR,DEUSER,SSS,TTT,DF_QP,DEF)         'Elastic electricity demands'   %semislash%
$if     EXIST '../data/DEF_STEPS.inc' $INCLUDE      '../data/DEF_STEPS.inc';
$if not EXIST '../data/DEF_STEPS.inc' $INCLUDE '../../base/data/DEF_STEPS.inc';
%semislash%;

SET DHF  'Steps in elastic heat demand' %semislash%
$if     EXIST '../data/DHF.inc' $INCLUDE      '../data/DHF.inc';
$if not EXIST '../data/DHF.inc' $INCLUDE '../../base/data/DHF.inc';
%semislash%;

SET DHF_D1(DHF)    'Downwards steps in elastic heat demand, relative data format' %semislash%
$if     EXIST '../data/DHF_D1.inc' $INCLUDE      '../data/DHF_D1.inc';
$if not EXIST '../data/DHF_D1.inc' $INCLUDE '../../base/data/DHF_D1.inc';
%semislash%;

SET DHF_U1(DHF)    'Upwards steps in elastic heat demand, relative data format' %semislash%
$if     EXIST '../data/DHF_U1.inc' $INCLUDE      '../data/DHF_U1.inc';
$if not EXIST '../data/DHF_U1.inc' $INCLUDE '../../base/data/DHF_U1.inc';
%semislash%;

SET DHF_D2(DHF)    'Downwards steps in elastic heat demand, absolute Money and MW-incremental data format' %semislash%
$if     EXIST '../data/DHF_D2.inc' $INCLUDE      '../data/DHF_D2.inc';
$if not EXIST '../data/DHF_D2.inc' $INCLUDE '../../base/data/DHF_D2.inc';
%semislash%;

SET DHF_U2(DHF)    'Upwards steps in elastic heat demand, absolute Money and MW-incremental data format' %semislash%
$if     EXIST '../data/DHF_U2.inc' $INCLUDE      '../data/DHF_U2.inc';
$if not EXIST '../data/DHF_U2.inc' $INCLUDE '../../base/data/DHF_U2.inc';
%semislash%;

SET DHF_D3(DHF)    'Downwards steps in elastic heat demand, absolute Money and fraction of nominal demand data format' %semislash%
$if     EXIST '../data/DHF_D3.inc' $INCLUDE      '../data/DHF_D3.inc';
$if not EXIST '../data/DHF_D3.inc' $INCLUDE '../../base/data/DHF_D3.inc';
%semislash%;

SET DHF_U3(DHF)    'Upwards steps in elastic heat demand, absolute Money and fraction of nominal demand data format' %semislash%
$if     EXIST '../data/DHF_U3.inc' $INCLUDE      '../data/DHF_U3.inc';
$if not EXIST '../data/DHF_U3.inc' $INCLUDE '../../base/data/DHF_U3.inc';
%semislash%;

PARAMETER DHF_STEPS(AAA,DHUSER,SSS,TTT,DF_QP,DHF)         'Elastic heat demands'   %semislash%
$if     EXIST '../data/DHF_STEPS.inc' $INCLUDE      '../data/DHF_STEPS.inc';
$if not EXIST '../data/DHF_STEPS.inc' $INCLUDE '../../base/data/DHF_STEPS.inc';
%semislash%;
* ------------------------------------------------------------------------------
$label dflexquantend

$ifi %DEFPCALIB%==yes PARAMETER DEFP_CALIB(RRR,SSS,TTT)                  'Calibrate the price side of electricity demand'   %semislash%
$ifi %DEFPCALIB%==yes $if     EXIST '../data/DEFP_CALIB.inc' $INCLUDE      '../data/DEFP_CALIB.inc';
$ifi %DEFPCALIB%==yes $if not EXIST '../data/DEFP_CALIB.inc' $INCLUDE '../../base/data/DEFP_CALIB.inc';
$ifi %DEFPCALIB%==yes %semislash%;

$ifi %DHFPCALIB%==yes PARAMETER DHFP_CALIB(AAA,SSS,TTT)                  'Calibrate the price side of heat demand'   %semislash%
$ifi %DHFPCALIB%==yes $if     EXIST '../data/DHFP_CALIB.inc' $INCLUDE      '../data/DHFP_CALIB.inc';
$ifi %DHFPCALIB%==yes $if not EXIST '../data/DHFP_CALIB.inc' $INCLUDE '../../base/data/DHFP_CALIB.inc';
$ifi %DHFPCALIB%==yes %semislash%;

*-------------------------------------------------------------------------------
*--- End: Any declarations and definitions of sets, aliases and acronyms for addon
*-------------------------------------------------------------------------------



PARAMETER GKFX(YYY,AAA,GGG)    'Capacity of existing generation technologies (MW)' %semislash%
$if     EXIST '../data/GKFX.inc' $INCLUDE      '../data/GKFX.inc';
$if not EXIST '../data/GKFX.inc' $INCLUDE '../../base/data/GKFX.inc';
%semislash%;

PARAMETER YVALUE(YYY)   'Numerical value of the years labels'  %semislash%
$if     EXIST '../data/YVALUE.inc' $INCLUDE      '../data/YVALUE.inc';
$if not EXIST '../data/YVALUE.inc' $INCLUDE '../../base/data/YVALUE.inc';
%semislash%;

PARAMETER DECOM_G(YYY,YYY,AAA,GGG)    'DECOMMISIONING YEAR OF ENDOGENOUS GENERATION INVESTMENTS' %semislash%
$if     EXIST '../data/DECOM_G.inc' $INCLUDE      '../data/DECOM_G.inc';
$if not EXIST '../data/DECOM_G.inc' $INCLUDE '../../base/data/DECOM_G.inc';
%semislash%;

PARAMETER FMAXINVEST(CCC,FFF)   'Maximum investment (MW) by fuel type for each year simulated'    %semislash%
$if     EXIST '../data/FMAXINVEST.inc' $INCLUDE      '../data/FMAXINVEST.inc';
$if not EXIST '../data/FMAXINVEST.inc' $INCLUDE '../../base/data/FMAXINVEST.inc';
%semislash%;

/*  todo
PARAMETER FMAXINVESTNA(YYY,FFF)   'Maximum investment (MW) by fuel type for each year simulated(aggregated countries)'    %semislash%
$if     EXIST '../data/FMAXINVESTNA.inc' $INCLUDE      '../data/FMAXINVESTNA.inc';
$if not EXIST '../data/FMAXINVESTNA.inc' $INCLUDE '../../base/data/FMAXINVESTNA.inc';
%semislash%;   */   FMAXINVESTNA(YYY,FFF) = 0;

/*  todo
PARAMETER GROWTHCAPCG(C,GGG)    'Maximum model generated capacity increase (MW) from one year to the next'   %semislash%
$if     EXIST '../data/GROWTHCAPCG.inc' $INCLUDE         '../data/GROWTHCAPCG.inc';
$if not EXIST '../data/GROWTHCAPCG.inc' $INCLUDE '../../base/data/GROWTHCAPCG.inc';
%semislash%;   */   GROWTHCAPCG(C,GGG)  = INF;

PARAMETER DISLOSS_E(RRR)    'Loss in electricity distribution (fraction)'   %semislash%
$if     EXIST '../data/DISLOSS_E.inc' $INCLUDE      '../data/DISLOSS_E.inc';
$if not EXIST '../data/DISLOSS_E.inc' $INCLUDE '../../base/data/DISLOSS_E.inc';
%semislash%;

PARAMETER DISLOSS_H(AAA)    'Loss in heat distribution (fraction)'  %semislash%
$if     EXIST '../data/DISLOSS_H.inc' $INCLUDE      '../data/DISLOSS_H.inc';
$if not EXIST '../data/DISLOSS_H.inc' $INCLUDE '../../base/data/DISLOSS_H.inc';
%semislash%;

PARAMETER DISCOST_E(RRR)    'Cost of electricity distribution (Money/MWh)'  %semislash%
$if     EXIST '../data/DISCOST_E.inc' $INCLUDE      '../data/DISCOST_E.inc';
$if not EXIST '../data/DISCOST_E.inc' $INCLUDE '../../base/data/DISCOST_E.inc';
%semislash%;

PARAMETER DISCOST_H(AAA)    'Cost of heat distribution (Money/MWh)'     %semislash%
$if     EXIST '../data/DISCOST_H.inc' $INCLUDE      '../data/DISCOST_H.inc';
$if not EXIST '../data/DISCOST_H.inc' $INCLUDE '../../base/data/DISCOST_H.inc';
%semislash%;

PARAMETER FKPOT(CCCRRRAAA,FFF)    'Fuel potential restricted by geography (MW)'   %semislash%
$if     EXIST '../data/FKPOT.inc' $INCLUDE      '../data/FKPOT.inc';
$if not EXIST '../data/FKPOT.inc' $INCLUDE '../../base/data/FKPOT.inc';
%semislash%;

/* Todo
PARAMETER FKMIN(YYY,CCCRRRAAA,FFF)    'Capacity restricted by geography (MW)'   %semislash%
$if     EXIST '../data/FKMIN.inc' $INCLUDE      '../data/FKMIN.inc';
$if not EXIST '../data/FKMIN.inc' $INCLUDE '../../base/data/FKMIN.inc';
%semislash%;  */     FKMIN(YYY,CCCRRRAAA,FFF)=0;

/*
PARAMETER FKMAX(YYY,CCCRRRAAA,FFF)    'Capacity by geography (MW)'   %semislash%
$if     EXIST '../data/FKMAX.inc' $INCLUDE      '../data/FKMAX.inc';
$if not EXIST '../data/FKPOT.inc' $INCLUDE '../../base/data/FKMAX.inc';
%semislash%;*/   FKMAX(YYY,CCCRRRAAA,FFF)=0;

/*
PARAMETER FKEQ(YYY,CCCRRRAAA,FFF)    'Capacity by geography (MW)'   %semislash%
$if     EXIST '../data/FKEQ.inc' $INCLUDE      '../data/FKEQ.inc';
$if not EXIST '../data/FKEQ.inc' $INCLUDE '../../base/data/FKEQ.inc';
%semislash%; */    FKEQ(YYY,CCCRRRAAA,FFF)=0;

/*
PARAMETER FKMINNA(YYY,FFF)    'Capacity restricted by geography (MW)'   %semislash%
$if     EXIST '../data/FKMINNA.inc' $INCLUDE      '../data/FKMINNA.inc';
$if not EXIST '../data/FKMINNA.inc' $INCLUDE '../../base/data/FKMINNA.inc';
%semislash%; */ FKMINNA(YYY,FFF)=0;

/*PARAMETER FKMAXNA(YYY,FFF)    'Capacity restricted by geography (MW)'   %semislash%
$if     EXIST '../data/FKMAXNA.inc' $INCLUDE      '../data/FKMAXNA.inc';
$if not EXIST '../data/FKPOT.inc' $INCLUDE '../../base/data/FKMAXNA.inc';
%semislash%;*/ FKMAXNA(YYY,FFF) =0;

/*
PARAMETER FKEQNA(YYY,FFF)    'Capacity restricted by geography (MW)'   %semislash%
$if     EXIST '../data/FKEQNA.inc' $INCLUDE      '../data/FKEQNA.inc';
$if not EXIST '../data/FKEQNA.inc' $INCLUDE '../../base/data/FKEQNA.inc';
%semislash%; */  FKEQNA(YYY,FFF)=0;

PARAMETER FGEMIN(CCCRRRAAA,FFF)    'Minimum electricity generation by fuel (MWh)'  %semislash%
$if     EXIST '../data/FGEMIN.inc' $INCLUDE      '../data/FGEMIN.inc';
$if not EXIST '../data/FGEMIN.inc' $INCLUDE '../../base/data/FGEMIN.inc';
%semislash%;

PARAMETER FGEMAX(CCCRRRAAA,FFF)     'Maximum electricity generation by fuel (MWh)'   %semislash%
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

* Maximum capacity at new technologies. Presently not implemented.
*PARAMETER GKNMAX(YYY,AAA,GGG)   'Maximum capacity at new technologies (MW)'  %semislash%
*$if     EXIST '../data/GKNMAX.inc' $INCLUDE      '../data/GKNMAX.inc';
*$if not EXIST '../data/GKNMAX.inc' $INCLUDE '../../base/data/GKNMAX.inc';
*%semislash%;


PARAMETER WTRRSFLH(AAA)    'Full load hours for hydro reservoir plants (hours)'  %semislash%
$if     EXIST '../data/WTRRSFLH.inc' $INCLUDE      '../data/WTRRSFLH.inc';
$if not EXIST '../data/WTRRSFLH.inc' $INCLUDE '../../base/data/WTRRSFLH.inc';
%semislash%;

PARAMETER WTRRRFLH(AAA)    'Full load hours for hydro run-of-river plants (hours)'  %semislash%
$if     EXIST '../data/WTRRRFLH.inc' $INCLUDE      '../data/WTRRRFLH.inc';
$if not EXIST '../data/WTRRRFLH.inc' $INCLUDE '../../base/data/WTRRRFLH.inc';
%semislash%;

PARAMETER WNDFLH(AAA)    'Full load hours for wind power (hours)'  %semislash%
$if     EXIST '../data/WNDFLH.inc' $INCLUDE      '../data/WNDFLH.inc';
$if not EXIST '../data/WNDFLH.inc' $INCLUDE '../../base/data/WNDFLH.inc';
%semislash%;

PARAMETER SOLEFLH(AAA)    'Full load hours for solar power (hours)'  %semislash%
$if     EXIST '../data/SOLEFLH.inc' $INCLUDE      '../data/SOLEFLH.inc';
$if not EXIST '../data/SOLEFLH.inc' $INCLUDE '../../base/data/SOLEFLH.inc';
%semislash%;


PARAMETER SOLHFLH(AAA)    'Full load hours for solar power (hours)'  %semislash%
$if     EXIST '../data/SOLHFLH.inc' $INCLUDE      '../data/SOLHFLH.inc';
$if not EXIST '../data/SOLHFLH.inc' $INCLUDE '../../base/data/SOLHFLH.inc';
%semislash%;

PARAMETER WAVEFLH(AAA)    'Full load hours for wave power (hours)'  %semislash%
$if     EXIST '../data/WAVEFLH.inc' $INCLUDE      '../data/WAVEFLH.inc';
$if not EXIST '../data/WAVEFLH.inc' $INCLUDE '../../base/data/WAVEFLH.inc';
%semislash%;

PARAMETER HYRSDATA(AAA,HYRSDATASET,SSS)    'Data for hydro with storage'  %semislash%
$if     EXIST '../data/HYRSDATA.inc' $INCLUDE         '../data/HYRSDATA.inc';
$if not EXIST '../data/HYRSDATA.inc' $INCLUDE '../../base/data/HYRSDATA.inc';
%semislash%;

PARAMETER TAX_GF(YYY,AAA,G)    'Fuel taxes on heat-only units'  %semislash%
$if     EXIST '../data/TAX_GF.inc' $INCLUDE      '../data/TAX_GF.inc';
$if not EXIST '../data/TAX_GF.inc' $INCLUDE '../../base/data/TAX_GF.inc';
%semislash%;

PARAMETER TAX_GE(YYY,AAA,G)    'Electricity taxes on generation units and subsidies(-) (RMB/MWh)'  %semislash%
$if     EXIST '../data/TAX_GE.inc' $INCLUDE      '../data/TAX_GE.inc';
$if not EXIST '../data/TAX_GE.inc' $INCLUDE '../../base/data/TAX_GE.inc';
%semislash%;

PARAMETER TAX_GH(YYY,AAA,G)    'Heat taxes on generation units'   %semislash%
$if     EXIST '../data/TAX_GH.inc' $INCLUDE      '../data/TAX_GH.inc';
$if not EXIST '../data/TAX_GH.inc' $INCLUDE '../../base/data/TAX_GH.inc';
%semislash%;

PARAMETER TAX_KN(YYY,AAA,G)    'Tax (neg. subsidy) for investment in electricity generation (mRMB/MW)'  %semislash%
$if     EXIST '../data/TAX_KN.inc' $INCLUDE      '../data/TAX_KN.inc';
$if not EXIST '../data/TAX_KN.inc' $INCLUDE '../../base/data/TAX_KN.inc';
%semislash%;

PARAMETER TAX_F(FFF,CCC)   'Fuel taxes for heat and electricity production (Money/GJ)'  %semislash%
$if     EXIST '../data/TAX_F.inc' $INCLUDE      '../data/TAX_F.inc';
$if not EXIST '../data/TAX_F.inc' $INCLUDE '../../base/data/TAX_F.inc';
%semislash%;

PARAMETER TAX_DE(CCC,DEUSER)    'Consumers tax on electricity consumption (Money/MWh)'  %semislash%
$if     EXIST '../data/TAX_DE.inc' $INCLUDE      '../data/TAX_DE.inc';
$if not EXIST '../data/TAX_DE.inc' $INCLUDE '../../base/data/TAX_DE.inc';
%semislash%;

PARAMETER TAX_DH(CCC,DHUSER)    'Consumers tax on heat consumption (Money/MWh)'  %semislash%
$if     EXIST '../data/TAX_DH.inc' $INCLUDE      '../data/TAX_DH.inc';
$if not EXIST '../data/TAX_DH.inc' $INCLUDE '../../base/data/TAX_DH.inc';
%semislash%;

SCALAR DISCOUNTRATE 'Discount rate by country (fraction)' !! Hans "by Country"?
$if     EXIST '../data/DISCOUNTRATE.inc' $INCLUDE         '../data/DISCOUNTRATE.inc';
$if not EXIST '../data/DISCOUNTRATE.inc' $INCLUDE '../../base/data/DISCOUNTRATE.inc';
%semislash%;

PARAMETER ANNUITYCG(CCC,GGG)   'Transforms investment in transmission lines into annual payment (fraction)'  %semislash%
$if     EXIST '../data/ANNUITYCG.inc' $INCLUDE         '../data/ANNUITYCG.inc';
$if not EXIST '../data/ANNUITYCG.inc' $INCLUDE '../../base/data/ANNUITYCG.inc';
%semislash%;

PARAMETER ANNUITYCX(CCC)   'Transforms investment to annual payment (fraction) for transmission'  %semislash%
$if     EXIST '../data/ANNUITYCX.inc' $INCLUDE         '../data/ANNUITYCX.inc';
$if not EXIST '../data/ANNUITYCX.inc' $INCLUDE '../../base/data/ANNUITYCX.inc';
%semislash%;


PARAMETER GINVCOST(AAA,GGG)    'Investment cost for new technology (MMoney/MW)'  %semislash%
$if     EXIST '../data/GINVCOST.inc' $INCLUDE         '../data/GINVCOST.inc';
$if not EXIST '../data/GINVCOST.inc' $INCLUDE '../../base/data/GINVCOST.inc';
%semislash%;

PARAMETER GOMVCOST(AAA,GGG)    'Variable operating and maintenance costs (Money/MWh)'  %semislash%
$if     EXIST '../data/GOMVCOST.inc' $INCLUDE         '../data/GOMVCOST.inc';
$if not EXIST '../data/GOMVCOST.inc' $INCLUDE '../../base/data/GOMVCOST.inc';
%semislash%;

PARAMETER GOMFCOST(AAA,GGG)    'Annual fixed operating costs (kMoney/MW)'  %semislash%
$if     EXIST '../data/GOMFCOST.inc' $INCLUDE         '../data/GOMFCOST.inc';
$if not EXIST '../data/GOMFCOST.inc' $INCLUDE '../../base/data/GOMFCOST.inc';
%semislash%;

PARAMETER GEFFRATE(AAA,GGG)    "Fuel efficiency rating (strictly positive, typically close to 1; default/1/, use eps for 0)"  %semislash%
$if     EXIST '../data/GEFFRATE.inc' $INCLUDE         '../data/GEFFRATE.inc';
$if not EXIST '../data/GEFFRATE.inc' $INCLUDE '../../base/data/GEFFRATE.inc';
%semislash%;
* Default value inserted:
GEFFRATE(IA,G)$(NOT GEFFRATE(IA,G)) = 1;

PARAMETER DEFP_BASE(RRR)    'Nominal annual average consumer electricity price (Money/MWh)'  %semislash%
$if     EXIST '../data/DEFP_BASE.inc' $INCLUDE         '../data/DEFP_BASE.inc';
$if not EXIST '../data/DEFP_BASE.inc' $INCLUDE '../../base/data/DEFP_BASE.inc';
%semislash%;

PARAMETER DHFP_BASE(AAA)    'Nominal annual average consumer heat price (Money/MWh)'  %semislash%
$if     EXIST '../data/DHFP_BASE.inc' $INCLUDE         '../data/DHFP_BASE.inc';
$if not EXIST '../data/DHFP_BASE.inc' $INCLUDE '../../base/data/DHFP_BASE.inc';
%semislash%;



*-------------------------------------------------------------------------------
*---- End: Geographically specific values --------------------------------------
*-------------------------------------------------------------------------------


*-------------------------------------------------------------------------------
*---- Annual electricity demand : ---------------------------------------------
*-------------------------------------------------------------------------------
PARAMETER DE(YYY,RRR,DEUSER)    'Annual electricity consumption (MWh)' %semislash%
$if     EXIST '../data/DE.inc' $INCLUDE         '../data/DE.inc';
$if not EXIST '../data/DE.inc' $INCLUDE '../../base/data/DE.inc';
%semislash%;


*-------------------------------------------------------------------------------
*---- Annual heat demand: -----------------------------------------------------
*-------------------------------------------------------------------------------
PARAMETER DH(YYY,AAA,DHUSER)    'Annual heat consumption (MWh)'  %semislash%
$if     EXIST '../data/DH.inc' $INCLUDE         '../data/DH.inc';
$if not EXIST '../data/DH.inc' $INCLUDE '../../base/data/DH.inc';
%semislash%;



*-------------------------------------------------------------------------------
*---- Transmission data: ------------------------------------------------------
*-------------------------------------------------------------------------------
!! Previous name XKINI; for data consistency, kept for data inclusion for this specific version, data copied to XKFX below.     todo
PARAMETER XKINI(YYY,IRRRE,IRRRI)  'Capacity of exogenously given transmission capacity between regions (MW)'   %semislash%
$if     EXIST '../data/XKINI.inc' $INCLUDE         '../data/XKINI.inc';
$if not EXIST '../data/XKINI.inc' $INCLUDE '../../base/data/XKINI.inc';
%semislash%;

PARAMETER XKFX(YYY,IRRRE,IRRRI)  'Capacity of exogenously given transmission capacity between regions (MW)'; !! New suggested name for XKINI. XKFX data copie3d to XKFX.
XKFX(YYY,IRRRE,IRRRI) = XKINI(YYY,IRRRE,IRRRI);

PARAMETER XINVCOST(YYY,IRRRE,IRRRI)   'Investment cost in new transmission capacity, default: INF or 0: no investment, EPS or positive: possible with stated cost (Money/MW)'    %semislash%
$if     EXIST '../data/XINVCOST.inc' $INCLUDE         '../data/XINVCOST.inc';
$if not EXIST '../data/XINVCOST.inc' $INCLUDE '../../base/data/XINVCOST.inc';
%semislash%;

PARAMETER XCOST(IRRRE,IRRRI)      'Transmission cost between regions (Money/MWh)'   %semislash%
$if     EXIST '../data/XCOST.inc' $INCLUDE         '../data/XCOST.inc';
$if not EXIST '../data/XCOST.inc' $INCLUDE '../../base/data/XCOST.inc';
%semislash%;

PARAMETER XLOSS(IRRRE,IRRRI)      'Transmission loss between regions (fraction)'  %semislash%
$if     EXIST '../data/XLOSS.inc' $INCLUDE         '../data/XLOSS.inc';
$if not EXIST '../data/XLOSS.inc' $INCLUDE '../../base/data/XLOSS.inc';
%semislash%;

$ifi %XKRATE_DOL%==IRRRE_IRRRI          PARAMETER XKRATE(IRRRE,IRRRI)         "Transmission capacity rating (share; non-negative, typically close to 1; default/1/, use eps for 0)";
$ifi %XKRATE_DOL%==IRRRE_IRRRI_SSS      PARAMETER XKRATE(IRRRE,IRRRI,SSS)     "Transmission capacity rating (share; non-negative, typically close to 1; default/1/, use eps for 0)";
$ifi %XKRATE_DOL%==IRRRE_IRRRI_SSS_TTT  PARAMETER XKRATE(IRRRE,IRRRI,SSS,TTT) "Transmission capacity rating (share; non-negative, typically close to 1; default/1/, use eps for 0)";
$if     EXIST '../data/XKRATE.inc' $INCLUDE         '../data/XKRATE.inc';
$if not EXIST '../data/XKRATE.inc' $INCLUDE '../../base/data/XKRATE.inc';
%semislash%;
* Default value inserted:
$ifi %XKRATE_DOL%==IRRRE_IRRRI          XKRATE(IRE,IRI)$(NOT XKRATE(IRE,IRI)) = 1;
$ifi %XKRATE_DOL%==IRRRE_IRRRI_SSS      XKRATE(IRE,IRI,S)$(NOT XKRATE(IRE,IRI,S)) = 1;
$ifi %XKRATE_DOL%==IRRRE_IRRRI_SSS_TTT  XKRATE(IRE,IRI,S,T)$(NOT XKRATE(IRE,IRI,S,T)) = 1;



PARAMETER XMAXINV(IRRRE,IRRRI)   'Max investment in transmission capacity between two regions for each simulated year (each 5th year)'  %semislash%
$if     EXIST '../data/XMAXINV.inc' $INCLUDE         '../data/XMAXINV.inc';
$if not EXIST '../data/XMAXINV.inc' $INCLUDE '../../base/data/XMAXINV.inc';
%semislash%;

*-------------------------------------------------------------------------------
*---- Exchange with third countries: ------------------------------------------
*-------------------------------------------------------------------------------
* Fixed profile:
PARAMETER X3FX(YYY,RRR)    'Annual net electricity export to third regions'  %semislash%
$if     EXIST '../data/X3FX.inc' $INCLUDE      '../data/X3FX.inc';
$if not EXIST '../data/X3FX.inc' $INCLUDE '../../base/data/X3FX.inc';
%semislash%;


$ifi not %X3V%==yes $goto X3V_label3
*-------------------------------------------------------------------------------
* Price-dependant electricity exchange to places outside the simulated area
*-------------------------------------------------------------------------------

* Price (Money/MWh) for the price dependent electricity exchange.
* It will be assumed that prices should be positive.
* For import the prices should be increasing with ord(X3VSTEP0),
* for export the prices should be decreasing with ord(X3VSTEP0).


PARAMETER X3VPIM(YYY,RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)   'Price (Money/MWh) of price dependent imported electricity'  %semislash%
$if     EXIST '../data/X3VPIM.inc' $INCLUDE      '../data/X3VPIM.inc';
$if not EXIST '../data/X3VPIM.inc' $INCLUDE '../../base/data/X3VPIM.inc';
%semislash%;


PARAMETER X3VPEX(YYY,RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)   'Price (Money/MWh) of price dependent exported electricity'  %semislash%
$if     EXIST '../data/X3VPEX.inc' $INCLUDE      '../data/X3VPEX.inc';
$if not EXIST '../data/X3VPEX.inc' $INCLUDE '../../base/data/X3VPEX.inc';
%semislash%;


* Maximum quantity (MW) of price dependent electricity exchange per time segment:
PARAMETER X3VQIM(RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)   'Limit (MW) on price dependent electricity import'  %semislash%
$if     EXIST '../data/X3VQIM.inc' $INCLUDE      '../data/X3VQIM.inc';
$if not EXIST '../data/X3VQIM.inc' $INCLUDE '../../base/data/X3VQIM.inc';
%semislash%;


PARAMETER X3VQEX(RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)   'Limit (MW) on price dependent electricity export'  %semislash%
$if     EXIST '../data/X3VQEX.inc' $INCLUDE      '../data/X3VQEX.inc';
$if not EXIST '../data/X3VQEX.inc' $INCLUDE '../../base/data/X3VQEX.inc';
%semislash%;

$label X3V_label3

*-------------------------------------------------------------------------------
* Annually specified fuel prices: ---------------------------------------------
*-------------------------------------------------------------------------------

PARAMETER FUELPRICE(YYY,AAA,FFF)                   'Fuel prices (Money/GJ)'   %semislash%
$if     EXIST '../data/FUELPRICE.inc' $INCLUDE      '../data/FUELPRICE.inc';
$if not EXIST '../data/FUELPRICE.inc' $INCLUDE '../../base/data/FUELPRICE.inc';
%semislash%;


*-------------------------------------------------------------------------------
*---- Emission policy data: ---------------------------------------------------
*-------------------------------------------------------------------------------

PARAMETER M_POL(YYY,MPOLSET,CCC)    'Emission policy data'   %semislash%
$if     EXIST '../data/M_POL.inc' $INCLUDE         '../data/M_POL.inc';
$if not EXIST '../data/M_POL.inc' $INCLUDE '../../base/data/M_POL.inc';
%semislash%;

/*
PARAMETER M_POLNA(YYY,MPOLSET)    'Emission policy data'   %semislash%
$if     EXIST '../data/M_POLNA.inc' $INCLUDE         '../data/M_POLNA.inc';
$if not EXIST '../data/M_POLNA.inc' $INCLUDE '../../base/data/M_POLNA.inc';
%semislash%;  */    M_POLNA(YYY,MPOLSET)=0;

*-------------------------------------------------------------------------------
*---- Seasonal and daily variations: ------------------------------------------
*-------------------------------------------------------------------------------


* DISSE FILER INDHOLDER NaSTEN ALLESAMMEN KODE, CONDITIONALS, ETC! Skal revideres!

PARAMETER WEIGHT_S(SSS)                            'Weight (relative length) of each season'    %semislash%
$if     EXIST '../data/WEIGHT_S.inc' $INCLUDE      '../data/WEIGHT_S.inc';
$if not EXIST '../data/WEIGHT_S.inc' $INCLUDE '../../base/data/WEIGHT_S.inc';
%semislash%;

PARAMETER WEIGHT_T(TTT)                            'Weight (relative length) of each time period'   %semislash%
$if     EXIST '../data/WEIGHT_T.inc' $INCLUDE         '../data/WEIGHT_T.inc';
$if not EXIST '../data/WEIGHT_T.inc' $INCLUDE '../../base/data/WEIGHT_T.inc';
%semislash%;

PARAMETER CYCLESINS(S) 'Number of short term storage load cycles per season (use inf with duration curve approach) ((0;inf])'  %semislash%
$if     EXIST '../data/CYCLESINS.inc' $INCLUDE         '../data/CYCLESINS.inc';
$if not EXIST '../data/CYCLESINS.inc' $INCLUDE '../../base/data/CYCLESINS.inc';
%semislash%;

PARAMETER GKRATE(AAA,GGG,SSS)                       "Capacity rating (non-negative, typically close to 1; default/1/, use eps for 0)" %semislash%
$if     EXIST '../data/GKRATE.inc' $INCLUDE         '../data/GKRATE.inc';
$if not EXIST '../data/GKRATE.inc' $INCLUDE '../../base/data/GKRATE.inc';
%semislash%;
* Default value inserted:
GKRATE(IA,G,S)$(NOT GKRATE(IA,G,S)) = 1;


PARAMETER DE_VAR_T(RRR,DEUSER,SSS,TTT)                    'Variation in electricity demand'   %semislash%
$if     EXIST '../data/DE_VAR_T.inc' $INCLUDE      '../data/DE_VAR_T.inc';
$if not EXIST '../data/DE_VAR_T.inc' $INCLUDE '../../base/data/DE_VAR_T.inc';
%semislash%;

PARAMETER DH_VAR_T(AAA,DHUSER,SSS,TTT)                    'Variation in heat demand'   %semislash%
$if     EXIST '../data/DH_VAR_T.inc' $INCLUDE      '../data/DH_VAR_T.inc';
$if not EXIST '../data/DH_VAR_T.inc' $INCLUDE '../../base/data/DH_VAR_T.inc';
%semislash%;

PARAMETER WTRRSVAR_S(AAA,SSS)                      'Variation of the water inflow to reservoirs'   %semislash%
$if     EXIST '../data/WTRRSVAR_S.inc' $INCLUDE      '../data/WTRRSVAR_S.inc';
$if not EXIST '../data/WTRRSVAR_S.inc' $INCLUDE '../../base/data/WTRRSVAR_S.inc';
%semislash%;

PARAMETER WTRRRVAR_T(AAA,SSS,TTT)                  'Variation of generation of hydro run-of-river'    %semislash%
$if     EXIST '../data/WTRRRVAR_T.inc' $INCLUDE      '../data/WTRRRVAR_T.inc';
$if not EXIST '../data/WTRRRVAR_T.inc' $INCLUDE '../../base/data/WTRRRVAR_T.inc';
%semislash%;

PARAMETER WND_VAR_T(AAA,SSS,TTT)                   'Variation of the wind generation'    %semislash%
$if     EXIST '../data/WND_VAR_T.inc' $INCLUDE      '../data/WND_VAR_T.inc';
$if not EXIST '../data/WND_VAR_T.inc' $INCLUDE '../../base/data/WND_VAR_T.inc';
%semislash%;

PARAMETER SOLE_VAR_T(AAA,SSS,TTT)                  'Variation of the solarE generation'   %semislash%
$if     EXIST '../data/SOLE_VAR_T.inc' $INCLUDE      '../data/SOLE_VAR_T.inc';
$if not EXIST '../data/SOLE_VAR_T.inc' $INCLUDE '../../base/data/SOLE_VAR_T.inc';
%semislash%;


PARAMETER SOLH_VAR_T(AAA,SSS,TTT)                  'Variation of the solarH generation'   %semislash%
$if     EXIST '../data/SOLH_VAR_T.inc' $INCLUDE      '../data/SOLH_VAR_T.inc';
$if not EXIST '../data/SOLH_VAR_T.inc' $INCLUDE '../../base/data/SOLH_VAR_T.inc';
%semislash%;

PARAMETER WAVE_VAR_T(AAA,SSS,TTT)                  'Variation of the solarH generation'   %semislash%
$if     EXIST '../data/WAVE_VAR_T.inc' $INCLUDE      '../data/WAVE_VAR_T.inc';
$if not EXIST '../data/WAVE_VAR_T.inc' $INCLUDE '../../base/data/WAVE_VAR_T.inc';
%semislash%;

PARAMETER X3FX_VAR_T(RRR,SSS,TTT)                  'Variation in fixed exchange with 3. region'   %semislash%
$if     EXIST '../data/X3FX_VAR_T.inc' $INCLUDE      '../data/X3FX_VAR_T.inc';
$if not EXIST '../data/X3FX_VAR_T.inc' $INCLUDE '../../base/data/X3FX_VAR_T.inc';
%semislash%;

PARAMETER HYPPROFILS(AAA,SSS)                      'Hydro with storage seasonal price profile'   %semislash%
$if     EXIST '../data/HYPPROFILS.inc' $INCLUDE      '../data/HYPPROFILS.inc';
$if not EXIST '../data/HYPPROFILS.inc' $INCLUDE '../../base/data/HYPPROFILS.inc';
%semislash%;


$ifi %bb3%==yes WEIGHT_T(T)=1;


$ifi %YIELDREQUIREMENT%==yes  PARAMETER YIELDREQ(GGG)  'Differentiates yield requirements for different technologies'   %semislash%
$ifi %YIELDREQUIREMENT%==yes  $if     EXIST '../data/YIELDREQ.inc' $INCLUDE      '../data/YIELDREQ.inc';
$ifi %YIELDREQUIREMENT%==yes  $if not EXIST '../data/YIELDREQ.inc' $INCLUDE '../../base/data/YIELDREQ.inc';
$ifi %YIELDREQUIREMENT%==yes  %semislash%;


$ifi not %BB4%==yes $goto label_BB4_1
$ifi %BB4%==yes SET YMODEL "YMODEL is a set used to derive the years from Y in each Balbase4 model";
$ifi %BB4%==yes PARAMETER YMODELDELTA(YMODEL) 'The number of years between two consequtive years in a BB4 model';
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
$if     EXIST '../data/OMONEY.inc' $INCLUDE         '../data/OMONEY.inc';
$if not EXIST '../data/OMONEY.inc' $INCLUDE '../../base/data/OMONEY.inc';


SCALAR PENALTYQ  'Penalty on violation of equation'  %semislash%
$if     EXIST '../data/PENALTYQ.inc' $INCLUDE         '../data/PENALTYQ.inc';
$if not EXIST '../data/PENALTYQ.inc' $INCLUDE '../../base/data/PENALTYQ.inc';
%semislash%;
