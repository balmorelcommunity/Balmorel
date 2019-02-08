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
ACRONYMS STEAMTURBINE_SUBCRITICAL, RESERVOIR_PMP, WATERTURBINE, ENGINE_IC, BOILER, COMBINEDCYCLE, EXCESS_HEAT, ELECTRICITY_BATTERY, GEOTHERMAL,
GASTURBINE, HEATPUMP, HEATPUMP_AIR, HEATPUMP_EXCESSHEAT, HEATPUMP_GROUND, PIT, WATERTANK, SOLARPV, SOLARHEATING, WINDTURBINE_OFFSHORE_FAR, WINDTURBINE_OFFSHORE_NEARSHORE, WINDTURBINE_ONSHORE;

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

PARAMETER ANNUITYCG(C,G)               "Transforms investment in technologies into annual payment (fraction)";

PARAMETER DEBT_SHARE_G(G)              "Share of debt for the investment of each generation technology (fraction)";
DEBT_SHARE_G(G)$(GDATA(G,'GDKVARIABL') EQ 1)=0.8;

PARAMETER INTEREST_RATE_G(G)           "Interest rate applied to the loan of each generation technology (fraction)";
INTEREST_RATE_G(G)$(GDATA(G,'GDKVARIABL') EQ 1)=0.06;

PARAMETER PAYBACK_TIME_G(G)            "Payback time of the loan for generation technologies (years)";
* Loan repayment assumption: lifetime of the technology if lifetime is higher than 20 years, else 20 years
PAYBACK_TIME_G(G)$(GDATA(G,'GDKVARIABL') EQ 1)=MIN(GDATA(G,'GDLIFETIME'),20);

PARAMETER ANNUITYCX(C)                 "Transforms investment in transmission lines into annual payment (fraction)";

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

ANNUITYCG(C,G)$(GDATA(G,'GDKVARIABL') EQ 1)= ((1-DEBT_SHARE_G(G))*DISCOUNTRATE + INTEREST_RATE_G(G) * DEBT_SHARE_G (G)* (1 - (1 + DISCOUNTRATE) ** (-PAYBACK_TIME_G(G))) / (1 - (1 + INTEREST_RATE_G(G)) **( -PAYBACK_TIME_G(G)))) / (1 - (1 + DISCOUNTRATE) ** (-GDATA(G,'GDLIFETIME')));

ANNUITYCX(C)= ((1-DEBT_SHARE_X)*DISCOUNTRATE + INTEREST_RATE_X * DEBT_SHARE_X* (1 - (1 + DISCOUNTRATE) ** (-PAYBACK_TIME_X)) / (1 - (1 + INTEREST_RATE_X) ** (-PAYBACK_TIME_X))) / (1 - (1 + DISCOUNTRATE) **( -PAYBACK_TIME_X));

*------------END OF CALCULATIONS-------------



*------------OUTPUT GENERATION-------------

file annuity_generation /'../../base/auxils/annuity_calculation/ANNUITYCG.inc'/;
annuity_generation.nd  = 12;
put annuity_generation;
put '*PARAMETER ANNUITYCG(C,G) CALCULATED WITH AUXILS' //
loop((C,G)$(GDATA(G,'GDKVARIABL') EQ 1),
          put ANNUITYCG.tn(C,G),'=' ANNUITYCG(C,G) :0 ';' /
);
putclose;

file annuity_transmission /'../../base/auxils/annuity_calculation/ANNUITYCX.inc'/;
annuity_transmission.nd  = 12;
put annuity_transmission;
put '*PARAMETER ANNUITYCX(C) CALCULATED WITH AUXILS' //
loop(C,
          put ANNUITYCX.tn(C),'=' ANNUITYCX(C) :0 ';' /
);
putclose;

*------------END OF OUTPUT GENERATION-------------
