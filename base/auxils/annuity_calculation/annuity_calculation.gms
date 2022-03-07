* CODE TO CALCULATE THE ANNUITIES OF THE SYSTEM - JUAN GEA BERMUDEZ


*----------INPUT DATA--------------------

* ACRONYMS:
* ACRONYMS for technology types
* Each of the following ACRONYMS symbolise a technology type.
* They correspond in a one-to-one way with the internal sets IGCND, IGBRP etc. below.
* They should generally not be changed.
* New technology types may be added only if also code specifying their properties are added.
ACRONYMS  GCND, GBPR, GEXT, GHOB, GETOH, GHSTO, GESTO, GHSTOS, GESTOS, GHYRS, GHYRR, GWND, GSOLE, GSOLH, GWAVE;

*ACRONYMS for tech groups
* They can be used for multiple purposes
* They should generally not be changed.
* New technology types may be added only if also code specifying their properties are added.
ACRONYMS STEAMTURBINE_SUBCRITICAL, STEAMTURBINE_SUPERCRITICAL, RESERVOIR_PMP, WATERTURBINE, ENGINE_IC, BOILER, COMBINEDCYCLE, EXCESS_HEAT, ELECTRICITY_BATTERY, GEOTHERMAL,
GASTURBINE, DUMMY, HEATPUMP, PIT, WATERTANK, SOLARPV, SOLARHEATING,WINDTURBINE_ONSHORE, WINDTURBINE_OFFSHORE,BACKUP_ELECTRICITY,BACKUP_HEAT;

*ACRONYMS for subtech groups
* They can be used for multiple purposes
* They should generally not be changed.
* New technology types may be added only if also code specifying their properties are added.
ACRONYMS RG1,RG2,RG3,RG1_OFF1,RG2_OFF1,RG3_OFF1,RG1_OFF2,RG2_OFF2,RG3_OFF2,RG1_OFF3,RG2_OFF3,RG3_OFF3,RG1_OFF4,RG2_OFF4,RG3_OFF4,RG1_OFF5,RG2_OFF5,RG3_OFF5,AIR,AIR_AIR,AIR_WTR, EXCESSHEAT_WTR, GROUND_WTR, EXCESSHEAT,GROUND,HUB_OFF;
*Hydrogen add-on
ACRONYM HYDROGEN_GH2STO,H2_STORAGE, HYDROGEN_GETOH2, HYDROGEN_GETOHH2, HYDROGEN_GEHTOH2, HYDROGEN_GCH4TOH2, HYDROGEN_GH2FUEL, HYDROGEN_GH2TOE, HYDROGEN_GH2TOEH, HYDROGEN_GH2TOBIOMETH,FUELCELL, BIOMETHDAC, ELECTROLYZER,STEAMREFORMING, BACKUP_HYDROGEN,BACKUP_BIOMETHANE,HYDROGEN_GBIOGASMETHANATION,HYDROGEN_GBIOGASUPGRADING,BIOGASUPGRADING,BIOGASMETHANATION;

SET CCCRRRAAA          "All geographical entities (CCC + RRR + AAA)"
$if     EXIST '../data/CCCRRRAAA.inc' $INCLUDE         '../data/CCCRRRAAA.inc';
$if not EXIST '../data/CCCRRRAAA.inc' $INCLUDE '../../base/data/CCCRRRAAA.inc';

SET CCC(CCCRRRAAA)       "All Countries"
$if     EXIST '../data/CCC.inc' $INCLUDE         '../data/CCC.inc';
$if not EXIST '../data/CCC.inc' $INCLUDE '../../base/data/CCC.inc';

SET C(CCC)    "Countries in the simulation"
$if     EXIST '../data/C.inc' $INCLUDE         '../data/C.inc';
$if not EXIST '../data/C.inc' $INCLUDE '../../base/data/C.inc';

