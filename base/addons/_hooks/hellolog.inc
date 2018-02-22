* File hellolog.inc for handling Balmorel addons identifying themselves in the log file if they are used in the present model
* Cf. file error1.inc:
*   Putting from present file is to the file specified in error1.inc
*   Any niceties before and after the generated list of addons are given in error1.inc.

put logfile;

* ==============================================================================
put / "The model applied in the present run is  ";


$ifi %BB1%==yes          put "Balbase1 (BB1)." /;
$ifi %BB2%==yes          put "Balbase2 (BB2)." /;
$ifi %BB3%==yes          put "Balbase3 (BB3)." /;
$ifi %BB4%==yes          put "Balbase4 (BB4)." /;


* ==============================================================================
put / "The following addons are applied:" /;


ISCALAR1 = 0;   !! For this reason: DO NOT use ISCALAR1 in hellolog files for any addon code!

$ifi %testbb1234%==yes            $include   "../../base/addons/bb1234compare/bb1234_hellolog.inc";
$ifi %testbb1234%==yes            ISCALAR1 = 1;

$ifi %hyrsbb123%==yes             $include   "../../base/addons/hyrsbb123/hyrsbb123_hellolog.inc";
$ifi %hyrsbb123%==yes             ISCALAR1 = 1;



/* more .. todo
WNDSHUTDOWN
FV
COMBTECH
X3V
POLICIES
SYSTEMCOST
PLANTCLOSURES
HEATTRANS
REShareE
REShareH
REShareEH
AGKNDISC
H2
stointers

*/

$ifi %BB4%==yes $goto BB4here

* This is for non-BB4:  --------------------------------------------------------
$ifi %combtech%==yes              $include   "../../base/addons/combtech/combtech_hellolog.inc";
$ifi %combtech%==yes              ISCALAR1 = 1;

$ifi %bypass%==yes                $include   "../../base/addons/bypass/bypass_hellolog.inc";
$ifi %bypass%==yes                ISCALAR1 = 1;

$ifi %dflexquant%==yes            $include "../../base/addons/demandflexquant/dflexquant_hellolog.inc";
$ifi %dflexquant%==yes            ISCALAR1 = 1;

$ifi %dflextime%==yes             $include "../../base/addons/demandflextime/dflextime_hellolog.inc";
$ifi %dflextime%==yes             ISCALAR1 = 1;

$ifi %FlowBased%==yes             $include   "../../base/addons/flowbased/flowbased_hellolog.inc";
$ifi %FlowBased%==yes             ISCALAR1 = 1;

IF((ISCALAR1 EQ 0), PUT " - No addons applied"/; );


$ifi not %BB4%==yes $goto endBB4

* This is for BB4:  ------------------------------------------------------------
$label  BB4here



$ifi %combtech%==yes     put " - *** Addon combtech not implemented for addon BB4   " /;

$ifi %bypass%==yes       put " - *** Addon bypass not implemented for addon BB4   " /;

$ifi %dflexquant%==yes            $include "../../base/addons/demandflexquant/dflexquant_hellolog.inc";
$ifi %dflexquant%==yes            ISCALAR1 = 1;

$ifi %forcedoutage%==singlehour       $include "../../base/addons/forcedoutage/forcedoutage_hellolog.inc";
$ifi %forcedoutage%==singlehour       ISCALAR1 = 1;





IF((ISCALAR1 EQ 0), PUT " - No addons applied"/; );

$label endBB4


* ==============================================================================

put / "The following options (not related to addons) have the following option values:";
PUT / " - Option 'HYRSBB123'      for handling of hydro with storage when using BB3 set at: " "%HYRSBB123%";
PUT / " - Option 'inputdatatxt'   for printing an overview of the inputdata to file inputout.out set at: " "%inputdatatxt%";
PUT / " - Option 'printfiles'     for printing various simulation results to folder output set at: " "%printfiles%";
PUT / " - Option 'savepointvalue' for saving a GDX file that contains the information on the current solution point set at: " "%savepointvalue%" ".  See balopt.opt for more information" ;
PUT / " - Option 'bb4weighty'     for BB4 set at: " "%bb4weighty%" "" ;


*WNDSHUTDOWN
*NOELTRANSINV
* inputdatatxt
*INPUTDATA2GDX
*and more ...

PUT / / "This addon overview is under construction and therefore incomplete." / /;



$label endoffile
