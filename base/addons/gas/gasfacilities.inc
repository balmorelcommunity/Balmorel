*------------------------------------------------------------------------------*
*  Transmission posibilities
*------------------------------------------------------------------------------*

TABLE SUPPLY_MAX(YYY,SOURCE) 'Hourly exogenous natural gas supply capacity'
          Nybro           Ellund      Oeresund
2003      1002.029427     344         eps
2004      1059.107052     344         eps
2005      1116.184678     344         eps
2006      1116.184678     344         eps
2007      1116.184678     344         eps
2008      1116.184678     344         eps
2009      1116.184678     344         eps
2010      1116.184678     344         eps
2011      1045.154744     344         eps
2012      974.1248097     344         eps
2013      903.0948757     344         eps
2014      832.0649417     344         eps
2015      761.0350076     344         eps
2016      731.2278031     344         eps
2017      701.4205987     344         eps
2018      671.6133942     344         eps
2019      641.8061898     344         eps
2020      611.9989853     344         eps
2021      582.1917808     344         eps
2022      552.3845764     344         eps
2023      522.5773719     344         eps
2024      492.7701674     344         eps
2025      462.962963      344         eps
2026      462.962963      344         eps
2027      462.962963      344         eps
2028      462.962963      344         eps
2029      462.962963      344         eps
2030      462.962963      344         eps
*       2005.ELLUND          344,
*       2005.OERESUND        0,
*       2005.NYBRO           1040
;

TABLE EXP_MAX(YYY,SOURCE) 'Hourly exogenous natural gas export capacity'
            OERESUND     NYBRO    ELLUND
2005        286          303      344
2006        358          303      344
2007        358          303      344
2008        358          303      344
2009        358          303      344
2010        358          303      344
2011        358          303      344
2012        358          303      344
2013        358          303      344
2014        358          303      344
2015        358          303      344
2016        358          303      344
2017        358          303      344
2018        358          303      344
2019        358          303      344
2020        358          303      344
2021        358          303      344
2022        358          303      344
2023        358          303      344
2024        358          303      344
2025        358          303      344
2026        358          303      344
2027        358          303      344
2028        358          303      344
2029        358          303      344
2030        358          303      344
;

TABLE DEV_MAX(YYY,SYSEXIT) 'Hourly exogenous natural gas delivery capacity'
            DK-EXIT
2005        1191
2006        1191
2007        1191
2008        1191
2009        1191
2010        1191
2011        1191
2012        1191
2013        1191
2014        1191
2015        1191
2016        1191
2017        1191
2018        1191
2019        1191
2020        1191
2021        1191
2022        1191
2023        1191
2024        1191
2025        1191
2026        1191
2027        1191
2028        1191
2029        1191
2030        1191
;

DEV_MAX(YYY,SYSEXIT)     =  DEV_MAX(YYY,SYSEXIT)         * kNm3ToMWh;
SUPPLY_MAX(YYY,SOURCE)   =  SUPPLY_MAX(YYY,SOURCE)       * kNm3ToMWh;
EXP_MAX(YYY,SOURCE)      =  EXP_MAX(YYY,SOURCE)          * kNm3ToMWh;


* TAL FOR ELLUND FORSTÆRKELSE OG BGI KAPACITET ER TAGET UD AF LUFTEN

PARAMETER COST_NGINV(NGINV0) 'Investment costs'
/
* Investment cost in Bill. DKkr 2006
BGI          2.0
NO_SYDARNE   0.8
NO_NYBRO     1.2
NO_TYRA      0.8
DK_COMPR     0.255
NEGP_ELLUND  1.0
/;
* Omregning til EURO90
COST_NGINV(NGINV0)=1/(7.43)/(1.389)*1000*1000*1000*COST_NGINV(NGINV0);

PARAMETER GNET_COST(C,GNETSTEPS0) 'Marginal cost of gas transmissionnetwork expansion EURO90/(Unit expansion)'
* Data source: Kapacitetsudvidelse i transmissionssystemet - Simulering med Pipeline studio.
*              Den anvendte pris er en gennemsnitsværdi, da omkostningsstrukturen i notat er konkav kapacitetsforøgelsen.
*              Døgnbelastningsfaktor på 1.07 er anvendt til at skalere døgnmængder til timemængder.
*                        COST
*                        EURO90/MWh/h
/
Denmark.GNETSTEP1        28923
Denmark.GNETSTEP2        28923
Denmark.GNETSTEP3        28923
/;

