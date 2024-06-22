$ifi %MR%==yes IA(AAA)$ICA('Denmark',AAA)=yes$MRAREAS(AAA);
$ifi %MR%==yes IA('DK_E_Rural') = yes;
$ifi %MR%==yes IA('DK_W_Rural') = yes;
$ifi %MR%==yes IA('DK_E_Offshore') = yes;
$ifi %MR%==yes IA('DK_W_Offshore') = yes;

PARAMETERS
          ITC_EX_Y(SYSEXIT)         'Reserved yearly exit capacity'
          ITC_EX_M(SYSEXIT,s,t)     'Reserved monthly exit capacity'
          ITC_EN_Y(SYSENTRY)        'Reserved yearly entry capacity'
          ITC_EN_M(SYSENTRY,s,t)    'Reserved monthly entry capacity'
          IDGRES_Y(AAA,s,t)         'Residual gas demand'
          IDGOTH_Y(AAA,s,t)         'Gas demand from other large consumers'
          IDGRES_SUMVAR(AAA)        'Residual gasforbrug, weightsum over the variation'
          IDGOTH_SUMVAR(AAA)        'Gasforbrug andre timeaflæste, vægtsum over variation'
          IGSFXW(STORE,STORETYPE,SSS)           'Net quantity gas stored in present week (MWh)'
          ISC(SCON)                 'Storage allowances procured'
          IGEX_PRICE(SOURCE,SSS)    'Export value of natural gas'

          ISE_DGRES_Y(AAA,S,T)
          ISE_DGOTH_Y(AAA,S,T)


          IGEXT_COST(SOURCE,S)         'Gas extraction variable costs'


          ISUPPLY_MAX(SOURCE)            'Exogenous maximum supply capacity'
          IEXP_MAX(SOURCE)               'Exogenous maximum supply capacity'
          IDEV_MAX(SYSEXIT)              'Exogenous maximum delivery capacity'
          ISTORE_MAX(STORE,STORETYPE)    'Exogenous maximum storage capacity'
          IINJ_MAX(STORE,STORETYPE)      'Exogenous maximum injection capacity'
          IEXT_MAX(STORE,STORETYPE)      'Exogenous maximum extraction capacity'
          ;

$ifi %bb1%==yes IDGRES_SUMVAR(IA) = sum((S,T), IHOURSINST(S,T)*DGRES_VAR(IA,S,T));
$ifi %bb1%==yes IDGOTH_SUMVAR(IA) = sum((S,T), IHOURSINST(S,T)*DGOTH_VAR(IA,S,T));

$ifi %bb2%==yes IDGRES_SUMVAR(IA) = sum((S,T), IHOURSINST(S,T)*DGRES_VAR(IA,S,T));
$ifi %bb2%==yes IDGOTH_SUMVAR(IA) = sum((S,T), IHOURSINST(S,T)*DGOTH_VAR(IA,S,T));

$ifi %bb3%==yes IDGRES_SUMVAR(IA) = sum((SSS,T), IHOURSINST(SSS,T)*DGRES_VAR(IA,SSS,T));
$ifi %bb3%==yes IDGOTH_SUMVAR(IA) = sum((SSS,T), IHOURSINST(SSS,T)*DGOTH_VAR(IA,SSS,T));