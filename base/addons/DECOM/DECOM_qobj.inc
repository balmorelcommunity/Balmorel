* Decommissioning introduced by Juan Gea Bermúdez 2018.


* The following expressions are added to the objective function,
* after IOF1_ * IDISCOUNTFACTOR(Y) * IWEIGHTY(Y) * ( :

- IOF1000*(SUM((IA,G)$IAGK_HASORPOT(Y,IA,G),VDECOM_ACCUM_EXO(Y,IA,G)*GOMFCOST(IA,G)))



