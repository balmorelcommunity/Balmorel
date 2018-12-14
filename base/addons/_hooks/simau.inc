* Location of annual update specifications used in add-ons

$ifi %HYDROGEN%==yes   $include   "../../base/addons/hydrogen/hydrogen_simau.inc";

$ifi %BB4%==yes $goto beginbb4


$ifi not %BB4%==yes $goto endoffile

$label beginbb4
* bb4:

$ifi %heattrans%==yes  $include   "../../base/addons/heattrans/bb4/heattrans_simau.inc";

                  

$label endoffile

