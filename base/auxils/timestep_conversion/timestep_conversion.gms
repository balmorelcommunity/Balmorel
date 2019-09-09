* CODE TO CALCULATE CONVERT THE TIMESTEP USED - JUAN GEA BERMUDEZ

*---------- DATA DEFINITION--------------------
*New time sets
SET SSS_NEW /S001*S364/;
SET TTT_NEW /T01*T24/;

ALIAS(SSS_NEW,ISSS_NEW);
ALIAS(TTT_NEW,ITTT_NEW);


SET CCCRRRAAA          "All geographical entities (CCC + RRR + AAA)" ;
$INCLUDE         '../../base/auxils/timestep_conversion/input/CCCRRRAAA.inc';


SET RRR(CCCRRRAAA)       "All regions" ;
$INCLUDE         '../../base/auxils/timestep_conversion/input/RRR.inc';


SET AAA(CCCRRRAAA)       "All areas";
$INCLUDE         '../../base/auxils/timestep_conversion/input/AAA.inc';


SET SSS                "All seasons"
$INCLUDE      '../../base/auxils/timestep_conversion/input/SSS.inc';


SET TTT                "All time periods" ;
$INCLUDE      '../../base/auxils/timestep_conversion/input/TTT.inc';

SET DEUSER             "Electricity demand user groups. Set must include element RESE for holding demand not included in any other user group" ;
$INCLUDE         '../../base/auxils/timestep_conversion/input/DEUSER.inc';


SET DHUSER             "Heat demand user groups. Set must include element RESH for holding demand not included in any other user group"  ;
$INCLUDE         '../../base/auxils/timestep_conversion/input/DHUSER.inc';


SET GGG          "All generation technologies"   ;
$INCLUDE      '../../base/auxils/timestep_conversion/input/GGG.inc';


SET G(GGG)    "Generation technologies in the simulation"  ;
$INCLUDE         '../../base/auxils/timestep_conversion/input/G.inc';


SET S(SSS)    "Seasons in the simulation"   ;
$INCLUDE      '../../base/auxils/timestep_conversion/input/S.inc';


SET T(TTT)    "Time periods within the season in the simulation"  ;
$INCLUDE         '../../base/auxils/timestep_conversion/input/T.inc';

SET HYRSDATASET  "Characteristics of hydro reservoirs" ;
$INCLUDE         '../../base/auxils/timestep_conversion/input/HYRSDATASET.inc';


*Original timeseries
PARAMETER WND_VAR_T(AAA,SSS,TTT)                   "Variation of the wind generation"    ;
execute_load  '../../base/auxils/timestep_conversion/input/all_endofmodel.gdx', WND_VAR_T;

PARAMETER SOLE_VAR_T(AAA,SSS,TTT)                  "Variation of the solarE generation"   ;
execute_load  '../../base/auxils/timestep_conversion/input/all_endofmodel.gdx', SOLE_VAR_T;

PARAMETER SOLH_VAR_T(AAA,SSS,TTT)                  "Variation of the solarH generation"   ;
execute_load  '../../base/auxils/timestep_conversion/input/all_endofmodel.gdx', SOLH_VAR_T;

PARAMETER WTRRSVAR_S(AAA,SSS)                      "Variation of the water inflow to reservoirs"   ;
execute_load  '../../base/auxils/timestep_conversion/input/all_endofmodel.gdx', WTRRSVAR_S;

PARAMETER WTRRRVAR_T(AAA,SSS,TTT)                  "Variation of generation of hydro run-of-river"  ;
execute_load  '../../base/auxils/timestep_conversion/input/all_endofmodel.gdx', WTRRRVAR_T;

PARAMETER HYRSDATA(AAA,HYRSDATASET,SSS)    "Data for hydro with storage"  ;
execute_load  '../../base/auxils/timestep_conversion/input/all_endofmodel.gdx', HYRSDATA;

PARAMETER HYPPROFILS(AAA,SSS)                      "Hydro with storage seasonal price profile" ;
execute_load  '../../base/auxils/timestep_conversion/input/all_endofmodel.gdx', HYPPROFILS;

