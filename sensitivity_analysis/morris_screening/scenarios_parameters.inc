Set MorrisParameters   'Parameters analysed in a Morris Screening' %semislash%
$INCLUDE      '../../sensitivity_analysis/morris_screening/MorrisParameters.inc';
%semislash%;


TABLE MORRISSAMPLING(scenarios,MorrisParameters) "Technologies characteristics"
**Creation of inc file
$call =xls2gms r=A1:H452 I="../../sensitivity_analysis/morris_screening/scenario_creation/output/MorrisSampling.xlsx" O="../../sensitivity_analysis/morris_screening/scenario_creation/output/MorrisSampling_out.inc"
**Reading scenario parameters
$include "../../sensitivity_analysis/morris_screening/scenario_creation/output/MorrisSampling_out.inc"
;


PARAMETER SAMPLING(scenarios,MorrisParameters);
SAMPLING(scenarios,MorrisParameters)=MORRISSAMPLING(scenarios,MorrisParameters);

Parameter P2H_TAX_Scenarios(scenarios) '';
P2H_TAX_Scenarios(scenarios)=SAMPLING(scenarios,'P2H_TAX');

Parameter SOS_TAX_BIOMASS_Scenarios(scenarios) '';
SOS_TAX_BIOMASS_Scenarios(scenarios)=SAMPLING(scenarios,'SOS_TAX_BIOMASS');

Parameter VOL_GRID_TARIFF_Scenarios(scenarios) '';
VOL_GRID_TARIFF_Scenarios(scenarios)=SAMPLING(scenarios,'VOL_GRID_TARIFF');

Parameter DISCOUNT_RATE_Scenarios(scenarios) '';
DISCOUNT_RATE_Scenarios(scenarios)=SAMPLING(scenarios,'DISCOUNT_RATE');

Parameter HEAT_STO_POT_Scenarios(scenarios) '';
HEAT_STO_POT_Scenarios(scenarios)=SAMPLING(scenarios,'HEAT_STO_POT');

Parameter BOILER_POT_Scenarios(scenarios) '';
BOILER_POT_Scenarios(scenarios)=SAMPLING(scenarios,'BOILER_POT');

Parameter HP_POT_Scenarios(scenarios) '';
HP_POT_Scenarios(scenarios)=SAMPLING(scenarios,'HP_POT');

Parameter BYPASS_Scenarios(scenarios) '';
BYPASS_Scenarios(scenarios)=SAMPLING(scenarios,'BYPASS');



PARAMETER DEBT_SHARE_G(G)              "Share of debt for the investment of each generation technology (fraction)";
DEBT_SHARE_G(G)$(GDATA(G,'GDKVARIABL') EQ 1)=0.8;

PARAMETER PAYBACK_TIME_G(G)            "Payback time of the loan for generation technologies (years)";
* Loan repayment assumption: lifetime of the technology if lifetime is higher than 20 years, else 20 years
PAYBACK_TIME_G(G)$(GDATA(G,'GDKVARIABL') EQ 1)=MIN(GDATA(G,'GDLIFETIME'),20);
