

   QHYDROGEN_HGEHTOH2
   QHYDROGEN_HGETOHH2
   QHYDROGEN_H2TOEH
$ifi %h2_transmission_definition%=='region'   QHYDROGEN_EQ
$ifi %h2_transmission_definition%=='area'     QHYDROGEN_EQ_AREA
   QHYDROGEN_STOMAXCON
   QHYDROGEN_STOMAXLOAD
   QHYDROGEN_STOMAXUNLD
   QHYDROGEN_STOVOL
   QHYDROGEN_GCH4KT_UP
   QBIOMETHANE_EQ
   QBIOMETHANE_STOVOLTS
   QGKBIOMETHANE_UP
   QGKBIOGASUPGRADING_UP
   QGKBIOGASMETHANATION_UP



   QXH2K_UP
$ifi %H2TransInvest%==yes  QXH2KNACCUMNET
$ifi %H2TransInvest%==yes  QXH2KNACCUMNET_NGTOH2
$ifi %H2TransInvest%==yes  QXH2INVSYMMETRY
$ifi %H2TransInvest%==yes  QXH2INVSYMMETRY_NGTOH2
$ifi %H2TransInvest%==yes  QXH2KMAX_NGTOH2
$ifi %H2TransInvest%==yes  $ifi %ES_H2TRANS%==yes  QVXH2KN_ES
$ifi %H2TransInvest%==yes  $ifi %ES_H2TRANS%==yes  QXH2LAMBDA_ES

* Flexible hydrogen demand in space by Ioannis
$ifi not %flexible_h2_space%==yes $goto no_flexible_h2_space
QSYNTHETIC_EQ_PRODUCTION
QSYNTHETIC_EQ_SHIFT
QSYNTHETIC_EQ_SHIFT_UP
QSYNTHETIC_EQ_SHIFT_DOWN
QSYNTHETIC_EQ_SHIFT_BALANCE_MOVE
QSYNTHETIC_EQ_SHIFT_BALANCE_OVERALL
$label no_flexible_h2_space

$ifi %generic_synfuel%==yes $ifi not %RollingSeasons%==yes   QSYNFUEL_EQ
$ifi %generic_synfuel%==yes $ifi not %RollingSeasons%==yes   QSYNFUEL_AVIATION_SHARE
$ifi %generic_synfuel%==yes $ifi %RollingSeasons%==yes       QSYNFUEL_S_EQ
$ifi %generic_synfuel%==yes $ifi %RollingSeasons%==yes       QSYNFUEL_AVIATION_SHARE_S
$ifi %generic_synfuel%==yes    QSYNBIOFUELPROD_UP  
$ifi %generic_synfuel%==yes    QSYNH2FUELPROD_UP  
$ifi %generic_synfuel%==yes    QSYNFUELSET1
$ifi %generic_synfuel%==yes    QSYNFUELSET2
$ifi %generic_synfuel%==yes    QSYNKSET  
$ifi %generic_synfuel%==yes $ifi %generic_synfuel_inflex%==yes    QSYNINFLEX  