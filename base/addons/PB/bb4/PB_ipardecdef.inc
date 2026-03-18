PARAMETER   ILCA(Y,G,TECH_GROUP,FFF, PB_GDTYPE_SET);
PARAMETER   IM_CO2_prod_elec(Y,G) "CO2eq emission for the production of 1 kWh by unit G"; 
PARAMETER   IM_CO2_prod_heat(Y,G) "CO2eq emission for the production of 1 MJ by unit G"; 
PARAMETER   IM_CO2_constr(Y,G)   "CO2eq emission for the construction of 1 MW of unit G ";


*The following specify relation between GDTECHGROUP and GDFUEL
ILCA(Y, G,TECH_GROUP,FFF, PB_GDTYPE_SET) = YES $(GDATA(G,'GDTECHGROUP') EQ PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET, Y,'GROUP_TECH') AND GDATA(G,'GDFUEL') EQ PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'FUEL') AND GDATA(G,'GDTYPE') EQ PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'Generation_type'));

*The following attributes LCA values to each generator based on its GDTECHGROUP, GDFUEL and GDTYPE, for the different impact categories
*Climate Change
LOOP((Y, G, TECH_GROUP, FFF, PB_GDTYPE_SET),
    IF (ILCA(Y,G,TECH_GROUP,FFF, PB_GDTYPE_SET),
        IM_CO2_prod_elec(Y,G) = PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET, Y,  'LCA_CO2_prod_elec');
		IM_CO2_prod_heat(Y,G)  = PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET, Y, 'LCA_CO2_prod_heat');
		IM_CO2_constr(Y,G)= PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET, Y, 'LCA_CO2_constr');
    );
);

$ifi not %CCS%==yes $goto No_CCS1
    LOOP((Y, G, TECH_GROUP, FFF, PB_GDTYPE_SET)$(CCS_G(G)),
        IF (ILCA(Y,G,TECH_GROUP,FFF, PB_GDTYPE_SET)$(CCS_G(G)),
            IM_CO2_prod_elec(Y,G) = PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET, Y,  'LCA_CO2_prod_elec');
		    IM_CO2_prod_heat(Y,G)  = PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET, Y, 'LCA_CO2_prod_heat');
		    IM_CO2_constr(Y,G)= PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET, Y, 'LCA_CO2_constr');
        );
    );
$label No_CCS1

*Ozone depletion
PARAMETER   IM_Ozone_depletion_prod_elec(Y,G) "CFC11eq emission for the production of 1 kWh by unit G)"; 
PARAMETER   IM_Ozone_depletion_prod_heat(Y,G) "CFC11eq emission for the production of 1 MJ by unit G)"; 
PARAMETER   IM_Ozone_depletion_constr(Y,G)   "CFC11eq emission for the construction of 1 MW of unit G ";
LOOP((Y,G, TECH_GROUP, FFF, PB_GDTYPE_SET),
    IF (ILCA(Y,G,TECH_GROUP,FFF, PB_GDTYPE_SET),
        IM_Ozone_depletion_prod_elec(Y,G) = PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_Ozone_depletion_prod_elec');
		IM_Ozone_depletion_prod_heat(Y,G)  = PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_Ozone_depletion_prod_heat');
		IM_Ozone_depletion_constr(Y,G)= PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET,Y,'LCA_Ozone_depletion_constr');
    );
);

$ifi not %CCS%==yes $goto No_CCS2
    LOOP((Y,G, TECH_GROUP, FFF, PB_GDTYPE_SET)$(CCS_G(G)),
        IF (ILCA(Y,G,TECH_GROUP,FFF, PB_GDTYPE_SET)$(CCS_G(G)),
            IM_Ozone_depletion_prod_elec(Y,G) = PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_Ozone_depletion_prod_elec');
		    IM_Ozone_depletion_prod_heat(Y,G)  = PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_Ozone_depletion_prod_heat');
		    IM_Ozone_depletion_constr(Y,G)= PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET,Y,'LCA_Ozone_depletion_constr');
        );
    );
$label No_CCS2

*Land use
PARAMETER   IM_LU_prod_elec(Y,G) "Pt emission for the production of 1 kWh by unit G)"; 
PARAMETER   IM_LU_prod_heat(Y,G) "Pt emission for the production of 1 MJ by unit G)"; 
PARAMETER   IM_LU_constr(Y,G)   "Pt emission for the construction of 1 MW of unit G ";

