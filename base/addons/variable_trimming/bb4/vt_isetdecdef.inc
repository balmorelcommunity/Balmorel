*** TV_G is the set of technologies that can be subject to trimming for IAGKNY

SET TV_G(GGG) 'technologies that are included in variable trimming'  ;

TV_G(G)$IGBPR(G) = YES;
TV_G(G)$IGCND(G) = YES;
TV_G(G)$IGEXT(G) = YES;
TV_G(G)$IGHOB(G) = YES;

TV_G(G)$(GDATA(G,'GDTECHGROUP') eq EXCESS_HEAT) = NO;

