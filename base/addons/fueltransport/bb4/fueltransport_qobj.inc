* -------- COSTS of Annual Transport of Fuel -------- *
* Regional fuel transport is limited by total potential (very high number for a specific transport corridor)
$ifi %fueltransport_definition%==region + SUM((FFF, IRRRE, IRRRI)$FUELTRANSPORT_COST(FFF,IRRRI,IRRRE), FUELTRANSPORT_COST(FFF,IRRRI,IRRRE)*VFUELTRANSPORT(Y,IRRRE,IRRRI,FFF))
$ifi %fueltransport_definition%==area   + SUM((FFF, IAAAE, IAAAI)$FUELTRANSPORT_COST(FFF,IAAAI,IAAAE), FUELTRANSPORT_COST(FFF,IAAAI,IAAAE)*VFUELTRANSPORT(Y,IAAAE,IAAAI,FFF))