LOOP((Y,G, TECH_GROUP, FFF, PB_GDTYPE_SET),
    IF (ILCA(Y,G,TECH_GROUP,FFF, PB_GDTYPE_SET),
        IM_LU_prod_elec(Y,G) = PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_LU_prod_elec');
		IM_LU_prod_heat(Y,G)  = PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_LU_prod_heat');
		IM_LU_constr(Y,G)= PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET,Y,'LCA_LU_constr');
    );
);

$ifi not %CCS%==yes $goto No_CCS3
    LOOP((Y,G, TECH_GROUP, FFF, PB_GDTYPE_SET)$(CCS_G(G)),
        IF (ILCA(Y,G,TECH_GROUP,FFF, PB_GDTYPE_SET)$(CCS_G(G)),
            IM_LU_prod_elec(Y,G) = PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_LU_prod_elec');
            IM_LU_prod_heat(Y,G)  = PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_LU_prod_heat');
            IM_LU_constr(Y,G)= PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET,Y,'LCA_LU_constr');
        );
    );
$label No_CCS3

*Water use
PARAMETER   IM_WU_prod_elec(Y,G) "m3 deprivation impact for the production of 1 kWh by unit G)"; 
PARAMETER   IM_WU_prod_heat(Y,G) "m3 deprivation impact for the production of 1 MJ by unit G)"; 
PARAMETER   IM_WU_constr(Y,G)   "m3 deprivation impact for the construction of 1 MW of unit G ";
LOOP((Y,G, TECH_GROUP, FFF, PB_GDTYPE_SET),
    IF (ILCA(Y,G,TECH_GROUP,FFF, PB_GDTYPE_SET),
        IM_WU_prod_elec(Y,G) = PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_WU_prod_elec');
		IM_WU_prod_heat(Y,G)  = PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_WU_prod_heat');
		IM_WU_constr(Y,G)= PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET,Y,'LCA_WU_constr');
    );
);

$ifi not %CCS%==yes $goto No_CCS4
    LOOP((Y,G, TECH_GROUP, FFF, PB_GDTYPE_SET)$(CCS_G(G)),
        IF (ILCA(Y,G,TECH_GROUP,FFF, PB_GDTYPE_SET)$(CCS_G(G)),
            IM_WU_prod_elec(Y,G) = PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_WU_prod_elec');
            IM_WU_prod_heat(Y,G)  = PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_WU_prod_heat');
            IM_WU_constr(Y,G)= PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET,Y,'LCA_WU_constr');
        );
    );
$label No_CCS4

*Eutrophication freshwater
PARAMETER   IM_Eutrophication_freshwater_prod_elec(Y,G) "kg P equivalent emission for the production of 1 kWh by unit G)"; 
PARAMETER   IM_Eutrophication_freshwater_prod_heat(Y,G) "kg P equivalent emission for the production of 1 MJ by unit G)"; 
PARAMETER   IM_Eutrophication_freshwater_constr(Y,G)   "kg P equivalent emission for the construction of 1 MW of unit G ";
LOOP((Y,G, TECH_GROUP, FFF, PB_GDTYPE_SET),
    IF (ILCA(Y,G,TECH_GROUP,FFF, PB_GDTYPE_SET),
        IM_Eutrophication_freshwater_prod_elec(Y,G) = PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_Eutrophication_freshwater_prod_elec');
		IM_Eutrophication_freshwater_prod_heat(Y,G)  = PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_Eutrophication_freshwater_prod_heat');
		IM_Eutrophication_freshwater_constr(Y,G)= PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET,Y,'LCA_Eutrophication_freshwater_constr');
    );
);

$ifi not %CCS%==yes $goto No_CCS5
    LOOP((Y,G, TECH_GROUP, FFF, PB_GDTYPE_SET)$(CCS_G(G)),
        IF (ILCA(Y,G,TECH_GROUP,FFF, PB_GDTYPE_SET)$(CCS_G(G)),
            IM_Eutrophication_freshwater_prod_elec(Y,G) = PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_Eutrophication_freshwater_prod_elec');
            IM_Eutrophication_freshwater_prod_heat(Y,G)  = PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_Eutrophication_freshwater_prod_heat');
            IM_Eutrophication_freshwater_constr(Y,G)= PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET,Y,'LCA_Eutrophication_freshwater_constr');
        );
    );
$label No_CCS5

