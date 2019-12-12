PARAMETER LIMITSFORFUELS_CONVFACTOR(FFF)
/THERMGAS 0.6
$ifi not %combtech%==yes $goto nocombtech
THERMGAS_UP 0.6
$label nocombtech
$ifi not %hydrogen%==yes $goto nohydrogen
THERMGAS_H2 0.6
$label nohydrogen
/;
