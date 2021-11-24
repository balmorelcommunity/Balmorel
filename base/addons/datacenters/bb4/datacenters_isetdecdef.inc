SET IDC_GSUBGROUP_ABSCHILLER(G)         'Absorption chiller technologies in datacenters';
SET IDC_GSUBGROUP_ELECCHILLER(G)        'Electric chiller technologies in datacenters';
SET IDC_GSUBGROUP_COLDSTORAGE(G)        'Cooling storage technologies in datacenters';
SET IDC_GCHILLER(G)                     'Chiller technologies in datacenters';
SET IDC_GHEATPUMP(G)                    'Heat pump technologies for waste-heat recovery in datacenters';

* Based on 'GDSUBTECHGROUP'
IDC_GSUBGROUP_ABSCHILLER(G)     = YES$(GDATA(G,'GDSUBTECHGROUP') EQ DC_ABSCHILLER);
IDC_GSUBGROUP_ELECCHILLER(G)    = YES$(GDATA(G,'GDSUBTECHGROUP') EQ DC_ELECCHILLER);
IDC_GSUBGROUP_COLDSTORAGE(G)    = YES$(GDATA(G,'GDSUBTECHGROUP') EQ DC_COLDSTORAGE);
IDC_GCHILLER(G)                 = YES$(IDC_GSUBGROUP_ABSCHILLER(G) OR IDC_GSUBGROUP_ELECCHILLER(G));
IDC_GHEATPUMP(G)                = YES$(GDATA(G,'GDSUBTECHGROUP') EQ DC_HEATPUMP);
