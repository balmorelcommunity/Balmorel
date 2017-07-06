* Set related to technology and areas:

* hans: denne fil er meget uoverskuelig. 

SET AGKN(AAA,GGG) 'Areas for possible location of new technologies';
* Initialisation by "AGKN(AAA,G)=YES", then add any specific restrictions
* to IAGKN in balmorel.gms or directly on capacities in balbase2.sim
*AGKN(AAA,G)=YES;

$ifi %bb1%==yes AGKN(AAA,G)=NO;
$ifi %bb3%==yes AGKN(AAA,G)=NO;




/*  hans: indhodlet er SET ALLOWEDINV(AAA,GGG) , dett er indsat nedenfor. 
$if EXIST 'investments.inc' $INCLUDE 'investments.inc';
$if not EXIST 'investments.inc' $INCLUDE '../../base/data/investments.inc';
*/


* LARS20070820: Added temporarily for hydrogen
$ifi %H2%==yes SET H2GGG(GGG)/
$ifi %H2%==yes $include '../../base/addons/hydrogen/Balmorel Set G InvestPos.inc';
$ifi %H2%==yes /;
$ifi %H2%==yes ALLOWEDINV(AAA,H2GGG)=yes;


$ifi %bb2%==yes AGKN(AAA,G)=NO;
*$ifi %bb2%==yes AGKN(AAA,G)=YES$ALLOWEDINV(AAA,G);  FLYTTET NED
* The information given above will be supplemented automatically in Balmorel.gms
* such that no investments can be made in the following cases:
* - if GDATA(G,"GDURBRUR") is inconsistent with IA
* - if FKPOTC, FKPOTR, FKPOTA is zero for IA
* - if GDATA(G,"GDKVARIABL") is 0.
* Therefore you do not have to enter "NO" for such cases.

*------------------------------------------------------------------------------



* LARS20070814: Tilfoejet mulighed for at investere i varmelagre i nogle Svenske omraader.

* Must use gas as fuel in area currently supplied with natural gas.
$Setglobal MUSTGAS yes

* Assume gas can be supplied to areas in Denmark which currently don't use gas
$Setglobal EXPANDGAS

SET ALLOWEDINV(AAA,GGG) "Area, technology where technolgy may be invested based on AGKN and implicit constraints "/

DK_E_1.(
ST-B1-NGn
$ifi not %MUSTGAS%==yes ST-B1-FOn
$ifi not %MUSTGAS%==yes ST-B1-STn
$ifi not %MUSTGAS%==yes ST-B1-WOn
CC-B0-NGn
CC-B1-NGn
HO-B0-NG
$ifi not %MUSTGAS%==yes HO-B0-FO
$ifi not %MUSTGAS%==yes HO-B0-ST
$ifi not %MUSTGAS%==yes HO-B0-WO
EH-P0
EH-P1
EH-E9
)

DK_E_2.(
ST-B1-NGn
$ifi not %MUSTGAS%==yes ST-B1-FOn
$ifi not %MUSTGAS%==yes ST-B1-STn
$ifi not %MUSTGAS%==yes ST-B1-WOn
CC-B0-NGn
CC-B1-NGn
HO-B0-NG
$ifi not %MUSTGAS%==yes HO-B0-FO
$ifi not %MUSTGAS%==yes HO-B0-ST
$ifi not %MUSTGAS%==yes HO-B0-WO
EH-P0
EH-P1
EH-E9
)

DK_E_3.(
$ifi %EXPANDGAS%==yes ST-B1-NGn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
$ifi %EXPANDGAS%==yes CC-B0-NGn
$ifi %EXPANDGAS%==yes CC-B1-NGn
$ifi %EXPANDGAS%==yes HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
)

DK_E_4.(
$ifi %EXPANDGAS%==yes ST-B1-NGn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
$ifi %EXPANDGAS%==yes CC-B0-NGn
$ifi %EXPANDGAS%==yes CC-B1-NGn
$ifi %EXPANDGAS%==yes HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
)

DK_E_5.(
$ifi %EXPANDGAS%==yes ST-B1-NGn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
$ifi %EXPANDGAS%==yes CC-B0-NGn
$ifi %EXPANDGAS%==yes CC-B1-NGn
$ifi %EXPANDGAS%==yes HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
)

