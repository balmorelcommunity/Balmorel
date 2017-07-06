* File data.inc to the addon REShareEH.

SET GREE(GGG) 'Generation technologies qualified as renewable electricity technologies'
/

ST-B9-MW
ST-B9-ST
ST-B9-WO
ST-B9-WW
ST-E0-WOsn
ST-E0-WWsn
ST-E1-WOsn
ST-B1-MWn
ST-B1-STn
ST-B1-WOn
ST-B1-WWn
CC-C1-WOn
CC-E1-WOn
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
        HY-R
WI-L9
WI-S9
WI-L0
WI-S0
WI-L1
WI-S1
HO-B8-MW
HO-B8-ST
HO-B8-WO
HO-B0-MW
HO-B0-ST
HO-B0-WO
ST-E8-WW
ST-E9-WO
ST-B8-WW
ST-E8-ST
DK_W_CHP3
DK_W_CHP4
DK_E_CHP3
DK_E_CHP4

/;



SET GREEH(GGG) 'Generation technologies qualified as renewable electricity and heat technologies'  ;

GREEH(GGG)$IGF(GGG,'FUEL_WIND') = yes;
GREEH(GGG)$IGF(GGG,'FUEL_MUNIWASTE') = yes;
GREEH(GGG)$IGF(GGG,'FUEL_STRAW') = yes;
GREEH(GGG)$IGF(GGG,'FUEL_WOOD') = yes;
GREEH(GGG)$IGF(GGG,'FUEL_WIND') = yes;
GREEH(GGG)$IGF(GGG,'FUEL_WATER)' = yes;
GREEH(GGG)$IGF(GGG,'FUEL_SUN') = yes;
GREEH(GGG)$IGF(GGG,'FUEL_WIND') = yes;






SET CCCRESHAREEH 'Group of countries with a common renewable electricity and heat share goal'
/
   CCCRESHAREEH_NORDIC
/;




SET CCCRESHAREEHC(CCCRESHAREEH,CCC) 'Countries within group with common renewable electricity share goal'
/
    CCCRESHAREEH_NORDIC. DENMARK
    CCCRESHAREEH_NORDIC. Norway
    CCCRESHAREEH_NORDIC. Sweden
    CCCRESHAREEH_NORDIC. FINLAND

/;



PARAMETER RESHAREEH(CCCRESHAREEH) 'Share of renewable electricity (fraction)'
/
        CCCRESHAREEH_NORDIC  0.5
/;