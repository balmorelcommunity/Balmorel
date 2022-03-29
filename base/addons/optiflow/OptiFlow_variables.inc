FREE VARIABLE     VOBJW                                                     "Objective function value assuming weighted objective values technique";
FREE VARIABLE     VOBJQ                                                     "Objective function value assuming parameterised quantities technique";
FREE VARIABLE     VOBJWQ                                                    "Objective function value assuming weighted objective values and parameterised quantities technique";
FREE VARIABLE     VFLOWINDICVALUES(FLOWINDIC)                                  "Quantities of indicators (time weighted) (U)";
POSITIVE VARIABLE VFLOW(AAA,IPROCFROM,IPROCTO,FLOW,S,T)                   "FLOW endogenous quantities between two PROC (U/h)";
POSITIVE VARIABLE VFLOWSOURCE(AAA,PROCSOURCE,FLOW,S,T)                    "FLOW quantities from Source (U/h)";
POSITIVE VARIABLE VFLOWSINK(AAA,PROCSINK,FLOW,S,T)                        "FLOW quantities to Sink (U/h)";
FREE VARIABLE     VFLOWBUFFER(AAA,PROCBUFFER,FLOW,S,T)                    "Net FLOW quantities to Buffer (U/h)";
POSITIVE VARIABLE VFLOWTRANS(IAAAE,IAAAI,PROC,FLOW,S,T)                        "Transport quantities (ton/h)";
POSITIVE VARIABLE VSTORAGEVOL(AAA,PROC,FLOW,S,T)                          "Content in PROCSTORAGE (U)";
POSITIVE VARIABLE VSTORAGEVOL_Y(AAA,PROC,FLOW,S)                         "Content in PROCSTORAGE_Y (U)";
POSITIVE VARIABLE VSTORAGEVOL_ST(AAA,PROC,FLOW,S,T);

POSITIVE VARIABLE VQNODEBALANCE(AAA,PROC,IFLOWIN,IFLOWOUT,S,T,IPLUSMINUS) "Feasibility-ensuring variable with high penalty cost - values are all zero in an OK model instance (U/h)";
POSITIVE VARIABLE VQSOURCEBALANCE(AAA,PROCSOURCE,FLOW,S,T,IPLUSMINUS)     "Feasibility-ensuring variable with high penalty cost - values are all zero in an OK model instance (U/h)";
POSITIVE VARIABLE VQSINKBALANCE(AAA,PROCSINK,FLOW,S,T,IPLUSMINUS)         "Feasibility-ensuring variable with high penalty cost - values are all zero in an OK model instance (U/h)";
POSITIVE VARIABLE VQBUFFERBALANCE(AAA,PROCBUFFER,FLOW,S,T,IPLUSMINUS)     "Feasibility-ensuring variable with high penalty cost - values are all zero in an OK model instance (U/h)";

POSITIVE VARIABLE VQFLOWBOUNDSHAREOUT2OUTUP(AAA,PROC,IFLOWIN,IFLOWOUT,S,T,ILOUPFXSET,IPLUSMINUS)    "Feasibility-ensuring variable with high penalty cost - values are all zero in an OK model instance (U/h)";
POSITIVE VARIABLE VQFLOWBOUNDSHAREOUT2OUTLO(AAA,PROC,IFLOWIN,IFLOWOUT,S,T,ILOUPFXSET,IPLUSMINUS)    "Feasibility-ensuring variable with high penalty cost - values are all zero in an OK model instance (U/h)";
POSITIVE VARIABLE VQFLOWBOUNDSHAREOUT2OUTFX(AAA,PROC,IFLOWIN,IFLOWOUT,S,T,ILOUPFXSET,IPLUSMINUS)    "Feasibility-ensuring variable with high penalty cost - values are all zero in an OK model instance (U/h)";

POSITIVE VARIABLE VQFLOWSHAREOUT2INLO(AAA,PROC,IFLOWIN,IFLOWOUT,S,T,ILOUPFXSET,IPLUSMINUS)
POSITIVE VARIABLE VQFLOWSHAREOUT2INUP(AAA,PROC,IFLOWIN,IFLOWOUT,S,T,ILOUPFXSET,IPLUSMINUS)
POSITIVE VARIABLE VQFLOWSHAREOUT2INFX(AAA,PROC,IFLOWIN,IFLOWOUT,S,T,ILOUPFXSET,IPLUSMINUS)



$ifi %inv%==yes   POSITIVE VARIABLE VPROCKAPACCUMNET(YYY,AAA,PROC)         'Accumulated new investments (Presently not: minus any decommissioning of them due to lifetime expiration) this BB4, at end of previous (i.e., start of current) year (MW)';
$ifi %inv%==yes   POSITIVE VARIABLE VPROCKAPNEW(YYY,AAA,PROC)                 'New capacity (/h)';  !! se kommentarer til YYY  i bb4.sim
$ifi %inv%==yes   BINARY VARIABLE VPROCKAPNEWSCALE_U(YYY,AAA,PROC)   "Binary variable to model economy of scale of waste incineration plants" ;
$ifi %inv%==yes   BINARY VARIABLE VPROCKAPDEC_U(YYY,AAA,PROC)        "Binary variable to model decomissioning of existing incineration plants" ;


*-------------------------------------------------------------------------------
*----- Any declarations of variables (and equations) for addon:
*-------------------------------------------------------------------------------
* Addon APKNdisc for discrete size investments in selected PROC
$ifi %APKNdisc%==yes $include "..\addons\OptiFlow\apkndisc\apkndiscvarsequas.inc";

*-------------------------------------------------------------------------------
*----- End: Any declarations of variables for addon
*-------------------------------------------------------------------------------


* At least in development phase: add large but finite .UP on positive variables (IF to be applied in final code, add $conditions):
$ifi %addUP%==yes VFLOWINDICVALUES.UP(FLOWINDIC)      = 1E15;

$ifi %addUP%==yes VFLOWSOURCE.UP(IA,PROCSOURCE,FLOW,S,T)    = ILOUPBOUNDS;  !! May be overwritten by real data later
$ifi %addUP%==yes VFLOWSINK.UP(IA,PROCSINK,FLOW,S,T)        = ILOUPBOUNDS;  !! May be overwritten by real data later
$ifi %addUP%==yes VFLOWBUFFER.LO(IA,PROCBUFFER,FLOW,S,T)    =-ILOUPBOUNDS;  !! May be overwritten by real data later
$ifi %addUP%==yes VFLOWBUFFER.UP(IA,PROCBUFFER,FLOW,S,T)    = ILOUPBOUNDS;  !! May be overwritten by real data later
$ifi %addUP%==yes VFLOWTRANS.UP(IAAAE,IAAAI,FLOW,S,T)       = ILOUPBOUNDS;  !! May be overwritten by real data later
$ifi %addUP%==yes VSTORAGEVOL.UP(IA,PROCSTORAGE,FLOW,S,T)   = ILOUPBOUNDS;  !! May be overwritten by real data later
$ifi %addUP%==yes VPROCKAPNEW.UP(IA,PROC)                   = ILOUPBOUNDS;  !! May be overwritten by real data later


VPROCKAPNEW.UP(IA,PROC)$(APROCKAPNEW(IA,PROC))=1E4;
