* File Balmorel.gms
$TITLE Balmorel version 3.03 (June 2018; latest 20180614)

SCALAR IBALVERSN 'This version of Balmorel' /303.20180614/;
* Efforts have been made to make a good model.
* However, most probably the model is incomplete and subject to errors.
* It is distributed with the idea that it will be usefull anyway,
* and with the purpose of getting the essential feedback,
* which in turn will permit the development of improved versions
* to the benefit of other user.
* Hopefully it will be applied in that spirit.

* All GAMS code of the Balmorel model is distributed under ICS license,
* see the license file in the base/model folder.


*-------------------------------------------------------------------------------
*-------------------------------------------------------------------------------
*-------------------------------------------------------------------------------


* This is a preliminary version of Balmorel 3.03.
* It is intended for review and commenting.
* See a short list of changes since previous version 3.02 in base/documentation/Balmorel303.txt.
* It is scheduled that a final version 3.03 will be available early 2017.

*-------------------------------------------------------------------------------
*-------------------------------------------------------------------------------
*-------------------------------------------------------------------------------


* GAMS options are $included from file balgams.opt.
* In order to make them apply globally, the option $ONGLOBAL will first be set here:
$ONGLOBAL

$ifi %system.filesys%==UNIX
execute 'chmod  -R ug+rw "../.."';

* The balgams file holds control settings for GAMS.
* Use local file if it exists, otherwise use the one in folder  ../../base/model/.
$ifi     exist 'balgams.opt'  $include  'balgams.opt';
$ifi not exist 'balgams.opt'  $include  '../../base/model/balgams.opt';

* The balopt file holds option (control) settings for the Balmorel model.
* Use local file if it exists, otherwise use the one in folder  ../../base/model/.


$ifi     exist 'balopt.opt'  $include                  'balopt.opt';
$ifi not exist 'balopt.opt'  $include '../../base/model/balopt.opt';

$ifi %system.filesys%==UNIX
execute 'chmod  -R ug+rw "../.."';

* If merging of savepoint files is to be performed,
* make sure that there are no gdx files initially in applied folders:
$ifi %system.filesys%==UNIX
$ifi %MERGESAVEPOINTRESULTS%==yes  execute "rm *.gdx";
$ifi %system.filesys%==MSNT
$ifi %MERGESAVEPOINTRESULTS%==yes  execute "del *.gdx";
$ifi %system.filesys%==UNIX
$ifi %MERGESAVEPOINTRESULTS%==yes  execute "rm ../output/temp/*.gdx";
$ifi %system.filesys%==MSNT
$ifi %MERGESAVEPOINTRESULTS%==yes  execute "del ..\output\temp\*.gdx";

*-------------------------------------------------------------------------------
*-------------------------------------------------------------------------------
*---- Some generally applicable stuff: -----------------------------------------
*-------------------------------------------------------------------------------


* The following may be used in display, put or execute_unload statements (the text, not the value, holds relevant information)
SCALAR SystemDateTime "%system.date%,  %system.time%" /NA/;

* Displaying only a text string will not be accessible through the 'table of content' on the .lst file, therefore this
SCALAR INFODISPLAY  "See information next:" /NA/;
DISPLAY INFODISPLAY, "Balmorel run stared at", SystemDateTime;

* Convenient Factors, typically relating Output and Input:
SCALAR IOF100     'Multiplier 100'        /100/;
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
SCALAR IOF1_      'Multiplier 1 (used with QOBJ and derivation of marginal values)'   /1/;!! special, possibly to disappear in future versions
* Scalars for occational use, their meaning will be context dependent:
SCALAR ISCALAR1   '(Context dependent)';
SCALAR ISCALAR2   '(Context dependent)';
SCALAR ISCALAR3   '(Context dependent)';
SCALAR ISCALAR4   '(Context dependent)';
SCALAR ISCALAR5   '(Context dependent)';

* Initialisations of printing of log and error files and messages:
$INCLUDE '../../base/logerror/logerinc/error1.inc';

* Ensuring existence of needed output folders:
$ifi not dexist "../../simex"            execute 'mkdir -p "../../simex"';
$ifi not dexist "../logerror/logerinc"   execute 'mkdir -p "../logerror/logerinc"';
$ifi not dexist "../output/economic"     execute 'mkdir -p "../output/economic"';
$ifi not dexist "../output/inputout"     execute 'mkdir -p "../output/inputout"';
$ifi not dexist "../output/printout"     execute 'mkdir -p "../output/printout"';
$ifi not dexist "../output/temp"         execute 'mkdir -p "../output/temp"';


*-------------------------------------------------------------------------------
*---- End: Some generally applicable stuff -------------------------------------
*-------------------------------------------------------------------------------



*-------------------------------------------------------------------------------
*-------------------------------------------------------------------------------
* In case of Model Balbase4 the following included file substitutes the remaining part of the present file Balmorel.gms:
$ifi %BB4%==yes $include '../../base/model/Balmorelbb4.inc';
$ifi %BB4%==yes $goto ENDOFMODEL
*-------------------------------------------------------------------------------
*-------------------------------------------------------------------------------



*-------------------------------------------------------------------------------
*-------------------------------------------------------------------------------
*---- Declarations and inclusion of data files: --------------------------------
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
*---- User defined SETS and ACRONYMS needed for data entry: --------------------
*-------------------------------------------------------------------------------

* Declarations: ----------------------------------------------------------------

* SETS:
* Geography related:
SET CCCRRRAAA         'All geographical entities (CCC + RRR + AAA)';
SET CCC(CCCRRRAAA)    'All Countries';
SET RRR(CCCRRRAAA)    'All regions';
SET AAA(CCCRRRAAA)    'All areas';
SET CCCRRR(CCC,RRR)   'Regions in countries';
SET RRRAAA(RRR,AAA)   'Areas in regions';
* Time related:
SET YYY               'All years';
SET SSS               'All seasons';
SET TTT               'All time periods';
* Technology and fuel related:
SET GGG               'All generation technologies';
SET GDATASET          'Generation technology data';
SET FFF               'Fuels';
SET FDATASET          'Characteristics of fuels';
SET HYRSDATASET       'Characteristics of hydro reservoirs';
* Demand related:
SET DEUSER            "Electricity demand user groups. Set must include element RESE for holding demand not included in any other user group";
SET DHUSER            "Heat demand user groups. Set must include element RESH for holding demand not included in any other user group";
/*  addon dflexquant
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
*/
SET MPOLSET           'Emission and other policy data';
SET C(CCC)            'Countries in the simulation';
SET G(GGG)            'Generation technologies in the simulation';
SET AGKN(AAA,GGG)     'Areas for possible location of new technologies';
SET Y(YYY)            'Years in the simulation';
SET S(SSS)            'Seasons in the simulation';
SET T(TTT)            'Time periods within the season in the simulation';
SET TWORKDAY(TTT)     'Time segments, T, in workdays';
SET TWEEKEND(TTT)     'Time segments, T, in weekends';

* Internal set IGGGALIAS may be used in the $included data files:
ALIAS(GGG,IGGGALIAS);
* Set CCCRRRAAAALIAS may be used in the $included data files:
ALIAS(CCCRRRAAA,CCCRRRAAAALIAS);

* ACRONYMS:
* ACRONYMS for technology types
* Each of the following ACRONYMS symbolise a technology type.
* They correspond in a one-to-one way with the internal sets IGCND, IGBRP etc. below.
* They should generally not be changed.
* New technology types may be added only if also code specifying their properties are added.
ACRONYMS  GCND, GBPR, GEXT, GHOB, GETOH, GHSTO, GESTO, GHSTOS, GESTOS, GHYRS, GHYRR, GWND, GSOLE, GSOLH, GWAVE;

* ACRONYMS for user defined fuels will be given as part of file FFF.inc

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
$if     EXIST '../data/GGG.inc' $INCLUDE         '../data/GGG.inc';
$if not EXIST '../data/GGG.inc' $INCLUDE '../../base/data/GGG.inc';
%semislash%;

SET GDATASET           'Generation technology data' %semislash%
$if     EXIST '../data/GDATASET.inc' $INCLUDE      '../data/GDATASET.inc';
$if not EXIST '../data/GDATASET.inc' $INCLUDE '../../base/data/GDATASET.inc';
%semislash%;

* The following file FFF.inc contains a set and, as exception, also acronyms:
SET FFF                'Fuels'  %semislash%
$if     EXIST '../data/FFF.inc' $INCLUDE      '../data/FFF.inc';
$if not EXIST '../data/FFF.inc' $INCLUDE '../../base/data/FFF.inc';
%semislash%;

SET FDATASET           'Characteristics of fuels ' %semislash%
$if     EXIST '../data/FDATASET.inc' $INCLUDE         '../data/FDATASET.inc';
$if not EXIST '../data/FDATASET.inc' $INCLUDE '../../base/data/FDATASET.inc';
%semislash%;

SET HYRSDATASET  'Characteristics of hydro reservoirs' %semislash%
$if     EXIST '../data/HYRSDATASET.inc' $INCLUDE         '../data/HYRSDATASET.inc';
$if not EXIST '../data/HYRSDATASET.inc' $INCLUDE '../../base/data/HYRSDATASET.inc';
%semislash%;

SET DEUSER      "Electricity demand user groups. Set must include element RESE for holding demand not included in any other user group"  %semislash%
$if     EXIST '../data/DEUSER.inc' $INCLUDE         '../data/DEUSER.inc';
$if not EXIST '../data/DEUSER.inc' $INCLUDE '../../base/data/DEUSER.inc';
%semislash%;


SET DF_QP  'Quantity and price information for elastic demands' %semislash%
$if     EXIST '../data/DF_QP.inc' $INCLUDE         '../data/DF_QP.inc';
$if not EXIST '../data/DF_QP.inc' $INCLUDE '../../base/data/DF_QP.inc';
%semislash%;

* ------------------------------------------------------------------------------
$ifi not %dflexquant%==yes $goto dflexquantend1

SET DEF  'Steps in elastic electricity demand'  %semislash%
$if     EXIST '../data/DEF.inc' $INCLUDE         '../data/DEF.inc';
$if not EXIST '../data/DEF.inc' $INCLUDE '../../base/data/DEF.inc';
%semislash%;

SET DEF_D1(DEF)   'Downwards steps in elastic el. demand, relative data format' %semislash%
$if     EXIST '../data/DEF_D1.inc' $INCLUDE         '../data/DEF_D1.inc';
$if not EXIST '../data/DEF_D1.inc' $INCLUDE '../../base/data/DEF_D1.inc';
%semislash%;

SET DEF_U1(DEF)   'Upwards steps in elastic el. demand, relative data format' %semislash%
$if     EXIST '../data/DEF_U1.inc' $INCLUDE         '../data/DEF_U1.inc';
$if not EXIST '../data/DEF_U1.inc' $INCLUDE '../../base/data/DEF_U1.inc';
%semislash%;

SET DEF_D2(DEF)   'Downwards steps in elastic el. demand, absolute Money and MW-incremental data format'%semislash%
$if     EXIST '../data/DEF_D2.inc' $INCLUDE         '../data/DEF_D2.inc';
$if not EXIST '../data/DEF_D2.inc' $INCLUDE '../../base/data/DEF_D2.inc';
%semislash%;

SET DEF_U2(DEF)   'Upwards steps in elastic el. demand, absolute Money and MW-incremental data format' %semislash%
$if     EXIST '../data/DEF_U2.inc' $INCLUDE         '../data/DEF_U2.inc';
$if not EXIST '../data/DEF_U2.inc' $INCLUDE '../../base/data/DEF_U2.inc';
%semislash%;

SET DEF_D3(DEF)   'Downwards steps in elastic el. demand, absolute Money and fraction of nominal demand data format' %semislash%
$if     EXIST '../data/DEF_D3.inc' $INCLUDE         '../data/DEF_D3.inc';
$if not EXIST '../data/DEF_D3.inc' $INCLUDE '../../base/data/DEF_D3.inc';
%semislash%;

SET DEF_U3(DEF)   'Upwards steps in elastic el. demand, absolute Money and fraction of nominal demand data format' %semislash%
$if     EXIST '../data/DEF_U3.inc' $INCLUDE         '../data/DEF_U3.inc';
$if not EXIST '../data/DEF_U3.inc' $INCLUDE '../../base/data/DEF_U3.inc';
%semislash%;
* ------------------------------------------------------------------------------
$label dflexquantend1


SET DHUSER "Heat demand user groups. Set must include element RESH for holding demand not included in any other user group" %semislash%
$if     EXIST '../data/DHUSER.inc' $INCLUDE         '../data/DHUSER.inc';
$if not EXIST '../data/DHUSER.inc' $INCLUDE '../../base/data/DHUSER.inc';
%semislash%;

SET DHF  'Steps in elastic heat demand' %semislash%
$if     EXIST '../data/DHF.inc' $INCLUDE         '../data/DHF.inc';
$if not EXIST '../data/DHF.inc' $INCLUDE '../../base/data/DHF.inc';
%semislash%;

SET DHF_D1(DHF)    'Downwards steps in elastic heat demand, relative data format' %semislash%
$if     EXIST '../data/DHF_D1.inc' $INCLUDE         '../data/DHF_D1.inc';
$if not EXIST '../data/DHF_D1.inc' $INCLUDE '../../base/data/DHF_D1.inc';
%semislash%;

SET DHF_U1(DHF)    'Upwards steps in elastic heat demand, relative data format' %semislash%
$if     EXIST '../data/DHF_U1.inc' $INCLUDE         '../data/DHF_U1.inc';
$if not EXIST '../data/DHF_U1.inc' $INCLUDE '../../base/data/DHF_U1.inc';
%semislash%;

SET DHF_D2(DHF)    'Downwards steps in elastic heat demand, absolute Money and MW-incremental data format' %semislash%
$if     EXIST '../data/DHF_D2.inc' $INCLUDE         '../data/DHF_D2.inc';
$if not EXIST '../data/DHF_D2.inc' $INCLUDE '../../base/data/DHF_D2.inc';
%semislash%;

SET DHF_U2(DHF)    'Upwards steps in elastic heat demand, absolute Money and MW-incremental data format' %semislash%
$if     EXIST '../data/DHF_U2.inc' $INCLUDE         '../data/DHF_U2.inc';
$if not EXIST '../data/DHF_U2.inc' $INCLUDE '../../base/data/DHF_U2.inc';
%semislash%;

SET DHF_D3(DHF)    'Downwards steps in elastic heat demand, absolute Money and fraction of nominal demand data format' %semislash%
$if     EXIST '../data/DHF_D3.inc' $INCLUDE         '../data/DHF_D3.inc';
$if not EXIST '../data/DHF_D3.inc' $INCLUDE '../../base/data/DHF_D3.inc';
%semislash%;

SET DHF_U3(DHF)    'Upwards steps in elastic heat demand, absolute Money and fraction of nominal demand data format' %semislash%
$if     EXIST '../data/DHF_U3.inc' $INCLUDE         '../data/DHF_U3.inc';
$if not EXIST '../data/DHF_U3.inc' $INCLUDE '../../base/data/DHF_U3.inc';
%semislash%;

SET MPOLSET  'Emission and other policy data'   %semislash%
$if     EXIST '../data/MPOLSET.inc' $INCLUDE         '../data/MPOLSET.inc';
$if not EXIST '../data/MPOLSET.inc' $INCLUDE '../../base/data/MPOLSET.inc';
%semislash%;

SET C(CCC)    'Countries in the simulation'  %semislash%
$if     EXIST '../data/C.inc' $INCLUDE         '../data/C.inc';
$if not EXIST '../data/C.inc' $INCLUDE '../../base/data/C.inc';
%semislash%;

SET G(GGG)    'Generation technologies in the simulation'  %semislash%
$if     EXIST '../data/G.inc' $INCLUDE         '../data/G.inc';
$if not EXIST '../data/G.inc' $INCLUDE '../../base/data/G.inc';
%semislash%;

SET AGKN(AAA,GGG)   'Areas for possible location of new technologies'   %semislash%
$if     EXIST '../data/AGKN.inc' $INCLUDE         '../data/AGKN.inc';
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


* Printing of data to the list file controlled by %ONOFFDATALISTING% and %ONOFFCODELISTING%
* (see file balgams.opt):
%ONOFFCODELISTING%

