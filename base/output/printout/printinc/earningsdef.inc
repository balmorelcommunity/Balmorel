SET OPROFITLABELS /      'Revenue electricity',
                         'Revenue heat',
                         'Fuel costs',
                         'Variable O&M costs',
                         'Fixed O%M costs',
                         'CO2 costs',
                         'Taxes',
                         'Profit (no cap. costs)'
                         /;


PARAMETERS Rev_E(YYY,AAA,GGG)            'Revenue from electricity sales',
           Rev_H(YYY,AAA,GGG)            'Revenue from heat sales',
           Fuel_C(YYY,AAA,GGG)           'Fuel costs',
           VOM_C(YYY,AAA,GGG)            'Variable operating costs (without fuel)',
           FOM_C(YYY,AAA,GGG)            'Fixed operating costs',
           CO2Costs(YYY,AAA,GGG)         'CO2 costs',
           Tax_C(YYY,AAA,GGG)            'Taxes',
           Profitability(YYY,AAA,GGG)    'Profitability'
           OProfitable(OPROFITLABELS,G)  'Output table for profitability'
           ;
FILE file_profit /"../printout/profits.out"/;
if ((file_profit.pw LT 32000),
file_profit.pw = 32000
);