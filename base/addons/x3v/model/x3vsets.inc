*---------------------------------------------------------------------------------------------------------------
* The following concerns price-dependant electricity exchange to places outside the simulated area
*---------------------------------------------------------------------------------------------------------------

$ontext
Price dependent electricity exchange with places outside the simulated geographical
scope may be used together with the fixed electricity exchange with third  countries.
The price-quantity relationships are given as a piecewise step curve.
There are card(X3VSTEP)steps applied in simulation, and in the data
card(X3VSTEP0) steps
may be given. The length (MW) of each import step is X3VIMQ and X3VEXQ of
each export step.
The associated prices are X3VIMP and X3VIMP, respectively.
The prices are given on a yearly basis,
the value for the currently simulated year are held in IX3VPIM_Y and IX3VPEX_Y.
The exchange is assumed to be lossless and without transmission cost.

The simulated price dependent electricity exchange transmission connections
are specified in the set X3VX.
$offtext


* The set of regions with which there can be price dependent electricity exchange:
SET X3VPLACE0 'Set of possible places with price dependent electricity exchange data'
/
X3VGERMAN 'Germany'
X3VPOL 'Poland'
/;


SET X3VPLACE(X3VPLACE0) 'Set of simulatd places with price dependent electricity exchange data'
/
X3VGERMAN
X3VPOL
/;

* The combinations of RRR and X3VPLACE that are to be simulated:

SET X3VX(RRR,X3VPLACE0) 'Simulated transmisision lines for price dependent electricity exchange' ;
   X3VX('DK_W','X3VGERMAN')=YES;
   X3VX('DK_E','X3VGERMAN')=YES;
   X3VX('SE_S','X3VGERMAN')=YES;
   X3VX('SE_S','X3VPOL')=YES;

*-----------------------------------------

* The following set RX3VSUBSTI indicates (by assigning YES) if elements in X3VPLACE0
* is a substitute for a region in RRR. If it is, the price dependent exchange
* should only be used if the region is NOT included in a country in set C,
* i.e. the set RX3VSUBSTI(IR,X3VPLACE0) (where IR is a region in C) should be empty.
* The only function of the set RX3VSUBSTI is to help the user to avoid errors
* by printing an error message.

SET RX3VSUBSTI(RRR,X3VPLACE0) 'Substitutes in price dependent electricity exchange';
* RX3VSUBSTI(RRR,X3VPLACE)=NO; /* This is used if no substitutes*/
* Give the real information, if any:

*  RX3VSUBSTI('DE_R','X3VGERMAN')=YES;
*  RX3VSUBSTI('PL_R','X3VPOL')=YES;

* The set of steps on the price dependent electricity exchange curves.
* The same number of steps is assumed for the import and the export directions:
SET X3VSTEP0 'Steps for price dependent electricity exchange data'
   /X3VSTEP01*X3VSTEP04/;

* The set of steps on the price dependent electricity exchange curve
* used in simulation (no exchange if empty, in this case use 'IX3VSTEP(X3VSTEP)=NO'):
SET X3VSTEP(X3VSTEP0) 'Simulated steps for price dependent electricity  exchange'
*   X3VSTEP(X3VSTEP0)=NO;
   /X3VSTEP01*X3VSTEP01/;