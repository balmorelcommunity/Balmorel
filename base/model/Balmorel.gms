* File Balmorel.gms
$TITLE Balmorel version 3.02 (September 2011)

* Dynamic partial equilibrium model for the electricity and CHP sector.

* Efforts have been made to make a good model.
* However, most probably the model is incomplete and subject to errors.
* It is distributed with the idea that it will be usefull anyway,
* and with the purpose of getting the essential feedback,
* which in turn will permit the development of improved versions
* to the benefit of other user.
* Hopefully it will be applied in that spirit.

* Description, further documentation, examples of applications of the model,
* conditions of use, and contact for feedback may be found at www.Balmorel.com.


SCALAR IBALVERSN 'This version of Balmorel' /302.20110920/;
* (Internal version id BC07)


*-------------------------------------------------------------------------------
*-------------------------------------------------------------------------------
*-------------------------------------------------------------------------------

* GAMS options are $included from file balgams.opt or file balgams.bui.
* In order to make them apply globally, the option $ONGLOBAL will first be set here:
$ONGLOBAL

* Use local file if it exists, otherwise use the one in  ../../base/model/ folder.
* Use balgams.bui (for the Balmorel User Interface (BUI)) if it exists, otherwise use balgams.opt.
$ifi  exist 'balgams.bui'  $include 'balgams.bui';
$ifi  exist 'balgams.bui'  $goto endincludebalgams
$ifi  exist 'balgams.opt'  $include 'balgams.opt';
$ifi  exist 'balgams.opt'  $goto endincludebalgams
$ifi  exist '../../base/model/balgams.bui'  $include '../../base/model/balgams.bui';
$ifi  exist '../../base/model/balgams.bui'  $goto endincludebalgams
$include    '../../base/model/balgams.opt'
$label endincludebalgams


* The balopt file holds control settings for the Balmorel model.
* Use local file if it exists, otherwise use the one in  ../../base/model/ folder.
* Use balopt.bui (for the Balmorel User Interface (BUI)) if it exists, otherwise use balopt.opt.
$ifi  exist 'balopt.bui'  $include 'balopt.bui';
$ifi  exist 'balopt.bui'  $goto endincludebalopt
$ifi  exist 'balopt.opt'  $include 'balopt.opt';
$ifi  exist 'balopt.opt'  $goto endincludebalopt
$ifi  exist '../../base/model/balopt.bui'  $include '../../base/model/balopt.bui';
$ifi  exist '../../base/model/balopt.bui'  $goto endincludebalopt
$include    '../../base/model/balopt.opt'
$label endincludebalopt


* In case of Model Balbase4 the following included file substitutes the remaining part of the present file Balmorel.gms:
$ifi %BB4%==yes $include '../../base/model/BalmorelBB4.inc';
$ifi %BB4%==yes $goto ENDOFMODEL


*-------------------------------------------------------------------------------
*-------------------------------------------------------------------------------
* Declarations and inclusion of data files:
*-------------------------------------------------------------------------------
*-------------------------------------------------------------------------------


*-------------------------------------------------------------------------------
*---- User defined SETS and ACRONYMS needed for data entry: --------------------
*-------------------------------------------------------------------------------

* Declarations: ----------------------------------------------------------------

* SETS:
SET CCCRRRAAA         'All geographical entities (CCC + RRR + AAA)';
SET CCC(CCCRRRAAA)    'All Countries';
SET RRR(CCCRRRAAA)    'All regions';
SET AAA(CCCRRRAAA)    'All areas';
SET CCCRRR(CCC,RRR)   'Regions in countries';
SET RRRAAA(RRR,AAA)   'Areas in regions';
SET YYY               'All years';
SET SSS               'All seasons';
SET TTT               'All time periods';
SET GGG               'All generation technologies';
SET GDATASET          'Generation technology data';
SET FFF               'Fuels';
SET FDATASET          'Characteristics of fuels';
SET HYRSDATAS         'Characteristics of hydro reservoirs';
SET DF_QP             'Quantity and price information for elastic demands';
SET DEF               'Steps in elastic electricity demand';
SET DEF_D1(DEF)       'Downwards steps in elastic el. demand, relative data format';
SET DEF_U1(DEF)       'Upwards steps in elastic el. demand, relative data format';
SET DEF_D2(DEF)       'Downwards steps in elastic el. demand, absolute Money and MW-incremental data format';
SET DEF_U2(DEF)       'Upwards steps in elastic el. demand, absolute Money and MW-incremental data format';
SET DEF_D3(DEF)       'Downwards steps in elastic el. demand, absolute Money and fraction of nominal demand data format';
SET DEF_U3(DEF)       'Upwards steps in elastic el. demand, absolute Money and fraction of nominal demand data format';
SET DHF               'Steps in elastic heat demand';
SET DHF_D1(DHF)       'Downwards steps in elastic heat demand, relative data format';
SET DHF_U1(DHF)       'Upwards steps in elastic heat demand, relative data format';
SET DHF_D2(DHF)       'Downwards steps in elastic heat demand, absolute Money and MW-incremental data format';
SET DHF_U2(DHF)       'Upwards steps in elastic heat demand, absolute Money and MW-incremental data format';
SET DHF_D3(DHF)       'Downwards steps in elastic heat demand, absolute Money and fraction of nominal demand data format';
SET DHF_U3(DHF)       'Upwards steps in elastic heat demand, absolute Money and fraction of nominal demand data format';
SET MPOLSET           'Emission and other policy data';
SET C(CCC)            'Countries in the simulation';
SET G(GGG)            'Generation technologies in the simulation';
SET AGKN(AAA,GGG)     'Areas for possible location of new technologies';
SET Y(YYY)            'Years in the simulation';
SET S(SSS)            'Seasons in the simulation';
SET T(TTT)            'Time periods within the season in the simulation';
SET DAYTYPE           'Types of days within the week, typically workdays/weekend';
SET TWORKDAY(TTT)     'Time segments, T, in workdays';
SET TWEEKEND(TTT)     'Time segments, T, in weekends';



SET SCENARIO            'All scenarios';
SET SCENARSIM(SCENARIO) 'Scenarios in simulation';

* ALIASES:
ALIAS(SCENARSIM,SC);
* Internal set IGGGALIAS may be used in the $included data files:
ALIAS(GGG,IGGGALIAS);







* ACRONYMS:
* ACRONYMS for technology types
* Each of the following ACRONYMS symbolise a technology type,
* They correspond in a one-to-one way with the internal sets IGCND, IGBRP etc. below.
* They should generally not be changed.
* New technology types may be added only if also code specifying their properties are added.
ACRONYMS   GCND, GBPR, GEXT, GHOB, GETOH, GHSTO, GESTO, GHYRS, GHYRR, GWND, GSOLE, GSOLH;

* ACRONYMS for user defined fuels will be given in a $included file FFFACRONYMS.inc.


*-------------------------------------------------------------------------------
*----- Definitions of SETS and ACRONYMS that are given in the $included files:
*-------------------------------------------------------------------------------
* Printing of data to the list file controlled by %ONOFFDATALISTING% and %ONOFFCODELISTING%
* (see file balgams.opt):
%ONOFFDATALISTING%

SET CCCRRRAAA          'All geographical entities (CCC + RRR + AAA)' %semislash%
$if     EXIST '../data/CCCRRRAAA.inc' $INCLUDE      '../data/CCCRRRAAA.inc';
$if not EXIST '../data/CCCRRRAAA.inc' $INCLUDE '../../base/data/CCCRRRAAA.inc';
%semislash%;

SET CCC(CCCRRRAAA)       'All Countries' %semislash%
$if     EXIST '../data/CCC.inc' $INCLUDE      '../data/CCC.inc';
$if not EXIST '../data/CCC.inc' $INCLUDE '../../base/data/CCC.inc';
%semislash%;

SET RRR(CCCRRRAAA)       'All regions' %semislash%
$if     EXIST '../data/RRR.inc' $INCLUDE      '../data/RRR.inc';
$if not EXIST '../data/RRR.inc' $INCLUDE '../../base/data/RRR.inc';
%semislash%;

SET AAA(CCCRRRAAA)       'All areas' %semislash%
$if     EXIST '../data/AAA.inc' $INCLUDE      '../data/AAA.inc';
$if not EXIST '../data/AAA.inc' $INCLUDE '../../base/data/AAA.inc';
%semislash%;

SET CCCRRR(CCC,RRR)      'Regions in countries' %semislash%
$if     EXIST '../data/CCCRRR.inc' $INCLUDE      '../data/CCCRRR.inc';
$if not EXIST '../data/CCCRRR.inc' $INCLUDE '../../base/data/CCCRRR.inc';
%semislash%;

SET RRRAAA(RRR,AAA)      'Areas in regions' %semislash%
$if     EXIST '../data/RRRAAA.inc' $INCLUDE      '../data/RRRAAA.inc';
$if not EXIST '../data/RRRAAA.inc' $INCLUDE '../../base/data/RRRAAA.inc';
%semislash%;

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

SET GGG                'All generation technologies'   %semislash%
$if     EXIST '../data/GGG.inc' $INCLUDE      '../data/GGG.inc';
$if not EXIST '../data/GGG.inc' $INCLUDE '../../base/data/GGG.inc';
%semislash%;

SET GDATASET           'Generation technology data' %semislash%
$if     EXIST '../data/GDATASET.inc' $INCLUDE      '../data/GDATASET.inc';
$if not EXIST '../data/GDATASET.inc' $INCLUDE '../../base/data/GDATASET.inc';
%semislash%;

SET FFF                'Fuels'  %semislash%
$if     EXIST '../data/FFF.inc' $INCLUDE      '../data/FFF.inc';
$if not EXIST '../data/FFF.inc' $INCLUDE '../../base/data/FFF.inc';
%semislash%;

* ACRONYMS for fuels:
$ifi %semislash%=="/" ACRONYMS
$if     EXIST '../data/FFFACRONYM.inc' $INCLUDE      '../data/FFFACRONYM.inc';
$if not EXIST '../data/FFFACRONYM.inc' $INCLUDE '../../base/data/FFFACRONYM.inc';
;

SET FDATASET           'Characteristics of fuels ' %semislash%
$if     EXIST '../data/FDATASET.inc' $INCLUDE      '../data/FDATASET.inc';
$if not EXIST '../data/FDATASET.inc' $INCLUDE '../../base/data/FDATASET.inc';
%semislash%;

SET HYRSDATAS  'Characteristics of hydro reservoirs' %semislash%
$if     EXIST '../data/HYRSDATAS.inc' $INCLUDE      '../data/HYRSDATAS.inc';
$if not EXIST '../data/HYRSDATAS.inc' $INCLUDE '../../base/data/HYRSDATAS.inc';
%semislash%;

SET DF_QP  'Quantity and price information for elastic demands' %semislash%
$if     EXIST '../data/DF_QP.inc' $INCLUDE      '../data/DF_QP.inc';
$if not EXIST '../data/DF_QP.inc' $INCLUDE '../../base/data/DF_QP.inc';
%semislash%;

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

SET MPOLSET  'Emission and other policy data'   %semislash%
$if     EXIST '../data/MPOLSET.inc' $INCLUDE      '../data/MPOLSET.inc';
$if not EXIST '../data/MPOLSET.inc' $INCLUDE '../../base/data/MPOLSET.inc';
%semislash%;

SET C(CCC)    'Countries in the simulation'  %semislash%
$if     EXIST '../data/C.inc' $INCLUDE      '../data/C.inc';
$if not EXIST '../data/C.inc' $INCLUDE '../../base/data/C.inc';
%semislash%;

SET G(GGG)    'Generation technologies in the simulation'  %semislash%
$if     EXIST '../data/G.inc' $INCLUDE      '../data/G.inc';
$if not EXIST '../data/G.inc' $INCLUDE '../../base/data/G.inc';
%semislash%;

SET AGKN(AAA,GGG)   'Areas for possible location of new technologies'   %semislash%
$if     EXIST '../data/AGKN.inc' $INCLUDE      '../data/AGKN.inc';
$if not EXIST '../data/AGKN.inc' $INCLUDE '../../base/data/AGKN.inc';
%semislash%;

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

SET DAYTYPE       'Types of days within the week, typically workdays/weekend' %semislash%
$if     EXIST '../data/DAYTYPE.inc' $INCLUDE         '../data/DAYTYPE.inc';
$if not EXIST '../data/DAYTYPE.inc' $INCLUDE '../../base/data/DAYTYPE.inc';
%semislash%

SET TWORKDAY(TTT)   'Time segments, T, in workdays'  %semislash%
$if     EXIST '../data/TWORKDAY.inc' $INCLUDE         '../data/TWORKDAY.inc';
$if not EXIST '../data/TWORKDAY.inc' $INCLUDE '../../base/data/TWORKDAY.inc';
%semislash%

SET TWEEKEND(TTT)   'Time segments, T, in weekends'   %semislash%
$if     EXIST '../data/TWEEKEND.inc' $INCLUDE         '../data/TWEEKEND.inc';
$if not EXIST '../data/TWEEKEND.inc' $INCLUDE '../../base/data/TWEEKEND.inc';
%semislash%


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

SET SCENARIO            'All scenarios'  %semislash%
$if     EXIST '../data/SCENARIO.inc' $INCLUDE         '../data/SCENARIO.inc';
$if not EXIST '../data/SCENARIO.inc' $INCLUDE '../../base/data/SCENARIO.inc';
%semislash%

SET SCENARSIM(SCENARIO) 'Scenarios in simulation'  %semislash%
$if     EXIST '../data/SCENARSIM.inc' $INCLUDE         '../data/SCENARSIM.inc';
$if not EXIST '../data/SCENARSIM.inc' $INCLUDE '../../base/data/SCENARSIM.inc';
%semislash%



* Printing of data to the list file controlled by %ONOFFDATALISTING% and %ONOFFCODELISTING%
* (see file balgams.opt):
%ONOFFCODELISTING%
*-------------------------------------------------------------------------------
*--- End: Definitions of SETS and ACRONYMS that are given in the $included files
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
*----- Definitions of ALIASES that are needed for data entry:
*-------------------------------------------------------------------------------

ALIAS (RRR,IRRRE,IRRRI);
ALIAS (AAA,IAAAE,IAAAI);

*-------------------------------------------------------------------------------
*----- End: Definitions of ALIASES that are needed for data entry
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
*----- Any declarations and definitions of sets, aliases and acronyms for addon:
*-------------------------------------------------------------------------------

$ifi %GAS%==yes $include '../../base/addons/gas/gassets.inc';
$ifi %TSP%==yes $include '../../base/addons/Transport/TSPSets.inc';

$ifi %COMBTECH%==yes
$if     EXIST '../data/ggcomb.inc' $INCLUDE         '../data/ggcomb.inc';
$ifi %COMBTECH%==yes
$if not EXIST '../data/ggcomb.inc' $INCLUDE '../../base/data/ggcomb.inc';

* Addon AGKNDISC: discrete size investment in technologies:
$ifi not %AGKNDISC%==yes  $goto label_AGKNDISC1

SET AGKNDISCAG(AAA,GGG)   'Areas for possible location of discrete capacity investments in technologies' %semislash%
$if     EXIST '../data/AGKNDISCAG.inc' $INCLUDE         '../data/AGKNDISCAG.inc';
$if not EXIST '../data/AGKNDISCAG.inc' $INCLUDE '../../base/data/AGKNDISCAG.inc';
%semislash%

SET AGKNDISCGSIZESET    'Set of possible sizes for discrete capacity investments in technologies' %semislash%
$if     EXIST '../data/AGKNDISCGSIZESET.inc' $INCLUDE         '../data/AGKNDISCGSIZESET.inc';
$if not EXIST '../data/AGKNDISCGSIZESET.inc' $INCLUDE '../../base/data/AGKNDISCGSIZESET.inc';
%semislash%

SET AGKNDISCGDATASET    'Technology investment data types for discrete capacity size investments' %semislash%
$if     EXIST '../data/AGKNDISCGDATASET.inc' $INCLUDE         '../data/AGKNDISCGDATASET.inc';
$if not EXIST '../data/AGKNDISCGDATASET.inc' $INCLUDE '../../base/data/AGKNDISCGDATASET.inc';
%semislash%

PARAMETER AGKNDISCGDATA(GGG,AGKNDISCGSIZESET,AGKNDISCGDATASET) 'Technology investment data for discrete capacity size investments' %semislash%
$if     EXIST '../data/AGKNDISCGDATA.inc' $INCLUDE         '../data/AGKNDISCGDATA.inc';
$if not EXIST '../data/AGKNDISCGDATA.inc' $INCLUDE '../../base/data/AGKNDISCGDATA.inc';
%semislash%

$label label_AGKNDISC1
* End: Addon AGKNDISC: discrete size investment in technologies.

*-------------------------------------------------------------------------------
* End: Any declarations and definitions of sets, aliases and acronyms for addon
*-------------------------------------------------------------------------------




*-------------------------------------------------------------------------------
* The choice of model made in the balopt.opt fil is checked here,
* and basic sets concerning time within the year are reconstructed accordingly if needed:

$ifi %bb3%==yes $KILL T
$ifi %bb3%==yes SET T(TTT)   /T001*T168/;
$ifi %bb3%==yes $KILL TWORKDAY
$ifi %bb3%==yes $KILL TWEEKEND
$ifi %bb3%==yes SET TWORKDAY(TTT)   /T001*T120/;
$ifi %bb3%==yes SET TWEEKEND(TTT)   /T121*T168/;
*-------------------------------------------------------------------------------




*-------------------------------------------------------------------------------
*----- Any internal sets for addon to be placed here: --------------------------


$ifi %H2%==yes $include '../../base/addons/hydrogen/H2G.inc';

*----- End: Any internal sets for addon to be placed here: ---------------------
*-------------------------------------------------------------------------------



*------------------------------------------------------------------------------
* End: Declaration of internal sets
*------------------------------------------------------------------------------



*------------------------------------------------------------------------------
* Declaration and definition of numerical data: PARAMETERS and SCALARS:
*------------------------------------------------------------------------------


*------------------------------------------------------------------------------
*---- Technology data: ---------------------------------------------------------
*------------------------------------------------------------------------------
PARAMETER GDATA(GGG,GDATASET)    'Technologies characteristics' %semislash%
* Printing of data to the list file controlled by %ONOFFDATALISTING% and %ONOFFCODELISTING%:
%ONOFFDATALISTING%
$if     EXIST '../data/gdata.inc' $INCLUDE         '../data/gdata.inc';
$if not EXIST '../data/gdata.inc' $INCLUDE '../../base/data/gdata.inc';
%ONOFFCODELISTING%



*-------------------------------------------------------------------------------
* Definitions of internal sets relative to technologies,

* The following are convenient internal subsets of generation technologies:

SET IGCND(G)               'Condensing technologies';
SET IGBPR(G)               'Back pressure technologies';
SET IGEXT(G)               'Extraction technologies';
SET IGHOB(G)               'Heat-only boilers';
SET IGETOH(G)              'Electric heaters, heatpumps, electrolysis plants';
SET IGHSTO(G)              'Heat seasonal storage technologies';
SET IGESTO(G)              'Electricity seasonal storage technologies';
SET IGHYRS(G)              'Hydropower with reservoir';
SET IGHYRR(G)              'Hydropower run-of-river no reservoir';
SET IGWND(G)               'Wind power technologies';
SET IGSOLE(G)              'Solar electrical power technologies';
SET IGSOLH(G)              'Solar heat technologies';
SET IGHH(G)                'Technologies generating heat-only';
SET IGHHNOSTO(G)           'Technologies generating heat-only, except storage';
SET IGNOTETOH(G)           'Technologies excluding electric heaters, heat pumps,electrolysis plants';
SET IGKH(G)                'Technologies with capacity specified on heat';
SET IGKHNOSTO(G)           'Technologies with capacity specified on heat, except storage';
SET IGKE(G)                'Technologies with capacity specified on electricity';
SET IGKENOSTO(G)           'Technologies with capacity specified on electricity, except storage';
SET IGDISPATCH(G)          'Dispatchable technologies';
SET IGEE(G)                'Technologies generating electricity only';
SET IGEENOSTO(G)           'Technologies generating electricity only, except storage';
SET IGKKNOWN(G)            'Technoloies for which the capacity is specified by the user';
SET IGKFIND(G)             'Technologies for which the capacity is found by algorithm';
SET IGEH(G)                'Technologies generating electricity and heat';
SET IGE(G)                 'Technologies generating electricity';
SET IGH(G)                 'Technologies generating heat';

* The following sets are special, and may be deleted/changed in future versions.
SET IGNUC(G)               'Nuclear power technologies';
SET IG2LEVEL(G)            'Slowly regulating technologies, level change only between weekday/weekend';
SET IGEBASE(G)             'Power plants capable of supplying base load';
SET IGERES(G)              'Power plants capable of supplying short term reserve';
* The following sets concern combination technologies.

* The following discribes the main applications for the subsets:
*
* The sets:
* IGNUC,IGCND,IGBPR,IGEXT,IGHOB,IGETOH,IGHSTO,IGESTO,IGHYRS,IGHYRR,IGWND,IGSOLE,IGSOLH
* are directly extracted from GDATA(G,'GDTYPE') and are used to reference
* technology types.
*
* IGHH and IGEE are used in the balance equations and for output control.
*
* IGHHNOSTO and IGEENOSTO is not currently used for anything.
*
* IGNOTETOH is used for O&M cost in the objective function, in the balance
* equation, in heat storage balance equations and in various output functions.
*
* IGKH and IGKE are used for capacity restrictions and for certain output files.
*
* IGKHNOSTO and IGKENOSTO are used for output.
*
* IGDISPATCH is used capacity restrictions and output.
*
* IGKKNOWN is used to exclude investment options.
*
* IGKFIND is used to single out investment options.
*
* IGEH is used for CHP specific taxes.
*
* IGE and IGH are used all over.


