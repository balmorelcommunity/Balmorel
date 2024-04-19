* File RESEdata.inc to the addon REShareEH.

*$ontext
SET GREE(GGG) 'Generation technologies qualified as renewable electricity technologies'
/

ST-B9-MW
ST-B9-WW
        HY-S01
        HY-S02
        HY-S03
        HY-S04
        HY-S05
        HY-S06
        HY-S07
        HY-S08
        HY-S09
        HY-S10

WI-L9

/;



SET GREEH(GGG) 'Generation technologies qualified as renewable electricity and heat technologies'  ;

GREEH(GGG)$IGF(GGG,'WIND') = yes;
GREEH(GGG)$IGF(GGG,'STRAW') = yes;
GREEH(GGG)$IGF(GGG,'WOOD') = yes;
GREEH(GGG)$IGF(GGG,'WIND') = yes;
GREEH(GGG)$IGF(GGG,'WATER') = yes;
GREEH(GGG)$IGF(GGG,'SUN') = yes;
*$OFFTEXT



SET CCCRESHAREE 'Group of countries with a common renewable electricity share goal'
/
   CCCRESHAREE_NORDIC

/;



SET CCCRESHAREEC(CCCRESHAREE,CCC) 'Countries within group with common renewable electricity share goal'
/
    CCCRESHAREE_NORDIC. DENMARK
    CCCRESHAREE_NORDIC. Norway
    CCCRESHAREE_NORDIC. Sweden
    CCCRESHAREE_NORDIC. FINLAND
/;



PARAMETER RESHAREE(CCCRESHAREE) 'Share of renewable electricity (fraction)'
/
        CCCRESHAREE_NORDIC  0.0
/;