*Ecotoxicity freshwater
PARAMETER   IM_Ecotoxicity_freshwater_prod_elec(Y,G) "impact in CTU  for the production of 1 kWh by unit G)"; 
PARAMETER   IM_Ecotoxicity_freshwater_prod_heat(Y,G) "impact in CTU for the production of 1 MJ by unit G)"; 
PARAMETER   IM_Ecotoxicity_freshwater_constr(Y,G)   "impact in CTU for the construction of 1 MW of unit G ";
LOOP((Y,G, TECH_GROUP, FFF, PB_GDTYPE_SET),
    IF (ILCA(Y,G,TECH_GROUP,FFF, PB_GDTYPE_SET),
        IM_Ecotoxicity_freshwater_prod_elec(Y,G) = PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_Ecotoxicity_freshwater_prod_elec');
		IM_Ecotoxicity_freshwater_prod_heat(Y,G)  = PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_Ecotoxicity_freshwater_prod_heat');
		IM_Ecotoxicity_freshwater_constr(Y,G)= PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET,Y,'LCA_Ecotoxicity_freshwater_constr');
    );
);

$ifi not %CCS%==yes $goto No_CCS6
    LOOP((Y,G, TECH_GROUP, FFF, PB_GDTYPE_SET)$(CCS_G(G)),
        IF (ILCA(Y,G,TECH_GROUP,FFF, PB_GDTYPE_SET)$(CCS_G(G)),
            IM_Ecotoxicity_freshwater_prod_elec(Y,G) = PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_Ecotoxicity_freshwater_prod_elec');
            IM_Ecotoxicity_freshwater_prod_heat(Y,G)  = PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_Ecotoxicity_freshwater_prod_heat');
            IM_Ecotoxicity_freshwater_constr(Y,G)= PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET,Y,'LCA_Ecotoxicity_freshwater_constr');
        );
    );
$label No_CCS6

*Particulate Matter
PARAMETER   IM_PM_prod_elec(Y,G) "disease incidence for the production of 1 kWh by unit G)"; 
PARAMETER   IM_PM_prod_heat(Y,G) "disease incidence for the production of 1 MJ by unit G)"; 
PARAMETER   IM_PM_constr(Y,G)   "disease incidence for the construction of 1 MW of unit G ";
LOOP((Y,G, TECH_GROUP, FFF, PB_GDTYPE_SET),
    IF (ILCA(Y,G,TECH_GROUP,FFF, PB_GDTYPE_SET),
        IM_PM_prod_elec(Y,G) = PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET, Y,'LCA_PM_prod_elec');
		IM_PM_prod_heat(Y,G)  = PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET, Y,'LCA_PM_prod_heat');
		IM_PM_constr(Y,G)= PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET,Y,'LCA_PM_constr');
    );
);

$ifi not %CCS%==yes $goto No_CCS7
    LOOP((Y,G, TECH_GROUP, FFF, PB_GDTYPE_SET)$(CCS_G(G)),
        IF (ILCA(Y,G,TECH_GROUP,FFF, PB_GDTYPE_SET)$(CCS_G(G)),
            IM_PM_prod_elec(Y,G) = PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET, Y,'LCA_PM_prod_elec');
            IM_PM_prod_heat(Y,G)  = PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET, Y,'LCA_PM_prod_heat');
            IM_PM_constr(Y,G)= PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET,Y,'LCA_PM_constr');
        );
    );
$label No_CCS7

*Resource use
PARAMETER   IM_Resource_prod_elec(Y,G) "kg of Sb equivalent for the production of 1 kWh by unit G)"; 
PARAMETER   IM_Resource_prod_heat(Y,G) "kg of Sb equivalent for the production of 1 MJ by unit G)"; 
PARAMETER   IM_Resource_constr(Y,G)   "kg of Sb equivalent for the construction of 1 MW of unit G ";
LOOP((Y,G, TECH_GROUP, FFF, PB_GDTYPE_SET),
    IF (ILCA(Y,G,TECH_GROUP,FFF, PB_GDTYPE_SET),
        IM_Resource_prod_elec(Y,G) = PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_Resource_prod_elec');
		IM_Resource_prod_heat(Y,G)  = PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_Resource_prod_heat');
		IM_Resource_constr(Y,G)= PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET,Y,'LCA_Resource_constr');
    );
);

