* CCS add-on. Added by Juan Gea Bermudez

PARAMETER CCS_DECO2COMP_G(GGG)  "Power consumption to compress CO2 and get ir ready for delivery (MW/(kgCO2/h))";

PARAMETER CCS_CO2CAPTEFF_G(GGG) "CO2 capture efficiency of each G (-)";

SCALAR CCS_TRANSPORTCOST  "CO2 transport and storage cost (money/tCO2)";

*added by mason lester
*added to fix equations that have negative and 0 IM_CO2 values

PARAMETER CCS_CO2CAPTVAL_G(GGG) "CO2 capture value of each G (kg/GJ)";

