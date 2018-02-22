* File dflexquant_par.inc for the Balmorel model.
* For use with addon dflexquant
* Latest revision 20171023 (hr)

PARAMETER DEF_STEPS(RRR,DEUSER,SSS,TTT,DF_QP,DEF)               "Elastic electricity demands ()"; !! () todo
$ifi %DEFPCALIB%==yes PARAMETER DEFP_CALIB(RRR,DEUSER,SSS,TTT)  "Calibrate the price side of electricity demand ()"; !! () todo
PARAMETER DHF_STEPS(AAA,DHUSER,SSS,TTT,DF_QP,DHF)               "Elastic heat demands ()"; !! () todo
$ifi %DHFPCALIB%==yes PARAMETER DHFP_CALIB(AAA,DHUSER,SSS,TTT)  "Calibrate the price side of heat demand ()"; !! () todo



PARAMETER IDE_T_DFLEXQUANT(Y,RRR,DEUSER,S,T)      "Nominal electricity demand time segment (S,T) current simulation year (MW)";
PARAMETER IDH_T_DFLEXQUANT(Y,AAA,DHUSER,S,T)      "Nominal heat demand time segment (S,T) current simulation year (MW)";


* PARAMETER IDEFP_T holds the price levels of individual steps in the electricity demand function,
* transformed to be comparable with production costs (including fuel taxes)
* by subtraction of taxes and distribution costs.

* Unit: Money/MWh.
PARAMETER IDEFP_T(RRR,DEUSER,SSS,TTT,DEF)    'Prices on elastic electricity demand steps (Money/MWh)';

IDEFP_T(IR,DEUSER,S,T,DEF_D1) = DEF_STEPS(IR,DEUSER,S,T,'DF_PRICE',DEF_D1)*DEFP_BASE(IR)
- SUM(C$CCCRRR(C,IR),TAX_DE(C,DEUSER)) - DISCOST_E(IR)
$ifi not %DEFPCALIB%==yes ;
$ifi %DEFPCALIB%==yes  + DEFP_CALIB(IR,DEUSER,S,T) ;

*IDEFP_T(IR,DEUSER,S,T,DEF_U1) = DEF_STEPS(IR,DEUSER,S,T,'DF_PRICE',DEF_U1)*DEFP_BASE(IR)      JUST REPETITION (?)
*- SUM(C$CCCRRR(C,IR),TAX_DE(C,DEUSER)) - DISCOST_E(IR)
*$ifi %DEFPCALIB%==yes  + DEFP_CALIB(IR,DEUSER,S,T) ;

IDEFP_T(IR,DEUSER,S,T,DEF_D2) = DEF_STEPS(IR,DEUSER,S,T,'DF_PRICE',DEF_D2);
IDEFP_T(IR,DEUSER,S,T,DEF_U2) = DEF_STEPS(IR,DEUSER,S,T,'DF_PRICE',DEF_U2);
IDEFP_T(IR,DEUSER,S,T,DEF_D3) = DEF_STEPS(IR,DEUSER,S,T,'DF_PRICE',DEF_D3);
IDEFP_T(IR,DEUSER,S,T,DEF_U3) = DEF_STEPS(IR,DEUSER,S,T,'DF_PRICE',DEF_U3);

* TODO: Why are heat and elec not almost identical?


* PARAMETER IDHFP_T holds the price levels of individual steps in the heat demand function,
* transformed to be comparable with production costs (including fuel taxes)
* by subtraction of consumer taxes and distribution costs.

* Unit: Money/MWh.

PARAMETER IDHFP_T(AAA,DHUSER,SSS,TTT,DHF)   'Prices on elastic heat demand steps (Money/MWh)';

IDHFP_T(IA,DHUSER,S,T,DHF)$(DHF_D1(DHF)+DHF_U1(DHF)+DHF_D2(DHF)+DHF_U2(DHF)+DHF_D2(DHF)+DHF_U2(DHF))=
   DHF_STEPS(IA,DHUSER,S,T,'DF_PRICE',DHF)*DHFP_BASE(IA) - SUM(C$ICA(C,IA),TAX_DH(C,DHUSER)) - DISCOST_H(IA)
$ifi %DHFPCALIB%==yes  + DHFP_CALIB(IA,S,T)
;

* For output:
PARAMETER ODFLEXQUANT(Y,RRR,DEUSER,ODEFQUANTTYPE) "Consumption related to flexible demand quantities (MWh)"
