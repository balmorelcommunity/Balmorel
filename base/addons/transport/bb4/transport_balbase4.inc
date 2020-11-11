* Transport add-on. Added by Juan Gea Bermudez

* Additional equations in model definition:

$ifi %import_results%==yes $ifi %ADDTERMTRANSPORTDEMAND%==yes  $goto $NO_PEAKTRANSPORTDEMAND
QTRANSPEAKDEMAND
$label $NO_PEAKTRANSPORTDEMAND

$ifi %import_results%==yes $ifi %ADDTERMTRANSPORTDEMAND%==yes         $goto $SEASONALTRANSPORTDEMAND
$ifi %import_results%==yes $ifi %ADDSEASONALTRANSPORTDEMAND%==yes     $goto $SEASONALTRANSPORTDEMAND
QTRANSDEMAND_Y
QTRANSPEAKDEMANDLIMIT
$label $SEASONALTRANSPORTDEMAND

$ifi not %import_results%==yes $goto $NO_SEASONALTRANSPORTDEMAND
$ifi     %import_results%==yes $ifi not %ADDSEASONALTRANSPORTDEMAND%==yes  $goto $NO_SEASONALTRANSPORTDEMAND
QTRANSDEMAND_S
$label $NO_SEASONALTRANSPORTDEMAND

$ifi not %import_results%==yes $goto $NO_TERMTRANSPORTDEMAND
$ifi     %import_results%==yes $ifi not %ADDTERMTRANSPORTDEMAND%==yes  $goto $NO_TERMTRANSPORTDEMAND
QTRANSDEMAND_T
$label $NO_TERMTRANSPORTDEMAND


