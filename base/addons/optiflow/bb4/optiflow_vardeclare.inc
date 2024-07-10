
FREE VARIABLE     VOBJQ                                                     "Objective function value assuming parameterised quantities technique";
FREE VARIABLE     VOBJWQ                                                   "Objective function value assuming weighted objective values and parameterised quantities technique";
FREE VARIABLE     VFLOWINDICVALUES(Y,FLOWINDIC)                                  "Quantities of indicators (time weighted) (U)";
POSITIVE VARIABLE VFLOW(Y,AAA,IPROCFROM,IPROCTO,FLOW,S,T)                   "FLOW endogenous quantities between two PROC (U/h)";
POSITIVE VARIABLE VFLOWSOURCE(Y,AAA,PROCSOURCE,FLOW,S,T)                    "FLOW quantities from Source (U/h)";
POSITIVE VARIABLE VFLOWSINK(Y,AAA,PROCSINK,FLOW,S,T)                        "FLOW quantities to Sink (U/h)";
FREE VARIABLE     VFLOWBUFFER(Y,AAA,PROCBUFFER,FLOW,S,T)                    "Net FLOW quantities to Buffer (U/h)";
POSITIVE VARIABLE VFLOWTRANS(Y,IAAAE,IAAAI,PROC,FLOW,S,T)                   "Transport quantities (ton/h)";
POSITIVE VARIABLE VSTORAGEVOL(Y,AAA,PROC,FLOW,S,T)                          "Content in PROCSTORAGE (U)";
POSITIVE VARIABLE VSTORAGEVOL_Y(Y,AAA,PROC,FLOW,S)                         "Content in PROCSTORAGE_Y (U)";
POSITIVE VARIABLE VSTORAGEVOL_ST(Y,AAA,PROC,FLOW,S,T);

POSITIVE VARIABLE VQNODEBALANCE(Y,AAA,PROC,IFLOWIN,IFLOWOUT,S,T,IPLUSMINUS) "Feasibility-ensuring variable with high penalty cost - values are all zero in an OK model instance (U/h)";
POSITIVE VARIABLE VQSOURCEBALANCE(Y,AAA,PROCSOURCE,FLOW,S,T,IPLUSMINUS)     "Feasibility-ensuring variable with high penalty cost - values are all zero in an OK model instance (U/h)";
POSITIVE VARIABLE VQSINKBALANCE(Y,AAA,PROCSINK,FLOW,S,T,IPLUSMINUS)         "Feasibility-ensuring variable with high penalty cost - values are all zero in an OK model instance (U/h)";
POSITIVE VARIABLE VQBUFFERBALANCE(Y,AAA,PROCBUFFER,FLOW,S,T,IPLUSMINUS)     "Feasibility-ensuring variable with high penalty cost - values are all zero in an OK model instance (U/h)";

POSITIVE VARIABLE VQFLOWBOUNDSHAREOUT2OUTUP(Y,AAA,PROC,IFLOWIN,IFLOWOUT,S,T,ILOUPFXSET,IPLUSMINUS)    "Feasibility-ensuring variable with high penalty cost - values are all zero in an OK model instance (U/h)";
POSITIVE VARIABLE VQFLOWBOUNDSHAREOUT2OUTLO(Y,AAA,PROC,IFLOWIN,IFLOWOUT,S,T,ILOUPFXSET,IPLUSMINUS)    "Feasibility-ensuring variable with high penalty cost - values are all zero in an OK model instance (U/h)";
POSITIVE VARIABLE VQFLOWBOUNDSHAREOUT2OUTFX(Y,AAA,PROC,IFLOWIN,IFLOWOUT,S,T,ILOUPFXSET,IPLUSMINUS)    "Feasibility-ensuring variable with high penalty cost - values are all zero in an OK model instance (U/h)";