PARAMETER GNET_MAX(C,GNETSTEPS0) 'Steplength for marginal expansion cost curve (Unit expansion)'
* Unit cost must be increasing with step number
* Data source: Kapacitetsudvidelse i transmissionssystemet - Simulering med Pipeline studio. (Energinet.dk)
*                        Max_Effect
*                        kNm3/d
/
Denmark.GNETSTEP1        4757
Denmark.GNETSTEP2        0
Denmark.GNETSTEP3        0
/;

TABLE GNET_DEV_EFFECT(C,SYSEXIT) 'Increased delivery capacity from network expansion (MWh/h)/(Unit expansion)'
               DK-EXIT
Denmark        1
;

TABLE GNET_EXP_EFFECT(C,SOURCE) 'Increased export capacity from network expansion (MWh/h)/(Unit expansion)'
               OERESUND
Denmark        1
;

TABLE DEVEFFECT(NGINV0,SYSEXIT) 'Increased delivery capacity from infrastrukture investments (MWh/h)'
                DK-EXIT
BGI             eps
NO_SYDARNE      eps
NO_NYBRO        eps
NO_TYRA         eps
DK_COMPR        1
NEGP_ELLUND     eps
;


TABLE SUPEFFECT(NGINV0,SOURCE)
* Additional hourly supply capacity gained from investment
                NYBRO     ELLUND  OERESUND
BGI             eps       eps     542
NO_SYDARNE      542       eps     eps
NO_NYBRO        1125      eps     eps
NO_TYRA         420       eps     eps
DK_COMPR        eps       eps     eps
NEGP_ELLUND     eps       378.84  eps
;
SUPEFFECT(NGINV0,SOURCE) = SUPEFFECT(NGINV0,SOURCE)*kNm3ToMWh;

TABLE EXPEFFECT(NGINV0,SOURCE)
* Additional hourly export capacity gained from investment MNm3/h
                NYBRO     ELLUND  OERESUND
BGI             eps       eps     542
NO_SYDARNE      eps       eps     eps
NO_NYBRO        eps       eps     eps
NO_TYRA         eps       eps     eps
DK_COMPR        eps       eps     200
NEGP_ELLUND     eps       eps     378.84
;
EXPEFFECT(NGINV0,SOURCE) = EXPEFFECT(NGINV0,SOURCE)*kNm3ToMWh;

*------------------------------------------------------------------------------*
*  STORAGE FACILITIES
*------------------------------------------------------------------------------*

TABLE INJ_MAX(YYY,STORE,STORETYPE)
* kNm3/h
        LITORUP.Cavern         STENLILLE.Aquifer
2005    165                    110
2006    165                    110
2007    165                    110
2008    165                    110
2009    165                    110
2010    165                    110
2011    165                    110
2012    165                    110
2013    165                    110
2014    165                    110
2015    165                    110
2016    165                    110
2017    165                    110
2018    165                    110
2019    165                    110
2020    165                    110
2021    165                    110
2022    165                    110
2023    165                    110
2024    165                    110
2025    165                    110
2026    165                    110
2027    165                    110
2028    165                    110
2029    165                    110
2030    165                    110
;

TABLE EXT_MAX(YYY,STORE,STORETYPE)
* kNm3/h
        LITORUP.Cavern       STENLILLE.Aquifer
2005    600                  600
2006    600                  600
2007    600                  600
2008    600                  600
2009    600                  600
2010    600                  600
2011    600                  600
2012    600                  600
2013    600                  600
2014    600                  600
2015    600                  600
2016    600                  600
2017    600                  600
2018    600                  600
2019    600                  600
2020    600                  600
2021    600                  600
2022    600                  600
2023    600                  600
2024    600                  600
2025    600                  600
2026    600                  600
2027    600                  600
2028    600                  600
2029    600                  600
2030    600                  600
;

TABLE STORAGE_MAX(YYY,STORE,STORETYPE)
* kNm3
        LITORUP.Cavern        STENLILLE.Aquifer
