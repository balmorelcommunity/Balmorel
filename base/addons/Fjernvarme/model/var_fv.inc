* Variables regarding district heating

Positive Variables
                    VIHFV(AAA,IAAAI,STEPFV)         'Extenstion of heat in each step'
                    VDHFV(AAA,IAAAI,S,T)            'Production of heat in time period'
                    VGH_IND(AAA,G)                  'Level of production on individual technologies'
                    VQGH_IND(AAA,G,S,T,IPLUSMINUS)  'Penalty on diviation from profile generation'
                    VGHN_IND(AAA,G)                 'Level of production on individual technologies'
                    VQGHN_IND(AAA,G,S,T,IPLUSMINUS) 'Penalty on diviation from profile generation'
;

* Initialize.
VIHFV.l(IA,AIND,STEPP)$AINDN(IA,AIND) =0;
