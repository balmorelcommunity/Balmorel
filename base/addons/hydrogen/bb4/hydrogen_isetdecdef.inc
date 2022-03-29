Set IHYDROGEN_GH2STO(G)           'Hydrogen storage';
Set IHYDROGEN_GETOH2(G)           'Technologies consuming electricity to produce hydrogen';
Set IHYDROGEN_GEHTOH2(G)          'Technologies consuming electricity and heat to produce hydrogen';
Set IHYDROGEN_GETOHH2(G)          'Technologies consuming electricity to produce heat and hydrogen';
Set IHYDROGEN_GCH4TOH2(G)         'Steam reforming technologies producing hydrogen from natural gas';
Set IHYDROGEN_GH2FUEL(G)          'Power plants using hydrogen as fuel (excluding H2 storage and biomethane technologies)';
SET IHYDROGEN_GH2TOE(G)           'Technology producing only electricity consuming hydrogen'
SET IHYDROGEN_GH2TOEH(G)          'Technology producing electricity and consuming hydrogen'
Set IHYDROGEN_GH2UP(G)            'Fuels needing boost of hydrogen (not used)'
Set IHYDROGEN_GH2TOBIOMETH(G)     'Hydrogen + DAC to synthetic natural gas technologies'
SET IHYDROGEN_GBIOGASMETHANATION(G)  'Technologies consuming biogas, electricity, and H2 to produce biomethane'
SET IHYDROGEN_GBIOGASUPGRADING(G)    'Technologies consuming biogas and electricity to remove CO2 and produce biomethane'
SET IGBIOMETHANE(G)               'Generation technology using biomethane technology'
SET IHYDROGEN(G)                   'Generation technologies producing hydrogen'
;

* Based on 'GDTYPE'
IHYDROGEN_GH2STO(G)   = YES$(GDATA(G,'GDTYPE') EQ HYDROGEN_GH2STO);
IHYDROGEN_GETOH2(G)   = YES$(GDATA(G,'GDTYPE') EQ HYDROGEN_GETOH2);
IHYDROGEN_GEHTOH2(G)  = YES$(GDATA(G,'GDTYPE') EQ HYDROGEN_GEHTOH2);
IHYDROGEN_GETOHH2(G)  = YES$(GDATA(G,'GDTYPE') EQ HYDROGEN_GETOHH2);
IHYDROGEN_GCH4TOH2(G) = YES$(GDATA(G,'GDTYPE') EQ HYDROGEN_GCH4TOH2);
IHYDROGEN_GH2TOE(G)= YES$(GDATA(G,'GDTYPE') EQ HYDROGEN_GH2TOE);
IHYDROGEN_GH2TOEH(G)= YES$(GDATA(G,'GDTYPE') EQ HYDROGEN_GH2TOEH);
IHYDROGEN_GH2TOBIOMETH(G) = YES$(GDATA(G,'GDTYPE') EQ HYDROGEN_GH2TOBIOMETH);
IHYDROGEN_GBIOGASMETHANATION(G) = YES$(GDATA(G,'GDTYPE') EQ HYDROGEN_GBIOGASMETHANATION);
IHYDROGEN_GBIOGASUPGRADING(G) = YES$(GDATA(G,'GDTYPE') EQ HYDROGEN_GBIOGASUPGRADING);

* Based on 'GDFUEL'
IHYDROGEN_GH2FUEL(G)  = YES$(GDATA(G,'GDFUEL') EQ HYDROGEN);
IGBIOMETHANE(G)  = YES$(GDATA(G,'GDFUEL') EQ BIOMETHANE);

IHYDROGEN_GH2FUEL(G) = IHYDROGEN_GH2FUEL(G) - IHYDROGEN_GH2STO(G) - IHYDROGEN_GH2TOBIOMETH(G);

IGDISPATCH(G) = IGDISPATCH(G) + IHYDROGEN_GETOH2(G)+IHYDROGEN_GEHTOH2(G) +IHYDROGEN_GH2STO(G)+IHYDROGEN_GH2TOE(G)+IHYDROGEN_GH2TOEH(G)+IHYDROGEN_GETOHH2(G)
                +IHYDROGEN_GH2TOBIOMETH(G) +IHYDROGEN_GCH4TOH2(G)+IHYDROGEN_GBIOGASMETHANATION(G)+IHYDROGEN_GBIOGASUPGRADING(G);

IGNOTETOH(G)= IGNOTETOH(G)+IHYDROGEN_GH2TOE(G)+IHYDROGEN_GH2TOEH(G)+IHYDROGEN_GH2TOBIOMETH(G)+IHYDROGEN_GCH4TOH2(G)+IHYDROGEN_GBIOGASMETHANATION(G)+IHYDROGEN_GBIOGASUPGRADING(G);

*Ida added last part, GETOH2/GEHTOH2 added here as capacity is on the electricity used
IGKE(G) = IGKE(G)+ IHYDROGEN_GETOH2(G)+IHYDROGEN_GEHTOH2(G)+IHYDROGEN_GH2TOEH(G)+IHYDROGEN_GETOHH2(G) +IHYDROGEN_GH2TOE(G);

*Ida additions - this way GH2TOE is included in capacity constraints and obj function of Balmorel.gms
*Maybe also in some output files. A bit unclear where it is included.
IGKENOSTO(G) = IGKENOSTO(G) + IHYDROGEN_GETOH2(G)+IHYDROGEN_GEHTOH2(G)+IHYDROGEN_GH2TOE(G)+IHYDROGEN_GH2TOEH(G)+IHYDROGEN_GETOHH2(G) ;
IGEE(G) = IGEE(G) +IHYDROGEN_GH2TOE(G);
IGEENOSTO(G) = IGEENOSTO(G) + IHYDROGEN_GH2TOE(G);
IGE(G) = IGE(G)+IHYDROGEN_GH2TOE(G)+IHYDROGEN_GH2TOEH(G);
IGH(G) = IGH(G)+IHYDROGEN_GH2TOEH(G)+IHYDROGEN_GETOHH2(G);


IHYDROGEN(G)= IHYDROGEN_GEHTOH2(G)+IHYDROGEN_GETOHH2(G)+ IHYDROGEN_GETOH2(G) + IHYDROGEN_GH2STO(G)+ IHYDROGEN_GCH4TOH2(G);


*ECONOMIES OF SCALE
SET IXH2KN_ES(IRRRE,IRRRI) "H2 Transmission lines whose cost depends on economy of scale";

IXH2KN_ES(IRRRE,IRRRI)$SUM(XES,XH2KN_ES(IRRRE,IRRRI,XES))=YES;

$ifi not %H2TransInvest%==yes  IXH2KN_ES(IRRRE,IRRRI)=NO;
$ifi not %ES_H2TRANS%==yes  IXH2KN_ES(IRRRE,IRRRI)=NO;
