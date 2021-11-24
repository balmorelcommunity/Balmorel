
*In each DC-generation area, adds the heat consumption from all chiller technologies, with
*existing or invested capacity, in that DC-generation area to the local heat balance.
+(SUM(IAGK_HASORPOT(IY411,IA,G)$IDC_GCHILLER(G), (VGH_T(IY411,IA,G,IS3,T)*DC_GDHE(G))$DC_GDHE(G)))$DC_AG(IA)




