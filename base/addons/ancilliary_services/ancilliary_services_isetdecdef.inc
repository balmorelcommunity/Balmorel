* Ancilliary services by Juan Gea Bermúdez 2019.


SET IASG(G) "Ancilliary service: technology allowed to provide for ancilliary services";

IASG(IGUC)$(GDATA(IGUC,'GDUCRAMPU') GE AS_MIN_RAMPING AND GDATA(IGUC,'GDUCRAMPD') GE AS_MIN_RAMPING AND IGKE(IGUC))=YES;

*Non-flexible CHP units are not allowed to participate in the reserves markets
IASG(IGBPR)$(NOT (IGBYPASS(IGBPR)))=NO;
*Storage is not allowed to participate in the reserves markets
IASG(IGESTOALL)=NO;
IASG(IGHYRS)=NO;
*Variable production technologies are not allowed to participate in the reserves markets
IASG(IGHYRR)=NO;
IASG(IGWND)=NO;
IASG(IGSOLE)=NO;
IASG(IGWAVE)=NO;


