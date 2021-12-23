PARAMETERS
WTR_REG_VARSG(GGG,SSS,WYYY) 'regulated inflow time series [indifferent]'
WTR_UNREG_VARSG(GGG,SSS,WYYY) 'unregulated inflow time series [indifferent]'
HD_REGFLH(GGG,WYYY) 'Full load hour of regulated hydropower inflow [hours]'
HD_UNREGFLH(GGG,WYYY) 'Full load hour of regulated hydropower inflow [hours]'
HD_RATES(AAA,GGG,SSS,WYYY) 'Weekly maximum storage withdrawal time series [MW]'
HD_RATET(AAA,GGG,SSS,WYYY) 'Hourly maximum production time series [fraction]'
HYDROPOWER_GKFX(AAA,GGG,YYY) 'Installed capacity of hydropower modules [MW]'
HDATA(GGG,HDATASET) 'Techno-economic data for hydropower plants'
RES_CHANGE(RRR,WYYY) 'Reservoir change within a weather year [GWh]'
HYDROPOWER_TRANSFER(AAA,GGG,IGGGALIAS) 'coefficient of energy value between two modules'
HYDROPOWER_PUMPTRANSFER(AAA,GGG,IGGGALIAS) 'Energy content of water pumped in relation to energy content added by pumping'
HMINLEVELS(GGG,SSS) 'minimum levels for hydropower storage'
HYDROCAS_HSEG_VOC(HSEG)   'price steps for hydropower segments'
;


$if     EXIST '../data/HD_INFLOW_WEATHERYEAR.inc' $INCLUDE         '../data/HD_INFLOW_WEATHERYEAR.inc';
$if not EXIST '../data/HD_INFLOW_WEATHERYEAR.inc' $INCLUDE '../../base/data/HD_INFLOW_WEATHERYEAR.inc';

$if     EXIST '../data/HD_FX.inc' $INCLUDE         '../data/HD_FX.inc';
$if not EXIST '../data/HD_FX.inc' $INCLUDE '../../base/data/HD_FX.inc';

$if     EXIST '../data/HD_RATE.inc' $INCLUDE         '../data/HD_RATE.inc';
$if not EXIST '../data/HD_RATE.inc' $INCLUDE '../../base/data/HD_RATE.inc';

HD_RATES(AAA,'AGG-NO2_WTR15',SSS,WYYY) =     HD_RATES(AAA,'AGG-NO2_WTR13',SSS,WYYY);
HD_RATES(AAA,'AGG-NO3_WTR15',SSS,WYYY) =     HD_RATES(AAA,'AGG-NO3_WTR13',SSS,WYYY);
HD_RATES(AAA,'AGG-NO5_WTR15',SSS,WYYY) =     HD_RATES(AAA,'AGG-NO5_WTR13',SSS,WYYY);

$if     EXIST '../data/HDATA.inc' $INCLUDE         '../data/HDATA.inc';
$if not EXIST '../data/HDATA.inc' $INCLUDE '../../base/data/HDATA.inc';

$if     EXIST '../data/HD_FLH.inc' $INCLUDE         '../data/HD_FLH.inc';
$if not EXIST '../data/HD_FLH.inc' $INCLUDE '../../base/data/HD_FLH.inc';


* Replace hydropower capacity with newly defined ones
HYRSDATA(IA,HYRSDATASET,S)$SUM(HYDROCAS_CCC, ICA(HYDROCAS_CCC,IA)) = 0;
WTRRRVAR_T(IA,S,T)$SUM(HYDROCAS_CCC, ICA(HYDROCAS_CCC,IA)) = 0;


GKRATE(IA,G,S)$(SUM(HYDROCAS_CCC, ICA(HYDROCAS_CCC,IA)) AND SUM(Y, HYDROPOWER_GKFX(IA,G,Y)) ) = SUM(IWY, HD_RATET(IA,G,S,IWY))/CARD(IWY) * (1$(NOT HDATA(G,'HDGKRATEBASE')) + HDATA(G,'HDGKRATEBASE'));
*GKRATE(IA,G,S)$(SUM(HYDROCAS_CCC, ICA(HYDROCAS_CCC,IA)) AND SUM(Y, HYDROPOWER_GKFX(IA,G,Y)) AND GDATA(G,'GDTYPE') EQ GHYRS AND NOT SUM(ISALIAS, GKRATE(IA,G,ISALIAS))) =1;
*GKRATE(IA,G,S)$(SUM(HYDROCAS_CCC, ICA(HYDROCAS_CCC,IA)) AND SUM(Y, HYDROPOWER_GKFX(IA,G,Y)) AND GDATA(G,'GDTYPE') EQ GHYRS) =  HDATA(G,'HDGKRATEBASE') * GKRATE(IA,G,S);

GKFX(YYY,IA,G)$(SUM(HYDROCAS_CCC, ICA(HYDROCAS_CCC,IA)) AND ((GDATA(G,'GDTYPE') EQ GHYRS) OR (GDATA(G,'GDTYPE') EQ GHYRR))) = 0;
GKFX(YYY,IA,G)$SUM(HYDROCAS_CCC, ICA(HYDROCAS_CCC,IA)) = GKFX(YYY,IA,G) + HYDROPOWER_GKFX(IA,G,YYY);


PARAMETER INLFOWADJUST(AAA)   'inflow adjustments for scenario'  ;

*INLFOWADJUST(AAA)$INLFOWADJUST(AAA)  = 1;
INLFOWADJUST('NO1_A1') = 1;
