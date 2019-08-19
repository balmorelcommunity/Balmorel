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
GASTURBINE, DUMMY, HEATPUMP, PIT, WATERTANK, SOLARPV, SOLARHEATING,WINDTURBINE_ONSHORE, WINDTURBINE_OFFSHORE;

*ACRONYMS for subtech groups
* They can be used for multiple purposes
* They should generally not be changed.
* New technology types may be added only if also code specifying their properties are added.
ACRONYMS RG1,RG2,RG3,RG1_OFF1,RG2_OFF1,RG3_OFF1,RG1_OFF2,RG2_OFF2,RG3_OFF2,RG1_OFF3,RG2_OFF3,RG3_OFF3,RG1_OFF4,RG2_OFF4,RG3_OFF4,RG1_OFF5,RG2_OFF5,RG3_OFF5,AIR,EXCESSHEAT,GROUND;

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


SET FDATASET           "Characteristics of fuels "
$if     EXIST '../data/FDATASET.inc' $INCLUDE      '../data/FDATASET.inc';
$if not EXIST '../data/FDATASET.inc' $INCLUDE '../../base/data/FDATASET.inc';


PARAMETER FDATA(FFF,FDATASET)    "Fuel specific values"
$if     EXIST '../data/FDATA.inc' $INCLUDE      '../data/FDATA.inc';
$if not EXIST '../data/FDATA.inc' $INCLUDE '../../base/data/FDATA.inc';


SET GGG          "All generation technologies"
$if     EXIST '../data/GGG.inc' $INCLUDE      '../data/GGG.inc';
$if not EXIST '../data/GGG.inc' $INCLUDE '../../base/data/GGG.inc';


SET G(GGG)    "Generation technologies in the simulation"
$if     EXIST '../data/G.inc' $INCLUDE         '../data/G.inc';
$if not EXIST '../data/G.inc' $INCLUDE '../../base/data/G.inc';

SET GDATASET     "Generation technology data"
$if     EXIST '../data/GDATASET.inc' $INCLUDE      '../data/GDATASET.inc';
$if not EXIST '../data/GDATASET.inc' $INCLUDE '../../base/data/GDATASET.inc';

PARAMETER GDATA(GGG,GDATASET)    "Technologies characteristics"
$if     EXIST '../data/GDATA.inc' $INCLUDE         '../data/GDATA.inc';
$if not EXIST '../data/GDATA.inc' $INCLUDE '../../base/data/GDATA.inc';

SCALAR DISCOUNTRATE "Discount rate by country (fraction)"
$if     EXIST '../data/DISCOUNTRATE.inc' $INCLUDE         '../data/DISCOUNTRATE.inc';
$if not EXIST '../data/DISCOUNTRATE.inc' $INCLUDE '../../base/data/DISCOUNTRATE.inc';

SCALAR    LIFETIME_X               "Lifetime of transmission lines (years)";
$if     EXIST '../data/LIFETIME_X.inc' $INCLUDE         '../data/LIFETIME_X.inc';
$if not EXIST '../data/LIFETIME_X.inc' $INCLUDE '../../base/data/LIFETIME_X.inc';

PARAMETER ANNUITYCG(CCC,GGG)               "Transforms investment in technologies into annual payment (fraction)";

PARAMETER DEBT_SHARE_G(GGG)              "Share of debt for the investment of each generation technology (fraction)";
DEBT_SHARE_G(GGG)$(GDATA(GGG,'GDKVARIABL') EQ 1)=0.8;

PARAMETER INTEREST_RATE_G(GGG)           "Interest rate applied to the loan of each generation technology (fraction)";
INTEREST_RATE_G(GGG)$(GDATA(GGG,'GDKVARIABL') EQ 1)=0.07;

PARAMETER PAYBACK_TIME_G(GGG)            "Payback time of the loan for generation technologies (years)";
* Loan repayment assumption: lifetime of the technology if lifetime is higher than 20 years, else 20 years
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

*----------END OF INPUT DATA--------------------



*------------CALCULATIONS-------------

ANNUITYCG(CCC,GGG)$(GDATA(GGG,'GDKVARIABL') EQ 1)= ((1-DEBT_SHARE_G(GGG))*DISCOUNTRATE + INTEREST_RATE_G(GGG) * DEBT_SHARE_G (GGG)* (1 - (1 + DISCOUNTRATE) ** (-PAYBACK_TIME_G(GGG))) / (1 - (1 + INTEREST_RATE_G(GGG)) **( -PAYBACK_TIME_G(GGG)))) / (1 - (1 + DISCOUNTRATE) ** (-GDATA(GGG,'GDLIFETIME')));

ANNUITYCX(CCC)= ((1-DEBT_SHARE_X)*DISCOUNTRATE + INTEREST_RATE_X * DEBT_SHARE_X* (1 - (1 + DISCOUNTRATE) ** (-PAYBACK_TIME_X)) / (1 - (1 + INTEREST_RATE_X) ** (-PAYBACK_TIME_X))) / (1 - (1 + DISCOUNTRATE) **( -PAYBACK_TIME_X));

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

*------------END OF OUTPUT GENERATION-------------
