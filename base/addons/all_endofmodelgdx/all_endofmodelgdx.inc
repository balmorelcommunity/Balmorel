* Addon all_endofmodelgdx for the Balmorel model.

* This will addon provide the file all_endofmodel.gdx to the model folder.
* Sometimes it is convenient to have all available infomation (with most recent values) at this point.
* (If the interest is not on the most recent values, you need not find it in that file.)

* First some slight preprocessing to not get irrelevant information for the VQ variables

$ifi %bb4%==yes $goto bb4begin

* BB1, BB2, BB3 ----------------------------------------------------------------
VQEEQ.M(IR,S,T,IPLUSMINUS)              = 0;
VQHEQ.M(IA,S,T,IPLUSMINUS)              = 0;
VQESTOVOLT.M(IA,S,T,IPLUSMINUS)         = 0;
VQESTOVOLTS.M(IA,S,T,IPLUSMINUS)        = 0;
VQHSTOVOLT.M(IA,S,T,IPLUSMINUS)         = 0;
VQHSTOVOLTS.M(IA,S,T,IPLUSMINUS)        = 0;
VQHYRSSEQ.M(IA,S,IPLUSMINUS)            = 0;
VQHYRSMINMAXVOL.M(IA,S,IPLUSMINUS)      = 0;
VQGEQCF.M(C,FFF,IPLUSMINUS)             = 0;
VQGMINCF.M(C,FFF)                       = 0;
VQGMAXCF.M(C,FFF)                       = 0;
VQGEQRF.M(IR,FFF,IPLUSMINUS)            = 0;
VQGMAXRF.M(IR,FFF)                      = 0;
VQGMINRF.M(IR,FFF)                      = 0;
VQGEQAF.M(IA,FFF,IPLUSMINUS)            = 0;
VQGMAXAF.M(IA,FFF)                      = 0;
VQGMINAF.M(IA,FFF)                      = 0;
VQXK.M(IRE,IRI,S,T,IPLUSMINUS)          = 0;

$ifi not %bb4%==yes $goto bb4end

$label bb4begin

$ifi not %vqdebug%==yes $goto bb4end
* BB4 --------------------------------------------------------------------------
VQEEQ.M(Y,IR,S,T,IPLUSMINUS)            = 0;
VQHEQ.M(Y,IA,S,T,IPLUSMINUS)            = 0;
VQESTOVOLT.M(Y,IA,S,T,IPLUSMINUS)       = 0;
VQESTOVOLTS.M(Y,IA,S,T,IPLUSMINUS)      = 0;
VQHSTOVOLT.M(Y,IA,S,T,IPLUSMINUS)       = 0;
VQHSTOVOLTS.M(Y,IA,S,T,IPLUSMINUS)      = 0;
VQHYRSSEQ.M(Y,IA,S,IPLUSMINUS)          = 0;
VQHYMAXG.M(Y,IA,S,T,IPLUSMINUS)         = 0;
VQGKNACCUMNET.M(Y,IA,G,IPLUSMINUS)      = 0;
VQGKNACCUMGROSS.M(Y,IA,G,IPLUSMINUS)    = 0;
VQXKNACCUMNET.M(Y,IRE,IRI,IPLUSMINUS)   = 0;
VQXKNACCUMGROSS.M(Y,IRE,IRI,IPLUSMINUS) = 0;
VQHYRSMINVOL.M(Y,IA,S,IPLUSMINUS)       = 0;
VQHYRSMAXVOL.M(Y,IA,S,IPLUSMINUS)       = 0;
VQGKE_UP.M(Y,IA,G,S,T,IPLUSMINUS)       = 0;
VQGKH_UP.M(Y,IA,G,S,T,IPLUSMINUS)       = 0;
VQXK_UP.M(Y,IRE,IRI,S,T,IPLUSMINUS)     = 0;
VQKFUEL.M(Y,CCCRRRAAA,FFF)              = 0;
* ------------------------------------------------------------------------------
$label bb4end

execute_unload "all_endofmodel.gdx";