$ifi not %CCS%==yes $goto No_CCS8
    LOOP((Y,G, TECH_GROUP, FFF, PB_GDTYPE_SET)$(CCS_G(G)),
        IF (ILCA(Y,G,TECH_GROUP,FFF, PB_GDTYPE_SET)$(CCS_G(G)),
            IM_Resource_prod_elec(Y,G) = PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_Resource_prod_elec');
            IM_Resource_prod_heat(Y,G)  = PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_Resource_prod_heat');
            IM_Resource_constr(Y,G)= PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET,Y,'LCA_Resource_constr');
        );
    );
$label No_CCS8

*Acidification
PARAMETER   IM_Acidification_prod_elec(Y,G) "mol of H+ equivalent for the production of 1 kWh by unit G)"; 
PARAMETER   IM_Acidification_prod_heat(Y,G) "mol of H+ equivalent for the production of 1 MJ by unit G)"; 
PARAMETER   IM_Acidification_constr(Y,G)   "mol of H+ equivalent for the construction of 1 MW of unit G ";
LOOP((Y,G, TECH_GROUP, FFF, PB_GDTYPE_SET),
    IF (ILCA(Y,G,TECH_GROUP,FFF, PB_GDTYPE_SET),
        IM_Acidification_prod_elec(Y,G) = PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET, Y,'LCA_Acidification_prod_elec');
		IM_Acidification_prod_heat(Y,G)  = PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_Acidification_prod_heat');
		IM_Acidification_constr(Y,G)= PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET,Y,'LCA_Acidification_constr');
    );
);

$ifi not %CCS%==yes $goto No_CCS9
    LOOP((Y,G, TECH_GROUP, FFF, PB_GDTYPE_SET)$(CCS_G(G)),
        IF (ILCA(Y,G,TECH_GROUP,FFF, PB_GDTYPE_SET)$(CCS_G(G)),
            IM_Acidification_prod_elec(Y,G) = PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET, Y,'LCA_Acidification_prod_elec');
            IM_Acidification_prod_heat(Y,G)  = PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_Acidification_prod_heat');
            IM_Acidification_constr(Y,G)= PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET,Y,'LCA_Acidification_constr');
        );
    );
$label No_CCS9

*Ionising radiation
PARAMETER   IM_Radiation_prod_elec(Y,G) "kBq U-235 equivalent for the production of 1 kWh by unit G)"; 
PARAMETER   IM_Radiation_prod_heat(Y,G) "kBq U-235 equivalent for the production of 1 MJ by unit G)"; 
PARAMETER   IM_Radiation_constr(Y,G)   "kBq U-235 equivalent for the construction of 1 MW of unit G ";
LOOP((Y,G, TECH_GROUP, FFF, PB_GDTYPE_SET),
    IF (ILCA(Y,G,TECH_GROUP,FFF, PB_GDTYPE_SET),
        IM_Radiation_prod_elec(Y,G) = PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET, Y,'LCA_Radiation_prod_elec');
		IM_Radiation_prod_heat(Y,G)  = PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_Radiation_prod_heat');
		IM_Radiation_constr(Y,G)= PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET,Y,'LCA_Radiation_constr');
    );
);

$ifi not %CCS%==yes $goto No_CCS10
    LOOP((Y,G, TECH_GROUP, FFF, PB_GDTYPE_SET)$(CCS_G(G)),
        IF (ILCA(Y,G,TECH_GROUP,FFF, PB_GDTYPE_SET)$(CCS_G(G)),
            IM_Radiation_prod_elec(Y,G) = PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET, Y,'LCA_Radiation_prod_elec');
            IM_Radiation_prod_heat(Y,G)  = PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET,Y, 'LCA_Radiation_prod_heat');
            IM_Radiation_constr(Y,G)= PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET,Y,'LCA_Radiation_constr');
        );
    );
$label No_CCS10

