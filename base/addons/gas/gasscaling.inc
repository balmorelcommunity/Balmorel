$ifi %bb1%==yes balbase1.scaleopt=1;
$ifi %bb1%==yes balbase1.scaleopt=1;
$ifi %bb1%==yes balbase1.scaleopt=1;


VGUD.scale(IA,S,T)$ICA('Denmark',IA)                 = 1/(1+2*(IDGRES_Y(IA,S,T)+IDGOTH_Y(IA,S,T)));
VSTOCK.scale(STORE,STORETYPE,S,T)  = 1/(1+ISTORE_MAX(STORE,STORETYPE));
VINJ.scale(STORE,STORETYPE,S,T)    = 1/(1+IINJ_MAX(STORE,STORETYPE));
VEXT.scale(STORE,STORETYPE,S,T)    = 1/(1+IEXT_MAX(STORE,STORETYPE));
VEXP.scale(SOURCE,S,T)             = 1/(1+IEXP_MAX(SOURCE));
VSUP.scale(SOURCE,S,T)             = 1/(1+ISUPPLY_MAX(SOURCE));
VTC_EN_Y.scale                     = 1/10000;
VTC_EN_M.scale(IMONTH)             = 1/1000;
VTC_EN_W.scale(S)                  = 1/1000;
VTC_EN_D.scale(S,DAY)              = 1/1000;
VTC_EX_Y.scale                     = 1/10000;
VTC_EX_M.scale(IMONTH)             = 1/1000;
VTC_EX_W.scale(S)                  = 1/1000;
VTC_EX_D.scale(S,DAY)              = 1/1000;
VSC.scale(SCON)                    = 1/(1+SUM((STORE,STORETYPE),ISTORE_MAX(STORE,STORETYPE)));
* VGINFINV(NGINV) - Well scaled
VGINVSTORE.scale(STORE,STORETYPE)  = 1/10000;
VGINVEXT.scale(STORE,STORETYPE)    = 1/1000;
VGINVINJ.scale(STORE,STORETYPE)    = 1/1000;


   VOBJ.scale                      =1/1000;
   VGE_T.scale(IAGK_Y(IA,G),S,T)           =1/(1+VGE_T.up(IA,G,S,T)$(VGE_T.up(IA,G,S,T) LE INF));
   VGH_T.scale(IAGK_Y(IA,G),S,T)           =1/(1+VGH_T.up(IA,G,S,T)$(VGH_T.up(IA,G,S,T) LE INF));
   VX_T.scale(IRE,IRI,S,T)         =1/(1+IXKINI_Y(IRE,IRI));
   VGEN_T.scale(IAGKN(IA,G),S,T)          =1/1000;
   VGHN_T.scale(IAGKN(IA,G),S,T)          =1/1000;
   VGKN.scale(IAGKN(IA,G))                =1/1000;
   VXKN.scale(IRE,IRI)             =1/(1+IXKINI_Y(IRE,IRI));
   VHYRS_S.scale(IA,S)             =1/1000000;
   VGE2LEVEL.scale(IAGK_Y(IA,IG2LEVEL),S,DAYTYPE) =1/(1+Sum(t,VGE_T.up(IA,IG2LEVEL,S,T)$(VGE_T.up(IA,IG2LEVEL,S,T) LE INF)));
   VESTOLOADT.scale(IA,S,T)        =1/(1+Sum(IAGK_Y(IA,IGESTO),VGE_T.up(IA,IGESTO,S,T)$(VGE_T.up(IA,IGESTO,S,T) LE INF)));
   VHSTOLOADT.scale(IA,S,T)        =1/(1+Sum(IAGK_Y(IA,IGHSTO),VGH_T.up(IA,IGHSTO,S,T)$(VGH_T.up(IA,IGHSTO,S,T) LE INF)));
   VESTOVOLT.scale(IA,S,T)         =1/(1+Sum(IAGK_Y(IA,IGESTO),VGE_T.up(IA,IGESTO,S,T)$(VGE_T.up(IA,IGESTO,S,T) LE INF)));
   VHSTOVOLT.scale(IA,S,T)         =1/(1+Sum(IAGK_Y(IA,IGHSTO),VGH_T.up(IA,IGHSTO,S,T)$(VGH_T.up(IA,IGHSTO,S,T) LE INF)));
$ifi %X3V%==yes VX3VIM_T.scale(X3VX(IR,X3VPLACE),X3VSTEP,S,T) = 1/(1+VX3VIM_T.up(IR,X3VPLACE,X3VSTEP,S,T));
$ifi %X3V%==yes VX3VEX_T.scale(X3VX(IR,X3VPLACE),X3VSTEP,S,T) = 1/(1+VX3VEX_T.up(IR,X3VPLACE,X3VSTEP,S,T));

balbase2.optfile=1;