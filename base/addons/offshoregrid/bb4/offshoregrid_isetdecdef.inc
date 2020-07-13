*Offshore grid add-on. Implemented by Juan Gea Bermudez 2019

SET IGKN_ES(GGG)         "Technologies lines whose cost depends on economy of scale";
SET IXKN_ES(IRRRE,IRRRI) "Transmission lines whose cost depends on economy of scale";


IGKN_ES(GGG)$SUM(XES,GKN_ES(GGG,XES))=YES;
IXKN_ES(IRRRE,IRRRI)$SUM(XES,XKN_ES(IRRRE,IRRRI,XES))=YES;

$ifi not %TechInvest%==yes   IGKN_ES(GGG)=NO;
$ifi not %TransInvest%==yes  IXKN_ES(IRRRE,IRRRI)=NO;


