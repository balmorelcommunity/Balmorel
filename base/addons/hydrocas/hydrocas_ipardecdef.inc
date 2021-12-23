** Allocation of the inflow time series to the different power plants

* max natural inflow to ROR plants installed capacity 2020 times 168. For ROR in river systems multiply again with .8
* the rest is allocated to Short FLEX and RIVER_STORAGE according to annual inflow

*
ALIAS(G,IGALIAS2);
PARAMETERS
IHYINF_REG_S(AAA,GGG,SSS) 'Regulated inflow to hydropower modules [MWh/MW installed capacity]'
IHYINF_UNREG_S(AAA,GGG,SSS) 'Unregulated inflow to hydropower modules [MWh/MW installed capacity]'
IWTR_REG_VARSGSUM(G) 'Sum of input inflow time series'
IWTR_UNREG_VARSGSUM(G) 'Sum of input inflow time series'
IHYINF_REG_SUM(AAA,GGG) 'Sum of inflow time series'
IHYINF_UNREG_SUM(AAA,GGG) 'Sum of inflow time series'

IHYINFANN_REG(AAA,GGG) 'annual inflow factor (FLH)'
IHYINFANN_UNREG(AAA,GGG) 'annual inflow factor (FLH) for unregulated inflow'

IHIGHUNREGSEASONS(AAA,GGG,SSS) 'seasons with high unregulated inflow'               !! Special case used for calculating stepwise pric

IRES_CHANGE(YYY,AAA,GGG) 'reservoir change [MWh per installed capacity]'
IRES_CHANGE_A(YYY,AAA,GGG) 'inter-annual storage potential [GWh]'
IRES_CHANGE_R(YYY,RRR) 'total inter-annual storage potential for region [GWh]'

IHD_RATES(AAA,GGG,SSS) 'Weekly maximum storage withdrawal [MW/MW installed capacity]'
;


GKFX(YYY,IA,G)$(SUM(HYDROCAS_CCC, ICA(HYDROCAS_CCC,IA)) AND ((GDATA(G,'GDTYPE') EQ GHYRS) OR (GDATA(G,'GDTYPE') EQ GHYRR))) = 0;
GKFX(YYY,IA,G)$SUM(HYDROCAS_CCC, ICA(HYDROCAS_CCC,IA)) = GKFX(YYY,IA,G) + HYDROPOWER_GKFX(IA,G,YYY);
IAGK_HYDROPOWER(IA,G)$(SUM(HYDROCAS_CCC, ICA(HYDROCAS_CCC,IA)) AND (IGHYRS(G) OR IGHYRR(G))) = YES$(SUM(Y, GKFX(Y,IA,G)) OR AGKN(IA,G));     !! neccessary to redifine?

** INFLOW CALCULATION:
IHYINFANN_REG(IA,G)$IAGK_HYDROPOWER(IA,G)          =   SUM(IWY, HD_REGFLH(G,IWY)) / CARD(IWY) *(1$(NOT INLFOWADJUST(IA)) + INLFOWADJUST(IA)) ;
IHYINFANN_UNREG(IA,G)$IAGK_HYDROPOWER(IA,G)    =   SUM(IWY, HD_UNREGFLH(G,IWY)) / CARD(IWY) *(1$(NOT INLFOWADJUST(IA)) + INLFOWADJUST(IA)) ;

IWTR_REG_VARSGSUM(G) = SUM(IWY, SUM(SSS, WTR_REG_VARSG(G,SSS,IWY))) / CARD(IWY);
IWTR_UNREG_VARSGSUM(G) = SUM(IWY, SUM(SSS, WTR_UNREG_VARSG(G,SSS,IWY))) / CARD(IWY);

IHYINF_REG_S(IA,G,SSS)$(IAGK_HYDROPOWER(IA,G) AND IHYINFANN_REG(IA,G))       = SUM(IWY, WTR_REG_VARSG(G,SSS,IWY)) / CARD(IWY)  * IHYINFANN_REG(IA,G)          / IWTR_REG_VARSGSUM(G) ;
IHYINF_UNREG_S(IA,G,SSS)$(IAGK_HYDROPOWER(IA,G) AND IHYINFANN_UNREG(IA,G))   = SUM(IWY, WTR_UNREG_VARSG(G,SSS,IWY)) / CARD(IWY)* IHYINFANN_UNREG(IA,G)    / IWTR_UNREG_VARSGSUM(G);

