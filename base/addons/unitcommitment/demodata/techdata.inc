* Unit commitment add-on to Balmorel.
* Implemented by Hans Ravn 2006-2007.
* See the documentation for details and inspiration.

* Technology data.

* Note: the present example uses assignments of individual values.
* The alternative is to include the information along with all other information in PARAMETER GDATA.
* The choice concerns mainly how the input data source is organised.


* Specify which units participate in unit commitment by assigning the value 1 to GDATA(IGCND,'GDUC').
* You may use assignment for individual units, or for groups like IGCND, IGBPR etc.
* Technologies generating electricity and heat
GDATA(IGEH,'GDUC')=1;
* Heat-only boilers
GDATA(IGHOB,'GDUC')=1;



$ifi %UnitComm%==yes  GDATA(G,'GDUCUCOST')=1000;        /* 'UnitCmin: start cost (Money/start)'   */
$ifi %UnitComm%==yes  GDATA(G,'GDUCGMIN' )= 0.4;        /* 'UnitCmin: minimum production when on (fraction of nominal capacity)'   */
*$ifi %UnitComm%==yes  GDATA(G,'GDUCCOST0')=  1000;     /* 'UnitCmin: fixed hourly cost Money/hour'   */
*$ifi %UnitComm%==yes  GDATA(G,'GDUCF0'   )= 5;         /* 'UnitCmin: fixed hourly fuel use MWh'   */

$ifi %UnitCmin%==yes  GDATA(G,'GDUCDCOST' )= 100;       /* 'UnitCmin: shut down cost (Money/start)'   */
$ifi %UnitCmin%==yes  GDATA(G,'GDUCUTMIN' )= 4;         /* 'UnitCmin: minimum up time (hours)'   */
$ifi %UnitCmin%==yes  GDATA(G,'GDUCDTMIN' )= 4;         /* 'UnitCmin: minimum down time (hours)'   */


$ifi %UnitCramp%==yes   GDATA(GGG,'GDUCDURD')=3;        /* 'UnitCramp: duration of shut down process (hours)'   */
$ifi %UnitCramp%==yes   GDATA(GGG,'GDUCDURU')=4;        /* 'UnitCramp: duration of start up process (hours)'    */


* The following data are not compliant with the format of GDATA:

$ifi %UnitCramp%==yes       UCGSHUTD(G,IUCT)=333;       /* UNITS?*/
$ifi %UnitCramp%==yes       UCGSTARTU(G,IUCT)=444;      /* UNITS?*/

$ifi %UnitCramp%==yes    GDATA(G,'GDUCRAMPU')=10;       /* 'UnitCramp: ramp-up limit (MW/h)'  */
$ifi %UnitCramp%==yes    GDATA(G,'GDUCRAMPD')=10;       /* 'UnitCramp: ramp-DOWN limit (MW/h)'  */

$ifi %UnitCscc%==yes     GDATA(G,'GDUCSCCC')=12;        /* 'UnitCscc: time to cool (hours)' */

$ifi %UnitCseg%==yes      NOT MADE