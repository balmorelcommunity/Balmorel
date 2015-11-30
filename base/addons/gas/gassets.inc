


$ifi %MR%==yes SET MRAREAS(AAA) /
$ifi %MR%==yes $include '../../base/addons/gas/MRareas.inc';
$ifi %MR%==yes DK_W_Urban
$ifi %MR%==yes DK_W_Rural
$ifi %MR%==yes DK_W_Odense
$ifi %MR%==yes DK_W_Trefor
$ifi %MR%==yes DK_W_Aarhus
$ifi %MR%==yes DK_W_Aalborg
$ifi %MR%==yes DK_E_Urban
$ifi %MR%==yes DK_E_Rural
$ifi %MR%==yes /;




ALIAS(AAA,NODE,i,j,NODES);

SETS    DDD                "Regional NAT_GAS Distribution",
        NODEDATASET        "MR Station specific datatypes"
;

SETS    DDDAAA(DDD,AAA)    "MR Stations in distribution area",
        RRRDDD(RRR, DDD)   "NAT_GAS Distribution areas in region";

SETS    DDD        "Regional NAT_GAS Distribution"
        /       DONG_VEST,
                MIDT_NORD,
                NGF,
                DONG_OEST,
                HNG,
                SE_S_DIST
        /;

SETS    RRRDDD(RRR,DDD) "NAT_GAS Distribution areas in region"
        /       DK_E.(DONG_OEST,HNG),
                DK_W.(DONG_VEST,MIDT_NORD,NGF)
        /;

* Depending on geografical resolution different areas (MR) much be contained in
* the distribition areas.
$ifi %MR%==yes $goto MRDist
SETS    DDDNODE(DDD,AAA)       "MR Stations in distribution area"
/
        MIDT_NORD.(DK_W_Urban, DK_W_AALBORG,DK_W_AARHUS,DK_W_1, DK_W_Rural),
        DONG_VEST.(DK_W_TREFOR,DK_W_2),
        NGF.(DK_W_ODENSE),
        DONG_OEST.(DK_E_2,DK_E_1,DK_E_Rural),
        HNG.(DK_E_Urban )
        SE_S_DIST.SE_S_Rural
/;
$goto end_dist
$Label MRDist
SETS    DDDNODE(DDD,AAA)       "MR Stations in distribution area"
/
        MIDT_NORD.(BRANDE, ELLIDSHOEJ, HAVERSLEV, HERNING, KARUP, LITORUP, VIBORG, AALBORG),
        DONG_VEST.(EGTVED,ELLUND,HELLE,LILBALLE,LISELSKAER,NYBRO,NOERSKOV,POTTEHUSE,STANDST,TAULOV,TERKELSBOEL,FROESLEV),
        NGF.(MIDDELFART,BILLESBOELLE,KOELBJERG,HOEJBY,ULLERSLEV,NYBORG),
        DONG_OEST.(SLAGELSE,SOROE,RINGSTED,STENLILLE),
        HNG.(BROENDBY,DRAGOER,KARLSLUNDE,KOEGE,LYNGE,MAALOEV,TORSLUNDE,VALLENSBAEK,SYDHAVNEN,AMAGERF)
        SE_S_Dist.SE_S_Rural
/;
$label end_dist

SETS    NODEDATASET         "MR Station specific datatypes"
        /
                X
                Y
                Capacity
                PRESSURE
        /;


* The following will probably not be implemented.

$ifi %MR%==yes SET NOTMR(AAA)/ DK_E_Urban, DK_W_Odense, DK_W_TREFOR/;


$ifi NOT %HEATING%==yes $goto end_heat
SET HEAT(AAA) /
VEKS_V
CTR_V
VFORBRANDING_V
NFORBRANDING_V
AALBORG_V
AARHUS_V
ODENSE_V
HERNING_V
TVIS_V
/;
ALIAS(HEAT,HEAT2);

SET HX(i,j) /
VEKS_V.CTR_V
VEKS_V.VFORBRANDING_V
CTR_V.VEKS_V
CTR_V.VFORBRANDING_V
VFORBRANDING_V.CTR_V
VFORBRANDING_V.VEKS_V
/;

SET HEATMR(HEAT,AAA)/
VEKS_V.(TORSLUNDE),
CTR_V.(HCOERSTED),
VFORBRANDING_V.(VALLENSBAEK)
NFORBRANDING_V.(LYNGE)
AALBORG_V.(AALBORG, ELLIDSHOEJ)
AARHUS_V.(HERNING)
ODENSE_V.(HOEJBY)
HERNING_V.(HERNING)
TVIS_V.(TAULOV, SKAERBAEK)
/;

SETS
    IHX(i,j)
    ;

IHX(i,j)=YES$(HEAT(i)*HEAT(j)*HX(i,j));
$label end_heat



SET SOURCE(AAA)
/
NYBRO
OERESUND
ELLUND
/;

SET TRANSIT(AAA)
/
OERESUND
/;


SET STORE(AAA)
/
STENLILLE
LITORUP
SE_S_RURAL
/;

