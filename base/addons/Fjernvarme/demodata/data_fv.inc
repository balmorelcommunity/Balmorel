* File data_fv.inc to the addon "District hearting".

PARAMETER NETINVESTED(AAA,AAA,STEPP) 'Percentatage of possible expansion performed';

$ifi %USENETINVESTED%==yes execute_load '../printout/NETINVESTED.gdx',NETINVESTED=NETINVESTED;

Table DHFV(AAA,STEPFV)   'Heat demand in extention areas GWh'
* Scenario: 20 pct heat savings
                 STEPFV1         STEPFV2         STEPFV3         STEPFV4         STEPFV5         STEPFV6         STEPFV7         STEPFV8         STEPFV9
DK_E_1_IND       0.04750         0.01094         0.05543         0.06216         0.03737         0.03104         0.03541         0.04080         0.06990
DK_E_2_IND       0.06361         0.03578         0.05736         0.07187         0.04657         0.04195         0.04577         0.06043         0.08407
DK_E_3_IND       0.00654         0.00706         0.00799         0.00972         0.01225         0.00779         0.00512         0.00820         0.00752
DK_E_4_IND       0.02412         0.02392         0.02904         0.04372         0.02221         0.02288         0.02927         0.03421         0.05038
DK_E_5_IND       0.02289         0.02222         0.02006         0.02503         0.01249         0.01369         0.01273         0.01234         0.01821
DK_E_Rural_IND   0.01124         0.00769         0.01028         0.00730         0.00531         0.00344         0.00316         0.00312         0.00460
DK_E_Urban_IND   0.57664         0.43643         0.50292         0.20579         0.26225         0.29678         0.33728         0.36011         0.50862
DK_W_1_IND       0.08336         0.09985         0.19439         0.21012         0.20216         0.18581         0.15126         0.15307         0.18914
DK_W_2_IND       0.03109         0.01998         0.03903         0.01550         0.04920         0.04447         0.02479         0.02246         0.02230
DK_W_3_IND       0.01407         0.00613         0.00974         0.00871         0.01011         0.00927         0.00723         0.00555         0.00621
DK_W_4_IND       0.00187         0.00375         0.00015         0.00446         0.00286         0.00320         0.00220         0.00183         0.00162
DK_W_5_IND       0.00584         0.01138         0.00970         0.000001        0.03597         0.01647         0.02384         0.01699         0.01361
DK_W_6_IND       0.00561         0.00460         0.00729         0.00478         0.00826         0.00424         0.00409         0.00395         0.00476
DK_W_ODENSE_IND  0.09835         0.04973         0.02396         0.03022         0.02682         0.03032         0.03135         0.03504         0.05089
DK_W_Rural_IND   0.09881         0.09114         0.03798         0.09207         0.07854         0.04839         0.03687         0.04222         0.05377
DK_W_TREFOR_IND  0.11307         0.05749         0.11527         0.06082         0.04306         0.04493         0.04679         0.04355         0.05418
DK_W_Urban_IND   0.04070         0.00964         0.01595         0.01024         0.00792         0.01250         0.00793         0.01254         0.00498
DK_W_AALBORG_IND 0.10008         0.04200         0.02073         0.01624         0.01425         0.00973         0.00970         0.01125         0.01415
DK_W_AARHUS_IND  0.01870         0.09573         0.01133         0.05277         0.04696         0.01962         0.02094         0.01365         0.01984
DK_E_PUREDH_IND  0.01375         0.01941         0.02157         0.04151         0.03817         0.02578         0.03013         0.01710         0.01976
DK_W_PUREDH_IND  0.03976         0.05612         0.06236         0.11999         0.11035         0.07454         0.08709         0.04942         0.05714


PARAMETER HEATPEAK(AAA);

HEATPEAK(AIND) = DH('2010',AIND)*SMAX((S,T), DH_VAR_T(AIND,S,T))/IDH_SUMST(AIND);

* Table currently in mDKK06/GWh
Table PHFV(AAA,STEPFV)   'Price of head extention areas'
* These price data are given in mDKK06/GWh/year (converted by assignment below).
                 STEPFV1      STEPFV2      STEPFV3      STEPFV4      STEPFV5      STEPFV6      STEPFV7      STEPFV8      STEPFV9
