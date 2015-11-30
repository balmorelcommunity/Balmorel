* File uc_modeladd.inc
* Unit commitment add-on to Balmorel.
* Implemented by Hans Ravn 2006-2007.
* Revised and enhanced by Lars Bregnsbæk 2011.

* Additional equations in model definition:

QUCMINVGF
QUCMINVGFN
QUCMAXVGF
QUCMAXVGFN
QUCSTARTQ
QUCSTARTQN
* Eqaution QUCTEST is for test purpose only, comment out otherwise. Details are hard coded in the equation definition.
QUCTEST

$ifi %UnitCmin%==yes    QUCUT
$ifi %UnitCmin%==yes    QUCDT
$ifi %UnitCmin%==yes    QUCUTN
$ifi %UnitCmin%==yes    QUCDTN

$ifi %UnitCramp%==yes   QUCRAMPU
$ifi %UnitCramp%==yes   QUCRAMPUN
$ifi %UnitCramp%==yes   QUCRAMPD
$ifi %UnitCramp%==yes   QUCRAMPDN

