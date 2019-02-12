*To be improved

EPrice_YRST(Y,IR,S,T) = OMONEY*IOF1_*QEEQ.M(Y,IR,S,T)/(IHOURSINST(S,T)*IDISCOUNTFACTOR(Y)*IWEIGHTY(Y));
EPrice_YRST_average(Y,IR)= SUM((S,T), EPrice_YRST(Y,IR,S,T))/336;
CO2_emissions(Y,C)= SUM((IA,IGE)$(IAGK_HASORPOT(Y,IA,IGE) AND ICA(C,IA)),SUM((IS3,T),IHOURSINST(IS3,T)*(IM_CO2(IGE)*IOF0001)*
      IOF3P6 * VGE_T.L(Y,IA,IGE,IS3,T)/(GDATA(IGE,"GDFE")* GEFFRATE(IA,IGE))))
    + SUM((IA,IGH)$(IAGK_HASORPOT(Y,IA,IGH) AND ICA(C,IA)), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_CO2(IGH) * IOF0001) *
      IOF3P6 * GDATA(IGH,"GDCV")*VGH_T.L(Y,IA,IGH,IS3,T)/(GDATA(IGH,"GDFE") * GEFFRATE(IA,IGH))));

Production(Y,C,G)=IOF0001*SUM(IA$ICA(C,IA),SUM((S,T),IHOURSINST(S,T)*VGE_T.L(Y,IA,G,S,T)));
Investments(Y,IA,G)=VGKN.L(Y,IA,G);

*Cross writting report

EPrice_YRST_scen(scenarios,Y,IR,S,T)= EPrice_YRST(Y,IR,S,T);
EPrice_YRST_scen_average(scenarios,Y,IR)= EPrice_YRST_average(Y,IR);
CO2_emissions_scen(scenarios,Y,C)=CO2_emissions(Y,C);
Production_scen(scenarios,Y,C,G)=Production(Y,C,G);
Investments_scen(scenarios,Y,IA,G)=Investments(Y,IA,G);
