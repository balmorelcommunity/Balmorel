*---------------------------------------------------------
* File      : ../SIMDATA/NETWORK.INC
* Author    :
* Version   : 1.0
* Remarks   :
* Date      : 16/09/2005 11:43:56
* Changed   : 28/10/2005 10:55:14
* Changed by:
*---------------------------------------------------------
$eolcom #







TABLE           NODEDATA(NODES,NODEDATASET)
                X       Y       Capacity        Pressure
*               coord   coord   kNm3/h          min Deliv
AMAGERF         10967   681     18              45
AVEDOERE        10503   597     1000            0
BILLESBOELLE    4457    -66     10              45
BRANDE          2989    2349    6               45
BROENDBY        10437   917     88              45
DRAGOER         10840   457     16              45
EGTVED          2520    981     64              45
ELLIDSHOEJ      3876    4182    38              45
ELLUND          2600    -1840   44              45
HAVERSLEV       3576    3862    22              45
HCOERSTED       10967   681     1000            45
HELLE           1480    997     10              45
HERNING         3020    2597    134             45
HOEJBY          5600    -343    116             45
HVIDOVRE        10592   842                     45
KARLSLUNDE      9860    397     60              45
KARUP           3187    3002    22              45
KOEGE           9740    137     38              45
KOELBJERG       4742    -187    38              45
LILBALLE        3300    697     10              45
LISELSKAER      2366    -303    38              45
LITORUP         3407    3557    6               45
LYNGE           10160   1697    92              45
MIDDELFART      4065    100     10              45
MAALOEV         10040   1377    80              45
NOERSKOV        2900    1818    22              45
NYBORG          6380    -223    10              45
NYBRO           482     895     6               45
OERESUND        11363   391                     45
POTTEHUSE       2379    45      20              45
RINGSTED        8969    24      50              45
SKAERBAEK       3329    243     1000            45
SLAGELSE        7660    -23     28              45
SOROE           8330    83      28              45
STANDST         2420    277     38              45
STENLILLE       8700    497     50              45
SYDHAVNEN       10967   681     10              45
TAULOV          3600    477     22              45
TERKELSBOEL     2477    -1183   20              45
TORSLUNDE       10020   677     28              45
ULLERSLEV       5900    -323    14              45
VALLENSBAEK     10197   810     30              45
VARDE           1229    957     38              45
VESTAMAGER      10780   657                     45
VIBORG          3300    3297    112             45
AALBORG         4440    4817    110             45
DK_E_Rural      10000   -1000
DK_W_Rural      2000    4000


SET PRESSURE_REGU(i)
/
NYBRO
/;



PARAMETER
                INJ_MAX(i)              /       LITORUP         165,
                                                STENLILLE       110/,           # kNm3/time
                EXT_MAX(i)              /       LITORUP         600,            # kNm3/time
                                                STENLILLE       600/,           # kNm3/time
                STORAGE_MAX(i)          /       LITORUP         400000,                # kNm3
                                                STENLILLE       300000/;

PARAMETER       SUPPLY_MAX(i)           /       ELLUND          344,
                                                OERESUND        0,
                                                NYBRO           1040
                                        /,
                EXP_MAX(i)              /       ELLUND          344,
                                                OERESUND        286,
                                                NYBRO           0
                /;



PARAMETER       REGU_PRESSURE(i)        /       NYBRO           78/;

* ---------------------------------------- *
*       PIPES
* ---------------------------------------- *



TABLE EDGEDATA(e,EDGEDATASET)
                            L       WT      ID      KNOT   ROUGH        PRESSURE        LOSSFACT
