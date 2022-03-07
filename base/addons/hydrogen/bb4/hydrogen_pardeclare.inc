PARAMETERS
HYDROGEN_DH2          (YYY,CCCRRRAAA)              'Yearly demand for hydrogen from the transport sector'
HYDROGEN_DH2_VAR_T    (CCCRRRAAA,SSS,TTT)          'Variation profile of H2 demand per region'
HYDROGEN_STOVOL_START (Y,AAA,G,SSS)                'Start level of hydrogen storage'
DAC_DE(GGG)          'Power demand needed to produce biomethane through DAC (Mwe/MWth biomethane)'
DAC_DH(GGG)          'Heat demand needed to produce biomethane through DAC (Mwth/MWth biomethane)'
METHANATION_DE(GGG)   'Electricity demand needed to produce biomethane through biogas methanation (MW/MWth biomethane)'
METHANATION_DH2(GGG) 'H2 demand needed to produce biomethane through biogas methanation (MWth/MWth biomethane)'
BIOGASUPGRADING_DE(GGG) 'Electricity demand needed to produce biomethane through biogas upgrading (MW/MWth biomethane)'

H2STOVOLTS(Y,AAA,GGG,SSS,TTT)          'Hydrogen storage content to be used in future runs (MWh)'
H2STOVOLTSVAL(Y,AAA,GGG,SSS,TTT)       'Hydrogen storage value to be used in future runs (MWh)'

BIOMETHSTOVOLTS(Y,SSS,TTT)          'Biomethane storage content to be used in future runs (MWh)'
BIOMETHSTOVOLTSVAL(Y,SSS,TTT)       'Biomethane storage value to be used in future runs (MWh)'

GH2_T(YYY,AAA,GGG,SSS,TTT)               'Hydrogen generation (MW)  to be transferred to future runs'
GBIOMETHANE_T(YYY,AAA,GGG,SSS,TTT)      'Synthetic natural gas generation (MW)  to be transferred to future runs'
GBIOGASMETHANATION_T(YYY,AAA,GGG,SSS,TTT)      'Biomethane generation (MW) from biogas methanation  to be transferred to future runs'
GBIOGASUPGRADING_T(YYY,AAA,GGG,SSS,TTT)      'Biomethane generation (MW)from biogas upgrading  to be transferred to future runs'

HYDROGEN_PRICE(YYY,RRR,SSS,TTT)                'Hydrogen price (money/MWh)  to be transferred to future runs'
BIOMETHANE_PRICE(YYY,SSS,TTT)            'Biomethane price (money/MWh)  to be transferred to future runs'
;

*IHYDROGEN_DH2_REGION_SUMST and IHYDROGEN_DH2_AREA_SUMST  are put here for convenience.
PARAMETER IHYDROGEN_DH2_REGION_SUMST(RRR)            'Variation profile of H2 demand per region';
PARAMETER IHYDROGEN_DH2_AREA_SUMST(AAA)              'Variation profile of H2 demand per region';

PARAMETER DISLOSS_H2(CCCRRRAAA)            'Distribution loss H2';

* Transmission capacity (MW) between regions IRE (exporting) and  IRI (importing)
* at the beginning of current simulation year:
PARAMETER XH2KFX(YYY,IRRRE,IRRRI) "H2 transmission capacity between regions at beginning of year (MW)";

PARAMETER XH2INVCOST(YYY,IRRRE,IRRRI)  "Investment cost in new H2 transmission capacity (Money/MW)";
* Observe: if INF is entered in XH2INVCOST, this means that no tranmission capacity can be established between the two associated regions.

PARAMETER XH2INVCOST_NGTOH2(YYY,IRRRE,IRRRI)  "Investment cost in conversion of natural grids to  H2 transmission capacity (Money/MW)";
* Observe: if INF is entered in XH2INVCOST_NGTOH2, this means that no tranmission capacity can be established between the two associated regions.

PARAMETER XH2COST(IRRRE,IRRRI)  "H2 transmission cost between regions (calculated from exported quantity) (Money/MWh)" ;

PARAMETER XH2LOSS(IRRRE,IRRRI)  "H2 transmission loss between regions (calculated from exported quantity) (share)";

PARAMETER XH2KRATE(IRRRE,IRRRI,SSS,TTT)    "H2 Transmission capacity rating (share; non-negative, typically close to 1; default/1/, use eps for 0)" ;

PARAMETER ANNUITYCXH2(CCC) "Transforms investment in H2 transmission lines into annual payment (fraction). Possibly different meaning in BB4";

PARAMETER XH2MAXK_NGTOH2(YYY,IRRRE,IRRRI)  "Max H2 transmission capacity between two regions of potential conversion of natural grids to H2 grids (MW)";

SCALAR    LIFETIME_XH2                   "Lifetime of H2 transmission lines (years)";

PARAMETER  XH2KACCUMNET(YYY,IRRRE,IRRRI) "Resulting H2 transmission capacity development at end (MISSING: minus any decommissioning of them due to lifetime expiration) this BB4, at end of previous (i.e., available at start of current) year (MW) to be transferred to future runs";
PARAMETER  XH2_T(Y,IRRRE,IRRRI,S,T)      "H2 export from region IRRRE to IRRRI to be transferred to future runs (MW)  to be transferred to future runs";

PARAMETER XH2INVCOST_ES(YYY,IRRRE,IRRRI,XES) 'Investment cost in H2 transmission lines at the beginning of each XES (money/XKN_ES )';
PARAMETER XH2KN_ES(IRRRE,IRRRI,XES) 'Installed capacity in H2 transmission lines at the beginning of each XES (MW)';