$ifi %MR%==yes SET GGGMR(GGG) /
$ifi %MR%==yes $include '../../base/addons/gas/GGGMRset.inc';
$ifi %MR%==yes /;

SET SYSENTRY
/
Nybro
Ellund
Oresund
/;

SET SYSEXIT
/
Oeresund
Ellund
DK-EXIT
/;





* ----- Storage ------*
SET        SCON                 /        STORE1,
                                         STORE2/;

SET        SCONDATASET
/
VOLCAP       'Volume capacity in the storage facilities'
INJCAP       'Injection capcity'
EXTCAP       'Withdrawal capacity'
TARRIF       'Package tarrif'
/;


SET DAY 'Days of the week'
/
MONDAY
TUESDAY
WEDNESDAY
THURSDAY
FRIDAY
SATURDAY
SUNDAY
/;

SET DAYT 'Hours to days relationship'
/
          MONDAY.(T1*T24),
          TUESDAY.(T25*T48),
          WEDNESDAY.(T49*T72),
          THURSDAY.(T73*T96),
          FRIDAY.(T97*T130),
          SATURDAY.(T131*T154),
          SUNDAY.(T155*T168)
/;


* Definition of individual steps in the residual gas demand function:

SET DGRESF  'Steps in elastic residual gas demand'
/ DGRESF_D1_9,DGRESF_D1_8,DGRESF_D1_7,DGRESF_D1_6,DGRESF_D1_5,DGRESF_D1_4,DGRESF_D1_3,DGRESF_D1_2,DGRESF_D1_1,
  DGRESF_U1_1,DGRESF_U1_2,DGRESF_U1_3,DGRESF_U1_4,DGRESF_U1_5,DGRESF_U1_6,DGRESF_U1_7,DGRESF_U1_8,DGRESF_U1_9,
  DGRESF_D2_9,DGRESF_D2_8,DGRESF_D2_7,DGRESF_D2_6,DGRESF_D2_5,DGRESF_D2_4,DGRESF_D2_3,DGRESF_D2_2,DGRESF_D2_1,
  DGRESF_U2_1,DGRESF_U2_2,DGRESF_U2_3,DGRESF_U2_4,DGRESF_U2_5,DGRESF_U2_6,DGRESF_U2_7,DGRESF_U2_8,DGRESF_U2_9
/;




* Definition of subsets of steps for regulation downwards (decreased demand)
* and upwards (increased demands) of electricity demand:

SET DGRESF_D1(DGRESF) 'Downwards steps in elastic residual gas demand, relative data format'
/
*DGRESF_D1_9,DGRESF_D1_8,DGRESF_D1_7,DGRESF_D1_6,DGRESF_D1_5,DGRESF_D1_4,DGRESF_D1_3,DGRESF_D1_2,DGRESF_D1_1
/;

SET DGRESF_U1(DGRESF) 'Upwards steps in elastic residual gas demand, relative data format'
/
*DGRESF_U1_1,DGRESF_U1_2,DGRESF_U1_3,DGRESF_U1_4,DGRESF_U1_5,DGRESF_U1_6,DGRESF_U1_7,DGRESF_U1_8,DGRESF_U1_9
/;

SET DGRESF_D2(DGRESF) 'Downwards steps in elastic residual gas demand, absolute and MW-incremental data format'
/
* DGRESF_D2_9,DGRESF_D2_8,DGRESF_D2_7,DGRESF_D2_6,DGRESF_D2_5,DGRESF_D2_4,DGRESF_D2_3,DGRESF_D2_2,DGRESF_D2_1
/;

SET DGRESF_U2(DGRESF) 'Upwards steps in elastic residual gas demand, absolute and MW-incremental data format'
/
* DGRESF_U2_1,DGRESF_U2_2,DGRESF_U2_3,DGRESF_U2_4,DGRESF_U2_5,DGRESF_U2_6,DGRESF_U2_7,DGRESF_U2_8,DGRESF_U2_9
/;


* Definition of individual steps in the other large consumers gas demand function:

SET DGOTHF  'Steps in elastic other large consumers gas demand'
/ DGOTHF_D1_9,DGOTHF_D1_8,DGOTHF_D1_7,DGOTHF_D1_6,DGOTHF_D1_5,DGOTHF_D1_4,DGOTHF_D1_3,DGOTHF_D1_2,DGOTHF_D1_1,
  DGOTHF_U1_1,DGOTHF_U1_2,DGOTHF_U1_3,DGOTHF_U1_4,DGOTHF_U1_5,DGOTHF_U1_6,DGOTHF_U1_7,DGOTHF_U1_8,DGOTHF_U1_9,
  DGOTHF_D2_9,DGOTHF_D2_8,DGOTHF_D2_7,DGOTHF_D2_6,DGOTHF_D2_5,DGOTHF_D2_4,DGOTHF_D2_3,DGOTHF_D2_2,DGOTHF_D2_1,
  DGOTHF_U2_1,DGOTHF_U2_2,DGOTHF_U2_3,DGOTHF_U2_4,DGOTHF_U2_5,DGOTHF_U2_6,DGOTHF_U2_7,DGOTHF_U2_8,DGOTHF_U2_9
