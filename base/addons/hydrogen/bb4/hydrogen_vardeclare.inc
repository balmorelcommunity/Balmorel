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
$ifi %h2_transmission_definition%=='region'   VXH2_T(Y,IRRRE,IRRRI,S,T)             'H2 export from region IRRRE towards IRRRI (MW)'
$ifi %h2_transmission_definition%=='region'   VXH2KN(Y,IRRRE,IRRRI)                 'New H2 transmission capacity (MW)'
$ifi %h2_transmission_definition%=='region'   VXH2KNACCUMNET(Y,IRRRE,IRRRI)         'Accumulated new H2 transmission investments (MISSING: minus any decommissioning of them due to lifetime expiration) this BB4, at end of previous (i.e., available at start of current) year (MW)'
$ifi %h2_transmission_definition%=='region'   VXH2KN_NGTOH2(Y,IRRRE,IRRRI)          'New Conversion of existing natural gas pipe to H2 transmission capacity (MW)'
$ifi %h2_transmission_definition%=='region'   VXH2KNACCUMNET_NGTOH2(Y,IRRRE,IRRRI)  'Accumulated new Conversion of existing natural gas pipe to H2 Transmission investments (MISSING: minus any decommissioning of them due to lifetime expiration) this BB4, at end of previous (i.e., available at start of current) year (MW)'
$ifi %h2_transmission_definition%=='area'   VXH2_T(Y,IAAAE,IAAAI,S,T)             'H2 export from region IAAAE towards IAAAI (MW)'
$ifi %h2_transmission_definition%=='area'   VXH2KN(Y,IAAAE,IAAAI)                 'New H2 transmission capacity (MW)'
$ifi %h2_transmission_definition%=='area'   VXH2KNACCUMNET(Y,IAAAE,IAAAI)         'Accumulated new H2 transmission investments (MISSING: minus any decommissioning of them due to lifetime expiration) this BB4, at end of previous (i.e., available at start of current) year (MW)'
$ifi %h2_transmission_definition%=='area'   VXH2KN_NGTOH2(Y,IAAAE,IAAAI)          'New Conversion of existing natural gas pipe to H2 transmission capacity (MW)'
$ifi %h2_transmission_definition%=='area'   VXH2KNACCUMNET_NGTOH2(Y,IAAAE,IAAAI)  'Accumulated new Conversion of existing natural gas pipe to H2 Transmission investments (MISSING: minus any decommissioning of them due to lifetime expiration) this BB4, at end of previous (i.e., available at start of current) year (MW)'
   VSYNFUEL_G_T(Y,AAA,G,S,T)             'Production of synfuel'

;

$ifi not %flexible_h2_space%==yes $goto no_flexible_h2_space
Positive variable 
VGE_T_FLEXDH2(Y,RRR,S,T) 'Hourly hydrogen for flexible hydrogen demand'
VGE_FLEXDH2(Y,RRR) 'Total hydrogen for flexible hydrogen demand'
VFLEXDH2_SHIFT(Y,RRR) 'how much to shift from one area to area'
; 
$label no_flexible_h2_space

$ifi %h2_transmission_definition%=='region' SOS2 VARIABLE VXH2LAMBDA(Y,IRRRE,IRRRI,XES) 'SOS2 Variable for modelling economy of scale';
$ifi %h2_transmission_definition%=='area'   SOS2 VARIABLE VXH2LAMBDA(Y,IAAAE,IAAAI,XES) 'SOS2 Variable for modelling economy of scale';