2005    400000                300000
2006    400000                300000
2007    400000                300000
2008    400000                300000
2009    400000                300000
2010    400000                300000
2011    400000                300000
2012    400000                300000
2013    400000                300000
2014    400000                300000
2015    400000                300000
2016    400000                300000
2017    400000                300000
2018    400000                300000
2019    400000                300000
2020    400000                300000
2021    400000                300000
2022    400000                300000
2023    400000                300000
2024    400000                300000
2025    400000                300000
2026    400000                300000
2027    400000                300000
2028    400000                300000
2029    400000                300000
2030    400000                300000
;


TABLE GSTOREDATA(STORETYPE,*) 'Storage investment data'
            INVCOST       FOMK         INJEFFECT    EXTEFFECT      ELECT     GAS        MargInjInvCost   MargExtInvCost
*           EURO02/kNm3   EURO02/kN3   -Ratio to volume capacity-  fraction  fraction   Marginal cost    Marginal cost
*                                                                  of INJ    of EXT     of inj capacity  of ext capacity
*                                                                                       EURO02/kNm3/h    EURO02/kNm3/h
Dep_Field    42.40        13           0.0002       0.0006         0.00341   0.002      10320            10320
Aquifer      49.10        15           0.0002       0.000458       0.00341   0.002      10560            10560
Cavern       83.90        11           0.00041      0.00198        0.0033    0.0009     10080            10080
LNG         150.60        45           0.0004557    0.00651        0.00526   0.00319    7104             7104
;

* INVCOST is the yearly annuity payment.
* DATASOURCES: The 2002 European Gas Storage Study, Lille Torup Naturgaslager - Grønt regnskab 2004,
*              Stenlille Naturgaslager - Grønt regnskab 2004

* Faktor 1.302272195 brug til omregning af EURO02 til EURO90
* Translate costs to EURO90/MWh
GSTOREDATA(STORETYPE,'INVCOST')        = GSTOREDATA(STORETYPE,'INVCOST')/1.302272195/kNm3ToMWh;
GSTOREDATA(STORETYPE,'MargInjInvCost') = GSTOREDATA(STORETYPE,'MargInjInvCost')/1.302272195/kNm3ToMWh;
GSTOREDATA(STORETYPE,'MargExtInvCost') = GSTOREDATA(STORETYPE,'MargExtInvCost')/1.302272195/kNm3ToMWh;
GSTOREDATA(STORETYPE,'FOMK')           = GSTOREDATA(STORETYPE,'FOMK')/1.302272195/kNm3ToMWh;

PARAMETER MAXINVEST(STORE,STORETYPE) 'Maximum possible capacity at storage location'
/
LITORUP.Cavern      300000
STENLILLE.Aquifer   100000
STENLILLE.Cavern    1000000
STENLILLE.LNG       1000000
SE_S_RURAL.LNG      1000000
/;
* Location of LNG investment in Denmark is irrelevant for the model.
* STENLILLE.Cavern repressents investment in a storage facility in Tønder. Location is irrelevant for model so no individual location node is defined.

PARAMETER  TSOSTORAGE(YYY,STORE,STORETYPE)  'Storage reserved for emergencies by the TSO';

TSOSTORAGE(Y,'Stenlille','Aquifer') = STORAGE_MAX(Y,'Stenlille','Aquifer')/sum((STORE,STORETYPE), STORAGE_MAX(Y,STORE,STORETYPE))*(sum((STORE,STORETYPE), STORAGE_MAX(Y,STORE,STORETYPE))-605000);
TSOSTORAGE(Y,'LiTorup','Cavern')    = STORAGE_MAX(Y,'LiTorup','Cavern')/sum((STORE,STORETYPE), STORAGE_MAX(Y,STORE,STORETYPE))*(sum((STORE,STORETYPE), STORAGE_MAX(Y,STORE,STORETYPE))-605000);

TSOSTORAGE(YYY,STORE,STORETYPE)    =  TSOSTORAGE(YYY,STORE,STORETYPE)     * kNm3ToMWh;
INJ_MAX(YYY,STORE,STORETYPE)       =  INJ_MAX(YYY,STORE,STORETYPE)        * kNm3ToMWh;
EXT_MAX(YYY,STORE,STORETYPE)       =  EXT_MAX(YYY,STORE,STORETYPE)        * kNm3ToMWh;
STORAGE_MAX(YYY,STORE,STORETYPE)   =  STORAGE_MAX(YYY,STORE,STORETYPE)    * kNm3ToMWh;