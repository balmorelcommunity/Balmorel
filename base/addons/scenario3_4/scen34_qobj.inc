** Not currently in use
** Tax from scenario 1 or 2 is added as a capacity based tax
*+ SUM(C, SUM(IAGK_HASORPOT(Y,IA,IGETOH)$ICA(C,IA),  TAX_GETOH('2030',C)  * (VGKNACCUMNET(Y,IA,IGETOH) + GKFX(Y,IA,IGETOH)) /(GDATA(IGETOH,'GDFE') *(1$(NOT GEFFRATE(IA,IGETOH)) + GEFFRATE(IA,IGETOH)))     ))


