*Offshore grid add-on. Implemented by Juan Gea Bermudez 2019

*IMPORTANT!: The following code only works if the years are optimized consecutively. For example, this two-year mode optimization would not provide coherent results: [2020,2040] and [2030;2050]

$ifi %TransInvest%==yes VXLAMBDA.FX(IY411FIRST,IRE,IRI,XES)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411FIRST)),IXKN(Y,IRE,IRI)) AND IXKN_ES(IRE,IRI))=VXLAMBDA.L(IY411FIRST,IRE,IRI,XES);
$ifi %TechInvest%==yes  VGLAMBDA.FX(IY411FIRST,IA,G,XES)$(SUM(Y$(YVALUE(Y) LE YVALUE(IY411FIRST)),IAGKNY(Y,IA,G)) AND IGKN_ES(G))=VGLAMBDA.L(IY411FIRST,IA,G,XES);