/;




* Definition of subsets of steps for regulation downwards (decreased demand)
* and upwards (increased demands) of electricity demand:

SET DGOTHF_D1(DGOTHF) 'Downwards steps in elastic other large consumers gas demand, relative data format'
/
*DGOTHF_D1_9,DGOTHF_D1_8,DGOTHF_D1_7,DGOTHF_D1_6,DGOTHF_D1_5,DGOTHF_D1_4,DGOTHF_D1_3,DGOTHF_D1_2,DGOTHF_D1_1
/;

SET DGOTHF_U1(DGOTHF) 'Upwards steps in elastic other large consumers gas demand, relative data format'
/
*DGOTHF_U1_1,DGOTHF_U1_2,DGOTHF_U1_3,DGOTHF_U1_4,DGOTHF_U1_5,DGOTHF_U1_6,DGOTHF_U1_7,DGOTHF_U1_8,DGOTHF_U1_9
/;

SET DGOTHF_D2(DGOTHF) 'Downwards steps in elastic other large consumers gas demand, absolute and MW-incremental data format'
/
* DGOTHF_D2_9,DGOTHF_D2_8,DGOTHF_D2_7,DGOTHF_D2_6,DGOTHF_D2_5,DGOTHF_D2_4,DGOTHF_D2_3,DGOTHF_D2_2,DGOTHF_D2_1
/;

SET DGOTHF_U2(DGOTHF) 'Upwards steps in elastic other large consumers gas demand, absolute and MW-incremental data format'
/
* DGOTHF_U2_1,DGOTHF_U2_2,DGOTHF_U2_3,DGOTHF_U2_4,DGOTHF_U2_5,DGOTHF_U2_6,DGOTHF_U2_7,DGOTHF_U2_8,DGOTHF_U2_9
/;

$ifi %PIPELINE%==yes $include '../../base/addons/gas/flowsets.inc';


SET
   IMONTH /JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC/;

PARAMETER IMONTH_W(IMONTH)
/
JAN       31,
FEB       28,
MAR       31,
APR       30,
MAY       31,
JUN       30,
JUL       31,
AUG       31,
SEP       30,
OCT       31,
NOV       30,
DEC       31
/;
ALIAS(IMONTH,IMONTHALIAS)
PARAMETER IFROMDAY(IMONTH),
          ITODAY(IMONTH);

IFROMDAY(IMONTH)=sum(IMONTHALIAS$(ord(IMONTH)<ord(IMONTHALIAS)), IMONTH_W(IMONTH));
ITODAY(IMONTH)=sum(IMONTHALIAS$(ord(IMONTH)<=ord(IMONTHALIAS)), IMONTH_W(IMONTH));

SET IWHEN(IMONTH,SSS,DAY);
IWHEN(IMONTH,SSS,DAY)$(IFROMDAY(IMONTH) < ord(DAY) + 7*ord(SSS) and ord(DAY) + 7*ord(SSS) < ITODAY(IMONTH)) = YES;

SET MONTHSSS(IMONTH,SSS)
/
JAN.(S01,S02,S03,S04)
FEB.(S05,S06,S07,S08)
MAR.(S09,S10,S11,S12,S13)
APR.(S14,S15,S16,S17)
MAY.(S18,S19,S20,S21,S22)
JUN.(S23,S24,S25,S26)
JUL.(S27,S28,S29,S30)
AUG.(S31,S32,S33,S34,S35)
SEP.(S36,S37,S38,S39)
OCT.(S40,S41,S42,S43)
NOV.(S44,S45,S46,S47,S48)
DEC.(S49,S50,S51,S52)
/;

PARAMETER
         MONTHSCALE(IMONTH) "Scales monthly prices to time acctually in month"
         ;
MONTHSCALE(IMONTH) =  sum(SSS$MONTHSSS(IMONTH,SSS),7)/IMONTH_W(IMONTH);

SET NGINV0   /BGI, NO_SYDARNE, NO_NYBRO, NO_TYRA, DK_COMPR, NEGP_ELLUND/;
SET NGINV(NGINV0)    /NO_SYDARNE, NO_NYBRO, DK_COMPR/;
*SET NGINV(NGINV0)    //;

SET STORETYPE /Aquifer, Cavern, LNG, Dep_Field/;

SET STOREINV(STORE, STORETYPE);

SET GNETSTEPS0 /GNETSTEP1*GNETSTEP3/;

SET GNETSTEPS(GNETSTEPS0) /GNETSTEP1/;

SET gasanvendelser "FROM MDB2GMS" /
'Centralt kraftværk'
'Andre timeaflæste'
'Decentral kraftvarme'
'Decentral ren varmeproduktion'
Fjernvarmekedeler
'Industriel andet formål'
'Industriel kraftvarme'
residual
/;