SET FFF                "Fuels"
$if     EXIST '../data/FFF.inc' $INCLUDE      '../data/FFF.inc';
$if not EXIST '../data/FFF.inc' $INCLUDE '../../base/data/FFF.inc';
*INCLUDE FFF FROM OTHER ADDONS
$include   "../../base/addons/hydrogen/bb4/hydrogen_fffadditions.inc";

SET FDATASET           "Characteristics of fuels "
$if     EXIST '../data/FDATASET.inc' $INCLUDE      '../data/FDATASET.inc';
$if not EXIST '../data/FDATASET.inc' $INCLUDE '../../base/data/FDATASET.inc';

PARAMETER FDATA(FFF,FDATASET)    "Fuel specific values"
$if     EXIST '../data/FDATA.inc' $INCLUDE      '../data/FDATA.inc';
$if not EXIST '../data/FDATA.inc' $INCLUDE '../../base/data/FDATA.inc';
*INCLUDE FDATA FROM OTHER ADDONS
$include   "../../base/addons/hydrogen/bb4/hydrogen_fdataadditions.inc";

SET GGG          "All generation technologies"
$if     EXIST '../data/GGG.inc' $INCLUDE      '../data/GGG.inc';
$if not EXIST '../data/GGG.inc' $INCLUDE '../../base/data/GGG.inc';
*INCLUDE GGG FROM OTHER ADDONS
$include   "../../base/addons/industry/bb4/industry_gggadditions.inc";
$include   "../../base/addons/indivusers/bb4/indivusers_gggadditions.inc";
$include   "../../base/addons/hydrogen/bb4/hydrogen_gggadditions.inc";

SET G(GGG)    "Generation technologies in the simulation"
$if     EXIST '../data/G.inc' $INCLUDE         '../data/G.inc';
$if not EXIST '../data/G.inc' $INCLUDE '../../base/data/G.inc';
*INCLUDE G FROM OTHER ADDONS
$include   "../../base/addons/industry/bb4/industry_gadditions.inc";
$include   "../../base/addons/indivusers/bb4/indivusers_gadditions.inc";
$include   "../../base/addons/hydrogen/bb4/hydrogen_gadditions.inc";

SET GDATASET     "Generation technology data"
$if     EXIST '../data/GDATASET.inc' $INCLUDE      '../data/GDATASET.inc';
$if not EXIST '../data/GDATASET.inc' $INCLUDE '../../base/data/GDATASET.inc';

PARAMETER GDATA(GGG,GDATASET)    "Technologies characteristics"
$if     EXIST '../data/GDATA.inc' $INCLUDE         '../data/GDATA.inc';
$if not EXIST '../data/GDATA.inc' $INCLUDE '../../base/data/GDATA.inc';
*INCLUDE GDATA FROM OTHER ADDONS
$include   "../../base/addons/hydrogen/bb4/hydrogen_gdataadditions.inc";

SCALAR DISCOUNTRATE "Discount rate by country (fraction)"
$if     EXIST '../data/DISCOUNTRATE.inc' $INCLUDE         '../data/DISCOUNTRATE.inc';
$if not EXIST '../data/DISCOUNTRATE.inc' $INCLUDE '../../base/data/DISCOUNTRATE.inc';

SCALAR    LIFETIME_X               "Lifetime of transmission lines (years)";
$if     EXIST '../data/LIFETIME_X.inc' $INCLUDE         '../data/LIFETIME_X.inc';
$if not EXIST '../data/LIFETIME_X.inc' $INCLUDE '../../base/data/LIFETIME_X.inc';

SCALAR    LIFETIME_XH               "Lifetime of heat transmission lines (years)";
$if     EXIST '../data/HEATTRANS_LIFETIME_XH.inc' $INCLUDE         '../data/HEATTRANS_LIFETIME_XH.inc';
$if not EXIST '../data/HEATTRANS_LIFETIME_XH.inc' $INCLUDE '../../base/data/HEATTRANS_LIFETIME_XH.inc';

