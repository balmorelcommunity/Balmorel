
* PARAMETER GKDERATE contains a possibility to represent planned outages.
* It works through the parameter GKDERATE.
* It permits to take out units in one or more season (whole seasons only).
* If unit 'G' in area 'A' is planned out in season 'S' then let GKDERATE('G','A','S')=0.
* If unit 'G' in area 'A' is not planned out in season 'S' then let GKDERATE('G','A','S')
* attain 1 minus the stochastic FOR value (typically this will be 0.9 or 0.95).

* hans__ :  var3low.inc:
TABLE GKDERATE(AAA,GGG,SSS)  'Reduction in capacity'
                                     S01       S02       S03       S04       S05       S06       S07       S08       S09       S10       S11     S12
*FI_R_Rural.NU-C8-NU                 1         0.98      1         0.96      0.74      0.9       0.9       0.77      0.86      1       1       1
*SE_M_Rural.NU-C8-NU                 0.99      0.94      0.91      0.73      0.46      0.42      0.29      0.35      0.56      0.73    0.76    0.81
*SE_S_Rural.NU-C8-NU                 0.99      0.94      0.91      0.73      0.46      0.42      0.29      0.35      0.56      0.73    0.76    0.81
DK_E_Rural.DK_E_Rural_ST-E8-ORs      0.99      0.94      0.91      0.73      0.46      0.42      0.29      0.7       0.85      0.96    0.98    0.98
;

* for normal years use:             0.98      0.98      0.98      0.94      0.82      0.77      0.77      0.77      0.85      0.96    0.98    0.98


* Unless other values are assigned in the TABLE above,
* a default value 0.90 is used and assigned below:

$ontext
* Lars: QUICKFIX to limit number of assigned elements in GKDERATE
$ifi %BB1%==yes GKDERATE(AAA,G,SSS)$((not ((GDATA(G,'GDTYPE') EQ 10) OR (GDATA(G,'GDTYPE') EQ GWND))) and SUM(Y,GKFX(Y,AAA,G)))= 0.90        ;
$ifi %BB2%==yes GKDERATE(AAA,G,SSS)$((not ((GDATA(G,'GDTYPE') EQ 10) OR (GDATA(G,'GDTYPE') EQ GWND))) and (AGKN(AAA,G) or SUM(Y,GKFX(Y,AAA,G))))= 0.90        ;
$ifi %BB3%==yes GKDERATE(AAA,G,SSS)$((not ((GDATA(G,'GDTYPE') EQ 10) OR (GDATA(G,'GDTYPE') EQ GWND))) and SUM(Y,GKFX(Y,AAA,G)))= 0.90        ;
$ifi %ADDINVEST%==yes GKDERATE(AAA,G,SSS)$((not ((GDATA(G,'GDTYPE') EQ 10) OR (GDATA(G,'GDTYPE') EQ GWND))) and (AGKN(AAA,G) or SUM(Y,GKFX(Y,AAA,G))))= 0.90        ;
$ifi %BB1%==yes GKDERATE(AAA,G,SSS)$((((GDATA(G,'GDTYPE') EQ 10) OR (GDATA(G,'GDTYPE') EQ GWND))) and SUM(Y,GKFX(Y,AAA,G)))= 1        ;
$ifi %BB2%==yes GKDERATE(AAA,G,SSS)$((((GDATA(G,'GDTYPE') EQ 10) OR (GDATA(G,'GDTYPE') EQ GWND))) and (AGKN(AAA,G) or SUM(Y,GKFX(Y,AAA,G))))= 1        ;
$ifi %BB3%==yes GKDERATE(AAA,G,SSS)$((((GDATA(G,'GDTYPE') EQ 10) OR (GDATA(G,'GDTYPE') EQ GWND))) and SUM(Y,GKFX(Y,AAA,G)))= 1        ;
$ifi %ADDINVEST%==yes GKDERATE(AAA,G,SSS)$(((GDATA(G,'GDTYPE') EQ 10) OR (GDATA(G,'GDTYPE') EQ GWND)) and (AGKN(AAA,G) or SUM(Y,GKFX(Y,AAA,G))))= 1        ;
$offtext

* Hans ændret :
$ifi %BB1%==yes GKDERATE(AAA,G,SSS) = 0.90        ;
$ifi %BB2%==yes GKDERATE(AAA,G,SSS) = 0.90        ;
$ifi %BB3%==yes GKDERATE(AAA,G,SSS) = 0.9     ;
$ifi %ADDINVEST%==yes GKDERATE(AAA,G,SSS)       ;



* $include '../../base/data/gkderateweek.inc';  hans12345

/*
* hans__ overskriv! :
* PEME 02082004 HER SÆTTES GKDERATE LIG MED GKDERATEW
  LOOP(IR,
     LOOP((AAA,IGE)$(RRRAAA(IR,AAA)),
$ifi %BB1%==yes GKDERATE(AAA,IGE,SSS)$((not IGWND(IGE)) and (SUM(Y,GKFX(Y,AAA,IGE))>0))= GKDERATEW(SSS,IR);
$ifi %BB2%==yes GKDERATE(AAA,IGE,SSS)$((not IGWND(IGE)) and (AGKN(AAA,IGE) or (SUM(Y,GKFX(Y,AAA,IGE))>0)))= GKDERATEW(SSS,IR);
$ifi %BB3%==yes GKDERATE(AAA,IGE,SSS)$((not IGWND(IGE)) and (SUM(Y,GKFX(Y,AAA,IGE))>0))= GKDERATEW(SSS,RRR);
$ifi %ADDINVEST%==yes GKDERATE(AAA,IGE,SSS)$((not IGWND(IGE)) and (AGKN(AAA,IGE) or (SUM(Y,GKFX(Y,AAA,IGE))>0)))= GKDERATEW(SSS,IR);
     );
  );
*/
$ontext
* Lars: Ud. Foreløbigt håndteret for oven.
* PEME: Scaling of GKDERATE of Nuclear power to ensure correct nuclear production in 2001:
GKDERATE(IGHYRS,AAA,SSS)$(AGKN(AAA,IGHYRS) or SUM(Y,GKFX(Y,AAA,IGHYRS)))= 0.817;
GKDERATE(IGWND,AAA,SSS)$(AGKN(AAA,IGWND) or SUM(Y,GKFX(Y,AAA,IGWND)))= 1;
GKDERATE(IGNUC,'FI_R_Rural',SSS)=GKDERATE('FI_R_Rural_NU-C8-NU','FI_R_Rural',SSS) * 1.176 ;
GKDERATE(IGNUC,'SE_M_Rural',SSS)=GKDERATE('SE_M_Rural_NU-C8-NU','SE_M_Rural',SSS) * 1.088 ;
GKDERATE(IGNUC,'SE_S_Rural',SSS)=GKDERATE('SE_S_Rural_NU-C8-NU','SE_S_Rural',SSS) * 1.088 ;
$offtext

* hans__ minwater? (tep)



