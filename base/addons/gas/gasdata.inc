* This file contains and references data required for running the Balmorel model
* with the GAS add-on.


SCALAR kNm3ToMWh /11/;

* If simulating with high geografical detail alternative values for district
* heating demand must be used.

*-------------------------------------------------------------------------------
* Include demand for district heating at MR geografical level.
*-------------------------------------------------------------------------------

$ifi %MR%==yes $INCLUDE '../../base/addons/gas/DH-MR.inc';

* Heat demand variation profile used:
$ifi %MR%==yes DH_VAR_T(MRAREAS(AAA),SSS,TTT)$DDDNODE('HNG',AAA)         = DH_VAR_T('DK_E_Urban',SSS,TTT);
$ifi %MR%==yes DH_VAR_T(MRAREAS(AAA),SSS,TTT)$DDDNODE('DONG_OEST',AAA)   = DH_VAR_T('DK_E_Rural',SSS,TTT);
$ifi %MR%==yes DH_VAR_T(MRAREAS(AAA),SSS,TTT)$DDDNODE('DONG_VEST',AAA)   = DH_VAR_T('DK_W_Rural',SSS,TTT);
$ifi %MR%==yes DH_VAR_T(MRAREAS(AAA),SSS,TTT)$DDDNODE('NGF',AAA)         = DH_VAR_T('DK_E_Urban',SSS,TTT);
$ifi %MR%==yes DH_VAR_T(MRAREAS(AAA),SSS,TTT)$DDDNODE('Midt_Nord',AAA)   = DH_VAR_T('DK_W_Urban',SSS,TTT);

*-------------------------------------------------------------------------------
* Swedish gas consumption which is not instigated by generation of district heating
* or electricity.
*-------------------------------------------------------------------------------

PARAMETER SE_DGRES(YYY,AAA,IMONTH)/
2004.SE_S_Rural.JAN 104764
2004.SE_S_Rural.FEB 123812
2004.SE_S_Rural.MAR 85716
2004.SE_S_Rural.APR 47620
2004.SE_S_Rural.MAY 28572
2004.SE_S_Rural.JUN 28572
2004.SE_S_Rural.JUL 19048
2004.SE_S_Rural.AUG 28572
2004.SE_S_Rural.SEP 28572
2004.SE_S_Rural.OCT 47620
2004.SE_S_Rural.NOV 76192
2004.SE_S_Rural.DEC 104764
/;

PARAMETER SE_DGOTH(YYY,AAA,IMONTH)/
2004.SE_S_Rural.JAN 514285
2004.SE_S_Rural.FEB 485713
2004.SE_S_Rural.MAR 495237
2004.SE_S_Rural.APR 409523
2004.SE_S_Rural.MAY 380952
2004.SE_S_Rural.JUN 371428
2004.SE_S_Rural.JUL 323809
2004.SE_S_Rural.AUG 371428
2004.SE_S_Rural.SEP 380952
2004.SE_S_Rural.OCT 409523
2004.SE_S_Rural.NOV 466666
2004.SE_S_Rural.DEC 523809
/;

SE_DGRES(Y,AAA,IMONTH)=SE_DGRES('2004',AAA,IMONTH) ;
SE_DGOTH(Y,AAA,IMONTH)=SE_DGOTH('2004',AAA,IMONTH) ;




PARAMETER
          DGRES(YYY,AAA)                          'Residual gasforbrug, årligt per område',
          DGOTH(YYY,AAA)                          'Gasforbrug andre timeaflæste, årligt per område'
          DGRES_VAR(AAA,SSS,TTT)                  'Residual gasforbrug, timevariation',
          DGOTH_VAR(AAA,SSS,TTT)                  'Gasforbrug andre timeaflæste, timevariation'
          DGRESF_STEPS(AAA,SSS,TTT,DF_QP,DGRESF)  'Elastic residual gas demands'
          DGOTHF_STEPS(AAA,SSS,TTT,DF_QP,DGOTHF)  'Elastic gas demands from "other" large consumers'
          SE_DGRES_VAR_T(AAA,SSS,TTT)             'Variation in Swedish residual consumption',
          SE_DGOTH_VAR_T(AAA,SSS,TTT)             'Variation in Swedish "other" large consumers demand'
          ISE_DGRES_SUMVAR(AAA,IMONTH)            'Residual gas consumption, weightsum over the variation'
          ISE_DGOTH_SUMVAR(AAA,IMONTH)            'Other large gas consumers, weightsum over the variation'
;