* The sets are defined based on information in PARAMETER GDATA in the file tech.inc:


   IGCND(G)    = YES$((GDATA(G,'GDTYPE') EQ 1)  OR (GDATA(G,'GDTYPE') EQ GCND));
   IGBPR(G)    = YES$((GDATA(G,'GDTYPE') EQ 2)  OR (GDATA(G,'GDTYPE') EQ GBPR));
   IGEXT(G)    = YES$((GDATA(G,'GDTYPE') EQ 3)  OR (GDATA(G,'GDTYPE') EQ GEXT));
   IGHOB(G)    = YES$((GDATA(G,'GDTYPE') EQ 4)  OR (GDATA(G,'GDTYPE') EQ GHOB));
   IGETOH(G)   = YES$((GDATA(G,'GDTYPE') EQ 5)  OR (GDATA(G,'GDTYPE') EQ GETOH));
   IGHSTO(G)   = YES$((GDATA(G,'GDTYPE') EQ 6)  OR (GDATA(G,'GDTYPE') EQ GHSTO));
   IGESTO(G)   = YES$((GDATA(G,'GDTYPE') EQ 7)  OR (GDATA(G,'GDTYPE') EQ GESTO));
   IGHYRS(G)   = YES$((GDATA(G,'GDTYPE') EQ 8)  OR (GDATA(G,'GDTYPE') EQ GHYRS));
   IGHYRR(G)   = YES$((GDATA(G,'GDTYPE') EQ 9)  OR (GDATA(G,'GDTYPE') EQ GHYRR));
   IGWND(G)    = YES$((GDATA(G,'GDTYPE') EQ 10) OR (GDATA(G,'GDTYPE') EQ GWND));
   IGSOLE(G)   = YES$((GDATA(G,'GDTYPE') EQ 11) OR (GDATA(G,'GDTYPE') EQ GSOLE));
   IGSOLH(G)   = YES$(GDATA(G,'GDTYPE')  EQ GSOLH);

   IGHHNOSTO(G) = NO;   IGHHNOSTO(IGHOB)   = YES;  IGHHNOSTO(IGSOLH)= YES;

   IGHH(G)      =       IGHHNOSTO(G)
                         +IGHSTO(G);

   IGNOTETOH(G)= NOT IGETOH(G);

   IGDISPATCH(G)    =   IGCND(G)
                         +IGBPR(G)
                         +IGEXT(G)
                         +IGHOB(G)
                         +IGESTO(G)
                         +IGETOH(G)
                         +IGHYRS(G);

   IGEE(G)          =   IGCND(G)
                         +IGHYRS(G)
                         +IGHYRR(G)
                         +IGWND(G)
                         +IGSOLE(G)
                         +IGESTO(G);

   IGEENOSTO(G)     =   IGCND(G)
                         +IGHYRS(G)
                         +IGHYRR(G)
                         +IGWND(G)
                         +IGSOLE(G);

   IGKHNOSTO(G)     =   IGETOH(G)
                         +IGHHNOSTO(G);

   IGKH(G)          =     IGKHNOSTO(G)
                         +IGHSTO(G);

   IGKE(G)          =   IGCND(G)
                         +IGBPR(G)
                         +IGEXT(G)
                         +IGESTO(G)
                         +IGHYRS(G)
                         +IGHYRR(G)
                         +IGWND(G)
                         +IGSOLE(G);

   IGKENOSTO(G)     =   IGKE(G)
                         -IGESTO(G);

   IGKKNOWN(G) = YES$(GDATA(G,'GDKVARIABL') EQ 0);
   IGKFIND(G) = NOT IGKKNOWN(G);

   IGEH(G) = IGBPR(G)+IGEXT(G)+IGETOH(G);
   IGE(G)=IGEE(G)+IGEH(G);
   IGH(G)=IGHH(G)+IGEH(G);


* Rev.3.01: The following definitions are not standardised in Balmorel
* (and may be deleted/changed in future versions),
* the user must supply data and code as desired:
   IGNUC(G)    = YES$((GDATA(G,'GDFUEL') EQ 1) OR (GDATA(G,'GDFUEL') EQ NUCLEAR));
   IG2LEVEL(G) = IGNUC(G);
   IGEBASE(IGE)=YES$(((GDATA(IGE,'GDFUEL') = NATGAS) or (GDATA(IGE,'GDFUEL') = COAL) or (GDATA(IGE,'GDFUEL') = WOOD)) and (IGEXT(IGE) or IGCND(IGE)));
IGERES(G)=yes$(IGCND(G) or IGBPR(G) or IGEXT(G) or IGHYRS(G));
* End: Rev.3.01: The following definitions are not standardised in Balmorel.




*-------------------------------------------------------------------------------
*----- Any internal sets assignments for addon to be placed here: --------------
*-------------------------------------------------------------------------------
* NOTE: When making new generation technology types. Some add-ons may already
* be using values of GDATA(G,'GDTYPE'). Check addons referenced here to maximize
* consistency and avoid conflicts. It is encouraged to avoid using the '-' set
* operator and instead use the '+' operator for compound assignments.

$ifi %COMBTECH%==yes   SET IGCOMB1(G)              'Combination technologies, primary';
$ifi %COMBTECH%==yes   SET IGCOMB2(G)              'Combination technologies, secondary with primary in G';
$ifi %COMBTECH%==yes   SET GGCOMB(GGG,IGGGALIAS)   'Combination techologies in the same combination';
$ifi %COMBTECH%==yes   IGCOMB1(G) =no;
$ifi %COMBTECH%==yes   IGCOMB2(G) =no;
$ifi %COMBTECH%==yes   $include '../../base/addons/combtech/combGassign.inc';
*

$ifi %H2%==yes $include '../../base/addons/hydrogen/H2Gassign.inc';
*-------------------------------------------------------------------------------
*----- End: Any internal sets assignments for addon to be placed here ----------
*-------------------------------------------------------------------------------



*-------------------------------------------------------------------------------
*---- End: Technology data -----------------------------------------------------
*-------------------------------------------------------------------------------







*-------------------------------------------------------------------------------
*---- Annually specified generation capacities: --------------------------------
*-------------------------------------------------------------------------------

* Printing of data to the list file controlled by %ONOFFDATALISTING% and %ONOFFCODELISTING%:
%ONOFFDATALISTING%

PARAMETER GKFX(YYY,AAA,GGG)    'Capacity of existing generation technologies (MW)' %semislash%
$if     EXIST '../data/gkfx.inc' $INCLUDE      '../data/gkfx.inc';
$if not EXIST '../data/gkfx.inc' $INCLUDE '../../base/data/gkfx.inc';
%semislash%;

$ifi %MR%==yes $include '../../base/addons/gas/GKFX-MR.inc';



* Printing of data to the list file controlled by %ONOFFDATALISTING% and %ONOFFCODELISTING%:
%ONOFFCODELISTING%

*-------------------------------------------------------------------------------
*---- End: Annually specified generation capacities ----------------------------
*-------------------------------------------------------------------------------




*-------------------------------------------------------------------------------
*---- Geographically specific values: -----------------------------------------
*-------------------------------------------------------------------------------




PARAMETER YVALUE(YYY)                  'Numerical value of the years labels';
PARAMETER FDATA(FFF,FDATASET)          'Fuel specific values';
PARAMETER IRESDE(RRR)                  'Reserve requirements attributable to demand (%)';
PARAMETER IRESWI(RRR)                  'Reserve requirements attributable to wind';

PARAMETER FMAXINVEST(CCC,FFF)          'Maximum investment (MW) by fueltype for each year simulated';
PARAMETER GROWTHCAP(C,GGG)             'Maximum model generated capacity increase (MW) from one year to the next';

$ifi %loss%==212 PARAMETER DISLOSS_E(RRR)               'Loss in electricity distribution (fraction)';
$ifi %loss%==212 PARAMETER DISLOSS_H(AAA)               'Loss in heat distribution (fraction)';
$ifi %loss%==301 PARAMETER DISLOSS0E(RRR)               'Loss in electricity distribution (constant, UNIT?)';
$ifi %loss%==301 PARAMETER DISLOSS0H(AAA)               'Loss in heat distribution (constant, UNIT?)';
$ifi %loss%==301 PARAMETER DISLOSS1E(RRR)               'Loss in electricity distribution (fraction)';
$ifi %loss%==301 PARAMETER DISLOSS1H(AAA)               'Loss in heat distribution (fraction)';
PARAMETER DISCOST_E(RRR)               'Cost of electricity distribution (Money/MWh)';
PARAMETER DISCOST_H(AAA)               'Cost of heat distribution (Money/MWh)';
PARAMETER FKPOT(CCCRRRAAA,FFF)         'Fuel potential restriction by geography (MW)';
PARAMETER FGEMIN(CCCRRRAAA,FFF)        'Minimum electricity generation by fuel (MWh)';
PARAMETER FGEMAX(CCCRRRAAA,FFF)        'Maximum electricity generation by fuel (MWh)';
PARAMETER GMINF(CCCRRRAAA,FFF)         'Minimum fuel use (GJ) per year';
PARAMETER GMAXF(CCCRRRAAA,FFF)         'Maximum fuel use (GJ) per year';
PARAMETER GEQF(CCCRRRAAA,FFF)          'Required fuel use (GJ) per year';
PARAMETER WTRRSFLH(AAA)                'Full load hours for hydro reservoir plants (hours)';
PARAMETER WTRRRFLH(AAA)                'Full load hours for hydro run-of-river plants (hours)';
PARAMETER WNDFLH(AAA)                  'Full load hours for wind power (hours)';
PARAMETER SOLEFLH(AAA)                 'Full load hours for solarE power (hours)';
PARAMETER SOLHFLH(AAA)                 'Full load hours for solarH power (hours)';
PARAMETER HYRSDS(AAA,HYRSDATAS,SSS)    'Data for hydro with storage';
PARAMETER TAX_FHO(AAA,G)               'Fuel taxes on heat-only units';
PARAMETER TAX_FHO_C(FFF,CCC)           'Fuel taxes on heat-only units';
PARAMETER TAX_GH(AAA,G)                'Heat taxes on generation units';
PARAMETER TAX_FCHP_C(FFF,CCC)          'Fuel taxes on CHP units';
PARAMETER TAX_HHO_C(FFF,CCC)           'Fuel taxes on HO units';
PARAMETER TAX_F(FFF,CCC)               'Fuel taxes for heat and electricity production (Money/GJ)';
PARAMETER TAX_DE(CCC)                  'Consumers tax on electricity consumption (Money/MWh)';
PARAMETER TAX_DH(CCC)                  'Consumers tax on heat consumption (Money/MWh)';
PARAMETER ANNUITYC(CCC)                'Transforms investment to annual payment (fraction)';
PARAMETER GINVCOST(AAA,GGG)            'Investment cost for new technology (MMoney/MW)';
PARAMETER GOMVCOST(AAA,GGG)            'Variable operating and maintenance costs (Money/MWh)';
PARAMETER GOMFCOST(AAA,GGG)            'Annual fixed operating costs (kMoney/MW)';
PARAMETER GEFFDERATE(AAA,GGG)          'Reduction in fuel efficiency (fraction)';
PARAMETER DEFP_BASE(RRR)               'Nominal annual average consumer electricity price (Money/MWh)';
PARAMETER DHFP_BASE(AAA)               'Nominal annual average consumer heat price (Money/MWh)';



PARAMETER DE(YYY,RRR)                  'Annual electricity consumption (MWh)';
PARAMETER DH(YYY,AAA)                  'Annual heat consumption (MWh)';
*---- Transmission data: -------------------------------------------------------
PARAMETER XKINI(YYY,IRRRE,IRRRI)       'Initial transmission capacity between regions (MW)';
PARAMETER XINVCOST(IRRRE,IRRRI)        'Investment cost in new transmission capacity (Money/MW)';
PARAMETER XCOST(IRRRE,IRRRI)           'Transmission cost between regions (Money/MWh)';
$ifi %loss%==212 PARAMETER XLOSS(IRRRE,IRRRI)       'Transmission loss between regions (fraction)';
$ifi %loss%==310 PARAMETER XLOSS0(IRRRE,IRRRI)      'Transmission loss between regions (constant, UNIT?)';
$ifi %loss%==310 PARAMETER XLOSS1(IRRRE,IRRRI)      'Transmission loss between regions (fraction)';
PARAMETER XKDERATE(IRRRE,IRRRI)        'Transmission capacity derating (fraction)';
PARAMETER X3FX(YYY,RRR)                'Annual net electricity export to third regions';
$ifi %X3V%==yes PARAMETER X3VPIM(YYY,RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)    'Price (Money/MWh) of price dependent imported electricity';
$ifi %X3V%==yes PARAMETER X3VPEX(YYY,RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)    'Price (Money/MWh) of price dependent exported electricity';
$ifi %X3V%==yes PARAMETER X3VQIM(RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)        'Limit (MW) on price dependent electricity import';
$ifi %X3V%==yes PARAMETER X3VQEX(RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)        'Limit (MW) on price dependent electricity export';
* Fuel prices: -----------------------------------------------------------------

PARAMETER M_POL(YYY,MPOLSET,CCC)                   'Emission policy data';
*  Time:
PARAMETER WEIGHT_S(SSS)                            'Weight (relative length) of each season';
PARAMETER WEIGHT_T(TTT)                            'Weight (relative length) of each time period';

PARAMETER GKDERATE(AAA,GGG,SSS)                    'Reduction in capacity';
PARAMETER DE_VAR_T(RRR,SSS,TTT)                    'Variation in electricity demand';
PARAMETER DH_VAR_T(AAA,SSS,TTT)                    'Variation in heat demand';
PARAMETER WTRRSVAR_S(AAA,SSS)                      'Variation of the water inflow to reservoirs';
PARAMETER WTRRRVAR_T(AAA,SSS,TTT)                  'Variation of generation of hydro run-of-river';
PARAMETER WND_VAR_T(AAA,SSS,TTT)                   'Variation of the wind generation';
PARAMETER SOLE_VAR_T(AAA,SSS,TTT)                  'Variation of the solar generation';
PARAMETER X3FX_VAR_T(RRR,SSS,TTT)                  'Variation in fixed exchange with 3. region';
PARAMETER HYPPROFILS(AAA,SSS)                      'Hydro with storage seasonal price profile';
PARAMETER DEF_STEPS(RRR,SSS,TTT,DF_QP,DEF)         'Elastic electricity demands';
PARAMETER DEFP_CALIB(RRR,SSS,TTT)                  'Calibrate the price side of electricity demand';
PARAMETER DHF_STEPS(AAA,SSS,TTT,DF_QP,DHF)         'Elastic heat demands';
PARAMETER DHFP_CALIB(AAA,SSS,TTT)                  'Calibrate the price side of heat demand';

SCALAR PENALTYQ  'Penalty on violation of equation';



* Printing of data to the list file controlled by %ONOFFDATALISTING% and %ONOFFCODELISTING%:
%ONOFFDATALISTING%

PARAMETER YVALUE(YYY)   'Numerical value of the years labels'  %semislash%
$if     EXIST '../data/YVALUE.inc' $INCLUDE      '../data/YVALUE.inc';
$if not EXIST '../data/YVALUE.inc' $INCLUDE '../../base/data/YVALUE.inc';
%semislash%;

PARAMETER FDATA(FFF,FDATASET)    'Fuel specific values'  %semislash%
$if     EXIST '../data/FDATA.inc' $INCLUDE      '../data/FDATA.inc';
$if not EXIST '../data/FDATA.inc' $INCLUDE '../../base/data/FDATA.inc';
%semislash%;

$ifi not %BASELOADSERVICE%==yes $goto BASELOADSERVICE_label1

PARAMETER IRESDE(RRR)   'Reserve requirements attributable to demand (%)'  %semislash%
$if     EXIST '../data/IRESDE.inc' $INCLUDE      '../data/IRESDE.inc';
$if not EXIST '../data/IRESDE.inc' $INCLUDE '../../base/data/IRESDE.inc';
%semislash%;

PARAMETER IRESWI(RRR)   'Reserve requirements attributable to wind'      %semislash%
$if     EXIST '../data/IRESWI.inc' $INCLUDE      '../data/IRESWI.inc';
$if not EXIST '../data/IRESWI.inc' $INCLUDE '../../base/data/IRESWI.inc';
%semislash%;

PARAMETER FMAXINVEST(CCC,FFF)   'Maximum investment (MW) by fueltype for each year simulated'    %semislash%
$if     EXIST '../data/FMAXINVEST.inc' $INCLUDE      '../data/FMAXINVEST.inc';
$if not EXIST '../data/FMAXINVEST.inc' $INCLUDE '../../base/data/FMAXINVEST.inc';
%semislash%;
$label BASELOADSERVICE_label1

PARAMETER GROWTHCAP(C,GGG)    'Maximum model generated capacity increase (MW) from one year to the next'   %semislash%
$if     EXIST '../data/GROWTHCAP.inc' $INCLUDE      '../data/GROWTHCAP.inc';
$if not EXIST '../data/GROWTHCAP.inc' $INCLUDE '../../base/data/GROWTHCAP.inc';
%semislash%;

$ifi %loss%==310 $goto label_loss1
PARAMETER DISLOSS_E(RRR)    'Loss in electricity distribution (fraction)'   %semislash%
$if     EXIST '../data/DISLOSS_E.inc' $INCLUDE      '../data/DISLOSS_E.inc';
$if not EXIST '../data/DISLOSS_E.inc' $INCLUDE '../../base/data/DISLOSS_E.inc';
%semislash%;

PARAMETER DISLOSS_H(AAA)    'Loss in heat distribution (fraction)'  %semislash%
$if     EXIST '../data/DISLOSS_H.inc' $INCLUDE      '../data/DISLOSS_H.inc';
$if not EXIST '../data/DISLOSS_H.inc' $INCLUDE '../../base/data/DISLOSS_H.inc';
%semislash%;

$label label_loss1

$ifi %loss%==212 $goto label_loss2
PARAMETER DISLOSS0E(RRR)    'Loss in electricity distribution (constant, UNIT?)'   %semislash%
*$if     EXIST '../data/DISLOSS0E.inc' $INCLUDE          '../data/DISLOSS0E.inc';
*$if not EXIST '../data/DISLOSS0E.inc' $INCLUDE  '../../base/data/DISLOSS0E.inc';
%semislash%;

PARAMETER DISLOSS0H(AAA)    'Loss in heat distribution (constant, UNIT?)'  %semislash%
*$if     EXIST '../data/DISLOSS0H.inc' $INCLUDE         '../data/DISLOSS0H.inc';
*$if not EXIST '../data/DISLOSS0H.inc' $INCLUDE '../../base/data/DISLOSS0H.inc';
%semislash%;

PARAMETER DISLOSS1E(RRR)    'Loss in electricity distribution (fraction)'   %semislash%
$if     EXIST '../data/DISLOSS1E.inc' $INCLUDE         '../data/DISLOSS1E.inc';
$if not EXIST '../data/DISLOSS1E.inc' $INCLUDE '../../base/data/DISLOSS1E.inc';
%semislash%;

PARAMETER DISLOSS1H(AAA)    'Loss in heat distribution (fraction)'  %semislash%
$if     EXIST '../data/DISLOSS1H.inc' $INCLUDE         '../data/DISLOSS1H.inc';
$if not EXIST '../data/DISLOSS1H.inc' $INCLUDE '../../base/data/DISLOSS1H.inc';
%semislash%;

$label label_loss2


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


PARAMETER FGEMIN(CCCRRRAAA,FFF)    'Minimum electricity generation by fuel (MWh)'  %semislash%
$if     EXIST '../data/FGEMIN.inc' $INCLUDE      '../data/FGEMIN.inc';
$if not EXIST '../data/FGEMIN.inc' $INCLUDE '../../base/data/FGEMIN.inc';
%semislash%;

PARAMETER FGEMAX(CCCRRRAAA,FFF)     'Maximum electricity generation by fuel (MWh)'   %semislash%
$if     EXIST '../data/FGEMAX.inc' $INCLUDE      '../data/FGEMAX.inc';
$if not EXIST '../data/FGEMAX.inc' $INCLUDE '../../base/data/FGEMAX.inc';
%semislash%;

PARAMETER GMINF(CCCRRRAAA,FFF)   'Minimum fuel use (GJ) per year'    %semislash%
$if     EXIST '../data/GMINF.inc' $INCLUDE      '../data/GMINF.inc';
$if not EXIST '../data/GMINF.inc' $INCLUDE '../../base/data/GMINF.inc';
%semislash%;

PARAMETER GMAXF(CCCRRRAAA,FFF)    'Maximum fuel use (GJ) per year'       %semislash%
$if     EXIST '../data/GMAXF.inc' $INCLUDE      '../data/GMAXF.inc';
$if not EXIST '../data/GMAXF.inc' $INCLUDE '../../base/data/GMAXF.inc';
%semislash%;

PARAMETER GEQF(CCCRRRAAA,FFF)    'Required fuel use (GJ) per year'  %semislash%
$if     EXIST '../data/GEQF.inc' $INCLUDE      '../data/GEQF.inc';
$if not EXIST '../data/GEQF.inc' $INCLUDE '../../base/data/GEQF.inc';
%semislash%;

* Maximum capacity at new technologies
PARAMETER GKNMAX(YYY,AAA,GGG)   'Maximum capacity at new technologies (MW)'  %semislash%
$if     EXIST '../data/GKNMAX.inc' $INCLUDE      '../data/GKNMAX.inc';
$if not EXIST '../data/GKNMAX.inc' $INCLUDE '../../base/data/GKNMAX.inc';
%semislash%;


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


PARAMETER HYRSDS(AAA,HYRSDATAS,SSS)    'Data for hydro with storage'  %semislash%
$if     EXIST '../data/HYRSDS.inc' $INCLUDE      '../data/HYRSDS.inc';
$if not EXIST '../data/HYRSDS.inc' $INCLUDE '../../base/data/HYRSDS.inc';
%semislash%;

PARAMETER TAX_F(FFF,CCC)   'Fuel taxes for heat and electricity production (Money/GJ)'  %semislash%
$if     EXIST '../data/TAX_F.inc' $INCLUDE      '../data/TAX_F.inc';
$if not EXIST '../data/TAX_F.inc' $INCLUDE '../../base/data/TAX_F.inc';
%semislash%;

PARAMETER TAX_DE(CCC)    'Consumers tax on electricity consumption (Money/MWh)'  %semislash%
$if     EXIST '../data/TAX_DE.inc' $INCLUDE      '../data/TAX_DE.inc';
$if not EXIST '../data/TAX_DE.inc' $INCLUDE '../../base/data/TAX_DE.inc';
%semislash%;

PARAMETER TAX_DH(CCC)    'Consumers tax on heat consumption (Money/MWh)'  %semislash%
$if     EXIST '../data/TAX_DH.inc' $INCLUDE      '../data/TAX_DH.inc';
$if not EXIST '../data/TAX_DH.inc' $INCLUDE '../../base/data/TAX_DH.inc';
%semislash%;



PARAMETER ANNUITYC(CCC)   'Transforms investment to annual payment (fraction)'  %semislash%
$if     EXIST '../data/ANNUITYC.inc' $INCLUDE         '../data/ANNUITYC.inc';
$if not EXIST '../data/ANNUITYC.inc' $INCLUDE '../../base/data/ANNUITYC.inc';
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

PARAMETER GEFFDERATE(AAA,GGG)    'Reduction in fuel efficiency (fraction)'  %semislash%
$if     EXIST '../data/GEFFDERATE.inc' $INCLUDE         '../data/GEFFDERATE.inc';
$if not EXIST '../data/GEFFDERATE.inc' $INCLUDE '../../base/data/GEFFDERATE.inc';
%semislash%;

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
PARAMETER DE(YYY,RRR)    'Annual electricity consumption (MWh)' %semislash%
$if     EXIST '../data/de.inc' $INCLUDE         '../data/de.inc';
$if not EXIST '../data/de.inc' $INCLUDE '../../base/data/de.inc';
%semislash%;


*-------------------------------------------------------------------------------
*---- Annual heat demand: -----------------------------------------------------
*-------------------------------------------------------------------------------
PARAMETER DH(YYY,AAA)    'Annual heat consumption (MWh)'  %semislash%
$if     EXIST '../data/dh.inc' $INCLUDE         '../data/dh.inc';
$if not EXIST '../data/dh.inc' $INCLUDE '../../base/data/dh.inc';
%semislash%;



