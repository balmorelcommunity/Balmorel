* File heattrans_k_hasorpot.inc for the Balmorel model. For use with addon heattrans.
* Latest revision 20181010(hr)


IAGKFX(Y,IA,IGETOH)$XHGETOH(IGETOH) = YES$GKFX(Y,IA,IGETOH);
IAGK_HASORPOT(Y,IA,IGETOH)$XHGETOH(IGETOH) = YES$GKFX(Y,IA,IGETOH);



$ifi not %GenInvest%==yes $goto Generation_investments_end

    TODO: Not implementd for investmenst yet

$label Generation_investments_end