DK_W_1.(
ST-B1-NGn
$ifi not %MUSTGAS%==yes ST-B1-FOn
$ifi not %MUSTGAS%==yes ST-B1-STn
$ifi not %MUSTGAS%==yes ST-B1-WOn
CC-B0-NGn
CC-B1-NGn
HO-B0-NG
$ifi not %MUSTGAS%==yes HO-B0-FO
$ifi not %MUSTGAS%==yes HO-B0-ST
$ifi not %MUSTGAS%==yes HO-B0-WO
EH-P0
EH-P1
EH-E9
)

DK_W_2.(
ST-B1-NGn
$ifi not %MUSTGAS%==yes ST-B1-FOn
$ifi not %MUSTGAS%==yes ST-B1-STn
$ifi not %MUSTGAS%==yes ST-B1-WOn
CC-B0-NGn
CC-B1-NGn
HO-B0-NG
$ifi not %MUSTGAS%==yes HO-B0-FO
$ifi not %MUSTGAS%==yes HO-B0-ST
$ifi not %MUSTGAS%==yes HO-B0-WO
EH-P0
EH-P1
EH-E9
)

DK_W_3.(
$ifi %EXPANDGAS%==yes ST-B1-NGn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
ST-B1-WWn
$ifi %EXPANDGAS%==yes CC-B0-NGn
$ifi %EXPANDGAS%==yes CC-B1-NGn
$ifi %EXPANDGAS%==yes HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
)

DK_W_4.(
$ifi EXPANDGAS==yes ST-B1-NGn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
$ifi %EXPANDGAS%==yes CC-B0-NGn
$ifi %EXPANDGAS%==yes CC-B1-NGn
$ifi %EXPANDGAS%==yes HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
)

DK_W_5.(
$ifi %EXPANDGAS%==yes ST-B1-NGn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
$ifi %EXPANDGAS%==yes CC-B0-NGn
$ifi %EXPANDGAS%==yes CC-B1-NGn
$ifi %EXPANDGAS%==yes HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
)

DK_W_6.(
$ifi %EXPANDGAS%==yes ST-B1-NGn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
$ifi %EXPANDGAS%==yes CC-B0-NGn
$ifi %EXPANDGAS%==yes CC-B1-NGn
$ifi %EXPANDGAS%==yes HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
)

DK_W_AALBORG.(
ST-E0-COsn
ST-E0-FOsn
ST-E0-WOsn
ST-E0-NGsn
ST-E1-COsn
ST-E1-FOsn
ST-E1-WOsn
ST-B1-NGn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
CC-E0-NGn
CC-B0-NGn
CC-E1-NGn
CC-B1-NGn
HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
)

DK_W_AARHUS.(
ST-E0-COsn
ST-E0-FOsn
ST-E0-WOsn
ST-E0-NGsn
ST-E1-COsn
ST-E1-FOsn
ST-E1-WOsn
ST-B1-NGn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
CC-E0-NGn
CC-B0-NGn
CC-E1-NGn
CC-B1-NGn
HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
)

DK_W_TREFOR.(
ST-E0-COsn
ST-E0-FOsn
ST-E0-WOsn
*ST-E0-WWsn
ST-E0-NGsn
ST-E1-COsn
ST-E1-FOsn
ST-E1-WOsn
ST-B1-NGn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
CC-E0-NGn
CC-B0-NGn
CC-E1-NGn
CC-B1-NGn
HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
)

DK_W_ODENSE.(
ST-E0-COsn
ST-E0-FOsn
ST-E0-WOsn
ST-E0-NGsn
ST-E1-COsn
ST-E1-FOsn
ST-E1-WOsn
ST-B1-NGn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
CC-E0-NGn
CC-B0-NGn
CC-E1-NGn
CC-B1-NGn
HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
)


DK_E_Urban.(
WI-L15
WI-L20
WI-L25
ST-C0-COsn
ST-C0-FOsn
ST-C0-WOsn
ST-E0-COsn
ST-E0-FOsn
ST-E0-WOsn
ST-E0-NGsn
ST-C1-COsn
ST-E1-COsn
ST-E1-FOsn
ST-E1-WOsn
ST-B1-NGn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
CC-C0-NGn
CC-E0-NGn
CC-B0-NGn
CC-C1-NGn
CC-E1-NGn
CC-B1-NGn
GT-C0-LO
GT-C0-NG
GT-C2-LO
GT-C2-NG
HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
)

