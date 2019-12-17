* Ancilliary services by Juan Gea Bermúdez 2019.

SET IASFCRUP(G) "Ancilliary service: technology allowed to provide for frequency containment reserves for up regulation";
SET IASAFRRUP(G) "Ancilliary service: technology allowed to provide for automatic frequency restoration reserves for up regulation";
SET IASMFRRUP(G) "Ancilliary service: technology allowed to provide for manual frequency restoration reserves for up regulation";
SET IASMRRUP(G) "Ancilliary service: technology allowed to provide for manual replacement reserves for up regulation";

SET IASFCRDOWN(G) "Ancilliary service: technology allowed to provide for frequency containment reserves for down regulation";
SET IASAFRRDOWN(G) "Ancilliary service: technology allowed to provide for automatic frequency restoration reserves for down regulation";
SET IASMFRRDOWN(G) "Ancilliary service: technology allowed to provide for manual frequency restoration reserves for down regulation";
SET IASMRRDOWN(G) "Ancilliary service: technology allowed to provide for manual replacement reserves for down regulation";


*Frequency containment reserves
IASFCRUP(IGUC)$(GDATA(IGUC,'GDUCRAMPU') GE MIN_RAMPING_FCR AND IGKE(IGUC))=YES;
IASFCRUP(IGUC)$(GDATA(IGUC,'GDUCRAMPD') GE MIN_RAMPING_FCR AND IGEH(IGUC))=YES;
IASFCRDOWN(IGUC)$(GDATA(IGUC,'GDUCRAMPD') GE MIN_RAMPING_FCR AND IGKE(IGUC))=YES;
IASFCRDOWN(IGUC)$(GDATA(IGUC,'GDUCRAMPU') GE MIN_RAMPING_FCR AND IGEH(IGUC))=YES;

*Manual frequency restoration reserves
IASAFRRUP(IGUC)$(GDATA(IGUC,'GDUCRAMPU') GE MIN_RAMPING_AFRR AND IGKE(IGUC))=YES;
IASAFRRUP(IGUC)$(GDATA(IGUC,'GDUCRAMPD') GE MIN_RAMPING_AFRR AND IGEH(IGUC))=YES;
IASAFRRDOWN(IGUC)$(GDATA(IGUC,'GDUCRAMPD') GE MIN_RAMPING_AFRR AND IGKE(IGUC))=YES;
IASAFRRDOWN(IGUC)$(GDATA(IGUC,'GDUCRAMPU') GE MIN_RAMPING_AFRR AND IGEH(IGUC))=YES;
IASAFRRUP(IGUC)$(GDATA(IGUC,'GDTECHGROUP') EQ ELECTRICITY_BATTERY)=NO;
IASAFRRDOWN(IGUC)$(GDATA(IGUC,'GDTECHGROUP') EQ ELECTRICITY_BATTERY)=NO;

*Automatic frequency restoration reserves
IASMFRRUP(IGUC)$(GDATA(IGUC,'GDUCRAMPU') GE MIN_RAMPING_MFRR  AND IGKE(IGUC) AND GDATA(IGUC,'GDUCDTMIN') LE MAX_STARTTIME_MFRR)=YES;
IASMFRRDOWN(IGUC)$(GDATA(IGUC,'GDUCRAMPU') GE MIN_RAMPING_MFRR AND IGEH(IGUC) AND GDATA(IGUC,'GDUCDTMIN') LE MAX_STARTTIME_MFRR)=YES;
IASMFRRUP(IGUC)$(GDATA(IGUC,'GDTECHGROUP') EQ ELECTRICITY_BATTERY)=NO;
IASMFRRDOWN(IGUC)$(GDATA(IGUC,'GDTECHGROUP') EQ ELECTRICITY_BATTERY)=NO;

*Manual replacement reserves
IASMRRUP(IGUC)$(IGKE(IGUC) AND GDATA(IGUC,'GDUCDTMIN') LE MAX_STARTTIME_MRR)=YES;
IASMRRDOWN(IGUC)$(IGEH(IGUC) AND GDATA(IGUC,'GDUCDTMIN') LE MAX_STARTTIME_MRR)=YES;
IASMRRUP(IGUC)$(GDATA(IGUC,'GDTECHGROUP') EQ ELECTRICITY_BATTERY)=NO;
IASMRRDOWN(IGUC)$(GDATA(IGUC,'GDTECHGROUP') EQ ELECTRICITY_BATTERY)=NO;

*Variable production technologies (solar, wind, wave, etc) are not allowed to provide reserves
IASFCRUP(IGUC)$(NOT(IGDISPATCH(IGUC)))=NO;
IASAFRRUP(IGUC)$(NOT(IGDISPATCH(IGUC)))=NO;
IASMFRRUP(IGUC)$(NOT(IGDISPATCH(IGUC)))=NO;
IASMRRUP(IGUC)$(NOT(IGDISPATCH(IGUC)))=NO;
IASFCRDOWN(IGUC)$(NOT(IGDISPATCH(IGUC)))=NO;
IASAFRRDOWN(IGUC)$(NOT(IGDISPATCH(IGUC)))=NO;
IASMFRRDOWN(IGUC)$(NOT(IGDISPATCH(IGUC)))=NO;
IASMRRDOWN(IGUC)$(NOT(IGDISPATCH(IGUC)))=NO;
