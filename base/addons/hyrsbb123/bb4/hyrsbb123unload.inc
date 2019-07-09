* File HYRSBB123unlaod.inc for the Balmorel model.
* For use with addon HYRSBB123.

$ifi not %BB3%==yes       $goto label_hydrobb123unload

$ifi %HYRSBB123%==quant      execute_unload  '../../simex/HYRSG_BB3.gdx',HYRSG;
$ifi %HYRSBB123%==quant      execute_unload  '../../simex/WATERVAL_BB3.gdx',WATERVAL;
$ifi %HYRSBB123%==price      execute_unload  '../../simex/HYRSG_BB3.gdx',HYRSG;
$ifi %HYRSBB123%==price      execute_unload  '../../simex/WATERVAL_BB3.gdx',WATERVAL;
$ifi %HYRSBB123%==quantprice execute_unload  '../../simex/HYRSG_BB3.gdx',HYRSG;
$ifi %HYRSBB123%==quantprice execute_unload  '../../simex/VHYRS_SL_BB3.gdx',VHYRS_SL;
$ifi %HYRSBB123%==quantprice execute_unload  '../../simex/WATERVAL_BB3.gdx',WATERVAL;

$label label_hydrobb123unload