PARAMETER GKRATE(AAA,GGG,SSS)                       "Capacity rating (non-negative, typically close to 1; default/1/, use eps for 0)" ;
execute_load  '../../base/auxils/timestep_conversion/input/all_endofmodel.gdx', GKRATE;

PARAMETER DE_VAR_T(RRR,DEUSER,SSS,TTT)                    "Variation in electricity demand"   ;
execute_load  '../../base/auxils/timestep_conversion/input/all_endofmodel.gdx', DE_VAR_T;

PARAMETER DH_VAR_T(AAA,DHUSER,SSS,TTT)                    "Variation in heat demand"   ;
execute_load  '../../base/auxils/timestep_conversion/input/all_endofmodel.gdx', DH_VAR_T;

PARAMETER WEIGHT_S(SSS)                            "Weight (relative length) of each season"    ;
execute_load  '../../base/auxils/timestep_conversion/input/all_endofmodel.gdx', WEIGHT_S;

PARAMETER WEIGHT_T(TTT)                            "Weight (relative length) of each time period"  ;
execute_load  '../../base/auxils/timestep_conversion/input/all_endofmodel.gdx', WEIGHT_T;

*REST OF HYDRO PARAMETERS.........

*New timeseries
PARAMETER WND_VAR_T_NEW(AAA,SSS_NEW,TTT_NEW)                   "Variation of the wind generation"    ;
PARAMETER SOLE_VAR_T_NEW(AAA,SSS_NEW,TTT_NEW)                  "Variation of the solarE generation"   ;
PARAMETER SOLH_VAR_T_NEW(AAA,SSS_NEW,TTT_NEW)                  "Variation of the solarH generation"   ;
PARAMETER GKRATE_NEW(AAA,GGG,SSS_NEW)                       "Capacity rating (non-negative, typically close to 1; default/1/, use eps for 0)" ;
PARAMETER WTRRSVAR_S_NEW(AAA,SSS_NEW)                        "Variation of the water inflow to reservoirs"   ;
PARAMETER WTRRRVAR_T_NEW(AAA,SSS_NEW,TTT_NEW)                  "Variation of generation of hydro run-of-river"  ;
PARAMETER HYRSDATA_NEW(AAA,HYRSDATASET,SSS_NEW)           "Data for hydro with storage"  ;
PARAMETER HYPPROFILS_NEW(AAA,SSS_NEW)                      "Hydro with storage seasonal price profile" ;
PARAMETER DE_VAR_T_NEW(RRR,DEUSER,SSS_NEW,TTT_NEW)                    "Variation in electricity demand"   ;
PARAMETER DH_VAR_T_NEW(AAA,DHUSER,SSS_NEW,TTT_NEW)                    "Variation in heat demand"   ;
PARAMETER WEIGHT_S_NEW(SSS_NEW)                            "Weight (relative length) of each season"    ;
PARAMETER WEIGHT_T_NEW(TTT_NEW)                            "Weight (relative length) of each time period" ;


*----------END OF INPUT DATA--------------------

*----------INTERNAL SETS----


SET ST_LINK(SSS,TTT,SSS_NEW,TTT_NEW);
SET S_LINK(SSS,SSS_NEW);
SCALAR COUNT_OLD_SET;
SCALAR COUNT_NEW_SET;

COUNT_OLD_SET=0;
LOOP(SSS,
   LOOP(TTT,
      COUNT_OLD_SET=COUNT_OLD_SET+1;
      COUNT_NEW_SET=0;
      LOOP(SSS_NEW,
         LOOP(TTT_NEW,
         COUNT_NEW_SET=COUNT_NEW_SET+1;
         IF(COUNT_NEW_SET EQ COUNT_OLD_SET,
            ST_LINK(SSS,TTT,SSS_NEW,TTT_NEW)=YES;
            S_LINK(SSS,SSS_NEW)=YES;
         );
         );
      );
   );
);

*-----END OF INTERNAL SETS--------------


