* Transport add-on. Added by Juan Gea Bermudez

* Additional equations in model definition:

$ifi     %import_results%==yes $ifi %ADDSEASONALTRANSPORTDEMAND%==yes     $goto $SEASONALTRANSPORTDEMAND
$ifi not %import_results%==yes $ifi %ADDSEASONALTRANSPORTDEMAND%==yes     $goto $SEASONALTRANSPORTDEMAND
QTRANSDEMAND_Y
$label $SEASONALTRANSPORTDEMAND

$ifi not %import_results%==yes $ifi not %ADDSEASONALTRANSPORTDEMAND%==yes  $goto $NO_SEASONALTRANSPORTDEMAND
QTRANSDEMAND_S
$label $NO_SEASONALTRANSPORTDEMAND
