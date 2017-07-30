PARAMETER HYDROGEN_DH2(YYY,CCCRRRAAA)  'Yearly demand for hydrogen at a Regional level(MWh of H2)'

/

*------------------------------------------------------
*DATA THAT ARE SCENARIO DEPENDANT
*------------------------------------------------------
*W I N D    E N E R G Y    S C E N A R I O

*Hydrogen consumption for upgrading of BIOGAS in rural areas
*Demand is estimated according to the biogas potential for DK and
*assuming in East and West the same % of biogas is upgraded through methanation

2014   .   DK2_Rural       0
2014   .   DK1_Rural       0
2020   .   DK2_Rural       34806
2020   .   DK1_Rural       462426
2025   .   DK2_Rural       63811
2025   .   DK1_Rural       847780
2030   .   DK2_Rural       92817
2030   .   DK1_Rural       1233135
2035   .   DK2_Rural       121822
2035   .   DK1_Rural       1618490
2040   .   DK2_Rural       228982
2040   .   DK1_Rural       3042189
2045   .   DK2_Rural       336142
2045   .   DK1_Rural       4465889
2050   .   DK2_Rural       443302
2050   .   DK1_Rural       5889589


*Hydrogen consumption for biorefineries. Biorefinery distribution is exogenously given, following the indications of the FV modellen

2025   .   DK2_Large       480177
2025   .   DK1_Large       480177
2030   .   DK2_Large       911219
2030   .   DK1_Large       1009487
2035   .   DK2_Large       1327835
2035   .   DK1_Large       1553224
2040   .   DK2_Large       2465087
2040   .   DK2_Medium      81490
2040   .   DK1_Large       2825003
2040   .   DK1_Medium      101863
2045   .   DK2_Large       3569992
2045   .   DK2_Medium      196153
2045   .   DK1_Large       4056453
2045   .   DK1_Medium      243230
2050   .   DK2_Large       4676301
2050   .   DK2_Medium      315736
2050   .   DK1_Large       5273639
2050   .   DK1_Medium      392536

$ontext

*B I O M A S S    S C E N A R I O

2014   .   DK2_Rural       0
2014   .   DK1_Rural       0
2020   .   DK2_Rural       5142
2020   .   DK1_Rural       68313
2025   .   DK2_Rural       9427
2025   .   DK1_Rural       125241
2030   .   DK2_Rural       13712
2030   .   DK1_Rural       182168
2035   .   DK2_Rural       17996
2035   .   DK1_Rural       239096
2040   .   DK2_Rural       21329
2040   .   DK1_Rural       283373
2045   .   DK2_Rural       24662
2045   .   DK1_Rural       327650
2050   .   DK2_Rural       27995
2050   .   DK1_Rural       371927

$offtext

$ontext
*------------------------------------------------------
*DATA THAT ARE NOT SCENARIO DEPENDANT
*------------------------------------------------------

2014   .    DE_CS         0
2014   .    DE_NE         0
2014   .    DE_NW         0
2014   .    NO_M          0
2014   .    NO_N          0
2014   .    NO_O          0
2014   .    NO_S          0
2014   .    SE_M          0
2014   .    SE_N          0
2014   .    SE_S          0
2014   .    FI_R          0
2020   .    DE_CS         256651
2020   .    DE_NE         3777
2020   .    DE_NW         32497
2020   .    NO_M          6613
2020   .    NO_N          6613
2020   .    NO_O          12650
2020   .    NO_S          29117
2020   .    SE_M          95805
2020   .    SE_N          26156
2020   .    SE_S          24669
2020   .    FI_R          83805
2025   .    DE_CS         522973
2025   .    DE_NE         7696
2025   .    DE_NW         66218
2025   .    NO_M          10617
2025   .    NO_N          10617
2025   .    NO_O          20307
2025   .    NO_S          46742
2025   .    SE_M          148001
2025   .    SE_N          40406
2025   .    SE_S          38110
2025   .    FI_R          125939
2030   .    DE_CS         789295
2030   .    DE_NE         11615
2030   .    DE_NW         99939
2030   .    NO_M          14620
2030   .    NO_N          14620
2030   .    NO_O          27964
2030   .    NO_S          64366
2030   .    SE_M          200196
2030   .    SE_N          54655
2030   .    SE_S          51550
2030   .    FI_R          168073
2035   .    DE_CS         764709
2035   .    DE_NE         11253
2035   .    DE_NW         96826
2035   .    NO_M          24127
2035   .    NO_N          24127
2035   .    NO_O          46148
2035   .    NO_S          106222
2035   .    SE_M          193907
2035   .    SE_N          52938
2035   .    SE_S          49931
2035   .    FI_R          162793
2040   .    DE_CS         740123
2040   .    DE_NE         10891
2040   .    DE_NW         93713
2040   .    NO_M          33634
2040   .    NO_N          33634
2040   .    NO_O          64333
2040   .    NO_S          148078
2040   .    SE_M          187618
2040   .    SE_N          51221
2040   .    SE_S          48311
2040   .    FI_R          157513
2045   .    DE_CS         629423
2045   .    DE_NE         9262
2045   .    DE_NW         79697
2045   .    NO_M          54793
2045   .    NO_N          54793
2045   .    NO_O          104806
2045   .    NO_S          241238
2045   .    SE_M          108554
2045   .    SE_N          29636
2045   .    SE_S          27952
2045   .    FI_R          123797
2050   .    DE_CS         518723
2050   .    DE_NE         7633
2050   .    DE_NW         65680
2050   .    NO_M          75953
2050   .    NO_N          75953
2050   .    NO_O          145280
2050   .    NO_S          334398
2050   .    SE_M          29489
2050   .    SE_N          8051
2050   .    SE_S          7593
2050   .    FI_R          90081

$offtext 

/;
















