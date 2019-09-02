
PARAMETER G_CAP_YCRAF_scenarios(scenarios,Y,C,RRR,AAA,G,FFF,COMMODITY,TECH_TYPE,VARIABLE_CATEGORY,UNITS) "Generation capacity for each year, country, region, area, technology, fuel, commodity, technology type and variable type (GW)";
PARAMETER G_STO_YCRAF_scenarios(scenarios,Y,C,RRR,AAA,G,FFF,COMMODITY,TECH_TYPE,VARIABLE_CATEGORY,UNITS) "Generation storage for each year, country, region, area, technology, fuel, commodity, technology type and variable type (GWh)";
PARAMETER PRO_YCRAGF_scenarios(scenarios,Y,C,RRR,AAA,G,FFF,COMMODITY,TECH_TYPE,UNITS) "Annual Energy Production for each year, country, region, area, technology, fuel, commodity and technology type (TWh)";
PARAMETER F_CONS_YCRA_scenarios(scenarios,Y,C,RRR,AAA,G,FFF,TECH_TYPE,UNITS) "Fuel consumption for each year, country, region, area, technology, fuel and technology type (TWh)";
PARAMETER X_CAP_YCR_scenarios(scenarios,Y,C,IRRRE,IRRRI,VARIABLE_CATEGORY,UNITS) "Transmission capacity for each year, country, from region to region (GW)";
PARAMETER X_FLOW_YCR_scenarios(scenarios,Y,C,IRRRE,IRRRI,UNITS) "Transmission flow for each year, country, from region to region (TWh)";
PARAMETER ECO_G_YCRAG_scenarios(scenarios,Y,C,RRR,AAA,G,FFF,TECH_TYPE,CATEGORY,SUBCATEGORY,UNITS) "Generation Economic Output for each year, country, region, fuel, technology type, area and technology (Mmoney)";
PARAMETER ECO_X_YCR_scenarios(scenarios,Y,C,RRR,CATEGORY,SUBCATEGORY,UNITS) "Electric Transmission Economic Output for each year, country and region (Mmoney)";
PARAMETER ECO_XH_YCRA_scenarios(scenarios,Y,C,RRR,AAA,CATEGORY,SUBCATEGORY,UNITS) "Heat Transmission Economic Output for each year, country and region and area (Mmoney)";
PARAMETER OBJ_YCR_scenarios(scenarios,Y,C,RRR,SUBCATEGORY,UNITS) "Objective function (Mmoney)";
PARAMETER EL_PRICE_YCR_scenarios(scenarios,Y,C,RRR,PRICE_CATEGORY,UNITS) "Average Electricity Prices for each region (money/MWh)";
PARAMETER EL_PRICE_YCRST_scenarios(scenarios,Y,C,RRR,SSS,TTT,UNITS) "Hourly Electricity Prices for each region (money/MWh)";
PARAMETER H_PRICE_YCRA_scenarios(scenarios,Y,C,RRR,AAA,PRICE_CATEGORY,UNITS) "Average heating Prices for each area(money/MWh)";
PARAMETER H_PRICE_YCRAST_scenarios(scenarios,Y,C,RRR,AAA,SSS,TTT,UNITS) "Hourly heating Prices for each area (money(MWh)";
PARAMETER EL_DEMAND_YCR_scenarios(scenarios,Y,C,RRR,VARIABLE_CATEGORY,UNITS) "Aggregated annual Electricity Demand (TWh)";
PARAMETER H_DEMAND_YCRA_scenarios(scenarios,Y,C,RRR,AAA,VARIABLE_CATEGORY,UNITS) "Aggregated Annual heat Demand (MWh)";
PARAMETER EMI_YCRAG_scenarios(scenarios,Y,C,RRR,AAA,G,FFF,TECH_TYPE,UNITS) "Annual CO2 emissions(ktons)";


$ifi %HEATTRANS%==yes PARAMETER XH_CAP_YCA_scenarios(scenarios,Y,C,IAAAE,IAAAI,VARIABLE_CATEGORY,UNITS) "Heat Transmission capacity for each year, country, from area to area (GW)";
$ifi %HEATTRANS%==yes PARAMETER XH_FLOW_YCA_scenarios(scenarios,Y,C,IAAAE,IAAAI,UNITS) "Heat Transmission flow for each year, country, from area to area (TWh)";
