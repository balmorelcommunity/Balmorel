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


FLH_WIND_ON_DK=2043.049;
FLH_WIND_OFF_DK=3607.546;
FLH_WATER_NO=4371.361;
FLH_WATER_SE=4091.299;
FLH_PV=704.1228;

%CAPEX
CPX_PV_2020=1.040;
CPX_PV_2025=0.805;
CPX_PV_2030=0.623;
CPX_Wind_Onshore_2020=0.946;
CPX_Wind_Onshore_2025=0.908;
CPX_Wind_Onshore_2030=0.869;
CPX_Wind_Offshore_2020=2.962;
CPX_Wind_Offshore_2025=2.771;
CPX_Wind_Offshore_2030=2.580;
CPX_ST_BP_STR_2020=1.233;
CPX_ST_BP_STR_2025=1.201;
CPX_ST_BP_STR_2030=1.170;
CPX_ST_BP_MW_2020=1.233;
CPX_ST_BP_MW_2025=1.201;
CPX_ST_BP_MW_2030=1.170;
CPX_ST_CND_CO_2020=1.127;
CPX_ST_CND_CO_2025=1.099;
CPX_ST_CND_CO_2030=1.070;
CPX_GT_CND_NG_2020=0.564;
CPX_GT_CND_NG_2025=0.549;
CPX_GT_CND_NG_2030=0.535;
CPX_GTCC_EXT_NG_2020=0.841;
CPX_GTCC_EXT_NG_2025=0.817;
CPX_GTCC_EXT_NG_2030=0.793;
CPX_GTCC_BP_NG_2020=1.242;
CPX_GTCC_BP_NG_2025=1.194;
CPX_GTCC_BP_NG_2030=1.147;
CPX_ENG_EXT_NG_2020=0.908;
CPX_ENG_EXT_NG_2025=0.884;
CPX_ENG_EXT_NG_2030=0.860;
CPX_HP_EL_2020=0.631;
CPX_HP_EL_2025=0.597;
CPX_HP_EL_2030=0.564;
CPX_BO_NG_2020=0.057;
CPX_BO_NG_2025=0.053;
CPX_BO_NG_2030=0.048;

% PI_OnWind=3199; %1 Full load hours of operation of onshore wind turbines in 2035
% PI_OffWind=4466; %2 Full load hours of operation of offshore wind turbines in 2035 
% PI_SolarPV=1073; %3 Full load hours of operation of solar PV in 2035 
% PI_SolarDH=750; %4 Full load hours of operation of solar collectors in 2035 
% PI_Hydropower=4236; %5 Full load hours of operation of hydropower plants in 2035 
% RHO_WPprice=6.86; %6 Wood Pellets price in 2035 (international market price) (Money/GJ) 
% MU_Straw=115.0;   %7 Available straw for electricity and DH in Denmark in 2035 (PJ/year)
% MU_Biogas=24.7;   %8 Available biogas for electricity and DH in Denmark in 2035 (PJ/year)
% MU_MSW=32.6;      %9 Available MSW for electricity and DH in Denmark in 2035(PJ/year)
% MU_HP=4.7;        %10 Maximum heat production from heat pumps in large DH in 2035(PJ/year)
% K_OnWind=0.52;    %11 CAPEX of Onshore wind turbines by 2035 (Money/MW)
% K_OffWind=1.56;   %12 CAPEX of Offshore wind turbines by 2035 (Money/MW)
% K_SolarPV=0.50;   %13 CAPEX of Solar PV by 2035 (Money/MW)
% K_SolarDH=0.16;   %14 CAPEX of Solar DH by 2035 (Money/MW)
% K_BioCHP=1.29;    %15 CAPEX of Biomass CHP plants (Large Steam turbines) by 2035 (Money/MWelectricity)
% Lambda_coal=0;    %16 Limit to coal use in Denmark by 2035 (PJ/year)
% Lambda_NG=7.6;    %17 Limit to Natural Gas use in Denmark by 2035 (PJ/year)
% Lambda_nuclear=6727;  %18 Installed nuclear capacity in Sweden by 2035 (MW electricity)
% NU_biorefineries=4.4; %19 DH production as a by-product in biorefineries in Denmark by 2035 (PJ/year)
% TAU_availability=0.9; %20 Hourly Availability of power transmission lines between Denmark and connected grids (%)
% TAU_investments=10000; %21 Still non-planned possibility to invest in new power transmission lines between Denmark and other connected grids by 2035(MW)
% DR=0.04;               %22 Discount rate(%)
% DELTA_ElecDK=110.1;    %23 Classic electricity demand (not EV, HPs, H2 included) in Denmark by 2035 (PJ/year)
% DELTA_ElecDE=1625.0;   %24 Classic electricity demand (not EV, HPs, H2 included) in Germany by 2035 (PJ/year)
% DELTA_ElecNO=297.2;    %25 Classic electricity demand (not EV, HPs, H2 included) in Norway by 2035 (PJ/year)
% DELTA_ElecSE=412.3;    %26 Classic electricity demand (not EV, HPs, H2 included) in Sweden by 2035 (PJ/year)
% DELTA_DHDK=118.1;      %27 District Heating demand in Denmark by 2035 (PJ/year)

par = [FLH_WIND_ON_DK,FLH_WIND_OFF_DK,FLH_WATER_NO,FLH_WATER_SE,FLH_PV,...
       CPX_PV_2020,CPX_PV_2025,CPX_PV_2030,CPX_Wind_Onshore_2020,CPX_Wind_Onshore_2025,...
       CPX_Wind_Onshore_2030,CPX_Wind_Offshore_2020,CPX_Wind_Offshore_2025,CPX_Wind_Offshore_2030,...
       CPX_ST_BP_STR_2020,CPX_ST_BP_STR_2025,CPX_ST_BP_STR_2030,CPX_ST_BP_MW_2020,CPX_ST_BP_MW_2025,...
       CPX_ST_BP_MW_2030,CPX_ST_CND_CO_2020,CPX_ST_CND_CO_2025,CPX_ST_CND_CO_2030,CPX_GT_CND_NG_2020,...
       CPX_GT_CND_NG_2025,CPX_GT_CND_NG_2030,CPX_GTCC_EXT_NG_2020,CPX_GTCC_EXT_NG_2025,CPX_GTCC_EXT_NG_2030,...
       CPX_GTCC_BP_NG_2020,CPX_GTCC_BP_NG_2025,CPX_GTCC_BP_NG_2030,CPX_ENG_EXT_NG_2020,CPX_ENG_EXT_NG_2025,...
       CPX_ENG_EXT_NG_2030,CPX_HP_EL_2020,CPX_HP_EL_2025,CPX_HP_EL_2030,CPX_BO_NG_2020,CPX_BO_NG_2025,CPX_BO_NG_2030];

 