*-------------------------------------------------------------------------------
*---- Transmission data: ------------------------------------------------------
*-------------------------------------------------------------------------------

PARAMETER XKINI(YYY,IRRRE,IRRRI)  'Initial transmission capacity between regions (MW)'   %semislash%
$if     EXIST '../data/XKINI.inc' $INCLUDE      '../data/XKINI.inc';
$if not EXIST '../data/XKINI.inc' $INCLUDE '../../base/data/XKINI.inc';
%semislash%;

PARAMETER XINVCOST(IRRRE,IRRRI)   'Investment cost in new transmission capacity (Money/MW)'    %semislash%
$if     EXIST '../data/XINVCOST.inc' $INCLUDE      '../data/XINVCOST.inc';
$if not EXIST '../data/XINVCOST.inc' $INCLUDE '../../base/data/XINVCOST.inc';
%semislash%;

PARAMETER XCOST(IRRRE,IRRRI)      'Transmission cost between regions (Money/MWh)'   %semislash%
$if     EXIST '../data/XCOST.inc' $INCLUDE      '../data/XCOST.inc';
$if not EXIST '../data/XCOST.inc' $INCLUDE '../../base/data/XCOST.inc';
%semislash%;

$ifi %loss%==310 $goto label_loss3
PARAMETER XLOSS(IRRRE,IRRRI)      'Transmission loss between regions (fraction)'  %semislash%
$if     EXIST '../data/XLOSS.inc' $INCLUDE         '../data/XLOSS.inc';
$if not EXIST '../data/XLOSS.inc' $INCLUDE '../../base/data/XLOSS.inc';
%semislash%;
$label label_loss3

$ifi %loss%==212 $goto label_loss4
PARAMETER XLOSS0(IRRRE,IRRRI)      'Transmission loss between regions (fraction)'  %semislash%
$if     EXIST '../data/XLOSS0.inc' $INCLUDE         '../data/XLOSS0.inc';
*$if not EXIST '../data/XLOSS0.inc' $INCLUDE '../../base/data/XLOSS0.inc';
%semislash%;

PARAMETER XLOSS1(IRRRE,IRRRI)      'Transmission loss between regions (fraction)'  %semislash%
$if     EXIST '../data/XLOSS1.inc' $INCLUDE         '../data/XLOSS1.inc';
$if not EXIST '../data/XLOSS1.inc' $INCLUDE '../../base/data/XLOSS1.inc';
%semislash%;

$label label_loss4

PARAMETER XKDERATE(IRRRE,IRRRI)   'Transmission capacity derating (fraction)'  %semislash%
$if     EXIST '../data/XKDERATE.inc' $INCLUDE      '../data/XKDERATE.inc';
$if not EXIST '../data/XKDERATE.inc' $INCLUDE '../../base/data/XKDERATE.inc';
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
$if     EXIST '../data/m_pol.inc' $INCLUDE         '../data/m_pol.inc';
$if not EXIST '../data/m_pol.inc' $INCLUDE '../../base/data/m_pol.inc';
%semislash%;

*-------------------------------------------------------------------------------
*---- Seasonal and daily variations: ------------------------------------------
*-------------------------------------------------------------------------------


* DISSE FILER INDHOLDER NaSTEN ALLESAMMEN KODE, CONDITIONALS, ETC! Skal revideres!

PARAMETER WEIGHT_S(SSS)                            'Weight (relative length) of each season'    %semislash%
$if     EXIST '../data/WEIGHT_S.inc' $INCLUDE      '../data/WEIGHT_S.inc';
$if not EXIST '../data/WEIGHT_S.inc' $INCLUDE '../../base/data/WEIGHT_S.inc';
%semislash%;

PARAMETER WEIGHT_T(TTT)                            'Weight (relative length) of each time period'   %semislash%
$if     EXIST '../data/WEIGHT_T.inc' $INCLUDE      '../data/WEIGHT_T.inc';
$if not EXIST '../data/WEIGHT_T.inc' $INCLUDE '../../base/data/WEIGHT_T.inc';
%semislash%;

PARAMETER CYCLESINS(SSS)   'Number of load cycles per season '   %semislash%
$if     EXIST '../data/CYCLESINS.inc' $INCLUDE      '../data/CYCLESINS.inc';
$if not EXIST '../data/CYCLESINS.inc' $INCLUDE '../../base/data/CYCLESINS.inc';
%semislash%;

PARAMETER GKDERATE(AAA,GGG,SSS)                    'Reduction in capacity'   %semislash%
$if     EXIST '../data/GKDERATE.inc' $INCLUDE      '../data/GKDERATE.inc';
$if not EXIST '../data/GKDERATE.inc' $INCLUDE '../../base/data/GKDERATE.inc';
%semislash%;

PARAMETER DE_VAR_T(RRR,SSS,TTT)                    'Variation in electricity demand'   %semislash%
$if     EXIST '../data/DE_VAR_T.inc' $INCLUDE      '../data/DE_VAR_T.inc';
$if not EXIST '../data/DE_VAR_T.inc' $INCLUDE '../../base/data/DE_VAR_T.inc';
%semislash%;

PARAMETER DH_VAR_T(AAA,SSS,TTT)                    'Variation in heat demand'   %semislash%
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


PARAMETER X3FX_VAR_T(RRR,SSS,TTT)                  'Variation in fixed exchange with 3. region'   %semislash%
$if     EXIST '../data/X3FX_VAR_T.inc' $INCLUDE      '../data/X3FX_VAR_T.inc';
$if not EXIST '../data/X3FX_VAR_T.inc' $INCLUDE '../../base/data/X3FX_VAR_T.inc';
%semislash%;

PARAMETER HYPPROFILS(AAA,SSS)                      'Hydro with storage seasonal price profile'   %semislash%
$if     EXIST '../data/HYPPROFILS.inc' $INCLUDE      '../data/HYPPROFILS.inc';
$if not EXIST '../data/HYPPROFILS.inc' $INCLUDE '../../base/data/HYPPROFILS.inc';
%semislash%;

PARAMETER DEF_STEPS(RRR,SSS,TTT,DF_QP,DEF)         'Elastic electricity demands'   %semislash%
$if     EXIST '../data/DEF_STEPS.inc' $INCLUDE      '../data/DEF_STEPS.inc';
$if not EXIST '../data/DEF_STEPS.inc' $INCLUDE '../../base/data/DEF_STEPS.inc';
%semislash%;

PARAMETER DEFP_CALIB(RRR,SSS,TTT)                  'Calibrate the price side of electricity demand'   %semislash%
$if     EXIST '../data/DEFP_CALIB.inc' $INCLUDE      '../data/DEFP_CALIB.inc';
$if not EXIST '../data/DEFP_CALIB.inc' $INCLUDE '../../base/data/DEFP_CALIB.inc';
%semislash%;

PARAMETER DHF_STEPS(AAA,SSS,TTT,DF_QP,DHF)         'Elastic heat demands'   %semislash%
$if     EXIST '../data/DHF_STEPS.inc' $INCLUDE      '../data/DHF_STEPS.inc';
$if not EXIST '../data/DHF_STEPS.inc' $INCLUDE '../../base/data/DHF_STEPS.inc';
%semislash%;

PARAMETER DHFP_CALIB(AAA,SSS,TTT)                  'Calibrate the price side of heat demand'   %semislash%
$if     EXIST '../data/DHFP_CALIB.inc' $INCLUDE      '../data/DHFP_CALIB.inc';
$if not EXIST '../data/DHFP_CALIB.inc' $INCLUDE '../../base/data/DHFP_CALIB.inc';
%semislash%;


$ifi %bb3%==yes WEIGHT_T(T)=1;


* Printing of data to the list file controlled by %ONOFFDATALISTING% and %ONOFFCODELISTING%:
%ONOFFCODELISTING%

*-------------------------------------------------------------------------------
*---- Investments: --------------------------------------------------------------
*-------------------------------------------------------------------------------

* LARS: Investments made in BB2 are loaded automatically in non BB2 simulations
* conditioned by the ADDINVEST global variable (see balopt.opt).
* The parameter declaration is not conditional as it is used also when saving
* investments in a BB2 simulation conditioned by the MAKEINVEST global variable.

PARAMETER GKVACCDECOM(Y,AAA,G)   'Investments in generation technology by BB2 up to and including year Y with subtraction of decommisioning';
PARAMETER GKVACC(Y,AAA,G)        'Investments in generation technology by BB2 up to and including year Y without subtraction of decommisioning';
PARAMETER GVKGN(YYY,AAA,G)       'Investments in generation technology by BB2 in year Y';
PARAMETER XKACC(Y,IRRRE,IRRRI)   'Investments in electricity transmission by BB2 up to and including year Y';

$ifi %ADDINVEST%==yes execute_load '../../base/data/GKVACCDECOM.gdx', GKVACCDECOM;
$ifi %ADDINVEST%==yes execute_load '../../base/data/GKVACC.gdx', GKVACC;
$ifi %ADDINVEST%==yes execute_load '../../base/data/GVKGN.gdx', GVKGN;
$ifi %ADDINVEST%==yes execute_load '../../base/data/XKACC.gdx', XKACC;



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

* Include a case identification, if it exists.
* Note: the scalar OCASEID must not be declared here, only in an included file,
* or, if not found, in print1.inc; therefore this $include must come before $include of print1.inc.
* If using BUI, the file '../data/OCASEID.inc' will be provided by BUI.
$if     EXIST '../data/OCASEID.inc' $INCLUDE      '../data/OCASEID.inc';


*-------------------------------------------------------------------------------
*----- Any parameters for addon to be placed here: -----------------------------
*-------------------------------------------------------------------------------
* These add-on data pertain to natural gas.
$ifi %GAS%==yes $INCLUDE '../../base/addons/gas/gasdata.inc';
$ifi %CAES%==yes $INCLUDE '../../base/addons/CAES/CAESdata.inc';
$ifi %X3V%==yes $INCLUDE '../../base/addons/x3v/data/x3vdata.inc';
$ifi %H2%==yes $INCLUDE '../../base/addons/Hydrogen/H2data.inc';
$ifi %NAP%==yes $INCLUDE '../../base/addons/NAP/NAPdata.inc';
* These add-on data pertain to transport technology(KHED).
$ifi %TSP%==yes  $INCLUDE '../../base/addons/Transport/TSPParameters.inc';
$ifi %HEATTRANS%==yes $INCLUDE '../../base/addons/heattrans/data/htrans.inc';
* This file (if exists) contains:
* PARAMETER XHKINI(IAAAE,IAAAI)    'Initial heat transmission capacity between regions'
* PARAMETER XHINVCOST(IAAAE,IAAAI) 'Investment cost in new heat transmission cap'
* PARAMETER XHCOST(IAAAE,IAAAI)    'Heat transmission cost between countries'
* PARAMETER XHLOSS(IAAAE,IAAAI)    'Heat transmission loss between regions'


* Printing of data to the list file controlled by %ONOFFDATALISTING% and %ONOFFCODELISTING%:
%ONOFFDATALISTING%
PARAMETER HYFXRW(YYY,RRR,SSS)      'Water quantity to be transferred to model Balbase3 (MWh)';
$ifi %bb3%==yes execute_load '../../base/data/HYFXRW.gdx', HYFXRW;
PARAMETER WATERVAL(YYY,AAA,SSS)    'Water value (price) to be transferred to model Balbase3 (Money/MWh)';
$ifi %bb3%==yes execute_load '../../base/data/WATERVAL.gdx', WATERVAL;

SCALAR PENALTYQ  'Penalty on violation of equation'  %semislash%
$if     EXIST '../data/PENALTYQ.inc' $INCLUDE      '../data/PENALTYQ.inc';
$if not EXIST '../data/PENALTYQ.inc' $INCLUDE '../../base/data/PENALTYQ.inc';
%semislash%;

* Printing of data to the list file controlled by %ONOFFDATALISTING% and %ONOFFCODELISTING%:
%ONOFFCODELISTING%


*-------------------------------------------------------------------------------
*----- End: Any parameters for addon to be placed here -------------------------
*-------------------------------------------------------------------------------


*-------------------------------------------------------------------------------
* End: Declaration and definition of numerical data: PARAMETERS and SCALARS
*-------------------------------------------------------------------------------



*-------------------------------------------------------------------------------
* Declaration and definition of internal sets, aliases and parameters:
*-------------------------------------------------------------------------------


* Aliases relative to time:
ALIAS (Y,IYALIAS);

ALIAS (S,ISALIAS);
ALIAS (T,ITALIAS);


PARAMETER IGKFXYMAX(AAA,G) "The maximum over years in Y of exogenously specified capacity (MW)" ;

* Aliases relative to fuel:
ALIAS (FFF,IFFFALIAS);