SCALAR    LIFETIME_XH2               "Lifetime of H2 transmission lines (years)";
$if     EXIST '../data/HYDROGEN_LIFETIME_XH2.inc' $INCLUDE         '../data/HYDROGEN_LIFETIME_XH2.inc';
$if not EXIST '../data/HYDROGEN_LIFETIME_XH2.inc' $INCLUDE '../../base/data/HYDROGEN_LIFETIME_XH2.inc';

PARAMETER ANNUITYCG(CCC,GGG)               "Transforms investment in technologies into annual payment (fraction)";

PARAMETER DEBT_SHARE_G(GGG)              "Share of debt for the investment of each generation technology (fraction)";
DEBT_SHARE_G(GGG)$(GDATA(GGG,'GDKVARIABL') EQ 1)=0;

PARAMETER INTEREST_RATE_G(GGG)           "Interest rate applied to the loan of each generation technology (fraction)";
INTEREST_RATE_G(GGG)$(GDATA(GGG,'GDKVARIABL') EQ 1)=DISCOUNTRATE;

PARAMETER PAYBACK_TIME_G(GGG)            "Payback time of the loan for generation technologies (years)";
* Private economic perspective: Loan repayment assumption: lifetime of the technology if lifetime is higher than 20 years, else 20 years
*PAYBACK_TIME_G(GGG)$(GDATA(GGG,'GDKVARIABL') EQ 1)=MIN(GDATA(GGG,'GDLIFETIME'),20);
* Socio economic perspective: loan repayment equals lifetime
PAYBACK_TIME_G(GGG)$(GDATA(GGG,'GDKVARIABL') EQ 1)=GDATA(GGG,'GDLIFETIME');

PARAMETER ANNUITYCX(CCC)                 "Transforms investment in transmission lines into annual payment (fraction)";

SCALAR DEBT_SHARE_X                    "Share of debt for the investment of transmission lines (fraction)";
*Assumption: share of debt equal to 0
DEBT_SHARE_X=0;

SCALAR    INTEREST_RATE_X              "Interest rate applied to the loan of transmission lines";
*Assumption: interest rate equals socio economic discount rate
INTEREST_RATE_X = DISCOUNTRATE;

SCALAR    PAYBACK_TIME_X               "Payback time of the loan for transmission lines (years)";
*Assumption: payback time equals lifetime
PAYBACK_TIME_X = LIFETIME_X;

PARAMETER ANNUITYCXH(CCC)  "Transforms investment in heat transmission lines into annual payment (fraction). Possibly different meaning in BB4";

SCALAR DEBT_SHARE_XH                    "Share of debt for the investment of heat transmission lines (fraction)";
*Assumption: share of debt equal to 0
DEBT_SHARE_XH=0;

SCALAR    INTEREST_RATE_XH              "Interest rate applied to the loan of heat transmission lines";
*Assumption: interest rate equals socio economic discount rate
INTEREST_RATE_XH = DISCOUNTRATE;

SCALAR    PAYBACK_TIME_XH               "Payback time of the loan for heat transmission lines (years)";
*Assumption: payback time equals lifetime
PAYBACK_TIME_XH = LIFETIME_XH;

PARAMETER ANNUITYCXH2(CCC)  "Transforms investment in H2 transmission lines into annual payment (fraction). Possibly different meaning in BB4";

SCALAR DEBT_SHARE_XH2                    "Share of debt for the investment of H2 transmission lines (fraction)";
*Assumption: share of debt equal to 0
DEBT_SHARE_XH2=0;

SCALAR    INTEREST_RATE_XH2              "Interest rate applied to the loan of H2 transmission lines";
*Assumption: interest rate equals socio economic discount rate
INTEREST_RATE_XH2 = DISCOUNTRATE;

SCALAR    PAYBACK_TIME_XH2               "Payback time of the loan for H2 transmission lines (years)";
*Assumption: payback time equals lifetime
PAYBACK_TIME_XH2 = LIFETIME_XH2;


*----------END OF INPUT DATA--------------------



*------------CALCULATIONS-------------

