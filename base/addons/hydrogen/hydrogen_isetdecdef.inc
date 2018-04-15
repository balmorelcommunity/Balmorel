Set IHYDROGEN_GH2STO(G)           'Hydrogen storage';
Set IHYDROGEN_GETOH2(G)           'Electrolysis plants - capacity on electricity';
Set IHYDROGEN_GEHTOH2(G)          'SOEC using both electricity and heat to produce H2 - capacity on electricity';
Set IHYDROGEN_GCH4TOH2(G)         'Steam reforming technologies producing hydrogen from natural gas - capacity on hydrogen';
Set IHYDROGEN_GH2FUEL(G)          'Power plants using hydrogen as fuel';
*IDA new additions
SET IHYDROGEN_GH2TOE(G)           'Solid oxide fuel cells'
Set IHYDROGEN_GH2UP(G)            'Fuels needing boost of hydrogen'
;

* Based on 'GDTYPE'
IHYDROGEN_GH2STO(G)   = YES$(GDATA(G,'GDTYPE') EQ HYDROGEN_GH2STO);
IHYDROGEN_GETOH2(G)   = YES$(GDATA(G,'GDTYPE') EQ HYDROGEN_GETOH2);
IHYDROGEN_GCH4TOH2(G) = YES$(GDATA(G,'GDTYPE') EQ HYDROGEN_GCH4TOH2);

*IDA new additions
IHYDROGEN_GH2UP(G)= YES$(GDATA(G,'GDFUEL') EQ THERMGAS_H2 OR GDATA(G,'GDFUEL') EQ BIOGAS_H2);
IHYDROGEN_GH2TOE(G)= YES$(GDATA(G,'GDTYPE') EQ HYDROGEN_GH2TOE);
IHYDROGEN_GEHTOH2(G)  = YES$(GDATA(G,'GDTYPE') EQ HYDROGEN_GEHTOH2);

* Based on 'GDFUEL'
IHYDROGEN_GH2FUEL(G)  = YES$(GDATA(G,'GDFUEL') EQ HYDROGEN);
*Ida This was here before just hydrogen: HYDROGEN_GH2FUEL);

IHYDROGEN_GH2FUEL(G) = IHYDROGEN_GH2FUEL(G) - IHYDROGEN_GH2STO(G);

IGDISPATCH(G) = IGDISPATCH(G) + IHYDROGEN_GETOH2(G) +IHYDROGEN_GH2STO(G)+IHYDROGEN_GEHTOH2(G);

*Not electrolysis plants
IGNOTETOH(G)= IGNOTETOH(G)+IHYDROGEN_GH2TOE(G);




*Ida added last part, GETOH2/GEHTOH2 added here as capacity is on the electricity used
IGKE(G) = IGKE(G) + IHYDROGEN_GETOH2(G)+IHYDROGEN_GH2TOE(G)+IHYDROGEN_GEHTOH2(G);

*Ida additions - this way GH2TOE is included in capacity constraints and obj function of Balmorel.gms
*Maybe also in some output files. A bit unclear where it is included.
IGKENOSTO(G) = IGKENOSTO(G) + IHYDROGEN_GETOH2(G)+IHYDROGEN_GH2TOE(G)+IHYDROGEN_GEHTOH2(G);
IGEE(G) = IGEE(G) +IHYDROGEN_GH2TOE(G);
IGEENOSTO(G) = IGEENOSTO(G) + IHYDROGEN_GH2TOE(G) ;
IGE(G) = IGE(G)+IHYDROGEN_GH2TOE(G);
IGH(G) = IGH(G)+IHYDROGEN_GETOH2(G);