* Internal sets and aliases in relation to geography.
* Note: although it is possible, you should generally not (i.e., don't!) use
* the following internal sets for data entry or data assignments
* (it may be impossible in future versions).
SET IR(RRR)            'Regions in the simulation';
SET IA(AAA)            'Areas in the simulation';
SET ICA(CCC,AAA)       'Assignment of areas to countries in the simulation';
ALIAS (IR,IRE,IRI);
ALIAS (IA,IAE,IAI);

* The simple way to limit the geographical scope of the model is to specify in the input data
* the set C as a proper subset of the set CCC,
* because the following mechanism will automatically exclude all regions
* and areas not in any country in C.
ICA(CCC,AAA) = YES$(SUM(RRR$ (RRRAAA(RRR,AAA) AND CCCRRR(CCC,RRR)),1) GT 0);
IR(RRR) = YES$(SUM(C,CCCRRR(C,RRR)));
IA(AAA) = YES$(SUM(C,ICA(C,AAA)));


*-------------------------------------------------------------------------------
* Application of default data:
*-------------------------------------------------------------------------------

* GOMVCOST, GOMFCOST and GINVCOST are given the default values in GDATA unless otherwise specified in data file:
GOMVCOST(IA,G)$((NOT GOMVCOST(IA,G)) AND (SUM(Y,GKFX(Y,IA,G)) OR AGKN(IA,G))) = GDATA(G,'GDOMVCOST0');
GOMFCOST(IA,G)$((NOT GOMFCOST(IA,G)) AND (SUM(Y,GKFX(Y,IA,G)) OR AGKN(IA,G))) = GDATA(G,'GDOMFCOST0');
GINVCOST(IA,G)$((NOT GINVCOST(IA,G)) AND (SUM(Y,GKFX(Y,IA,G)) OR AGKN(IA,G))) = GDATA(G,'GDINVCOST0');

*-------------------------------------------------------------------------------
* End of: Application of default data
*-------------------------------------------------------------------------------


* Time aggregation:
$ifi %timeaggr%==yes  $include '../../base/model/timeaggr.inc';

* This file contains initialisations of printing of log and error messages:
$INCLUDE '../../base/logerror/logerinc/error1.inc';



* --- Internal sets in relation to time: ---------------------------------------
SET IS3(S)   'Present season simulated in balbase3';
ALIAS(S,IS3LOOPSET);

* The following relates technology and fuel:
SET IGF(GGG,FFF)   'Relation between technology type and fuel type';

* Internal scalars:

* Convenient Factors, typically relating Output and Input:
SCALAR IOF1000    'Multiplier 1000'       /1000/;
SCALAR IOF1000000 'Multiplier 1000000'    /1000000/;
SCALAR IOF0001    'Multiplier 0.001'      /0.001/;
SCALAR IOF0000001 'Multiplier 0.000001'   /0.000001/;
SCALAR IOF3P6     'Multiplier 3.6'        /3.6/;
SCALAR IOF24      'Multiplier 24'         /24/;
SCALAR IOF8760    'Multiplier 8760'       /8760/;
SCALAR IOF8784    'Multiplier 8784'       /8784/;
SCALAR IOF365     'Multiplier 365'        /365/;
SCALAR IOF05      'Multiplier 0.5'        /0.5/;
SCALAR IOF1_      'Multiplier 1 (special, to disappear in future versions'  /1/;
* Scalars for occational use, their meaning will be context dependent :
SCALAR ISCALAR1 '(Context dependent)';
SCALAR ISCALAR2 '(Context dependent)';
SCALAR ISCALAR3 '(Context dependent)';
SCALAR ISCALAR4 '(Context dependent)';

*------------------------------------------------------------------------------
* Internal sets:


SET IAGK_Y(AAA,G)        'Area, technology with positive capacity current simulation year';
SET IXKN(IRRRE,IRRRI)   'Pair of regions that may get new transmission capacity';

* Specification of where new endogenous generation capacity may be located:

SET IAGKN(AAA,G)     'Area, technology where technology may be invested based on AGKN and implicit constraints ';
* Initialisation: equal to AGKN:
IAGKN(IA,G)=AGKN(IA,G);

* No investment in secondary combination technologies:
$ifi %COMBTECH%==yes    IAGKN(IA,IGCOMB2)=NO;

SET IPLUSMINUS "Violation of equation"  /IPLUS Violation of equation upwards, IMINUS  Violation of equation downwards/;
* Note: When placed on the left hand side of the equation
* the sign to the IMINUS and IPLUS terms should be - and +, respectively.
* This way the sign and the name will be intuitively consistent in equation listings.


*------------------------------------------------------------------------------
* Internal parameters and settings:
*------------------------------------------------------------------------------


* Set GDCV value to one for IGBPR and IGHOB units so that their fuel consumption
* can be found using the same formula as for IGCND and IGEXT:
GDATA(IGBPR,'GDCV') = 1;
GDATA(IGHOB,'GDCV') = 1;

* Specifying the relation between technology type and fuel type in IGF:

IGF(G,FFF)=YES$(GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDNB'));   /* This assignent line may in future versions become invalid, only fuels Acronyms will remain supported. */
IGF(G,FFF)$(GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))=YES;

* The following parameters contain information about CO2 and SO2 emission
* from technology G based on the fuel used and its emission data:

PARAMETER   IM_CO2(G)  'CO2 emission coefficient for fuel';
PARAMETER   IM_SO2(G)  'SO2 emission coefficient for fuel';
PARAMETER   IM_N2O(G)  'NO2 emission coefficient for fuel';

LOOP(FFF,
     IM_CO2(G)$IGF(G,FFF) = FDATA(FFF,'FDCO2');
     IM_SO2(G)$IGF(G,FFF) =
             FDATA(FFF,'FDSO2')$(GDATA(G,'GDDESO2') EQ 0) +
            (FDATA(FFF,'FDSO2')*(1-GDATA(G,'GDDESO2')))$(GDATA(G,'GDDESO2') GT 0);
     IM_N2O(G)$IGF(G,FFF) = FDATA(FFF,'FDN2O');
    );



* Further declarations relative to variations:
* Parameters holding the total weight in the (arbitrary) units of the weights
* used in input for each season and time period.
* To be used in calculations below.


PARAMETER IWEIGHSUMS          'Weight of the time of each season in S';
PARAMETER IWEIGHSUMT          'Weight of the time of each time period in T ';

* The (arbitrary) units used in the input are converted to days and hours,
* respectively. Note that IHOURSIN24 is given in hours.

PARAMETER IDAYSIN_S(SSS)      'Days in each season';         /* Note: to disappear in later versions, do not use */
PARAMETER IHOURSIN24(T)       'Hours in each time segment';  /* Note: to disappear in later versions, do not use */

PARAMETER IHOURSINST(SSS,T)   'Length of time segment (hours)';

* Annual amounts as expressed in the units of the weights and demands used
* in input in the file var.inc:

PARAMETER IDE_SUMST(RRR)      'Annual amount of electricity demand';
PARAMETER IDH_SUMST(AAA)      'Annual amount of heat demand';
PARAMETER IX3FXSUMST(RRR)     'Annual amount of electricity exported to third countries';

* Sums for finding the wind and solar generated electricity generation
* as expressed in the units of the weights and demands used in input:

PARAMETER IWND_SUMST(AAA)  'Annual amount of wind generated electricity';
PARAMETER ISOLESUMST(AAA)  'Annual amount of solar generated electricity';
PARAMETER ISOLHSUMST(AAA)  'Annual amount of solar generated heat';
PARAMETER IWTRRSSUM(AAA)   'Annual amount of hydro from reservoirs generated electricity';
PARAMETER IWTRRRSUM(AAA)   'Annual amount of hydro-run-of-river generated electricity';

*-------------------------------------------------------------------------------
* Set the time weights depending on the model:
*-------------------------------------------------------------------------------
* To guard against division-by-zero and other errors make sure that the following sums do not have inappropriate values:
$ifi %BB1%==yes    IWEIGHSUMS = SUM(S, WEIGHT_S(S));
$ifi %BB1%==yes    IWEIGHSUMT = SUM(T, WEIGHT_T(T));
$ifi %BB1%==yes    IDAYSIN_S(S)  = IOF365*WEIGHT_S(S) / IWEIGHSUMS;
$ifi %BB1%==yes    IHOURSIN24(T) = IOF24* WEIGHT_T(T) / IWEIGHSUMT;
$ifi %BB1%==yes    IHOURSINST(S,T)=IDAYSIN_S(S)*IHOURSIN24(T);
$ifi %BB1%==yes    IDE_SUMST(IR) = SUM((S,T), IHOURSINST(S,T)*DE_VAR_T(IR,S,T));
$ifi %BB1%==yes    IDH_SUMST(IA) = SUM((S,T), IHOURSINST(S,T)*DH_VAR_T(IA,S,T));
$ifi %BB1%==yes    IX3FXSUMST(IR) = SUM((S,T), IHOURSINST(S,T)*X3FX_VAR_T(IR,S,T));
$ifi %BB1%==yes    IWND_SUMST(IA)=SUM((S,T), IHOURSINST(S,T)*WND_VAR_T(IA,S,T));
$ifi %BB1%==yes    ISOLESUMST(IA)=SUM((S,T), IHOURSINST(S,T)*SOLE_VAR_T(IA,S,T));
$ifi %BB1%==yes    ISOLHSUMST(IA)=SUM((S,T), IHOURSINST(S,T)*SOLH_VAR_T(IA,S,T));
$ifi %BB1%==yes    IWTRRRSUM(IA)=SUM((S,T), IHOURSINST(S,T)*WTRRRVAR_T(IA,S,T));
$ifi %BB1%==yes    IWTRRSSUM(IA)=SUM(S, IDAYSIN_S(S) * WTRRSVAR_S(IA,S));

$ifi %BB2%==yes    IWEIGHSUMS = SUM(S, WEIGHT_S(S));
$ifi %BB2%==yes    IWEIGHSUMT = SUM(T, WEIGHT_T(T));
$ifi %BB2%==yes    IDAYSIN_S(S)  = IOF365*WEIGHT_S(S) / IWEIGHSUMS;
$ifi %BB2%==yes    IHOURSIN24(T) = IOF24* WEIGHT_T(T) / IWEIGHSUMT;
$ifi %BB2%==yes    IHOURSINST(S,T)=IDAYSIN_S(S)*IHOURSIN24(T);
$ifi %BB2%==yes    IDE_SUMST(IR) = SUM((S,T), IHOURSINST(S,T)*DE_VAR_T(IR,S,T));
$ifi %BB2%==yes    IDH_SUMST(IA) = SUM((S,T), IHOURSINST(S,T)*DH_VAR_T(IA,S,T));
$ifi %BB2%==yes    IX3FXSUMST(IR) = SUM((S,T), IHOURSINST(S,T)*X3FX_VAR_T(IR,S,T));
$ifi %BB2%==yes    IWND_SUMST(IA)=SUM((S,T), IHOURSINST(S,T)*WND_VAR_T(IA,S,T));
$ifi %BB2%==yes    ISOLESUMST(IA)=SUM((S,T), IHOURSINST(S,T)*SOLE_VAR_T(IA,S,T));
$ifi %BB2%==yes    ISOLHSUMST(IA)=SUM((S,T), IHOURSINST(S,T)*SOLH_VAR_T(IA,S,T));
$ifi %BB2%==yes    IWTRRRSUM(IA)=SUM((S,T), IHOURSINST(S,T)*WTRRRVAR_T(IA,S,T));
$ifi %BB2%==yes    IWTRRSSUM(IA)=SUM(S, IDAYSIN_S(S) * WTRRSVAR_S(IA,S));

$ifi %BB3%==yes    IWEIGHSUMS = SUM(SSS, WEIGHT_S(SSS));
$ifi %BB3%==yes    IWEIGHSUMT = SUM(T, WEIGHT_T(T));
$ifi %BB3%==yes    IDAYSIN_S(SSS)  = IOF365*WEIGHT_S(SSS) / IWEIGHSUMS;
$ifi %BB3%==yes    IHOURSIN24(T) = IOF24* WEIGHT_T(T) / IWEIGHSUMT;
$ifi %BB3%==yes    IHOURSINST(SSS,T)=IDAYSIN_S(SSS)*IHOURSIN24(T);
$ifi %BB3%==yes    IDE_SUMST(IR) = SUM((SSS,T), IHOURSINST(SSS,T)*DE_VAR_T(IR,SSS,T));
$ifi %BB3%==yes    IDH_SUMST(IA) = SUM((SSS,T), IHOURSINST(SSS,T)*DH_VAR_T(IA,SSS,T));
$ifi %BB3%==yes    IX3FXSUMST(IR) = SUM((SSS,T), IHOURSINST(SSS,T)*X3FX_VAR_T(IR,SSS,T));
$ifi %BB3%==yes    IWND_SUMST(IA)=SUM((SSS,T), IHOURSINST(SSS,T)*WND_VAR_T(IA,SSS,T));
$ifi %BB3%==yes    ISOLESUMST(IA)=SUM((SSS,T), IHOURSINST(SSS,T)*SOLE_VAR_T(IA,SSS,T));
$ifi %BB3%==yes    ISOLHSUMST(IA)=SUM((SSS,T), IHOURSINST(SSS,T)*SOLH_VAR_T(IA,SSS,T));
$ifi %BB3%==yes    IWTRRRSUM(IA)=SUM((SSS,T), IHOURSINST(SSS,T)*WTRRRVAR_T(IA,SSS,T));
$ifi %BB3%==yes    IWTRRSSUM(IA)=SUM(SSS, IDAYSIN_S(SSS) * WTRRSVAR_S(IA,SSS));




*-------------------------------------------------------------------------------
* End of: Set the time weights depending on the model
*-------------------------------------------------------------------------------


* PARAMETER IDEFP_T holds the price levels of individual steps
* in the electricity demand function, transformed to be comparable with
* production costs (including fuel taxes) by subtraction of taxes
* and distribution costs.

* Unit: Money/MWh.


PARAMETER IDEFP_T(RRR,SSS,TTT,DEF)    'Prices on elastic electricity demand steps (Money/MWh)';

IDEFP_T(IR,S,T,DEF_D1) = DEF_STEPS(IR,S,T,'DF_PRICE',DEF_D1)*
DEFP_BASE(IR)
- SUM(C$CCCRRR(C,IR),TAX_DE(C)) - DISCOST_E(IR) + DEFP_CALIB(IR,S,T);

IDEFP_T(IR,S,T,DEF_U1) = DEF_STEPS(IR,S,T,'DF_PRICE',DEF_U1)*
DEFP_BASE(IR)
- SUM(C$CCCRRR(C,IR),TAX_DE(C)) - DISCOST_E(IR) + DEFP_CALIB(IR,S,T);

IDEFP_T(IR,S,T,DEF_D2) = DEF_STEPS(IR,S,T,'DF_PRICE',DEF_D2);

IDEFP_T(IR,S,T,DEF_U2) = DEF_STEPS(IR,S,T,'DF_PRICE',DEF_U2);

IDEFP_T(IR,S,T,DEF_D3) = DEF_STEPS(IR,S,T,'DF_PRICE',DEF_D3);

IDEFP_T(IR,S,T,DEF_U3) = DEF_STEPS(IR,S,T,'DF_PRICE',DEF_U3);

* PARAMETER IDHFP_T holds the price levels of individual steps
* in the electricity demand function, transformed to be comparable with
* production costs (including fuel taxes) by subtraction of consumer taxes
* and distribution costs.

* Unit: Money/MWh.


PARAMETER IDHFP_T(AAA,SSS,TTT,DHF)   'Prices on elastic heat demand steps (Money/MWh)';

IDHFP_T(IA,S,T,DHF)=   DHF_STEPS(IA,S,T,'DF_PRICE',DHF)*
DHFP_BASE(IA)
- SUM(C$ICA(C,IA),TAX_DH(C)) -DISCOST_H(IA) + DHFP_CALIB(IA,S,T);


* Demand of electricity (MW) and heat (MW) current simulation year:
PARAMETER IDE_T_Y(RRR,S,T)         'Electricity demand (MW) time segment (S,T)   current simulation year',
          IDH_T_Y(AAA,S,T)      'Heat demand (MW) time segment (S,T) current simulation year';
* Generation capacity (MW) at the beginning of current simulation year,
* specified by GKFX and by accumulated endogeneous investments, respectively:
PARAMETER IGKFX_Y(AAA,GGG)         'Externally given generation capacity in year Y (MW)',
          IGKFX_Y_1(AAA,GGG)    'Externally given generation capacity in year -1 (MW)',
          IGKVACCTOY(AAA,G)     'Internally given generation capacity at beginning of year (MW)(cumulative investments minus decommissioning)',
*          IGKVACCTOYNODECOM(G,AAA)'Cumulative investments in generation capacity at beginning of year',
          IGKVACCEOY(AAA,G)     'Internally given generation capacity at end of year (MW)(cumulative investments minus decommissioning)';


* Emission policy data during current simulation year:
PARAMETER ITAX_CO2_Y(C)   'Tax on CO2 (Money/t)' ,
          ITAX_SO2_Y(C)'Tax on SO2 (Money/t)',
          ITAX_NOX_Y(C)'Tax on NOX (Money/kg)';
PARAMETER ILIM_CO2_Y(C)   'CO2 emission limit',
          ILIM_SO2_Y(C)'SO2 emission limit',
          ILIM_NOX_Y(C)'NOX emission limit';

* Transmission capacity (MW) between regions RE (exporting) and  RI (importing)
* at the beginning of current simulation year:
PARAMETER IXKINI_Y(IRRRE,IRRRI)      'Externally given transmission capacity between regions at beginning of year (MW)',
          IXKVACCTOY(IRRRE,IRRRI) 'Internally given transmission capacity at beginning of year (MW)(cumulative investments)';

* Possibilities for new transmission lines:

IXKN(IRE,IRI) = NO;


* Fixed exchange with third countries (MW) current simulation year:
PARAMETER IX3FX_T_Y(RRR,S,T)   'Export to third countries for each time segment (MW)';


* Fuel price for current simulation year:
PARAMETER IFUELP_Y(AAA,FFF)   'Fuel price in the year simulated';


* Inflow in areas each season:
* The following is used in balbase1.sim and balbase2.sim
PARAMETER IHYINF_S(AAA,SSS)  'Water inflow to hydro reservoirs in areas in each season (MWh/MW)';

* In BB3 one of the following parameters are used to control the use of hydro:
PARAMETER IHYFXRW(RRR,SSS)   'Water quantity to be transferred to model Balbase3 (MWh)' ;
* OR the following is used. Conditioned by %WATERVAL%
PARAMETER IWATERVAL(AAA,SSS)   'Water price (value) to be transferred to model Balbase3 (Money/MWh)' ;




PARAMETER IGROWTHCAP(C,G)        'Limit on growth of technology dependant on years between optimisation';


PARAMETER IGKNMAX_Y(AAA,G)       'Maximum capacity at new technologies (MW)';

*-------------------------------------------------------------------------------
*----- Any internal sets and parameters for addon to be placed here: -----------
*-------------------------------------------------------------------------------
* Internals for GAS moved up just above calculation of weights and dump of
* input data.
* These internal parameters pertain to hydrogen technologies.
$ifi %H2%==yes $include '../../base/addons/Hydrogen/H2InternalParameters.inc';
* These internal parameters pertain to natural gas.
$ifi %GAS%==yes $include '../../base/addons/gas/gasinternal.inc';
* These internal parameters pertain to price sensitivy electricity exchange with
* third countries.
$ifi %X3V%==yes $include '../../base/addons/x3v/model/x3vinternal.inc';
* These internal parameters and sets pertain to heat transmission.
$if %heattrans% == yes $include '../../base/addons/heattrans/model/htinternal.inc';

$ifi %AGKNDISC%==yes   $include '../../base/addons/agkndisc/agkndiscinternal.inc';

*-------------------------------------------------------------------------------
*----- End: Any internal sets and parameters for addon to be placed here -------
*-------------------------------------------------------------------------------


*-------------------------------------------------------------------------------
* End: Internal parameters and settings
*-------------------------------------------------------------------------------


*-------------------------------------------------------------------------------
* Possibly write input data, prepare output file possibilities:
*-------------------------------------------------------------------------------

* The following file contains definitions of logical file names
* and the associated names of files that may be used for printout of simulation results.
* It also contains various definitions that are useful for the production and layout of the output.

* Prepare some printing possibilities:
$INCLUDE '../../base/output/printout/printinc/print1.inc';

* Overview of input data in text format (see the description at the top of the file inputout):
$ifi %inputdatatxt%== yes        $INCLUDE '../../base/output/printout/printinc/inputout.inc';
$ifi %inputdatatxt%== yesnosolve $INCLUDE '../../base/output/printout/printinc/inputout.inc';
$ifi %inputdatatxt%== yesnosolve $goto ENDOFMODEL
* Unload input data to gdx file:
* Note that the execute_unload command will also identify variables and equations
$ifi %INPUTDATA2GDX%==yes execute_unload '%relpathInputdata2GDX%INPUTDATAOUT.gdx';
* Transfer inputdata a seperate Access file (only possible if %INPUTDATA2GDX%==yes):
$ifi %INPUTDATAGDX2MDB%==yes execute "=GDX2ACCESS %relpathInputdata2GDX%INPUTDATAOUT.gdx";
* Transfer to Excel, read the identifiers to be transferred from file inputdatagdx2xls.txt (only possible if %INPUTDATA2GDX%==yes):
* Note: presently not working (the relevant data is not set i file inputdatagdx2xls.txt):
* NOTWORKING (i.e. you MUST have '$setglobal INPUTDATAGDX2XLS'): Note:  GAMS version 22.7 and later have better support for this....
*$ifi %INPUTDATAGDX2XLS%==yes  execute  "GDXXRW.EXE Input=%relpathInputdata2GDX%INPUTDATAOUT.gdx  Output=%relpathInputdata2GDX%INPUTDATAOUT.xls  @%relpathModel%inputdatagdx2xls.txt";


*-------------------------------------------------------------------------------
* End: Possibly write input data, prepare output file possibilities
*-------------------------------------------------------------------------------



$ifi %REShareE%==yes $include '../addons/REShareE/demodata/RESEdata.inc';
$ifi %REShareE%==yes $include '../addons/REShareE/RESEintrn.inc';
$ifi %REShareE%==yes file REShareEPrt4 / '../printout/RESEprt4.out' /;

*$ifi %REShareEH%==yes $include '../addons/REShareEH/demodata/RESEHdata.inc';
*$ifi %REShareEH%==yes $include '../addons/REShareEH/RESEHintrn.inc';
*$ifi %REShareEH%==yes file REShareEHPrt4 / '../printout/RESEHprt4.out' /;

$ifi %REShareEH%==yes
$if     EXIST '../data/RESEHDATA.inc' $INCLUDE         '../data/RESEHDATA.inc';
$ifi %REShareEH%==yes
$if not EXIST '../data/RESEHDATA.inc' $INCLUDE '../../base/data/RESEHDATA.inc';
$ifi %REShareEH%==yes $include '../../base/addons/REShareEH/RESEHintrn.inc';
$ifi %REShareEH%==yes file REShareEHPrt4 / '../printout/RESEHprt4.out' /;

*------------------------------

*$ifi %DECOMP%==yes IGDECOMP(IGWND)$(not SUM((YYY,AAAOFFSHORE), GKFX(YYY,AAAOFFSHORE,IGWND)))=yes;
*$ifi %DECOMP%==yes GKFX(YYY,AAA,IGDECOMP)$((not ICA('Denmark',AAA)) and ord(YYY) GT SUM(YYYALIAS$(DECOMPYEAR(YYYALIAS)), ord(YYYALIAS)))
*$ifi %DECOMP%==yes                = GKFX(YYY,AAA,IGDECOMP)*(1-ANNUALDECOMP)**(ord(YYY) - SUM(YYYALIAS$(DECOMPYEAR(YYYALIAS)), ord(YYYALIAS)));


* LARS: Automatic decommissioning dependent on DECOMP control variable.
$ifi %DECOMP%==yes SCALAR ANNUALDECOMP /0.03/;
$ifi %DECOMP%==yes SET DECOMPYEAR(YYY) /2010/;
$ifi %DECOMP%==yes ALIAS(YYY,YYYALIAS);
$ifi %DECOMP%==yes SET IGDECOMP(G);
$ifi %DECOMP%==yes IGDECOMP(G)=no;
$ifi %DECOMP%==yes IGDECOMP(IGCND)$(GDATA(IGCND,'GDFUEL') EQ NATGAS    )=yes;
$ifi %DECOMP%==yes IGDECOMP(IGCND)$(GDATA(IGCND,'GDFUEL') EQ COAL      )=yes;
$ifi %DECOMP%==yes IGDECOMP(IGCND)$(GDATA(IGCND,'GDFUEL') EQ LIGNITE   )=yes;
$ifi %DECOMP%==yes IGDECOMP(IGCND)$(GDATA(IGCND,'GDFUEL') EQ FUELOIL   )=yes;
$ifi %DECOMP%==yes IGDECOMP(IGCND)$(GDATA(IGCND,'GDFUEL') EQ LIGHTOIL  )=yes;
$ifi %DECOMP%==yes IGDECOMP(IGCND)$(GDATA(IGCND,'GDFUEL') EQ ORIMULSION)=yes;
$ifi %DECOMP%==yes IGDECOMP(IGCND)$(GDATA(IGCND,'GDFUEL') EQ SHALE     )=yes;
$ifi %DECOMP%==yes IGDECOMP(IGCND)$(GDATA(IGCND,'GDFUEL') EQ PEAT      )=yes;
$ifi %DECOMP%==yes IGDECOMP(IGEXT)$(GDATA(IGEXT,'GDFUEL') EQ NATGAS    )=yes;
$ifi %DECOMP%==yes IGDECOMP(IGEXT)$(GDATA(IGEXT,'GDFUEL') EQ COAL      )=yes;
$ifi %DECOMP%==yes IGDECOMP(IGEXT)$(GDATA(IGEXT,'GDFUEL') EQ LIGNITE   )=yes;
$ifi %DECOMP%==yes IGDECOMP(IGEXT)$(GDATA(IGEXT,'GDFUEL') EQ FUELOIL   )=yes;
$ifi %DECOMP%==yes IGDECOMP(IGEXT)$(GDATA(IGEXT,'GDFUEL') EQ LIGHTOIL  )=yes;
$ifi %DECOMP%==yes IGDECOMP(IGEXT)$(GDATA(IGEXT,'GDFUEL') EQ ORIMULSION)=yes;
$ifi %DECOMP%==yes IGDECOMP(IGEXT)$(GDATA(IGEXT,'GDFUEL') EQ SHALE     )=yes;
$ifi %DECOMP%==yes IGDECOMP(IGEXT)$(GDATA(IGEXT,'GDFUEL') EQ PEAT      )=yes;
$ifi %DECOMP%==yes IGDECOMP(IGBPR)$(GDATA(IGBPR,'GDFUEL') EQ NATGAS    )=yes;
$ifi %DECOMP%==yes IGDECOMP(IGBPR)$(GDATA(IGBPR,'GDFUEL') EQ COAL      )=yes;
$ifi %DECOMP%==yes IGDECOMP(IGBPR)$(GDATA(IGBPR,'GDFUEL') EQ LIGNITE   )=yes;
$ifi %DECOMP%==yes IGDECOMP(IGBPR)$(GDATA(IGBPR,'GDFUEL') EQ FUELOIL   )=yes;
$ifi %DECOMP%==yes IGDECOMP(IGBPR)$(GDATA(IGBPR,'GDFUEL') EQ LIGHTOIL  )=yes;
$ifi %DECOMP%==yes IGDECOMP(IGBPR)$(GDATA(IGBPR,'GDFUEL') EQ ORIMULSION)=yes;
$ifi %DECOMP%==yes IGDECOMP(IGBPR)$(GDATA(IGBPR,'GDFUEL') EQ SHALE     )=yes;
$ifi %DECOMP%==yes IGDECOMP(IGBPR)$(GDATA(IGBPR,'GDFUEL') EQ PEAT      )=yes;

* $ifi %DECOMP%==yes IGDECOMP(IGWND)$(not SUM((YYY,AAAOFFSHORE), GKFX(YYY,AAAOFFSHORE,IGWND)))=yes;
$ifi %DECOMP%==yes GKFX(YYY,AAA,IGDECOMP)$((ICA('Sweden',AAA) or ICA('Norway',AAA) or ICA('Finland',AAA) or ICA('Germany',AAA)) and ord(YYY) GT SUM(YYYALIAS$(DECOMPYEAR(YYYALIAS)), ord(YYYALIAS)))
$ifi %DECOMP%==yes                = GKFX(YYY,AAA,IGDECOMP)*(1-ANNUALDECOMP)**(ord(YYY) - SUM(YYYALIAS$(DECOMPYEAR(YYYALIAS)), ord(YYYALIAS)));


* Unload input data to gdx and possibly MDB files.
* Note that this is a compile time operation, such that only the 'direct' data
* definitions (and no assignments) are reflected:
execute_unload '%relpathModel%..\output\temp\1INPUT.gdx';

*------------------------------


*-------------------------------------------------------------------------------
*  Declaration of VARIABLES:
*-------------------------------------------------------------------------------


FREE     VARIABLE VOBJ                           'Objective function value (MMoney)';
POSITIVE VARIABLE VGE_T(AAA,G,S,T)               'Electricity generation (MW), existing units';
POSITIVE VARIABLE VGEN_T(AAA,G,S,T)              'Electricity generation (MW), new units';
POSITIVE VARIABLE VGH_T(AAA,G,S,T)               'Heat generation (MW), existing units';
POSITIVE VARIABLE VX_T(IRRRE,IRRRI,S,T)          'Electricity export from region IRRRE to IRRRI (MW)';
POSITIVE VARIABLE VGHN_T(AAA,G,S,T)              'Heat generation (MW), new units';
POSITIVE VARIABLE VGKN(AAA,G)                    'New generation capacity (MW)';
POSITIVE VARIABLE VXKN(IRRRE,IRRRI)              'New electricity transmission capacity (MW)';
POSITIVE VARIABLE VDECOM(AAA,G)                  'Decommissioned capacity(MW)';
POSITIVE VARIABLE VDEF_T(RRR,S,T,DEF)            'Flexible electricity demands (MW)';
POSITIVE VARIABLE VDHF_T(AAA,S,T,DHF)            'Flexible heat demands (MW)';
POSITIVE VARIABLE VGHYPMS_T(AAA,S,T)             'Contents of pumped hydro storage (MWh)';
POSITIVE VARIABLE VHYRS_S(AAA,S)                 'Hydro energy equivalent at the start of the season (MWh)';
POSITIVE VARIABLE VESTOLOADT(AAA,S,T)            'Loading of electricity storage (MW)';
POSITIVE VARIABLE VHSTOLOADT(AAA,S,T)            'Loading of heat storage (MW)';
POSITIVE VARIABLE VESTOVOLT(AAA,S,T)             'Electricity storage contents at beginning of time segment (MWh)';
POSITIVE VARIABLE VHSTOVOLT(AAA,S,T)             'Heat storage contents at beginning of time segment (MWh)';
POSITIVE VARIABLE VQEEQ(RRR,S,T,IPLUSMINUS)      'Feasibility in electricity generation equals demand equation QEEQ';
POSITIVE VARIABLE VQHEQ(AAA,S,T,IPLUSMINUS)      'Feasibility in heat balance QHEQ';
POSITIVE VARIABLE VQESTOVOLT(AAA,S,T,IPLUSMINUS) 'Feasibility in electricity storage equation QESTOVOLT';
POSITIVE VARIABLE VQHSTOVOLT(AAA,S,T,IPLUSMINUS) 'Feasibility in heat storage equation VQHSTOVOLT';
POSITIVE VARIABLE VQHYRSSEQ(AAA,S,IPLUSMINUS)    'Feasibility of QHYRSSEQ';
POSITIVE VARIABLE VGE2LEVEL(AAA,G,S,DAYTYPE)     'Average load of slowly regulating production (MW)';
*-------------------------------------------------------------------------------
*----- Any variables for addon to be placed here: ------------------------------
*-------------------------------------------------------------------------------
* These add-on variables pertain to natural gas.
$ifi %GAS%==yes $include '../../base/addons/gas/gasvariables.inc';
* This file includes:
* [list equations]
* These add-on variables pertain to compressed air energy storage.
$ifi %CAES%==yes $INCLUDE '../../base/addons/CAES/CAESvariables.inc';
* These add-on variables pertain to hydrogen technology.
$ifi %H2%==yes $include '../../base/addons/Hydrogen/H2variables.inc';
* These add-on variables pertain to transport technology (KHED)
$ifi %TSP%==yes $include '../../base/addons/Transport/TSPVariables.inc';
* These add-on vairables pertain to price sensitive electricity exchange with
* third countries.
$ifi %X3V%==yes $include '../../base/addons/x3v/model/x3vvariables.inc';
* These add-on vairables pertain heat transmission
$ifi %HEATTRANS%==yes $include '../../base/addons/heattrans/model/htvariables.inc';

$ifi %AGKNDISC%==yes  $include '../../base/addons/agkndisc/agkndiscvariables.inc';


*-------------------------------------------------------------------------------
*----- End: Any variables for addon to be placed here: -------------------------
*-------------------------------------------------------------------------------

* Note that intervals for variables may be set later (as .lo, .up  and/or .fx).

*-------------------------------------------------------------------------------
*  End: Declaration of VARIABLES
*-------------------------------------------------------------------------------


*-------------------------------------------------------------------------------
*  Declaration and definition of EQUATIONS:
*-------------------------------------------------------------------------------

* Equation declarations:

EQUATIONS
   QOBJ                     'Objective function'
   QEEQ(RRR,S,T)          'Electricity generation equals demand'
   QHEQ(AAA,S,T)          'Heat generation equals demand'
   QGCBGBPR(AAA,G,S,T)    'CHP generation (back pressure) limited by Cb-line'
   QGCBGEXT(AAA,G,S,T)    'CHP generation (extraction) limited by Cb-line'
   QGCVGEXT(AAA,G,S,T)    'CHP generation (extraction) limited by Cv-line'
   QGGETOH(AAA,G,S,T)     'Electric heat generation'
   QGNCBGBPR(AAA,G,S,T)   'CHP generation (back pressure) Cb-line, new'
   QGNCBGEXT(AAA,G,S,T)   'CHP generation (extraction) Cb-line, new'
   QGNCVGEXT(AAA,G,S,T)   'CHP generation (extraction) Cv-line, new'
   QGNGETOH(AAA,G,S,T)    'Electric heat generation, new'
   QGE2LEVEL(AAA,G,S,T)   'Variation on slowly regulated technologies'
   QGEKNT(AAA,G,S,T)      'Generation on new electricity cap, limited by capacity'
   QGHKNT(AAA,G,S,T)      'Generation on new IGHH cap, limited by capacity'
   QGKNHYRR(AAA,G,S,T)    'Generation on new hydro-ror limited by capacity and water'
   QGKNWND(AAA,G,S,T)     'Generation on new windpower limited by capacity and wind'
   QGKNSOLE(AAA,G,S,T)    'Generation on new solarpower limited by capacity and sun'
   QGKNSOLH(AAA,G,S,T)    'Generation on new solarheat limited by capacity and sun'
   QHYRSSEQ(AAA,S)        'Hydropower with reservoir seasonal energy constraint'
   QHYMINRS(AAA,G,S)       'Hydropower reservoir - minimum level'
   QHYMAXRS(AAA,G,S)       'Hydropower reservoir - maximum level'
   QHYMING(AAA,S,T)       'Regulated and unregulated hydropower production lower than capacity'
   QESTOVOLT(AAA,S,T)     'Electricty storage dynamic equation (MWh)'
   QESTOLOADT(AAA,S,T)    'Electricity storage loading less than heat production (MW)'
   QHSTOVOLT(AAA,S,T)     'Heat storage dynamic equation (MWh)'
   QHSTOLOADT(AAA,S,T)    'Heat storage loading less than heat production (MW)'
   QHSTOLOADTLIM(AAA,S,T) 'Upper limit to heat storage loading (MW)'
   QESTOLOADTLIM(AAA,S,T) 'Upper limit to electricity storage loading (MW)'
   QHSTOVOLTLIM(AAA,S,T)  'Heat storage capacity limit (MWh)'
   QESTOVOLTLIM(AAA,S,T)  'Electricity storage capacity limit (MWh)'
   QKFUELC(C,FFF)          'Total capacity using fuel FFF is limited in country'
   QKFUELR(RRR,FFF)        'Total capacity using fuel FFF is limited in region'
   QKFUELA(AAA,FFF)        'Total capacity using fuel FFF is limited in area'
   QGMINFUELC(C,FFF)      'Minimum electricity generation by fuel per country'
   QGMAXFUELC(C,FFF)      'Maximum electricity generation by fuel per country'
   QGMINFUELR(RRR,FFF)    'Minimum electricity generation by fuel per region'
   QGMAXFUELR(RRR,FFF)    'Maximum electricity generation by fuel per region'
   QGMINFUELA(AAA,FFF)    'Minimum electricity generation by fuel per area'
   QGMAXFUELA(AAA,FFF)    'Maximum electricity generation by fuel per area'
   QGMINCF(C,FFF)         'Minimum fuel usage per country constraint'
   QGMAXCF(C,FFF)         'Maximum fuel usage per country constraint'
   QGEQCF(C,FFF)          'Required fuel usage per country constraint'
   QGMINRF(RRR,FFF)       'Minimum fuel usage per region constraint'
   QGMAXRF(RRR,FFF)       'Maximum fuel usage per region constraint'
   QGEQRF(RRR,FFF)        'Required fuel usage per region constraint'
   QGMINAF(AAA,FFF)       'Minimum fuel usage per area constraint'
   QGMAXAF(AAA,FFF)       'Maximum fuel usage per area constraint'
   QGEQAF(AAA,FFF)        'Required fuel usage per area constraint'
   QXK(IRRRE,IRRRI,S,T)   'Transmission capacity constraint'
   QLIMCO2(C)             'Limit on annual CO2-emission'
   QLIMSO2(C)             'Limit on annual SO2 emission'
   QLIMNOX(C)             'Limit on annual NOx emission'
   QHYFXRW(RRR,S)         'Hydro with reservoir available for this region and season (MWh)'
   QHYFXCW(C,S)           'Hydro with reservoir available for this country and season (MWh)'
   QBASELOAD(C,S,T)        'Minimum production for baseload service providers (MW)'
   QRESDE(RRR,S,T)        'Reserve requirement proportional with demand (MW)'
   QRESWI(RRR,S,T)        'Reserve requirement proportional with wind power (MW)'
   QMAXINVEST(C,FFF)      'Maximal investment by country and fuel during one simulated year (MW)'
   QGMAXINVEST2(C,G)      'Maximum model generated capacity increase from one year to the next (MW)'



*-------------------------------------------------------------------------------
*----- Any equations declarations for addon to be placed here: -----------------
*-------------------------------------------------------------------------------


$ifi %DECOMPEFF%==yes   QGEKOT(AAA,G,S,T)      'Generation on old electricity capacity, limited by capacity';
$ifi %DECOMPEFF%==yes   QGHKOT(AAA,G,S,T)      'Generation on old electricity capacity, limited by capacity';

$ifi %DECOMPEFF%==yes   QGKOHYRR(AAA,G,S,T)    'Generation on old hydro-ror limited by capacity and water';
$ifi %DECOMPEFF%==yes   QGKOWND(AAA,G,S,T)     'Generation on old windpower limited by capacity and wind';
$ifi %DECOMPEFF%==yes   QGKOSOLE(AAA,G,S,T)    'Generation on old solarpower limited by capacity and sun';

$ifi %REShareE%==yes QREShareE(CCCREShareE)    'Minimum share of electricity production from renewable electricity';
$ifi %REShareEH%==yes QREShareEH(CCCREShareEH) 'Minimum share of electricity and heat production from renewable electricity';

$ifi %AGKNDISC%==yes QAGKNDISC01(AAA,G)         'At most one of the specified discrete capacity size investments is chosen (Addon AGKNDISC)';
$ifi %AGKNDISC%==yes QAGKNDISCCONT(AAA,G)       'The invested capacity must be one of the specified sizes or zero (MW) (Addon AGKNDISC)';

*-------------------------------------------------------------------------------
*----- End: Any equations declarations for addon to be placed here -------------
*-------------------------------------------------------------------------------


;

* Equation definitions:
*----- The objective function QOBJ: --------------------------------------------
QOBJ ..

   VOBJ =E=


*IOF0000001*(Note: in final version there will be no factor, because scaling of the equation is used.
IOF1_*(

* Cost of fuel consumption during the year:

     SUM((IAGK_Y(IA,IGE),FFF)$IGF(IGE,FFF),
                 IFUELP_Y(IA,FFF) * IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 VGE_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* GEFFDERATE(IA,IGE))))


    +SUM((IAGK_Y(IA,IGH),FFF)$IGF(IGH,FFF),
                 IFUELP_Y(IA,FFF) * IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 GDATA(IGH,'GDCV')*VGH_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH))))


    +SUM((IAGKN(IA,IGE),FFF)$IGF(IGE,FFF),
                 IFUELP_Y(IA,FFF) * IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 VGEN_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* GEFFDERATE(IA,IGE))))

    +SUM((IAGKN(IA,IGH),FFF)$IGF(IGH,FFF),
                 IFUELP_Y(IA,FFF) * IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 GDATA(IGH,'GDCV')*VGHN_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH))))


