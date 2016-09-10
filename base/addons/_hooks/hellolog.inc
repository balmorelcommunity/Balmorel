* File hellolog.inc for handling Balmorel addons identifying themselves in the log file if they are used in the present model
* Cf. file error1.inc:
*   Putting from present file is to the file specified in error1.inc
*   Any niceties before and after the generated list of addons are given in error1.inc.

ISCALAR5 = 0;

$ifi %combtech%==yes  $include   "../../base/addons/combtech/combtech_hellolog.inc";
$ifi %combtech%==yes  ISCALAR5 = 1;

$ifi %bypass%==yes    $include   "../../base/addons/bypass/bypass_hellolog.inc";
$ifi %bypass%==yes    ISCALAR5 = 1;


* At end of file:
IF((ISCALAR5 EQ 0), PUT "No addons applied"/; );

PUT "This addon overview is under construction and therefore incomplete." /;


