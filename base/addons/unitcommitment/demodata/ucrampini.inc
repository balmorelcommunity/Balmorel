* Unit commitment add-on to Balmorel.
* Implemented by Hans Ravn 2006-2007.
* See the documentation for details and inspiration.

* Data:

* NB: UCRAMPINI is tricky! It must be consistent with UCINI. Two consistent possibilities are to assign 0 or INF.

$ifi %UnitCramp%==yes  UCRAMPINI(IA,GGG)=0;
$ifi %UnitCramp%==yes  UCINIGE(IA,G,SSS)=0;
$ifi %UnitCramp%==yes  UCINIGH(IA,G,SSS)=0;