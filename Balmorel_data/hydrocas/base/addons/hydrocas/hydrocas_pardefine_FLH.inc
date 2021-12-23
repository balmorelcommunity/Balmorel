



$if     EXIST '../data/HYDROCAS_HDATASET_FLH.inc' $INCLUDE         '../data/HYDROCAS_HDATASET_FLH.inc';
$if not EXIST '../data/HYDROCAS_HDATASET_FLH.inc' $INCLUDE '../../base/data/HYDROCAS_HDATASET_FLH.inc';

$if     EXIST '../data/HYDROCAS_HDATA_FLH.inc' $INCLUDE         '../data/HYDROCAS_HDATA_FLH.inc';
$if not EXIST '../data/HYDROCAS_HDATA_FLH.inc' $INCLUDE '../../base/data/HYDROCAS_HDATA_FLH.inc';

$if     EXIST '../data/HYDROCAS_TRANSFER_FLH.inc' $INCLUDE         '../data/HYDROCAS_TRANSFER_FLH.inc';
$if not EXIST '../data/HYDROCAS_TRANSFER_FLH.inc' $INCLUDE '../../base/data/HYDROCAS_TRANSFER_FLH.inc';

$if     EXIST '../data/HYDROCAS_HMINLEVELS_FLH.inc' $INCLUDE         '../data/HYDROCAS_HMINLEVELS_FLH.inc';
$if not EXIST '../data/HYDROCAS_HMINLEVELS_FLH.inc' $INCLUDE '../../base/data/HYDROCAS_HMINLEVELS_FLH.inc';

$if     EXIST '../data/HYDROCAS_INFLOW_FLH.inc' $INCLUDE         '../data/HYDROCAS_INFLOW_FLH.inc';
$if not EXIST '../data/HYDROCAS_INFLOW_FLH.inc' $INCLUDE '../../base/data/HYDROCAS_INFLOW_FLH.inc';

$if     EXIST '../data/HYDROCAS_GKFX_FLH.inc' $INCLUDE         '../data/HYDROCAS_GKFX_FLH.inc';
$if not EXIST '../data/HYDROCAS_GKFX_FLH.inc' $INCLUDE '../../base/data/HYDROCAS_GKFX_FLH.inc';

$onmulti
$if     EXIST '../data/HYDROCAS_GKRATE_FLH.inc' $INCLUDE         '../data/HYDROCAS_GKRATE_FLH.inc';
$if not EXIST '../data/HYDROCAS_GKRATE_FLH.inc' $INCLUDE '../../base/data/HYDROCAS_GKRATE_FLH.inc';
$offmulti

$if     EXIST '../data/HYDROCAS_RATES_FLH.inc' $INCLUDE         '../data/HYDROCAS_RATES_FLH.inc';
$if not EXIST '../data/HYDROCAS_RATES_FLH.inc' $INCLUDE '../../base/data/HYDROCAS_RATES_FLH.inc';


* Replace hydropower capacity with newly defined ones
HYRSDATA(IA,HYRSDATASET,S)$SUM(HYDROCAS_CCC, ICA(HYDROCAS_CCC,IA)) = 0;
WTRRRVAR_T(IA,S,T)$SUM(HYDROCAS_CCC, ICA(HYDROCAS_CCC,IA)) = 0;

GKRATE(IA,G,S)$(SUM(HYDROCAS_CCC, ICA(HYDROCAS_CCC,IA)) AND SUM(Y, HYDROCAS_GKFX(IA,G,Y)) AND GDATA(G,'GDTYPE') EQ GHYRS AND NOT GKRATE(IA,G,S)) =1;
GKRATE(IA,G,S)$(SUM(HYDROCAS_CCC, ICA(HYDROCAS_CCC,IA)) AND SUM(Y, HYDROCAS_GKFX(IA,G,Y)) AND GDATA(G,'GDTYPE') EQ GHYRS) =  HDATA(G,'HDGKRATEBASE') * GKRATE(IA,G,S);

HMINLEVELS(G,S)$(HDATA(G,'HDRESERVOIR') AND (HMINLEVELS(G,S) < 0.8)) = 0.2;
HMINLEVELS(G,S)$(HDATA(G,'HDRESERVOIR') AND (HMINLEVELS(G,S) = 0.8)) = 0.85;


PARAMETER HYDROCAS_HSEG_VOC(HSEG)   'price steps for hydropower segments'
/
1        0
2        2.5
3        5
4        7.5
/;


PARAMETER INLFOWADJUST(AAA)   'inflow adjustments for wet scenario'
/
NO1_A1        0.827676263
NO2_A1        1.086784264
NO3_A1        0.991855418
NO4_A1        0.979106842
NO5_A1        1.251382545
/;


INLFOWADJUST(AAA)$INLFOWADJUST(AAA)  = 1;
