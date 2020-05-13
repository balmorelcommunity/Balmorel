

* Gridtariff on natgas and biong consumption in industry and district heating for heat production. Data is suggested by Marie, mostly from Energinet as a source
    + SUM((C,IS3,T), SUM(IAGK_HASORPOT(Y,IA,G)$(GDATA(G,'GDFUEL') EQ FDATA('ELECTRIC','FDACRONYM')),
         IHOURSINST(IS3,T) * 15.95 * GDATA(G,'GDCV') * VGH_T(Y,IA,G,IS3,T)/ (GDATA(G,'GDFE') * (1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G)))))

    + SUM((C,IS3,T), SUM(IAGK_HASORPOT(Y,IA,G)$(GDATA(G,'GDFUEL') EQ FDATA('NATGAS','FDACRONYM')),
         IHOURSINST(IS3,T) * 2.61 * GDATA(G,'GDCV') * VGH_T(Y,IA,G,IS3,T)/ (GDATA(G,'GDFE') * (1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G)))))

    + SUM((C,IS3,T), SUM(IAGK_HASORPOT(Y,IA,G)$(GDATA(G,'GDFUEL') EQ FDATA('BIONG','FDACRONYM')),
         IHOURSINST(IS3,T) * 2.61 * GDATA(G,'GDCV') * VGH_T(Y,IA,G,IS3,T)/ (GDATA(G,'GDFE') * (1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G)))))



$ifi not %indheAT%==yes  $goto label_GridTariffs_qobj_indheAT_END
* Gas grid tariff
   + SUM(C, 8.01*
         SUM(

                 (INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP,FFF)$(ICA(C,INDHEAT_IA) AND INDHEAT_GDATA(INDHEAT_G,'GDFUEL') EQ FDATA('BIONG','FDACRONYM') AND ( INDHEAT_GINGROUP(INDHEAT_G,INDHEAT_GROUP))
                 ),

                 SUM((IS3,T),
                         IHOURSINST(IS3,T)  * INDHEAT_VGF_T(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP,IS3,T))
             )
         )

   + SUM(C, 8.01*
         SUM(

                 (INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP,FFF)$(ICA(C,INDHEAT_IA) AND INDHEAT_GDATA(INDHEAT_G,'GDFUEL') EQ FDATA('NATGAS','FDACRONYM') AND ( INDHEAT_GINGROUP(INDHEAT_G,INDHEAT_GROUP))
                 ),

                 SUM((IS3,T),
                         IHOURSINST(IS3,T)  * INDHEAT_VGF_T(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP,IS3,T))
             )
         )


   + SUM(C, 40.61 *
         SUM(

                 (INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP,FFF)$(ICA(C,INDHEAT_IA) AND INDHEAT_GDATA(INDHEAT_G,'GDFUEL') EQ FDATA('ELECTRIC','FDACRONYM') AND ( INDHEAT_GINGROUP(INDHEAT_G,INDHEAT_GROUP))
                 ),

                 SUM((IS3,T),
                         IHOURSINST(IS3,T)  * INDHEAT_VGF_T(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP,IS3,T))
             )
         )



$LABEL label_GridTariffs_qobj_indheAT_END



