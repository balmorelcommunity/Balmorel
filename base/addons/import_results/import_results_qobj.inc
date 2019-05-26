* File HYRSBB123addobj.inc for the Balmorel model.
* For use with addon HYRSBB123.
* Included into the objective function QOBJ in Balmorel.gms.

$ifi %HYRSBB123%==none    $goto label_no_hydro_results_import

$ifi not %HYRSBB123%==contprice    $goto label_no_hydro_contprice
                                         +    SUM((IA,S,T)$(IS3(S) AND SUM(IGHYRS,IAGK_HASORPOT(Y,IA,IGHYRS))),
                                                 IHOURSINST(S,T)*WATERVAL(Y,IA,S)*SUM(IGHYRS$IAGK_HASORPOT(Y,IA,IGHYRS),VGE_T(Y,IA,IGHYRS,S,T))
                                               )
                                         +    SUM((IA,S,T)$(IS3(S) AND NOT(IS3(S++1)) AND ORD(T) EQ 1 AND SUM(IGHYRS,IAGK_HASORPOT(Y,IA,IGHYRS))),
                                                 IHOURSINST(S,T)*SUM(ISALIAS$(NOT IS3(ISALIAS)),WATERVAL(Y,IA,ISALIAS)*HYRSG(Y,IA,ISALIAS))/SUM(ISALIAS$(NOT IS3(ISALIAS)),HYRSG(Y,IA,ISALIAS))*VHYRS_SDELTAMWHNEG(Y,IA,S++1)
                                        )
$label label_no_hydro_contprice


$label label_no_hydro_results_import

$ifi not %ADDELECSTORCONT%==contprice    $goto label_no_intraseasonal_electricity_storage_content
                                   + SUM((IA,IGESTOS)$IAGK_HASORPOT(Y,IA,IGESTOS),
                                         SUM((S,T)$(IS3(S)),
                                                 IHOURSINST(S,T)*GVESTOVOLTSVAL(Y,IA,IGESTOS,S,T)*VGE_T(Y,IA,IGESTOS,S,T)
                                         )
                                   )
*                                   + SUM((IA,IGESTOS)$IAGK_HASORPOT(Y,IA,IGESTOS),
*                                         SUM((S,T)$(IS3(S) AND ORD(T) EQ 1 AND GVESTOVOLTSVAL(Y,IA,IGESTOS,S++1,T) AND GVESTOVOLTSVAL(Y,IA,IGESTOS,S++1,T) NE EPS),
*                                                 IHOURSINST(S,T)*GVESTOVOLTSVAL(Y,IA,IGESTOS,S++1,T)*(VESTOVOLTSDELTAMWHPOS(Y,IA,IGESTOS,S++1,T)+VESTOVOLTSDELTAMWHNEG(Y,IA,IGESTOS,S++1,T))
*                                         )
*                                   )
$label label_no_intraseasonal_electricity_storage_content

$ifi not %ADDHEATSTORCONT%==contprice    $goto label_no_intraseasonal_heat_storage_content
                                   + SUM((IA,IGHSTOS)$IAGK_HASORPOT(Y,IA,IGHSTOS),
                                         SUM((S,T)$(IS3(S)),
                                                 IHOURSINST(S,T)*GVHSTOVOLTSVAL(Y,IA,IGHSTOS,S,T)*VGH_T(Y,IA,IGHSTOS,S,T)
                                         )
                                   )
*                                   + SUM((IA,IGHSTOS)$IAGK_HASORPOT(Y,IA,IGHSTOS),
*                                         SUM((S,T)$(IS3(S) AND ORD(T) EQ 1 AND GVHSTOVOLTSVAL(Y,IA,IGHSTOS,S++1,T) AND GVHSTOVOLTSVAL(Y,IA,IGHSTOS,S++1,T) NE EPS),
*                                                 IHOURSINST(S,T)*GVHSTOVOLTSVAL(Y,IA,IGHSTOS,S++1,T)*(VHSTOVOLTSDELTAMWHPOS(Y,IA,IGHSTOS,S++1,T)+VHSTOVOLTSDELTAMWHNEG(Y,IA,IGHSTOS,S++1,T))
*                                         )
*                                   )

$label label_no_intraseasonal_heat_storage_content


