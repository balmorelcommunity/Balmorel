* Equations for fuel transport


* Regional fuel transport is limited by total potential (very high number for a specific transport corridor)
$ifi %fueltransport_definition%==region VFUELTRANSPORT.UP(Y,IRRRE,IRRRI,FFF)$FUELTRANSPORT_COST(FFF, IRRRE, IRRRI) = GMAXF(Y,'DENMARK',FFF);

* Areal fuel transport is limited by total potential (very high number for a specific transport corridor)
$ifi %fueltransport_definition%==area VFUELTRANSPORT.UP(Y,IAAAE,IAAAI,FFF)$FUELTRANSPORT_COST(FFF, IAAAE, IAAAI) = GMAXF(Y,'DENMARK',FFF);