$ontext
*LCA data for CCS power plants, producing electricity only, for the different impact categories
*Climate change
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-51_SS-10-MW_Y-2020')=0.172621612;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-53_SS-10-MW_Y-2030')=0.172621612;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-54_SS-10-MW_Y-2040')=0.172621612;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-55_SS-10-MW_Y-2050')=0.172621612;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-59_LS-100-MW_Y-2020')=0.172621612;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-61_LS-100-MW_Y-2030')=0.172621612;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-62_LS-100-MW_Y-2040')=0.172621612;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-63_LS-100-MW_Y-2050')=0.172621612;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-37_SS-5-MW_Y-2020')=0.172621612;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-39_SS-5-MW_Y-2030')=0.172621612;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-40_SS-5-MW_Y-2040')=0.172621612;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-40_SS-5-MW_Y-2050')=0.172621612;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-42_LS-40-MW_Y-2020')=0.172621612;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-43_LS-40-MW_Y-2030')=0.172621612;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-44_LS-40-MW_Y-2040')=0.172621612;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-44_LS-40-MW_Y-2050')=0.172621612;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-47_Y-2020')=0.172621612;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-48_Y-2030')=0.172621612;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-49_Y-2040')=0.172621612;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-50_Y-2050')=0.172621612;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_ST_NGASCCS_CND_E-47_LS-400-MW_Y-2020')=0.172621612;

$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_LS-220-MW-FEED_Y-2020')=0.024984315;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_MS-80-MW-FEED_Y-2020 ')=0.024984315;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_SS-35-MW-FEED_Y-2020 ')=0.024984315;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_LS-220-MW-FEED_Y-2030 ')=0.024984315;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2030 ')=0.024984315;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2040')=0.024984315;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2050 ')=0.024984315;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2030')=0.024984315;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2040 ')=0.024984315;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2050')=0.024984315;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-25_LS-220-MW-FEED_Y-2040')=0.024984315;
$ifi %CCS%==yes IM_CO2_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-25_LS-220-MW-FEED_Y-2050')=0.024984315;

                               
*Ozone depletion
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-51_SS-10-MW_Y-2020')=1.0072E-07;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-53_SS-10-MW_Y-2030')=1.0072E-07;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-54_SS-10-MW_Y-2040')=1.0072E-07;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-55_SS-10-MW_Y-2050')=1.0072E-07;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-59_LS-100-MW_Y-2020')=1.0072E-07;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-61_LS-100-MW_Y-2030')=1.0072E-07;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-62_LS-100-MW_Y-2040')=1.0072E-07;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-63_LS-100-MW_Y-2050')=1.0072E-07;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-37_SS-5-MW_Y-2020')=1.0072E-07;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-39_SS-5-MW_Y-2030')=1.0072E-07;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-40_SS-5-MW_Y-2040')=1.0072E-07;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-40_SS-5-MW_Y-2050')=1.0072E-07;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-42_LS-40-MW_Y-2020')=1.0072E-07;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-43_LS-40-MW_Y-2030')=1.0072E-07;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-44_LS-40-MW_Y-2040')=1.0072E-07;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-44_LS-40-MW_Y-2050')=1.0072E-07;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-47_Y-2020')=1.0072E-07;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-48_Y-2030')=1.0072E-07;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-49_Y-2040')=1.0072E-07;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-50_Y-2050')=1.0072E-07;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_ST_NGASCCS_CND_E-47_LS-400-MW_Y-2020')=1.0072E-07;

$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_LS-220-MW-FEED_Y-2020')=6.55869E-10;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_MS-80-MW-FEED_Y-2020 ')=6.55869E-10;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_SS-35-MW-FEED_Y-2020 ')=6.55869E-10;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_LS-220-MW-FEED_Y-2030 ')=6.55869E-10;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2030 ')=6.55869E-10;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2040')=6.55869E-10;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2050 ')=6.55869E-10;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2030')=6.55869E-10;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2040 ')=6.55869E-10;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2050')=6.55869E-10;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-25_LS-220-MW-FEED_Y-2040')=6.55869E-10;
$ifi %CCS%==yes IM_Ozone_depletion_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-25_LS-220-MW-FEED_Y-2050')=6.55869E-10;

*Land usage
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-51_SS-10-MW_Y-2020')=0.211679555;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-53_SS-10-MW_Y-2030')=0.211679555;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-54_SS-10-MW_Y-2040')=0.211679555;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-55_SS-10-MW_Y-2050')=0.211679555;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-59_LS-100-MW_Y-2020')=0.211679555;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-61_LS-100-MW_Y-2030')=0.211679555;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-62_LS-100-MW_Y-2040')=0.211679555;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-63_LS-100-MW_Y-2050')=0.211679555;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-37_SS-5-MW_Y-2020')=0.211679555;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-39_SS-5-MW_Y-2030')=0.211679555;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-40_SS-5-MW_Y-2040')=0.211679555;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-40_SS-5-MW_Y-2050')=0.211679555;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-42_LS-40-MW_Y-2020')=0.211679555;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-43_LS-40-MW_Y-2030')=0.211679555;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-44_LS-40-MW_Y-2040')=0.211679555;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-44_LS-40-MW_Y-2050')=0.211679555;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-47_Y-2020')=0.211679555;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-48_Y-2030')=0.211679555;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-49_Y-2040')=0.211679555;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-50_Y-2050')=0.211679555;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_ST_NGASCCS_CND_E-47_LS-400-MW_Y-2020')=0.211679555;