*------------CALCULATIONS-------------
WND_VAR_T_NEW(AAA,SSS_NEW,TTT_NEW)=SUM((SSS,TTT)$ST_LINK(SSS,TTT,SSS_NEW,TTT_NEW),WND_VAR_T(AAA,SSS,TTT));
SOLE_VAR_T_NEW(AAA,SSS_NEW,TTT_NEW)=SUM((SSS,TTT)$ST_LINK(SSS,TTT,SSS_NEW,TTT_NEW),SOLE_VAR_T(AAA,SSS,TTT));
SOLH_VAR_T_NEW(AAA,SSS_NEW,TTT_NEW)=SUM((SSS,TTT)$ST_LINK(SSS,TTT,SSS_NEW,TTT_NEW),SOLH_VAR_T(AAA,SSS,TTT));
GKRATE_NEW(AAA,GGG,SSS_NEW)=SUM(SSS$S_LINK(SSS,SSS_NEW),GKRATE(AAA,GGG,SSS));
WTRRSVAR_S_NEW(AAA,SSS_NEW)=SUM(SSS$S_LINK(SSS,SSS_NEW),WTRRSVAR_S(AAA,SSS));
WTRRRVAR_T_NEW(AAA,SSS_NEW,TTT_NEW)=SUM((SSS,TTT)$ST_LINK(SSS,TTT,SSS_NEW,TTT_NEW),WTRRRVAR_T(AAA,SSS,TTT));
HYRSDATA_NEW(AAA,HYRSDATASET,SSS_NEW)=SUM(SSS$S_LINK(SSS,SSS_NEW),HYRSDATA(AAA,HYRSDATASET,SSS));
HYPPROFILS_NEW(AAA,SSS_NEW)=SUM(SSS$S_LINK(SSS,SSS_NEW),HYPPROFILS(AAA,SSS));
DE_VAR_T_NEW(RRR,DEUSER,SSS_NEW,TTT_NEW)=SUM((SSS,TTT)$ST_LINK(SSS,TTT,SSS_NEW,TTT_NEW),DE_VAR_T(RRR,DEUSER,SSS,TTT));
DH_VAR_T_NEW(AAA,DHUSER,SSS_NEW,TTT_NEW)=SUM((SSS,TTT)$ST_LINK(SSS,TTT,SSS_NEW,TTT_NEW),DH_VAR_T(AAA,DHUSER,SSS,TTT));
WEIGHT_S_NEW(SSS_NEW)=CARD(TTT_NEW);
WEIGHT_T_NEW(TTT_NEW)=1;

*------------END OF CALCULATIONS-------------




*------------OUTPUT GENERATION-------------


execute_unload  '../../base/auxils/timestep_conversion/output/results.gdx',
ST_LINK,S_LINK,
WND_VAR_T_NEW,
SOLE_VAR_T_NEW,
SOLH_VAR_T_NEW,
GKRATE_NEW,
WTRRSVAR_S_NEW,
WTRRRVAR_T_NEW,
HYRSDATA_NEW,
HYPPROFILS_NEW,
DE_VAR_T_NEW,
DH_VAR_T_NEW,
WEIGHT_S_NEW,
WEIGHT_T_NEW
;

*$ONTEXT
*WND_VAR_T timeseries
file WND_VAR_T_timeseries /'../../base/auxils/timestep_conversion/output/WND_VAR_T.inc'/;
WND_VAR_T_timeseries.nd  = 6;
put WND_VAR_T_timeseries;
put '*PARAMETER WND_VAR_T CALCULATED WITH AUXILS' //
loop((AAA,SSS_NEW,TTT_NEW)$SUM((ISSS_NEW,ITTT_NEW),WND_VAR_T_NEW(AAA,ISSS_NEW,ITTT_NEW)),
            put "WND_VAR_T('",AAA.tl :0,"','",SSS_NEW.tl :0,"','",TTT_NEW.tl :0,"')=", WND_VAR_T_NEW(AAA,SSS_NEW,TTT_NEW) :0 ';' /
);
putclose;

