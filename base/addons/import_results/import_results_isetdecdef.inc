SET IVHYRS_SL(YYY,AAA)  "Internal contains Hourly hydro storage level";
SET IESTOVOLTS(YYY,AAA,GGG) "Internal contains Inter-seasonal Electricity storage contents";
SET IHSTOVOLTS(YYY,AAA,GGG) "Internal contains Inter-seasonal Heat storage contents";
SET IESTOVOLT(YYY,AAA,GGG) "Internal contains Intra-seasonal Electricity storage contents";
SET IHSTOVOLT(YYY,AAA,GGG) "Internal contains Intra-seasonal Heat storage content";
$ifi %HYDROGEN%==yes SET IH2STOVOLTS(YYY,AAA,GGG) "Internal contains Inter-seasonal hydrogen storage contents";

$ifi %HYRSBB123%==none    IVHYRS_SL(Y,IA)=0;
$ifi %ADDESTOVOLTS%==none IESTOVOLTS(Y,IA,IGESTOS)=0;
$ifi %ADDHSTOVOLTS%==none IHSTOVOLTS(Y,IA,IGHSTOS)=0;
$ifi %ADDESTOVOLT%==none  IESTOVOLT(Y,IA,IGESTO)=0;
$ifi %ADDHSTOVOLT%==none  IHSTOVOLT(Y,IA,IGHSTO)=0;
$ifi %HYDROGEN%==yes $ifi %ADDH2STOVOLTS%==none  IH2STOVOLTS(Y,IA,IHYDROGEN_GH2STO)=0;

$ifi not %HYRSBB123%==none    IVHYRS_SL(Y,IA)$SUM(S,VHYRS_SL(Y,IA,S))=YES;
$ifi not %ADDESTOVOLTS%==none IESTOVOLTS(Y,IA,IGESTOS)$SUM((S,T),ESTOVOLTS(Y,IA,IGESTOS,S,T))=YES;
$ifi not %ADDHSTOVOLTS%==none IHSTOVOLTS(Y,IA,IGHSTOS)$SUM((S,T),HSTOVOLTS(Y,IA,IGHSTOS,S,T))=YES;
$ifi not %ADDESTOVOLT%==none  IESTOVOLT(Y,IA,IGESTO)$SUM((S,T),ESTOVOLT(Y,IA,IGESTO,S,T))=YES;
$ifi not %ADDHSTOVOLT%==none  IHSTOVOLT(Y,IA,IGHSTO)$SUM((S,T),HSTOVOLT(Y,IA,IGHSTO,S,T))=YES;
$ifi %HYDROGEN%==yes $ifi not %ADDH2STOVOLTS%==none IH2STOVOLTS(Y,IA,IHYDROGEN_GH2STO)$SUM((S,T),H2STOVOLTS(Y,IA,IHYDROGEN_GH2STO,S,T))=YES;


