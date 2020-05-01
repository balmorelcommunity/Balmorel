PARAMETERS
* grid tariff cost calculation for output.
GR_FC_OUTPUT_TECH(YYY,YYY,AAA,GGG)  'Grid tariffs, fixed charges payed by P2H'
GR_EC_OUTPUT_TECH(YYY,YYY,AAA,GGG)  'Grid tariffs, energy charges payed by P2H'
GR_DC_OUTPUT_TECH(YYY,YYY,AAA)      'Grid tariffs, demand charges payed by P2H'
GR_EC_OUTPUT_USER(YYY,YYY,RRR,DEUSER) 'Grid tariffs, energy charges payed by user groups'
GR_DC_OUTPUT_USER(YYY,YYY,RRR,DEUSER) 'Grid tariffs, demand charges payed by user groups'

GR_FC_OUTPUT_USER(YYY,YYY,RRR,DEUSER)  'Grid tariffs, fixed charges payed by user groups'

* for calculating grid tariffs for scenario 3 and 4
GR_FC_INPUTOUT_TECH(YYY,YYY,AAA)
GR_FC_INPUTOUT_USER(YYY,YYY,RRR,DEUSER)
GR_GETOH_VAR_TCT(YYY,TECH_GROUP,SSS,TTT)     'total power to heat electricity consumption'
GR_GETOH_VAR_T(YYY,SSS,TTT)     'total power to heat electricity consumption'
GR_GETOH_TCFX(YYY,TECH_GROUP)                'installed power to heat electricity consumption capacity'
GR_GETOH_FX(YYY)                'installed power to heat electricity consumption capacity'
GR_GETOH_CAP1(YYY,MMM)
GR_GETOH_CAP2(YYY,CCC,MMM)
GR_GETOH_CAPY(YYY,CCC)
GR_GETOH_TOTAL(YYY,CCC)
GR_GETOH_PRICE(YYY,CCC)
;