* File HYRSBB123addobj.inc for the Balmorel model.
* For use with addon HYRSBB123.
* Included into the objective function QOBJ in Balmorel.gms.

$ifi %HYRSBB123%==none    $goto label_no_hydro_results_import

$ifi %HYRSBB123%==price       + SUM((IA,IGHYRS)$IAGK_HASORPOT(Y,IA,IGHYRS), SUM((IS3,T), WATERVAL(Y,IA,IS3)* IHOURSINST(IS3,T) * VGE_T(Y,IA,IGHYRS,IS3,T)))



$ontext
$ifi %HYRSBB123%==price       + SUM(IAGK_HASORPOT(IY411,IA,IGHYRS),SUM((IS3,T), IWATERVAL_Y(Y,IA,IS3)* IHOURSINST(IS3,T) * VGE_T(Y,IA,IGHYRS,IS3,T)))

$ifi %HYRSBB123%==quantprice  + SUM(IAGK_HASORPOT(IY411,IA,IGHYRS),SUM((IS3,T), IWATERVAL_Y(IA,IS3)* IHOURSINST(IS3,T) * VGE_T(Y,IA,IGHYRS,IS3,T)))   !!  no investments in  BB3
$ifi %HYRSBB123%==quantprice  + SUM((IA,IS3)$IHYRSBB123G_Y(IA,IS3), (SUM(T,IHOURSINST(IS3,T)))* SUM(IHYRSBB12DELTASET, VIHYRSBB12DELTAMHW(IA,IHYRSBB12DELTASET) *IHYRSBB123EXTRAVAL(IA,IS3,IHYRSBB12DELTASET)))
$offtext

$label label_no_hydro_results_import