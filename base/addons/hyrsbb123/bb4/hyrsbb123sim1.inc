* File HYRSBB123sim1.inc for the Balmorel model.
* For use with addon HYRSBB123.
* Included into bb123.sim before loop over seasons, inside the loop over years.

IHYRSBB123BB3GACCUM(IA)  = 0;
IHYRSBB123BB12GACCUM(IA) = 0;
IHYRSBB123DELTAVOL(IA) = 0;
IHYRSBB123VOLINI(IA,S)$(ORD(S) EQ 1) = VHYRS_SL(Y,IA,S);

* Todo: if S and SSS are different then a rescaling might be useful for comparison of results (HYRSG).
* So for now: make sure that S and SSS are identical.






