*Balancing market introduced by Juan Gea-Bermudez and Polyneikis Kanellas

*Removing technologies whose VUCON values are going to be fixed to avoid infeasibilities and reduce complexity of the code
IUCUTMIN(IGUC)$SUM(S$(GDATA(IGUC,'GDUCUTMIN') GT WEIGHT_S(S) OR GDATA(IGUC,'GDUCDTMIN') GT WEIGHT_S(S)),1)=NO;
IUCDTMIN(IGUC)$SUM(S$(GDATA(IGUC,'GDUCUTMIN') GT WEIGHT_S(S) OR GDATA(IGUC,'GDUCDTMIN') GT WEIGHT_S(S)),1)=NO;



