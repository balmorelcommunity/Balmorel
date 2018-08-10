* File combtech_isetdecdef.inc for addon combtech for the Balmorel model

SET IGCOMB1(G)              'Combination technologies, primary, for addon combtech';
SET IGCOMB2(G)              'Combination technologies, secondary with primary in G, for addon combtech';

loop((G,IGALIAS)$GGCOMB(G,IGALIAS),
IGCOMB1(G) = YES$(GDATA(G,'GDCOMB') EQ 1);
IGCOMB2(IGALIAS) = YES$(GDATA(IGALIAS,'GDCOMB') EQ 2);

);


