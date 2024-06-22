Sets regarding district heating

Set AINDN(AAA,IAAAI)   'Nearest area for areas with possible extenstions on heat'
/
  DK_E_1.         DK_E_1_IND
  DK_E_2.         DK_E_2_IND
  DK_E_3.         DK_E_3_IND
  DK_E_4.         DK_E_4_IND
  DK_E_5.         DK_E_5_IND

  DK_W_1.         DK_W_1_IND
  DK_W_2.         DK_W_2_IND
  DK_W_3.         DK_W_3_IND
  DK_W_4.         DK_W_4_IND
  DK_W_5.         DK_W_5_IND
  DK_W_6.         DK_W_6_IND

  DK_W_AALBORG.   DK_W_AALBORG_IND
  DK_W_AARHUS.    DK_W_AARHUS_IND
  DK_W_TREFOR.    DK_W_TREFOR_IND
  DK_W_ODENSE.    DK_W_ODENSE_IND

  DK_E_Urban.     DK_E_Urban_IND
  DK_E_Rural.     DK_E_Rural_IND
  DK_W_Urban.     DK_W_Urban_IND
  DK_W_Rural.     DK_W_Rural_IND

  DK_E_PUREDH.    DK_E_PUREDH_IND
  DK_W_PUREDH.    DK_W_PUREDH_IND

/;

$ifi %IND%==yes AINDN(AAA,IAAAI) = no;

Set STEPFV  'Steps in head exstentions' /STEPFV1*STEPFV10/;

Set STEPP(STEPFV)   'Steps for price of demand'  /
STEPFV1*STEPFV9
/;

Set STEPD(STEPFV)   'Steps for demand'  /
STEPFV1*STEPFV9
/;

set tech / nat,olie/;

alias(techalias,tech);