$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_LS-220-MW-FEED_Y-2020')=0.047911733;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_MS-80-MW-FEED_Y-2020 ')=0.047911733;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_SS-35-MW-FEED_Y-2020 ')=0.047911733;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_LS-220-MW-FEED_Y-2030 ')=0.047911733;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2030 ')=0.047911733;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2040')=0.047911733;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2050 ')=0.047911733;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2030')=0.047911733;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2040 ')=0.047911733;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2050')=0.047911733;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-25_LS-220-MW-FEED_Y-2040')=0.047911733;
$ifi %CCS%==yes IM_LU_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-25_LS-220-MW-FEED_Y-2050')=0.047911733;


*Water usage
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-51_SS-10-MW_Y-2020')=0.037216977;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-53_SS-10-MW_Y-2030')=0.037216977;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-54_SS-10-MW_Y-2040')=0.037216977;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-55_SS-10-MW_Y-2050')=0.037216977;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-59_LS-100-MW_Y-2020')=0.037216977;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-61_LS-100-MW_Y-2030')=0.037216977;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-62_LS-100-MW_Y-2040')=0.037216977;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-63_LS-100-MW_Y-2050')=0.037216977;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-37_SS-5-MW_Y-2020')=0.037216977;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-39_SS-5-MW_Y-2030')=0.037216977;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-40_SS-5-MW_Y-2040')=0.037216977;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-40_SS-5-MW_Y-2050')=0.037216977;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-42_LS-40-MW_Y-2020')=0.037216977;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-43_LS-40-MW_Y-2030')=0.037216977;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-44_LS-40-MW_Y-2040')=0.037216977;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-44_LS-40-MW_Y-2050')=0.037216977;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-47_Y-2020')=0.037216977;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-48_Y-2030')=0.037216977;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-49_Y-2040')=0.037216977;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-50_Y-2050')=0.037216977;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_ST_NGASCCS_CND_E-47_LS-400-MW_Y-2020')=0.037216977;

$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_LS-220-MW-FEED_Y-2020')=0.011671391;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_MS-80-MW-FEED_Y-2020 ')=0.011671391;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_SS-35-MW-FEED_Y-2020 ')=0.011671391;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_LS-220-MW-FEED_Y-2030 ')=0.011671391;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2030 ')=0.011671391;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2040')=0.011671391;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2050 ')=0.011671391;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2030')=0.011671391;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2040 ')=0.011671391;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2050')=0.011671391;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-25_LS-220-MW-FEED_Y-2040')=0.011671391;
$ifi %CCS%==yes IM_WU_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-25_LS-220-MW-FEED_Y-2050')=0.011671391;

*Eutrophication freshwater
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-51_SS-10-MW_Y-2020')=1.34191E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-53_SS-10-MW_Y-2030')=1.34191E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-54_SS-10-MW_Y-2040')=1.34191E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-55_SS-10-MW_Y-2050')=1.34191E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-59_LS-100-MW_Y-2020')=1.34191E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-61_LS-100-MW_Y-2030')=1.34191E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-62_LS-100-MW_Y-2040')=1.34191E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-63_LS-100-MW_Y-2050')=1.34191E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-37_SS-5-MW_Y-2020')=1.34191E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-39_SS-5-MW_Y-2030')=1.34191E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-40_SS-5-MW_Y-2040')=1.34191E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-40_SS-5-MW_Y-2050')=1.34191E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-42_LS-40-MW_Y-2020')=1.34191E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-43_LS-40-MW_Y-2030')=1.34191E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-44_LS-40-MW_Y-2040')=1.34191E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-44_LS-40-MW_Y-2050')=1.34191E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-47_Y-2020')=1.34191E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-48_Y-2030')=1.34191E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-49_Y-2040')=1.34191E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-50_Y-2050')=1.34191E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_ST_NGASCCS_CND_E-47_LS-400-MW_Y-2020')=1.34191E-05;

