* RUN only in BB1 or BB2
$ifi %BB3%==yes $goto not_bb1orbb2

* Save start level in hydrogen storage in each season
*loop((IA,IHYDROGEN_GH2STO)$(IAGK_Y(IA,IHYDROGEN_GH2STO) OR IAGKN(IA,IHYDROGEN_GH2STO)),HYDROGEN_STOVOL_START(Y,IA,IHYDROGEN_GH2STO,S) = VHYDROGEN_STOVOL_S.l(IA,IHYDROGEN_GH2STO,S));

$label not_bb1orbb2


