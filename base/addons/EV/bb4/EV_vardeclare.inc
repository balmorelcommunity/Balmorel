POSITIVE VARIABLE         VEV_VNETCHARGE_BEV(Y,RRR,S,T)            'Net charging of BEV for tax and tariff calculation'
POSITIVE VARIABLE         VEV_VNETCHARGE_PHEV(Y,RRR,S,T)           'Net charging of PHEV for tax and tariff calculation'
POSITIVE VARIABLE         VEV_VNETDISCHARGE_BEV(Y,RRR,S,T)            'Net discharging of BEV for tax and tariff calculation'
POSITIVE VARIABLE         VEV_VNETDISCHARGE_PHEV(Y,RRR,S,T)           'Net discharging of PHEV for tax and tariff calculation'

$ifi not %SMART%==yes $goto SMART_END
POSITIVE VARIABLE         VEV_VSOC_BEV(Y,RRR,S,T)
POSITIVE VARIABLE         VEV_VSOC_PHEV(Y,RRR,S,T)       'State of charge of the PHEV vehicle fleet.'
POSITIVE VARIABLE         VEV_VG2V_BEV(Y,RRR,S,T)        'Grid to vehicle. Charging of BEVs.'
POSITIVE VARIABLE         VEV_VV2G_BEV(Y,RRR,S,T)        'Vehicle to grid. Discharging of BEVs'
POSITIVE VARIABLE         VEV_VG2V_PHEV(Y,RRR,S,T)       'Grid to vehicle. Charging of PHEVs.'
POSITIVE VARIABLE         VEV_VV2G_PHEV(Y,RRR,S,T)       'Vehicle to grid. Discharging of PHEVs'
$label  SMART_END

$ifi not %V2G%==yes $goto V2G_END
POSITIVE VARIABLE         VEV_VSOC_BEV(Y,RRR,S,T)
POSITIVE VARIABLE         VEV_VSOC_PHEV(Y,RRR,S,T)       'State of charge of the PHEV vehicle fleet.'
POSITIVE VARIABLE         VEV_VG2V_BEV(Y,RRR,S,T)        'Grid to vehicle. Charging of BEVs.'
POSITIVE VARIABLE         VEV_VV2G_BEV(Y,RRR,S,T)        'Vehicle to grid. Discharging of BEVs'
POSITIVE VARIABLE         VEV_VG2V_PHEV(Y,RRR,S,T)       'Grid to vehicle. Charging of PHEVs.'
POSITIVE VARIABLE         VEV_VV2G_PHEV(Y,RRR,S,T)       'Vehicle to grid. Discharging of PHEVs'
$label  V2G_END

$ifi not %STEPCHARGSCHEME%==yes $goto STEPCHARGSCHEME_END
POSITIVE VARIABLE         VEV_VSOC_BEV(Y,RRR,S,T)
POSITIVE VARIABLE         VEV_VSOC_PHEV(Y,RRR,S,T)       'State of charge of the PHEV vehicle fleet.'
POSITIVE VARIABLE         VEV_VG2V_BEV(Y,RRR,S,T)        'Grid to vehicle. Charging of BEVs.'
POSITIVE VARIABLE         VEV_VV2G_BEV(Y,RRR,S,T)        'Vehicle to grid. Discharging of BEVs'
POSITIVE VARIABLE         VEV_VG2V_PHEV(Y,RRR,S,T)       'Grid to vehicle. Charging of PHEVs.'
POSITIVE VARIABLE         VEV_VV2G_PHEV(Y,RRR,S,T)       'Vehicle to grid. Discharging of PHEVs'
$label  STEPCHARGSCHEME_END
;

