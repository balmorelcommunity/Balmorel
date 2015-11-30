* RUN only in BB1 or BB2
$ifi %BB3%==yes $goto not_bb1orbb2

* Save start level in hydrogen storage in each season
*loop((IA,IGH2STO)$(IAGK_Y(IA,IGH2STO) OR IAGKN(IA,IGH2STO)),H2STOVOL_START(Y,IA,IGH2STO,S) = VH2STOVOL_S.l(IA,IGH2STO,S));

$label not_bb1orbb2