$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_LS-220-MW-FEED_Y-2020')=2.08079E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_MS-80-MW-FEED_Y-2020 ')=2.08079E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_SS-35-MW-FEED_Y-2020 ')=2.08079E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_LS-220-MW-FEED_Y-2030 ')=2.08079E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2030 ')=2.08079E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2040')=2.08079E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2050 ')=2.08079E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2030')=2.08079E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2040 ')=2.08079E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2050')=2.08079E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-25_LS-220-MW-FEED_Y-2040')=2.08079E-05;
$ifi %CCS%==yes IM_Eutrophication_freshwater_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-25_LS-220-MW-FEED_Y-2050')=2.08079E-05;

*Ecotoxicity freshwater
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-51_SS-10-MW_Y-2020')=6.012688197;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-53_SS-10-MW_Y-2030')=6.012688197;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-54_SS-10-MW_Y-2040')=6.012688197;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-55_SS-10-MW_Y-2050')=6.012688197;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-59_LS-100-MW_Y-2020')=6.012688197;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-61_LS-100-MW_Y-2030')=6.012688197;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-62_LS-100-MW_Y-2040')=6.012688197;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-63_LS-100-MW_Y-2050')=6.012688197;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-37_SS-5-MW_Y-2020')=6.012688197;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-39_SS-5-MW_Y-2030')=6.012688197;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-40_SS-5-MW_Y-2040')=6.012688197;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-40_SS-5-MW_Y-2050')=6.012688197;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-42_LS-40-MW_Y-2020')=6.012688197;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-43_LS-40-MW_Y-2030')=6.012688197;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-44_LS-40-MW_Y-2040')=6.012688197;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-44_LS-40-MW_Y-2050')=6.012688197;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-47_Y-2020')=6.012688197;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-48_Y-2030')=6.012688197;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-49_Y-2040')=6.012688197;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-50_Y-2050')=6.012688197;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_ST_NGASCCS_CND_E-47_LS-400-MW_Y-2020')=6.012688197;

$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_LS-220-MW-FEED_Y-2020')=4.496520766;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_MS-80-MW-FEED_Y-2020 ')=4.496520766;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_SS-35-MW-FEED_Y-2020 ')=4.496520766;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_LS-220-MW-FEED_Y-2030 ')=4.496520766;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2030 ')=4.496520766;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2040')=4.496520766;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2050 ')=4.496520766;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2030')=4.496520766;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2040 ')=4.496520766;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2050')=4.496520766;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-25_LS-220-MW-FEED_Y-2040')=4.496520766;
$ifi %CCS%==yes IM_Ecotoxicity_freshwater_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-25_LS-220-MW-FEED_Y-2050')=4.496520766;

*Particulate matter
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-51_SS-10-MW_Y-2020')=4.06093E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-53_SS-10-MW_Y-2030')=4.06093E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-54_SS-10-MW_Y-2040')=4.06093E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-55_SS-10-MW_Y-2050')=4.06093E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-59_LS-100-MW_Y-2020')=4.06093E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-61_LS-100-MW_Y-2030')=4.06093E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-62_LS-100-MW_Y-2040')=4.06093E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-63_LS-100-MW_Y-2050')=4.06093E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-37_SS-5-MW_Y-2020')=4.06093E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-39_SS-5-MW_Y-2030')=4.06093E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-40_SS-5-MW_Y-2040')=4.06093E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-40_SS-5-MW_Y-2050')=4.06093E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-42_LS-40-MW_Y-2020')=4.06093E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-43_LS-40-MW_Y-2030')=4.06093E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-44_LS-40-MW_Y-2040')=4.06093E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-44_LS-40-MW_Y-2050')=4.06093E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-47_Y-2020')=4.06093E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-48_Y-2030')=4.06093E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-49_Y-2040')=4.06093E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-50_Y-2050')=4.06093E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_ST_NGASCCS_CND_E-47_LS-400-MW_Y-2020')=4.06093E-09;

$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_LS-220-MW-FEED_Y-2020')=1.36912E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_MS-80-MW-FEED_Y-2020 ')=1.36912E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_SS-35-MW-FEED_Y-2020 ')=1.36912E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_LS-220-MW-FEED_Y-2030 ')=1.36912E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2030 ')=1.36912E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2040')=1.36912E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2050 ')=1.36912E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2030')=1.36912E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2040 ')=1.36912E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2050')=1.36912E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-25_LS-220-MW-FEED_Y-2040')=1.36912E-09;
$ifi %CCS%==yes IM_PM_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-25_LS-220-MW-FEED_Y-2050')=1.36912E-09;

