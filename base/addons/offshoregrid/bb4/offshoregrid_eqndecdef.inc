*Offshore grid add-on. Implemented by Juan Gea Bermudez 2019

*Equations for modelling economy of scale
   QVXKN_ES(YYY,IRRRE,IRRRI)  'Equation to ensure the proper capacity when using SOS2 variables'
   QXLAMBDA_ES(YYY,IRRRE,IRRRI) 'Equation to ensure all the Lambda variables are equal to 1 for the same transmission line'
   QVGKN_ES(YYY,AAA,G)  'Equation to ensure the proper capacity when using SOS2 variables'
   QGLAMBDA_ES(YYY,AAA,G) 'Equation to ensure all the Lambda variables are equal to 1 for the same technology'


QVXKN_ES(IY411,IRE,IRI)$((IXKN(IRI,IRE) OR IXKN(IRE,IRI)) AND (IXKN_ES(IRE,IRI)))..
   VXKN(IY411,IRE,IRI) =E= SUM(XES,VXLAMBDA(IY411,IRE,IRI,XES)*XKN_ES(IRE,IRI,XES));

QXLAMBDA_ES(IY411,IRE,IRI)$((IXKN(IRI,IRE) OR IXKN(IRE,IRI)) AND (IXKN_ES(IRE,IRI)))..
  SUM(XES,VXLAMBDA(IY411,IRE,IRI,XES)) =E= 1;

QVGKN_ES(IY411,IA,G)$(IGKN_ES(G) AND IAGKNY(IY411,IA,G))..
   VGKN(IY411,IA,G) =E= SUM(XES,VGLAMBDA(IY411,IA,G,XES)*GKN_ES(G,XES));


QGLAMBDA_ES(IY411,IA,G)$(IGKN_ES(G) AND IAGKNY(IY411,IA,G))..
    SUM(XES,VGLAMBDA(IY411,IA,G,XES)) =E= 1;



