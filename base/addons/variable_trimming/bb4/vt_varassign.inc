$ifi %GenInvest%==yes         IAGK_NOINVEST(Y,IA,G)$(IY411FIRST(Y) AND IAGKN(IA,G) AND (YVALUE(Y+1) GT GDATA(G,'GDLASTYEAR')) AND NOT VGKNACCUMNET.L(Y,IA,G)) = yes;
display iagk_noinvest;