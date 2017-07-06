* File uc_intern.inc.
* Unit commitment add-on to Balmorel.
* Implemented by Hans Ravn 2006-2007.
* Revised and enhanced by Lars Bregnsbæk 2011.
* See the documentation for details and inspiration.

* Internal sets

SET IGUCE(G) "Unit commitment: the set of IGKE units participating in unit commitment" ;
IGUCE(IGKE)$GDATA(IGKE,'GDUC')=yes;

SET IGUCH(G) "Unit commitment: the set of IGKHNOSTO units participating in unit commitment";
IGUCH(IGKHNOSTO)$GDATA(IGKHNOSTO,'GDUC')=yes;

SET IGUC(G) "Unit commitment: the set of units participating in unit commitment";
IGUC(IGUCE)=YES;
IGUC(IGUCH)=YES;

$ifi %UnitCramp%==yes UCGSHUTD(IGUC,IUCT)$(ord(IUCT) LE GDATA(IGUC,'GDUCDURD') and GDATA(IGUC,'GDUCDURD'))   = SUM((IA),GKFX('2015',IA,IGUC)*(GDATA(IGUC,'GDUCDURD')-ord(IUCT))/GDATA(IGUC,'GDUCDURD')*GDATA(IGUC,'GDUCGMIN'));
$ifi %UnitCramp%==yes UCGSTARTU(IGUC,IUCT)$(ord(IUCT) LE GDATA(IGUC,'GDUCDURU') and GDATA(IGUC,'GDUCDURU'))  = SUM((IA),GKFX('2015',IA,IGUC)*(ord(IUCT))/GDATA(IGUC,'GDUCDURU')*GDATA(IGUC,'GDUCGMIN'));



