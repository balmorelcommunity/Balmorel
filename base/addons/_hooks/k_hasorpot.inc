* File k_hasorpot.inc
* Location of annual update of IAGK_HASORPOT and IXK_HASORPOT for addons


$ifi not %BB4%==yes $goto endoffile

$label beginbb4
* bb4:

$ifi %heattrans%==yes  $include   "../../base/addons/heattrans/bb4/heattrans_k_hasorpot.inc";



$label endoffile