* Operation and maintainance cost:

   + SUM(IAGK_Y(IA,IGE), GOMVCOST(IA,IGE) * SUM((IS3,T), IHOURSINST(IS3,T)*
     VGE_T(IA,IGE,IS3,T)))

   + SUM(IAGK_Y(IA,IGNOTETOH(IGH)), GOMVCOST(IA,IGNOTETOH) * SUM((IS3,T), IHOURSINST(IS3,T)*
     GDATA(IGNOTETOH,'GDCV')*(VGH_T(IA,IGNOTETOH,IS3,T))))

   + SUM(IAGKN(IA,IGE), GOMVCOST(IA,IGE) * SUM((IS3,T), IHOURSINST(IS3,T)*
     VGEN_T(IA,IGE,IS3,T)))

   + SUM(IAGKN(IA,IGNOTETOH(IGH)), GOMVCOST(IA,IGNOTETOH) * SUM((IS3,T), IHOURSINST(IS3,T)*
     GDATA(IGNOTETOH,'GDCV')*(VGHN_T(IA,IGNOTETOH,IS3,T))))

$ifi not %DECOMPEFF%==yes + IOF1000*(SUM(IAGK_Y(IA,G),(IGKVACCTOY(IA,G) + IGKFX_Y(IA,G))*GOMFCOST(IA,G)))
$ifi %DECOMPEFF%==yes     + IOF1000*(SUM(IAGK_Y(IA,G),(IGKVACCTOY(IA,G) + IGKFX_Y(IA,G) - VDECOM(IA,G))*GOMFCOST(IA,G)))

   + IOF1000*(SUM(IAGKN(IA,G),VGKN(IA,G)*GOMFCOST(IA,G)))

*  Hydro with storage seasonal price profile:

   + SUM(IAGK_Y(IA,IGHYRS), SUM((IS3,T), HYPPROFILS(IA,IS3)* IHOURSINST(IS3,T)
     * VGE_T(IA,IGHYRS,IS3,T)))

   + SUM(IAGKN(IA,IGHYRS), SUM((IS3,T), HYPPROFILS(IA,IS3)* IHOURSINST(IS3,T)
     * VGEN_T(IA,IGHYRS,IS3,T)))

$ifi not %bb3%==yes $goto not_waterval
$ifi not %WATERVAL%==yes $goto not_waterval
   + SUM(IAGK_Y(IA,IGHYRS),SUM((IS3,T), IWATERVAL(IA,IS3)* IHOURSINST(IS3,T)
     * VGE_T(IA,IGHYRS,IS3,T)))

   + SUM(IAGKN(IA,IGHYRS), SUM((IS3,T), IWATERVAL(IA,IS3)* IHOURSINST(IS3,T)
     * VGEN_T(IA,IGHYRS,IS3,T)))
$label not_waterval


* Transmission cost:

   + SUM((IRE,IRI)$(IXKINI_Y(IRE,IRI) OR IXKN(IRE,IRI) OR IXKN(IRI,IRE)),
       SUM((IS3,T), IHOURSINST(IS3,T) * (VX_T(IRE,IRI,IS3,T) * XCOST(IRE,IRI))))

* Investment costs, new generation and storage capacity:

    + IOF1000000*(SUM((IAGKN(IA,G)), VGKN(IA,G)*GINVCOST(IA,G)*(SUM(C$ICA(C,IA),ANNUITYC(C)))))

$ifi %AGKNDISC%==yes  $include '../../base/addons/agkndisc/agkndiscaddobj.inc';

* Investment costs, new transmission capacity
* (the average of the annuities for the two countries in question
* is used for international transmission):

    + SUM((IRE,IRI)$(IXKN(IRI,IRE) OR IXKN(IRE,IRI)), VXKN(IRE,IRI)*XINVCOST(IRE,IRI)*
      (IOF05*(SUM(C$CCCRRR(C,IRE),ANNUITYC(C))+SUM(C$CCCRRR(C,IRI),ANNUITYC(C)))))


* Emission taxes

    + SUM(C, SUM(IAGK_Y(IA,IGE)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_CO2(IGE)*IOF0001) *
      IOF3P6 *VGE_T(IA,IGE,IS3,T) /(GDATA(IGE,'GDFE') * GEFFDERATE(IA,IGE)) ) * (ITAX_CO2_Y(C))))

    + SUM(C, SUM(IAGK_Y(IA,IGH)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_CO2(IGH)*IOF0001) *
      IOF3P6 *GDATA(IGH,'GDCV')* VGH_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH)))*(ITAX_CO2_Y(C))))

    + SUM(C, SUM(IAGKN(IA,IGE)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_CO2(IGE)*IOF0001) *
      IOF3P6 * VGEN_T(IA,IGE,IS3,T) / (GDATA(IGE,'GDFE') * GEFFDERATE(IA,IGE)) ) * (ITAX_CO2_Y(C))))

    + SUM(C, SUM(IAGKN(IA,IGH)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_CO2(IGH)*IOF0001) *
      IOF3P6 *GDATA(IGH,'GDCV')* VGHN_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH)))*(ITAX_CO2_Y(C))))

    + SUM(C, SUM(IAGK_Y(IA,IGE)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_SO2(IGE)*IOF0001) *
      IOF3P6 *VGE_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE') * GEFFDERATE(IA,IGE)))*(ITAX_SO2_Y(C))))

    + SUM(C, SUM(IAGK_Y(IA,IGH)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_SO2(IGH)*IOF0001) *
      IOF3P6 *GDATA(IGH,'GDCV')* VGH_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH)))*(ITAX_SO2_Y(C))))

    + SUM(C, SUM(IAGKN(IA,IGE)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_SO2(IGE)*IOF0001) *
      IOF3P6 * VGEN_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')*GEFFDERATE(IA,IGE)))*(ITAX_SO2_Y(C))))

    + SUM(C, SUM(IAGKN(IA,IGH)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_SO2(IGH)*IOF0001) *
      IOF3P6*GDATA(IGH,'GDCV')* VGHN_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH)))*(ITAX_SO2_Y(C))))

    + SUM(C, SUM(IAGK_Y(IA,IGE)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T)*(GDATA(IGE,'GDNOX')*IOF0000001)*
      IOF3P6 * VGE_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')*GEFFDERATE(IA,IGE)))*(ITAX_NOX_Y(C))))

    + SUM(C, SUM(IAGK_Y(IA,IGH)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T)*(GDATA(IGH,'GDNOX')*IOF0000001)*
      IOF3P6 *GDATA(IGH,'GDCV')* VGH_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH)) )*(ITAX_NOX_Y(C))))

    + SUM(C, SUM(IAGKN(IA,IGE)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T)*(GDATA(IGE,'GDNOX')*IOF0000001)*
      IOF3P6 * VGEN_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')*GEFFDERATE(IA,IGE)))*(ITAX_NOX_Y(C))))

    + SUM(C, SUM(IAGKN(IA,IGH)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T)*(GDATA(IGH,'GDNOX')*IOF0000001)*
      IOF3P6 *GDATA(IGH,'GDCV')* VGHN_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH)))*(ITAX_NOX_Y(C))))

* Fuel taxes

    + SUM((C,FFF,IS3,T), SUM(IAGK_Y(IA,IGE)
      $(IGF(IGE,FFF) AND ICA(C,IA)),
      IHOURSINST(IS3,T) * TAX_F(FFF,C) * IOF3P6 *
      (VGE_T(IA,IGE,IS3,T) / (GDATA(IGE,'GDFE') * GEFFDERATE(IA,IGE)))))

   + SUM((C,FFF,IS3,T), SUM(IAGK_Y(IA,IGH)
      $(IGF(IGH,FFF) AND ICA(C,IA)),
      IHOURSINST(IS3,T) * TAX_F(FFF,C) * IOF3P6 *
      GDATA(IGH,'GDCV')* VGH_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE') * GEFFDERATE(IA,IGH))))

    + SUM((C,FFF,IS3,T), SUM(IAGKN(IA,IGE)
      $(IGF(IGE,FFF) AND ICA(C,IA)),
      IHOURSINST(IS3,T) * TAX_F(FFF,C) * IOF3P6 *
      (VGEN_T(IA,IGE,IS3,T) / (GDATA(IGE,'GDFE') * GEFFDERATE(IA,IGE)))))

   + SUM((C,FFF,IS3,T), SUM(IAGKN(IA,IGH)
      $(IGF(IGH,FFF) AND ICA(C,IA)),
      IHOURSINST(IS3,T) * TAX_F(FFF,C) * IOF3P6 *
      GDATA(IGH,'GDCV')*VGHN_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH))))

* More fuel taxes on technology types.
$ONTEXT  Not completely implemented yet - kept as appetizer.
   + SUM((IA,IGH,IS3,T)$(IAGK_Y(IA,IGH) and (IGHOB(IGH) or IGETOH(IGH))),
      TAX_FHO(IA,IGH)*IHOURSINST(IS3,T)  * IOF3P6 * GDATA(IGH,'GDCV')* VGH_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE') * GEFFDERATE(IA,IGH)))
   + SUM((IA,IGH,IS3,T)$(IAGKN(IA,IGH) and (IGHOB(IGH) or IGETOH(IGH))),
      TAX_FHO(IA,IGH)*IHOURSINST(IS3,T)  * IOF3P6 *  VGHN_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE') * GEFFDERATE(IA,IGH)))
* Heat generation taxes.
   + SUM((IA,IGH,IS3,T)$(IAGK_Y(IA,IGH) and TAX_GH(IA,IGH)),
      TAX_GH(IA,IGH)*IOF3P6*VGH_T(IA,IGH,IS3,T)*IHOURSINST(IS3,T))
   + SUM((IA,IGH,IS3,T)$(IAGKN(IA,IGH) and TAX_GH(IA,IGH)),
      TAX_GH(IA,IGH)*IOF3P6*VGHN_T(IA,IGH,IS3,T)*IHOURSINST(IS3,T))
$OFFTEXT
* Changes in consumers' utility relative to electricity consumption:

   + SUM(IR,
     SUM((IS3,T), IHOURSINST(IS3,T)
     * (SUM(DEF_D1, VDEF_T(IR,IS3,T,DEF_D1)* IDEFP_T(IR,IS3,T,DEF_D1)  )
     +  SUM(DEF_D2, VDEF_T(IR,IS3,T,DEF_D2)* IDEFP_T(IR,IS3,T,DEF_D2)  )
     +  SUM(DEF_D3, VDEF_T(IR,IS3,T,DEF_D3)* IDEFP_T(IR,IS3,T,DEF_D3)  )
     )

     )
     )

   - SUM(IR,
     SUM((IS3,T), IHOURSINST(IS3,T)
     * (SUM(DEF_U1, VDEF_T(IR,IS3,T,DEF_U1)* IDEFP_T(IR,IS3,T,DEF_U1)  )
     +  SUM(DEF_U2, VDEF_T(IR,IS3,T,DEF_U2)* IDEFP_T(IR,IS3,T,DEF_U2)  )
     +  SUM(DEF_U3, VDEF_T(IR,IS3,T,DEF_U3)* IDEFP_T(IR,IS3,T,DEF_U3)  )))
     )

* Changes in consumers' utility relative to heat consumption:

   + SUM(IA,
     SUM((IS3,T), IHOURSINST(IS3,T)
     * (SUM(DHF_D1, VDHF_T(IA,IS3,T,DHF_D1)* IDHFP_T(IA,IS3,T,DHF_D1)  )
     +  SUM(DHF_D2, VDHF_T(IA,IS3,T,DHF_D2)* IDHFP_T(IA,IS3,T,DHF_D2)  )
     +  SUM(DHF_D3, VDHF_T(IA,IS3,T,DHF_D3)* IDHFP_T(IA,IS3,T,DHF_D3)  )))
      )

   - SUM(IA,
     SUM((IS3,T), IHOURSINST(IS3,T)
     * (SUM(DHF_U1, VDHF_T(IA,IS3,T,DHF_U1)* IDHFP_T(IA,IS3,T,DHF_U1)  )
     +  SUM(DHF_D2, VDHF_T(IA,IS3,T,DHF_D2)* IDHFP_T(IA,IS3,T,DHF_D2)  )
     +  SUM(DHF_D3, VDHF_T(IA,IS3,T,DHF_D3)* IDHFP_T(IA,IS3,T,DHF_D3)  )))
     )


* Infeasibility penalties:
   + PENALTYQ*(
$ifi %BB1%==yes    +SUM((IA,IS3)$SUM(IGHYRS,IAGK_Y(IA,IGHYRS)),(VQHYRSSEQ(IA,IS3,'IMINUS')+VQHYRSSEQ(IA,IS3,'IPLUS')))
$ifi %BB2%==yes    +SUM((IA,IS3)$SUM(IGHYRS,IAGK_Y(IA,IGHYRS)),(VQHYRSSEQ(IA,IS3,'IMINUS')+VQHYRSSEQ(IA,IS3,'IPLUS')))
$ifi %BB4%==yes    +SUM((IA,IS3)$SUM(IGHYRS,IAGK_Y(IA,IGHYRS)),(VQHYRSSEQ(IA,IS3,'IMINUS')+VQHYRSSEQ(IA,IS3,'IPLUS')))
               +SUM((IA,IS3,T)$SUM(IGHSTO, IAGK_Y(IA,IGHSTO) or IAGKN(IA,IGHSTO)),(VQHSTOVOLT(IA,IS3,T,'IMINUS')+VQHSTOVOLT(IA,IS3,T,'IPLUS')))
               +SUM((IA,IS3,T)$SUM(IGESTO, IAGK_Y(IA,IGESTO) or IAGKN(IA,IGESTO)),(VQESTOVOLT(IA,IS3,T,'IMINUS')+VQESTOVOLT(IA,IS3,T,'IPLUS')))
               +SUM((IR,IS3,T),(VQEEQ(IR,IS3,T,'IMINUS')+VQEEQ(IR,IS3,T,'IPLUS')))
               +SUM((IA,IS3,T)$IDH_SUMST(IA),(VQHEQ(IA,IS3,T,'IMINUS')+VQHEQ(IA,IS3,T,'IPLUS')))
              )

* Add-on objective function contributions
* This file containts the gas induced additions to the objective function.
$ifi %GAS%==yes $include '../../base/addons/gas/gascosts.inc'
* LARS:  X3V obj  moved to a file.
$ifi %X3V%==yes $include '../../base/addons/x3v/model/x3vobj.inc';
* This file contains hydrogen induced additions to the objective function.
$ifi %H2%==yes $include '../../base/addons/Hydrogen/H2costs.inc'
* This file contains NAP induced additions to the objective function.
$ifi %NAP%==yes $include '../../base/addons/NAP/NAPobj.inc';
* This file contains transport induced additions to the objective function (KHED)
$ifi %TSP%==yes $include '../../base/addons/Transport/TSPObj.inc'
* This file contains Heat transmission induced additions to the objective function.
$ifi %HEATTRANS%==yes $include '../../base/addons/heattrans/model/htcosts.inc';

* LARS20071029: Experimentation. Case specifc costs. These costs are not a part
* of the core model, nor any add-on module. Create a file in the project
* dirrectory and it will be included automatically.
$if EXIST 'casecosts.inc' $INCLUDE 'casecosts.inc';

)
;
*----- End: The objective function QOBJ ----------------------------------------


*--------------------------Balance equations for electricity and heat ----------

QEEQ(IR,IS3,T) ..

      SUM(IAGK_Y(IA,IGE)$((RRRAAA(IR,IA)) AND IGNOTETOH(IGE)), VGE_T(IA,IGE,IS3,T))
    - SUM(IAGK_Y(IA,IGE)$((RRRAAA(IR,IA)) AND IGETOH(IGE)), VGE_T(IA,IGE,IS3,T))
    + SUM(IAGKN(IA,IGE)$((RRRAAA(IR,IA)) AND IGNOTETOH(IGE)), VGEN_T(IA,IGE,IS3,T))
    - SUM(IAGKN(IA,IGE)$((RRRAAA(IR,IA)) AND IGETOH(IGE)), VGEN_T(IA,IGE,IS3,T))
$ifi %loss%==212    + SUM(IRE$(IXKINI_Y(IRE,IR) OR IXKN(IRE,IR) OR IXKN(IR,IRE)), VX_T(IRE,IR,IS3,T)*(1-XLOSS(IRE,IR)))
$ifi %loss%==301    + SUM(IRE$(IXKINI_Y(IRE,IR) OR IXKN(IRE,IR) OR IXKN(IR,IRE)), VX_T(IRE,IR,IS3,T)*(1-XLOSS1(IRE,IR)))
    - SUM(IA$(RRRAAA(IR,IA) AND sum(IGESTO,IAGK_Y(IA,IGESTO))),VESTOLOADT(IA,IS3,T))
$ifi %X3V%==yes + SUM(X3VPLACE$X3VX(IR,X3VPLACE),SUM(X3VSTEP,VX3VIM_T(IR,X3VPLACE,X3VSTEP,IS3,T)))
$ifi %H2%==yes - SUM(IAGK_Y(IA,IGETOH2)$RRRAAA(IR,IA), VGE_T(IA,IGETOH2,IS3,T))
$ifi %H2%==yes - SUM(IAGKN(IA,IGETOH2)$RRRAAA(IR,IA), VGEN_T(IA,IGETOH2,IS3,T))
* This file contains transport induced additions to the balance equation(KHED)
$ifi %TSP%==yes $include '../../base/addons/Transport/TSPQEEQ.inc'
    =E=
      IX3FX_T_Y(IR,IS3,T)
    + (   (IDE_T_Y(IR,IS3,T)

         + SUM(DEF_U1,VDEF_T(IR,IS3,T,DEF_U1) )
         - SUM(DEF_D1,VDEF_T(IR,IS3,T,DEF_D1) )
         + SUM(DEF_U2,VDEF_T(IR,IS3,T,DEF_U2) )
         - SUM(DEF_D2,VDEF_T(IR,IS3,T,DEF_D2) )
         + SUM(DEF_U3,VDEF_T(IR,IS3,T,DEF_U3) )
         - SUM(DEF_D3,VDEF_T(IR,IS3,T,DEF_D3) )
$ifi %loss%==212     )/(1-DISLOSS_E(IR)))
$ifi %loss%==301     )/(1-DISLOSS1E(IR)))
      + SUM(IRI$(IXKINI_Y(IR,IRI) OR IXKN(IR,IRI) OR IXKN(IRI,IR)),VX_T(IR,IRI,IS3,T))
