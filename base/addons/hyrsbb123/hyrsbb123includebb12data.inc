* File HYRSBB123includebb12data.inc for the Balmorel model.
* For use with addon HYRSBB123.

* Data for handling of annual hydro constraints in BB3.
* Supposed to be saved by a previous execution of model BALBASE1 or BALBASE2 (BB1 or BB2).

$ifi not %BB3%==yes        $goto label_enofhyrsbb123includebb12data
$ifi     %HYRSBB123%==none $goto label_enofhyrsbb123includebb12data

execute_load '../../simex/HYRSG.gdx',    HYRSG;
execute_load '../../simex/WATERVAL.gdx', WATERVAL;
execute_load '../../simex/VHYRS_SL.gdx', VHYRS_SL;

* Trim with respect to S for the case that S in BB3 is a proper subset of the S used in BB1\BB2, for nicety of output only:
HYRSG(Y,AAA,SSS)$(not S(SSS))    = 0;
WATERVAL(Y,AAA,SSS)$(not S(SSS)) = 0;
VHYRS_SL(Y,AAA,SSS)$(not S(SSS)) = 0;
* The indexes Y and IA(AAA) are simply assumed to be the same.

$label label_enofhyrsbb123includebb12data
