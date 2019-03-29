*-----DECLARATION--------------

PARAMETERS
ITV_FIXED(Y,AAA,GGG) 'fixed costs including investment costs (€/MW/Y)'
ITV_VAREL(Y,AAA,GGG) 'variable costs for el production (€/MWh)'
ITV_VARHEAT(Y,AAA,GGG) 'variable costs for heat production (€/MWh)'

* parameters defined in vt_sim_agknytrim.sim
ITV_CHEAPESTCND(Y,AAA,TV_FLH) 'Annual cost of electricity for the cheapest CND unit, not condiering techs with fuel limits (€/MW/Y)'
ITV_CHEAPESTHOB(Y,AAA,TV_FLHHEAT) 'Annual cost of heat for the cheapest HOB unit, not condiering techs with fuel limits (€/MW/Y)'
ITV_CHEAPESTCNDR(Y,RRR,TV_FLH) 'Annual cost of electricity for the cheapest CND unit per region, not condiering techs with fuel limits (€/MW/Y)'

ITV_ANNUALCOST_E(Y,AAA,G,TV_FLH,TV_FLHHEAT,TV_PR) 'Annual cost of electricity generation per year in each segment (€/MW/Y)'
ITV_ANNUALCOST_H(Y,AAA,G,TV_FLH,TV_FLHHEAT,TV_PR) 'Annual cost of heat generation per year in each segment (€/MW/Y)'

ITV_CHEAPEST_E(Y,AAA,TV_FLH,TV_FLHHEAT,TV_PR) 'Annual cost of electricity for the cheapest technology, not considering techns with fuel limits (€/MW/Y)'
ITV_CHEAPEST_H(Y,AAA,TV_FLH,TV_FLHHEAT,TV_PR) 'Annual cost of heat for the cheapest technology, not considering techns with fuel limits (€/MW/Y)'
ITV_CHEAPEST_EF(Y,AAA,TV_FLH,TV_FLHHEAT,TV_PR) 'Annual cost of electricity for the cheapest technology, also considering techns with fuel limits (€/MW/Y)'
ITV_CHEAPEST_HF(Y,AAA,TV_FLH,TV_FLHHEAT,TV_PR) 'Annual cost of heat for the cheapest technology, also considering techns with fuel limits (€/MW/Y)'
;



*-------------------------------------------------
* Defining the costs
*-------------------------------------------------

* Fixed costs including investment costs
ITV_FIXED(Y,IA,G)$(IAGKNY_IY411(Y,IA,G)) = IOF1000*GOMFCOST(IA,G)  + IOF1000000*(GINVCOST(IA,G)*(SUM(C$ICA(C,IA),ANNUITYCG(C,G))));

* Variable costs for electricity generation
ITV_VAREL(Y,IA,G)$(IAGKNY_IY411(Y,IA,G) AND  IGNOTETOH(G) AND IGE(G)) =
           GOMVCOST(IA,G)$IGKE(G)                                                                     !! variable operation costs
         + (SUM(FFF$IGF(G,FFF), FUELPRICE(Y,IA,FFF) * IOF3P6 )                                 !! fuel costs
         + IM_CO2(G)*IOF0001 * IOF3P6 * SUM(C$ICA(C,IA), M_POL(Y,"TAX_CO2",C))                 !! CO2 costs
         + IM_SO2(G)*IOF0001 * IOF3P6 * SUM(C$ICA(C,IA), M_POL(Y,"TAX_SO2",C))                 !! SO2 costs
         + GDATA(G,'GDNOX')*IOF0000001 * SUM(C$ICA(C,IA), M_POL(Y,"TAX_NOX",C))                !! NOX costs
       )/(GDATA(G,'GDFE')*(1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G)))

$ifi %TAXES%==yes         + SUM(C$ICA(C,IA), TAX_G_EL(Y,C,G))
$ifi %TAXES%==yes         + (SUM(C$ICA(C,IA),TAX_F_EL(Y,C,G))
$ifi %TAXES%==yes         +      SUM(C$ICA(C,IA),TAX_F(Y,C,G))  ) / (GDATA(G,'GDFE') * (1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G)))
;

*Variable cost for heat generation
ITV_VARHEAT(Y,IA,G)$(IAGKNY_IY411(Y,IA,G) AND IGH(G))  =
                   (GOMVCOST(IA,G) * GDATA(G,'GDCV'))$IGKH(G)
                 + GDATA(G,'GDCV') * (
                   SUM(FFF$IGF(G,FFF), FUELPRICE(Y,IA,FFF) * IOF3P6 )
                 + IM_CO2(G) * IOF0001 * IOF3P6 * SUM(C$ICA(C,IA), M_POL(Y,"TAX_CO2",C))
                 + IM_SO2(G) * IOF0001 * IOF3P6 * SUM(C$ICA(C,IA), M_POL(Y,"TAX_SO2",C))
                 + GDATA(G,'GDNOX') * IOF0000001 * SUM(C$ICA(C,IA), M_POL(Y,"TAX_NOX",C))
                 )  /(GDATA(G,'GDFE') * (1$(NOT GEFFRATE(IA,G)) + GEFFRATE(IA,G)))

$ifi %TAXES%==yes      + SUM(C$ICA(C,IA),TAX_G_HEAT(Y,C,G))
$ifi %TAXES%==yes      + (       SUM(C$ICA(C,IA), TAX_F_HEAT(Y,C,G))
$ifi %TAXES%==yes                + SUM(C$ICA(C,IA), TAX_F(Y,C,G))  ) / (GDATA(G,'GDFE') * (1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G)))
;