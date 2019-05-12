* File HYRSBB123addobj.inc for the Balmorel model.
* For use with addon HYRSBB123.
* Included into the objective function QOBJ in Balmorel.gms.

$ifi %HYRSBB123%==none    $goto label_no_hydro_results_import

$ifi not %HYRSBB123%==contprice    $goto label_no_hydro_contprice
                                    + SUM(IAGK_HASORPOT(IY411,IA,IGHYRS),
                                         SUM((S)$((IS3(S) OR IS3(S--1)) AND WATERVAL(Y,IA,S)),
                                                 WATERVAL(Y,IA,S)*(VHYRS_SDELTAMWHPOS(Y,IA,S) + VHYRS_SDELTAMWHNEG(Y,IA,S))
                                         )
                                    )
$label label_no_hydro_contprice


$label label_no_hydro_results_import

$ifi not %ADDELECSTORCONT%==yes    $goto label_no_intraseasonal_electricity_storage_content
                                   + SUM((IA,IGESTOS)$IAGK_HASORPOT(Y,IA,IGESTOS),
                                         SUM((S,T)$((IS3(S) OR IS3(S--1)) AND ORD(T) EQ 1 AND GVESTOVOLTSVAL(Y,IA,IGESTOS,S,T)),
                                                 GVESTOVOLTSVAL(Y,IA,IGESTOS,S,T)*(VESTOVOLTSDELTAMWHPOS(Y,IA,IGESTOS,S,T)+VESTOVOLTSDELTAMWHNEG(Y,IA,IGESTOS,S,T))
                                         )
                                   )
$label label_no_intraseasonal_electricity_storage_content

$ifi not %ADDHEATSTORCONT%==yes    $goto label_no_intraseasonal_heat_storage_content
                                   + SUM((IA,IGHSTOS)$IAGK_HASORPOT(Y,IA,IGHSTOS),
                                         SUM((S,T)$((IS3(S) OR IS3(S--1)) AND ORD(T) EQ 1 AND GVHSTOVOLTSVAL(Y,IA,IGHSTOS,S,T)),
                                                 GVHSTOVOLTSVAL(Y,IA,IGHSTOS,S,T)*(VHSTOVOLTSDELTAMWHPOS(Y,IA,IGHSTOS,S,T)+VHSTOVOLTSDELTAMWHNEG(Y,IA,IGHSTOS,S,T))
                                         )
                                   )

$label label_no_intraseasonal_heat_storage_content
