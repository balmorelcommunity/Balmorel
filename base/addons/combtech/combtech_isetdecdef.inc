* File combtech_isetdecdef.inc for addon combtech for the Balmorel model

SET IGCOMB1(G)              'Combination technologies, primary, for addon combtech';
SET IGCOMB2(G)              'Combination technologies, secondary with primary in G, for addon combtech';
SET GGCOMB(GGG,GGG      )   'Combination techologies in the same combination, for addon combtech';

IGCOMB1(G) = YES$(GDATA(G,'GDCOMB') EQ 1);
IGCOMB2(G) = YES$(GDATA(G,'GDCOMB') EQ 2);


