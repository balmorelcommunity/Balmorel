*-----------------------------------------------------------------------------------------------*
* File      : gascontracts.inc
* Author    :
* Version   : 1.0
* Remarks   : #
* Date      : 06/10/2005 10:39:54
* Changed   : 27-06-2006 13:47:04
* Changed by:
*-----------------------------------------------------------------------------------------------*
*                   Volumen-    Udtrækskapacitet Injektionskapacitet Tarif uden
*                   kapacitet   pr. time         pr. time            fyldningskrav
*                   kWh         % af volumen     % af volumen        kr/MWh        

TABLE SCONDATA(SCON,SCONDATASET)
                    VOLCAP      EXTCAP   INJCAP   TARRIF
STORE1              1           0.00042  0.00021  35.4
STORE2              1           0.00209  0.00104  71.7
;




$ontext
TABLE SCONDATA(SCON,SCONDATASET)
                    VOLCAP      EXTCAP   INJCAP   TARRIF
STORE1              1           0.00042  0.00021  0.0303
STORE2              1           0.00209  0.00104  0.0655
;


Gamle tariffer:
TABLE SCONDATA(SCON,SCONDATASET)
        VOLCAP  INJCAP  EXTCAP  TARRIF
*       kWh     of vol  of vol  kr./MWh
STORE1  0.001   0.00042 0.00021 29.5
STORE2  0.001   0.00209 0.00104 65.5;

$offtext
$ifi not %FREESTORAGE%==yes TAU_INJ = 0.123*1000/100;
$ifi %FREESTORAGE%==yes TAU_INJ = 0;