DGRES(YYY,'SE_S_Rural')= sum(IMONTH, SE_DGRES(YYY,'SE_S_Rural',IMONTH));
DGOTH(YYY,'SE_S_Rural')= sum(IMONTH, SE_DGOTH(YYY,'SE_S_Rural',IMONTH));

* Load variation profiles for gas consumption which is not instigated by generation of
* electricity or district heating.
$if %MR%==yes $INCLUDE '../../base/addons/gas/gasvar-MR.inc';
$if not %MR%==yes $INCLUDE '../../base/addons/gas/gasvar.inc';

* To help make the variation profiles for Swedish gas consumption we use the profiles from NGF since these are based on Danish national averages.
$if %MR%==yes ISE_DGRES_SUMVAR('SE_S_Rural',IMONTH) = sum((SSS,TTT)$MONTHSSS(IMONTH,SSS), DGRES_VAR('hoejby',SSS,TTT));
$if %MR%==yes ISE_DGOTH_SUMVAR('SE_S_Rural',IMONTH) = sum((SSS,TTT)$MONTHSSS(IMONTH,SSS), DGOTH_VAR('hoejby',SSS,TTT));
$if not %MR%==yes ISE_DGRES_SUMVAR('SE_S_Rural',IMONTH) = sum((SSS,TTT)$MONTHSSS(IMONTH,SSS), DGRES_VAR('DK_W_ODENSE',SSS,TTT));
$if not %MR%==yes ISE_DGOTH_SUMVAR('SE_S_Rural',IMONTH) = sum((SSS,TTT)$MONTHSSS(IMONTH,SSS), DGOTH_VAR('DK_W_ODENSE',SSS,TTT));

$if %MR%==yes DGRES_VAR('SE_S_Rural',SSS,TTT) = DGRES_VAR('hoejby',SSS,TTT)/SUM(IMONTH$MONTHSSS(IMONTH,SSS),ISE_DGRES_SUMVAR('SE_S_Rural',IMONTH))*SUM(IMONTH$MONTHSSS(IMONTH,SSS), SE_DGRES('2004','SE_S_Rural',IMONTH)/DGRES('2004','SE_S_Rural'));
$if %MR%==yes DGOTH_VAR('SE_S_Rural',SSS,TTT) = DGOTH_VAR('hoejby',SSS,TTT)/SUM(IMONTH$MONTHSSS(IMONTH,SSS),ISE_DGOTH_SUMVAR('SE_S_Rural',IMONTH))*SUM(IMONTH$MONTHSSS(IMONTH,SSS), SE_DGOTH('2004','SE_S_Rural',IMONTH)/DGOTH('2004','SE_S_Rural'));
$if not %MR%==yes DGRES_VAR('SE_S_Rural',SSS,TTT) = DGRES_VAR('DK_W_ODENSE',SSS,TTT)/SUM(IMONTH$MONTHSSS(IMONTH,SSS),ISE_DGRES_SUMVAR('SE_S_Rural',IMONTH))*SUM(IMONTH$MONTHSSS(IMONTH,SSS), SE_DGRES('2004','SE_S_Rural',IMONTH)/DGRES('2004','SE_S_Rural'));
$if not %MR%==yes DGOTH_VAR('SE_S_Rural',SSS,TTT) = DGOTH_VAR('DK_W_ODENSE',SSS,TTT)/SUM(IMONTH$MONTHSSS(IMONTH,SSS),ISE_DGOTH_SUMVAR('SE_S_Rural',IMONTH))*SUM(IMONTH$MONTHSSS(IMONTH,SSS), SE_DGOTH('2004','SE_S_Rural',IMONTH)/DGOTH('2004','SE_S_Rural'));


* Load annual values for gas consumption which is not instigated by generation of
* electricity or district heating.
$if not %MR%==yes $INCLUDE '../../base/addons/gas/dg.inc';
$if %MR%==yes $INCLUDE '../../base/addons/gas/dg-MR.inc';

