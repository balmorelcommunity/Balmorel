POSITIVE VARIABLES
   VHYDROGEN_GH2_T(Y,AAA,GGG,S,T)        'Hydrogen production - existing plants (MWh)'
   VHYDROGEN_STOVOL_T(Y,AAA,G,SSS,T)     'Energy content of hydrogen storage in the beginning of time step T'
   VHYDROGEN_STOLOADT(Y,AAA,GGG,S,T)     'Loading of hydrogen storage'
   VGBIOMETH_T(Y,AAA,GGG,S,T)            'Synthetic natural gas producction (MWh)'
   VGBIOGASUPGRADING_T(Y,AAA,GGG,S,T)    'Biomethane producction from biogas upgrading (CO2 removal) (MWh)'
   VGBIOGASMETHANATION_T(Y,AAA,GGG,S,T)  'Biomethane producction from biogas methanation (h2+biogas) (MWh)'
   VBIOMETHSTOVOLTS(Y,SSS,T)             'Energy content of biomethane storage in the beginning of time step T'
   VBIOMETH_STOLOADT(Y,S,T)              'Loading of biomethane storage'
   VBIOMETH_STOUNLOADT(Y,S,T)            'Unloading of biomethane storage'
   VXH2_T(Y,IRRRE,IRRRI,S,T)             'H2 export from region IRRRE towards IRRRI (MW)'
   VXH2KN(Y,IRRRE,IRRRI)                 'New H2 transmission capacity (MW)'
   VXH2KN_NGTOH2(Y,IRRRE,IRRRI)          'New Conversion of existing natural gas pipe to H2 transmission capacity (MW)'
   VXH2KNACCUMNET(Y,IRRRE,IRRRI)         'Accumulated new H2 transmission investments (MISSING: minus any decommissioning of them due to lifetime expiration) this BB4, at end of previous (i.e., available at start of current) year (MW)'
   VXH2KNACCUMNET_NGTOH2(Y,IRRRE,IRRRI)  'Accumulated new Conversion of existing natural gas pipe to H2 Transmission investments (MISSING: minus any decommissioning of them due to lifetime expiration) this BB4, at end of previous (i.e., available at start of current) year (MW)'


;

SOS2 VARIABLE VXH2LAMBDA(Y,IRRRE,IRRRI,XES) 'SOS2 Variable for modelling economy of scale';

