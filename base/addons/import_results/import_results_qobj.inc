* Included into the objective function QOBJ in Balmorel.gms.


$ifi not %HYRSBB123%==price    $goto label_no_hydro_price
                                       +    SUM((IA,S,T)$(IS3(S) AND SUM(IGHYRS,IAGK_HASORPOT(Y,IA,IGHYRS))),
                                             IHOURSINST(S,T)*WATERVAL(Y,IA,S)*SUM(IGHYRS$IAGK_HASORPOT(Y,IA,IGHYRS),VGE_T(Y,IA,IGHYRS,S,T)+VHYRS_CURT(Y,IA,IGHYRS,S,T))
                                             )
$label label_no_hydro_price


$ifi not %ADDESTOVOLTS%==price    $goto label_no_interseasonal_electricity_storage_price
                                   +SUM((S,T,IA,IGESTOS)$(IS3(S) AND IAGK_HASORPOT(Y,IA,IGESTOS)),
                                                 IHOURSINST(S,T)*ESTOVOLTSVAL(Y,IA,IGESTOS,S,T)*(VGE_T(Y,IA,IGESTOS,S,T)/GDATA(IGESTOS,'GDFE')-VESTOLOADTS(Y,IA,IGESTOS,S,T))
                                   )


$label label_no_interseasonal_electricity_storage_price

$ifi not %ADDHSTOVOLTS%==price    $goto label_no_interseasonal_heat_storage_price
                                   +SUM((S,T,IA,IGHSTOS)$(IS3(S) AND IAGK_HASORPOT(Y,IA,IGHSTOS)),
                                                 IHOURSINST(S,T)*HSTOVOLTSVAL(Y,IA,IGHSTOS,S,T)*(VGH_T(Y,IA,IGHSTOS,S,T)/GDATA(IGHSTOS,'GDFE')-VHSTOLOADTS(Y,IA,IGHSTOS,S,T))
                                   )
$label label_no_interseasonal_heat_storage_price

$ifi not %ADDESTOVOLT%==price    $goto label_no_intraseasonal_electricity_storage_price
                                       +  SUM((S,T,IA,IGESTO)$(IS3(S) AND IAGK_HASORPOT(Y,IA,IGESTO)),
                                                 IHOURSINST(S,T)*ESTOVOLTVAL(Y,IA,IGESTO,S,T)*(VGE_T(Y,IA,IGESTO,S,T)/GDATA(IGESTO,'GDFE')-VESTOLOADT(Y,IA,IGESTO,S,T))
                                         )
$label label_no_intraseasonal_electricity_storage_price

$ifi not %ADDHSTOVOLT%==price    $goto label_no_intraseasonal_heat_storage_price
                                       +  SUM((S,T,IA,IGHSTO)$(IS3(S) AND IAGK_HASORPOT(Y,IA,IGHSTO)),
                                                 IHOURSINST(S,T)*HSTOVOLTVAL(Y,IA,IGHSTO,S,T)*(VGH_T(Y,IA,IGHSTO,S,T)/GDATA(IGHSTO,'GDFE')-VHSTOLOADT(Y,IA,IGHSTO,S,T))
                                         )
$label label_no_intraseasonal_heat_storage_price



