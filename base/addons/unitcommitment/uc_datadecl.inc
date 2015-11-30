* File uc_datadecl.inc.
* Unit commitment add-on to Balmorel.
* Implemented by Hans Ravn 2006-2007.
* Revised and enhanced by Lars Bregnsbæk 2011.

* Declarations for input data entities.


* Note: CARD(IUCT) must be at least as large as GDATA( *,'GDUCDTMIN') and GDATA( *,'GDUCUTMIN')
SET  IUCT 'Unit commitment: hour counter';
ALIAS(IUCT,IUCT2);

$ifi %UnitCramp%==yes   PARAMETER UCGSHUTD(GGG,IUCT)   'Description to be added';
$ifi %UnitCramp%==yes   PARAMETER UCGSTARTU(GGG,IUCT)  'Description to be added';

* Data for initial state:
* Initial unit commitment status (hours): positive: unit is in start-up process; negative: unit is in shutdown process.
PARAMETER UCINI(AAA,GGG)       'Unit commitment: Initial state';

$ifi %UnitCramp%==yes  PARAMETER UCRAMPINI(AAA,GGG)   'Unit commitment: UnitCramp: Initial state';
$ifi %UnitCramp%==yes  PARAMETER UCINIGE(AAA,GGG,SSS)  'Unit commitment: initial electricity production level (MW)';
$ifi %UnitCramp%==yes  PARAMETER UCINIGH(AAA,GGG,SSS)  'Unit commitment: initial heat production level (MW)';


* Note: CARD(IUCT) must be at least as large as  GDATA( *,'GDUCDTMIN') and as GDATA( *,'GDUCUTMIN').
* For this reason it should strictly speaking be input data, however, we put it here for (short term) convenience:
SET  IUCT 'Unit commitment: hour counter '  /  IUCT01*IUCT05  /;
