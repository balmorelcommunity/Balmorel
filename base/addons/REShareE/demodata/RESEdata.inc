* File RESEdata.inc to the addon GreenCert.

$ontext
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
*EH-P8
*EH-P9
*EH-P0
*EH-P1
*EH-E9
ST-E8-WW
ST-E9-WO
ST-B8-WW
ST-E8-ST
DK_W_CHP3
DK_W_CHP4
DK_E_CHP3
DK_E_CHP4

/;
$offtext

* HOV: du har da IGF! Brug den? Eller hvad med at indføre sets i stil med IGEXT etc, men for fuel? IGF

SET GREE(GGG) 'Generation technologies qualified as renewable electricity technologies'  ;
GREE(GGG)$(GDATA(GGG,'GDFUEL') EQ FUEL_WIND) = yes;
GREE(GGG)$(GDATA(GGG,'GDFUEL') EQ FUEL_MUNIWASTE) = yes;
GREE(GGG)$(GDATA(GGG,'GDFUEL') EQ FUEL_STRAW) = yes;
GREE(GGG)$(GDATA(GGG,'GDFUEL') EQ FUEL_WOOD) = yes;
GREE(GGG)$(GDATA(GGG,'GDFUEL') EQ FUEL_WIND) = yes;
*GREE(GGG)$(GDATA(GGG,'GDFUEL') EQ FUEL_WATER) = yes; KUN NY HYDRO!
GREE(GGG)$(GDATA(GGG,'GDFUEL') EQ FUEL_SUN) = yes;
GREE(GGG)$(GDATA(GGG,'GDFUEL') EQ FUEL_WIND) = yes;






SET CCCRESHAREE 'Group of countries with a common renewable electricity share goal'
/
   CCCRESHAREE_NORDIC
*   CCCRESHARE_SE_FI

/

Her kan man bare skrive noget nonsens! Årsag tilsyneladende: at der mangler et semikolon efter sidste skråstreg.

* Se noget yderst interessant lige ovenfor: det bliver ikke fanget som  en syntaksfejl, selv om det for mig virker som sådan!
* Efterfølgende display viser, at det definerede SET dog bliver rigtigt nok.
display "Se her efter mulig syntaksfejl: ",     CCCRESHAREE  ;




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