$ifi %GAS%==yes + SUM((STORE,STORETYPE)$RRRAAA(IR,STORE),VINJ(STORE,STORETYPE,IS3,T)*GSTOREDATA(STORETYPE,'ELECT'))
$ifi %CAES%==yes + SUM((IA,IGCAES)$((IAGK_Y(IA,IGCAES) or IAGKN(IA,IGCAES)) and RRRAAA(IR,IA)), VCAESCOMPRESS(IA,IGCAES,IS3,T)/CAESDATA(IGCAES,'CompEff'))
$ifi %X3V%==yes + SUM(X3VPLACE$X3VX(IR,X3VPLACE),SUM(X3VSTEP,VX3VEX_T(IR,X3VPLACE,X3VSTEP,IS3,T)))
      - VQEEQ(IR,IS3,T,'IMINUS') + VQEEQ(IR,IS3,T,'IPLUS')
 ;


QHEQ(IA,IS3,T)$(IDH_SUMST(IA) NE 0) ..

     SUM(IGBPR$IAGK_Y(IA,IGBPR),VGH_T(IA,IGBPR,IS3,T))
   + SUM(IGBPR$IAGKN(IA,IGBPR),VGHN_T(IA,IGBPR,IS3,T))
   + SUM(IGEXT$IAGK_Y(IA,IGEXT),VGH_T(IA,IGEXT,IS3,T))
   + SUM(IGEXT$IAGKN(IA,IGEXT),VGHN_T(IA,IGEXT,IS3,T))
   + SUM(IGHH$IAGK_Y(IA,IGHH),VGH_T(IA,IGHH,IS3,T))
   + SUM(IGHH$IAGKN(IA,IGHH),VGHN_T(IA,IGHH,IS3,T))
   + SUM(IGETOH$IAGK_Y(IA,IGETOH),VGH_T(IA,IGETOH,IS3,T))
   + SUM(IGETOH$IAGKN(IA,IGETOH),VGHN_T(IA,IGETOH,IS3,T))
   + SUM(IGESTO$IAGK_Y(IA,IGESTO),VGE_T(IA,IGESTO,IS3,T)/GDATA(IGESTO,'GDCB'))
   - VHSTOLOADT(IA,IS3,T)$SUM(IGHSTO$(IAGK_Y(IA,IGHSTO) or IAGKN(IA,IGHSTO)),1)
    =E=
     (IDH_T_Y(IA,IS3,T)
        + SUM(DHF_U1,VDHF_T(IA,IS3,T,DHF_U1) )
        - SUM(DHF_D1,VDHF_T(IA,IS3,T,DHF_D1) )
        + SUM(DHF_U2,VDHF_T(IA,IS3,T,DHF_U2) )
        - SUM(DHF_D2,VDHF_T(IA,IS3,T,DHF_D2) )
        + SUM(DHF_U3,VDHF_T(IA,IS3,T,DHF_U3) )
        - SUM(DHF_D3,VDHF_T(IA,IS3,T,DHF_D3) )

$ifi %loss%==212     )/(1-DISLOSS_H(IA))
$ifi %loss%==301     )/(1-DISLOSS1H(IA))
* Adds heat transmission if selected in the gas add-on
$ifi %HEATTRANS%==yes $include '../../base/addons/heattrans/model/htheatbalance.inc';
        - VQHEQ(IA,IS3,T,'IMINUS') + VQHEQ(IA,IS3,T,'IPLUS')
;

*------ Generation technologies' electricity/heat operating area: --------------

* Back pressure units:

QGCBGBPR(IAGK_Y(IA,IGBPR),IS3,T) ..
      VGE_T(IA,IGBPR,IS3,T) =E= VGH_T(IA,IGBPR,IS3,T) * GDATA(IGBPR,'GDCB');


QGNCBGBPR(IAGKN(IA,IGBPR),IS3,T) ..
      VGEN_T(IA,IGBPR,IS3,T) =E= VGHN_T(IA,IGBPR,IS3,T) * GDATA(IGBPR,'GDCB');


* Extraction units:

QGCBGEXT(IAGK_Y(IA,IGEXT),IS3,T) ..
   VGE_T(IA,IGEXT,IS3,T) =G= VGH_T(IA,IGEXT,IS3,T) * GDATA(IGEXT,'GDCB');


QGCVGEXT(IAGK_Y(IA,IGEXT),IS3,T)$
$ifi not %COMBTECH%==yes  1 ..
$ifi     %COMBTECH%==yes  (NOT IGCOMB2(IGEXT)) ..
* This will have a value if not a combination technology
     (IGKVACCTOY(IA,IGEXT)+IGKFX_Y(IA,IGEXT))*GKDERATE(IA,IGEXT,IS3)
         - VGH_T(IA,IGEXT,IS3,T) * GDATA(IGEXT,'GDCV')
$ifi %COMBTECH%==yes  * This will have a value in case of a combination technology.
$ifi %COMBTECH%==yes    + SUM(IGCOMB2$GGCOMB(IGEXT,IGCOMB2), VGH_T(IA,IGCOMB2,IS3,T) * GDATA(IGCOMB2,'GDCV'))$IGCOMB1(IGEXT)
    =G=
   VGE_T(IA,IGEXT,IS3,T)
$ifi %COMBTECH%==yes  * Add secondary generation if combination technologies are used
$ifi %COMBTECH%==yes  + SUM(IGCOMB2$GGCOMB(IGEXT,IGCOMB2), VGE_T(IA,IGCOMB2,IS3,T))$IGCOMB1(IGEXT)
;

QGNCBGEXT(IAGKN(IA,IGEXT),IS3,T) ..
   VGEN_T(IA,IGEXT,IS3,T) =G= VGHN_T(IA,IGEXT,IS3,T) * GDATA(IGEXT,'GDCB') ;


QGNCVGEXT(IAGKN(IA,IGEXT),IS3,T)$
$ifi not %COMBTECH%==yes  1 ..
$ifi     %COMBTECH%==yes  (NOT IGCOMB2(IGEXT)) ..

         VGKN(IA,IGEXT)*GKDERATE(IA,IGEXT,IS3)
       - VGHN_T(IA,IGEXT,IS3,T) * GDATA(IGEXT,'GDCV')
$ifi %COMBTECH%==yes  * This will have a value in case of a combination technology.
$ifi %COMBTECH%==yes         + SUM(IGCOMB2$GGCOMB(IGEXT,IGCOMB2), VGHN_T(IA,IGCOMB2,IS3,T) * GDATA(IGCOMB2,'GDCV'))$IGCOMB1(IGEXT)
    =G=
   VGEN_T(IA,IGEXT,IS3,T)
$ifi %COMBTECH%==yes  * Add secondary generation if combination technologies are used
$ifi %COMBTECH%==yes     + SUM(IGCOMB2$GGCOMB(IGEXT,IGCOMB2), VGEN_T(IA,IGCOMB2,IS3,T))$IGCOMB1(IGEXT)
;
* Electric heat pumps:

QGGETOH(IAGK_Y(IA,IGETOH),IS3,T) ..
       VGE_T(IA,IGETOH,IS3,T) =E= VGH_T(IA,IGETOH,IS3,T) / GDATA(IGETOH,'GDFE');

QGNGETOH(IAGKN(IA,IGETOH),IS3,T) ..
       VGEN_T(IA,IGETOH,IS3,T) =E= VGHN_T(IA,IGETOH,IS3,T) / GDATA(IGETOH,'GDFE');




*--------- Dispatchable generation technologies' operating area: ---------------

* Generation on new capacity is constrained by the capacity,
* modified by GKDERATE:

QGEKNT(IAGKN(IA,IGKE),IS3,T)$(IGDISPATCH(IGKE) AND
$ifi not %COMBTECH%==yes  1) ..
$ifi     %COMBTECH%==yes  (NOT IGCOMB2(IGKE))) ..
  VGKN(IA,IGKE)*GKDERATE(IA,IGKE,IS3)/(1$(not IGESTO(IGKE)) + GDATA(IGKE,'GDSTOHUNLD')$IGESTO(IGKE))
    =G=
  VGEN_T(IA,IGKE,IS3,T)
$ifi %COMBTECH%==yes  * Add secondary generation if combination technologies are used
$ifi %COMBTECH%==yes    + SUM(IGCOMB2$GGCOMB(IGKE,IGCOMB2), VGEN_T(%IA_IGKEf%IGCOMB2,IS3,T))$IGCOMB1(IGDISPATCH)
;


* Note: does not presently include COMBTECH.
QGHKNT(IAGKN(IA,IGKH),IS3,T)$IGDISPATCH(IGKH)..
  VGKN(IA,IGKH)*GKDERATE(IA,IGKH,IS3)/(1$(not IGHSTO(IGKH)) + GDATA(IGKH,'GDSTOHUNLD')$IGHSTO(IGKH))
     =G=
  VGHN_T(IA,IGKH,IS3,T)
;


$ifi %DECOMPEFF%==yes QGEKOT(IAGK_Y(IA,IGDISPATCH(IGE)),IS3,T) ..
$ifi %DECOMPEFF%==yes  (IGKFX_Y(IGDISPATCH,IA) + IGKVACCTOY(IGDISPATCH,IA)-VDECOM(IA,IGDISPATCH))*GKDERATE(IA,IGDISPATCH,IS3)
$ifi %DECOMPEFF%==yes     =G=
$ifi %DECOMPEFF%==yes  VGE_T(IA,IGDISPATCH,IS3,T)
$ifi %DECOMPEFF%==yes ;

* Rev. 3.01: missing GSOLH, to be added.
$ifi %DECOMPEFF%==yes QGHKOT(IAGK_Y(IA,IGKH),IS3,T) ..
$ifi %DECOMPEFF%==yes  (IGKFX_Y(IGKH,IA) + IGKVACCTOY(IGKH,IA)-VDECOM(IA,IGKH))*GKDERATE(IA,IGKH,IS3)
$ifi %DECOMPEFF%==yes     =G=
$ifi %DECOMPEFF%==yes  VGH_T(IA,IGKH,IS3,T)
$ifi %DECOMPEFF%==yes ;


*-------------- New hydro run-of-river: cannot be dispatched: ------------------


QGKNHYRR(IAGKN(IA,IGHYRR),IS3,T)$IWTRRRSUM(IA)..
 WTRRRFLH(IA) * VGKN(IAGKN) * WTRRRVAR_T(IA,IS3,T) / IWTRRRSUM(IA)
   =E=
   VGEN_T(IA,IGHYRR,IS3,T)

$ifi %DECOMPEFF%==yes QGKOHYRR(IAGK_Y(IA,IGHYRR),IS3,T)..
$ifi %DECOMPEFF%==yes  WTRRRFLH(IA) * (IGKFX_Y(IGHYRR,IA) + IGKVACCTOY(IGHYRR,IA)-VDECOM(IA,IGHYRR)) * WTRRRVAR_T(IA,IS3,T) / IWTRRRSUM(IA)
$ifi %DECOMPEFF%==yes    =E=
$ifi %DECOMPEFF%==yes  VGE_T(IA,IGHYRR,IS3,T)
;

*-------------- New windpower: cannot be dispatched: ---------------------------


QGKNWND(IAGKN(IA,IGWND),IS3,T)$IWND_SUMST(IA)..
 WNDFLH(IA) * VGKN(IA,IGWND) * WND_VAR_T(IA,IS3,T) / IWND_SUMST(IA)
$ifi     %WNDSHUTDOWN%==yes =G=
$ifi not %WNDSHUTDOWN%==yes =E=
  VGEN_T(IA,IGWND,IS3,T);

$ifi %DECOMPEFF%==yes QGKOWND(IAGK_Y(IA,IGWND),IS3,T)$IWND_SUMST(IA)..
$ifi %DECOMPEFF%==yes  WNDFLH(IA) * (IGKFX_Y(IGWND,IA) + IGKVACCTOY(IGWND,IA)-VDECOM(IA,IGWND)) * WND_VAR_T(IA,IS3,T) / IWND_SUMST(IA)
$ifi %DECOMPEFF%==yes    =G=
$ifi %DECOMPEFF%==yes   VGE_T(%IA_IGWND_IS3_T%);


*-------------- New solar power and heat: cannot be dispatched: ----------------
QGKNSOLE(IAGKN(IA,IGSOLE),IS3,T)$ISOLESUMST(IA)..
SOLEFLH(IA) * VGKN(IA,IGSOLE) * SOLE_VAR_T(IA,IS3,T) / ISOLESUMST(IA)
 =E=
VGEN_T(IA,IGSOLE,IS3,T);


QGKNSOLH(IAGKN(IA,IGSOLH),IS3,T)$ISOLHSUMST(IA)..
SOLHFLH(IA) * VGKN(IA,IGSOLH) * SOLH_VAR_T(IA,IS3,T) / ISOLHSUMST(IA)
 =E=
VGHN_T(IA,IGSOLH,IS3,T);


$ifi %DECOMPEFF%==yes QGKOSOLE(IAGK_Y(IA,IGSOLE),IS3,T)..
$ifi %DECOMPEFF%==yes SOLEFLH(IA) * (IGKFX_Y(IGSOLE,IA) + IGKVACCTOY(IGSOLE,IA)-VDECOM(IA,IGSOLE)) * SOLE_VAR_T(IA,IS3,T) / ISOLESUMST(IA)
$ifi %DECOMPEFF%==yes  =E=
$ifi %DECOMPEFF%==yes VGE_T(IA,IGSOLE,IS3,T);


*-------------- Hydropower with reservoirs: ------------------------------------
*
* Hydro reservoir content - dynamic seasonal equation

QHYRSSEQ(IA,S)$SUM(IGHYRS,IAGK_Y(IA,IGHYRS))..
      VHYRS_S(IA,S)
      + SUM(IGHYRS$IAGK_Y(IA,IGHYRS),
        IHYINF_S(IA,S) * (IGKVACCTOY(IA,IGHYRS)+IGKFX_Y(IA,IGHYRS))
        -SUM(T,IHOURSINST(S,T)*(VGE_T(IA,IGHYRS,S,T))))
      + SUM(IGHYRS$IAGKN(IA,IGHYRS),
        IHYINF_S(IA,S) * VGKN(IA,IGHYRS)
        -SUM(T,IHOURSINST(S,T)*(VGEN_T(IA,IGHYRS,S,T))))

      - VQHYRSSEQ(IA,S,'IMINUS') + VQHYRSSEQ(IA,S,'IPLUS')

      =G=  VHYRS_S(IA,S++1);

* Regulated and unregulated hydropower production lower than capacity

QHYMING(IA,IS3,T)$SUM(IGHYRS,IAGK_Y(IA,IGHYRS))..
      SUM(IGHYRS$IAGK_Y(IA,IGHYRS),VGE_T(IA,IGHYRS,IS3,T))
      + SUM(IGHYRS$IAGKN(IA,IGHYRS),VGEN_T(IA,IGHYRS,IS3,T))
      + SUM(IGHYRR$IAGK_Y(IA,IGHYRR),VGE_T(IA,IGHYRR,IS3,T))
      + SUM(IGHYRR$IAGKN(IA,IGHYRR),VGEN_T(IA,IGHYRR,IS3,T))
      =L=
      SUM(IGHYRS$IAGK_Y(IA,IGHYRS),(IGKVACCTOY(IA,IGHYRS)+IGKFX_Y(IA,IGHYRS))*GKDERATE(IA,IGHYRS,IS3))
      + SUM(IGHYRS$IAGKN(IA,IGHYRS),VGKN(IA,IGHYRS))
      ;

*------------ Short term heat and electricity storages:-------------------------


QESTOVOLT(IA,S,T)$(SUM(IGESTO, IAGK_Y(IA,IGESTO)+IAGKN(IA,IGESTO)) AND IS3(S))..
    VESTOVOLT(IA,S,T++1) =E= VESTOVOLT(IA,S,T)
  + IHOURSINST(S,T)*(VESTOLOADT(IA,S,T)*SUM(IGESTO$IAGK_Y(IA,IGESTO),GDATA(IGESTO,'GDFE'))
  - SUM(IGESTO$IAGK_Y(IA,IGESTO), VGE_T(IA,IGESTO,S,T))
  - SUM(IGESTO$IAGKN(IA,IGESTO),VGEN_T(IA,IGESTO,S,T))
  )  / CYCLESINS(S)
  - VQESTOVOLT(IA,S,T,'IPLUS') + VQESTOVOLT(IA,S,T,'IMINUS')
;

QESTOLOADT(IA,IS3,T)$SUM(IGESTO, IAGK_Y(IA,IGESTO)+IAGKN(IA,IGESTO))..
* LARS20070814: This equation is believed to be superfluous, as storage loading is
* restricted to be less than generation minus demand and net exports in the
* electrcity balance equation.
* However, until this is certain, the equation is maintained.
* There is also the possibility that the equation should restrict loading of
* electricity storages to use electricity from local generation units.
      SUM(IGE$(IGNOTETOH(IGE) AND IAGK_Y(IA,IGE)), VGE_T(IA,IGE,IS3,T))
     +SUM(IGE$(IGNOTETOH(IGE) AND IAGKN(IA,IGE)), VGEN_T(IA,IGE,IS3,T))
           - SUM(IGETOH$IAGK_Y(IA,IGETOH), VGE_T(IA,IGETOH,IS3,T))
           - SUM(IGETOH$IAGKN(IA,IGETOH), VGEN_T(IA,IGETOH,IS3,T))
   =G=
      VESTOLOADT(IA,IS3,T)
;

QHSTOVOLT(IA,S,T)$(SUM(IGHSTO, IAGK_Y(IA,IGHSTO)+IAGKN(IA,IGHSTO)) AND IS3(S))..
    VHSTOVOLT(IA,S,T)
  + IHOURSINST(S,T)* (VHSTOLOADT(IA,S,T)
  - SUM(IGHSTO$IAGK_Y(IA,IGHSTO), VGH_T(IA,IGHSTO,S,T))
  - SUM(IGHSTO$IAGKN(IA,IGHSTO), VGHN_T(IA,IGHSTO,S,T))
  ) / CYCLESINS(S)
    =E=       VHSTOVOLT(IA,S,T++1)
  - VQHSTOVOLT(IA,S,T,'IPLUS') + VQHSTOVOLT(IA,S,T,'IMINUS')
;


QHSTOLOADT(IA,IS3,T)$SUM(IGHSTO, IAGK_Y(IA,IGHSTO)+IAGKN(IA,IGHSTO))..
* This equation is believed to be superfluous, as storage loading is
* restricted to be less than generation minus demand in the heat balance equation.
* However, until this is certain, the equation is maintained.
   SUM(IGH$IAGK_Y(IA,IGH), VGH_T(IA,IGH,IS3,T))
  +SUM(IGH$IAGKN(IA,IGH), VGHN_T(IA,IGH,IS3,T))
         =G=
   VHSTOLOADT(IA,IS3,T)
;

* The following constraints replace simple bounds in bb123.sim, when
* investments in storage facilities are allowed. They pertain only to BB2 and to
* areas with an option to invest in storage facilities. Simple bounds cover all
* other situations.

QHSTOLOADTLIM(IA,IS3,T)$SUM(IGHSTO,IAGKN(IA,IGHSTO)) ..
* Existing or accumulated capacity
   SUM(IGHSTO$IAGK_Y(IA,IGHSTO),  (IGKFX_Y(IA,IGHSTO)+IGKVACCTOY(IA,IGHSTO))/GDATA(IGHSTO,'GDSTOHLOAD')
   )
* New investments
   +SUM(IGHSTO$IAGKN(IA,IGHSTO),   VGKN(IA,IGHSTO)/GDATA(IGHSTO,'GDSTOHLOAD')
   )
         =G=
   VHSTOLOADT(IA,IS3,T)
;

QESTOLOADTLIM(IA,IS3,T)$SUM(IGESTO,IAGKN(IA,IGESTO)) ..
* Existing or accumulated capacity
   SUM(IGESTO$IAGK_Y(IA,IGESTO),  (IGKFX_Y(IA,IGESTO)+IGKVACCTOY(IA,IGESTO))/GDATA(IGESTO,'GDSTOHLOAD')
   )