DK_E_1_IND         1.021        1.504        1.988        2.471        2.955        3.438        3.922        4.405        4.889
DK_E_2_IND         0.833        1.266        1.699        2.131        2.564        2.997        3.430        3.862        4.295
DK_E_3_IND         0.970        1.287        1.604        1.921        2.238        2.555        2.872        3.189        3.506
DK_E_4_IND         0.856        1.330        1.804        2.278        2.752        3.226        3.700        4.174        4.649
DK_E_5_IND         1.109        1.525        1.941        2.357        2.773        3.190        3.606        4.022        4.438
DK_E_Rural_IND     1.420        1.819        2.218        2.618        3.017        3.416        3.815        4.214        4.613
DK_E_Urban_IND     1.000        1.655        2.310        2.965        3.620        4.275        4.930        5.586        6.241
DK_W_1_IND         0.469        0.772        1.076        1.379        1.682        1.985        2.288        2.591        2.894
DK_W_2_IND         0.445        0.667        0.889        1.111        1.333        1.555        1.776        1.998        2.220
DK_W_3_IND         0.429        0.663        0.896        1.129        1.363        1.596        1.829        2.063        2.296
DK_W_4_IND         0.754        0.957        1.161        1.365        1.569        1.772        1.976        2.180        2.384
DK_W_5_IND         0.306        0.476        0.647        0.817        0.987        1.158        1.328        1.498        1.669
DK_W_6_IND         0.873        1.164        1.456        1.747        2.039        2.330        2.622        2.913        3.204
DK_W_ODENSE_IND    1.107        1.668        2.229        2.789        3.350        3.911        4.472        5.032        5.593
DK_W_Rural_IND     0.453        0.694        0.934        1.175        1.415        1.656        1.896        2.136        2.377
DK_W_TREFOR_IND    0.731        1.107        1.483        1.858        2.234        2.610        2.986        3.361        3.737
DK_W_Urban_IND     0.841        0.987        1.134        1.280        1.427        1.574        1.720        1.867        2.013
DK_W_AALBORG_IND   0.866        1.147        1.428        1.710        1.991        2.272        2.554        2.835        3.116
DK_W_AARHUS_IND    0.964        1.217        1.471        1.724        1.978        2.231        2.485        2.738        2.992
DK_E_PUREDH_IND    0.616        0.890        1.163        1.437        1.711        1.985        2.259        2.533        2.807
DK_W_PUREDH_IND    0.616        0.890        1.163        1.437        1.711        1.985        2.259        2.533        2.807

* Conversion from mDKK06/GWh/year to EUR90/MWh/year.
PHFV(AIND,STEPFV)=PHFV(AIND,STEPFV)/10.42*1000000/1000;


TABLE   DHCD(AAA,TECH)
                      NAT       OLIE
DK_E_1_IND            214351    250684
DK_E_2_IND            335212    313807
DK_E_3_IND            15533     68172
DK_E_4_IND            207404    167164
DK_E_5_IND            53036     127590
DK_E_Rural_IND        10865     39420
DK_E_Urban_IND        2377965   2301916
DK_W_1_IND            727438    1045574
DK_W_2_IND            110752    214327
DK_W_3_IND            46598     48468
DK_W_4_IND            1999      19571
DK_W_5_IND            26147     114057
DK_W_6_IND            31083     25226
DK_W_ODENSE_IND       211753    189870
DK_W_Rural_IND        309799    367115
DK_W_TREFOR_IND       340962    337724
DK_W_Urban_IND        10257     80602
DK_W_AALBORG_IND      68486     129430
DK_W_AARHUS_IND       35172     255720

DK_E_IND             564        11212
DK_W_IND             5680       18794
DK_E_PUREDH_IND      249        1133
DK_W_PUREDH_IND      291        194
;

Parameter HPRATIO(YYY)/
2010           0
2010           0
2011        0.07
2012        0.14
2013        0.21
2014        0.28
2015        0.35
2016        0.42
2017        0.49
2018        0.56
2019        0.63
2020        0.7
2021        0.73
2022        0.76
2023        0.79
2024        0.82
2025        0.85
2026        0.88
2027        0.91
2028        0.94
2029        0.97
2030           1
2031           1
2032           1
2033           1
2034           1
2035           1
2036           1
2037           1
2038           1
2039           1
2040           1
2041           1
2042           1
2043           1
2044           1
2045           1
2046           1
2047           1
2048           1
2049           1
2050           1
/;

PARAMETER HEATGROWTH(AAA,YYY);

HEATGROWTH(AIND,YYY)=DH(YYY,AIND)/DH('2010',AIND);

PARAMETER DHCD_SUM(AAA);

DHCD_SUM(AIND) = SUM(TECH, DHCD(AIND,TECH));


GKFX('2010',AIND,'HO-IND1-NG')$DHCD_SUM(AIND) = DHCD(AIND,'NAT')/DHCD_SUM(AIND)*HEATPEAK(AIND);
GKFX('2010',AIND,'HO-IND1-LO')$DHCD_SUM(AIND) = DHCD(AIND,'OLIE')/DHCD_SUM(AIND)*HEATPEAK(AIND);

*GKFX(YYY,AIND,G)$(YVALUE(YYY) > 2010 and GKFX('2010',AIND,G)) = max(0, GKFX('2010',AIND,G)-(YVALUE(YYY)-YVALUE('2010'))*GKFX('2010',AIND,G)/GDATA(G,'GDLIFETIME') );
GKFX(YYY,AIND,G)$(YVALUE(YYY) > 2010 and GKFX('2010',AIND,G)) = GKFX('2010',AIND,G)*(1- HPRATIO(YYY))*HEATGROWTH(AIND,YYY);
GKFX(YYY,AIND,'EH-IND1-GV')$(YVALUE(YYY) > 2010 ) = HPRATIO(YYY)*HEATGROWTH(AIND,YYY)*HEATPEAK(AIND);


FKPOT(AIND,'NAT_GAS') = GKFX('2008',AIND,'HO-IND1-NG');


























