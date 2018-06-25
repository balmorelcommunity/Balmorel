
SET IAGKNDISC(AAA,G) 'Areas for possible location of new technologies taking discrete capacity size investments';

* Based on 'GDTYPE'
IAGKNDISC(AAA,G)   = YES$(GDATA(G,'GDTYPE') EQ GETOH);

*AGKNDISC(AAA,GDATA('GDCOMB')) = yes;
*AGKNDISC('DK1_Large',GDATA(G,'GDCOMB')) = yes;
*AGKNDISC('FI_large',GDATA(G,'GDCOMB')) = yes;
*AGKNDISC('DK2_Large',GDATA(G,'GDCOMB')) = yes;

*AGKNDISC(AAA,GDATA('GDCOMB'))$RRRAAA('dk1',AAA)=yes;
*AGKNDISC(AAA,GDATA('GDCOMB'))$RRRAAA('dk2',AAA)=yes;



* med mulighed i alle AAA taget det meget lagn tid at finde den optimale løsning:
*DK_E_4      BACKSTOP    AGKNDISCSIZE1           1.00     6000.00
*DK_W_1      BACKSTOP    AGKNDISCSIZE1           1.00     6000.00
*FI_R_Rural  BACKSTOP    AGKNDISCSIZE2           1.00    12000.00
*NO_O_Rural  BACKSTOP    AGKNDISCSIZE1           1.00     6000.00


