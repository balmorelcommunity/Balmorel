* Consumption/production of district heat from chiller technologies is added to the heat balance in DC-generation areas.
* Negative sign of the expresion below so that negative DC_GDHE values (consumption of heat) substract to the heat balance.

-(SUM(IAGK_HASORPOT(IY411,IA,G)$IDC_GCHILLER(G), (VGH_T(IY411,IA,G,IS3,T)*DC_GDHE(G))$DC_GDHE(G)))$DC_AG(IA)