ANNUITYCG(CCC,GGG)$(GDATA(GGG,'GDKVARIABL') EQ 1)= ((1-DEBT_SHARE_G(GGG))*DISCOUNTRATE + INTEREST_RATE_G(GGG) * DEBT_SHARE_G (GGG)* (1 - (1 + DISCOUNTRATE) ** (-PAYBACK_TIME_G(GGG))) / (1 - (1 + INTEREST_RATE_G(GGG)) **( -PAYBACK_TIME_G(GGG)))) / (1 - (1 + DISCOUNTRATE) ** (-GDATA(GGG,'GDLIFETIME')));

ANNUITYCX(CCC)= ((1-DEBT_SHARE_X)*DISCOUNTRATE + INTEREST_RATE_X * DEBT_SHARE_X* (1 - (1 + DISCOUNTRATE) ** (-PAYBACK_TIME_X)) / (1 - (1 + INTEREST_RATE_X) ** (-PAYBACK_TIME_X))) / (1 - (1 + DISCOUNTRATE) **( -PAYBACK_TIME_X));

ANNUITYCXH(CCC)= ((1-DEBT_SHARE_XH)*DISCOUNTRATE + INTEREST_RATE_XH * DEBT_SHARE_XH* (1 - (1 + DISCOUNTRATE) ** (-PAYBACK_TIME_XH)) / (1 - (1 + INTEREST_RATE_XH) ** (-PAYBACK_TIME_XH))) / (1 - (1 + DISCOUNTRATE) **( -PAYBACK_TIME_XH));

ANNUITYCXH2(CCC)= ((1-DEBT_SHARE_XH2)*DISCOUNTRATE + INTEREST_RATE_XH2 * DEBT_SHARE_XH2* (1 - (1 + DISCOUNTRATE) ** (-PAYBACK_TIME_XH2)) / (1 - (1 + INTEREST_RATE_XH2) ** (-PAYBACK_TIME_XH2))) / (1 - (1 + DISCOUNTRATE) **( -PAYBACK_TIME_XH2));

*------------END OF CALCULATIONS-------------



*------------OUTPUT GENERATION-------------

file annuity_generation /'../../base/auxils/annuity_calculation/ANNUITYCG.inc'/;
annuity_generation.nd  = 12;
put annuity_generation;
put '*PARAMETER ANNUITYCG(CCC,GGG) CALCULATED WITH AUXILS' //
loop((CCC,GGG)$(GDATA(GGG,'GDKVARIABL') EQ 1),
          put ANNUITYCG.tn(CCC,GGG),'=' ANNUITYCG(CCC,GGG) :0 ';' /
);
putclose;

file annuity_transmission /'../../base/auxils/annuity_calculation/ANNUITYCX.inc'/;
annuity_transmission.nd  = 12;
put annuity_transmission;
put '*PARAMETER ANNUITYCX(CCC) CALCULATED WITH AUXILS' //
loop(CCC,
          put ANNUITYCX.tn(CCC),'=' ANNUITYCX(CCC) :0 ';' /
);
putclose;

file annuity_transmission_heat /'../../base/auxils/annuity_calculation/HEATTRANS_ANNUITYCXH.inc'/;
annuity_transmission_heat.nd  = 12;
put annuity_transmission_heat;
put '*PARAMETER ANNUITYCXH(CCC) CALCULATED WITH AUXILS' //
loop(CCC,
          put ANNUITYCXH.tn(CCC),'=' ANNUITYCXH(CCC) :0 ';' /
);
putclose;

file annuity_transmission_hydrogen /'../../base/auxils/annuity_calculation/HYDROGEN_ANNUITYCXH2.inc'/;
annuity_transmission_hydrogen.nd  = 12;
put annuity_transmission_hydrogen;
put '*PARAMETER ANNUITYCXH2(CCC) CALCULATED WITH AUXILS' //
loop(CCC,
          put ANNUITYCXH2.tn(CCC),'=' ANNUITYCXH2(CCC) :0 ';' /
);
putclose;

*------------END OF OUTPUT GENERATION-------------