DK_E_Rural.(
ST-B1-NGn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
CC-B0-NGn
CC-B1-NGn
HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
)

DK_W_Urban.(
WI-L15
WI-L20
WI-L25
ST-C0-COsn
ST-C0-FOsn
ST-C0-WOsn
ST-E0-COsn
ST-E0-FOsn
ST-E0-WOsn
ST-E0-NGsn
ST-C1-COsn
ST-E1-COsn
ST-E1-FOsn
ST-E1-WOsn
ST-B1-NGn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
CC-C0-NGn
CC-E0-NGn
CC-B0-NGn
CC-C1-NGn
CC-E1-NGn
CC-B1-NGn
GT-C0-LO
GT-C0-NG
GT-C2-LO
GT-C2-NG
HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
)

DK_W_Rural.(
ST-B1-NGn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
CC-B0-NGn
CC-B1-NGn
HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
)

DK_E_Offshore.(
WI-S15
WI-S20
WI-S25
)

DK_W_Offshore.(
WI-S15
WI-S20
WI-S25
)

FI_R_Urban.(
NU-C0-NU
NU-C2-NU
ST-C0-COsn
ST-C0-FOsn
ST-C0-WOsn
ST-E0-COsn
ST-E0-FOsn
ST-E0-WOsn
ST-E0-NGsn
ST-C1-COsn
ST-E1-COsn
ST-E1-FOsn
ST-E1-WOsn
ST-B1-NGn
ST-B1-FOn
ST-B1-STn
ST-B1-PEn
ST-B1-WOn
CC-C0-NGn
CC-E0-NGn
CC-B0-NGn
CC-C1-NGn
CC-E1-NGn
CC-B1-NGn
GT-C0-LO
GT-C0-NG
GT-C2-LO
GT-C2-NG
HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
)

FI_R_Rural.(
ST-B1-NGn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
CC-B0-NGn
CC-B1-NGn
HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
)

FI_R_Decen.(
ST-B1-NGn
CC-B0-NGn
CC-B1-NGn
HO-B0-NG
EH-P0
EH-P1
EH-E9
)

FI_R_Offshore.(
WI-S15
WI-S20
WI-S25
)

NO_N_Rural.(
ST-C0-COsn
ST-C0-FOsn
ST-C0-WOsn
ST-C1-COsn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
CC-C0-NGn
CC-B0-NGn
CC-C1-NGn
CC-B1-NGn
GT-C0-LO
GT-C0-NG
GT-C2-LO
GT-C2-NG
HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
)

NO_M_Rural.(
ST-C0-COsn
ST-C0-FOsn
ST-C0-WOsn
ST-C1-COsn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
CC-C0-NGn
CC-B0-NGn
CC-C1-NGn
CC-B1-NGn
GT-C0-LO
GT-C0-NG
GT-C2-LO
GT-C2-NG
WI-L15
WI-L20
WI-L25
HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
)

NO_S_Rural.(
ST-C0-COsn
ST-C0-FOsn
ST-C0-WOsn
ST-C1-COsn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
CC-C0-NGn
CC-B0-NGn
CC-C1-NGn
CC-B1-NGn
GT-C0-LO
GT-C0-NG
GT-C2-LO
GT-C2-NG
WI-L15
WI-L20
WI-L25
HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
)

NO_O_Rural.(
ST-C0-COsn
ST-C0-FOsn
ST-C0-WOsn
ST-C1-COsn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
CC-C0-NGn
CC-B0-NGn
CC-C1-NGn
CC-B1-NGn
GT-C0-LO
GT-C0-NG
GT-C2-LO
GT-C2-NG
HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
)

NO_N_Offshore.(
WI-S15
WI-S20
WI-S25
)

NO_M_Offshore.(
WI-S15
WI-S20
WI-S25
)

NO_S_Offshore.(
WI-S15
WI-S20
WI-S25
)

SE_N_Rural.(
WI-L15
WI-L20
WI-L25
HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
G-HSTORE
)

