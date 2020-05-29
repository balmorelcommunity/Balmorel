* Gridtariff on fuel consumption in industry and district heating for heat production.
    + SUM((C,IS3,T), SUM((IAGK_HASORPOT(Y,IA,G),FFF)$(IGF(G,FFF) AND SOCIOTARIFF_ALL(Y,C,FFF)>0),
         IHOURSINST(IS3,T) * SOCIOTARIFF_ALL(Y,C,FFF) * GDATA(G,'GDCV') * VGH_T(Y,IA,G,IS3,T)/ (GDATA(G,'GDFE') * (1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G)))))

$ifi not %indheAT%==yes  $goto label_GridTariffs_qobj_indheAT_END
* Gridtariff on fuel consumption in houses outside DH for heat production.
   + SUM((C,IS3,T),SUM((INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP,FFF)$(ICA(C,INDHEAT_IA) AND SOCIOTARIFF_INDHEAT(Y,C,FFF) AND INDHEAT_GINGROUP(INDHEAT_G,INDHEAT_GROUP)),
                  IHOURSINST(IS3,T)  * SOCIOTARIFF_INDHEAT(Y,C,FFF) * INDHEAT_VGF_T(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP,IS3,T)))
$LABEL label_GridTariffs_qobj_indheAT_END