*SOLE_VAR_T timeseries
file SOLE_VAR_T_timeseries /'../../base/auxils/timestep_conversion/output/SOLE_VAR_T.inc'/;
SOLE_VAR_T_timeseries.nd  = 6;
put SOLE_VAR_T_timeseries;
put '*PARAMETER SOLE_VAR_T CALCULATED WITH AUXILS' //
loop((AAA,SSS_NEW,TTT_NEW)$SUM((ISSS_NEW,ITTT_NEW),SOLE_VAR_T_NEW(AAA,ISSS_NEW,ITTT_NEW)),
            put "SOLE_VAR_T('",AAA.tl :0,"','",SSS_NEW.tl :0,"','",TTT_NEW.tl :0,"')=", SOLE_VAR_T_NEW(AAA,SSS_NEW,TTT_NEW) :0 ';' /
);
putclose;

*SOLH_VAR_T timeseries
file SOLH_VAR_T_timeseries /'../../base/auxils/timestep_conversion/output/SOLH_VAR_T.inc'/;
SOLH_VAR_T_timeseries.nd  = 6;
put SOLH_VAR_T_timeseries;
put '*PARAMETER SOLH_VAR_T CALCULATED WITH AUXILS' //
loop((AAA,SSS_NEW,TTT_NEW)$SUM((ISSS_NEW,ITTT_NEW),SOLH_VAR_T_NEW(AAA,ISSS_NEW,ITTT_NEW)),
            put "SOLH_VAR_T('",AAA.tl :0,"','",SSS_NEW.tl :0,"','",TTT_NEW.tl :0,"')=", SOLH_VAR_T_NEW(AAA,SSS_NEW,TTT_NEW) :0 ';' /
);
putclose;

*GKRATE timeseries
file GKRATE_timeseries /'../../base/auxils/timestep_conversion/output/GKRATE.inc'/;
GKRATE_timeseries.nd  = 6;
put GKRATE_timeseries;
put '*PARAMETER GKRATE CALCULATED WITH AUXILS' //
loop((AAA,GGG,SSS_NEW)$SUM((ISSS_NEW),GKRATE_NEW(AAA,GGG,ISSS_NEW)),
            put "GKRATE('",AAA.tl :0,"','",GGG.tl :0,"','",SSS_NEW.tl :0,"')=", GKRATE_NEW(AAA,GGG,SSS_NEW) :0 ';' /
);
putclose;

*WTRRSVAR_S timeseries
file WTRRSVAR_S_timeseries /'../../base/auxils/timestep_conversion/output/WTRRSVAR_S.inc'/;
WTRRSVAR_S_timeseries.nd  = 6;
put WTRRSVAR_S_timeseries;
put '*PARAMETER WTRRSVAR_S CALCULATED WITH AUXILS' //
loop((AAA,SSS_NEW)$SUM((ISSS_NEW),WTRRSVAR_S_NEW(AAA,ISSS_NEW)),
            put "WTRRSVAR_S('",AAA.tl :0,"','",SSS_NEW.tl :0,"')=", WTRRSVAR_S_NEW(AAA,SSS_NEW) :0 ';' /
);
putclose;

*WTRRRVAR_T timeseries
file WTRRRVAR_T_timeseries /'../../base/auxils/timestep_conversion/output/WTRRRVAR_T.inc'/;
WTRRRVAR_T_timeseries.nd  = 6;
put WTRRRVAR_T_timeseries;
put '*PARAMETER WTRRRVAR_T CALCULATED WITH AUXILS' //
loop((AAA,SSS_NEW,TTT_NEW)$SUM((ISSS_NEW,ITTT_NEW),WTRRRVAR_T_NEW(AAA,ISSS_NEW,ITTT_NEW)),
            put "WTRRRVAR_T('",AAA.tl :0,"','",SSS_NEW.tl :0,"','",TTT_NEW.tl :0,"')=", WTRRRVAR_T_NEW(AAA,SSS_NEW,TTT_NEW) :0 ';' /
);
putclose;

