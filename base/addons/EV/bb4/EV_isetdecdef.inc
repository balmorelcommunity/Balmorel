$ifi not %STEPCHARGSCHEME%==yes $goto STEPCHARGSCHEME_SET_END
set CHARGINGSTRAGEGY /dumb, smart, v2g/;
set cs(CHARGINGSTRAGEGY,Y);
cs('dumb',Y)$(Y.val =2020) = yes;
cs('dumb',Y)$(Y.val =2030) = yes;
cs('smart',Y)$(Y.val =2040) = yes;
cs('v2g',Y)$(Y.val =2050) = yes;

$label  STEPCHARGSCHEME_SET_END

SET IHASBEV(RRR)  "Internal set: region has BEV demand";
SET IHASPHEV(RRR)  "Internal set: region has PHEV demand";

IHASBEV(IR)$(SUM((Y,S,T),EV_BEV_Dumb(Y,S,T,IR)+EV_BEV_Avail(Y,S,T,IR)))=YES;
IHASPHEV(IR)$(SUM((Y,S,T),EV_PHEV_Dumb(Y,S,T,IR)+EV_PHEV_Avail(Y,S,T,IR)))=YES;

