* File HYRSBB123sim1.inc for the Balmorel model.
* For use with addon HYRSBB123.
* Included into bb123.sim before loop over seasons, inside the loop over years.
$ifi %RollingSeasons%==yes  $ifi not %HYRSBB123%==none  IHYRSBB123G_Y(Y,IA,S)       = HYRSG(Y,IA,S);
$ifi %RollingSeasons%==yes  $ifi not %HYRSBB123%==none  IWATERVAL_Y(Y,IA,S)         = WATERVAL(Y,IA,S);


$ifi %HYRSBB123%==none    $goto label_no_hydro_results_import_SIM
IHYRSBB123BB3GACCUM(Y,IA)  = 0;
IHYRSBB123BB12GACCUM(Y,IA) = 0;
IHYRSBB123DELTAVOL(Y,IA) = 0;
IHYRSBB123VOLINI(Y,IA,S)$(ORD(S) EQ 1) = VHYRS_SL(Y,IA,S);

* Todo: if S and SSS are different then a rescaling might be useful for comparison of results (HYRSG).
* So for now: make sure that S and SSS are identical.

$LABEL label_no_hydro_results_import_SIM
