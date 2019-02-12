%% Define initial reference parameters for Balmorel simulations 
% Amalia Pizarro Alonso (aroal@dtu.dk)
% Energy Systems Analysis group, DTU
% October, 2016 

%% Define reference value for model parameters (reference Pizarro et al 2016 - Joint optimization of waste and energy systems)
%The model contains a very large amount of parameters and a simplification
%is needed. These are the parameters that might influence the most the
%value of the objective function, electricy or DH prices. For further
%description, see the report.

%References value
%Please, be aware that these values might differ from the ones in the
%report, in order to enable easy communication between Balmorel, units are
%the one in Balmorel model but in the report, other units might have been
%chosen, e.g. Money in this scrip represents €90, but on the report €15


%FLH
FLH_WIND_ON_DK=2043.049;
FLH_WIND_OFF_DK=3607.546;
FLH_WATER_NO=4371.361;
FLH_WATER_SE=4091.299;
FLH_PV=704.1228;

%CAPEX
CPX_PV_2020=1.040;
%CPX_PV_2025=0.805;
CPX_PV_2030=0.623;
CPX_Wind_Onshore_2020=0.946;
%CPX_Wind_Onshore_2025=0.908;
CPX_Wind_Onshore_2030=0.869;
CPX_Wind_Offshore_2020=2.962;
%CPX_Wind_Offshore_2025=2.771;
CPX_Wind_Offshore_2030=2.580;
CPX_ST_BP_STR_2020=1.233;
%CPX_ST_BP_STR_2025=1.201;
CPX_ST_BP_STR_2030=1.170;
CPX_ST_BP_MW_2020=1.233;
%CPX_ST_BP_MW_2025=1.201;
CPX_ST_BP_MW_2030=1.170;
CPX_ST_CND_CO_2020=1.127;
%CPX_ST_CND_CO_2025=1.099;
CPX_ST_CND_CO_2030=1.070;
CPX_GT_CND_NG_2020=0.564;
%CPX_GT_CND_NG_2025=0.549;
CPX_GT_CND_NG_2030=0.535;
CPX_GTCC_EXT_NG_2020=0.841;
%CPX_GTCC_EXT_NG_2025=0.817;
CPX_GTCC_EXT_NG_2030=0.793;
CPX_GTCC_BP_NG_2020=1.242;
%CPX_GTCC_BP_NG_2025=1.194;
CPX_GTCC_BP_NG_2030=1.147;
CPX_ENG_EXT_NG_2020=0.908;
%CPX_ENG_EXT_NG_2025=0.884;
CPX_ENG_EXT_NG_2030=0.860;
CPX_HP_EL_2020=0.631;
%CPX_HP_EL_2025=0.597;
CPX_HP_EL_2030=0.564;
%CPX_BO_NG_2020=0.057;
%CPX_BO_NG_2025=0.053;
%CPX_BO_NG_2030=0.048;

%FUEL PRICES
PR_CO2_2020=18.018;
%PR_CO2_2025=25.676;
PR_CO2_2030=33.333;
PR_NG_2020=5.793;
%PR_NG_2025=7.098;
PR_NG_2030=8.403;
PR_CO_2020=1.850;
%PR_CO_2025=2.012;
PR_CO_2030=2.173;
PR_WP_2020=8.500;
%PR_WP_2025=8.700;
PR_WP_2030=8.900;
PR_STR_2020=5.800;
%PR_STR_2025=6.100;
PR_STR_2030=6.400;
PR_WC_2020=6.500;
%PR_WC_2025=6.800;
PR_WC_2030=7.100;

%Transmission capacity availability
TRANS=0.9;

%Electric Demand
DE_DK_2020=31448284.8219844;
DE_DK_2030=32857918.27;
DE_NO_2020=112839251.816979;

DE_NO_2030=117150895.6;
DE_SE_2020=132030967.31544;
%DE_SE_2025=134862595.5;
DE_SE_2030=137754952.8;
%DE_UK_2020=320502977.349906;
%DE_UK_2025=329452149.3;
%DE_UK_2030=338651202.5;
DE_GER_2020=529581867.799277;
%DE_GER_2025=539084549.6;
DE_GER_2030=548757745.2;

%District Heating
DH_DK_2020=35336996.56;
%DH_DK_2025=41696052.4;
DH_DK_2030=43173706.21;

%Nuclear capacity in Sweden
NUC=7146;

%Discount rate
DR=0.04;


par = [FLH_WIND_ON_DK,FLH_WIND_OFF_DK,FLH_WATER_NO,FLH_WATER_SE,FLH_PV,...
       CPX_PV_2020,CPX_PV_2030,CPX_Wind_Onshore_2020,...
       CPX_Wind_Onshore_2030,CPX_Wind_Offshore_2020,CPX_Wind_Offshore_2030,...
       CPX_ST_BP_STR_2020,CPX_ST_BP_STR_2030,CPX_ST_BP_MW_2020,...
       CPX_ST_BP_MW_2030,CPX_ST_CND_CO_2020,CPX_ST_CND_CO_2030,CPX_GT_CND_NG_2020,...
       CPX_GT_CND_NG_2030,CPX_GTCC_EXT_NG_2020,CPX_GTCC_EXT_NG_2030,...
       CPX_GTCC_BP_NG_2020,CPX_GTCC_BP_NG_2030,CPX_ENG_EXT_NG_2020,...
       CPX_ENG_EXT_NG_2030,CPX_HP_EL_2020,CPX_HP_EL_2030,...
       PR_CO2_2020,PR_CO2_2030,PR_NG_2020,PR_NG_2030,PR_CO_2020,PR_CO_2030,PR_WP_2020,...
       PR_WP_2030,PR_STR_2020,PR_STR_2030,PR_WC_2020,PR_WC_2030,TRANS,...
       DE_DK_2020,DE_DK_2030,DE_NO_2020,DE_NO_2030,DE_SE_2020,DE_SE_2030,...
       DE_GER_2020,DE_GER_2030,DH_DK_2020,DH_DK_2030,NUC,DR];