*HYRSDATA timeseries
file HYRSDATA_timeseries /'../../base/auxils/timestep_conversion/output/HYRSDATA.inc'/;
HYRSDATA_timeseries.nd  = 6;
put HYRSDATA_timeseries;
put '*PARAMETER HYRSDATA CALCULATED WITH AUXILS' //
loop((AAA,HYRSDATASET,SSS_NEW)$SUM((ISSS_NEW),HYRSDATA_NEW(AAA,HYRSDATASET,SSS_NEW)),
            put "HYRSDATA('",AAA.tl :0,"','",HYRSDATASET.tl :0,"','",SSS_NEW.tl :0,"')=", HYRSDATA_NEW(AAA,HYRSDATASET,SSS_NEW) :0 ';' /
);
putclose;

*HYPPROFILS timeseries
file HYPPROFILS_timeseries /'../../base/auxils/timestep_conversion/output/HYPPROFILS.inc'/;
HYPPROFILS_timeseries.nd  = 6;
put HYPPROFILS_timeseries;
put '*PARAMETER HYPPROFILS CALCULATED WITH AUXILS' //
loop((AAA,SSS_NEW)$SUM((ISSS_NEW),HYPPROFILS_NEW(AAA,ISSS_NEW)),
            put "HYPPROFILS('",AAA.tl :0,"','",SSS_NEW.tl :0,"')=", HYPPROFILS_NEW(AAA,SSS_NEW) :0 ';' /
);
putclose;

*DE_VAR_T timeseries
file DE_VAR_T_timeseries /'../../base/auxils/timestep_conversion/output/DE_VAR_T.inc'/;
DE_VAR_T_timeseries.nd  = 2;
put DE_VAR_T_timeseries;
put '*PARAMETER DE_VAR_T CALCULATED WITH AUXILS' //
loop((RRR,DEUSER,SSS_NEW,TTT_NEW)$SUM((ISSS_NEW,ITTT_NEW),DE_VAR_T_NEW(RRR,DEUSER,ISSS_NEW,ITTT_NEW)),
            put "DE_VAR_T('",RRR.tl :0,"','",DEUSER.tl :0,"','",SSS_NEW.tl :0,"','",TTT_NEW.tl :0,"')=", DE_VAR_T_NEW(RRR,DEUSER,SSS_NEW,TTT_NEW) :0 ';' /
);
putclose;

*DH_VAR_T timeseries
file DH_VAR_T_timeseries /'../../base/auxils/timestep_conversion/output/DH_VAR_T.inc'/;
DH_VAR_T_timeseries.nd  = 2;
put DH_VAR_T_timeseries;
put '*PARAMETER DH_VAR_T CALCULATED WITH AUXILS' //
loop((AAA,DHUSER,SSS_NEW,TTT_NEW)$SUM((ISSS_NEW,ITTT_NEW),DH_VAR_T_NEW(AAA,DHUSER,ISSS_NEW,ITTT_NEW)),
            put "DH_VAR_T('",AAA.tl :0,"','",DHUSER.tl :0,"','",SSS_NEW.tl :0,"','",TTT_NEW.tl :0,"')=", DH_VAR_T_NEW(AAA,DHUSER,SSS_NEW,TTT_NEW) :0 ';' /
);
putclose;

*WEIGHT_S timeseries
file WEIGHT_S_timeseries /'../../base/auxils/timestep_conversion/output/WEIGHT_S.inc'/;
WEIGHT_S_timeseries.nd  = 2;
put WEIGHT_S_timeseries;
put '*PARAMETER WEIGHT_S CALCULATED WITH AUXILS' //
loop(SSS_NEW,
            put "WEIGHT_S('",SSS_NEW.tl :0,"')=", WEIGHT_S_NEW(SSS_NEW) :0 ';' /
);
putclose;

*WEIGHT_T timeseries
file WEIGHT_T_timeseries /'../../base/auxils/timestep_conversion/output/WEIGHT_T.inc'/;
WEIGHT_T_timeseries.nd  = 2;
put WEIGHT_T_timeseries;
put '*PARAMETER WEIGHT_T CALCULATED WITH AUXILS' //
loop(TTT_NEW,
            put "WEIGHT_T('",TTT_NEW.tl :0,"')=", WEIGHT_T_NEW(TTT_NEW) :0 ';' /
);
putclose;

*$OFFTEXT
*------------END OF OUTPUT GENERATION-------------
