* LARS: kopieret fra var.inc. Tidsrækkerne her har 52 uger. Det andre som er udkommenteret havde
* 12 måneder.

*-------------
* PARAMETER WTRRSVAR_S contains the description of the seasonal variation of the
* amount of water inflow
* to the reservoirs for each installed MW capacity of hydropower with storage,
* Unit: (none)

* Observe: the table is specified directly in the present sheet.

* Data source:  Nordel

TABLE WTRRSVAR_S(AAA,SSS)  'Variation of the water inflow to reservoirs'
                 S01           S02           S03           S04           S05           S06           S07           S08
SE_N_Rural    870434        817799        757277        733767        822964        823203        834463        765678
NO_S_Rural   1450723       1362998       1262129       1222945       1371607       1372005       1390771       1276129

+                S09           S10           S11           S12           S13           S14           S15           S16
SE_N_Rural    853649        597501        557507        540084        464684        432662        430186        480870
NO_S_Rural   1422749        995835        929178        900140        774473        721103        716977        801451

+                S17           S18           S19           S20           S21           S22           S23           S24
SE_N_Rural    434677        520553        411666        688162        607012        330298        342297        219184
NO_S_Rural    724462        867588        686111       1146937       1011686        550496        570495        365307

+                S25           S26           S27           S28           S29           S30           S31           S32
SE_N_Rural    434041        296021        247570        375879        519256        488248        528843        560576
NO_S_Rural    723402        493369        412617        626466        865426        813747        881405        934294

+                S33           S34           S35           S36           S37           S38           S39           S40
SE_N_Rural    595472        491599        570678        588404        570755        582851        481280        569697
NO_S_Rural    992453        819332        951130        980673        951258        971418        802133        949495

+                S41           S42           S43           S44           S45           S46           S47           S48
SE_N_Rural    853638        783124        450189        825629        572255        598488        489413        528319
NO_S_Rural   1422729       1305206        750315       1376049        953758        997480        815688        880532

+                S49           S50           S51           S52
SE_N_Rural    566349        655690        810443        777368
NO_S_Rural    943915       1092817       1350738       1295614
;

WTRRSVAR_S(AAA,SSS)$(WTRRSVAR_S(AAA,SSS) EQ 0) = WTRRSVAR_S('NO_S_Rural',SSS) ;


*-------------


* LARS: Udkommenteret. Tidsrække for 12 måneder... ikke 52 uger.
$ontext
* PARAMETER WTRRSVAR_S contains the description of the seasonal variation of the
* amount of water inflow
* to the reservoirs for each installed MW capacity of hydropower with storage,
* Unit: (none)

* Observe: the table is specified directly in the present sheet.
* hans__ : KOPIERET OVER FRA VAR3LOW.inc'



TABLE WTRRSVAR_S(AAA,SSS)  'Variation of the water inflow to reservoirs'
                          S01       S02       S03       S04       S05       S06       S07       S08       S09       S10       S11     S12
DK_E_Urban                197       168       255       456       908       563       361       272       268       336       314     249
DK_E_Rural                197       168       255       456       908       563       361       272       268       336       314     249
DK_W_Urban                197       168       255       456       908       563       361       272       268       336       314     249
DK_W_Rural                197       168       255       456       908       563       361       272       268       336       314     249
EE_R_Urban                197       168       255       456       908       563       361       272       268       336       314     249
EE_R_Rural                197       168       255       456       908       563       361       272       268       336       314     249
* Finland aggregated to one area as well as one region - sns
*FI_R_Urban                197       168       255       456       908       563       361       272       268       336       314     249
FI_R_Rural                197       168       255       456       908       563       361       272       268       336       314     249
DE_R_Urban                197       168       255       456       908       563       361       272       268       336       314     249
DE_R_Rural                197       168       255       456       908       563       361       272       268       336       314     249
LV_R_Urban                197       168       255       456       908       563       361       272       268       336       314     249
LV_R_Rural                197       168       255       456       908       563       361       272       268       336       314     249
LT_R_Urban                197       168       255       456       908       563       361       272       268       336       314     249
LT_R_Rural                197       168       255       456       908       563       361       272       268       336       314     249
NO_N_Rural                154       107       170       351       761       860       459       372       337       330       154     142
NO_M_Rural                154       107       170       351       761       860       459       372       337       330       154     142
NO_S_Rural                154       107       170       351       761       860       459       372       337       330       154     142
NO_O_Rural                154       107       170       351       761       860       459       372       337       330       154     142
PL_R_Urban                197       168       255       456       908       563       361       272       268       336       314     249
PL_R_Rural                197       168       255       456       908       563       361       272       268       336       314     249
RU_W_Urban                197       168       255       456       908       563       361       272       268       336       314     249
RU_W_Rural                197       168       255       456       908       563       361       272       268       336       314     249
RU_K_Urban                197       168       255       456       908       563       361       272       268       336       314     249
RU_K_Rural                197       168       255       456       908       563       361       272       268       336       314     249
SE_N_Rural                130       103       158       447       903       782       416       282       307       267       157     177
SE_M_Urban                130       103       158       447       903       782       416       282       307       267       157     177
SE_M_Rural                130       103       158       447       903       782       416       282       307       267       157     177
SE_S_Rural                130       103       158       447       903       782       416       282       307       267       157     177
;

$offtext