POSITIVE VARIABLE VQFLOWSHAREOUT2INLO(Y,AAA,PROC,IFLOWIN,IFLOWOUT,S,T,ILOUPFXSET,IPLUSMINUS);
POSITIVE VARIABLE VQFLOWSHAREOUT2INUP(Y,AAA,PROC,IFLOWIN,IFLOWOUT,S,T,ILOUPFXSET,IPLUSMINUS);
POSITIVE VARIABLE VQFLOWSHAREOUT2INFX(Y,AAA,PROC,IFLOWIN,IFLOWOUT,S,T,ILOUPFXSET,IPLUSMINUS);



$ifi %inv%==yes   POSITIVE VARIABLE VPROCKAPACCUMNET(Y,AAA,PROC)         'Accumulated new investments (Presently not: minus any decommissioning of them due to lifetime expiration) this BB4, at end of previous (i.e., start of current) year (MW)';
$ifi %inv%==yes   POSITIVE VARIABLE VPROCKAPNEW(Y,AAA,PROC)                 'New capacity (/h)';  !! se kommentarer til YYY  i bb4.sim


$ontext
$ifi %inv%==yes   BINARY VARIABLE VPROCKAPNEWSCALE_U(Y,AAA,PROC)   "Binary variable to model economy of scale of waste incineration plants" ;
$ifi %inv%==yes   BINARY VARIABLE VPROCKAPDEC_U(Y,AAA,PROC)        "Binary variable to model decomissioning of existing incineration plants" ;
$offtext

$ifi %inv%==yes   POSITIVE VARIABLE VPROCKAPNEWSCALE_U(Y,AAA,PROC)   "Binary variable to model economy of scale of waste incineration plants" ;
$ifi %inv%==yes   POSITIVE VARIABLE VPROCKAPDEC_U(Y,AAA,PROC)        "Binary variable to model decomissioning of existing incineration plants" ;


*-------------------------------------------------------------------------------
*----- Any declarations of variables (and equations) for addon:
*-------------------------------------------------------------------------------
* Addon APKNdisc for discrete size investments in selected PROC
$ifi %APKNdisc%==yes $include "..\addons\OptiFlow\apkndisc\apkndiscvarsequas.inc";

*-------------------------------------------------------------------------------
*----- End: Any declarations of variables for addon
*-------------------------------------------------------------------------------


* At least in development phase: add large but finite .UP on positive variables (IF to be applied in final code, add $conditions):
$ifi %addUP%==yes VFLOWINDICVALUES.UP(Y,FLOWINDIC)      = 1E15;

$ifi %addUP%==yes VFLOWSOURCE.UP(Y,IA,PROCSOURCE,FLOW,S,T)    = ILOUPBOUNDS;  !! May be overwritten by real data later
$ifi %addUP%==yes VFLOWSINK.UP(Y,IA,PROCSINK,FLOW,S,T)        = ILOUPBOUNDS;  !! May be overwritten by real data later
$ifi %addUP%==yes VFLOWBUFFER.LO(Y,IA,PROCBUFFER,FLOW,S,T)    =-ILOUPBOUNDS;  !! May be overwritten by real data later
$ifi %addUP%==yes VFLOWBUFFER.UP(Y,IA,PROCBUFFER,FLOW,S,T)    = ILOUPBOUNDS;  !! May be overwritten by real data later
$ifi %addUP%==yes VFLOWTRANS.UP(Y,IAAAE,IAAAI,FLOW,S,T)       = ILOUPBOUNDS;  !! May be overwritten by real data later
$ifi %addUP%==yes VSTORAGEVOL.UP(Y,IA,PROCSTORAGE,FLOW,S,T)   = ILOUPBOUNDS;  !! May be overwritten by real data later
$ifi %addUP%==yes VPROCKAPNEW.UP(Y,IA,PROC)                   = ILOUPBOUNDS;  !! May be overwritten by real data later


VPROCKAPNEW.UP(Y,IA,PROC)$(APROCKAPNEW(Y,IA,PROC))=777777777777777;