*                           len(km)         dia(mm)        roughness    limit           c(e)
NYBRO_VARDE                 13.9    14      743.2          20           80              0.03
VARDE_HELLE                 12      14      743.2          20           80              0.03
HELLE_EGTVED                30.9    14      743.2          20           80              0.03
NYBRO_VARDE2                13.9    14      743.2          20           80              0.03
VARDE_EGTVED2               42.9    14      743.2          20           80              0.03
EGTVED_STANDST              12.8    14      594.6          20           80              0.03
STANDST_POTTEHUSE           5.3     14      594.6          20           80              0.03
POTTEHUSE_LISELSKAER        16.8    14      594.6          20           80              0.03
LISELSKAER_TERKELSBOEL      39.6    14      594.6          20           80              0.03
TERKELSBOEL_ELLUND          18.5    14      594.6          20           80              0.03
EGTVED_NOERSKOV             22.2    14      494            20           80              0.03
NOERSKOV_BRANDE             19.4    14      494            20           80              0.03
BRANDE_HERNING              21.7    14      494            20           80              0.03
HERNING_KARUP               21      14      494            20           80              0.03
KARUP_VIBORG                19.2    14      494            20           80              0.03
VIBORG_LITORUP              23.3    14      494            20           80              0.03
LITORUP_HAVERSLEV           23.1    14      342.8          20           80              0.03
HAVERSLEV_ELLIDSHOEJ        19      14      342.8          20           80              0.03
ELLIDSHOEJ_AALBORG          18.3    14      342.8          20           80              0.03
EGTVED_LILBALLE             18.1    14      743.2          20           80              0.03
LILBALLE_TAULOV             8.7     14      743.2          20           80              0.03
TAULOV_LYNGSODDE            6.7     14      743.2          20           80              0.03
LILLEBAELT_SYD              1.4     14      743.2   0.4    20           80              0.03
MIDDELFART_BILLESBOELLE     20.3    14      743.2          20           80              0.03
BILLESBOELLE_KOELBJERG      6.5     14      743.2          20           80              0.03
KOELBJERG_HOEJBY            28.7    14      743.2          20           80              0.03
HOEJBY_ULLERSLEV            12.6    14      743.2          20           80              0.03
ULLERSLEV_NYBORG            9.4     14      743.2          20           80              0.03
TAULOV_SKAERBAEK            3.5     14      245            20           80              0.03
STOREBAELTSYD               28.8    14      743.2          20           80              0.03
STORBAELTNORD               30.3    14      743.2          20           80              0.03
KONGSMARK_SLAGELSE          6.6     14      743.2          20           80              0.03
SLAGELSE_SOROE              17.2    14      743.2          20           80              0.03
SOROE_RINGSTED              17.1    14      743.2          20           80              0.03
RINGSTED_KOEGE              18      14      743.2          20           80              0.03
KOEGE_KARLSLUNDE            9.4     14      743.2          20           80              0.03
KARLSLUNDE_TORSLUNDE        6.6     14      743.2          20           80              0.03
TORSLUNDE_VALLENSBAEK       9.2     14      743.2          20           80              0.03
VALLENSBAEK_BROENDBY        2.9     14      743.2   0.4    20           80              0.03
BROENDBY_HVIDOVRE           4.7     14      743.2          20           80              0.03
HVIDOVRE_VESTAMAGER         2.8     14      743.2   0.4    20           80              0.03
TORSLUNDE_MAALOEV           15.2    14      392.4          20           80              0.03
MAALOEV_LYNGE               10.3    14      392.4          20           80              0.03
TORSLUNDE_STENLILLE         43.1    14      594.6          20           80              0.03
VESTAMAGER_DRAGOER          8.8     14      743.2          20           80              0.03
LILLEBAELT_NORD             1.3     14      743.2   0.4    20           80              0.03
HVIDOVRE_AVEDOERE           2.5     14      293.8          20           80              0.03
VESTAMAGER_AMAGERF          7.5     14      293.8          20           80              0.03
AMAGERF_SYDHAVNEN           0.2     14      293.8          20           80              0.03
SYDHAVNEN_HCOERSTED         0.1     14      293.8          20           80              0.03
DRAGOER_OERESUND            1.1     14      594.6          20           80              0.03



* ---------------------------------------- *
*       NETWORK
* ---------------------------------------- *