PARAMETER
         SCONDATA(SCON,SCONDATASET)   'Storage contracts',
         TAU_INJ                      'Injection tarrif',
         TAU_EN_Y                     'Annual entry tarrif',
         TAU_EX_Y                     'Annual exit tarrif',
         TAU_EN_M(IMONTH)             'Monthly entry tarrif',
         TAU_EX_M(IMONTH)             'Monthly exit tarrif',
         TAU_EN_W(SSS)                'Weekly entry tarrif',
         TAU_EX_W(SSS)                'Weekly exit tarrif',
         TAU_EN_D(SSS,DAY)            'Daily entry tarrif',
         TAU_EX_D(SSS,DAY)            'Daily exit tarrif',
         TAU_VOL                      'Tranmission volume tarrif',
         TAU_DIST(DDD)                'Distribution tariff',
         TC_EN_Y(SYSENTRY,YYY)        'Yearly transmissions capacity reserved exogenously'
         TC_EX_Y(SYSEXIT,YYY)         'Yearly transmissions capacity reserved exogenously'
         TC_EN_M(SYSENTRY,YYY,SSS,TTT) 'Monthly transmissions capacity reserved exogenously'
         TC_EX_M(SYSEXIT,YYY,SSS,TTT)  'Monthly transmissions capacity reserved exogenously'
;
$ifi not EXIST 'gascontracts.inc' $INCLUDE '../../base/addons/gas/gascontracts.inc';
$ifi EXIST 'gascontracts.inc' $INCLUDE 'gascontracts.inc';
$ifi not EXIST 'gastransprices.inc' $INCLUDE '../../base/addons/gas/gastransprices.inc';
$ifi EXIST 'gastransprices.inc' $INCLUDE 'gastransprices.inc';
$ifi not EXIST 'gx3vex.inc' $INCLUDE '../../base/addons/gas/gx3vex.inc';
$ifi EXIST 'gx3vex.inc' $INCLUDE 'gx3vex.inc';


* In the base scenario, gasprices are adjusted to reflect price difference with continent, and
* cleaned of transportation expenses.
FUELPRICE(YYY,IA,'NAT_GAS')$((ICA('Denmark',IA) or ICA('Sweden',IA))
                                          and (not sameas('Nybro',IA))
                                           and (not sameas('Ellund',IA))
                                          and (not sameas('Oeresund',IA)))
                                          =0;


* Priser justeres i overenstemmelse med forudsætninger i gas-el rapport.
$ifi %LOWGAS%==yes FUELPRICE(Y,'Nybro','NAT_GAS')        = 1.5/0.25*0.343/1.398;
$ifi %LOWGAS%==yes FUELPRICE(Y,'Oeresund','NAT_GAS')     = 1.5/0.25*0.343/1.398;

$ifi %MEDGAS%==yes FUELPRICE(Y,'Nybro','NAT_GAS')        = FUELPRICE(Y,'Nybro','NAT_GAS')        -1.026/1.398;
$ifi %MEDGAS%==yes FUELPRICE(Y,'Oeresund','NAT_GAS')     = FUELPRICE(Y,'Oeresund','NAT_GAS')     -1.026/1.398;

$ifi %HIGHGAS%==yes FUELPRICE(Y,'Nybro','NAT_GAS')       = FUELPRICE(Y,'Nybro','NAT_GAS')        -0.418/1.398;
$ifi %HIGHGAS%==yes FUELPRICE(Y,'Oeresund','NAT_GAS')    = FUELPRICE(Y,'Oeresund','NAT_GAS')     -0.418/1.398;


PARAMETER GEXT_COST(YYY,SOURCE,S) 'Average Extraction Cost EURO/MWh',
          GEX_PRICE(YYY,SOURCE,S) 'Export Price Money/MWh';

GEXT_COST(YYY,'Nybro',S)         =FUELPRICE(YYY,'Nybro','NAT_GAS');
GEXT_COST(YYY,'Oeresund',S)      =FUELPRICE(YYY,'Oeresund','NAT_GAS');
GEX_PRICE(YYY,SOURCE,S)$(not SAMEAS(SOURCE,'Oeresund'))          =FUELPRICE(YYY,'Ellund','NAT_GAS')*WSF(S);




PARAMETER
         SUPPLY_MAX(YYY,SOURCE) 'Hourly exogenous natural gas supply capacity'
         EXP_MAX(YYY,SOURCE) 'Hourly exogenous natural gas export capacity'
         COST_NGINV(NGINV0) 'Investment costs'
         SUPEFFECT(NGINV0,SOURCE) 'Effect on supply capacity from investment'
         EXPEFFECT(NGINV0,SOURCE) 'Effect on export capacity from investment'
         INJ_MAX(YYY,STORE,STORETYPE) 'Injection capacity, exogenous'
         EXT_MAX(YYY,STORE,STORETYPE) 'Extraction capacity, exogenous'
         STORAGE_MAX(YYY,STORE,STORETYPE) 'Storage volumetric capacity, exogenous'
         GSTOREDATA(STORETYPE,*) 'Storage investment data'
         MAXINVEST(STORE,STORETYPE) 'Maximum possible capacity at storage location'
         TSOSTORAGE(YYY,STORE,STORETYPE)  'Storage reserved for emergencies by the TSO'
         ;