* New investments
   +SUM(IGESTO$IAGKN(IA,IGESTO),  VGKN(IA,IGESTO)/GDATA(IGESTO,'GDSTOHLOAD')   )
         =G=
   VESTOLOADT(IA,IS3,T)
;

* Storage contents does not exceed upper limit (MWh):
QHSTOVOLTLIM(IA,IS3,T)$SUM(IGHSTO,IAGKN(IA,IGHSTO)) ..
* Existing or accumulated capacity
  SUM(IGHSTO$IAGK_Y(IA,IGHSTO),   IGKFX_Y(IA,IGHSTO)+IGKVACCTOY(IA,IGHSTO)     )
* New investments
  +SUM(IGHSTO$IAGKN(IA,IGHSTO),   VGKN(IA,IGHSTO)
   )
         =G=
  VHSTOVOLT(IA,IS3,T)
;

QESTOVOLTLIM(IA,IS3,T)$SUM(IGESTO,IAGKN(IA,IGESTO)) ..
* Existing or accumulated capacity
  SUM(IGESTO$IAGK_Y(IA,IGESTO),  IGKFX_Y(IA,IGESTO)+IGKVACCTOY(IA,IGESTO)      )
* New investments
  +SUM(IGESTO$IAGKN(IA,IGESTO),  VGKN(IA,IGESTO)   )
         =G=
  VESTOVOLT(IA,IS3,T)
;

*---------- Maximal installable capacity per fuel type is restricted (MW): ----

QKFUELC(C,FFF)$FKPOT(C,FFF) ..
      SUM(IAGK_Y(IA,G)$(IGF(G,FFF) AND ICA(C,IA)), IGKVACCTOY(IA,G))
    + SUM(IAGK_Y(IA,G)$(IGF(G,FFF) AND ICA(C,IA)), IGKFXYMAX(IA,G))
    + SUM(IAGKN(IA,G)$(IGF(G,FFF) AND ICA(C,IA)),     VGKN(IA,G))
         =L=  FKPOT(C,FFF);

QKFUELR(IR,FFF)$FKPOT(IR,FFF)..

      SUM(IAGK_Y(IA,G)$(IGF(G,FFF) AND RRRAAA(IR,IA)), IGKVACCTOY(IA,G))
      + SUM(IAGK_Y(IA,G)$(IGF(G,FFF) AND RRRAAA(IR,IA)), IGKFXYMAX(IA,G))
      + SUM(IAGKN(IA,G)$(IGF(G,FFF) AND RRRAAA(IR,IA)),   VGKN(IA,G))
        =L=  FKPOT(IR,FFF);


QKFUELA(IA,FFF)$FKPOT(IA,FFF) ..
        SUM(IAGK_Y(IA,G)$IGF(G,FFF),  IGKVACCTOY(IA,G))
      + SUM(IAGK_Y(IA,G)$IGF(G,FFF), IGKFXYMAX(IA,G))
      + SUM(IAGKN(IA,G)$IGF(G,FFF),   VGKN(IA,G))
        =L=  FKPOT(IA,FFF);

* Electricity generation constraints by fuel (in energy), country

QGMINFUELC(C,FFF)$FGEMIN(C,FFF)..
     SUM((IA,IS3,T)$ICA(C,IA), SUM(G$(IGF(G,FFF) AND IAGK_Y(IA,G)),  IHOURSINST(IS3,T) * VGE_T(IA,G,IS3,T)))
   + SUM((IA,IS3,T)$ICA(C,IA), SUM(G$(IGF(G,FFF) AND IAGKN(IA,G)),   IHOURSINST(IS3,T) * VGEN_T(IA,G,IS3,T)))
     =G= FGEMIN(C,FFF);

QGMAXFUELC(C,FFF)$FGEMAX(C,FFF)..
    FGEMAX(C,FFF)
     =G=
     SUM((IA,IS3,T)$ICA(C,IA), SUM(G$(IGF(G,FFF) AND IAGK_Y(IA,G)),   IHOURSINST(IS3,T) * VGE_T(IA,G,IS3,T)))
   + SUM((IA,IS3,T)$ICA(C,IA), SUM(G$(IGF(G,FFF) AND IAGKN(IA,G)),    IHOURSINST(IS3,T) * VGEN_T(IA,G,IS3,T)))
;
* Electricity generation constraints by fuel (in energy), region
QGMINFUELR(IR,FFF)$FGEMIN(IR,FFF)..
     SUM((IA,IS3,T)$RRRAAA(IR,IA), SUM(G$(IGF(G,FFF) AND IAGK_Y(IA,G)),  IHOURSINST(IS3,T) * VGE_T(IA,G,IS3,T)))
   + SUM((IA,IS3,T)$RRRAAA(IR,IA), SUM(G$(IGF(G,FFF) AND IAGKN(IA,G)),   IHOURSINST(IS3,T) * VGEN_T(IA,G,IS3,T)))
     =G= FGEMIN(IR,FFF);

QGMAXFUELR(IR,FFF)$FGEMAX(IR,FFF)..
    FGEMAX(IR,FFF)
     =G=
     SUM((IA,IS3,T)$RRRAAA(IR,IA), SUM(G$(IGF(G,FFF) AND IAGK_Y(IA,G)),  IHOURSINST(IS3,T) * VGE_T(IA,G,IS3,T)))
   + SUM((IA,IS3,T)$RRRAAA(IR,IA), SUM(G$(IGF(G,FFF) AND IAGKN(IA,G)),   IHOURSINST(IS3,T) * VGEN_T(IA,G,IS3,T)))
;

* Electricity generation constraints by fuel (in energy), area

QGMINFUELA(IA,FFF)$FGEMIN(IA,FFF)..
     SUM((IS3,T), SUM(G$(IGF(G,FFF) AND IAGK_Y(IA,G)),  IHOURSINST(IS3,T) * VGE_T(IA,G,IS3,T)))
   + SUM((IS3,T), SUM(G$(IGF(G,FFF) AND IAGKN(IA,G)),   IHOURSINST(IS3,T) * VGEN_T(IA,G,IS3,T)))
     =G= FGEMIN(IA,FFF);

QGMAXFUELA(IA,FFF)$FGEMAX(IA,FFF)..
    FGEMAX(IA,FFF)
     =G=
     SUM((IS3,T), SUM(G$(IGF(G,FFF) AND IAGK_Y(IA,G)),   IHOURSINST(IS3,T) * VGE_T(IA,G,IS3,T)))
   + SUM((IS3,T), SUM(G$(IGF(G,FFF) AND IAGKN(IA,G)),    IHOURSINST(IS3,T) * VGEN_T(IA,G,IS3,T)))
;

* Fuel use constraints (in energy), area

QGMINAF(IA,FFF)$GMINF(IA,FFF)..
    SUM(IGE$(IAGK_Y(IA,IGE) AND IGF(IGE,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 VGE_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* GEFFDERATE(IA,IGE))))

    +SUM(IGH$(IAGK_Y(IA,IGH) AND IGF(IGH,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 GDATA(IGH,'GDCV')*VGH_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH))))

    +SUM(IGE$(IAGKN(IA,IGE) AND IGF(IGE,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 VGEN_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* GEFFDERATE(IA,IGE))))

    +SUM(IGH$(IAGKN(IA,IGH) AND IGF(IGH,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 GDATA(IGH,'GDCV')*VGHN_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH))))
    =G= GMINF(IA,FFF);

QGMAXAF(IA,FFF)$GMAXF(IA,FFF)..
    GMAXF(IA,FFF)
         =G=
    SUM(IGE$(IAGK_Y(IA,IGE) AND IGF(IGE,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 VGE_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* GEFFDERATE(IA,IGE))))

    +SUM(IGH$(IAGK_Y(IA,IGH) AND IGF(IGH,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 GDATA(IGH,'GDCV')*VGH_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH))))

    +SUM(IGE$(IAGKN(IA,IGE) AND IGF(IGE,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 VGEN_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* GEFFDERATE(IA,IGE))))

    +SUM(IGH$(IAGKN(IA,IGH) AND IGF(IGH,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 GDATA(IGH,'GDCV')*VGHN_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH))))
;


QGEQAF(IA,FFF)$GEQF(IA,FFF)..
    GEQF(IA,FFF)
   =E=
    SUM(IGE$(IAGK_Y(IA,IGE) AND IGF(IGE,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 VGE_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* GEFFDERATE(IA,IGE))))

    +SUM(IGH$(IAGK_Y(IA,IGH) AND IGF(IGH,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 GDATA(IGH,'GDCV')*VGH_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH))))

    +SUM(IGE$(IAGKN(IA,IGE) AND IGF(IGE,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 VGEN_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* GEFFDERATE(IA,IGE))))

    +SUM(IGH$(IAGKN(IA,IGH) AND IGF(IGH,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 GDATA(IGH,'GDCV')*VGHN_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH))))
   ;

* Fuel use constraints (in energy), region

QGMINRF(IR,FFF)$GMINF(IR,FFF)..
    SUM(IA$RRRAAA(IR,IA),
    SUM(IGE$(IAGK_Y(IA,IGE) AND IGF(IGE,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 VGE_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* GEFFDERATE(IA,IGE))))

    +SUM(IGH$(IAGK_Y(IA,IGH) AND IGF(IGH,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 GDATA(IGH,'GDCV')*VGH_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH))))

    +SUM(IGE$(IAGKN(IA,IGE) AND IGF(IGE,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 VGEN_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* GEFFDERATE(IA,IGE))))

    +SUM(IGH$(IAGKN(IA,IGH) AND IGF(IGH,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 GDATA(IGH,'GDCV')*VGHN_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH))))
    )
    =G= GMINF(IR,FFF);

QGMAXRF(IR,FFF)$GMAXF(IR,FFF)..
    GMAXF(IR,FFF)
         =G=
    SUM(IA$RRRAAA(IR,IA),
    SUM(IGE$(IAGK_Y(IA,IGE) AND IGF(IGE,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 VGE_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* GEFFDERATE(IA,IGE))))

    +SUM(IGH$(IAGK_Y(IA,IGH) AND IGF(IGH,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 GDATA(IGH,'GDCV')*VGH_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH))))

    +SUM(IGE$(IAGKN(IA,IGE) AND IGF(IGE,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 VGEN_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* GEFFDERATE(IA,IGE))))

    +SUM(IGH$(IAGKN(IA,IGH) AND IGF(IGH,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 GDATA(IGH,'GDCV')*VGHN_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH))))
    );


QGEQRF(IR,FFF)$GEQF(IR,FFF)..
    GEQF(IR,FFF)
   =E=
    SUM(IA$RRRAAA(IR,IA),
    SUM(IGE$(IAGK_Y(IA,IGE) AND IGF(IGE,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 VGE_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* GEFFDERATE(IA,IGE))))

    +SUM(IGH$(IAGK_Y(IA,IGH) AND IGF(IGH,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 GDATA(IGH,'GDCV')*VGH_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH))))

    +SUM(IGE$(IAGKN(IA,IGE) AND IGF(IGE,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 VGEN_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* GEFFDERATE(IA,IGE))))

    +SUM(IGH$(IAGKN(IA,IGH) AND IGF(IGH,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 GDATA(IGH,'GDCV')*VGHN_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH))))
    );

* Fuel use constraints (in energy), country

QGMINCF(C,FFF)$GMINF(C,FFF)..
    SUM(IA$ICA(C,IA),
    SUM(IGE$(IAGK_Y(IA,IGE) AND IGF(IGE,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 VGE_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* GEFFDERATE(IA,IGE))))

    +SUM(IGH$(IAGK_Y(IA,IGH) AND IGF(IGH,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 GDATA(IGH,'GDCV')*VGH_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH))))

    +SUM(IGE$(IAGKN(IA,IGE) AND IGF(IGE,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 VGEN_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* GEFFDERATE(IA,IGE))))

    +SUM(IGH$(IAGKN(IA,IGH) AND IGF(IGH,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 GDATA(IGH,'GDCV')*VGHN_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH))))
    )
    =G= GMINF(C,FFF);

QGMAXCF(C,FFF)$GMAXF(C,FFF)..
    GMAXF(C,FFF)
         =G=
    SUM(IA$ICA(C,IA),
    SUM(IGE$(IAGK_Y(IA,IGE) AND IGF(IGE,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 VGE_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* GEFFDERATE(IA,IGE))))

    +SUM(IGH$(IAGK_Y(IA,IGH) AND IGF(IGH,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 GDATA(IGH,'GDCV')*VGH_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH))))

    +SUM(IGE$(IAGKN(IA,IGE) AND IGF(IGE,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 VGEN_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* GEFFDERATE(IA,IGE))))

    +SUM(IGH$(IAGKN(IA,IGH) AND IGF(IGH,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 GDATA(IGH,'GDCV')*VGHN_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH))))
    );


QGEQCF(C,FFF)$GEQF(C,FFF)..
    GEQF(C,FFF)
   =E=
    SUM(IA$ICA(C,IA),
    SUM(IGE$(IAGK_Y(IA,IGE) AND IGF(IGE,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 VGE_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* GEFFDERATE(IA,IGE))))

    +SUM(IGH$(IAGK_Y(IA,IGH) AND IGF(IGH,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 GDATA(IGH,'GDCV')*VGH_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH))))

    +SUM(IGE$(IAGKN(IA,IGE) AND IGF(IGE,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 VGEN_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* GEFFDERATE(IA,IGE))))

    +SUM(IGH$(IAGKN(IA,IGH) AND IGF(IGH,FFF)),
                 IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 GDATA(IGH,'GDCV')*VGHN_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH))))
    );



*----------- Transmission (MW):------------------------------------------------

* Electricity transmission is limited by transmission capacity:

QXK(IRE,IRI,IS3,T)$(IXKINI_Y(IRE,IRI) OR IXKN(IRI,IRE) OR IXKN(IRE,IRI))..
     XKDERATE(IRE,IRI)*(
       IXKINI_Y(IRE,IRI)+IXKVACCTOY(IRE,IRI)
     + VXKN(IRE,IRI)$(IXKN(IRE,IRI) OR IXKN(IRI,IRE))+ VXKN(IRI,IRE)$(IXKN(IRE,IRI) OR IXKN(IRI,IRE))
     )
     =G=  VX_T(IRE,IRI,IS3,T);

*------------ Emissions: ------------------------------------------------------

QLIMCO2(C)$(ILIM_CO2_Y(C) LT INF)..

      SUM(IAGK_Y(IA,IGE)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_CO2(IGE) * IOF0001) *
      IOF3P6 * VGE_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* GEFFDERATE(IA,IGE))))

    + SUM(IAGK_Y(IA,IGH)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_CO2(IGH) * IOF0001) *
      IOF3P6 * GDATA(IGH,'GDCV')*VGH_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE') * GEFFDERATE(IA,IGH))))

    + SUM(IAGKN(IA,IGE)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_CO2(IGE) * IOF0001) *
      IOF3P6 * VGEN_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE') * GEFFDERATE(IA,IGE))))

    + SUM(IAGKN(IA,IGH)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_CO2(IGH) * IOF0001) *
      IOF3P6 * GDATA(IGH,'GDCV')*VGHN_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE') * GEFFDERATE(IA,IGH))))

      =L= ILIM_CO2_Y(C) ;


QLIMSO2(C)$(ILIM_SO2_Y(C) LT INF)..

      SUM(IAGK_Y(IA,IGE)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_SO2(IGE) * IOF0001) *
      IOF3P6 * VGE_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE') * GEFFDERATE(IA,IGE))))

    + SUM(IAGK_Y(IA,IGH)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_SO2(IGH) * IOF0001) *
      IOF3P6 * GDATA(IGH,'GDCV') * VGH_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE') * GEFFDERATE(IA,IGH))))

    + SUM(IAGKN(IA,IGE)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_SO2(IGE) * IOF0001) *
      IOF3P6 * VGEN_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE') * GEFFDERATE(IA,IGE))))

    + SUM(IAGKN(IA,IGH)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_SO2(IGH) * IOF0001) *
      IOF3P6 * GDATA(IGH,'GDCV') * VGHN_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE') * GEFFDERATE(IA,IGH))))


      =L= ILIM_SO2_Y(C) ;


