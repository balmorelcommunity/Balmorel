* Gridtariff on fuel consumption in industry and district heating for heat production.
    + SUM((C,IA,G,FFF,IS3,T)$((IAGK_HASORPOT(Y,IA,G) AND ICA(C,IA) AND GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM') AND SOCIOTARIFF_ALL(Y,C,FFF)>0)),
         IHOURSINST(IS3,T) * SOCIOTARIFF_ALL(Y,C,FFF) * GDATA(G,'GDCV') * VGH_T(Y,IA,G,IS3,T)/ (GDATA(G,'GDFE') * (1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G))))

$ifi not %INDHEAT%==yes  $goto label_GridTariffs_qobj_indheAT_END
* Gridtariff on fuel consumption in houses outside DH for heat production.
   + SUM((C,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP,FFF,IS3,T)$(ICA(C,INDHEAT_IA) AND INDHEAT_GDATA(INDHEAT_G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM') AND SOCIOTARIFF_INDHEAT(Y,C,FFF)>0 AND INDHEAT_GINGROUP(INDHEAT_G,INDHEAT_GROUP)),
                  IHOURSINST(IS3,T)  * SOCIOTARIFF_INDHEAT(Y,C,FFF) * INDHEAT_VGF_T(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP,IS3,T)
         )
$LABEL label_GridTariffs_qobj_indheAT_END