$ifi EXIST 'gasfacilities.inc' $INCLUDE 'gasfacilities.inc';
$ifi not EXIST 'gasfacilities.inc' $INCLUDE '../../base/addons/gas/gasfacilities.inc';

PARAMETER
        GSFXW(YYY,STORE,STORETYPE,SSS)    'Allokeret netto gasudtræk fra lager per uge'
        SC_Y(YYY,SCON)                    'Bestilte gaslagerprodukter'
        GPFXW(YYY,SOURCE,SSS)             'Allokering af gasproduktion'
        HYFXRW_GAS(YYY,SSS,RRR)           'Allokering af vandkraftmængder til uger'
        STOREACC(YYY,STORE,STORETYPE)     'Storage volumetric investment from bb2'
        INJACC(YYY,STORE,STORETYPE)       'Storage injection investment from bb2'
        EXTACC(YYY,STORE,STORETYPE)       'Storage extraction investment from bb2'
        EXPACC(YYY,SOURCE)                'Gas export capacity investment from bb2'
        SUPACC(YYY,SOURCE)                'Gas supply capacity investment from bb2'
        DEVACC(YYY,SYSEXIT)               'Gas delivery capacity investment from bb2'
;

* Load bb1/bb2 allocations to bb3 model
$ifi %bb3%==yes execute_load '../../base/addons/gas/GSFXW.gdx', GSFXW;
$ifi %bb3%==yes execute_load '../../base/addons/gas/reserved_capacity.gdx', TC_EN_Y,TC_EX_Y,TC_EN_M,TC_EX_M;
$ifi %bb3%==yes execute_load '../../base/addons/gas/SC_Y.gdx', SC_Y;

* Load investments undertaken in BB2 to BB1 or BB3 simulations.
$ifi %ADDINVEST%==yes execute_load '../../base/addons/gas/gasinvest.gdx',STOREACC,INJACC,EXTACC,EXPACC,SUPACC,DEVACC;

PARAMETER
          GASANNUITY / 0.117 /
         ;

* The following are currently unused functional representations of the cost
* elements of the objective function using gams-f. These are especially applicable
* in a MCP framework. Note that elements may not match that of the objective function
* in this model and therefore should be verified before use.

$ontext
* FUNCTIONS using gams-f
CTC_EN_YEAR == IOF0000001/7.43*TAU_EN_Y;
CTC_EX_Y == IOF0000001/7.43*TAU_EX_Y;
CTC_EN_M(IMONTH) == IOF0000001/7.43*TAU_EN_M(IMONTH)*MONTHSCALE(IMONTH);
CTC_EX_M(IMONTH) == IOF0000001/7.43*TAU_EX_M(IMONTH)*MONTHSCALE(IMONTH);
CTC_EN_W(IS3) == IOF0000001/7.43*TAU_EN_W(IS3);
CTC_EX_W(IS3) == IOF0000001/7.43*TAU_EX_W(IS3);
CTC_EN_D(IS3,DAY) == IOF0000001/7.43*TAU_EN_D(IS3,DAY);
CTC_EX_D(IS3,DAY) == IOF0000001/7.43*TAU_EX_D(IS3,DAY);
CSUP(SOURCE,IS3,T) == IOF0000001/7.43*IHOURSINST(IS3,T)*TAU_VOL;
CSC(SCON) == IOF0000001/7.43*SCONDATA(SCON,'TARRIF');
CINJ(STORE, IS3,T) ==  IOF0000001/7.43*IHOURSINST(IS3,T)*TAU_INJ;
CGUD(AAA,IS3,T) == IOF0000001/7.43*TAU_DIST(DDD);
CEXP(SOURCE,IS3,T) == -IOF0000001/7.43*IHOURSINST(IS3,T)*(IGEX_PRICE(SOURCE,IS3)-IFUELP_Y('Nybro','NAT_GAS'));
$offtext


* The following concerns a possible future endogenous implementation of gas
* transmissions constrains based on modelling physical flows.

$ifi %PIPELINE%==yes $INCLUDE '../../base/addons/gasprops.inc';
$ifi %PIPELINE%==yes $INCLUDE '../../base/addons/gastech.inc';
$ifi %PIPELINE%==yes $INCLUDE '../../base/addons/network.inc';
$ifi %PIPELINE%==yes $INCLUDE '../../base/addons/linearize.inc';