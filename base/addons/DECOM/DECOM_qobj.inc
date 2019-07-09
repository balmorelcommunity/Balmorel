* Decommissioning introduced by Juan Gea Bermúdez 2018.


* The following expressions are added to the objective function,
* after IOF1_ * IDISCOUNTFACTOR(Y) * IWEIGHTY(Y) * ( :

- IOF1000*(SUM((IA,G)$IGDECOMEXOPOT(Y,IA,G),VDECOM_EXO_ACCUM(Y,IA,G)*GOMFCOST(IA,G)))



