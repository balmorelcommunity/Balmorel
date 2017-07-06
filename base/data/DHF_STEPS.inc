* PARAMETER DHF_STEPS describes the elastic electricity demands
* in relative terms, by quantifying the steps. Compare PARAMETER DEF_STEPS.
* Unit: (none).


* hans__ :   var3low
PARAMETER DHF_STEPS(AAA,SSS,TTT,DF_QP,DHF)  'Elastic heat demands'
;


TABLE DHF_STEPS
                              DHF_DINF
DK_E_Urban.S01.T001.DF_QUANT -INF
DK_E_Urban.S01.T001.DF_PRICE 10000
*
DK_W_Urban.S01.T001.DF_QUANT -INF
DK_W_Urban.S01.T001.DF_PRICE 10000


+                            DHF_UINF
DK_E_Urban.S01.T001.DF_QUANT INF
DK_E_Urban.S01.T001.DF_PRICE -10000
*
DK_W_Urban.S01.T001.DF_QUANT INF
DK_W_Urban.S01.T001.DF_PRICE -10000
;

/* hans12345
DHF_STEPS(IA,SSS,TTT,DF_QP,DHF_U1)$(DHF_STEPS(IA,SSS,TTT,DF_QP,DHF_U) EQ 0) = DHF_STEPS('DK_W_Urban','S01','T001',DF_QP,DHF_U) ;
DHF_STEPS(IA,SSS,TTT,DF_QP,DHF_D1)$(DHF_STEPS(IA,SSS,TTT,DF_QP,DHF_D) EQ 0) = DHF_STEPS('DK_W_Urban','S01','T001',DF_QP,DHF_D) ;
*/