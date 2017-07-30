Set IHYDROGEN_GH2STO(G)           'Hydrogen storage';
Set IHYDROGEN_GETOH2(G)           'Electrolysis plants';
Set IHYDROGEN_GCH4TOH2(G)         'Steam reforming technologies producing hydrogen from natural gas';
Set IHYDROGEN_GH2FUEL(G)          'Power plants using hydrogen as fuel';

;

* HansH2 changed:
* The following acronyms correspond in a one-to-one way to the above sets:
ACRONYM HYDROGEN_GH2STO, HYDROGEN_GETOH2, HYDROGEN_GCH4TOH2, HYDROGEN_GH2FUEL;


* Based on 'GDTYPE'
IHYDROGEN_GH2STO(G)   = YES$(GDATA(G,'GDTYPE') EQ HYDROGEN_GH2STO);                   /* HansH2 changed */
IHYDROGEN_GETOH2(G)   = YES$(GDATA(G,'GDTYPE') EQ HYDROGEN_GETOH2);                   /* HansH2 changed */
IHYDROGEN_GCH4TOH2(G) = YES$(GDATA(G,'GDTYPE') EQ HYDROGEN_GCH4TOH2);                 /* HansH2 changed */
* Based on 'GDFUEL'
IHYDROGEN_GH2FUEL(G)  = YES$(GDATA(G,'GDFUEL') EQ HYDROGEN_GH2FUEL);                  /* HansH2 changed */

IHYDROGEN_GH2FUEL(G) = IHYDROGEN_GH2FUEL(G) - IHYDROGEN_GH2STO(G);

IGDISPATCH(G) = IGDISPATCH(G) + IHYDROGEN_GETOH2(G) +IHYDROGEN_GH2STO(G);

IGNOTETOH(G)= IGNOTETOH(G) - IHYDROGEN_GH2STO(G) - IHYDROGEN_GETOH2(G) - IHYDROGEN_GCH4TOH2(G);
IGKE(G) = IGKE(G) + IHYDROGEN_GETOH2(G);



