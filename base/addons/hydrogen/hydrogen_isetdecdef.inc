Set IGH2STO(G)           'Hydrogen storage';
Set IGETOH2(G)           'Electrolysis plants';
Set IGCH4TOH2(G)         'Steam reforming technologies producing hydrogen from natural gas';
Set IGH2FUEL(G)          'Power plants using hydrogen as fuel';

;

* HansH2 changed:
* The following acronyms correspond in a one-to-one way to the above sets:
ACRONYM     GH2STO, GETOH2, GCH4TOH2, GH2FUEL;


* Based on 'GDTYPE'
IGH2STO(G)   = YES$(GDATA(G,'GDTYPE') EQ GH2STO);                   /* HansH2 changed */
IGETOH2(G)   = YES$(GDATA(G,'GDTYPE') EQ GETOH2);                   /* HansH2 changed */
IGCH4TOH2(G) = YES$(GDATA(G,'GDTYPE') EQ GCH4TOH2);                 /* HansH2 changed */
* Based on 'GDFUEL'
IGH2FUEL(G)  = YES$(GDATA(G,'GDFUEL') EQ GH2FUEL);                  /* HansH2 changed */

IGH2FUEL(G) = IGH2FUEL(G) - IGH2STO(G);

IGDISPATCH(G) = IGDISPATCH(G) + IGETOH2(G) +IGH2STO(G);

IGNOTETOH(G)= IGNOTETOH(G) - IGH2STO(G) - IGETOH2(G) - IGCH4TOH2(G);
IGKE(G) = IGKE(G) + IGETOH2(G);