PARAMETER ARC_NODE_INC(e,i) /
NYBRO_VARDE             .NYBRO           1
NYBRO_VARDE             .VARDE            -1
VARDE_HELLE             .VARDE           1
VARDE_HELLE             .HELLE           -1
HELLE_EGTVED            .HELLE           1
HELLE_EGTVED            .EGTVED          -1
NYBRO_VARDE2            .NYBRO           1
NYBRO_VARDE2            .VARDE           -1
VARDE_EGTVED2           .VARDE           1
VARDE_EGTVED2           .EGTVED          -1
EGTVED_STANDST          .EGTVED          1
EGTVED_STANDST          .STANDST         -1
STANDST_POTTEHUSE       .STANDST         1
STANDST_POTTEHUSE       .POTTEHUSE       -1
POTTEHUSE_LISELSKAER    .POTTEHUSE       1
POTTEHUSE_LISELSKAER    .LISELSKAER      -1
LISELSKAER_TERKELSBOEL  .LISELSKAER      1
LISELSKAER_TERKELSBOEL  .TERKELSBOEL     -1
TERKELSBOEL_ELLUND      .TERKELSBOEL     1
TERKELSBOEL_ELLUND      .ELLUND          -1
EGTVED_NOERSKOV         .EGTVED          1
EGTVED_NOERSKOV         .NOERSKOV        -1
NOERSKOV_BRANDE         .NOERSKOV        1
NOERSKOV_BRANDE         .BRANDE          -1
BRANDE_HERNING          .BRANDE          1
BRANDE_HERNING          .HERNING          -1
HERNING_KARUP           .HERNING         1
HERNING_KARUP           .KARUP           -1
KARUP_VIBORG            .KARUP           1
KARUP_VIBORG            .VIBORG          -1
VIBORG_LITORUP          .VIBORG          1
VIBORG_LITORUP          .LITORUP         -1
LITORUP_HAVERSLEV       .LITORUP         1
LITORUP_HAVERSLEV       .HAVERSLEV       -1
HAVERSLEV_ELLIDSHOEJ    .HAVERSLEV       1
HAVERSLEV_ELLIDSHOEJ    .ELLIDSHOEJ      -1
ELLIDSHOEJ_AALBORG      .ELLIDSHOEJ      1
ELLIDSHOEJ_AALBORG      .AALBORG         -1
EGTVED_LILBALLE         .EGTVED          1
EGTVED_LILBALLE         .LILBALLE        -1
LILBALLE_TAULOV         .LILBALLE        1
LILBALLE_TAULOV         .TAULOV          -1
TAULOV_LYNGSODDE        .TAULOV          1
TAULOV_LYNGSODDE        .LYNGSODDE       -1
LILLEBAELT_SYD          .LYNGSODDE        1
LILLEBAELT_SYD          .MIDDELFART       -1
MIDDELFART_BILLESBOELLE .MIDDELFART      1
MIDDELFART_BILLESBOELLE .BILLESBOELLE    -1
BILLESBOELLE_KOELBJERG  .BILLESBOELLE    1
BILLESBOELLE_KOELBJERG  .KOELBJERG       -1
KOELBJERG_HOEJBY        .KOELBJERG       1
KOELBJERG_HOEJBY        .HOEJBY          -1
HOEJBY_ULLERSLEV        .HOEJBY          1
HOEJBY_ULLERSLEV        .ULLERSLEV       -1
ULLERSLEV_NYBORG        .ULLERSLEV       1
ULLERSLEV_NYBORG        .NYBORG          -1
TAULOV_SKAERBAEK        .TAULOV          1
TAULOV_SKAERBAEK        .SKAERBAEK       -1
STOREBAELTSYD           .NYBORG          1
STOREBAELTSYD           .KONGSMARK       -1
*STORBAELTNORD           .NYBORG          1
*STORBAELTNORD           .KONGSMARK       -1
KONGSMARK_SLAGELSE      .KONGSMARK       1
KONGSMARK_SLAGELSE      .SLAGELSE        -1
SLAGELSE_SOROE          .SLAGELSE         1
SLAGELSE_SOROE          .SOROE            -1
SOROE_RINGSTED          .SOROE           1
SOROE_RINGSTED          .RINGSTED        -1
RINGSTED_KOEGE          .RINGSTED        1
RINGSTED_KOEGE          .KOEGE           -1
KOEGE_KARLSLUNDE        .KOEGE           1
KOEGE_KARLSLUNDE        .KARLSLUNDE      -1
KARLSLUNDE_TORSLUNDE    .KARLSLUNDE      1
KARLSLUNDE_TORSLUNDE    .TORSLUNDE       -1
TORSLUNDE_VALLENSBAEK   .TORSLUNDE       1
TORSLUNDE_VALLENSBAEK   .VALLENSBAEK     -1
VALLENSBAEK_BROENDBY    .VALLENSBAEK     1
VALLENSBAEK_BROENDBY    .BROENDBY        -1
BROENDBY_HVIDOVRE       .BROENDBY        1
BROENDBY_HVIDOVRE       .HVIDOVRE        -1
HVIDOVRE_VESTAMAGER     .HVIDOVRE        1
HVIDOVRE_VESTAMAGER     .VESTAMAGER      -1
TORSLUNDE_MAALOEV       .TORSLUNDE       1
TORSLUNDE_MAALOEV       .MAALOEV         -1
MAALOEV_LYNGE           .MAALOEV         1
MAALOEV_LYNGE           .LYNGE           -1
TORSLUNDE_STENLILLE     .TORSLUNDE       1
TORSLUNDE_STENLILLE     .STENLILLE       -1
VESTAMAGER_DRAGOER      .VESTAMAGER      1
VESTAMAGER_DRAGOER      .DRAGOER         -1
*LILLEBAELT_NORD         .LYNGSODDE       1
*LILLEBAELT_NORD         .MIDDELFART      -1
HVIDOVRE_AVEDOERE       .HVIDOVRE        1
HVIDOVRE_AVEDOERE       .AVEDOERE        -1
VESTAMAGER_AMAGERF      .VESTAMAGER      1
VESTAMAGER_AMAGERF      .AMAGERF         -1
AMAGERF_SYDHAVNEN       .AMAGERF         1
AMAGERF_SYDHAVNEN       .SYDHAVNEN       -1
SYDHAVNEN_HCOERSTED     .SYDHAVNEN       1
SYDHAVNEN_HCOERSTED     .HCOERSTED       -1
DRAGOER_OERESUND        .DRAGOER         1
DRAGOER_OERESUND        .OERESUND        -1
/;

SET N(AAA,e),ARC(i,j), SEMIARC(e,i,j),NN(i,j);
N(IA,e) = YES$(ARC_NODE_INC(e,IA) ne 0) ;
SEMIARC(e,i,j)= YES$(ARC_NODE_INC(e,i)=1 and ARC_NODE_INC(e,j)=-1);
ARC(i,j)=YES$(sum(e$SEMIARC(e,i,j),1)>0);
NN(i,j) = YES$(ARC(i,j) or ARC(j,i));