QLIMNOX(C)$(ILIM_NOX_Y(C) LT INF)..

     SUM(IAGK_Y(IA,IGE)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (GDATA(IGE,'GDNOX') * IOF0000001) *
     IOF3P6 * VGE_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE') * GEFFDERATE(IA,IGE))))

   + SUM(IAGK_Y(IA,IGH)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (GDATA(IGH,'GDNOX') * IOF0000001) *
     IOF3P6 * GDATA(IGH,'GDCV') * VGH_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE') * GEFFDERATE(IA,IGH))))

   + SUM(IAGKN(IA,IGE)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (GDATA(IGE,'GDNOX') * IOF0000001) *
     IOF3P6 * VGEN_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE') * GEFFDERATE(IA,IGE))))

   + SUM(IAGKN(IA,IGH)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (GDATA(IGH,'GDNOX') * IOF0000001) *
     IOF3P6 * GDATA(IGH,'GDCV') * VGHN_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE') * GEFFDERATE(IA,IGH))))

      =L= ILIM_NOX_Y(C) ;


QGE2LEVEL(IA,IGE,IS3,T)$(IG2LEVEL(IGE) AND IAGK_Y(IA,IGE))..
       VGE2LEVEL(IA,IGE,IS3,'WORKDAY')$TWORKDAY(T)
     + VGE2LEVEL(IA,IGE,IS3,'WEEKEND')$TWEEKEND(T) =E= VGE_T(IA,IGE,IS3,T);

* Reserve requirement attributed to electricity demand.

QRESDE(IR,IS3,T)$IRESDE(IR) ..
      SUM(IAGK_Y(IA,IGERES)$((RRRAAA(IR,IA)) AND IGNOTETOH(IGERES)), VGE_T.UP(IA,IGERES,IS3,T)-VGE_T(IA,IGERES,IS3,T))
    + SUM(IAGKN(IA,IGERES)$((RRRAAA(IR,IA)) AND IGNOTETOH(IGERES)), VGKN(IA,IGERES)*GKDERATE(IA,IGERES,IS3)-VGEN_T(IA,IGERES,IS3,T))
         =G=
    +IRESDE(IR)*(   (IDE_T_Y(IR,IS3,T)
         + SUM(DEF_U1,VDEF_T(IR,IS3,T,DEF_U1) )
         - SUM(DEF_D1,VDEF_T(IR,IS3,T,DEF_D1) )
         + SUM(DEF_U2,VDEF_T(IR,IS3,T,DEF_U2) )
         - SUM(DEF_D2,VDEF_T(IR,IS3,T,DEF_D2) )
         + SUM(DEF_U3,VDEF_T(IR,IS3,T,DEF_U3) )
         - SUM(DEF_D3,VDEF_T(IR,IS3,T,DEF_D3) )
$ifi %loss%==212     )/(1-DISLOSS_E(IR)))
$ifi %loss%==301     )/(1-DISLOSS1E(IR)))
;


* Reserve requirement attributed to wind.
QRESWI(IR,IS3,T)$IRESWI(IR) ..
      SUM(IAGK_Y(IA,IGERES)$((RRRAAA(IR,IA)) AND IGNOTETOH(IGERES)), VGE_T.UP(IA,IGERES,IS3,T)-VGE_T(IA,IGERES,IS3,T))
    + SUM(IAGKN(IA,IGERES)$((RRRAAA(IR,IA)) AND IGNOTETOH(IGERES)), VGKN(IA,IGERES)*GKDERATE(IA,IGERES,IS3)-VGEN_T(IA,IGERES,IS3,T))
         =G=
    +IRESWI(IR)*(
          SUM(IAGK_Y(IA,IGWND)$RRRAAA(IR,IA),VGE_T(IAGK_Y,IS3,T))
         +SUM(IAGKN(IA,IGWND)$RRRAAA(IR,IA),VGEN_T(IAGKN,IS3,T))
         );


QMAXINVEST(C,FFF)$(FMAXINVEST(C,FFF) > 0) ..
         FMAXINVEST(C,FFF)
 =G=
         SUM((IAGKN(IA,G))$(ICA(C,IA) and IGF(G,FFF)), VGKN(IA,G))
;


QGMAXINVEST2(C,IGKFIND)$GROWTHCAP(C,IGKFIND)..
   SUM(IA$(IAGKN(IA,IGKFIND) AND ICA(C,IA)),VGKN(IA,IGKFIND))
   =L=
   SUM(IA$(IAGKN(IA,IGKFIND) AND ICA(C,IA)),
    (IGKFX_Y_1(IA,IGKFIND)-IGKFX_Y(IA,IGKFIND)+IGKVACCEOY(IA,IGKFIND)-IGKVACCTOY(IA,IGKFIND)))
   +IGROWTHCAP(C,IGKFIND);



*------ Begin equations used only in balbase3 ----------------------------------
$ifi not %BB3%==yes $goto label_bb3_1
QHYFXRW(IR,IS3)$(IHYFXRW(IR,IS3) GT 0)..
        IHYFXRW(IR,IS3)
 =G=
       SUM((IA,IGHYRS)$(RRRAAA(IR,IA) AND (IAGK_Y(IA,IGHYRS))),
       SUM(T,IHOURSINST(IS3,T)*VGE_T(IA,IGHYRS,IS3,T)))
     + SUM((IA,IGHYRR)$(RRRAAA(IR,IA) AND (IAGK_Y(IA,IGHYRR))),
       SUM(T,IHOURSINST(IS3,T)*VGE_T(IA,IGHYRR,IS3,T)))
     ;

QHYFXCW(C,IS3)$(SUM(IR$CCCRRR(C,IR),IHYFXRW(IR,IS3)) GT 0)..
       SUM((IA,IGHYRS)$(ICA(C,IA) AND (IAGK_Y(IA,IGHYRS))),
       SUM(T,IHOURSINST(IS3,T)*VGE_T(IA,IGHYRS,IS3,T)))
      + SUM((IA,IGHYRR)$(ICA(C,IA) AND (IAGK_Y(IA,IGHYRR))),
       SUM(T,IHOURSINST(IS3,T)*VGE_T(IA,IGHYRR,IS3,T)))
       =L= SUM(IR$CCCRRR(C,IR),IHYFXRW(IR,IS3));
$label  label_bb3_1
*------ End equations used only in Balbase3 ------------------------------------

*------ Equations for use only in Balbase4: ------------------------------------

$ifi not %BB4%==yes $goto label_BB4_2
*-------------------------------------------------------------------------------
*--------- Total generation capacity increase between two consecutive model years is found for each technology --
*-------------------------------------------------------------------------------
* Note: IYALIAS44 is aliased with Y. IY411 holds all year in model. IY410 holds all year in model except the last one. Y402 is aliased with Y.
QGKVACCTOT(IYALIAS44,IA,IGKFIND,SIMYEARS)$(IY410(IYALIAS44) AND ORD(IYALIAS44) = ORD_IY(SIMYEARS) )..

   SUM(Y402$(IY411(Y402) AND ORD(Y402) = ORD_IY(SIMYEARS+1)), VGKVACCTOT(Y402,IA,IGKFIND))

  =E=

  VGKVACCTOT(IYALIAS44,IA,IGKFIND) + VGKN(IYALIAS44,IA,IGKFIND)
;


*-------------------------------------------------------------------------------
*--------- New generation capacity is removed when lifetime years have passed --
*-------------------------------------------------------------------------------
*BB4:
* Note: IYALIAS44 is aliased with Y. IY411 holds all year in model. IY410 holds all year in model except the last one. Y402 and Y403 are aliased with Y.
QGKVACCTOY(IYALIAS44,IA,IGKFIND,SIMYEARS)$(IY410(IYALIAS44) AND ORD(IYALIAS44) = ORD_IY(SIMYEARS) )..

      SUM(Y402$(IY411(Y402) AND ORD(Y402) = ORD_IY(SIMYEARS+1)), VGKVACCTOY(Y402,IA,IGKFIND))

     =E=
      VGKVACCTOT(IYALIAS44,IA,IGKFIND) + VGKN(IYALIAS44,IA,IGKFIND) -
     SUM(Y402$( YVALUE(Y402) <=  ( SUM(Y403$(ORD(Y403) = ORD_IY(SIMYEARS+1)),YVALUE(Y403))  -    GDATA(IGKFIND, 'GDLIFETIME')    ) ),
             IVGKN(Y402,IA,IGKFIND)$(YVALUE(Y402) LT YVALUE_YALIAS) +
             VGKN(Y402,IA,IGKFIND)$(YVALUE(Y402) GE YVALUE_YALIAS)
        )
;
*-------------------------------------------------------------------------------
*---------- Capacity constraint existing technologies --------------------------
*-------------------------------------------------------------------------------

$ontext
*-------------------------------------------------------------------------------
*---------- capacity constraints existing combination technologies -------------
*-------------------------------------------------------------------------------
*BB4:
QEGKCOMB1UP(IYALIAS44,IA,IGCOMB1,S,T)$( IGKE(IGCOMB1) AND IY411(Y) AND ( ORD(Y) <> ORD_YALIAS ) AND (IAGK_Y(IYALIAS44,IA,IGCOMB1) OR IAGKN_Y(IYALIAS44,IA,IGCOMB1))    )..

         VGE_T(IA,IGCOMB1,Y,IST) =L=
         (VGKVACCTOY(IGCOMB1,IA,Y) + IGKFX_Y(IGCOMB1,IA,Y))*GKDERATE(IGCOMB1,IA,S)*GDATA(IGCOMB1,'GDCOMBSK')
;


QEGKCOMB2UP(IA,IGCOMB1,IGCOMB2,Y,IST(S,T))$(IGKE(IGCOMB1) AND GGCOMB(IGCOMB1,IGCOMB2) AND IY411(Y) AND ( ORD(Y) <> ORD_YALIAS )  AND (IAGK_Y(IA,IGCOMB1,Y) OR IAGKN_Y(IA,IGCOMB1,Y))   )..

         VGE_T(IA,IGCOMB2,Y,IST) =L=
         (VGKVACCTOY(IGCOMB1,IA,Y) + IGKFX_Y(IGCOMB1,IA,Y))*GKDERATE(IGCOMB1,IA,S)*GDATA(IGCOMB2,'GDCOMBSK')
;

QHGKCOMB1UP(IA,IGCOMB1,Y,IST(S,T))$(IGKH(IGCOMB1) AND IY(Y) AND ( ORD(Y) <> ORD_YALIAS )   )..

         VGH_T(IA,IGCOMB1,Y,IST) =L=
         (VGKVACCTOY(IGCOMB1,IA,Y) + IGKFX_Y(IGCOMB1,IA,Y))*GKDERATE(IGCOMB1,IA,S)*GDATA(IGCOMB1,'GDCOMBSK')
;

QHGKCOMB2UP(IA,IGCOMB1,IGCOMB2,Y,IST(S,T))$(IGKE(IGCOMB1) AND GGCOMB(IGCOMB1,IGCOMB2) AND IY(Y) AND ( ORD(Y) <> ORD_YALIAS )  )..

         VGH_T(IA,IGCOMB2,Y,IST)$(IGKH(IGCOMB1) AND GGCOMB(IGCOMB1,IGCOMB2)) =L=
         (VGKVACCTOY(IGCOMB1,IA,Y) + IGKFX_Y(IGCOMB1,IA,Y))*GKDERATE(IGCOMB1,IA,S)*GDATA(IGCOMB2,'GDCOMBSK')
;
$offtext
*------ End equations for use only in Balbase4 ---------------------------------
$label label_BB4_2

*-------------------------------------------------------------------------------
*----- Any equations for addon to be placed here: ------------------------------
*-------------------------------------------------------------------------------

* These add-on equations pertain to combination technologies.
$ifi %COMBTECH%==yes $include '../../base/addons/combtech/combEQ.inc';
* This file includes:
*EQUATIONS
*   QECOMBGLK(AAA,G,S,T)   'Combination technology, sum of production limit, electricity'
*   QECOMBSLO(AAA,G,S,T)   'Combination technology, minimum share of total production, electricity'
*   QECOMBSUP(AAA,G,S,T)   'Combination technology, maximum share of total production, electricity'
*   QHCOMBGLK(AAA,G,S,T)   'Combination technology, sum of production limit, heat'
*   QHCOMBSLO(AAA,G,S,T)   'Combination technology, minimum share of total production, heat'
*   QHCOMBSUP(AAA,G,S,T)   'Combination technology, maximum share of total production, heat'
*   QNECOMBGLK(AAA,G,S,T)  'New combination technology, sum of production limit, electricity'
*   QNECOMBSLO(AAA,G,S,T)  'New combination technology, minimum share of total production, electricity'
*   QNECOMBSUP(AAA,G,S,T)  'New combination technology, maximum share of total production, electricity'
*   QNHCOMBGLK(AAA,G,S,T)  'New combination technology, sum of production limit, heat'
*   QNHCOMBSLO(AAA,G,S,T)  'New combination technology, minimum share of total production, heat'
*   QNHCOMBSUP(AAA,G,S,T)  'New combination technology, maximum share of total production, heat';

* These add-on equations pertain to price sensitive electricity exchange with
* third countries.
$ifi %X3V%==yes $include '../../base/addons/x3v/model/x3veq.inc';

* These add-on equations pertain to natural gas.
$ifi %GAS%==yes $include '../../base/addons/gas/gasequations.inc';
* This file includes:
* [list equations]
$ifi %CAES%==yes $INCLUDE '../../base/addons/CAES/CAESequations.inc';

* These add-on equations pertain to hydrogen.
$ifi %H2%==yes $include '../../base/addons/Hydrogen/H2equations.inc';

* These add-on equations pertain to transport(KHED)
$ifi %TSP%==yes $INCLUDE '../../base/addons/Transport/TSPEquations.inc';

* These add-on equations pertain to targets for wind power.
$ifi not %WINDTARGET%==yes $goto end_windtarget_eq
$ifi EXIST 'wndtargetdata.inc' $include 'wndtargetdata.inc';
$ifi not EXIST 'wndtargetdata.inc'$INCLUDE '../../base/addons/windtarget/wndtargetdata.inc';
$INCLUDE '../../base/addons/windtarget/windequations.inc';
$label end_windtarget_eq

* These add-on equations pertain to heat transmission.
$ifi %HEATTRANS%==yes $include '../../base/addons/heattrans/model/htequations.inc';

* These add-on equations pertain to targets for renewables.
$ifi %RENEWTARGET%==yes $INCLUDE '../../base/addons/renewtarget/renewdata.inc';
$ifi %RENEWTARGET%==yes $INCLUDE '../../base/addons/renewtarget/reneweqn.inc';

* These add-on equations pertain to capping fossil fuel consumption.
$ifi %FOSSILTARGET%==yes $INCLUDE '../../base/addons/fossiltarget/fossildata.inc';
$ifi %FOSSILTARGET%==yes $INCLUDE '../../base/addons/fossiltarget/fossileqn.inc';

$ifi %REShareE%==yes $include  '../../base/addons/REShareE/RESEeqns.inc';
$ifi %REShareEH%==yes $include '../../base/addons/REShareEH/RESEHeqns.inc';

$ifi %AGKNDISC%==yes  $include  '../../base/addons/AGKNDISC/AGKNDISCequations.inc';

*-------------------------------------------------------------------------------
*----- End: Any equations for addon to be placed here. -------------------------
*-------------------------------------------------------------------------------



*-------------------------------------------------------------------------------
*  End: Declaration and definition of EQUATIONS
*-------------------------------------------------------------------------------



*-------------------------------------------------------------------------------
* Definition of the models:
*-------------------------------------------------------------------------------

MODEL BALBASE1 'Balmorel model without endogeneous investments'
/
*--- Objective function --------------------------------------------------------
                                QOBJ
*--- Balance equations ---------------------------------------------------------
                                QEEQ
                                QHEQ
*--- Feasible generation region ------------------------------------------------
                                QGCBGBPR
                                QGCBGEXT
                                QGCVGEXT
                                QGGETOH
$ifi %BASELOADSERVICE%==yes     QRESWI
$ifi %BASELOADSERVICE%==yes     QRESDE
*--- Storage restructions ------------------------------------------------------
                                QHYRSSEQ
                                QESTOVOLT
                                QESTOLOADT
                                QHSTOVOLT
                                QHSTOLOADT
*--- Transmission capacity -----------------------------------------------------
                                QXK

*--- Electricity generation restrictions by fuel -------------------------------
                                QGMINFUELC
                                QGMAXFUELC
                                QGMINFUELR
                                QGMAXFUELR
                                QGMINFUELA
                                QGMAXFUELA
*--- Fuel consumption restrictions ---------------------------------------------
                                QGMINCF
                                QGMAXCF
                                QGEQCF
                                QGMINRF
                                QGMAXRF
                                QGEQRF
                                QGMINAF
                                QGMAXAF
                                QGEQAF
*--- Emissions restrictions ----------------------------------------------------
                                QLIMCO2
                                QLIMSO2
                                QLIMNOX
*--- Operational restrictions --------------------------------------------------
                                QGE2LEVEL

*----- Any equations for addon to be placed here: ------------------------------
$ifi %COMBTECH%==yes $include '../../base/addons/combtech/combbb1.inc';
$ifi %X3VfxQ%==yes              QX3VBAL
$ifi %GAS%==yes $INCLUDE '../../base/addons/gas/gasbb1.inc';
$ifi %CAES%==yes $INCLUDE '../../base/addons/CAES/CAESbb2.inc';
$ifi %H2%==yes $INCLUDE '../../base/addons/Hydrogen/H2bb1.inc';
$ifi %RENEWTARGET%==yes QRENEW
$ifi %WINDTARGET%==yes $include '../../base/addons/windtarget/wndtargetbb12.inc';
* This file contains equations for transport technology(KHED)
$ifi %TSP%==yes $INCLUDE '../../base/addons/Transport/TSPbb1.inc';
$ifi %FOSSILTARGET%==yes QFOSSILTARGET
$ifi %HEATTRANS%==yes $include '../../base/addons/heattrans/model/htbb1.inc';

*----- End: Any equations for addon to be placed here. -------------------------

/;

* Scale the model: only equation QOBJ is really badly scaled:
BALBASE1.SCALEOPT=1;
QOBJ.SCALE=IOF1000000;




MODEL BALBASE2  'Balmorel model with endogeneous investments'
/
*--- Objective function --------------------------------------------------------
                                QOBJ
*--- Balance equations ---------------------------------------------------------
                                QEEQ
                                QHEQ
*--- Feasible generation region ------------------------------------------------
                                QGCBGBPR
                                QGCBGEXT
                                QGCVGEXT
                                QGGETOH
                                QGNCBGBPR
                                QGNCBGEXT
                                QGNCVGEXT
                                QGNGETOH
$ifi %BASELOADSERVICE%==yes     QRESWI
$ifi %BASELOADSERVICE%==yes     QRESDE
*--- Generation capacities -----------------------------------------------------
                                QGEKNT
                                QGHKNT
                                QGKNWND
                                QGKNHYRR
                                QGKNSOLE
                                QGKNSOLH
*--- Storage restrictions ------------------------------------------------------

                                QHYRSSEQ
                                QESTOVOLT
                                QESTOLOADT
                                QHSTOVOLT
                                QHSTOLOADT
                                QHSTOLOADTLIM
                                QESTOLOADTLIM
                                QHSTOVOLTLIM
                                QESTOVOLTLIM

*--- Transmission capacity -----------------------------------------------------
                                QXK
*--- Fuel capacity restrictions ------------------------------------------------
                                QKFUELC
                                QKFUELR
                                QKFUELA

*--- Electricity generation restrictions by fuel -------------------------------
                                QGMINFUELC
                                QGMAXFUELC
                                QGMINFUELR
                                QGMAXFUELR
                                QGMINFUELA
                                QGMAXFUELA
*--- Fuel consumption restrictions ---------------------------------------------
                                QGMINCF
                                QGMAXCF
                                QGEQCF
                                QGMINRF
                                QGMAXRF
                                QGEQRF
                                QGMINAF
                                QGMAXAF
                                QGEQAF
*--- Emissions restrictions ----------------------------------------------------
                                QLIMCO2
                                QLIMSO2
                                QLIMNOX
*--- Operational restrictions --------------------------------------------------
                                QGE2LEVEL

*----- Any equations for addon to be placed here: ------------------------------
* These add-on equations pertain to transport(KHED)
$ifi %TSP%==yes $INCLUDE '../../base/addons/Transport/TSPbb1.inc';
*--- Capacity restrictions for decommisioning ----------------------------------
$ifi %DECOMPEFF%==yes           QGEKOT
$ifi %DECOMPEFF%==yes           QGHKOT
$ifi %DECOMPEFF%==yes           QGKOHYRR
$ifi %DECOMPEFF%==yes           QGKOWND
$ifi %DECOMPEFF%==yes           QGKOSOLE
*--- Investment restricitions --------------------------------------------------
$ifi %BASELOADSERVICE%==yes     QMAXINVEST
$ifi %X3VfxQ%==yes              QX3VBAL
$ifi %WINDTARGET%==yes $include '../../base/addons/windtarget/wndtargetbb12.inc';
$ifi %COMBTECH%==yes $include '../../base/addons/combtech/combbb2.inc';
$ifi %GAS%==yes $INCLUDE '../../base/addons/gas/gasbb2.inc';
$ifi %CAES%==yes $INCLUDE '../../base/addons/CAES/CAESbb2.inc';
$ifi %H2%==yes $INCLUDE '../../base/addons/Hydrogen/H2bb1.inc'
$ifi %FOSSILTARGET%==yes QFOSSILTARGET
$ifi %RENEWTARGET%==yes QRENEW
$ifi %HEATTRANS%==yes $include '../../base/addons/heattrans/model/htbb1.inc';
$ifi %REShareE%==yes QREShareE
$ifi %REShareEH%==yes QREShareEH

$ifi %AGKNDISC%==yes  QAGKNDISCCONT
$ifi %AGKNDISC%==yes  QAGKNDISC01

*----- End: Any equations for addon to be placed here. -------------------------
/;

* Scale the model: only equation QOBJ is really badly scaled:
BALBASE2.SCALEOPT=1;
QOBJ.SCALE=IOF1000000;

MODEL BALBASE3 'Balmorel model without endogeneous investments, simulating each season individually'
/
*--- Objective function --------------------------------------------------------
                                QOBJ
*--- Balance equations ---------------------------------------------------------
                                QEEQ
                                QHEQ
*--- Feasible generation region ------------------------------------------------
                                QGCBGBPR
                                QGCBGEXT
                                QGCVGEXT
                                QGGETOH
*--- Storage restrictions ------------------------------------------------------
                                QESTOVOLT
                                QESTOLOADT
                                QHSTOVOLT
                                QHSTOLOADT
*--- Transmission capacity -----------------------------------------------------
                                QXK
*--- Operational restrictions --------------------------------------------------
                                QGE2LEVEL
*--- Additional hydro restrictions ---------------------------------------------
$ifi not %WATERVAL%==yes        QHYFXRW    /* An alternative to QHYFXCW */
*$ifi not %WATERVAL%==yes       QHYFXCW    /* An alternative to QHYFXRW */
*----- Any equations for addon to be placed here: ------------------------------
$ifi %COMBTECH%==yes $include '../../base/addons/combtech/combbb1.inc';
$ifi %GAS%==yes $INCLUDE '../../base/addons/gas/gasbb3.inc';
$ifi %H2%==yes $INCLUDE '../../base/addons/Hydrogen/H2bb3.inc';
$ifi %CAES%==yes $INCLUDE '../../base/addons/CAES/CAESbb2.inc';
* These add-on equations pertain to transport(KHED)
$ifi %TSP%==yes $INCLUDE '../../base/addons/Transport/TSPbb3.inc';
$ifi %HEATTRANS%==yes $include '../../base/addons/heattrans/model/htbb1.inc';
*----- End: Any equations for addon to be placed here. -------------------------
/;

* Scale the model: only equation QOBJ is really badly scaled:
BALBASE3.SCALEOPT=1;
QOBJ.SCALE=IOF1000000;



*-------------------------------------------------------------------------------
*----- Any further models to be defined here:
*-------------------------------------------------------------------------------


*-------------------------------------------------------------------------------
*----- End: Any further models to be defined here
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
*----- End of definition of models ---------------------------------------------
*-------------------------------------------------------------------------------


* The input data are subject to a certain control for 'reasonable' values.
* The errors are checked by the code in the files ERRORx.INC

$INCLUDE '../../base/logerror/logerinc/error2.inc';
$ifi %COMBTECH%==yes  $INCLUDE  '../../base/addons/combtech/comberr2.inc';


* The following file contains definitions of a number of temporary parameters
* and sets that may be used for printout of simulation results.
$ifi %PRINTFILES%==yes $INCLUDE '../../base/output/printout/printinc/print2.inc';

* The following file contains file and parameter definitions for the economic
* output module.
$ifi %ECONOMIC%==yes $INCLUDE '../../base/processing/economic/eco_def.inc';


*-------------------------------------------------------------------------------
$ifi %CREATETIME%==yes $INCLUDE '../../base/model/createtime.inc';
$ifi %CREATETIME%==yes $goto ENDOFMODEL
* Here the model to be solved/simulated is included:

$ifi %bb1%==yes
$if EXIST 'bb123.sim' $INCLUDE 'bb123.sim';
$ifi %bb1%==yes
$if not EXIST 'bb123.sim' $INCLUDE '../../base/model/bb123.sim';

$ifi %bb2%==yes
$if EXIST 'bb123.sim' $INCLUDE 'bb123.sim';
$ifi %bb2%==yes
$if not EXIST 'bb123.sim' $INCLUDE '../../base/model/bb123.sim';

$ifi %bb3%==yes
$if EXIST 'bb123.sim' $INCLUDE 'bb123.sim';
$ifi %bb3%==yes
$if not EXIST 'bb123.sim' $INCLUDE '../../base/model/bb123.sim';


$ifi %bb4%==yes $INCLUDE '../../base/addons/BB4/BB4overview.inc';



*--- Results which can be transfered between simulations are placed here: ------
$ifi %bb1%==yes execute_unload  '../../base/data/HYFXRW.gdx',HYFXRW;
$ifi %bb1%==yes execute_unload  '../../base/data/WATERVAL.gdx',WATERVAL;
$ifi %bb2%==yes execute_unload  '../../base/data/HYFXRW.gdx',HYFXRW;
$ifi %bb2%==yes execute_unload  '../../base/data/WATERVAL.gdx',WATERVAL;


$ifi %MAKEINVEST%==yes execute_unload '../../base/data/GKVACC.gdx', GKVACC;
$ifi %MAKEINVEST%==yes execute_unload '../../base/data/GKVACCDECOM.gdx', GKVACCDECOM;
$ifi %MAKEINVEST%==yes execute_unload '../../base/data/GVKGN.gdx', GVKGN;
$ifi %MAKEINVEST%==yes execute_unload '../../base/data/XKACC.gdx', XKACC;


$ifi %H2%==yes execute_unload '../../base/addons/Hydrogen/H2STOVOL_START.gdx',H2STOVOL_START;
$ifi %GAS%==yes $INCLUDE '../../base/addons/gas/gasgdx.inc';
$ifi %X3V%==yes $INCLUDE '../../base/addons/x3v/model/x3vgdx.inc';
*--- End: Results which can be transfered between simulations are placed here --


*--- Results collection and comparison -----------------------------------------
* Merge simulation years:
$ifi %MERGESAVEPOINTRESULTS%==yes  execute "gdxmerge %relpathModel%..\output\temp\*.gdx";

* Rename merged.gdx to case identification.
* LARS20080916: Currently no facility for merging cases, however the final GDX and MDB are made
* as though this were an option.
*$ifi %GDXMERGESIMYEARS%==yes  execute "move merged.gdx %relpathGDXsimyears%%CASEID%.gdx";
$ifi %MERGESAVEPOINTRESULTS%==yes  execute "move merged.gdx %CASEID%.gdx";
$ifi %MERGESAVEPOINTRESULTS%==yes  execute "gdxmerge %CASEID%.gdx";
$ifi %MERGESAVEPOINTRESULTS%==yes  execute "move merged.gdx %relpathoutput%%CASEID%-Results.gdx";
$ifi %MERGESAVEPOINTRESULTS%==yes  execute "move %CASEID%.gdx %relpathoutput%%CASEID%.gdx";
$ifi %MERGEDSAVEPOINTRESULTS2MDB%==yes execute '=gdx2access %relpathoutput%%CASEID%-Results.gdx';


$ifi %comparewithbase%==yes   putclose  fileCOMPAREWITHBASEbat 'move  ' '%relpathModel%''..\..\output\BASE.gdx '  '%relpathoutput%BASE.gdx';

* Make an MS Access database from comparison results file.
* Irrelevant $ifi %MAKEACCESS%==yes execute '=gdx2access %CASEID%-COMPARE.gdx';
*--- End: Results collection and comparison ------------------------------------
$ifi %INPUTDATA2GDX%==yes execute 'move "%relpathModel%..\output\temp\1INPUT.gdx" "%relpathInputdata2GDX%INPUTDATAOUT.gdx"';
* Transfer inputdata a seperate Access file:
$ifi %INPUTDATAGDX2MDB%==yes execute "=GDX2ACCESS %relpathInputdata2GDX%INPUTDATAOUT.gdx";
* Transfer to Excel, read the identifiers to be transferred from file inputdatagdx2xls.txt:
* Note: presently not working (the relevant data is not set i file inputdatagdx2xls.txt):
* NOTWORKING (i.e. you MUST have '$setglobal INPUTDATAGDX2XLS'): Note:  GAMS version 22.7 and later have better support for this....
$ifi %INPUTDATAGDX2XLS%==yes  execute  "GDXXRW.EXE Input=%relpathInputdata2GDX%INPUTDATAOUT.gdx  Output=%relpathInputdata2GDX%INPUTDATAOUT.xls  @%relpathModel%inputdatagdx2xls.txt";



*----- End of model:------------------------------------------------------------
$label ENDOFMODEL
*----- End of model ------------------------------------------------------------