IHYINF_REG_SUM(IA,G) = SUM(SSS, IHYINF_REG_S(IA,G,SSS));
IHYINF_UNREG_SUM(IA,G) = SUM(SSS, IHYINF_UNREG_S(IA,G,SSS));

** RATE
IHD_RATES(IA,G,S)$IAGK_HYDROPOWER(IA,G) = SUM(IWY, HD_RATES(IA,G,S,IWY))/    CARD(IWY) / GKFX('2020',IA,G) ;

*  IHIGHUNREGSEASONS
IHIGHUNREGSEASONS(IA,G,S)$(IAGK_HYDROPOWER(IA,G) AND IGHYRS(G)) = 1$(((1$(NOT IHD_RATES(IA,G,S)) + IHD_RATES(IA,G,S))*(CARD(HSEG)-1)/CARD(HSEG)) < IHYINF_UNREG_S(IA,G,S) / CARD(TTT))     ;


* Change in reservoirs between year depending on weather year
* A total energy volume per region is given in "RES_CHANGE" and is allocated to reservoir through this formulas. Each reservoir within the region is given an inter-annual storage potential "IRES_CHANGE_A" based on relationship between summer inflow and storage size.
IRES_CHANGE_A(Y,IA,G)$IAGK_HYDROPOWER(IA,G)  =  MAX(0,GKFX(Y,IA,G) * HDATA(G,'HDRESERVOIR') - SUM(SSS$(ORD(SSS) > 16 and ORD(SSS) < 45),  IHYINF_REG_S(IA,G,SSS))* 0.6 *GKFX(Y,IA,G)) ;
IRES_CHANGE_R(Y,IR)$SUM(C$CCCRRR(C,IR), HYDROCAS_CCC(C))  = SUM((IA,G)$(RRRAAA(IR,IA) AND IAGK_HYDROPOWER(IA,G)), IRES_CHANGE_A(Y,IA,G));
IRES_CHANGE(Y,IA,G)$(IAGK_HYDROPOWER(IA,G) AND SUM(IR$RRRAAA(IR,IA), IRES_CHANGE_R(Y,IR) * SUM(IWY, RES_CHANGE(IR,IWY))))  =    IRES_CHANGE_A(Y,IA,G) / SUM(IR$RRRAAA(IR,IA), IRES_CHANGE_R(Y,IR) / SUM(IWY, RES_CHANGE(IR,IWY)*1000 / CARD(IWY))) / GKFX(Y,IA,G);




** Scale according to number of time segments:
$ifi %timeaggr%==YES IHYINF_REG_S(IA,G,S)$(IAGK_HYDROPOWER(IA,G) AND IGHYRS(G) AND NOT HDATA(G,'HDTYPE') EQ FLEX)     = Sum(SSS,  PS2SSS(S,SSS)*IHYINFNAT_S(IA,G,SSS))/COUNTELEMENTS(S);
$ifi %timeaggr%==YES IHYINF_UNREG_S(IA,G,S)$IAGK_HYDROPOWER(IA,G)  = Sum(SSS,  PS2SSS(S,SSS)*IHYINFUNREG_S(IA,G,SSS))/COUNTELEMENTS(S);

$ifi NOT %timeaggr%==YES IHYINF_REG_S(IA,G,S)$(IHYINF_REG_S(IA,G,S) AND IAGK_HYDROPOWER(IA,G))              = IHYINF_REG_S(IA,G,S)*SUM(SSSALIAS, IHYINF_REG_S(IA,G,SSSALIAS))/SUM(ISALIAS, IHYINF_REG_S(IA,G,ISALIAS));
$ifi NOT %timeaggr%==YES IHYINF_UNREG_S(IA,G,S)$(IHYINF_UNREG_S(IA,G,S) AND IAGK_HYDROPOWER(IA,G))          = IHYINF_UNREG_S(IA,G,S)*SUM(SSSALIAS, IHYINF_UNREG_S(IA,G,SSSALIAS))/SUM(ISALIAS, IHYINF_UNREG_S(IA,G,ISALIAS));
                                                                                                         !! new scaling method here?

* ORD(S) Not 1: SUM(SSSALIAS$(SSSVALUE(SSSALIAS) GT SSSVALUE(S-1) and SSSVALUE(SSSALIAS) LE SSSVALUE(S), IHYINF_REG_S(IA,G,SSSALIAS));
* ORD(S) = 1: SUM(SSSALIAS$(SSSALIAS.VAL, IHYINF_REG_S(IA,G,SSSALIAS)


