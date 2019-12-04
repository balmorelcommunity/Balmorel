* CODE TO CALCULATE FILL THE TIMESTEP NOT USED  WITH DATA FROM TIMESTEPS USED - JUAN GEA BERMUDEZ

*---------- DATA DEFINITION--------------------
*Possible conversion of timesteps

SET SSS;
$INCLUDE         '../data/SSS.inc';

SET TTT;
$INCLUDE         '../data/TTT.inc';

SET S;
$INCLUDE         '../data/S.inc';

SET T;
$INCLUDE         '../data/T.inc';

ALIAS (SSS,ISSS);
ALIAS (TTT,ITTT);

SET CCCRRRAAA          "All geographical entities (CCC + RRR + AAA)" ;
$INCLUDE         '../data/CCCRRRAAA.inc';
$include   "../../base/addons/offshoregrid/bb4/offshoregrid_cccrrraaaadditions.inc";
$include   "../../base/addons/industry/bb4/industry_cccrrraaaadditions.inc";

SET RRR(CCCRRRAAA)       "All regions" ;
$INCLUDE         '../data/RRR.inc';
$include   "../../base/addons/offshoregrid/bb4/offshoregrid_rrradditions.inc";

ALIAS(RRR,IRRR);

SET AAA(CCCRRRAAA)       "All areas";
$INCLUDE         '../data/AAA.inc';
$include   "../../base/addons/offshoregrid/bb4/offshoregrid_aaaadditions.inc";
$include   "../../base/addons/industry/bb4/industry_aaaadditions.inc";

ALIAS(AAA,IAAA);

SET GGG          "All generation technologies"   ;
$INCLUDE         '../data/GGG.inc';

SET YYY                "All years" ;
$INCLUDE         '../data/YYY.inc';

PARAMETER CHRONOHOUR(S,T) 'Meaning/size of each time step in each season (1 means 1 hour)';
$INCLUDE         '../data/CHRONOHOUR.inc';

SCALAR COUNT;

SET ST_LINK(SSS,TTT,ISSS,ITTT);

PARAMETER ESTOVOLTSVAL(YYY,AAA,GGG,SSS,TTT) "Inter-seasonal Electricity storage content  value (in input money) to be transferred to future runs (input-Money/MWh)";
$ifi  exist '../../base/auxils/timestep_filling/input/ESTOVOLTSVAL.gdx'  execute_load  '../../base/auxils/timestep_filling/input/ESTOVOLTSVAL.gdx', ESTOVOLTSVAL;
$ifi not  exist '../../base/auxils/timestep_filling/input/ESTOVOLTSVAL.gdx' ESTOVOLTSVAL(YYY,AAA,GGG,SSS,TTT)=0;

PARAMETER HSTOVOLTSVAL(YYY,AAA,GGG,SSS,TTT) "Inter-seasonal Heat storage content value (in input money) to be transferred to future runs (input-Money/MWh)";
$ifi  exist '../../base/auxils/timestep_filling/input/HSTOVOLTSVAL.gdx'  execute_load  '../../base/auxils/timestep_filling/input/HSTOVOLTSVAL.gdx', HSTOVOLTSVAL;
$ifi not  exist '../../base/auxils/timestep_filling/input/HSTOVOLTSVAL.gdx' HSTOVOLTSVAL(YYY,AAA,GGG,SSS,TTT)=0;

PARAMETER ESTOVOLTVAL(YYY,AAA,GGG,SSS,TTT) "Intra-seasonal Electricity storage content  value (in input money) to be transferred to future runs (input-Money/MWh)";
$ifi  exist '../../base/auxils/timestep_filling/input/ESTOVOLTVAL.gdx'  execute_load  '../../base/auxils/timestep_filling/input/ESTOVOLTVAL.gdx', ESTOVOLTVAL;
$ifi not  exist '../../base/auxils/timestep_filling/input/ESTOVOLTVAL.gdx' ESTOVOLTVAL(YYY,AAA,GGG,SSS,TTT)=0;

PARAMETER HSTOVOLTVAL(YYY,AAA,GGG,SSS,TTT) "Intra-seasonal Heat storage content value (in input money) to be transferred to future runs (input-Money/MWh)";
$ifi  exist '../../base/auxils/timestep_filling/input/HSTOVOLTVAL.gdx'  execute_load  '../../base/auxils/timestep_filling/input/HSTOVOLTVAL.gdx', HSTOVOLTVAL;
$ifi not  exist '../../base/auxils/timestep_filling/input/HSTOVOLTVAL.gdx' HSTOVOLTVAL(YYY,AAA,GGG,SSS,TTT)=0;


*----------END OF INPUT DATA--------------------


*------------CALCULATIONS-------------

COUNT=SUM((S,T)$(ORD(S) EQ 1 AND ORD(T) EQ 1),CHRONOHOUR(S,T));
LOOP(SSS$S(SSS),
   LOOP(TTT$T(TTT),
      ST_LINK(SSS,TTT,SSS,ITTT)$((ORD(ITTT)-ORD(TTT)) LT COUNT AND (ORD(ITTT) GE ORD(TTT)))=YES;
   );
);

ESTOVOLTSVAL(YYY,AAA,GGG,SSS,TTT)=SUM((ISSS,ITTT)$ST_LINK(ISSS,ITTT,SSS,TTT),ESTOVOLTSVAL(YYY,AAA,GGG,ISSS,ITTT));
HSTOVOLTSVAL(YYY,AAA,GGG,SSS,TTT)=SUM((ISSS,ITTT)$ST_LINK(ISSS,ITTT,SSS,TTT),HSTOVOLTSVAL(YYY,AAA,GGG,ISSS,ITTT)) ;
ESTOVOLTVAL(YYY,AAA,GGG,SSS,TTT)=SUM((ISSS,ITTT)$ST_LINK(ISSS,ITTT,SSS,TTT),ESTOVOLTVAL(YYY,AAA,GGG,ISSS,ITTT)) ;
HSTOVOLTVAL(YYY,AAA,GGG,SSS,TTT)=SUM((ISSS,ITTT)$ST_LINK(ISSS,ITTT,SSS,TTT),HSTOVOLTVAL(YYY,AAA,GGG,ISSS,ITTT));

*------------END OF CALCULATIONS-------------


*------------OUTPUT GENERATION-------------

execute_unload  "../../base/auxils/timestep_filling/output/ST_LINK.gdx", ST_LINK;

execute_unload  "../../base/auxils/timestep_filling/output/ESTOVOLTSVAL.gdx", ESTOVOLTSVAL;
execute_unload  "../../base/auxils/timestep_filling/output/HSTOVOLTSVAL.gdx", HSTOVOLTSVAL;
execute_unload  "../../base/auxils/timestep_filling/output/ESTOVOLTVAL.gdx", ESTOVOLTVAL;
execute_unload  "../../base/auxils/timestep_filling/output/HSTOVOLTVAL.gdx", HSTOVOLTVAL;



