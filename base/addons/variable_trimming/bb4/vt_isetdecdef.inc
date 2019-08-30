** ITV_G is the set of technologies that can be subject to trimming for IAGKNY
** This can be used as a switch to what technologies to include for the addon
SET ITV_G(GGG) 'technologies that are included in variable trimming'  ;

ITV_G(G)$IGBPR(G) = YES;
ITV_G(G)$IGCND(G) = YES;
ITV_G(G)$IGEXT(G) = YES;
ITV_G(G)$IGHOB(G) = YES;
$ifi %COMBTECH%==yes ITV_G(G)$IGCOMB1(G) = NO;
$ifi %COMBTECH%==yes ITV_G(G)$IGCOMB2(G) = NO;

ITV_G(G)$(GDATA(G,'GDTECHGROUP') eq EXCESS_HEAT) = NO;



SETS
ITV_HEATA(Y,AAA)'areas with heat consumption'
ITV_FILTER(Y,AAA,TV_FLH,TV_FLHHEAT,TV_PR)'instances of TV_FLH, TV_FLHHEAT and TV_PR to calculate in each areas'
ITV_REQMIN(Y,AAA,GGG) 'technologies with minimum usage requirements'
ITV_REQFX(Y,AAA,GGG) 'technologies with fixed usage requirements'
ITV_REQMAX(Y,AAA,GGG) 'technologies with maximum usage requirements'
ITV_REQEMIN(Y,AAA,GGG) 'technologies with minimum electricity generation requirements'
ITV_REQEMAX(Y,AAA,GGG) 'technologies with maximum electricity generation constraints'
ITV_ZERO(Y,AAA,GGG) 'technologies not allowed because of limits (is EPS)'
ITV_ZEROEL(Y,AAA,GGG) 'electricity generating technologies not allowed because of limits (is EPS)'

* The following sets are defined in vt_sim_agknytrim.sim
IAGKNY_IY411(YYY,AAA,GGG) 'set of allowed investment options'
ITV_IY411(Y)    'remaining years of the balbase4 model within the IY411-loop'
ITV_CHEAPEST(YYY,AAA,G,TV_FLH,TV_FLHHEAT,TV_PR) 'the cheapest technology in each segment'
ITV_NEVERCHEAP(YYY,AAA,GGG) 'technologies not cheapest in any segment '
ITV_NEVERCHEAP2(YYY,AAA,GGG) 'technologies not cheapest in any segment, or unallowed due to fuel or emission constraint, except technologies that has minimum fuel requirements'
ITVCOMPARED(Y,Y,AAA,G) 'technologies compared in each loop of variable trimming (for testing and debugging only)'
;

*----------------------------------------------------------------
* initialization:
*----------------------------------------------------------------

** IAGKNY_IY411 is first used in this file for the initialization. It is later used dynamically in vt_sim_agknytrim.sim
IAGKNY_IY411(Y,IA,G)$(IGKFIND(G) AND AGKN(IA,G) AND ITV_G(G) AND (Y.VAL LE (GDATA(G,'GDLASTYEAR') + GDATA(G,'GDLIFETIME')))$GDATA(G,'GDLASTYEAR') AND (Y.VAL GE GDATA(G,'GDFROMYEAR')) AND (Y.VAL GE GINVESTSTART)) = YES;

* Areas with heat demand:
ITV_HEATA(Y,IA)$SUM(DHUSER, DH(Y,IA,DHUSER)) = YES;


** ITV_FILTER is used to limit the amount of combination of FLH, FLHHEAT and PR considered. Depending on investment options in the area and if there is heat demand some cases can be disregarded.

* Areas without heat consumption do not consider cases with heat generation
ITV_FILTER(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR)$(NOT ITV_HEATA(Y,IA) AND SUM(G, IAGKNY_IY411(Y,IA,G)) AND (ORD(TV_FLHHEAT) EQ 1) AND (ORD(TV_PR) EQ 1)) = YES;

* Areas with BPR or HOB technologies consider cases where FLH and FLHHEAT are equal
ITV_FILTER(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR)$(ITV_HEATA(Y,IA) AND SUM(G$(IGHOB(G) OR IGBPR(G)), IAGKNY_IY411(Y,IA,G)) AND (TV_FLH.VAL EQ TV_FLHHEAT.VAL)) = YES;

* Areas with EXT technologies consider cases where FLH is greater or equal to FLHHEAT
ITV_FILTER(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR)$(ITV_HEATA(Y,IA) AND SUM(IGEXT, IAGKNY_IY411(Y,IA,IGEXT)) AND (TV_FLH.VAL GE TV_FLHHEAT.VAL)) = YES;

* Areas with bypass technologies consider cases where FLH is less or equal to FLHHEAT
ITV_FILTER(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR)$(ITV_HEATA(Y,IA) AND SUM(IGBYPASS, IAGKNY_IY411(Y,IA,IGBYPASS)) AND (TV_FLH.VAL LE TV_FLHHEAT.VAL)) = YES;