*Acidification
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-51_SS-10-MW_Y-2020')=0.002183073;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-53_SS-10-MW_Y-2030')=0.002183073;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-54_SS-10-MW_Y-2040')=0.002183073;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-55_SS-10-MW_Y-2050')=0.002183073;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-59_LS-100-MW_Y-2020')=0.002183073;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-61_LS-100-MW_Y-2030')=0.002183073;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-62_LS-100-MW_Y-2040')=0.002183073;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-63_LS-100-MW_Y-2050')=0.002183073;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-37_SS-5-MW_Y-2020')=0.002183073;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-39_SS-5-MW_Y-2030')=0.002183073;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-40_SS-5-MW_Y-2040')=0.002183073;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-40_SS-5-MW_Y-2050')=0.002183073;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-42_LS-40-MW_Y-2020')=0.002183073;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-43_LS-40-MW_Y-2030')=0.002183073;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-44_LS-40-MW_Y-2040')=0.002183073;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-44_LS-40-MW_Y-2050')=0.002183073;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-47_Y-2020')=0.002183073;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-48_Y-2030')=0.002183073;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-49_Y-2040')=0.002183073;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-50_Y-2050')=0.002183073;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_ST_NGASCCS_CND_E-47_LS-400-MW_Y-2020')=0.002183073;

$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_LS-220-MW-FEED_Y-2020')=0.000141728;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_MS-80-MW-FEED_Y-2020 ')=0.000141728;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_SS-35-MW-FEED_Y-2020 ')=0.000141728;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_LS-220-MW-FEED_Y-2030 ')=0.000141728;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2030 ')=0.000141728;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2040')=0.000141728;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2050 ')=0.000141728;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2030')=0.000141728;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2040 ')=0.000141728;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2050')=0.000141728;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-25_LS-220-MW-FEED_Y-2040')=0.000141728;
$ifi %CCS%==yes IM_Acidification_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-25_LS-220-MW-FEED_Y-2050')=0.000141728;

*Resource use
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-51_SS-10-MW_Y-2020')=6.38631E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-53_SS-10-MW_Y-2030')=6.38631E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-54_SS-10-MW_Y-2040')=6.38631E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-55_SS-10-MW_Y-2050')=6.38631E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-59_LS-100-MW_Y-2020')=6.38631E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-61_LS-100-MW_Y-2030')=6.38631E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-62_LS-100-MW_Y-2040')=6.38631E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_CC_NGASCCS_CND_E-63_LS-100-MW_Y-2050')=6.38631E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-37_SS-5-MW_Y-2020')=6.38631E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-39_SS-5-MW_Y-2030')=6.38631E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-40_SS-5-MW_Y-2040')=6.38631E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-40_SS-5-MW_Y-2050')=6.38631E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-42_LS-40-MW_Y-2020')=6.38631E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-43_LS-40-MW_Y-2030')=6.38631E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-44_LS-40-MW_Y-2040')=6.38631E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_GT_NGASCCS_CND_E-44_LS-40-MW_Y-2050')=6.38631E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-47_Y-2020')=6.38631E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-48_Y-2030')=6.38631E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-49_Y-2040')=6.38631E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_ENG_NGASCCS_CND_E-50_Y-2050')=6.38631E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_ST_NGASCCS_CND_E-47_LS-400-MW_Y-2020')=6.38631E-07;

$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_LS-220-MW-FEED_Y-2020')=6.78241E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_MS-80-MW-FEED_Y-2020 ')=6.78241E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-23_SS-35-MW-FEED_Y-2020 ')=6.78241E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_LS-220-MW-FEED_Y-2030 ')=6.78241E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2030 ')=6.78241E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2040')=6.78241E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_MS-80-MW-FEED_Y-2050 ')=6.78241E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2030')=6.78241E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2040 ')=6.78241E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-24_SS-35-MW-FEED_Y-2050')=6.78241E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-25_LS-220-MW-FEED_Y-2040')=6.78241E-07;
$ifi %CCS%==yes IM_Resource_prod_elec(Y,'GNR_ST_MSWCCS_CND_E-25_LS-220-MW-FEED_Y-2050')=6.78241E-07;

$offtext








