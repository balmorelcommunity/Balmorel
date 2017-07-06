
SET AGKNDISC(AAA,G) 'Areas for possible location of new technologies taking discrete capacity size investments';

*AGKNDISC(AAA,'backstop') = yes;
AGKNDISC('DK_W_1','backstop') = yes;
AGKNDISC('FI_R_Rural','backstop') = yes;
AGKNDISC('DK_E_1','backstop') = yes;

AGKNDISC(aaa,'backstop')$RRRAAA('dk_e',aaa)=yes;
AGKNDISC(aaa,'backstop')$RRRAAA('dk_w',aaa)=yes;



* med mulighed i alle AAA taget det meget lagn tid at finde den optimale løsning:
*DK_E_4      BACKSTOP    AGKNDISCSIZE1           1.00     6000.00
*DK_W_1      BACKSTOP    AGKNDISCSIZE1           1.00     6000.00
*FI_R_Rural  BACKSTOP    AGKNDISCSIZE2           1.00    12000.00
*NO_O_Rural  BACKSTOP    AGKNDISCSIZE1           1.00     6000.00


