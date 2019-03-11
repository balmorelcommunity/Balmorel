* Import results Juan Gea Bermúdez 2019.

*Adding Investment addition as exogenous capacities
$ifi %ADDTECHINVEST%==yes  GKFX(Y,IA,G)$GVGKNACCUMNET(Y,IA,G)=GKFX(Y,IA,G)+GVGKNACCUMNET(Y,IA,G);
$ifi %ADDTRANSINVEST%==yes XKFX(Y,IRE,IRI)$XVXKNACCUMNET(Y,IRE,IRI)=XKFX(Y,IRE,IRI)+XVXKNACCUMNET(Y,IRE,IRI);
