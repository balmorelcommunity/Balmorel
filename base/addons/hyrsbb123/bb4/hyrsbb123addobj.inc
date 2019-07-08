* File HYRSBB123addobj.inc for the Balmorel model.
* For use with addon HYRSBB123.
* Included into the objective function QOBJ in Balmorel.gms.

$ifi not %BB3%==yes $goto  label_HYRSBB123addobj

$ifi %BB3%==yes  $ifi %HYRSBB123%==price       + SUM(IAGK_Y(IA,IGHYRS),SUM((IS3,T), IWATERVAL_Y(IA,IS3)* IHOURSINST(IS3,T) * VGE_T(IA,IGHYRS,IS3,T)))   !!  no investments in  BB3

$ifi %BB3%==yes  $ifi %HYRSBB123%==quantprice  + SUM(IAGK_Y(IA,IGHYRS),SUM((IS3,T), IWATERVAL_Y(IA,IS3)* IHOURSINST(IS3,T) * VGE_T(IA,IGHYRS,IS3,T)))   !!  no investments in  BB3
$ifi %BB3%==yes  $ifi %HYRSBB123%==quantprice  + SUM((IA,IS3)$IHYRSBB123G_Y(IA,IS3), (SUM(T,IHOURSINST(IS3,T)))* SUM(IHYRSBB12DELTASET, VIHYRSBB12DELTAMHW(IA,IHYRSBB12DELTASET) *IHYRSBB123EXTRAVAL(IA,IS3,IHYRSBB12DELTASET)))

$label label_HYRSBB123addobj;
$ifi not %BB3%==yes  !! print some error message - todo.