SE_M_Urban.(
ST-C0-COsn
ST-C0-FOsn
ST-C0-WOsn
ST-E0-COsn
ST-E0-FOsn
ST-E0-WOsn
ST-E0-NGsn
ST-C1-COsn
ST-E1-COsn
ST-E1-FOsn
ST-E1-WOsn
ST-B1-NGn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
CC-C0-NGn
CC-E0-NGn
CC-B0-NGn
CC-C1-NGn
CC-E1-NGn
CC-B1-NGn
GT-C0-LO
GT-C0-NG
GT-C2-LO
GT-C2-NG
HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
G-HSTORE
)

SE_M_Rural.(
NU-C0-NU
NU-C2-NU
ST-B1-NGn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
CC-B0-NGn
CC-B1-NGn
WI-L15
WI-L20
WI-L25
HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
G-HSTORE
)

SE_S_Rural.(
ST-C0-COsn
ST-C0-FOsn
ST-C0-WOsn
ST-E0-COsn
ST-E0-FOsn
ST-E0-WOsn
ST-E0-NGsn
ST-C1-COsn
ST-E1-COsn
ST-E1-FOsn
ST-E1-WOsn
ST-B1-NGn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
CC-C0-NGn
CC-E0-NGn
CC-B0-NGn
CC-C1-NGn
CC-E1-NGn
CC-B1-NGn
GT-C0-LO
GT-C0-NG
GT-C2-LO
GT-C2-NG
WI-L15
WI-L20
WI-L25
HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
G-HSTORE
)

SE_N_Bio.(
G-HSTORE
)

SE_M_Bio.(
G-HSTORE
)

SE_S_Bio.(
G-HSTORE
)

SE_N_Offshore.(
WI-S15
WI-S20
WI-S25
)

SE_M_Offshore.(
WI-S15
WI-S20
WI-S25
)

SE_S_Offshore.(
WI-S15
WI-S20
WI-S25
)

DE_CS_A1.(
ST-C0-COsn
ST-C0-FOsn
ST-C0-WOsn
ST-E0-COsn
ST-E0-FOsn
ST-E0-WOsn
ST-E0-NGsn
ST-C1-COsn
ST-E1-COsn
ST-E1-FOsn
ST-E1-WOsn
ST-B1-NGn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
CC-C0-NGn
CC-E0-NGn
CC-B0-NGn
CC-C1-NGn
CC-E1-NGn
CC-B1-NGn
GT-C0-LO
GT-C0-NG
GT-C2-LO
GT-C2-NG
WI-L15
WI-L20
WI-L25
HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
)

DE_NE_A1.(
ST-C0-COsn
ST-C0-FOsn
ST-C0-WOsn
ST-E0-COsn
ST-E0-FOsn
ST-E0-WOsn
ST-E0-NGsn
ST-C1-COsn
ST-E1-COsn
ST-E1-FOsn
ST-E1-WOsn
ST-B1-NGn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
CC-C0-NGn
CC-E0-NGn
CC-B0-NGn
CC-C1-NGn
CC-E1-NGn
CC-B1-NGn
GT-C0-LO
GT-C0-NG
GT-C2-LO
GT-C2-NG
WI-L15
WI-L20
WI-L25
HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
)

DE_NW_A1.(
ST-C0-COsn
ST-C0-FOsn
ST-C0-WOsn
ST-E0-COsn
ST-E0-FOsn
ST-E0-WOsn
ST-E0-NGsn
ST-C1-COsn
ST-E1-COsn
ST-E1-FOsn
ST-E1-WOsn
ST-B1-NGn
ST-B1-FOn
ST-B1-STn
ST-B1-WOn
CC-C0-NGn
CC-E0-NGn
CC-B0-NGn
CC-C1-NGn
CC-E1-NGn
CC-B1-NGn
GT-C0-LO
GT-C0-NG
GT-C2-LO
GT-C2-NG
WI-L15
WI-L20
WI-L25
HO-B0-NG
HO-B0-FO
HO-B0-ST
HO-B0-WO
EH-P0
EH-P1
EH-E9
)

DE_NW_Offshore.(
WI-S15
WI-S20
WI-S25
)

DE_NE_Offshore.(
WI-S15
WI-S20
WI-S25
)

/;


$ifi %bb2%==yes AGKN(AAA,G)=YES$ALLOWEDINV(AAA,G);  /*FLYTTET NED hertil */    

 