*------------------------------------------------------------------------------
* Declaration of internal sets:
*------------------------------------------------------------------------------
* Internal sets and aliases in relation to geography.
* Note: although it is possible, you should generally not (i.e., don't!) use
* the following internal sets for data entry or data assignments
* (it may be impossible in future versions).
SET IR(RRR)            'Regions in the simulation';
SET IA(AAA)            'Areas in the simulation';
SET ICA(CCC,AAA)       'Assignment of areas to countries in the simulation';
* The simple way to limit the geographical scope of the model is to specify
* the set C as a proper subset of the set CCC in the input data,
* because the following mechanism will automatically exclude all regions
* and areas not in any country in C.
ICA(CCC,AAA) = YES$(SUM(RRR$ (RRRAAA(RRR,AAA) AND CCCRRR(CCC,RRR)),1) GT 0);
IR(RRR) = YES$(SUM(C,CCCRRR(C,RRR)));
IA(AAA) = YES$(SUM(C,ICA(C,AAA)));

SET IS3(S)   'Present season simulated in Balbase3';


*-------------------------------------------------------------------------------
*--- End: Definitions of SETS and ACRONYMS that are given in the $included files
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
*----- Definitions of SETS and ALIASES that are needed for data entry:
*-------------------------------------------------------------------------------

* Duplication of sets for describing electricity exchange between regions:
ALIAS (RRR,IRRRE,IRRRI);
ALIAS (IR,IRE,IRI);
* Duplication of sets for describing heat exchange between areas: /*varmetrans*/
ALIAS (AAA,IAAAE,IAAAI);
ALIAS (IA,IAE,IAI);
* Duplication of sets for fuel.
ALIAS (FFF,IFFFALIAS);
ALIAS (FFF,IFFFALIAS2);

ALIAS(S,IS3LOOPSET);

* Duplication of sets for seasons and hours:
ALIAS (Y,IYALIAS);
ALIAS (S,ISALIAS);
ALIAS (T,ITALIAS);


*-------------------------------------------------------------------------------
*----- End: Definitions of ALIASES that are needed for data entry
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
*----- Any declarations and definitions of sets, aliases and acronyms for addon:
*-------------------------------------------------------------------------------

$include "../../base/addons/_hooks/acronyms.inc"
$include "../../base/addons/_hooks/setdeclare.inc"
$include "../../base/addons/_hooks/setdefine.inc"

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
$ifi %bb3%==yes SET T(TTT)          /T001*T168/;
$ifi %bb3%==yes $KILL TWORKDAY
$ifi %bb3%==yes $KILL TWEEKEND
$ifi %bb3%==yes SET TWORKDAY(TTT)   /T001*T120/;
$ifi %bb3%==yes SET TWEEKEND(TTT)   /T121*T168/;
*-------------------------------------------------------------------------------


*-------------------------------------------------------------------------------
*----- Any internal sets for addon to be placed here: --------------------------


$ifi %FV%==yes $include '../../base/addons/fjernvarme/sets_fv.inc';


*----- End: Any internal sets for addon to be placed here: ---------------------
*-------------------------------------------------------------------------------



*-------------------------------------------------------------------------------
* End: Declaration of internal sets
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
*---- Declaration and definition of numerical data: PARAMETERS and SCALARS:
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
*---- Technology data: ---------------------------------------------------------
*-------------------------------------------------------------------------------
PARAMETER GDATA(GGG,GDATASET)    'Technologies characteristics' %semislash%
* Printing of data to the list file controlled by %ONOFFDATALISTING% and %ONOFFCODELISTING%:
%ONOFFDATALISTING%
$if     EXIST '../data/GDATA.inc' $INCLUDE         '../data/GDATA.inc';
$if not EXIST '../data/GDATA.inc' $INCLUDE '../../base/data/GDATA.inc';
%ONOFFCODELISTING%

*-------------------------------------------------------------------------------
*------------- Any GDATA additions for addon to be placed here: ----------------
*-------------------------------------------------------------------------------
$include "../../base/addons/_hooks/gdataadditions.inc"

*-------------------------------------------------------------------------------
* Definitions of internal sets relative to technologies,
* The sets are defined based on information in PARAMETER GDATA.

* The following are convenient internal subsets of generation technologies:

SET IGCND(G)               'Condensing technologies';                           !! Corresponding to acronym GCND
SET IGBPR(G)               'Back pressure technologies';                        !! Corresponding to acronym GBPR
SET IGEXT(G)               'Extraction technologies';                           !! Corresponding to acronym GEXT
SET IGHOB(G)               'Heat-only boilers';                                 !! Corresponding to acronym GHOB
SET IGETOH(G)              'Electric heaters, heatpumps, electrolysis plants';  !! Corresponding to acronym GETOH
SET IGHSTO(G)              'Intra-seasonal heat storage technologies';          !! Corresponding to acronym GHSTO
SET IGHSTOS(G)             'Inter-seasonal heat storage technologies';          !! Corresponding to acronym GHSTOS
SET IGHSTOALL(G)           'All heat storage technologies (intra- plus inter-seasonal) (option dependent)';
SET IGESTO(G)              'Intra-seasonal electricity storage technologies';   !! Corresponding to acronym GESTO
SET IGESTOS(G)             'Inter-seasonal electricity storage technologies';   !! Corresponding to acronym GESTOS
SET IGESTOALL(G)           'All electricity storage technologies (intra- plus inter-seasonal) (option dependent)';
SET IGHYRS(G)              'Hydropower with reservoir';                         !! Corresponding to acronym GHYRS
SET IGHYRR(G)              'Hydropower run-of-river no reservoir';              !! Corresponding to acronym GHYRR
SET IGWND(G)               'Wind power technologies';                           !! Corresponding to acronym GWND
SET IGSOLE(G)              'Solar electrical power technologies';               !! Corresponding to acronym GSOLE
SET IGSOLH(G)              'Solar heat technologies';                           !! Corresponding to acronym GSOLH
SET IGWAVE(G)              'Wave power technologies';                           !! Corresponding to acronym GWAVE
SET IGHH(G)                'Technologies generating heat-only';
SET IGHHNOSTO(G)           'Technologies generating heat-only, except storage';
SET IGNOTETOH(G)           'Technologies excluding electric heaters, heat pumps,electrolysis plants';
SET IGKH(G)                'Technologies with capacity specified on heat';
SET IGKHNOSTO(G)           'Technologies with capacity specified on heat, except storage';
SET IGKE(G)                'Technologies with capacity specified on electricity';
SET IGKENOSTO(G)           'Technologies with capacity specified on electricity, except storage';
SET IGDISPATCH(G)          'Dispatchable technologies';
SET IGEE(G)                'Technologies generating electricity only';
SET IGEENOSTO(G)           'Technologies generating electricity only, except storage (but includes hydro)';
SET IGKKNOWN(G)            'Technoloies for which the capacity is specified by the user';
SET IGKFIND(G)             'Technologies for which the capacity is found by algorithm as endogenous investments';
SET IGEH(G)                'Technologies generating electricity and heat';
SET IGE(G)                 'Technologies generating electricity';
SET IGH(G)                 'Technologies generating heat';
SET IGBYPASS(G)            'Technologies that may apply turbine bypass mode (subject to option bypass)';

* The following describes the main applications for the subsets:
*
* The sets:
* IGCND,IGBPR,IGEXT,IGHOB,IGETOH,IGHSTO,IGESTO,IGHSTOS,IGESTOS,IGHYRS,IGHYRR,IGWND,IGSOLE,IGSOLH,IGWAVE
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

* The sets are defined based on information in PARAMETER GDATA.

* The specifications of technology type 'GDTYPE' in GDATA may use an acronym or a number.
* Under most circumstances an acronym is preferable, the list is given above.
* If an acroym can not be used, use the numbers consistently as seen below.


   IGCND(G)        = YES$((GDATA(G,'GDTYPE') EQ 1)  OR (GDATA(G,'GDTYPE') EQ GCND));
   IGBPR(G)        = YES$((GDATA(G,'GDTYPE') EQ 2)  OR (GDATA(G,'GDTYPE') EQ GBPR));
   IGEXT(G)        = YES$((GDATA(G,'GDTYPE') EQ 3)  OR (GDATA(G,'GDTYPE') EQ GEXT));
   IGHOB(G)        = YES$((GDATA(G,'GDTYPE') EQ 4)  OR (GDATA(G,'GDTYPE') EQ GHOB));
   IGETOH(G)       = YES$((GDATA(G,'GDTYPE') EQ 5)  OR (GDATA(G,'GDTYPE') EQ GETOH));
   IGHSTO(G)       = YES$((GDATA(G,'GDTYPE') EQ 6)  OR (GDATA(G,'GDTYPE') EQ GHSTO));
   IGHSTOS(G)      = YES$(GDATA(G,'GDTYPE') EQ GHSTOS);
   IGESTO(G)       = YES$((GDATA(G,'GDTYPE') EQ 7)  OR (GDATA(G,'GDTYPE') EQ GESTO));
   IGESTOS(G)      = YES$(GDATA(G,'GDTYPE') EQ GESTOS);
   IGHYRS(G)       = YES$((GDATA(G,'GDTYPE') EQ 8)  OR (GDATA(G,'GDTYPE') EQ GHYRS));
   IGHYRR(G)       = YES$((GDATA(G,'GDTYPE') EQ 9)  OR (GDATA(G,'GDTYPE') EQ GHYRR));
   IGWND(G)        = YES$((GDATA(G,'GDTYPE') EQ 10) OR (GDATA(G,'GDTYPE') EQ GWND));
   IGSOLE(G)       = YES$((GDATA(G,'GDTYPE') EQ 11) OR (GDATA(G,'GDTYPE') EQ GSOLE));
   IGSOLH(G)       = YES$((GDATA(G,'GDTYPE') EQ 12) OR (GDATA(G,'GDTYPE') EQ GSOLH));
   IGWAVE(G)       = YES$((GDATA(G,'GDTYPE') EQ 22) OR (GDATA(G,'GDTYPE') EQ GWAVE));

* Assignments of IGESTO, IGESTOS, IGHSTO and IGHSTOS may be changed if option stointers has a non-default value.
$ifi "%stointers%"=="all"  IGESTOS(IGESTO) = YES; IGHSTOS(IGHSTO) = YES;
$ifi "%stointers%"=="all"  IGESTO(IGESTO) = NO;   IGHSTO(IGHSTO) = NO;
$ifi "%stointers%"=="none" IGESTO(IGESTOS) = YES; IGHSTO(IGHSTOS) = YES;
$ifi "%stointers%"=="none" IGESTOS(IGESTOS) = NO; IGHSTOS(IGHSTOS) = NO;

   IGHHNOSTO(G) = NO;   IGHHNOSTO(IGHOB)   = YES;  IGHHNOSTO(IGSOLH)= YES;

   IGHSTOALL(G) =       IGHSTO(G)
                         +IGHSTOS(G);

   IGHH(G)      =       IGHHNOSTO(G)
                         +IGHSTOALL(G);

   IGKHNOSTO(G)     =   IGETOH(G)
                         +IGHHNOSTO(G);

   IGKH(G)          =   IGKHNOSTO(G)
                         +IGHSTOALL(G);

   IGEENOSTO(G)     =   IGCND(G)     !! In contrast to heat related technologies,
                         +IGHYRS(G)  !! with elec related technologies a more enumeration approach is taken
                         +IGHYRR(G)  !! for illustrative purposes
                         +IGWND(G)
                         +IGSOLE(G)
                         +IGWAVE(G);


   IGEE(G)          =   IGCND(G)
                         +IGHYRS(G)
                         +IGHYRR(G)
                         +IGWND(G)
                         +IGSOLE(G)
                         +IGWAVE(G)
                         +IGESTO(G)
                         +IGESTOS(G);


   IGESTOALL(G) =       IGESTO(G)
                         +IGESTOS(G);


   IGKE(G)          =   IGCND(G)
                         +IGBPR(G)
                         +IGEXT(G)
                         +IGESTO(G)
                         +IGESTOS(G)
                         +IGHYRS(G)
                         +IGHYRR(G)
                         +IGWND(G)
                         +IGSOLE(G)
                         +IGWAVE(G);

   IGKENOSTO(G)     =   IGKE(G)
                         -IGESTO(G)
                         -IGESTOS(G);

   IGNOTETOH(G)= NOT IGETOH(G);

   IGEH(G) = IGBPR(G)+IGEXT(G)+IGETOH(G);
   IGE(G)=IGEE(G)+IGEH(G);
   IGH(G)=IGHH(G)+IGEH(G);

   IGDISPATCH(G)    =   IGCND(G)
                         +IGBPR(G)
                         +IGEXT(G)
                         +IGHOB(G)
                         +IGESTO(G)
                         +IGESTOS(G)
                         +IGHSTO(G)
                         +IGHSTOS(G)
                         +IGETOH(G)
                         +IGHYRS(G);

   IGKFIND(G)  = YES$(GDATA(G,'GDKVARIABL') EQ 1);
   IGKKNOWN(G) = NOT IGKFIND(G);

   IGBYPASS(G) = NO;
   IGBYPASS(IGBPR)$GDATA(IGBPR,'GDBYPASSC') = YES;

* Assignments of IGBYPASS may be changed if option bypass has a non-default value.
$ifi not %bypass%==yes IGBYPASS(G) = NO;


*-------------------------------------------------------------------------------
*----- Any internal sets assignments for addon to be placed here: --------------
*-------------------------------------------------------------------------------
* NOTE: When making new generation technology types. Some add-ons may already
* be using values of GDATA(G,'GDTYPE'). Check addons referenced here to maximize
* consistency and avoid conflicts. It is encouraged to avoid using the '-' set
* operator and instead use the '+' operator for compound assignments.


$include "../../base/addons/_hooks/isetdecdef.inc"

*---- Unit commitment --------------------------------------------------------------

$ifi %UnitComm%==yes $include '../../base/addons/unitcommitment/uc_datadecl.inc';

$ifi %POLICIES%==yes  $ifi exist 'pol_sets.inc' $INCLUDE 'pol_sets.inc';
$ifi %POLICIES%==yes  $ifi not exist 'pol_sets.inc' $INCLUDE '../../base/addons/Policies/pol_sets.inc';

$ifi %SYSTEMCOST%==yes  $ifi exist '../data/sets_syscost.inc' $INCLUDE             '../data/sets_syscost.inc';
$ifi %SYSTEMCOST%==yes  $ifi not exist ../data/'sets_syscost.inc' $INCLUDE '../../base/data/sets_syscost.inc';

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

PARAMETER GKFX(YYY,AAA,GGG)    'Capacity of exogenously given generation technologies (MW)' %semislash%
$if     EXIST '../data/GKFX.inc' $INCLUDE         '../data/GKFX.inc';
$if not EXIST '../data/GKFX.inc' $INCLUDE '../../base/data/GKFX.inc';
%semislash%;


* Printing of data to the list file controlled by %ONOFFDATALISTING% and %ONOFFCODELISTING%:
%ONOFFCODELISTING%

*-------------------------------------------------------------------------------
*---- End: Annually specified generation capacities ----------------------------
*-------------------------------------------------------------------------------

SET IAGK(AAA,G) 'Technologies with exogenous capacity in any simulation year';
IAGK(IA,G)$(SUM(Y,GKFX(Y,IA,G)))=yes;


*-------------------------------------------------------------------------------
*---- Geographically specific values: -----------------------------------------
*-------------------------------------------------------------------------------

PARAMETER YVALUE(YYY)                  "Numerical value of the years' labels";
PARAMETER FDATA(FFF,FDATASET)          'Fuel specific values';

PARAMETER FMAXINVEST(CCC,FFF)          'Maximum investment (MW) by fuel type for each year simulated';
PARAMETER GROWTHCAP(C,GGG)             'Maximum model generated capacity increase (MW) from one year to the next';

PARAMETER DISLOSS_E(RRR)               'Loss in electricity distribution (fraction)';
PARAMETER DISLOSS_H(AAA)               'Loss in heat distribution (fraction)';
PARAMETER DISCOST_E(RRR)               'Cost of electricity distribution (Money/MWh)';
PARAMETER DISCOST_H(AAA)               'Cost of heat distribution (Money/MWh)';
PARAMETER FKPOT(CCCRRRAAA,FFF)         'Fuel potential restriction by geography (MW)';
PARAMETER FGEMIN(CCCRRRAAA,FFF)        'Minimum electricity generation by fuel (default/0/, eps for 0) (MWh)';
PARAMETER FGEMAX(CCCRRRAAA,FFF)        'Maximum electricity generation by fuel (default/0/, eps for 0) (MWh)';
$ifi %GMINF_DOL%==CCCRRRAAA_FFF         PARAMETER GMINF(CCCRRRAAA,FFF)             'Minimum fuel use per year (default/0/, eps for 0) (GJ)';
$ifi %GMINF_DOL%==YYY_CCCRRRAAA_FFF     PARAMETER GMINF(YYY,CCCRRRAAA,FFF)         'Minimum fuel use per year (default/0/, eps for 0) (GJ)';
$ifi %GMAXF_DOL%==CCCRRRAAA_FFF         PARAMETER GMAXF(CCCRRRAAA,FFF)             'Maximum fuel use per year (default/0/, eps for 0) (GJ)';
$ifi %GMAXF_DOL%==YYY_CCCRRRAAA_FFF     PARAMETER GMAXF(YYY,CCCRRRAAA,FFF)         'Maximum fuel use per year (default/0/, eps for 0) (GJ)';
$ifi %GEQF_DOL%== CCCRRRAAA_FFF         PARAMETER GEQF(CCCRRRAAA,FFF)              'Required fuel use per year (default/0/, eps for 0) (GJ)';
$ifi %GEQF_DOL%== YYY_CCCRRRAAA_FFF     PARAMETER GEQF(YYY,CCCRRRAAA,FFF)          'Required fuel use per year (default/0/, eps for 0) (GJ)';
PARAMETER WTRRSFLH(AAA)                'Full load hours for hydro reservoir plants (hours)';
PARAMETER WTRRRFLH(AAA)                'Full load hours for hydro run-of-river plants (hours)';
$ifi %WNDFLH_DOL%==AAA_GGG              PARAMETER WNDFLH(AAA,GGG)                  "Full load hours for wind power (hours)";
$ifi %WNDFLH_DOL%==AAA                  PARAMETER WNDFLH(AAA)                      "Full load hours for wind power (hours)";
$ifi %SOLEFLH_DOL%==AAA                 PARAMETER SOLEFLH(AAA)                     "Full load hours for solarE power (hours)";
$ifi %SOLEFLH_DOL%==AAA_GGG             PARAMETER SOLEFLH(AAA,GGG)                 "Full load hours for solarE power (hours)";
$ifi %SOLHFLH_DOL%==AAA                 PARAMETER SOLHFLH(AAA)                     "Full load hours for solarH power (hours)";
$ifi %SOLHFLH_DOL%==AAA_GGG             PARAMETER SOLHFLH(AAA,GGG)                 "Full load hours for solarH power (hours)";
$ifi %GWAVE_DOL%==AAA                   PARAMETER WAVEFLH(AAA)                     "Full load hours for wave power";
$ifi %GWAVE_DOL%==AAA_GGG               PARAMETER WAVEFLH(AAA,GGG)                 "Full load hours for wave power";
PARAMETER HYRSMAXVOL_G(AAA,GGG)        'Reservoir capacity (MWh storage capacity / MW installed capacity)';
PARAMETER HYRSDATA(AAA,HYRSDATASET,SSS)'Data for hydro with storage';
PARAMETER TAX_FHO(YYY,AAA,G)           'Fuel taxes on heat-only units';
PARAMETER TAX_FHO_C(FFF,CCC)           'Fuel taxes on heat-only units';
PARAMETER TAX_GH(YYY,AAA,G)            'Heat taxes on generation units';
PARAMETER TAX_FCHP_C(FFF,CCC)          'Fuel taxes on CHP units';
PARAMETER TAX_HHO_C(FFF,CCC)           'Fuel taxes on HO units';
PARAMETER TAX_F(FFF,CCC)               'Fuel taxes for heat and electricity production (Money/GJ)';
PARAMETER TAX_DE(CCC,DEUSER)           "Consumers tax on electricity consumption (Money/MWh)";
PARAMETER TAX_DH(CCC,DHUSER)           "Consumers tax on heat consumption (Money/MWh)";
PARAMETER ANNUITYC(CCC)                'Transforms investment to annual payment (fraction)';
PARAMETER GINVCOST(AAA,GGG)            'Investment cost for new technology (MMoney/MW)';
PARAMETER GOMVCOST(AAA,GGG)            'Variable operating and maintenance costs (Money/MWh)';
PARAMETER GOMFCOST(AAA,GGG)            'Annual fixed operating costs (kMoney/MW)';
PARAMETER GEFFRATE(AAA,GGG)            "Fuel efficiency rating (strictly positive, typically close to 1; default/1/)";
PARAMETER DEFP_BASE(RRR)               'Nominal annual average consumer electricity price (Money/MWh)';
PARAMETER DHFP_BASE(AAA)               'Nominal annual average consumer heat price (Money/MWh)';
PARAMETER DE(YYY,RRR,DEUSER)           "Annual electricity consumption (MWh)";
PARAMETER DH(YYY,AAA,DHUSER)           "Annual heat consumption (MWh)";

*---- Transmission data: -------------------------------------------------------
PARAMETER XKINI(YYY,IRRRE,IRRRI)       'Initial transmission capacity between regions (MW)';
PARAMETER XINVCOST(IRRRE,IRRRI)        'Investment cost in new transmission capacity (Money/MW)';
PARAMETER XCOST(IRRRE,IRRRI)           'Transmission cost between regions (Money/MWh)';
PARAMETER XLOSS(IRRRE,IRRRI)           'Transmission loss between regions (fraction)';
$ifi %XKRATE_DOL%==IRRRE_IRRRI          PARAMETER XKRATE(IRRRE,IRRRI)         "Transmission capacity rating (share; non-negative, typically close to 1; default/1/, eps for 0)";
$ifi %XKRATE_DOL%==IRRRE_IRRRI_SSS      PARAMETER XKRATE(IRRRE,IRRRI,SSS)     "Transmission capacity rating (share; non-negative, typically close to 1; default/1/, eps for 0)";
$ifi %XKRATE_DOL%==IRRRE_IRRRI_SSS_TTT  PARAMETER XKRATE(IRRRE,IRRRI,SSS,TTT) "Transmission capacity rating (share; non-negative, typically close to 1; default/1/, eps for 0)";


*---- Third regions:
PARAMETER X3FX(YYY,RRR)                'Annual net electricity export to third regions (MWh)';
$ifi %X3V%==yes PARAMETER X3VPIM(YYY,RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)    'Price (Money/MWh) of price dependent imported electricity';
$ifi %X3V%==yes PARAMETER X3VPEX(YYY,RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)    'Price (Money/MWh) of price dependent exported electricity';
$ifi %X3V%==yes PARAMETER X3VQIM(RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)        'Limit (MW) on price dependent electricity import';
$ifi %X3V%==yes PARAMETER X3VQEX(RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)        'Limit (MW) on price dependent electricity export';

* Fuel prices: -----------------------------------------------------------------

PARAMETER M_POL(YYY,MPOLSET,CCC)                   'Emission policy data (various units, cf. MPOLSET)';
* Time series on (SSS,TTT):
PARAMETER WEIGHT_S(SSS)                            'Weight (relative length) of each season (~)';
PARAMETER WEIGHT_T(TTT)                            'Weight (relative length) of each time period (~)';
$ifi %GKRATE_DOL%==AAA_GGG_SSS                     PARAMETER GKRATE(AAA,GGG,SSS)         "Capacity rating (non-negative, typically close to 1; default/1/, eps for 0)";
$ifi %GKRATE_DOL%==AAA_GGG_SSS_TTT                 PARAMETER GKRATE(AAA,GGG,SSS,TTT)     "Capacity rating (non-negative, typically close to 1; default/1/, eps for 0)";
PARAMETER DE_VAR_T(RRR,DEUSER,SSS,TTT)             "Variation in electricity demand ()"; !! () todo
PARAMETER DH_VAR_T(AAA,DHUSER,SSS,TTT)             "Variation in heat demand ()"; !! () todo
PARAMETER WTRRSVAR_S(AAA,SSS)                      'Variation of the water inflow to reservoirs (~)';
PARAMETER WTRRRVAR_T(AAA,SSS,TTT)                  'Variation of generation of hydro run-of-river (~)';
PARAMETER WND_VAR_T(AAA,SSS,TTT)                   'Variation of the wind electricity generation (~)';
PARAMETER SOLE_VAR_T(AAA,SSS,TTT)                  'Variation of the solar electricity generation (~)';
PARAMETER WAVE_VAR_T(AAA,SSS,TTT)                  'Variation of the wave electricity generation (~)'
PARAMETER X3FX_VAR_T(RRR,SSS,TTT)                  'Variation in fixed electricity exchange with 3. region (~)';
PARAMETER HYPPROFILS(AAA,SSS)                      'Hydro with storage exogenous seasonal electricity price profile (Money/MWh)';
/*
PARAMETER DEF_STEPS(RRR,SSS,TTT,DF_QP,DEF)         'Elastic electricity demands ()';
$ifi %DEFPCALIB%==yes PARAMETER DEFP_CALIB(RRR,SSS,TTT)  'Calibrate the price side of electricity demand';
PARAMETER DHF_STEPS(AAA,SSS,TTT,DF_QP,DHF)         'Elastic heat demands ()';
*/
$ifi %DHFPCALIB%==yes PARAMETER DHFP_CALIB(AAA,SSS,TTT)  'Calibrate the price side of heat demand';
$ifi %YIELDREQUIREMENT%==yes  PARAMETER YIELDREQ(GGG) 'Differentiates yield requirements for different technologies';

SCALAR PENALTYQ  'Penalty on violation of equation';

* Data for handling of annual hydro constraints in BB3, to be saved by BB1/BB2 and used by BB3:
PARAMETER HYRSG(YYY,AAA,SSS)        'Water (hydro) generation quantity of the seasons to be transferred to model Balbase3 (MWh)';
PARAMETER VHYRS_SL(Y,AAA,SSS)       'To be saved for comparison with BB1/BB2 solution value for VHYRS_S.L (initial letter is V although declared as a parameter) (MWh)'
PARAMETER WATERVAL(YYY,AAA,SSS)     'Water value (in input Money) to be transferred to model Balbase3 (input-Money/MWh)';

* Printing of data to the list file controlled by %ONOFFDATALISTING% and %ONOFFCODELISTING%:
%ONOFFDATALISTING%

PARAMETER YVALUE(YYY)   'Numerical value of the years labels'  %semislash%
$if     EXIST '../data/YVALUE.inc' $INCLUDE         '../data/YVALUE.inc';
$if not EXIST '../data/YVALUE.inc' $INCLUDE '../../base/data/YVALUE.inc';
%semislash%;

PARAMETER FDATA(FFF,FDATASET)    'Fuel specific values'  %semislash%
$if     EXIST '../data/FDATA.inc' $INCLUDE         '../data/FDATA.inc';
$if not EXIST '../data/FDATA.inc' $INCLUDE '../../base/data/FDATA.inc';
%semislash%;

* The two specifications of fuel type 'FDACRONYM' and 'FDNB', have relative merits.
* Under most circumstances 'FDACRONYM' is preferable, and it is used internally in the GAMS code.
* Under these circumstances assign no value for 'FDNB'.
* If 'FDACRONYM' can not be used, use 'FDNB'.
* Always substitute 'FDACRONYM' values by 'FDNB' values if the latter are non-zero:
FDATA(FFF,'FDACRONYM')$(NOT FDATA(FFF,'FDACRONYM')) = FDATA(FFF,'FDNB');

PARAMETER FMAXINVEST(CCC,FFF)   'Maximum investment (MW) by fuel type for each year simulated'    %semislash%
$if     EXIST '../data/FMAXINVEST.inc' $INCLUDE         '../data/FMAXINVEST.inc';
$if not EXIST '../data/FMAXINVEST.inc' $INCLUDE '../../base/data/FMAXINVEST.inc';
%semislash%;

PARAMETER GROWTHCAP(C,GGG)    'Maximum model generated capacity increase (MW) from one year to the next'   %semislash%
$if     EXIST '../data/GROWTHCAP.inc' $INCLUDE         '../data/GROWTHCAP.inc';
$if not EXIST '../data/GROWTHCAP.inc' $INCLUDE '../../base/data/GROWTHCAP.inc';
%semislash%;

PARAMETER DISLOSS_E(RRR)    'Loss in electricity distribution (fraction)'   %semislash%
$if     EXIST '../data/DISLOSS_E.inc' $INCLUDE         '../data/DISLOSS_E.inc';
$if not EXIST '../data/DISLOSS_E.inc' $INCLUDE '../../base/data/DISLOSS_E.inc';
%semislash%;

PARAMETER DISLOSS_H(AAA)    'Loss in heat distribution (fraction)'  %semislash%
$if     EXIST '../data/DISLOSS_H.inc' $INCLUDE         '../data/DISLOSS_H.inc';
$if not EXIST '../data/DISLOSS_H.inc' $INCLUDE '../../base/data/DISLOSS_H.inc';
%semislash%;

PARAMETER DISCOST_E(RRR)    'Cost of electricity distribution (Money/MWh)'  %semislash%
$if     EXIST '../data/DISCOST_E.inc' $INCLUDE         '../data/DISCOST_E.inc';
$if not EXIST '../data/DISCOST_E.inc' $INCLUDE '../../base/data/DISCOST_E.inc';
%semislash%;

PARAMETER DISCOST_H(AAA)    'Cost of heat distribution (Money/MWh)'     %semislash%
$if     EXIST '../data/DISCOST_H.inc' $INCLUDE         '../data/DISCOST_H.inc';
$if not EXIST '../data/DISCOST_H.inc' $INCLUDE '../../base/data/DISCOST_H.inc';
%semislash%;

PARAMETER FKPOT(CCCRRRAAA,FFF)    'Fuel potential restricted by geography (MW)'   %semislash%
$if     EXIST '../data/FKPOT.inc' $INCLUDE         '../data/FKPOT.inc';
$if not EXIST '../data/FKPOT.inc' $INCLUDE '../../base/data/FKPOT.inc';
%semislash%;

PARAMETER FGEMIN(CCCRRRAAA,FFF)    'Minimum electricity generation by fuel (MWh)'  %semislash%
$if     EXIST '../data/FGEMIN.inc' $INCLUDE         '../data/FGEMIN.inc';
$if not EXIST '../data/FGEMIN.inc' $INCLUDE '../../base/data/FGEMIN.inc';
%semislash%;

PARAMETER FGEMAX(CCCRRRAAA,FFF)     'Maximum electricity generation by fuel (MWh)'   %semislash%
$if     EXIST '../data/FGEMAX.inc' $INCLUDE         '../data/FGEMAX.inc';
$if not EXIST '../data/FGEMAX.inc' $INCLUDE '../../base/data/FGEMAX.inc';
%semislash%;

$ifi %GMINF_DOL%==CCCRRRAAA_FFF      PARAMETER GMINF(CCCRRRAAA,FFF)             'Minimum fuel use per year (default/0/, eps for 0) (GJ)' %semislash%
$ifi %GMINF_DOL%==YYY_CCCRRRAAA_FFF  PARAMETER GMINF(YYY,CCCRRRAAA,FFF)         'Minimum fuel use per year (default/0/, eps for 0) (GJ)' %semislash%s
$if     EXIST '../data/GMINF.inc' $INCLUDE         '../data/GMINF.inc';
$if not EXIST '../data/GMINF.inc' $INCLUDE '../../base/data/GMINF.inc';
%semislash%;

$ifi %GMAXF_DOL%==CCCRRRAAA_FFF      PARAMETER GMAXF(CCCRRRAAA,FFF)             'Maximum fuel use per year (default/0/, eps for 0) (GJ)' %semislash%
$ifi %GMAXF_DOL%==YYY_CCCRRRAAA_FFF  PARAMETER GMAXF(YYY,CCCRRRAAA,FFF)         'Maximum fuel use per year (default/0/, eps for 0) (GJ)' %semislash%
$if     EXIST '../data/GMAXF.inc' $INCLUDE         '../data/GMAXF.inc';
$if not EXIST '../data/GMAXF.inc' $INCLUDE '../../base/data/GMAXF.inc';
%semislash%;

$ifi %GEQF_DOL%==CCCRRRAAA_FFF       PARAMETER GEQF(CCCRRRAAA,FFF)              'Required fuel use per year (default/0/, eps for 0) (GJ)' %semislash%
$ifi %GEQF_DOL%== YYY_CCCRRRAAA_FFF  PARAMETER GEQF(YYY,CCCRRRAAA,FFF)          'Required fuel use per year (default/0/, eps for 0) (GJ)' %semislash%
$if     EXIST '../data/GEQF.inc' $INCLUDE         '../data/GEQF.inc';
$if not EXIST '../data/GEQF.inc' $INCLUDE '../../base/data/GEQF.inc';
%semislash%;

* Maximum capacity at new technologies
PARAMETER GKNMAX(YYY,AAA,GGG)   "Maximum capacity of new technologies (MW) default/INF/, eps for 0)"  %semislash%
$if     EXIST '../data/GKNMAX.inc' $INCLUDE         '../data/GKNMAX.inc';
$if not EXIST '../data/GKNMAX.inc' $INCLUDE '../../base/data/GKNMAX.inc';
%semislash%;

PARAMETER WTRRSFLH(AAA)    'Full load hours for hydro reservoir plants (hours)'  %semislash%
$if     EXIST '../data/WTRRSFLH.inc' $INCLUDE         '../data/WTRRSFLH.inc';
$if not EXIST '../data/WTRRSFLH.inc' $INCLUDE '../../base/data/WTRRSFLH.inc';
%semislash%;

PARAMETER WTRRRFLH(AAA)    'Full load hours for hydro run-of-river plants (hours)'  %semislash%
$if     EXIST '../data/WTRRRFLH.inc' $INCLUDE         '../data/WTRRRFLH.inc';
$if not EXIST '../data/WTRRRFLH.inc' $INCLUDE '../../base/data/WTRRRFLH.inc';
%semislash%;

$ifi %WNDFLH_DOL%==AAA               PARAMETER WNDFLH(AAA)         'Full load hours for wind power (hours)'  %semislash%
$ifi %WNDFLH_DOL%==AAA_GGG           PARAMETER WNDFLH(AAA,GGG)     'Full load hours for wind power (hours)'  %semislash%
$if     EXIST '../data/WNDFLH.inc' $INCLUDE         '../data/WNDFLH.inc';
$if not EXIST '../data/WNDFLH.inc' $INCLUDE '../../base/data/WNDFLH.inc';
%semislash%;

$ifi %SOLEFLH_DOL%==AAA              PARAMETER SOLEFLH(AAA)        'Full load hours for solar power (hours)'  %semislash%
$ifi %SOLEFLH_DOL%==AAA_GGG          PARAMETER SOLEFLH(AAA,GGG)    'Full load hours for solar power (hours)'  %semislash%
$if     EXIST '../data/SOLEFLH.inc' $INCLUDE         '../data/SOLEFLH.inc';
$if not EXIST '../data/SOLEFLH.inc' $INCLUDE '../../base/data/SOLEFLH.inc';
%semislash%;

PARAMETER SOLHFLH(AAA)    'Full load hours for solar power (hours)'  %semislash%
$if     EXIST '../data/SOLHFLH.inc' $INCLUDE         '../data/SOLHFLH.inc';
$if not EXIST '../data/SOLHFLH.inc' $INCLUDE '../../base/data/SOLHFLH.inc';
%semislash%;

PARAMETER WAVEFLH(AAA)    'Full load hours for wave power (hours)'  %semislash%
$if     EXIST '../data/WAVEFLH.inc' $INCLUDE         '../data/WAVEFLH.inc';
$if not EXIST '../data/WAVEFLH.inc' $INCLUDE '../../base/data/WAVEFLH.inc';
%semislash%;

PARAMETER HYRSMAXVOL_G(AAA,GGG) 'Reservoir capacity (MWh storage capacity / MW installed capacity)'  %semislash%
$if     EXIST '../data/HYRSMAXVOL_G.inc' $INCLUDE         '../data/HYRSMAXVOL_G.inc';
$if not EXIST '../data/HYRSMAXVOL_G.inc' $INCLUDE '../../base/data/HYRSMAXVOL_G.inc';
%semislash%;

PARAMETER HYRSDATA(AAA,HYRSDATASET,SSS)    'Data for hydro with storage'  %semislash%
$if     EXIST '../data/HYRSDATA.inc' $INCLUDE         '../data/HYRSDATA.inc';
$if not EXIST '../data/HYRSDATA.inc' $INCLUDE '../../base/data/HYRSDATA.inc';
%semislash%;

PARAMETER TAX_GF(YYY,AAA,G)    'Fuel taxes on heat-only units'  %semislash%
$if     EXIST '../data/TAX_GF.inc' $INCLUDE         '../data/TAX_GF.inc';
$if not EXIST '../data/TAX_GF.inc' $INCLUDE '../../base/data/TAX_GF.inc';
%semislash%;

PARAMETER TAX_GE(YYY,AAA,G)    'Electricity taxes on generation units and subsidies(-) (EURO 90/MWh)'  %semislash%
$if     EXIST '../data/TAX_GE.inc' $INCLUDE         '../data/TAX_GE.inc';
$if not EXIST '../data/TAX_GE.inc' $INCLUDE '../../base/data/TAX_GE.inc';
%semislash%;

PARAMETER TAX_GH(YYY,AAA,G)    'Heat taxes on generation units'   %semislash%
$if     EXIST '../data/TAX_GH.inc' $INCLUDE         '../data/TAX_GH.inc';
$if not EXIST '../data/TAX_GH.inc' $INCLUDE '../../base/data/TAX_GH.inc';
%semislash%;

PARAMETER TAX_KN(YYY,AAA,G)    'Tax (neg. subsidy) for investment in electricity generation (mEUR90/MW)'  %semislash%
$if     EXIST '../data/TAX_KN.inc' $INCLUDE         '../data/TAX_KN.inc';
$if not EXIST '../data/TAX_KN.inc' $INCLUDE '../../base/data/TAX_KN.inc';
%semislash%;

PARAMETER TAX_F(FFF,CCC)   'Fuel taxes for heat and electricity production (Money/GJ)'  %semislash%
$if     EXIST '../data/TAX_F.inc' $INCLUDE         '../data/TAX_F.inc';
$if not EXIST '../data/TAX_F.inc' $INCLUDE '../../base/data/TAX_F.inc';
%semislash%;

PARAMETER TAX_DE(CCC,DEUSER) 'Consumers tax on electricity consumption (Money/MWh)'  %semislash%
$if     EXIST '../data/TAX_DE.inc' $INCLUDE         '../data/TAX_DE.inc';
$if not EXIST '../data/TAX_DE.inc' $INCLUDE '../../base/data/TAX_DE.inc';
%semislash%;

PARAMETER TAX_DH(CCC,DHUSER)    'Consumers tax on heat consumption (Money/MWh)'  %semislash%
$if     EXIST '../data/TAX_DH.inc' $INCLUDE         '../data/TAX_DH.inc';
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

PARAMETER GEFFRATE(AAA,GGG)    "Fuel efficiency rating (strictly positive, typically close to 1; default/1/)"  %semislash%
$if     EXIST '../data/GEFFRATE.inc' $INCLUDE         '../data/GEFFRATE.inc';
$if not EXIST '../data/GEFFRATE.inc' $INCLUDE '../../base/data/GEFFRATE.inc';
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
*---- Annual electricity demand : ----------------------------------------------
*-------------------------------------------------------------------------------
PARAMETER DE(YYY,RRR,DEUSER)    'Annual electricity consumption (MWh)' %semislash%
$if     EXIST '../data/DE.inc' $INCLUDE         '../data/DE.inc';
$if not EXIST '../data/DE.inc' $INCLUDE '../../base/data/DE.inc';
%semislash%;


*-------------------------------------------------------------------------------
*---- Annual heat demand: ------------------------------------------------------
*-------------------------------------------------------------------------------
PARAMETER DH(YYY,AAA,DHUSER)    'Annual heat consumption (MWh)'  %semislash%
$if     EXIST '../data/DH.inc' $INCLUDE         '../data/DH.inc';
$if not EXIST '../data/DH.inc' $INCLUDE '../../base/data/DH.inc';
%semislash%;


*-------------------------------------------------------------------------------
*---- Transmission data: ------------------------------------------------------
*-------------------------------------------------------------------------------

PARAMETER XKINI(YYY,IRRRE,IRRRI)  'Initial transmission capacity between regions (MW)'   %semislash%
$if     EXIST '../data/XKINI.inc' $INCLUDE         '../data/XKINI.inc';
$if not EXIST '../data/XKINI.inc' $INCLUDE '../../base/data/XKINI.inc';
%semislash%;

PARAMETER XINVCOST(IRRRE,IRRRI)   'Investment cost in new transmission capacity (Money/MW)'    %semislash%
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

$ifi %XKRATE_DOL%==IRRRE_IRRRI          PARAMETER XKRATE(IRRRE,IRRRI)         "Transmission capacity rating (share; non-negative, typically close to 1; default/1/, eps for 0)";  %semislash%
$ifi %XKRATE_DOL%==IRRRE_IRRRI_SSS_TTT  PARAMETER XKRATE(IRRRE,IRRRI,SSS,TTT) "Transmission capacity rating (share; non-negative, typically close to 1; default/1/, eps for 0)";  %semislash%
$if     EXIST '../data/XKRATE.inc' $INCLUDE         '../data/XKRATE.inc';
$if not EXIST '../data/XKRATE.inc' $INCLUDE '../../base/data/XKRATE.inc';
%semislash%;

PARAMETER XMAXINV(IRRRE,IRRRI)   'Max investment in transmission capacity between two regions for each simulated year(each 5th year)'  %semislash%
$if     EXIST '../data/XMAXINV.inc' $INCLUDE         '../data/XMAXINV.inc';
$if not EXIST '../data/XMAXINV.inc' $INCLUDE '../../base/data/XMAXINV.inc';
%semislash%;

*-------------------------------------------------------------------------------
*---- Exchange with third countries: ------------------------------------------
*-------------------------------------------------------------------------------
* Fixed profile:
PARAMETER X3FX(YYY,RRR)    'Annual net electricity export to third regions'  %semislash%
$if     EXIST '../data/X3FX.inc' $INCLUDE         '../data/X3FX.inc';
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
$if     EXIST '../data/X3VPIM.inc' $INCLUDE         '../data/X3VPIM.inc';
$if not EXIST '../data/X3VPIM.inc' $INCLUDE '../../base/data/X3VPIM.inc';
%semislash%;

PARAMETER X3VPEX(YYY,RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)   'Price (Money/MWh) of price dependent exported electricity'  %semislash%
$if     EXIST '../data/X3VPEX.inc' $INCLUDE         '../data/X3VPEX.inc';
$if not EXIST '../data/X3VPEX.inc' $INCLUDE '../../base/data/X3VPEX.inc';
%semislash%;

* Maximum quantity (MW) of price dependent electricity exchange per time segment:
PARAMETER X3VQIM(RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)   'Limit (MW) on price dependent electricity import'  %semislash%
$if     EXIST '../data/X3VQIM.inc' $INCLUDE         '../data/X3VQIM.inc';
$if not EXIST '../data/X3VQIM.inc' $INCLUDE '../../base/data/X3VQIM.inc';
%semislash%;

PARAMETER X3VQEX(RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)   'Limit (MW) on price dependent electricity export'  %semislash%
$if     EXIST '../data/X3VQEX.inc' $INCLUDE         '../data/X3VQEX.inc';
$if not EXIST '../data/X3VQEX.inc' $INCLUDE '../../base/data/X3VQEX.inc';
%semislash%;

$label X3V_label3

*-------------------------------------------------------------------------------
*---- Annually specified fuel prices: ------------------------------------------
*-------------------------------------------------------------------------------

PARAMETER FUELPRICE(YYY,AAA,FFF)                   'Fuel prices (Money/GJ)'   %semislash%
$if     EXIST '../data/FUELPRICE.inc' $INCLUDE         '../data/FUELPRICE.inc';
$if not EXIST '../data/FUELPRICE.inc' $INCLUDE '../../base/data/FUELPRICE.inc';
%semislash%;


*-------------------------------------------------------------------------------
*---- Emission policy data: ----------------------------------------------------
*-------------------------------------------------------------------------------

PARAMETER M_POL(YYY,MPOLSET,CCC)    'Emission policy data (various units, cf. MPOLSET)'   %semislash%
$if     EXIST '../data/M_POL.inc' $INCLUDE         '../data/M_POL.inc';
$if not EXIST '../data/M_POL.inc' $INCLUDE '../../base/data/M_POL.inc';
%semislash%;

*-------------------------------------------------------------------------------
*---- Seasonal and daily variations: -------------------------------------------
*-------------------------------------------------------------------------------


* DISSE FILER INDHOLDER NaSTEN ALLESAMMEN KODE, CONDITIONALS, ETC! Skal revideres!

PARAMETER WEIGHT_S(SSS)                            'Weight (relative length) of each season'    %semislash%
$if     EXIST '../data/WEIGHT_S.inc' $INCLUDE         '../data/WEIGHT_S.inc';
$if not EXIST '../data/WEIGHT_S.inc' $INCLUDE '../../base/data/WEIGHT_S.inc';
%semislash%;

PARAMETER WEIGHT_T(TTT)                            'Weight (relative length) of each time period'   %semislash%
$if     EXIST '../data/WEIGHT_T.inc' $INCLUDE         '../data/WEIGHT_T.inc';
$if not EXIST '../data/WEIGHT_T.inc' $INCLUDE '../../base/data/WEIGHT_T.inc';
%semislash%;

PARAMETER CHRONOHOUR(SSS,TTT) 'Number of short term storage load cycles per season ((0;inf))'  %semislash%
$if     EXIST '../data/CHRONOHOUR.inc' $INCLUDE         '../data/CHRONOHOUR.inc';
$if not EXIST '../data/CHRONOHOUR.inc' $INCLUDE '../../base/data/CHRONOHOUR.inc';
%semislash%;

* GKDERATE substituted by GKRATE
$ifi %GKRATE_DOL%==AAA_GGG_SSS_TTT  PARAMETER GKRATE(AAA,GGG,SSS,TTT)     'Capacity rating (non-negative, typically close to 1; default/1/, eps for 0)' %semislash%
$ifi %GKRATE_DOL%==AAA_GGG_SSS      PARAMETER GKRATE(AAA,GGG,SSS)         'Capacity rating (non-negative, typically close to 1; default/1/, eps for 0)' %semislash%
$if     EXIST '../data/GKRATE.inc' $INCLUDE         '../data/GKRATE.inc';
$if not EXIST '../data/GKRATE.inc' $INCLUDE '../../base/data/GKRATE.inc';
%semislash%;

PARAMETER DE_VAR_T(RRR,DEUSER,SSS,TTT)            'Variation in electricity demand'   %semislash%
$if     EXIST '../data/DE_VAR_T.inc' $INCLUDE         '../data/DE_VAR_T.inc';
$if not EXIST '../data/DE_VAR_T.inc' $INCLUDE '../../base/data/DE_VAR_T.inc';
%semislash%;

PARAMETER DH_VAR_T(AAA,DHUSER,SSS,TTT)             'Variation in heat demand'   %semislash%
$if     EXIST '../data/DH_VAR_T.inc' $INCLUDE         '../data/DH_VAR_T.inc';
$if not EXIST '../data/DH_VAR_T.inc' $INCLUDE '../../base/data/DH_VAR_T.inc';
%semislash%;

PARAMETER WTRRSVAR_S(AAA,SSS)                      'Variation of the water inflow to reservoirs'   %semislash%
$if     EXIST '../data/WTRRSVAR_S.inc' $INCLUDE         '../data/WTRRSVAR_S.inc';
$if not EXIST '../data/WTRRSVAR_S.inc' $INCLUDE '../../base/data/WTRRSVAR_S.inc';
%semislash%;

PARAMETER WTRRRVAR_T(AAA,SSS,TTT)                  'Variation of generation of hydro run-of-river'    %semislash%
$if     EXIST '../data/WTRRRVAR_T.inc' $INCLUDE         '../data/WTRRRVAR_T.inc';
$if not EXIST '../data/WTRRRVAR_T.inc' $INCLUDE '../../base/data/WTRRRVAR_T.inc';
%semislash%;

PARAMETER WND_VAR_T(AAA,SSS,TTT)                   'Variation of the wind generation'    %semislash%
$if     EXIST '../data/WND_VAR_T.inc' $INCLUDE         '../data/WND_VAR_T.inc';
$if not EXIST '../data/WND_VAR_T.inc' $INCLUDE '../../base/data/WND_VAR_T.inc';
%semislash%;

PARAMETER SOLE_VAR_T(AAA,SSS,TTT)                  'Variation of the solarE generation'   %semislash%
$if     EXIST '../data/SOLE_VAR_T.inc' $INCLUDE         '../data/SOLE_VAR_T.inc';
$if not EXIST '../data/SOLE_VAR_T.inc' $INCLUDE '../../base/data/SOLE_VAR_T.inc';
%semislash%;

PARAMETER SOLH_VAR_T(AAA,SSS,TTT)                  'Variation of the solarH generation'   %semislash%
$if     EXIST '../data/SOLH_VAR_T.inc' $INCLUDE         '../data/SOLH_VAR_T.inc';
$if not EXIST '../data/SOLH_VAR_T.inc' $INCLUDE '../../base/data/SOLH_VAR_T.inc';
%semislash%;

PARAMETER WAVE_VAR_T(AAA,SSS,TTT)                  'Variation of the solarH generation'   %semislash%
$if     EXIST '../data/WAVE_VAR_T.inc' $INCLUDE         '../data/WAVE_VAR_T.inc';
$if not EXIST '../data/WAVE_VAR_T.inc' $INCLUDE '../../base/data/WAVE_VAR_T.inc';
%semislash%;

PARAMETER X3FX_VAR_T(RRR,SSS,TTT)                  'Variation in fixed exchange with 3. region'   %semislash%
$if     EXIST '../data/X3FX_VAR_T.inc' $INCLUDE         '../data/X3FX_VAR_T.inc';
$if not EXIST '../data/X3FX_VAR_T.inc' $INCLUDE '../../base/data/X3FX_VAR_T.inc';
%semislash%;

PARAMETER HYPPROFILS(AAA,SSS)                      'Hydro with storage seasonal price profile'   %semislash%
$if     EXIST '../data/HYPPROFILS.inc' $INCLUDE         '../data/HYPPROFILS.inc';
$if not EXIST '../data/HYPPROFILS.inc' $INCLUDE '../../base/data/HYPPROFILS.inc';
%semislash%;

* ------------------------------------------------------------------------------
$ifi not %dflexquant%==yes $goto dflexquantend2

PARAMETER DEF_STEPS(RRR,DEUSER,SSS,TTT,DF_QP,DEF)         'Elastic electricity demands'   %semislash%
$if     EXIST '../data/DEF_STEPS.inc' $INCLUDE         '../data/DEF_STEPS.inc';
$if not EXIST '../data/DEF_STEPS.inc' $INCLUDE '../../base/data/DEF_STEPS.inc';
%semislash%;

$ifi %DEFPCALIB%==yes PARAMETER DEFP_CALIB(RRR,SSS,TTT)                  'Calibrate the price side of electricity demand'   %semislash%
$ifi %DEFPCALIB%==yes $if     EXIST '../data/DEFP_CALIB.inc' $INCLUDE         '../data/DEFP_CALIB.inc';
$ifi %DEFPCALIB%==yes $if not EXIST '../data/DEFP_CALIB.inc' $INCLUDE '../../base/data/DEFP_CALIB.inc';
$ifi %DEFPCALIB%==yes %semislash%;

PARAMETER DHF_STEPS(AAA,DHUSER,SSS,TTT,DF_QP,DHF)         'Elastic heat demands'   %semislash%
$if     EXIST '../data/DHF_STEPS.inc' $INCLUDE         '../data/DHF_STEPS.inc';
$if not EXIST '../data/DHF_STEPS.inc' $INCLUDE '../../base/data/DHF_STEPS.inc';
%semislash%;

$ifi %DHFPCALIB%==yes PARAMETER DHFP_CALIB(AAA,SSS,TTT)                  'Calibrate the price side of heat demand'   %semislash%
$ifi %DHFPCALIB%==yes $if     EXIST '../data/DHFP_CALIB.inc' $INCLUDE         '../data/DHFP_CALIB.inc';
$ifi %DHFPCALIB%==yes $if not EXIST '../data/DHFP_CALIB.inc' $INCLUDE '../../base/data/DHFP_CALIB.inc';
$ifi %DHFPCALIB%==yes %semislash%;
* ------------------------------------------------------------------------------
$label dflexquantend2


$ifi %bb3%==yes WEIGHT_T(T)=1;

$ifi %YIELDREQUIREMENT%==yes  PARAMETER YIELDREQ(GGG)  'Differentiates yield requirements for different technologies'   %semislash%
$ifi %YIELDREQUIREMENT%==yes  $if     EXIST '../data/YIELDREQ.inc' $INCLUDE         '../data/YIELDREQ.inc';
$ifi %YIELDREQUIREMENT%==yes  $if not EXIST '../data/YIELDREQ.inc' $INCLUDE '../../base/data/YIELDREQ.inc';
$ifi %YIELDREQUIREMENT%==yes  %semislash%;

* Printing of data to the list file controlled by %ONOFFDATALISTING% and %ONOFFCODELISTING%:
%ONOFFCODELISTING%

*-------------------------------------------------------------------------------
*---- Investments: --------------------------------------------------------------
*-------------------------------------------------------------------------------

* Investments made in BB2 are loaded automatically in non BB2 simulations
* conditioned by the ADDINVEST global variable (see balopt.opt).
* The parameter declaration is not conditional as it is used also when saving
* investments in a BB2 simulation conditioned by the MAKEINVEST global variable.

PARAMETER GKVACCDECOM(Y,AAA,G)   'Investments in generation technology by BB2 up to and including year Y with subtraction of decommissioning';
PARAMETER GKVACC(Y,AAA,G)        'Investments in generation technology by BB2 up to and including year Y without subtraction of decommissioning';
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
* It is advised to add a comment in the data file stating what the input currency is and to which year it refers.

$if     EXIST '../data/OMONEY.inc' $INCLUDE         '../data/OMONEY.inc';
$if not EXIST '../data/OMONEY.inc' $INCLUDE '../../base/data/OMONEY.inc';

*-------------------------------------------------------------------------------
*----- Any parameters for addon to be placed here: -----------------------------
*-------------------------------------------------------------------------------
$include "../../base/addons/_hooks/pardeclare.inc"
$include "../../base/addons/_hooks/pardefine.inc"

$ifi %X3V%==yes $INCLUDE '../../base/addons/x3v/data/x3vdata.inc';
$ifi %HEATTRANS%==yes $if     EXIST '../data/htrans.inc' $INCLUDE         '../data/htrans.inc';
$ifi %HEATTRANS%==yes $if not EXIST '../data/htrans.inc' $INCLUDE '../../base/data/htrans.inc';

$ifi %POLICIES%==yes   $if exist 'POLREQ.inc' $INCLUDE 'POLREQ.inc';
$ifi %POLICIES%==yes   $if not exist 'POLREQ.inc' $INCLUDE '../../base/addons/policies/data/POLREQ.inc';

$ifi %SYSTEMCOST%==yes   $if exist     '../data/BASELOADSERVICE.inc' $INCLUDE    '../data/BASELOADSERVICE.inc';
$ifi %SYSTEMCOST%==yes   $if not exist '../data/BASELOADSERVICE.inc' $INCLUDE '../../base/data/BASELOADSERVICE.inc';

* This file (if exists) contains:
* PARAMETER XHKINI(IAAAE,IAAAI)    'Initial heat transmission capacity between regions'
* PARAMETER XHINVCOST(IAAAE,IAAAI) 'Investment cost in new heat transmission cap'
* PARAMETER XHCOST(IAAAE,IAAAI)    'Heat transmission cost between countries'
* PARAMETER XHLOSS(IAAAE,IAAAI)    'Heat transmission loss between regions'

* Data for handling of annual hydro constraints in BB3:
$ifi %bb3%==yes $include '../../base/addons/hyrsbb123/hyrsbb123includebb12data.inc';

* Printing of data to the list file controlled by %ONOFFDATALISTING% and %ONOFFCODELISTING%:
%ONOFFDATALISTING%

SCALAR PENALTYQ  'Penalty on violation of equation'  %semislash%
$if     EXIST '../data/PENALTYQ.inc' $INCLUDE         '../data/PENALTYQ.inc';
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
* Reduce size of the large parameters:
DE_VAR_T(RRR,DEUSER,SSS,TTT)$(not IR(RRR)) = 0;
DH_VAR_T(AAA,DHUSER,SSS,TTT)$(not IA(AAA)) = 0;
X3FX_VAR_T(RRR,SSS,TTT)$(not IR(RRR)) = 0;
WND_VAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;
SOLE_VAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;
SOLH_VAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;
WAVE_VAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;
WTRRRVAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;

*-------------------------------------------------------------------------------
* Declaration and definition of (additional) internal sets, aliases and parameters:
*-------------------------------------------------------------------------------


PARAMETER IGKFXYMAX(AAA,G) "The maximum over years in Y of exogenously specified capacity (MW)" ;


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
$ifi %timeaggr%==yes  $include '../../base/addons/timeaggregation/timeaggr.inc';


* The following relates technology and fuel:
SET IGF(GGG,FFF)   'Relation between technology type and fuel type';


*------------------------------------------------------------------------------
* Internal sets:


SET IAGK_Y(AAA,G)        'Area, technology with positive capacity current simulation year';
SET IXKN(IRRRE,IRRRI)   'Pair of regions that may get new transmission capacity';

* Specification of where new endogenous generation capacity may be located:

SET IAGKN(AAA,G)     'Area, technology where technology may be invested based on AGKN and implicit constraints ';
* Initialisation: equal to AGKN:
IAGKN(IA,G)=AGKN(IA,G); !! Move TODO.


SET IPLUSMINUS "Violation of equation"  /IPLUS Violation of equation upwards, IMINUS  Violation of equation downwards/;
* Note: When placed on the left hand side of the equation
* the sign to the IMINUS and IPLUS terms should be - and +, respectively.
* This way the sign and the name will be intuitively consistent in equation listings in Balmorel.lst.

*------------------------------------------------------------------------------
* Internal parameters and settings:
*------------------------------------------------------------------------------


* Set GDCV value to one for IGBPR and IGHOB units so that their fuel consumption
* can be found using the same formula as for IGCND and IGEXT:
GDATA(IGBPR,'GDCV') = 1;
GDATA(IGHOB,'GDCV') = 1;

* Specifying the relation between technology type and fuel type in IGF:

IGF(G,FFF)=YES$(GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'));
IGF(G,FFF)$(GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))=YES;

PARAMETER IGKRATE(AAA,G,S,T)     "Rating of technology capacities (non-negative, typically less than or equal to 0); default/1/, eps for 0)";
* Transfer data from data file to IGKRATE according to domain:
$ifi %GKRATE_DOL%==AAA_GGG_SSS_TTT  IGKRATE(IA,G,S,T) = GKRATE(IA,G,S,T);
$ifi %GKRATE_DOL%==AAA_GGG_SSS      IGKRATE(IA,G,S,T) = GKRATE(IA,G,S);

* The following parameters contain information about CO2 and SO2 emission
* from technology G based on the fuel used and its emission data:
PARAMETER   IM_CO2(G)   'CO2 emission coefficient for fuel, fossil and renewable (kg/GJ)';
PARAMETER   IM_CO2RE(G) 'CO2 emission coefficient for fuel, renewable part (kg/GJ)';
PARAMETER   IM_SO2(G)   'SO2 emission coefficient for fuel (kg/GJ)';
PARAMETER   IM_N2O(G)   'NO2 emission coefficient for fuel (kg/GJ)';

LOOP(FFF,
  IM_CO2(G)$IGF(G,FFF)   = FDATA(FFF,'FDCO2');
  IM_CO2RE(G)$IGF(G,FFF) = FDATA(FFF,'FDCO2')*FDATA(FFF,'FDRE');
  IM_SO2(G)$IGF(G,FFF)   = FDATA(FFF,'FDSO2')$(GDATA(G,'GDDESO2') EQ 0) +
      (FDATA(FFF,'FDSO2')*(1-GDATA(G,'GDDESO2')))$(GDATA(G,'GDDESO2') GT 0);
  IM_N2O(G)$IGF(G,FFF)   = FDATA(FFF,'FDN2O');
);


* Further declarations relative to variations:
* Parameters holding the total weight in the (arbitrary) units of the weights
* used in input for each season and time period.
* To be used in calculations below.

PARAMETER IWEIGHSUMS          'Weight of the time of each season in S';
PARAMETER IWEIGHSUMT          'Weight of the time of each time period in T ';

* The (arbitrary) units used in the input are converted to days and hours,
* respectively. Note that IHOURSIN24 is given in hours.
PARAMETER IHOURSINST(SSS,T)   'Length of time segment (hours)';

* Annual amounts as expressed in the units of the weights and demands used
* in input in the file var.inc:
PARAMETER IDE_SUMST(RRR,DEUSER) 'Annual amount of nominal electricity demand (MWh)';
PARAMETER IDH_SUMST(AAA,DHUSER) 'Annual amount of nominal heat demand (MWh)';
PARAMETER IX3FXSUMST(RRR)       'Annual amount of fixed electricity export to third countries relative to X3FX_VAR_T and (S,T) (MWh)';

* Sums for finding the wind and solar generated electricity generation
* as expressed in the units of the weights and demands used in input:

PARAMETER IWND_SUMST(AAA)  'Annual amount of wind generated electricity relative to WND_VAR_T and (S,T) (MWh)';
PARAMETER ISOLESUMST(AAA)  'Annual amount of solar generated electricity relative to ISOLESUMST and (S,T) (MWh)';
PARAMETER ISOLHSUMST(AAA)  'Annual amount of solar generated heat relative to ISOLHSUMST and (S,T) (MWh)';
PARAMETER IWAVESUMST(AAA)  'Annual amount of wave generated electricity relative to WND_VAR_T and (S,T) (MWh)';
PARAMETER IWTRRSSUM(AAA)   'Annual amount of hydro from reservoirs generated electricity relative to IWTRRSSUM and (S,T) (MWh)';
PARAMETER IWTRRRSUM(AAA)   'Annual amount of hydro-run-of-river generated electricity relative to IWTRRRSUM and (S,T) (MWh)';

*-------------------------------------------------------------------------------
* Set the time weights depending on the model:
*-------------------------------------------------------------------------------
* The following code ensures that with time aggregation the energy content (MWh) in time series is conserved, but it does no ensure that the power (MW) is conserved.
* To get an aggregation that preserves both energy,  power and possibly more, use an addon or auxil.


$ifi %BB1%==yes    IWEIGHSUMS = SUM(S, WEIGHT_S(S));
$ifi %BB1%==yes    IWEIGHSUMT = SUM(T, WEIGHT_T(T));
$ifi %BB1%==yes    IHOURSINST(S,T)=IOF8760*WEIGHT_S(S)*WEIGHT_T(T)/(IWEIGHSUMS*IWEIGHSUMT);
$ifi %BB1%==yes    IDE_SUMST(IR,DEUSER) = SUM((S,T), IHOURSINST(S,T)*DE_VAR_T(IR,DEUSER,S,T));
$ifi %BB1%==yes    IDH_SUMST(IA,DHUSER) = SUM((S,T), IHOURSINST(S,T)*DH_VAR_T(IA,DHUSER,S,T));
$ifi %BB1%==yes    IX3FXSUMST(IR) = SUM((S,T), IHOURSINST(S,T)*X3FX_VAR_T(IR,S,T));
$ifi %BB1%==yes    IWND_SUMST(IA)=SUM((S,T), IHOURSINST(S,T)*WND_VAR_T(IA,S,T));
$ifi %BB1%==yes    ISOLESUMST(IA)=SUM((S,T), IHOURSINST(S,T)*SOLE_VAR_T(IA,S,T));
$ifi %BB1%==yes    ISOLHSUMST(IA)=SUM((S,T), IHOURSINST(S,T)*SOLH_VAR_T(IA,S,T));
$ifi %BB1%==yes    IWAVESUMST(IA)=SUM((S,T), IHOURSINST(S,T)*WAVE_VAR_T(IA,S,T));
$ifi %BB1%==yes    IWTRRRSUM(IA)=SUM((S,T),  IHOURSINST(S,T)*WTRRRVAR_T(IA,S,T));
$ifi %BB1%==yes    IWTRRSSUM(IA)=SUM(S, (WEIGHT_S(S)/IWEIGHSUMS)*WTRRSVAR_S(IA,S));

$ifi %BB2%==yes    IWEIGHSUMS = SUM(S, WEIGHT_S(S));
$ifi %BB2%==yes    IWEIGHSUMT = SUM(T, WEIGHT_T(T));
$ifi %BB2%==yes    IHOURSINST(S,T)=IOF8760*WEIGHT_S(S)*WEIGHT_T(T)/(IWEIGHSUMS*IWEIGHSUMT);
$ifi %BB2%==yes    IDE_SUMST(IR,DEUSER) = SUM((S,T), IHOURSINST(S,T)*DE_VAR_T(IR,DEUSER,S,T));
$ifi %BB2%==yes    IDH_SUMST(IA,DHUSER) = SUM((S,T), IHOURSINST(S,T)*DH_VAR_T(IA,DHUSER,S,T));
$ifi %BB2%==yes    IX3FXSUMST(IR) = SUM((S,T), IHOURSINST(S,T)*X3FX_VAR_T(IR,S,T));
$ifi %BB2%==yes    IWND_SUMST(IA)=SUM((S,T), IHOURSINST(S,T)*WND_VAR_T(IA,S,T));
$ifi %BB2%==yes    ISOLESUMST(IA)=SUM((S,T), IHOURSINST(S,T)*SOLE_VAR_T(IA,S,T));
$ifi %BB2%==yes    ISOLHSUMST(IA)=SUM((S,T), IHOURSINST(S,T)*SOLH_VAR_T(IA,S,T));
$ifi %BB2%==yes    IWAVESUMST(IA)=SUM((S,T), IHOURSINST(S,T)*WAVE_VAR_T(IA,S,T));
$ifi %BB2%==yes    IWTRRRSUM(IA)=SUM((S,T),  IHOURSINST(S,T)*WTRRRVAR_T(IA,S,T));
$ifi %BB2%==yes    IWTRRSSUM(IA)=SUM(S, (WEIGHT_S(S)/IWEIGHSUMS)*WTRRSVAR_S(IA,S));

$ifi %BB3%==yes    IWEIGHSUMS = SUM(SSS, WEIGHT_S(SSS));
$ifi %BB3%==yes    IWEIGHSUMT = SUM(T, WEIGHT_T(T));
$ifi %BB3%==yes    IHOURSINST(SSS,T)=IOF8760*(WEIGHT_S(SSS)*WEIGHT_T(T))/(IWEIGHSUMS*IWEIGHSUMT);
$ifi %BB3%==yes    IDE_SUMST(IR,DEUSER) = SUM((SSS,T), IHOURSINST(SSS,T)*DE_VAR_T(IR,DEUSER,SSS,T));
$ifi %BB3%==yes    IDH_SUMST(IA,DHUSER) = SUM((SSS,T), IHOURSINST(SSS,T)*DH_VAR_T(IA,DHUSER,SSS,T));
$ifi %BB3%==yes    IX3FXSUMST(IR) = SUM((SSS,T), IHOURSINST(SSS,T)*X3FX_VAR_T(IR,SSS,T));
$ifi %BB3%==yes    IWND_SUMST(IA)=SUM((SSS,T), IHOURSINST(SSS,T)*WND_VAR_T(IA,SSS,T));
$ifi %BB3%==yes    ISOLESUMST(IA)=SUM((SSS,T), IHOURSINST(SSS,T)*SOLE_VAR_T(IA,SSS,T));
$ifi %BB3%==yes    ISOLHSUMST(IA)=SUM((SSS,T), IHOURSINST(SSS,T)*SOLH_VAR_T(IA,SSS,T));
$ifi %BB3%==yes    IWAVESUMST(IA)=SUM((SSS,T), IHOURSINST(SSS,T)*WAVE_VAR_T(IA,SSS,T));
$ifi %BB3%==yes    IWTRRRSUM(IA)=SUM((SSS,T),  IHOURSINST(SSS,T)*WTRRRVAR_T(IA,SSS,T));
$ifi %BB3%==yes    IWTRRSSUM(IA)=SUM(SSS, (WEIGHT_S(SSS)/IWEIGHSUMS)*WTRRSVAR_S(IA,SSS));

*-------------------------------------------------------------------------------
* End of: Set the time weights depending on the model
*-------------------------------------------------------------------------------

/*
* PARAMETER IDEFP_T holds the price levels of individual steps
* in the electricity demand function, transformed to be comparable with
* production costs (including fuel taxes) by subtraction of taxes
* and distribution costs.
* Unit: Money/MWh.

PARAMETER IDEFP_T(RRR,SSS,TTT,DEF)    'Prices on elastic electricity demand steps (Money/MWh)';

IDEFP_T(IR,S,T,DEF_D1) = DEF_STEPS(IR,S,T,'DF_PRICE',DEF_D1)*DEFP_BASE(IR)
- SUM(C$CCCRRR(C,IR),TAX_DE(C)) - DISCOST_E(IR)
$ifi %DEFPCALIB%==yes  + DEFP_CALIB(IR,S,T)
;

IDEFP_T(IR,S,T,DEF_U1) = DEF_STEPS(IR,S,T,'DF_PRICE',DEF_U1)*DEFP_BASE(IR)
- SUM(C$CCCRRR(C,IR),TAX_DE(C)) - DISCOST_E(IR)
$ifi %DEFPCALIB%==yes  + DEFP_CALIB(IR,S,T)
;

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

IDHFP_T(IA,S,T,DHF)$(DHF_D1(DHF)+DHF_U1(DHF)+DHF_D2(DHF)+DHF_U2(DHF)+DHF_D2(DHF)+DHF_U2(DHF))=
   DHF_STEPS(IA,S,T,'DF_PRICE',DHF)*DHFP_BASE(IA) - SUM(C$ICA(C,IA),TAX_DH(C)) - DISCOST_H(IA)
$ifi %DHFPCALIB%==yes  + DHFP_CALIB(IA,S,T)
;


*/

* Demand of electricity (MW) and heat (MW) current simulation year:
PARAMETER IDE_T_Y(RRR,S,T)      'Nominal electricity demand (MW) time segment (S,T) current simulation year',
          IDH_T_Y(AAA,S,T)      'Nominal heat demand (MW) time segment (S,T) current simulation year';
* Generation capacity (MW) at the beginning of current simulation year,
* specified by GKFX and by accumulated endogeneous investments, respectively:
PARAMETER IGKFX_Y(AAA,GGG)      'Externally given generation capacity in year Y (MW)',
          IGKFX_Y_1(AAA,GGG)    'Externally given generation capacity in year -1 (MW)',
          IGKVACCTOY(AAA,G)     'Internally given generation capacity at beginning of year (MW)(cumulative investments minus decommissioning)',
*          IGKVACCTOYNODECOM(G,AAA)'Cumulative investments in generation capacity at beginning of year',
          IGKVACCEOY(AAA,G)     'Internally given generation capacity at end of year (MW)(cumulative investments minus decommissioning)';


* Emission policy data during current simulation year:
PARAMETER ITAX_CO2_Y(C)  'Tax on CO2 (Money/t)' ,
          ITAX_SO2_Y(C)  'Tax on SO2 (Money/t)',
          ITAX_NOX_Y(C)  'Tax on NOX (Money/kg)';
PARAMETER ILIM_CO2_Y(C)  'CO2 emission limit',
          ILIM_SO2_Y(C)  'SO2 emission limit',
          ILIM_NOX_Y(C)  'NOX emission limit';

* Taxes differentiated by area and technology (AAA,G)
PARAMETER  ITAX_GF(AAA,G)   'Fuel taxes on heat-only units',
           ITAX_GH(AAA,G)   'Heat taxes on generation units',
           ITAX_GE(AAA,G)   'Electricity taxes on generation units and subsidies(-) (EURO 90/MWh)',
           ITAX_KN(AAA,G)   'Tax (neg. subsidy) for investment in electricity generation (mEUR90/MW)';
*          ITAX_IE(AAA,G)
* Fuel use differentiated by geography and fuel (CCCRRRAAA,FFF)
PARAMETER  IGMAXF_Y(CCCRRRAAA,FFF)     'Maximum fuel use per year (GJ)',
           IGMINF_Y(CCCRRRAAA,FFF)     'Minimum fuel use per year (GJ)',
           IGEQF_Y(CCCRRRAAA,FFF)      'Required fuel use per year (GJ)'


* Transmission capacity (MW) between regions RE (exporting) and  RI (importing)
* at the beginning of current simulation year:
PARAMETER IXKINI_Y(IRRRE,IRRRI)      'Externally given transmission capacity between regions at beginning of year (MW)',
          IXKVACCTOY(IRRRE,IRRRI) 'Internally given transmission capacity at beginning of year (cumulative investments) (MW)';

* Possibilities for new transmission lines:

IXKN(IRE,IRI) = NO;

* Fixed exchange with third countries (MW) current simulation year:
PARAMETER IX3FX_T_Y(RRR,S,T)   'Fixed export to third countries for each time segment (MW)';

PARAMETER IXKRATE(IRRRE,IRRRI,SSS,TTT)  "Transmission capacity rating (share; non-negative, typically close to 1; default/1/, eps for 0)";
* Transfer data from data file to IXKRATE according to domain:
$ifi %XKRATE_DOL%==IRRRE_IRRRI          IXKRATE(IRE,IRI,S,T) = XKRATE(IRE,IRI);
$ifi %XKRATE_DOL%==IRRRE_IRRRI_SSS      IXKRATE(IRE,IRI,S,T) = XKRATE(IRE,IRI,S);
$ifi %XKRATE_DOL%==IRRRE_IRRRI_SSS_TTT  IXKRATE(IRE,IRI,S,T) = XKRATE(IRE,IRI,S,T);


* Fuel price for current simulation year:
PARAMETER IFUELP_Y(AAA,FFF)   'Fuel price in the year simulated';

* Inflow in areas each season:
* The following is used in balbase1.sim and balbase2.sim
PARAMETER IHYINF_S(AAA,SSS)  'Water inflow to hydro reservoirs in areas in each season (MWh/MW)';

* In BB3 one of the following parameters are used to control the use of hydro:

PARAMETER IGROWTHCAP(C,G)        'Limit on growth of technology dependant on years between optimisation';

PARAMETER IGKNMAX_Y(AAA,G)       'Maximum capacity of new technologies (MW)';

*-------------------------------------------------------------------------------
*----- Any internal sets and parameters for addon to be placed here: -----------
*-------------------------------------------------------------------------------

$INCLUDE '../../base/addons/_hooks/ipardecdef.inc';

* These internal parameters pertain to price sensitivy electricity exchange with third countries.
$ifi %X3V%==yes $include '../../base/addons/x3v/model/x3vinternal.inc';
* These internal parameters and sets pertain to heat transmission.
$if %HEATTRANS% == yes $include '../../base/addons/heattrans/model/htinternal.inc';
* Aggregated heat demand profile used in data_fv.inv, therefore placed here.
$ifi %FV%==yes $INCLUDE '../../base/addons/fjernvarme/data_fv.inc';
* Unit commitment addon
$ifi %UnitComm%==yes $include '../../base/addons/unitcommitment/uc_intern.inc';
* Discrete size investments addon
$ifi %AGKNDISC%==yes   $include '../../base/addons/agkndisc/agkndiscinternal.inc';


*-------------------------------------------------------------------------------
*----- End: Any internal sets and parameters for addon to be placed here -------
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
*----- End: Internal parameters and settings -----------------------------------
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
*----- Possibly write input data, prepare output file possibilities: -----------
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
$ifi %system.filesys%==UNIX
$ifi exist '"%relpathInputdata2GDX%INPUTDATAOUT.gdx"' rm '"%relpathInputdata2GDX%INPUTDATAOUT.gdx"';
$ifi %system.filesys%==MSNT
$ifi exist '"%relpathInputdata2GDX%INPUTDATAOUT.gdx"' del '"%relpathInputdata2GDX%INPUTDATAOUT.gdx"';

$ifi %INPUTDATA2GDX%==yes execute_unload '%relpathInputdata2GDX%INPUTDATAOUT.gdx';
* Transfer inputdata a seperate Access file (only possible if %INPUTDATA2GDX%==yes):

$ifi %INPUTDATAGDX2MDB%==yes execute '=GDX2ACCESS "%relpathInputdata2GDX%INPUTDATAOUT.gdx"';

$ifi %MERGEINPUTDATA%==yes
$ifi NOT (%BB3%==yes) execute_unload '../output/temp/1INPUT.gdx';

$ifi %MERGEINPUTDATA%==yes
$ifi %BB3%==yes $ifi not (%limitedresults%==yes) execute_unload '../output/temp/1INPUT.gdx';

$ifi %MERGEINPUTDATA%==yes
$ifi %BB3%==yes $ifi %limitedresults%==yes execute_unload '../output/temp/1INPUT.gdx'
$ifi %MERGEINPUTDATA%==yes
$ifi %BB3%==yes $ifi %limitedresults%==yes $INCLUDE '../../base/model/syminput.inc';

*-------------------------------------------------------------------------------
* End: Possibly write input data, prepare output file possibilities
*-------------------------------------------------------------------------------


$ifi %REShareE%==yes $include     '../addons/REShareE/RESEintrn.inc';
$ifi %REShareE%==yes file REShareEPrt4 / '../printout/RESEprt4.out' /;
$ifi %REShareE%==yes $if     EXIST '../data/RESEEDATA.inc' $INCLUDE         '../data/RESEEDATA.inc';
$ifi %REShareE%==yes $if not EXIST '../data/RESEEDATA.inc' $INCLUDE '../../base/data/RESEEDATA.inc';

$ifi %REShareEH%==yes $include '../addons/REShareEH/RESEHintrn.inc';
$ifi %REShareEH%==yes file REShareEHPrt4 / '../printout/RESEHprt4.out' /;
$ifi %REShareEH%==yes $if     EXIST '../data/RESEHDATA.inc' $INCLUDE         '../data/RESEHDATA.inc';
$ifi %REShareEH%==yes $if not EXIST '../data/RESEHDATA.inc' $INCLUDE '../../base/data/RESEHDATA.inc';

*------------------------------

* A number of input data IDs contain more information than is actually used with the set-up of the model.
* To reduce use of memory space and to reduce further processing and storage of unused data
* some of the larger data IDs are here reduced by resetting unused data items to default values.
$include "../../base/addons/_hooks/reducecard.inc"

DE_VAR_T(RRR,DEUSER,SSS,TTT)$((NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
DH_VAR_T(AAA,DHUSER,SSS,TTT)$((NOT IA(AAA)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
WND_VAR_T(AAA,SSS,TTT)$((NOT IA(AAA)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
SOLE_VAR_T(AAA,SSS,TTT)$((NOT IA(AAA)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
SOLH_VAR_T(AAA,SSS,TTT)$((NOT IA(AAA)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
WTRRSVAR_S(AAA,SSS)$((NOT IA(AAA)) OR (NOT S(SSS))) = 0;
WTRRRVAR_T(AAA,SSS,TTT)$((NOT IA(AAA)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
WAVE_VAR_T(AAA,SSS,TTT)$((NOT IA(AAA)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
X3FX_VAR_T(RRR,SSS,TTT)$((NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
*DEF_STEPS(RRR,SSS,TTT,DF_QP,DEF)$((NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
*DEF_STEPS(IR,S,T,DF_QP,DEF)$((NOT DEF_D1(DEF) AND (NOT DEF_D2(DEF)) AND (NOT DEF_D3(DEF)) AND (NOT DEF_U1(DEF)) AND (NOT DEF_U2(DEF)) AND (NOT DEF_U3(DEF)))) = 0;
*DHF_STEPS(AAA,SSS,TTT,DF_QP,DHF)$((NOT IA(AAA)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
*DHF_STEPS(IA,S,T,DF_QP,DHF)$((NOT DHF_D1(DHF) AND (NOT DHF_D2(DHF)) AND (NOT DHF_D3(DHF)) AND (NOT DHF_U1(DHF)) AND (NOT DHF_U2(DHF)) AND (NOT DHF_U3(DHF)))) = 0;
$ifi %GKRATE_DOL%==AAA_GGG_SSS_TTT     GKRATE(AAA,GGG,SSS,TTT)$((NOT IA(AAA)) OR (NOT G(GGG)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
$ifi %GKRATE_DOL%==AAA_GGG_SSS         GKRATE(AAA,GGG,SSS)$((NOT IA(AAA)) OR (NOT G(GGG)) OR (NOT S(SSS))) = 0;
GKNMAX(YYY,AAA,GGG)$((NOT Y(YYY)) OR (NOT IA(AAA))) = 0;

*------------------------------

* Unload input data to gdx and possibly MDB files.
* Note that this is a compile time operation, such that only the 'direct' data
* definitions (and no assignments) are reflected:


$include "../../base/addons/_hooks/checkassumptions.inc"

* No need to proceed further if there are compilation errors in the data:
$ifi not errorfree $abort "Balmorel execution aborted because of data errors (Message from Balmorel.gms)"

*------------------------------


*-------------------------------------------------------------------------------
*  Declaration of VARIABLES:
*-------------------------------------------------------------------------------

FREE     VARIABLE VOBJ                             'Objective function value (MMoney)';
POSITIVE VARIABLE VGE_T(AAA,G,S,T)                 'Electricity generation (MW), existing units';
POSITIVE VARIABLE VGEN_T(AAA,G,S,T)                'Electricity generation (MW), new units';
POSITIVE VARIABLE VGH_T(AAA,G,S,T)                 'Heat generation (MW), existing units';
POSITIVE VARIABLE VGF_T(AAA,G,S,T)                 'Fuel consumption rate (MW), existing units'
POSITIVE VARIABLE VX_T(IRRRE,IRRRI,S,T)            'Electricity export from region IRRRE to IRRRI (MW)';
POSITIVE VARIABLE VGHN_T(AAA,G,S,T)                'Heat generation (MW), new units';
POSITIVE VARIABLE VGFN_T(AAA,G,S,T)                'Fuel consumption rate (MW), new units'
POSITIVE VARIABLE VGKN(AAA,G)                      'New generation capacity (MW);  for storages (MWh) ';
POSITIVE VARIABLE VXKN(IRRRE,IRRRI)                'New electricity transmission capacity (MW)';
POSITIVE VARIABLE VDECOM(AAA,G)                    'Decommissioned capacity(MW)';
*POSITIVE VARIABLE VDEF_T(RRR,S,T,DEF)              'Flexible electricity demands (MW)';
*POSITIVE VARIABLE VDHF_T(AAA,S,T,DHF)              'Flexible heat demands (MW)';
POSITIVE VARIABLE VGHYPMS_T(AAA,S,T)               'Contents of pumped hydro storage (MWh)';
POSITIVE VARIABLE VHYRS_S(AAA,S)                   'Hydro energy equivalent at the start of the season (MWh)';
POSITIVE VARIABLE VESTOLOADT(AAA,S,T)              'Intra-seasonal electricity storage loading (MW)';
POSITIVE VARIABLE VESTOLOADTS(AAA,S,T)             'Inter-seasonal electricity storage loading (MW)';
POSITIVE VARIABLE VHSTOLOADT(AAA,S,T)              'Intra-seasonal heat storage loading (MW)';
POSITIVE VARIABLE VHSTOLOADTS(AAA,S,T)             'Inter-seasonal heat storage loading (MW)';
POSITIVE VARIABLE VESTOVOLT(AAA,S,T)               'Intra-seasonal electricity storage contents at beginning of time segment (MWh)';
POSITIVE VARIABLE VESTOVOLTS(AAA,S,T)              'Inter-seasonal electricity storage contents at beginning of time segment (MWh)';
POSITIVE VARIABLE VHSTOVOLT(AAA,S,T)               'Heat storage contents at beginning of time segment (MWh)';
POSITIVE VARIABLE VHSTOVOLTS(AAA,S,T)              'Inter-seasonal heat storage contents at beginning of time segment (MWh)';
POSITIVE VARIABLE VQEEQ(RRR,S,T,IPLUSMINUS)        'Feasibility in electricity balance equation QEEQ (MW)';
POSITIVE VARIABLE VQHEQ(AAA,S,T,IPLUSMINUS)        'Feasibility in heat balance equantion QHEQ (MW)';
POSITIVE VARIABLE VQESTOVOLT(AAA,S,T,IPLUSMINUS)   'Feasibility in intra-seasonal electricity storage equation QESTOVOLT (MWh)';
POSITIVE VARIABLE VQESTOVOLTS(AAA,S,T,IPLUSMINUS)  'Feasibility in inter-seasonal electricity storage equation QESTOVOLTS (MWh)';
POSITIVE VARIABLE VQHSTOVOLT(AAA,S,T,IPLUSMINUS)   'Feasibility in intra-seasonal heat storage equation VQHSTOVOLT (MWh)';
POSITIVE VARIABLE VQHSTOVOLTS(AAA,S,T,IPLUSMINUS)  'Feasibility in inter-seasonal heat storage equation VQHSTOVOLTS (MWh)';
POSITIVE VARIABLE VQHYRSSEQ(AAA,S,IPLUSMINUS)      'Feasibility of hydropower reservoir equation QHYRSSEQ (MWh)';
POSITIVE VARIABLE VQHYRSMINMAXVOL(AAA,S,IPLUSMINUS)'Feasibility of hydropower reservoir minimum (IPLUSMINUS) and maximum (IPLUSMINUS) content (MWh)';
POSITIVE VARIABLE VQGEQCF(C,FFF,IPLUSMINUS)        'Feasibility in Requered fuel usage per country constraint (MWh)'
POSITIVE VARIABLE VQGMINCF(C,FFF)                  'Feasibility in Minimum fuel usage per country constraint (MWh)'
POSITIVE VARIABLE VQGMAXCF(C,FFF)                  'Feasibility in Maximum fuel usage per country constraint (MWh)'
POSITIVE VARIABLE VQGEQRF(RRR,FFF,IPLUSMINUS)      'Feasibility in Requered fuel usage per region constraint (MWh)'
POSITIVE VARIABLE VQGMAXRF(RRR,FFF)                'Feasibility in Minimum fuel usage per region constraint (MWh)'
POSITIVE VARIABLE VQGMINRF(RRR,FFF)                'Feasibility in Maximum fuel usage per region constraint (MWh)'
POSITIVE VARIABLE VQGEQAF(AAA,FFF,IPLUSMINUS)      'Feasibility in Required fuel usage per area constraint (MWh)'
POSITIVE VARIABLE VQGMAXAF(AAA,FFF)                'Feasibility in Minimum fuel usage per area constraint (MWh)'
POSITIVE VARIABLE VQGMINAF(AAA,FFF)                'Feasibility in Maximum fuel usage per area constraint (MWh)'
POSITIVE VARIABLE VQXK(IRRRE,IRRRI,S,T,IPLUSMINUS) 'Feasibility in Transmission capacity constraint (MW)'


*-------------------------------------------------------------------------------
*----- Any variables for addon to be placed here: ------------------------------
*-------------------------------------------------------------------------------
$INCLUDE '../../base/addons/_hooks/vardeclare.inc';

* These variables are for addon X3V (price sensitive third countries elec exchange
$ifi %X3V%==yes $include '../../base/addons/x3v/model/x3vvariables.inc';
* These variables are for addon heat transmission
$ifi %HEATTRANS%==yes $include '../../base/addons/heattrans/model/htvariables.inc';
* These  variables are for addon district heating
$ifi %FV%==yes $include '../../base/addons/fjernvarme/var_fv.inc';
* These variables are for addon unit commitment
$ifi %UnitComm%==yes $include '../../base/addons/unitcommitment/uc_vars.inc';
$ifi %UnitComm%==yes $include '../../base/addons/unitcommitment/uc_eqns.inc';
* These variables are for addon discrete size investments
$ifi %AGKNDISC%==yes  $include '../../base/addons/agkndisc/agkndiscvariables.inc';
* These variables are for addon policies
$ifi %POLICIES%==yes $include '../../base/addons/policies/pol_var.inc';
* These variables are for addon system costs
$ifi %SYSTEMCOST%==yes $include '../../base/addons/SystemCost/var_syscost.inc';
* These variables are for addon for hydro
$ifi %HYRSBB123%==quantprice  $include "../../base/addons/hyrsbb123/hyrsbb123variables.inc";


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
   QOBJ                        'Objective function'
   QEEQ(RRR,S,T)               'Electricity generation equals demand (MW)'
   QHEQ(AAA,S,T)               'Heat generation equals demand (MW)'
   QGFEQ(AAA,G,S,T)            'Calculate fuel consumption, existing units (MW)'
   QGFNEQ(AAA,G,S,T)           'Calculate fuel consumption, new units (MW)'
   QGCBGBPR(AAA,G,S,T)         'CHP generation (back pressure) limited by Cb-line (MW)'
   QGCBGBPRBYPASS1(AAA,G,S,T)  'CHP generation (back pressure) with bypass limited by Cb-line (MW)'
   QGCBGBPRBYPASS2(AAA,G,S,T)  'CHP generation (back pressure) with bypass limited by BYPC-line (MW)'
   QGCBGEXT(AAA,G,S,T)         'CHP generation (extraction) limited by Cb-line (MW)'
   QGCVGEXT(AAA,G,S,T)         'CHP generation (extraction) limited by Cv-line (MW)'
   QGGETOH(AAA,G,S,T)          'Electric heat generation (MW)'
   QGNCBGBPR(AAA,G,S,T)        'CHP generation (back pressure) Cb-line, new (MW)'
   QGNCBGBPRBYPASS1(AAA,G,S,T) 'CHP generation (back pressure) with bypass limited by Cb-line, new (MW)'
   QGNCBGBPRBYPASS2(AAA,G,S,T) 'CHP generation (back pressure) with bypass limited by BYPC-line, new (MW)'
   QGNCBGEXT(AAA,G,S,T)        'CHP generation (extraction) Cb-line, new (MW)'
   QGNCVGEXT(AAA,G,S,T)        'CHP generation (extraction) Cv-line, new (MW)'
   QGNGETOH(AAA,G,S,T)         'Electric heat generation, new (MW)'
   QGEKNT(AAA,G,S,T)           'Generation on new electricity cap, limited by capacity (MW)'
   QGHKNT(AAA,G,S,T)           'Generation on new IGHH cap, limited by capacity (MW)'
   QGKNHYRR(AAA,G,S,T)         'Generation on new hydro-ror limited by capacity and water (MW)'
   QGKNWND(AAA,G,S,T)          'Generation on new windpower limited by capacity and wind (MW)'
   QGKNSOLE(AAA,G,S,T)         'Generation on new solarpower limited by capacity and sun (MW)'
   QGKNSOLH(AAA,G,S,T)         'Generation on new solarheat limited by capacity and sun (MW)'
   QGKNWAVE(AAA,G,S,T)         'Generation on new wavepower limited by cap and waves (MW)'
   QHYRSSEQ(AAA,S)             'Hydropower with reservoir seasonal dynamic energy constraint (MWh)'
   QHYRSMINVOL(AAA,S)          'Hydropower reservoir - minimum level (MWh)'
   QHYRSMAXVOL(AAA,S)          'Hydropower reservoir - maximum level (MWh)'
   QHYMAXG(AAA,S,T)            'Regulated and unregulated hydropower production lower than capacity'
   QESTOVOLT(AAA,S,T)          'Intra-seasonal electricty storage dynamic equation (MWh)'
   QESTOVOLTS(AAA,S,T)         'Inter-seasonal electricty storage dynamic equation (MWh)'
   QHSTOVOLT(AAA,S,T)          'Intra-seasonal heat storage dynamic equation (MWh)'
   QHSTOVOLTS(AAA,S,T)         'Inter-seasonal heat storage dynamic equation (MWh)'
   QHSTOLOADTLIM(AAA,S,T)      'Intra-seasonal heat storage upper loading limit (model Balbase2 only) (MW)'
   QHSTOLOADTLIMS(AAA,S,T)     'Inter-seasonal heat storage upper loading limit (model Balbase2 only) (MW)'
   QESTOLOADTLIM(AAA,S,T)      'Intra-seasonal electricity storage upper loading limit (model Balbase2 only) (MW)'
   QESTOLOADTLIMS(AAA,S,T)     'Intra-seasonal electricity storage upper loading limit (model Balbase2 only) (MW)'
   QHSTOVOLTLIM(AAA,S,T)       'Intra-seasonal heat storage capacity limit (model Balbase2 only) (MWh)'
   QHSTOVOLTLIMS(AAA,S,T)      'Inter-seasonal heat storage capacity limit (model Balbase2 only) (MWh)'
   QESTOVOLTLIM(AAA,S,T)       'Intra-seasonal electricity storage capacity limit (model Balbase2 only) (MWh)'
   QESTOVOLTLIMS(AAA,S,T)      'Inter-seasonal electricity storage capacity limit (model Balbase2 only) (MWh)'
   QKFUELC(C,FFF)              'Total capacity using fuel FFF is limited in country (MW)'
   QKFUELR(RRR,FFF)            'Total capacity using fuel FFF is limited in region (MW)'
   QKFUELA(AAA,FFF)            'Total capacity using fuel FFF is limited in area (MW)'
   QFGEMINC(C,FFF)             'Minimum electricity generation by fuel per country (MWh)'
   QFGEMAXC(C,FFF)             'Maximum electricity generation by fuel per country (MWh)'
   QFGEMINR(RRR,FFF)           'Minimum electricity generation by fuel per region (MWh)'
   QFGEMAXR(RRR,FFF)           'Maximum electricity generation by fuel per region (MWh)'
   QFGEMINA(AAA,FFF)           'Minimum electricity generation by fuel per area (MWh)'
   QFGEMAXA(AAA,FFF)           'Maximum electricity generation by fuel per area (MWh)'
   QGMINCF(C,FFF)              'Minimum fuel usage per country constraint (MWh)'
   QGMAXCF(C,FFF)              'Maximum fuel usage per country constraint (MWh)'
   QGEQCF(C,FFF)               'Required fuel usage per country constraint (MWh)'
*   QGEQCF_S(C,FFF,S)           'Seasonal required fuel usage per country constraint(MWh)'
   QGMINRF(RRR,FFF)            'Minimum fuel usage per region constraint (MWh)'
   QGMAXRF(RRR,FFF)            'Maximum fuel usage per region constraint (MWh)'
   QGEQRF(RRR,FFF)             'Required fuel usage per region constraint (MWh)'
*   QGEQRF_S(RRR,FFF,S)         'Seasonal required fuel usage per region constraint (MWh)'
   QGMINAF(AAA,FFF)            'Minimum fuel usage per area constraint (MWh)'
   QGMAXAF(AAA,FFF)            'Maximum fuel usage per area constraint (MWh)'
   QGEQAF(AAA,FFF)             'Required fuel usage per area constraint (MWh)'
*   QGEQAF_S(AAA,FFF,S)         'Seasonal required fuel usage per area constraint (MWh)'
   QXK(IRRRE,IRRRI,S,T)        'Transmission capacity constraint (MW)'
   QXMAXINV(IRRRE,IRRRI)       'Limit of new transmission capacity (MW)'
   QFMAXINVEST(C,FFF)          'Limit on investment in capacity defined per fuel'
   QLIMCO2(C)                  'Limit on annual CO2-emission (ton)'
   QLIMSO2(C)                  'Limit on annual SO2 emission (ton)'
   QLIMNOX(C)                  'Limit on annual NOx emission (kg)'
   QGMAXINVEST2(C,G)           'Maximum model generated capacity increase from one year to the next (MW)'
*   QSELFSUFFICIENCY(C)        'Equation to assure net import and exports are balanced in Denmark'


*-------------------------------------------------------------------------------
*----- Any equations declarations for addon to be placed here: -----------------
*-------------------------------------------------------------------------------


$ifi %PLANTCLOSURES%==yes   QGEKOT(AAA,G,S,T)      'Generation on old electricity capacity, limited by capacity';
$ifi %PLANTCLOSURES%==yes   QGHKOT(AAA,G,S,T)      'Generation on old electricity capacity, limited by capacity';

$ifi %PLANTCLOSURES%==yes   QGKOHYRR(AAA,G,S,T)    'Generation on old hydro-ror limited by capacity and water';
$ifi %PLANTCLOSURES%==yes   QGKOWND(AAA,G,S,T)     'Generation on old windpower limited by capacity and wind';
$ifi %PLANTCLOSURES%==yes   QGKOSOLE(AAA,G,S,T)    'Generation on old solarpower limited by capacity and sun';
$ifi %PLANTCLOSURES%==yes   QGKOWAVE(AAA,G,S,T)    'Generation on old wavepower limited by cap and waves';

$ifi %REShareE%==yes QREShareE(CCCREShareE)        'Minimum share of electricity production from renewable electricity';
$ifi %REShareEH%==yes QREShareEH(CCCREShareEH)     'Minimum share of electricity and heat production from renewable electricity';

$ifi %AGKNDISC%==yes QAGKNDISC01(AAA,G)            'At most one of the specified discrete capacity size investments is chosen (Addon AGKNDISC)';
$ifi %AGKNDISC%==yes QAGKNDISCCONT(AAA,G)          'The invested capacity must be one of the specified sizes or zero (MW) (Addon AGKNDISC)';

;

*-------------------------------------------------------------------------------
*----- End: Any equations declarations for addon to be placed here -------------
*-------------------------------------------------------------------------------




* Equation definitions:
*----- The objective function QOBJ: --------------------------------------------
QOBJ ..

   VOBJ =E=


*IOF0000001*(Note: in final version there will be no factor, because scaling of the equation is used.
IOF1_*(

* Cost of fuel consumption during the year:

     SUM((IAGK_Y(IA,G),FFF)$(GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM')),
                 IFUELP_Y(IA,FFF) * IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGF_T(IA,G,IS3,T)))

    +SUM((IAGKN(IA,G),FFF)$(GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM')),
                 IFUELP_Y(IA,FFF) * IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGFN_T(IA,G,IS3,T)))


* Operation and maintainance cost:

   + SUM(IAGK_Y(IA,IGE), GOMVCOST(IA,IGE) * SUM((IS3,T), IHOURSINST(IS3,T)*
     VGE_T(IA,IGE,IS3,T)))

   + SUM(IAGK_Y(IA,IGNOTETOH(IGH)), GOMVCOST(IA,IGNOTETOH) * SUM((IS3,T), IHOURSINST(IS3,T)*
     GDATA(IGNOTETOH,'GDCV')*(VGH_T(IA,IGNOTETOH,IS3,T))))

   + SUM(IAGKN(IA,IGE), GOMVCOST(IA,IGE) * SUM((IS3,T), IHOURSINST(IS3,T)*
     VGEN_T(IA,IGE,IS3,T)))

   + SUM(IAGKN(IA,IGNOTETOH(IGH)), GOMVCOST(IA,IGNOTETOH) * SUM((IS3,T), IHOURSINST(IS3,T)*
     GDATA(IGNOTETOH,'GDCV')*(VGHN_T(IA,IGNOTETOH,IS3,T))))

$ifi not %PLANTCLOSURES%==yes + IOF1000*(SUM(IAGK_Y(IA,G),(IGKVACCTOY(IA,G) + IGKFX_Y(IA,G))*GOMFCOST(IA,G)))
$ifi %PLANTCLOSURES%==yes     + IOF1000*(SUM(IAGK_Y(IA,G),(IGKVACCTOY(IA,G) + IGKFX_Y(IA,G) - VDECOM(IA,G))*GOMFCOST(IA,G)))

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

    + IOF1000000*(SUM((IAGKN(IA,G)), VGKN(IA,G)*GINVCOST(IA,G)*
$ifi %YIELDREQUIREMENT%==yes YIELDREQ(G)*
      (SUM(C$ICA(C,IA),ANNUITYC(C)))))


$ifi %AGKNDISC%==yes  $include '../../base/addons/agkndisc/agkndiscaddobj.inc';

* Investment tax (neg. subsidy), new electricity generation capacity:

    + IOF1000000*(SUM((IAGKN(IA,G)), VGKN(IA,G)*ITAX_KN(IA,G)*(SUM(C$ICA(C,IA),ANNUITYC(C)))))

* Investment costs, new transmission capacity
* (the average of the annuities for the two countries in question
* is used for international transmission):

    + SUM((IRE,IRI)$(IXKN(IRI,IRE) OR IXKN(IRE,IRI)), VXKN(IRE,IRI)*XINVCOST(IRE,IRI)*
      (IOF05*(SUM(C$CCCRRR(C,IRE),ANNUITYC(C))+SUM(C$CCCRRR(C,IRI),ANNUITYC(C)))))


* Emission taxes

    + SUM(C, SUM(IAGK_Y(IA,G)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_CO2(G)*IOF0001) * IOF3P6 * VGF_T(IA,G,IS3,T))  * ITAX_CO2_Y(C)))
    + SUM(C, SUM(IAGKN(IA,G)$ICA(C,IA),  SUM((IS3,T), IHOURSINST(IS3,T) * (IM_CO2(G)*IOF0001) * IOF3P6 * VGFN_T(IA,G,IS3,T)) * ITAX_CO2_Y(C)))

    + SUM(C, SUM(IAGK_Y(IA,G)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_SO2(G)*IOF0001) * IOF3P6 * VGF_T(IA,G,IS3,T))  * ITAX_SO2_Y(C)))
    + SUM(C, SUM(IAGKN(IA,G)$ICA(C,IA),  SUM((IS3,T), IHOURSINST(IS3,T) * (IM_SO2(G)*IOF0001) * IOF3P6 * VGFN_T(IA,G,IS3,T)) * ITAX_SO2_Y(C)))

    + SUM(C, SUM(IAGK_Y(IA,G)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (GDATA(G,'GDNOX')*IOF0000001)* IOF3P6 * VGF_T(IA,G,IS3,T))  * ITAX_NOX_Y(C)))
    + SUM(C, SUM(IAGKN(IA,G)$ICA(C,IA),  SUM((IS3,T), IHOURSINST(IS3,T) * (GDATA(G,'GDNOX')*IOF0000001)* IOF3P6 * VGFN_T(IA,G,IS3,T)) * ITAX_NOX_Y(C)))

* Fuel taxes

    + SUM((C,FFF,IS3,T), SUM(IAGK_Y(IA,G)$((GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))  AND ICA(C,IA)),
         IHOURSINST(IS3,T) * TAX_F(FFF,C) * IOF3P6 * VGF_T(IA,G,IS3,T)))

    + SUM((C,FFF,IS3,T), SUM(IAGKN(IA,G)$((GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM')) AND ICA(C,IA)),
         IHOURSINST(IS3,T) * TAX_F(FFF,C) * IOF3P6 * VGFN_T(IA,G,IS3,T)))

* More fuel taxes on technology types.

   + SUM((IA,G,IS3,T)$(IAGK_Y(IA,G) and ITAX_GF(IA,G)),
      ITAX_GF(IA,G)*IHOURSINST(IS3,T)  * IOF3P6 * VGF_T(IA,G,IS3,T))

   + SUM((IA,G,IS3,T)$(IAGKN(IA,G) and ITAX_GF(IA,G)),
      ITAX_GF(IA,G)*IHOURSINST(IS3,T)  * IOF3P6 * VGFN_T(IA,G,IS3,T))

* Electricity generation taxes (and subsidies).
   + SUM((IA,IGNOTETOH(IGE),IS3,T)$(IAGK_Y(IA,IGE) and ITAX_GE(IA,IGE)),
      ITAX_GE(IA,IGE)*IHOURSINST(IS3,T)  * VGE_T(IA,IGE,IS3,T))

   + SUM((IA,IGNOTETOH(IGE),IS3,T)$(IAGKN(IA,IGE) and ITAX_GE(IA,IGE)),
      ITAX_GE(IA,IGE)*IHOURSINST(IS3,T)  * VGEN_T(IA,IGE,IS3,T))

* Heat generation taxes.

   + SUM((IA,IGH,IS3,T)$(IAGK_Y(IA,IGH) and ITAX_GH(IA,IGH)),
      ITAX_GH(IA,IGH)*IOF3P6*VGH_T(IA,IGH,IS3,T)*IHOURSINST(IS3,T))

   + SUM((IA,IGH,IS3,T)$(IAGKN(IA,IGH) and ITAX_GH(IA,IGH)),
      ITAX_GH(IA,IGH)*IOF3P6*VGHN_T(IA,IGH,IS3,T)*IHOURSINST(IS3,T))


/*
* Changes in consumers' utility relative to electricity consumption:

   + SUM(IR,
     SUM((IS3,T), IHOURSINST(IS3,T)
     * (SUM(DEF_D1, VDEF_T(IR,IS3,T,DEF_D1)* IDEFP_T(IR,IS3,T,DEF_D1)  )
     +  SUM(DEF_D2, VDEF_T(IR,IS3,T,DEF_D2)* IDEFP_T(IR,IS3,T,DEF_D2)  )
     +  SUM(DEF_D3, VDEF_T(IR,IS3,T,DEF_D3)* IDEFP_T(IR,IS3,T,DEF_D3)  )))
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
     +  SUM(DHF_U2, VDHF_T(IA,IS3,T,DHF_U2)* IDHFP_T(IA,IS3,T,DHF_U2)  )
     +  SUM(DHF_U3, VDHF_T(IA,IS3,T,DHF_U3)* IDHFP_T(IA,IS3,T,DHF_U3)  )))
     )
*/

* Infeasibility penalties:
   + PENALTYQ*(
$ifi %BB1%==yes    +SUM((IA,IS3)$SUM(IGHYRS,IAGK_Y(IA,IGHYRS)),(VQHYRSSEQ(IA,IS3,'IMINUS')+VQHYRSSEQ(IA,IS3,'IPLUS')))
$ifi %BB2%==yes    +SUM((IA,IS3)$SUM(IGHYRS,IAGK_Y(IA,IGHYRS)),(VQHYRSSEQ(IA,IS3,'IMINUS')+VQHYRSSEQ(IA,IS3,'IPLUS')))
$ifi %BB1%==yes    +SUM((IA,IS3)$SUM(IGHYRS,IAGK_Y(IA,IGHYRS)),(VQHYRSMINMAXVOL(IA,IS3,'IMINUS')+VQHYRSMINMAXVOL(IA,IS3,'IPLUS')))
$ifi %BB2%==yes    +SUM((IA,IS3)$SUM(IGHYRS,IAGK_Y(IA,IGHYRS)),(VQHYRSMINMAXVOL(IA,IS3,'IMINUS')+VQHYRSMINMAXVOL(IA,IS3,'IPLUS')))
               +SUM((IA,IS3,T)$SUM(IGHSTO(G),  IAGK_Y(IA,IGHSTO)  OR IAGKN(IA,IGHSTO)), (VQHSTOVOLT(IA,IS3,T,'IMINUS') +VQHSTOVOLT(IA,IS3,T,'IPLUS')))
               +SUM((IA,IS3,T)$SUM(IGESTO(G),  IAGK_Y(IA,IGESTO)  OR IAGKN(IA,IGESTO)), (VQESTOVOLT(IA,IS3,T,'IMINUS') +VQESTOVOLT(IA,IS3,T,'IPLUS')))
               +SUM((IA,IS3,T)$SUM(IGHSTOS(G), IAGK_Y(IA,IGHSTOS) OR IAGKN(IA,IGHSTOS)),(VQHSTOVOLTS(IA,IS3,T,'IMINUS')+VQHSTOVOLTS(IA,IS3,T,'IPLUS')))
               +SUM((IA,IS3,T)$SUM(IGESTOS(G), IAGK_Y(IA,IGESTOS) OR IAGKN(IA,IGESTOS)),(VQESTOVOLTS(IA,IS3,T,'IMINUS')+VQESTOVOLTS(IA,IS3,T,'IPLUS')))

               +SUM((IR,IS3,T)$(SUM(DEUSER, IDE_SUMST(IR,DEUSER))), (VQEEQ(IR,IS3,T,'IMINUS')+VQEEQ(IR,IS3,T,'IPLUS')))
               +SUM((IA,IS3,T)$(SUM(DHUSER, IDH_SUMST(IA,DHUSER))), (VQHEQ(IA,IS3,T,'IMINUS')+VQHEQ(IA,IS3,T,'IPLUS')))

               +SUM((C,FFF)$IGEQF_Y(C,FFF) , VQGEQCF(C,FFF,'IPLUS')+VQGEQCF(C,FFF,'IMINUS')    )

               +SUM((C,FFF)$IGMINF_Y(C,FFF), VQGMINCF(C,FFF)      )
               +SUM((C,FFF)$IGMAXF_Y(C,FFF), VQGMAXCF(C,FFF)      )

               +SUM((IR,FFF)$IGEQF_Y(IR,FFF) , VQGEQRF(IR,FFF,'IPLUS')+VQGEQRF(IR,FFF,'IMINUS') )
               +SUM((IR,FFF)$IGMINF_Y(IR,FFF), VQGMAXRF(IR,FFF)    )
               +SUM((IR,FFF)$IGMAXF_Y(IR,FFF), VQGMINRF(IR,FFF)    )

               +SUM((IA,FFF)$IGEQF_Y(IA,FFF) , VQGEQAF(IA,FFF,'IPLUS')+VQGEQAF(IA,FFF,'IMINUS') )
               +SUM((IA,FFF)$IGMINF_Y(IA,FFF), VQGMAXAF(IA,FFF)    )
               +SUM((IA,FFF)$IGMAXF_Y(IA,FFF), VQGMINAF(IA,FFF)    )

               +SUM((IRE,IRI,IS3,T)$((IXKINI_Y(IRE,IRI) OR IXKN(IRI,IRE) OR IXKN(IRE,IRI)) AND (IXKINI_Y(IRE,IRI) NE INF) ), VQXK(IRE,IRI,IS3,T,'IPLUS')+VQXK(IRE,IRI,IS3,T,'IMINUS') )
              )

* Add-on objective function contributions
$INCLUDE '../../base/addons/_hooks/qobj.inc';

$ifi %X3V%==yes $include '../../base/addons/x3v/model/x3vobj.inc';
* This file contains Heat transmission induced additions to the objective function.
$ifi %HEATTRANS%==yes $include '../../base/addons/heattrans/model/htcosts.inc';
* This file contains district heating induced additions to the objective function.
$ifi %FV%==yes $include '../../base/addons/fjernvarme/cost_fv.inc';
* Unit commitmen add-on
$ifi %UnitComm%==yes    $include '../../base/addons/unitcommitment/uc_qobjadd.inc';

$ifi %POLICIES%==yes    $include '../../base/addons/policies/pol_cost.inc';
$ifi %SYSTEMCOST%==yes  $include '../../base/addons/SystemCost/cost_syscost.inc';
$ifi %UnitComm%==yes    $include '../../base/addons/unitcommitment/uc_qobjadd.inc';
$ifi %BB3%==yes  $ifi %HYRSBB123%==price      $include  '../../base/addons/hyrsbb123/hyrsbb123addobj.inc'
$ifi %BB3%==yes  $ifi %HYRSBB123%==quantprice $include  '../../base/addons/hyrsbb123/hyrsbb123addobj.inc'

)
;
*----- End: The objective function QOBJ ----------------------------------------


*--------------------------Balance equations for electricity and heat ----------

QEEQ(IR,IS3,T) ..

      SUM(IAGK_Y(IA,IGE)$((RRRAAA(IR,IA)) AND IGNOTETOH(IGE)), VGE_T(IA,IGE,IS3,T))
    - SUM(IAGK_Y(IA,IGE)$((RRRAAA(IR,IA)) AND IGETOH(IGE)), VGE_T(IA,IGE,IS3,T))
    + SUM(IAGKN(IA,IGE)$((RRRAAA(IR,IA)) AND IGNOTETOH(IGE)), VGEN_T(IA,IGE,IS3,T))
    - SUM(IAGKN(IA,IGE)$((RRRAAA(IR,IA)) AND IGETOH(IGE)), VGEN_T(IA,IGE,IS3,T))
    + SUM(IRE$(IXKINI_Y(IRE,IR) OR IXKN(IRE,IR) OR IXKN(IR,IRE)), VX_T(IRE,IR,IS3,T)*(1-XLOSS(IRE,IR)))
*    - SUM(IA$(RRRAAA(IR,IA) AND SUM(IGESTO,IAGK_Y(IA,IGESTO))),VESTOLOADT(IA,IS3,T))
*    - SUM(IA$(RRRAAA(IR,IA) AND SUM(IGESTOS,IAGK_Y(IA,IGESTOS))),VESTOLOADTS(IA,IS3,T))
    - SUM(IA$(RRRAAA(IR,IA) AND SUM(IGESTO$(IAGK_Y(IA,IGESTO) OR IAGKN(IA,IGESTO)),1)),VESTOLOADT(IA,IS3,T))
    - SUM(IA$(RRRAAA(IR,IA) AND SUM(IGESTOS$(IAGK_Y(IA,IGESTOS) OR IAGKN(IA,IGESTOS)),1)),VESTOLOADTS(IA,IS3,T))
$ifi %X3V%==yes + SUM(X3VPLACE$X3VX(IR,X3VPLACE),SUM(X3VSTEP,VX3VIM_T(IR,X3VPLACE,X3VSTEP,IS3,T)))
    =E=
      IX3FX_T_Y(IR,IS3,T)
    + (   (IDE_T_Y(IR,IS3,T)

*         + SUM(DEF_U1$IDEFP_T(IR,IS3,T,DEF_U1),VDEF_T(IR,IS3,T,DEF_U1) )
*         - SUM(DEF_D1$IDEFP_T(IR,IS3,T,DEF_D1),VDEF_T(IR,IS3,T,DEF_D1) )
*         + SUM(DEF_U2$IDEFP_T(IR,IS3,T,DEF_U2),VDEF_T(IR,IS3,T,DEF_U2) )
*         - SUM(DEF_D2$IDEFP_T(IR,IS3,T,DEF_D2),VDEF_T(IR,IS3,T,DEF_D2) )
*         + SUM(DEF_U3$IDEFP_T(IR,IS3,T,DEF_U3),VDEF_T(IR,IS3,T,DEF_U3) )
*         - SUM(DEF_D3$IDEFP_T(IR,IS3,T,DEF_D3),VDEF_T(IR,IS3,T,DEF_D3) )
     )/(1-DISLOSS_E(IR)))
      + SUM(IRI$(IXKINI_Y(IR,IRI) OR IXKN(IR,IRI) OR IXKN(IRI,IR)),VX_T(IR,IRI,IS3,T))
$ifi %X3V%==yes + SUM(X3VPLACE$X3VX(IR,X3VPLACE),SUM(X3VSTEP,VX3VEX_T(IR,X3VPLACE,X3VSTEP,IS3,T)))
$include "../../base/addons/_hooks/qeeq.inc"
      - VQEEQ(IR,IS3,T,'IMINUS') + VQEEQ(IR,IS3,T,'IPLUS')
;


QHEQ(IA,IS3,T)$(SUM(DHUSER, IDH_SUMST(IA,DHUSER)))..

     SUM(IGBPR$IAGK_Y(IA,IGBPR),VGH_T(IA,IGBPR,IS3,T))
   + SUM(IGBPR$IAGKN(IA,IGBPR),VGHN_T(IA,IGBPR,IS3,T))
   + SUM(IGEXT$IAGK_Y(IA,IGEXT),VGH_T(IA,IGEXT,IS3,T))
   + SUM(IGEXT$IAGKN(IA,IGEXT),VGHN_T(IA,IGEXT,IS3,T))
   + SUM(IGHH$IAGK_Y(IA,IGHH),VGH_T(IA,IGHH,IS3,T))
   + SUM(IGHH$IAGKN(IA,IGHH),VGHN_T(IA,IGHH,IS3,T))
   + SUM(IGETOH$IAGK_Y(IA,IGETOH),VGH_T(IA,IGETOH,IS3,T))
   + SUM(IGETOH$IAGKN(IA,IGETOH),VGHN_T(IA,IGETOH,IS3,T))
   + SUM(IGESTO$IAGK_Y(IA,IGESTO),(VGE_T(IA,IGESTO,IS3,T)/GDATA(IGESTO,'GDCB'))$GDATA(IGESTO,'GDCB'))  /* This may disappear, or stay plus similar for IGESTOs */
   - VHSTOLOADT(IA,IS3,T)$SUM(IGHSTO$(IAGK_Y(IA,IGHSTO) OR IAGKN(IA,IGHSTO)),1)
   - VHSTOLOADTS(IA,IS3,T)$SUM(IGHSTOS$(IAGK_Y(IA,IGHSTOS) OR IAGKN(IA,IGHSTOS)),1)
    =E=
     (IDH_T_Y(IA,IS3,T)
*        + SUM(DHF_U1$IDHFP_T(IA,IS3,T,DHF_U1),VDHF_T(IA,IS3,T,DHF_U1) )
*        - SUM(DHF_D1$IDHFP_T(IA,IS3,T,DHF_D1),VDHF_T(IA,IS3,T,DHF_D1) )
*        + SUM(DHF_U2$IDHFP_T(IA,IS3,T,DHF_U2),VDHF_T(IA,IS3,T,DHF_U2) )
*        - SUM(DHF_D2$IDHFP_T(IA,IS3,T,DHF_D2),VDHF_T(IA,IS3,T,DHF_D2) )
*        + SUM(DHF_U3$IDHFP_T(IA,IS3,T,DHF_U3),VDHF_T(IA,IS3,T,DHF_U3) )
*        - SUM(DHF_D3$IDHFP_T(IA,IS3,T,DHF_D3),VDHF_T(IA,IS3,T,DHF_D3) )
    )/(1-DISLOSS_H(IA))

* Adds heat transmission if selected in the gas add-on
$ifi %HEATTRANS%==yes $include '../../base/addons/heattrans/model/htheatbalance.inc';
$include "../../base/addons/_hooks/qheq.inc"
        - VQHEQ(IA,IS3,T,'IMINUS') + VQHEQ(IA,IS3,T,'IPLUS')
* Adds district heating if selected
$ifi %FV%==yes $include '../../base/addons/fjernvarme/heatbalance_fv.inc';
;

* Fuel consumption rate.
QGFEQ(IA,G,IS3,T)$IAGK_Y(IA,G) ..
    VGF_T(IA,G,IS3,T)
  =E=
   ( (VGE_T(IA,G,IS3,T)/(GDATA(G,'GDFE')*(1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G))))$(IGNOTETOH(G) AND IGE(G))
    +(GDATA(G,'GDCV')*VGH_T(IA,G,IS3,T)/(GDATA(G,'GDFE')*(1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G))))$IGH(G)
    )$(NOT IGBYPASS(G))

+  ( ((GDATA(G,'GDCB')*((VGH_T(IA,G,IS3,T)*GDATA(G,'GDBYPASSC') + VGE_T(IA,G,IS3,T))/(GDATA(G,'GDCB') + GDATA(G,'GDBYPASSC')))/(GDATA(G,'GDFE')*(1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G)))))
   +((GDATA(G,'GDCV')*((VGH_T(IA,G,IS3,T)*GDATA(G,'GDBYPASSC') + VGE_T(IA,G,IS3,T))/(GDATA(G,'GDCB') + GDATA(G,'GDBYPASSC')))/(GDATA(G,'GDFE')*(1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G)))))
   )$IGBYPASS(G)
$ifi %UnitComm%==yes $include '../../base/addons/unitcommitment/uc_qgfeqadd.inc';
;

* Fuel consumption rate calculated on new units.
QGFNEQ(IA,G,IS3,T)$IAGKN(IA,G) ..
    VGFN_T(IA,G,IS3,T)
  =E=
   ( (VGEN_T(IA,G,IS3,T)/(GDATA(G,'GDFE')*(1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G))))$(IGNOTETOH(G) AND IGE(G))
    +(GDATA(G,'GDCV')*VGHN_T(IA,G,IS3,T)/(GDATA(G,'GDFE')*(1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G))))$IGH(G)
    )$(NOT IGBYPASS(G))

+  ( ((GDATA(G,'GDCB')*((VGHN_T(IA,G,IS3,T)*GDATA(G,'GDBYPASSC') + VGEN_T(IA,G,IS3,T))/(GDATA(G,'GDCB') + GDATA(G,'GDBYPASSC')))/(GDATA(G,'GDFE')*(1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G)))))
   +((GDATA(G,'GDCV')*((VGHN_T(IA,G,IS3,T)*GDATA(G,'GDBYPASSC') + VGEN_T(IA,G,IS3,T))/(GDATA(G,'GDCB') + GDATA(G,'GDBYPASSC')))/(GDATA(G,'GDFE')*(1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G)))))
   )$IGBYPASS(G)
$ifi %UnitComm%==yes $include '../../base/addons/unitcommitment/uc_qgfeqadd.inc';
;


*------ Generation technologies' electricity/heat operating area: --------------

* Back pressure units:

QGCBGBPR(IAGK_Y(IA,IGBPR),IS3,T)$(NOT IGBYPASS(IGBPR)) ..
   VGE_T(IA,IGBPR,IS3,T) =E= VGH_T(IA,IGBPR,IS3,T) * GDATA(IGBPR,'GDCB');

QGNCBGBPR(IAGKN(IA,IGBPR),IS3,T)$(NOT IGBYPASS(IGBPR)) ..
    VGEN_T(IA,IGBPR,IS3,T) =E= VGHN_T(IA,IGBPR,IS3,T) * GDATA(IGBPR,'GDCB');

QGCBGBPRBYPASS1(IAGK_Y(IA,IGBPR),IS3,T)$IGBYPASS(IGBPR) ..
  VGE_T(IA,IGBPR,IS3,T) =L= VGH_T(IA,IGBPR,IS3,T) * GDATA(IGBPR,'GDCB');

QGNCBGBPRBYPASS1(IAGKN(IA,IGBPR),IS3,T)$IGBYPASS(IGBPR) ..
   VGEN_T(IA,IGBPR,IS3,T) =L= VGHN_T(IA,IGBPR,IS3,T) * GDATA(IGBPR,'GDCB');

QGCBGBPRBYPASS2(IAGK_Y(IA,IGBPR),IS3,T)$IGBYPASS(IGBPR)..
  VGE_T(IA,IGBPR,IS3,T) =L=
   (1+(GDATA(IGBPR,'GDBYPASSC')/GDATA(IGBPR,'GDCB')))*(IGKVACCTOY(IA,IGBPR)+IGKFX_Y(IA,IGBPR))*
   (1$(NOT GEFFRATE(IA,IGBPR))+GEFFRATE(IA,IGBPR)) - VGH_T(IA,IGBPR,IS3,T) * GDATA(IGBPR,'GDBYPASSC');

QGNCBGBPRBYPASS2(IAGKN(IA,IGBPR),IS3,T)$IGBYPASS(IGBPR)..
  VGEN_T(IA,IGBPR,IS3,T) =L=
   (1+(GDATA(IGBPR,'GDBYPASSC')/GDATA(IGBPR,'GDCB')))*(VGKN(IA,IGBPR))*
   (1$(NOT GEFFRATE(IA,IGBPR))+GEFFRATE(IA,IGBPR)) - VGHN_T(IA,IGBPR,IS3,T) * GDATA(IGBPR,'GDBYPASSC');


* Extraction units:

QGCBGEXT(IAGK_Y(IA,IGEXT),IS3,T) ..
   VGE_T(IA,IGEXT,IS3,T) =G= VGH_T(IA,IGEXT,IS3,T) * GDATA(IGEXT,'GDCB');



QGCVGEXT(IAGK_Y(IA,IGEXT),IS3,T)..                                                  !! combtech
          (IGKVACCTOY(IA,IGEXT)+IGKFX_Y(IA,IGEXT))*(1$(NOT IGKRATE(IA,IGEXT,IS3,T)) + IGKRATE(IA,IGEXT,IS3,T))
         - VGH_T(IA,IGEXT,IS3,T) * GDATA(IGEXT,'GDCV')
    =G=
   VGE_T(IA,IGEXT,IS3,T)
;

QGNCBGEXT(IAGKN(IA,IGEXT),IS3,T) ..
   VGEN_T(IA,IGEXT,IS3,T) =G= VGHN_T(IA,IGEXT,IS3,T) * GDATA(IGEXT,'GDCB') ;



QGNCVGEXT(IAGKN(IA,IGEXT),IS3,T)..
   VGKN(IA,IGEXT)*(1$(NOT IGKRATE(IA,IGEXT,IS3,T)) + IGKRATE(IA,IGEXT,IS3,T))
-  VGHN_T(IA,IGEXT,IS3,T) * GDATA(IGEXT,'GDCV')
    =G=
   VGEN_T(IA,IGEXT,IS3,T)
;
* Electric heat pumps:

QGGETOH(IAGK_Y(IA,IGETOH),IS3,T) ..
       VGE_T(IA,IGETOH,IS3,T) =E= VGH_T(IA,IGETOH,IS3,T) / GDATA(IGETOH,'GDFE');

QGNGETOH(IAGKN(IA,IGETOH),IS3,T) ..
       VGEN_T(IA,IGETOH,IS3,T) =E= VGHN_T(IA,IGETOH,IS3,T) / GDATA(IGETOH,'GDFE');



*--------- Dispatchable generation technologies' operating area: ---------------

* Generation on new capacity is constrained by the capacity,

QGEKNT(IAGKN(IA,IGKE),IS3,T)$IGDISPATCH(IGKE)..
  VGKN(IA,IGKE)*(1$(NOT IGKRATE(IA,IGKE,IS3,T))+IGKRATE(IA,IGKE,IS3,T))/(1$(NOT IGESTOALL(IGKE))+GDATA(IGKE,'GDSTOHUNLD')$IGESTOALL(IGKE))
    =G=
  VGEN_T(IA,IGKE,IS3,T)
;


* Note: does not presently include COMBTECH.
QGHKNT(IAGKN(IA,IGKH),IS3,T)$IGDISPATCH(IGKH)..
  VGKN(IA,IGKH)*(1$(NOT IGKRATE(IA,IGKH,IS3,T))+IGKRATE(IA,IGKH,IS3,T))/(1$(NOT IGHSTOALL(IGKH)) + GDATA(IGKH,'GDSTOHUNLD')$IGHSTOALL(IGKH))
     =G=
  VGHN_T(IA,IGKH,IS3,T)
;


$ifi %PLANTCLOSURES%==yes QGEKOT(IAGK_Y(IA,IGDISPATCH(IGE)),IS3,T) ..
$ifi %PLANTCLOSURES%==yes  (IGKFX_Y(IA,IGDISPATCH) + IGKVACCTOY(IA,IGDISPATCH)-VDECOM(IA,IGDISPATCH))*(1$(NOT IGKRATE(IA,IGDISPATCH,IS3,T))+IGKRATE(IA,IGDISPATCH,IS3,T))
$ifi %PLANTCLOSURES%==yes     =G=
$ifi %PLANTCLOSURES%==yes  VGE_T(IA,IGDISPATCH,IS3,T)
$ifi %PLANTCLOSURES%==yes ;

* Rev. 3.01: missing GSOLH, to be added.
$ifi %PLANTCLOSURES%==yes QGHKOT(IAGK_Y(IA,IGKH),IS3,T) ..
$ifi %PLANTCLOSURES%==yes  (IGKFX_Y(IA,IGKH) + IGKVACCTOY(IA,IGKH)-VDECOM(IA,IGKH))*(1$(NOT IGKRATE(IA,IGKH,IS3,T))+IGKRATE(IA,IGKH,IS3,T))
$ifi %PLANTCLOSURES%==yes     =G=
$ifi %PLANTCLOSURES%==yes  VGH_T(IA,IGKH,IS3,T)
$ifi %PLANTCLOSURES%==yes ;


*-------------- New hydro run-of-river: cannot be dispatched: ------------------


QGKNHYRR(IAGKN(IA,IGHYRR),IS3,T)$IWTRRRSUM(IA)..
 WTRRRFLH(IA) * VGKN(IAGKN) * WTRRRVAR_T(IA,IS3,T) / IWTRRRSUM(IA)
   =E=
   VGEN_T(IA,IGHYRR,IS3,T)

$ifi %PLANTCLOSURES%==yes QGKOHYRR(IAGK_Y(IA,IGHYRR),IS3,T)..
$ifi %PLANTCLOSURES%==yes  WTRRRFLH(IA) * (IGKFX_Y(IA,IGHYRR) + IGKVACCTOY(IA,IGHYRR)-VDECOM(IA,IGHYRR)) * WTRRRVAR_T(IA,IS3,T) / IWTRRRSUM(IA)
$ifi %PLANTCLOSURES%==yes    =E=
$ifi %PLANTCLOSURES%==yes  VGE_T(IA,IGHYRR,IS3,T)
;


*-------------- New windpower: cannot be dispatched: ---------------------------


QGKNWND(IAGKN(IA,IGWND),IS3,T)$IWND_SUMST(IA)..
$ifi %WNDFLH_DOL%==AAA        WNDFLH(IA)       * VGKN(IA,IGWND) * WND_VAR_T(IA,IS3,T) / IWND_SUMST(IA)
$ifi %WNDFLH_DOL%==AAA_GGG    WNDFLH(IA,IGWND) * VGKN(IA,IGWND) * WND_VAR_T(IA,IS3,T) / IWND_SUMST(IA)
$ifi     %WNDSHUTDOWN%==yes =G=
$ifi not %WNDSHUTDOWN%==yes =E=
  VGEN_T(IA,IGWND,IS3,T);

$ifi %PLANTCLOSURES%==yes  QGKOWND(IAGK_Y(IA,IGWND),IS3,T)$IWND_SUMST(IA)..
$ifi %PLANTCLOSURES%==yes  $ifi %WNDFLH_DOL%==AAA WNDFLH(IA)
$ifi %PLANTCLOSURES%==yes  $ifi %WNDFLH_DOL%==AAA_GGG WNDFLH(IA,IGWND)
$ifi %PLANTCLOSURES%==yes  * (IGKFX_Y(IA,IGWND) + IGKVACCTOY(IA,IGWND)-VDECOM(IA,IGWND)) * WND_VAR_T(IA,IS3,T) / IWND_SUMST(IA)
$ifi %PLANTCLOSURES%==yes    =G=
$ifi %PLANTCLOSURES%==yes   VGE_T(IA,IGWND,IS3,T);


*-------------- New solar power and heat: cannot be dispatched: ----------------
QGKNSOLE(IAGKN(IA,IGSOLE),IS3,T)$ISOLESUMST(IA)..
$ifi %SOLEFLH_DOL%==AAA                SOLEFLH(IA)        * VGKN(IA,IGSOLE) * SOLE_VAR_T(IA,IS3,T) / ISOLESUMST(IA)
$ifi %SOLEFLH_DOL%==AAA_GGG            SOLEFLH(IA,IGSOLE) * VGKN(IA,IGSOLE) * SOLE_VAR_T(IA,IS3,T) / ISOLESUMST(IA)
 =E=
VGEN_T(IA,IGSOLE,IS3,T);


QGKNSOLH(IAGKN(IA,IGSOLH),IS3,T)$ISOLHSUMST(IA)..
$ifi %SOLHFLH_DOL%==AAA               SOLHFLH(IA) * VGKN(IA,IGSOLH) * SOLH_VAR_T(IA,IS3,T) / ISOLHSUMST(IA)
$ifi %SOLHFLH_DOL%==AAA_GGG           SOLHFLH(IA,IGSOLH) * VGKN(IA,IGSOLH) * SOLH_VAR_T(IA,IS3,T) / ISOLHSUMST(IA)
 =E=
VGHN_T(IA,IGSOLH,IS3,T);


$ifi %PLANTCLOSURES%==yes QGKOSOLE(IAGK_Y(IA,IGSOLE),IS3,T)..
$ifi %PLANTCLOSURES%==yes $ifi %SOLEFLH_DOL%==AAA     SOLEFLH(IA)
$ifi %PLANTCLOSURES%==yes $ifi %SOLEFLH_DOL%==AAA_GGG SOLEFLH(IA,IGSOLE)
$ifi %PLANTCLOSURES%==yes * (IGKFX_Y(IA,IGSOLE) + IGKVACCTOY(IA,IGSOLE)-VDECOM(IA,IGSOLE)) * SOLE_VAR_T(IA,IS3,T) / ISOLESUMST(IA)
$ifi %PLANTCLOSURES%==yes  =E=
$ifi %PLANTCLOSURES%==yes VGE_T(IA,IGSOLE,IS3,T);

*-------------- New wave power: cannot be dispatched: -------------------------

QGKNWAVE(IAGKN(IA,IGWAVE),IS3,T)..
$ifi %GWAVE_DOL%==AAA        WAVEFLH(IA) * VGKN(IAGKN) * WAVE_VAR_T(IA,IS3,T) / IWAVESUMST(IA)
$ifi %GWAVE_DOL%==AAA_GGG    WAVEFLH(IA,IGWAVE) * VGKN(IAGKN) * WAVE_VAR_T(IA,IS3,T) / IWAVESUMST(IA)
 =E=
VGEN_T(IAGKN,IS3,T);

$ifi %PLANTCLOSURES%==yes QGKOWAVE(IAGK_Y(IA,IGWAVE),IS3,T)..
$ifi %PLANTCLOSURES%==yes $ifi %GWAVE_DOL%==AAA WAVEFLH(IA)
$ifi %PLANTCLOSURES%==yes $ifi %GWAVE_DOL%==AAA_GGG WAVEFLH(IA,IGWAVE)
$ifi %PLANTCLOSURES%==yes  * (IGKFX_Y(IA,IGWAVE) + IGKVACCTOY(IA,IGWAVE)-VDECOM(IA,IGWAVE)) * WAVE_VAR_T(IA,IS3,T) / IWAVESUMST(IA)
$ifi %PLANTCLOSURES%==yes  =E=
$ifi %PLANTCLOSURES%==yes VGE_T(IA,IGWAVE,IS3,T);



*-------------- Hydropower with reservoirs: ------------------------------------
*
* Hydro reservoir content - dynamic seasonal equation:

QHYRSSEQ(IA,S)$SUM(IGHYRS,IAGK_Y(IA,IGHYRS) or IAGKN(IA,IGHYRS))..
      VHYRS_S(IA,S)
      + SUM(IGHYRS$IAGK_Y(IA,IGHYRS),
        IHYINF_S(IA,S) * (IGKVACCTOY(IA,IGHYRS)+IGKFX_Y(IA,IGHYRS))
        -SUM(T,IHOURSINST(S,T)*(VGE_T(IA,IGHYRS,S,T))))
      + SUM(IGHYRS$IAGKN(IA,IGHYRS),
        IHYINF_S(IA,S) * VGKN(IA,IGHYRS)
        -SUM(T,IHOURSINST(S,T)*(VGEN_T(IA,IGHYRS,S,T))))

      - VQHYRSSEQ(IA,S,'IMINUS') + VQHYRSSEQ(IA,S,'IPLUS')

      =G=  VHYRS_S(IA,S++1);

* Regulated and unregulated hydropower production lower than capacity:

QHYMAXG(IA,IS3,T)$SUM(IGHYRS,IAGK_Y(IA,IGHYRS))..
      SUM(IGHYRS$IAGK_Y(IA,IGHYRS),VGE_T(IA,IGHYRS,IS3,T))
      + SUM(IGHYRS$IAGKN(IA,IGHYRS),VGEN_T(IA,IGHYRS,IS3,T))
      + SUM(IGHYRR$IAGK_Y(IA,IGHYRR),VGE_T(IA,IGHYRR,IS3,T))
      + SUM(IGHYRR$IAGKN(IA,IGHYRR),VGEN_T(IA,IGHYRR,IS3,T))
      =L=
        SUM(IGHYRS$IAGK_Y(IA,IGHYRS),(IGKVACCTOY(IA,IGHYRS)+IGKFX_Y(IA,IGHYRS))*(1$(NOT IGKRATE(IA,IGHYRS,IS3,T))+IGKRATE(IA,IGHYRS,IS3,T)))
      + SUM(IGHYRS$IAGKN(IA,IGHYRS),VGKN(IA,IGHYRS))
      ;

* Hydro storage within limits:

QHYRSMINVOL(IA,IS3)$(HYRSDATA(IA,'HYRSMINVOL',IS3) AND SUM(IGHYRS$(IAGK_Y(IA,IGHYRS) OR IAGKN(IA,IGHYRS)),1))..

      VHYRS_S(IA,IS3) =G= HYRSDATA(IA,'HYRSMINVOL',IS3)  *
        (SUM(IGHYRS,HYRSMAXVOL_G(IA,IGHYRS)*(IGKVACCTOY(IA,IGHYRS)+IGKFX_Y(IA,IGHYRS)+VGKN(IA,IGHYRS)$IAGKN(IA,IGHYRS)))
        -VQHYRSMINMAXVOL(IA,IS3,'IMINUS'));

* Hydro reservoir content - maximum level

QHYRSMAXVOL(IA,IS3)$(HYRSDATA(IA,'HYRSMAXVOL',IS3) AND SUM(IGHYRS$(IAGK_Y(IA,IGHYRS) OR IAGKN(IA,IGHYRS)),1))..

       HYRSDATA(IA,'HYRSMAXVOL',IS3)  *
        (SUM(IGHYRS, HYRSMAXVOL_G(IA,IGHYRS)*(IGKVACCTOY(IA,IGHYRS)+IGKFX_Y(IA,IGHYRS)  +VGKN(IA,IGHYRS)$IAGKN(IA,IGHYRS)))
        -VQHYRSMINMAXVOL(IA,IS3,'IPLUS'))=G= VHYRS_S(IA,IS3);

*------------ Short term heat and electricity storages:-------------------------

QESTOVOLT(IA,IS3,T)$SUM(IGESTO, IAGK_Y(IA,IGESTO)+IAGKN(IA,IGESTO))..
    VESTOVOLT(IA,IS3,T++1) =E= VESTOVOLT(IA,IS3,T)
  + CHRONOHOUR(IS3,T)*
  ( VESTOLOADT(IA,IS3,T)
  - SUM(IGESTO$IAGK_Y(IA,IGESTO), VGE_T(IA,IGESTO,IS3,T)/GDATA(IGESTO,'GDFE'))
  - SUM(IGESTO$IAGKN(IA,IGESTO),VGEN_T(IA,IGESTO,IS3,T)/GDATA(IGESTO,'GDFE'))
  )
  - VQESTOVOLT(IA,IS3,T,'IPLUS') + VQESTOVOLT(IA,IS3,T,'IMINUS')
;

QESTOVOLTS(IA,S,T)$(SUM(IGESTOS, IAGK_Y(IA,IGESTOS)+IAGKN(IA,IGESTOS)))..
    VESTOVOLTS(IA,S,T)
  + CHRONOHOUR(S,T)*
  (VESTOLOADTS(IA,S,T)
  - SUM(IGESTOS$IAGK_Y(IA,IGESTOS), VGE_T(IA,IGESTOS,S,T)/GDATA(IGESTOS,'GDFE'))
  - SUM(IGESTOS$IAGKN(IA,IGESTOS), VGEN_T(IA,IGESTOS,S,T)/GDATA(IGESTOS,'GDFE'))
  )
    =E=       VESTOVOLTS(IA,S,T+1)+SUM(ITALIAS$(ORD(ITALIAS) EQ 1),VESTOVOLTS(IA,S++1,ITALIAS)$(ORD(T) EQ CARD(T)))
   - VQESTOVOLTS(IA,S,T,'IPLUS') + VQESTOVOLTS(IA,S,T,'IMINUS')
;

QHSTOVOLT(IA,IS3,T)$(SUM(IGHSTO, IAGK_Y(IA,IGHSTO)+IAGKN(IA,IGHSTO)))..
    VHSTOVOLT(IA,IS3,T)
  + CHRONOHOUR(IS3,T)*
  (VHSTOLOADT(IA,IS3,T)
  - SUM(IGHSTO$IAGK_Y(IA,IGHSTO), VGH_T(IA,IGHSTO,IS3,T)/GDATA(IGHSTO,'GDFE'))
  - SUM(IGHSTO$IAGKN(IA,IGHSTO), VGHN_T(IA,IGHSTO,IS3,T)/GDATA(IGHSTO,'GDFE'))
  )
    =E=       VHSTOVOLT(IA,IS3,T++1)
  - VQHSTOVOLT(IA,IS3,T,'IPLUS') + VQHSTOVOLT(IA,IS3,T,'IMINUS')
;


QHSTOVOLTS(IA,S,T)$(SUM(IGHSTOS, IAGK_Y(IA,IGHSTOS)+IAGKN(IA,IGHSTOS)))..
    VHSTOVOLTS(IA,S,T)
  + CHRONOHOUR(S,T)*
  (VHSTOLOADTS(IA,S,T)
  - SUM(IGHSTOS$IAGK_Y(IA,IGHSTOS), VGH_T(IA,IGHSTOS,S,T)/GDATA(IGHSTOS,'GDFE'))
  - SUM(IGHSTOS$IAGKN(IA,IGHSTOS), VGHN_T(IA,IGHSTOS,S,T)/GDATA(IGHSTOS,'GDFE'))
  )
    =E=       VHSTOVOLTS(IA,S,T+1)+SUM(ITALIAS$(ORD(ITALIAS) EQ 1),VHSTOVOLTS(IA,S++1,ITALIAS)$(ORD(T) EQ CARD(T)))
   - VQHSTOVOLTS(IA,S,T,'IPLUS') + VQHSTOVOLTS(IA,S,T,'IMINUS')
;

* The following constraints limit when investments in storage facilities are allowed.
* They pertain only to BB2 and to areas with an option to invest in storage facilities.
* Simple bounds cover all other situations.

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

QHSTOLOADTLIMS(IA,IS3,T)$SUM(IGHSTOS,IAGKN(IA,IGHSTOS)) ..
* Existing or accumulated capacity
   SUM(IGHSTOS$IAGK_Y(IA,IGHSTOS),  (IGKFX_Y(IA,IGHSTOS)+IGKVACCTOY(IA,IGHSTOS))/GDATA(IGHSTOS,'GDSTOHLOAD')
   )
* New investments
   +SUM(IGHSTOS$IAGKN(IA,IGHSTOS),   VGKN(IA,IGHSTOS)/GDATA(IGHSTOS,'GDSTOHLOAD')
   )
         =G=
   VHSTOLOADTS(IA,IS3,T)
;

QESTOLOADTLIM(IA,IS3,T)$SUM(IGESTO,IAGKN(IA,IGESTO)) ..
* Existing or accumulated capacity
   SUM(IGESTO$IAGK_Y(IA,IGESTO),  (IGKFX_Y(IA,IGESTO)+IGKVACCTOY(IA,IGESTO))/GDATA(IGESTO,'GDSTOHLOAD')
   )
* New investments
   +SUM(IGESTO$IAGKN(IA,IGESTO),  VGKN(IA,IGESTO)/GDATA(IGESTO,'GDSTOHLOAD'))
         =G=
   VESTOLOADT(IA,IS3,T)
;

QESTOLOADTLIMS(IA,IS3,T)$SUM(IGESTOS,IAGKN(IA,IGESTOS)) ..
* Existing or accumulated capacity
   SUM(IGESTOS$IAGK_Y(IA,IGESTOS),  (IGKFX_Y(IA,IGESTOS)+IGKVACCTOY(IA,IGESTOS))/GDATA(IGESTOS,'GDSTOHLOAD')
   )
* New investments
   +SUM(IGESTOS$IAGKN(IA,IGESTOS),  VGKN(IA,IGESTOS)/GDATA(IGESTOS,'GDSTOHLOAD'))
         =G=
   VESTOLOADTS(IA,IS3,T)
;

* Storage contents does not exceed upper limit (MWh):
QHSTOVOLTLIM(IA,IS3,T)$SUM(IGHSTO,IAGKN(IA,IGHSTO)) ..
* Existing or accumulated capacity
  SUM(IGHSTO$IAGK_Y(IA,IGHSTO),   IGKFX_Y(IA,IGHSTO)+IGKVACCTOY(IA,IGHSTO))
* New investments
  +SUM(IGHSTO$IAGKN(IA,IGHSTO),   VGKN(IA,IGHSTO)
   )
         =G=
  VHSTOVOLT(IA,IS3,T)
;

QHSTOVOLTLIMS(IA,IS3,T)$SUM(IGHSTOS,IAGKN(IA,IGHSTOS)) ..
* Existing or accumulated capacity
  SUM(IGHSTOS$IAGK_Y(IA,IGHSTOS),   IGKFX_Y(IA,IGHSTOS)+IGKVACCTOY(IA,IGHSTOS))
* New investments
  +SUM(IGHSTOS$IAGKN(IA,IGHSTOS),   VGKN(IA,IGHSTOS)
   )
         =G=
  VHSTOVOLTS(IA,IS3,T)
;

QESTOVOLTLIM(IA,IS3,T)$SUM(IGESTO,IAGKN(IA,IGESTO)) ..
* Existing or accumulated capacity
  SUM(IGESTO$IAGK_Y(IA,IGESTO),   IGKFX_Y(IA,IGESTO)+IGKVACCTOY(IA,IGESTO))
* New investments
  +SUM(IGESTO$IAGKN(IA,IGESTO),   VGKN(IA,IGESTO)
   )
         =G=
  VESTOVOLT(IA,IS3,T)
;

QESTOVOLTLIMS(IA,IS3,T)$SUM(IGESTOS,IAGKN(IA,IGESTOS)) ..
* Existing or accumulated capacity
  SUM(IGESTOS$IAGK_Y(IA,IGESTOS),   IGKFX_Y(IA,IGESTOS)+IGKVACCTOY(IA,IGESTOS))
* New investments
  +SUM(IGESTOS$IAGKN(IA,IGESTOS),   VGKN(IA,IGESTOS)
   )
         =G=
  VESTOVOLTS(IA,IS3,T)
;

*---------- Maximal installable capacity per fuel type is restricted (MW): ----

QKFUELC(C,FFF)$FKPOT(C,FFF)..
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
      + SUM(IAGK_Y(IA,G)$IGF(G,FFF),  IGKFXYMAX(IA,G))
      + SUM(IAGKN(IA,G)$IGF(G,FFF),   VGKN(IA,G))
        =L=  FKPOT(IA,FFF);

* Electricity generation constraints by fuel (in energy), country
QFGEMINC(C,FFF)$FGEMIN(C,FFF)..
     SUM((IA,IS3,T)$ICA(C,IA), SUM(IGNOTETOH(IGE)$(IGF(IGE,FFF) AND IAGK_Y(IA,IGE)),  IHOURSINST(IS3,T) * VGE_T(IA,IGE,IS3,T)))
   + SUM((IA,IS3,T)$ICA(C,IA), SUM(IGNOTETOH(IGE)$(IGF(IGE,FFF) AND IAGKN(IA,IGE)),   IHOURSINST(IS3,T) * VGEN_T(IA,IGE,IS3,T)))
     =G= FGEMIN(C,FFF);

QFGEMAXC(C,FFF)$FGEMAX(C,FFF)..
    FGEMAX(C,FFF)
     =G=
     SUM((IA,IS3,T)$ICA(C,IA), SUM(IGNOTETOH(IGE)$(IGF(IGE,FFF) AND IAGK_Y(IA,IGE)),   IHOURSINST(IS3,T) * VGE_T(IA,IGE,IS3,T)))
   + SUM((IA,IS3,T)$ICA(C,IA), SUM(IGNOTETOH(IGE)$(IGF(IGE,FFF) AND IAGKN(IA,IGE)),    IHOURSINST(IS3,T) * VGEN_T(IA,IGE,IS3,T)))
;
* Electricity generation constraints by fuel (in energy), region
QFGEMINR(IR,FFF)$FGEMIN(IR,FFF)..
     SUM((IA,IS3,T)$RRRAAA(IR,IA), SUM(IGNOTETOH(IGE)$(IGF(IGE,FFF) AND IAGK_Y(IA,IGE)),  IHOURSINST(IS3,T) * VGE_T(IA,IGE,IS3,T)))
   + SUM((IA,IS3,T)$RRRAAA(IR,IA), SUM(IGNOTETOH(IGE)$(IGF(IGE,FFF) AND IAGKN(IA,IGE)),   IHOURSINST(IS3,T) * VGEN_T(IA,IGE,IS3,T)))
     =G= FGEMIN(IR,FFF);

QFGEMAXR(IR,FFF)$FGEMAX(IR,FFF)..
    FGEMAX(IR,FFF)
     =G=
     SUM((IA,IS3,T)$RRRAAA(IR,IA), SUM(IGNOTETOH(IGE)$(IGF(IGE,FFF) AND IAGK_Y(IA,IGE)),  IHOURSINST(IS3,T) * VGE_T(IA,IGE,IS3,T)))
   + SUM((IA,IS3,T)$RRRAAA(IR,IA), SUM(IGNOTETOH(IGE)$(IGF(IGE,FFF) AND IAGKN(IA,IGE)),   IHOURSINST(IS3,T) * VGEN_T(IA,IGE,IS3,T)))
;

* Electricity generation constraints by fuel (in energy), area
QFGEMINA(IA,FFF)$FGEMIN(IA,FFF)..
     SUM((IS3,T), SUM(IGNOTETOH(IGE)$(IGF(IGE,FFF) AND IAGK_Y(IA,IGE)),  IHOURSINST(IS3,T) * VGE_T(IA,IGE,IS3,T)))
   + SUM((IS3,T), SUM(IGNOTETOH(IGE)$(IGF(IGE,FFF) AND IAGKN(IA,IGE)),   IHOURSINST(IS3,T) * VGEN_T(IA,IGE,IS3,T)))
     =G= FGEMIN(IA,FFF);

QFGEMAXA(IA,FFF)$FGEMAX(IA,FFF)..
    FGEMAX(IA,FFF)
     =G=
     SUM((IS3,T), SUM(IGNOTETOH(IGE)$(IGF(IGE,FFF) AND IAGK_Y(IA,IGE)),   IHOURSINST(IS3,T) * VGE_T(IA,IGE,IS3,T)))
   + SUM((IS3,T), SUM(IGNOTETOH(IGE)$(IGF(IGE,FFF) AND IAGKN(IA,IGE)),    IHOURSINST(IS3,T) * VGEN_T(IA,IGE,IS3,T)))
;

* Fuel use constraints (in energy), area

QGMINAF(IA,FFF)$IGMINF_Y(IA,FFF)..
     SUM(G$(IAGK_Y(IA,G) AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGF_T(IA,G,IS3,T)))
    +SUM(G$(IAGKN(IA,G)  AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGFN_T(IA,G,IS3,T)))
    + VQGMINAF(IA,FFF)
    =G= IGMINF_Y(IA,FFF);

QGMAXAF(IA,FFF)$IGMAXF_Y(IA,FFF)..
    IGMAXF_Y(IA,FFF)
    + VQGMAXAF(IA,FFF)
         =G=
     SUM(G$(IAGK_Y(IA,G) AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGF_T(IA,G,IS3,T)))
    +SUM(G$(IAGKN(IA,G)  AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGFN_T(IA,G,IS3,T)))
;


QGEQAF(IA,FFF)$IGEQF_Y(IA,FFF)..
    IGEQF_Y(IA,FFF)
    + VQGEQAF(IA,FFF,'IPLUS') - VQGEQAF(IA,FFF,'IMINUS')
   =E=
     SUM(G$(IAGK_Y(IA,G) AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGF_T(IA,G,IS3,T)))
    +SUM(G$(IAGKN(IA,G)  AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGFN_T(IA,G,IS3,T)))
   ;


*QGEQAF_S(IA,FFF,IS3)$IGEQF_Y_S(IA,FFF,IS3)..
*    IGEQF_Y_S(IA,FFF,IS3)
*     =L=
*     SUM(G$(IAGK_Y(IA,G) AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * SUM(T, IHOURSINST(IS3,T) * VGF_T(IA,G,IS3,T)))
*    +SUM(G$(IAGKN(IA,G)  AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * SUM(T, IHOURSINST(IS3,T) * VGFN_T(IA,G,IS3,T)))
*   ;

* Fuel use constraints (in energy), region

QGMINRF(IR,FFF)$IGMINF_Y(IR,FFF)..
    SUM(IA$RRRAAA(IR,IA),
     SUM(G$(IAGK_Y(IA,G) AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGF_T(IA,G,IS3,T)))
    +SUM(G$(IAGKN(IA,G)  AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGFN_T(IA,G,IS3,T)))
    )
    + VQGMINRF(IR,FFF)
    =G= IGMINF_Y(IR,FFF);

QGMAXRF(IR,FFF)$IGMAXF_Y(IR,FFF)..
    IGMAXF_Y(IR,FFF)
    + VQGMAXRF(IR,FFF)
         =G=
    SUM(IA$RRRAAA(IR,IA),
     SUM(G$(IAGK_Y(IA,G) AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGF_T(IA,G,IS3,T)))
    +SUM(G$(IAGKN(IA,G)  AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGFN_T(IA,G,IS3,T)))
    );


QGEQRF(IR,FFF)$IGEQF_Y(IR,FFF)..
    IGEQF_Y(IR,FFF)
    + VQGEQRF(IR,FFF,'IPLUS') - VQGEQRF(IR,FFF,'IMINUS')
   =E=
    SUM(IA$RRRAAA(IR,IA),
    SUM(G$(IAGK_Y(IA,G) AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGF_T(IA,G,IS3,T)))
    +SUM(G$(IAGKN(IA,G)  AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGFN_T(IA,G,IS3,T)))
    );

*QGEQRF_S(IR,FFF,IS3)$IGEQF_Y_S(IR,FFF,IS3)..
*    IGEQF_Y_S(IR,FFF,IS3)
*   =L=
*    SUM(IA$RRRAAA(IR,IA),
*    SUM(G$(IAGK_Y(IA,G) AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * SUM(T, IHOURSINST(IS3,T) * VGF_T(IA,G,IS3,T)))
*    +SUM(G$(IAGKN(IA,G)  AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * SUM(T, IHOURSINST(IS3,T) * VGFN_T(IA,G,IS3,T)))
*    );

* Fuel use constraints (in energy), country

QGMINCF(C,FFF)$IGMINF_Y(C,FFF)..
    SUM(IA$ICA(C,IA),
     SUM(G$(IAGK_Y(IA,G) AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGF_T(IA,G,IS3,T)))
    +SUM(G$(IAGKN(IA,G)  AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGFN_T(IA,G,IS3,T)))
    )
    + VQGMINCF(C,FFF)
    =G= IGMINF_Y(C,FFF);

QGMAXCF(C,FFF)$IGMAXF_Y(C,FFF)..
    IGMAXF_Y(C,FFF)
    + VQGMAXCF(C,FFF)
         =G=
    SUM(IA$ICA(C,IA),
     SUM(G$(IAGK_Y(IA,G) AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGF_T(IA,G,IS3,T)))
    +SUM(G$(IAGKN(IA,G)  AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGFN_T(IA,G,IS3,T)))
    );


QGEQCF(C,FFF)$IGEQF_Y(C,FFF)..
    IGEQF_Y(C,FFF)
    + VQGEQCF(C,FFF,'IPLUS') - VQGEQCF(C,FFF,'IMINUS')
   =E=
    SUM(IA$ICA(C,IA),
     SUM(G$(IAGK_Y(IA,G) AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGF_T(IA,G,IS3,T)))
    +SUM(G$(IAGKN(IA,G)  AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) * VGFN_T(IA,G,IS3,T)))
    );

*QGEQCF_S(C,FFF,IS3)$IGEQF_Y_S(C,FFF,IS3)..
*    IGEQF_Y_S(C,FFF,IS3)
*   =L=
*    SUM(IA$ICA(C,IA),
*     SUM(G$(IAGK_Y(IA,G) AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * SUM(T, IHOURSINST(IS3,T) * VGF_T(IA,G,IS3,T)))
*    +SUM(G$(IAGKN(IA,G)  AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * SUM(T, IHOURSINST(IS3,T) * VGFN_T(IA,G,IS3,T)))
*    );


*----------- Transmission (MW):------------------------------------------------

* Electricity transmission is limited by transmission capacity:

QXK(IRE,IRI,IS3,T)$((IXKINI_Y(IRE,IRI) OR IXKN(IRI,IRE) OR IXKN(IRE,IRI)) AND (IXKINI_Y(IRE,IRI) NE INF) )..
      (1$(NOT IXKRATE(IRE,IRI,IS3,T))+IXKRATE(IRE,IRI,IS3,T))*(
       IXKINI_Y(IRE,IRI)+IXKVACCTOY(IRE,IRI)
     + VXKN(IRE,IRI)$(IXKN(IRE,IRI) OR IXKN(IRI,IRE))+ VXKN(IRI,IRE)$(IXKN(IRE,IRI) OR IXKN(IRI,IRE))
     )
     + VQXK(IRE,IRI,IS3,T,'IPLUS')-VQXK(IRE,IRI,IS3,T,'IMINUS')
     =G=  VX_T(IRE,IRI,IS3,T);


QXMAXINV(IRE,IRI)$((IXKN(IRE,IRI) OR IXKN(IRI,IRE)) AND XMAXINV(IRE,IRI))..
         XMAXINV(IRE,IRI)
=G=
         VXKN(IRE,IRI);

*------------ Emissions: ------------------------------------------------------

QLIMCO2(C)$(ILIM_CO2_Y(C) AND (ILIM_CO2_Y(C) LT INF))..

      SUM(IAGK_Y(IA,G)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_CO2(G) * IOF0001) * IOF3P6 * VGF_T(IA,G,IS3,T)))
    + SUM(IAGKN(IA,G)$ICA(C,IA),  SUM((IS3,T), IHOURSINST(IS3,T) * (IM_CO2(G) * IOF0001) * IOF3P6 * VGFN_T(IA,G,IS3,T)))

      =L= ILIM_CO2_Y(C) ;


QLIMSO2(C)$(ILIM_SO2_Y(C) AND (ILIM_SO2_Y(C) LT INF))..

      SUM(IAGK_Y(IA,G)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_SO2(G) * IOF0001) * IOF3P6 * VGF_T(IA,G,IS3,T)))
    + SUM(IAGKN(IA,G)$ICA(C,IA),  SUM((IS3,T), IHOURSINST(IS3,T) * (IM_SO2(G) * IOF0001) * IOF3P6 * VGFN_T(IA,G,IS3,T)))

      =L= ILIM_SO2_Y(C) ;


QLIMNOX(C)$(ILIM_NOX_Y(C) AND (ILIM_NOX_Y(C) LT INF))..

      SUM(IAGK_Y(IA,G)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (GDATA(G,'GDNOX') * IOF0000001) * IOF3P6 * VGF_T(IA,G,IS3,T)))
    + SUM(IAGKN(IA,G)$ICA(C,IA),  SUM((IS3,T), IHOURSINST(IS3,T) * (GDATA(G,'GDNOX') * IOF0000001) * IOF3P6 * VGFN_T(IA,G,IS3,T)))

      =L= ILIM_NOX_Y(C) ;



QFMAXINVEST(C,FFF)$(FMAXINVEST(C,FFF) > 0) ..
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

*------ End equations used only in Balbase3 ------------------------------------


*-------------------------------------------------------------------------------
*----- Any equations for addon to be placed here: ------------------------------
*-------------------------------------------------------------------------------

$include "../../base/addons/_hooks/eqndecdef.inc"

* These add-on equations pertain to district heating.
$ifi %FV%==yes $include '../../base/addons/fjernvarme/eq_fv.inc';


* These add-on equations pertain to price sensitive electricity exchange with
* third countries.
$ifi %X3V%==yes $include '../../base/addons/x3v/model/x3veq.inc';


* These add-on equations pertain to heat transmission.
$ifi %HEATTRANS%==yes $include '../../base/addons/heattrans/model/htequations.inc';

$ifi %REShareE%==yes $include  '../../base/addons/REShareE/RESEeqns.inc';
$ifi %REShareEH%==yes $include '../../base/addons/REShareEH/RESEHeqns.inc';
$ifi %AGKNDISC%==yes  $include  '../../base/addons/AGKNDISC/AGKNDISCequations.inc';
$ifi %POLICIES%==yes  $include '../../base/addons/policies/pol_eq.inc';
$ifi %SYSTEMCOST%==yes  $include '../../base/addons/SystemCost/eq_syscost.inc';
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
                                QGFEQ
*--- Feasible generation region ------------------------------------------------
                                QGCBGBPR
                                QGCBGEXT
                                QGCVGEXT
                                QGGETOH
                                QGCBGBPRBYPASS1
                                QGCBGBPRBYPASS2
                                QGNCBGBPRBYPASS1
                                QGNCBGBPRBYPASS2
*--- Storage restrictions ------------------------------------------------------
                                QHYRSSEQ
                                QHYRSMINVOL
                                QHYRSMAXVOL
                                QESTOVOLT
                                QESTOVOLTS
                                QHSTOVOLT
                                QHSTOVOLTS
*--- Transmission capacity -----------------------------------------------------
                                QXK
*--- Electricity generation restrictions by fuel -------------------------------
                                QFGEMINC
                                QFGEMAXC
                                QFGEMINR
                                QFGEMAXR
                                QFGEMINA
                                QFGEMAXA
*--- Fuel consumption restrictions ---------------------------------------------
                                QGMINCF
                                QGMAXCF
                                QGEQCF
*                               QGEQCF_S
                                QGMINRF
                                QGMAXRF
                                QGEQRF
*                               QGEQRF_S
                                QGMINAF
                                QGMAXAF
                                QGEQAF
*                               QGEQAF_S
*--- Emissions restrictions ----------------------------------------------------
                                QLIMCO2
                                QLIMSO2
                                QLIMNOX

*--- Operational restrictions --------------------------------------------------

*                                QSELFSUFFICIENCY
*----- Any equations for addon to be placed here: ------------------------------
$include "../../base/addons/_hooks/balbase1.inc"
* Eventually the following addons will be handled through the above inclusion of _hooks.inc
$ifi %FV%==yes $include '../../base/addons/fjernvarme/eqN_fv.inc';
$ifi %X3VfxQ%==yes              QX3VBAL
$ifi %HEATTRANS%==yes $include '../../base/addons/heattrans/model/htbb1.inc';
$ifi %UnitComm%==yes      $include '../../base/addons/unitcommitment/uc_modeladd.inc';
$ifi %POLICIES%==yes $include '../../base/addons/policies/pol_eqn.inc';
$ifi %REShareE%==yes QRESHAREE
$ifi %SYSTEMCOST%==yes $include '../../base/addons/SystemCost/eqn_syscost.inc';

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
                                QGFEQ
                                QGFNEQ
*--- Feasible generation region ------------------------------------------------
                                QGCBGBPR
                                QGCBGEXT
                                QGCVGEXT
                                QGGETOH
                                QGNCBGBPR
                                QGNCBGEXT
                                QGNCVGEXT
                                QGNGETOH
                                QGCBGBPRBYPASS1
                                QGCBGBPRBYPASS2
*--- Generation capacities -----------------------------------------------------
                                QGEKNT
                                QGHKNT
                                QGKNWND
                                QGKNHYRR
                                QGKNSOLE
                                QGKNSOLH
                                QGKNWAVE
*--- Storage restrictions ------------------------------------------------------
                                QHYRSSEQ
                                QHYRSMINVOL
                                QHYRSMAXVOL
                                QESTOVOLT
                                QESTOVOLTS
                                QHSTOVOLT
                                QHSTOVOLTS
                                QHSTOLOADTLIM
                                QHSTOLOADTLIMS
                                QESTOLOADTLIM
                                QESTOLOADTLIMS
                                QHSTOVOLTLIM
                                QHSTOVOLTLIMS
                                QESTOVOLTLIM
                                QESTOVOLTLIMS
*--- Transmission capacity -----------------------------------------------------
                                QXK
*--- Fuel capacity restrictions ------------------------------------------------
                                QKFUELC
                                QKFUELR
                                QKFUELA

*--- Electricity generation restrictions by fuel -------------------------------
                                QFGEMINC
                                QFGEMAXC
                                QFGEMINR
                                QFGEMAXR
                                QFGEMINA
                                QFGEMAXA
*--- Fuel consumption restrictions ---------------------------------------------
                                QGMINCF
                                QGMAXCF
                                QGEQCF
*                               QGEQCF_S
                                QGMINRF
                                QGMAXRF
                                QGEQRF
*                               QGEQRF_S
                                QGMINAF
                                QGMAXAF
                                QGEQAF
*                               QGEQAF_S
*--- Emissions restrictions ----------------------------------------------------
                                QLIMCO2
                                QLIMSO2
                                QLIMNOX
*--- Operational restrictions --------------------------------------------------
*                               QSELFSUFFICIENCY
*----- Any equations for addon to be placed here: ------------------------------
$include "../../base/addons/_hooks/balbase2.inc"
* Eventually the following addons will be handled through the above inclusion of _hooks.inc

*--- Capacity restrictions for decommissioning ----------------------------------
$ifi %PLANTCLOSURES%==yes           QGEKOT
$ifi %PLANTCLOSURES%==yes           QGHKOT
$ifi %PLANTCLOSURES%==yes           QGKOHYRR
$ifi %PLANTCLOSURES%==yes           QGKOWND
$ifi %PLANTCLOSURES%==yes           QGKOSOLE
$ifi %PLANTCLOSURES%==yes           QGKOWAVE
*--- Investment restricitions --------------------------------------------------
                                QXMAXINV

*----- Any equations for true addon to be placed here: -------------------------
$ifi %X3VfxQ%==yes              QX3VBAL
$ifi %HEATTRANS%==yes $include '../../base/addons/heattrans/model/htbb1.inc';
$ifi %UnitComm%==yes      $include '../../base/addons/unitcommitment/uc_modeladd.inc';
$ifi %REShareE%==yes QREShareE
$ifi %REShareEH%==yes QREShareEH

$ifi %AGKNDISC%==yes  QAGKNDISCCONT
$ifi %AGKNDISC%==yes  QAGKNDISC01
$ifi %POLICIES%==yes $include '../../base/addons/policies/pol_eqn.inc';
$ifi %SYSTEMCOST%==yes $include '../../base/addons/SystemCost/eqn_syscost.inc';
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
                                QGFEQ
                                QGFNEQ
*--- Feasible generation region ------------------------------------------------
                                QGCBGBPR
                                QGCBGEXT
                                QGCVGEXT
                                QGGETOH
                                QGCBGBPRBYPASS1
                                QGCBGBPRBYPASS2
*--- Storage bounds, hydro -----------------------------------------------------
                                QHYRSMINVOL
                                QHYRSMAXVOL
*--- Storage balance, intra-season only  ---------------------------------------
                                QESTOVOLT
                                QHSTOVOLT
*--- Transmission capacity -----------------------------------------------------
                                QXK
*----- Any equations for addon to be placed here: ------------------------------
$include "../../base/addons/_hooks/balbase3.inc"
* Eventually the following addons will be handled through the above inclusion of _hooks.inc

$ifi %HEATTRANS%==yes $include '../../base/addons/heattrans/model/htbb1.inc';
*----- End: Any equations for addon to be placed here. -------------------------
/;

* Scale the model: only equation QOBJ is really badly scaled:
BALBASE3.SCALEOPT=1;
QOBJ.SCALE=IOF1000000;



*-------------------------------------------------------------------------------
*----- Any further models to be defined here: ----------------------------------
*-------------------------------------------------------------------------------


*-------------------------------------------------------------------------------
*----- End: Any further models to be defined here: -----------------------------
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
*----- End of definition of models ---------------------------------------------
*-------------------------------------------------------------------------------


* The input data are subject to a certain control for 'reasonable' values.
* The errors are checked by the code in the files ERRORx.INC

$INCLUDE '../../base/logerror/logerinc/error2.inc';
$INCLUDE  '../../base/addons/_hooks/error2.inc';
* Eventually the following addons will be handled through the above inclusion of _hooks.inc

$ifi %POLICIES%==yes  $INCLUDE  '../../base/addons/policies/pol_err2.inc';

* The following file contains definitions of a number of temporary parameters
* and sets that may be used for printout of simulation results.
$ifi %PRINTFILES%==yes $INCLUDE '../../base/output/printout/printinc/print2.inc';


*-------------------------------------------------------------------------------
* Here the model to be solved/simulated is included:

BALBASE1.optfile = %USEOPTIONFILE%;
BALBASE2.optfile = %USEOPTIONFILE%;
BALBASE3.optfile = %USEOPTIONFILE%;

$ifi %bb1%==yes $if EXIST 'bb123.sim' $INCLUDE 'bb123.sim';
$ifi %bb1%==yes $if not EXIST 'bb123.sim' $INCLUDE '../../base/model/bb123.sim';

$ifi %bb2%==yes $if EXIST 'bb123.sim' $INCLUDE 'bb123.sim';
$ifi %bb2%==yes $if not EXIST 'bb123.sim' $INCLUDE '../../base/model/bb123.sim';

$ifi %bb3%==yes $if EXIST 'bb123.sim' $INCLUDE 'bb123.sim';
$ifi %bb3%==yes $if not EXIST 'bb123.sim' $INCLUDE '../../base/model/bb123.sim';


*--- Results which can be transfered between simulations are placed here: ------

$ifi %bb1%==yes execute_unload  '../../simex/HYRSG.gdx',HYRSG;
$ifi %bb1%==yes execute_unload  '../../simex/VHYRS_SL.gdx',VHYRS_SL;
$ifi %bb1%==yes execute_unload  '../../simex/WATERVAL.gdx',WATERVAL;

$ifi %bb2%==yes execute_unload  '../../simex/HYRSG.gdx',HYRSG;
$ifi %bb2%==yes execute_unload  '../../simex/VHYRS_SL.gdx',VHYRS_SL;
$ifi %bb2%==yes execute_unload  '../../simex/WATERVAL.gdx',WATERVAL;

$ifi  %bb3%==yes $ifi not %HYRSBB123%==none $include  "../../base/addons/hyrsbb123/hyrsbb123unload.inc";

$INCLUDE  '../../base/addons/_hooks/simex.inc';

$ifi %MAKEINVEST%==yes execute_unload '../../base/data/GKVACC.gdx', GKVACC;
$ifi %MAKEINVEST%==yes execute_unload '../../base/data/GKVACCDECOM.gdx', GKVACCDECOM;
$ifi %MAKEINVEST%==yes execute_unload '../../base/data/GVKGN.gdx', GVKGN;
$ifi %MAKEINVEST%==yes execute_unload '../../base/data/XKACC.gdx', XKACC;


$ifi %X3V%==yes $INCLUDE '../../base/addons/x3v/model/x3vgdx.inc';
*--- End: Results which can be transfered between simulations are placed here --

*----- End of model:------------------------------------------------------------
$include "../../base/addons/_hooks/endofmodel_pre.inc"
$label ENDOFMODEL
$include "../../base/addons/_hooks/endofmodel_post.inc"
*----- End of model ------------------------------------------------------------

$include "../../base/output/Open_MODEX_output.inc"

*--- Results collection for this case ------------------------------------------

$ifi not %system.filesys%==MSNT $goto endofMSNToutput
*The following section until $label endofMSNToutput is related to Windows output only
*Please use only backslash \ instead of forward slash / in this section until the label

$ifi %MERGESAVEPOINTRESULTS%==yes  execute 'gdxmerge "%relpathoutput%temp\*.gdx"';
$ifi %MERGESAVEPOINTRESULTS%==yes  execute 'move merged.gdx "%relpathoutput%%CASEID%.gdx"';

$ifi %MERGECASE%==NONE
$ifi %MERGESAVEPOINTRESULTS%==yes  execute 'gdxmerge "..\output\%CASEID%.gdx"';
$ifi %MERGECASE%==NONE
$ifi %MERGESAVEPOINTRESULTS%==yes  execute 'move merged.gdx "%relpathoutput%%CASEID%-results.gdx"'

$ifi %MERGECASE%==NONE
$ifi %MERGEDSAVEPOINTRESULTS2MDB%==yes execute '=gdx2access "%relpathoutput%%CASEID%-results.gdx"';
$ifi %MERGECASE%==NONE
$ifi %MERGEDSAVEPOINTRESULTS2SQLITE%==yes execute '=gdx2sqlite -i "%relpathoutput%%CASEID%-results.gdx" -o "%relpathoutput%%CASEID%-results.db"';

*--- Results collection and comparison for differents cases --------------------

$ifi not %MERGECASE%==NONE
$ifi %MERGESAVEPOINTRESULTS%==yes  execute 'gdxmerge "%relpathoutput%%CASEID%.gdx" "%relpathModel%..\..\%MERGEWITH%/output\%MERGEWITH%.gdx"';
$ifi not %MERGECASE%==NONE
$ifi %MERGESAVEPOINTRESULTS%==yes  execute 'move merged.gdx "%relpathoutput%%CASEID%-resmerged.gdx"';

$ifi not %MERGECASE%==NONE
$ifi %MERGEDSAVEPOINTRESULTS2MDB%==yes execute '=gdx2access "%relpathoutput%%CASEID%-resmerged.gdx"';
$ifi not %MERGECASE%==NONE
$ifi %MERGEDSAVEPOINTRESULTS2SQLITE%==yes execute '=gdx2sqlite -i "%relpathoutput%%CASEID%-resmerged.gdx" -o "%relpathoutput%%CASEID%-resmerged.db"';

$ifi not %DIFFCASE%==NONE
$ifi %MERGESAVEPOINTRESULTS%==yes  execute 'gdxdiff "%relpathoutput%%CASEID%-results.gdx" "%relpathModel%..\..\%DIFFWITH%/output/%DIFFWITH%-results.gdx"';
$ifi not %DIFFCASE%==NONE
$ifi %MERGESAVEPOINTRESULTS%==yes  execute 'move diffile.gdx "%relpathoutput%%CASEID%-diff.gdx"';

$label endofMSNToutput

$ifi not %system.filesys%==UNIX $goto endofUNIXoutput
*The following section until $label endofUNIXoutput is related to UNIX output only
*Please use only forward slash / instead of backslash \ in this section until the label

$ifi %MERGESAVEPOINTRESULTS%==yes  execute 'gdxmerge "../output/temp/*.gdx"';
$ifi %MERGESAVEPOINTRESULTS%==yes  execute 'mv ./merged.gdx ./"%relpathoutput%%CASEID%.gdx"';

$ifi %MERGECASE%==NONE
$ifi %MERGESAVEPOINTRESULTS%==yes  execute 'gdxmerge "../output/%CASEID%.gdx"';
$ifi %MERGECASE%==NONE
$ifi %MERGESAVEPOINTRESULTS%==yes  execute 'mv ./merged.gdx ./"%relpathoutput%%CASEID%-results.gdx"'

$ifi %MERGECASE%==NONE
$ifi %MERGEDSAVEPOINTRESULTS2MDB%==yes execute '=gdx2access ./"%relpathoutput%%CASEID%-results.gdx"';
$ifi %MERGECASE%==NONE
$ifi %MERGEDSAVEPOINTRESULTS2SQLITE%==yes execute '=gdx2sqlite -i ./"%relpathoutput%%CASEID%-results.gdx" -o ./"%relpathoutput%%CASEID%-results.db"';

*--- Results collection and comparison for differents cases --------------------

$ifi not %MERGECASE%==NONE
$ifi %MERGESAVEPOINTRESULTS%==yes  execute 'gdxmerge ./"%relpathoutput%%CASEID%.gdx" ./"%relpathModel%../../%MERGEWITH%/output/%MERGEWITH%.gdx"';
$ifi not %MERGECASE%==NONE
$ifi %MERGESAVEPOINTRESULTS%==yes  execute 'mv ./merged.gdx ./"%relpathoutput%%CASEID%-resmerged.gdx"';

$ifi not %MERGECASE%==NONE
$ifi %MERGEDSAVEPOINTRESULTS2MDB%==yes execute '=gdx2access ./"%relpathoutput%%CASEID%-resmerged.gdx"';
$ifi not %MERGECASE%==NONE
$ifi %MERGEDSAVEPOINTRESULTS2SQLITE%==yes execute '=gdx2sqlite -i ./"%relpathoutput%%CASEID%-resmerged.gdx" -o ./"%relpathoutput%%CASEID%-resmerged.db"';

$ifi not %DIFFCASE%==NONE
$ifi %MERGESAVEPOINTRESULTS%==yes  execute 'gdxdiff ./"%relpathoutput%%CASEID%-results.gdx" ./"%relpathModel%../../%DIFFWITH%/output/%DIFFWITH%-results.gdx"';
$ifi not %DIFFCASE%==NONE
$ifi %MERGESAVEPOINTRESULTS%==yes  execute 'mv ./diffile.gdx ./"%relpathoutput%%CASEID%-diff.gdx"';


$label endofUNIXoutput

*--- Main results calculation -----------------------------------------------
$ifi %OUTPUT_SUMMARY%==yes $if     EXIST '../../base/output/OUTPUT_SUMMARY.inc' $INCLUDE         '../../base/output/OUTPUT_SUMMARY.inc';
*--- End of Main results calculation ---------------------------------------

*----- End of file:------------------------------------------------------------
$label endoffile


