* Included into the objective function QOBJ in Balmorel.gms.


$ifi not %HYRSBB123%==price    $goto label_no_hydro_price
                                       +    SUM((IA,S,T)$(IS3(S) AND SUM(IGHYRS,IAGK_HASORPOT(Y,IA,IGHYRS))),
                                             IHOURFRAC*IHOURSINST(S,T)*WATERVAL(Y,IA,S)*SUM(IGHYRS$IAGK_HASORPOT(Y,IA,IGHYRS),VGE_T(Y,IA,IGHYRS,S,T)+VHYRS_CURT(Y,IA,IGHYRS,S,T))
                                             )
$label label_no_hydro_price


$ifi not %ADDESTOVOLTS%==price    $goto label_no_interseasonal_electricity_storage_price
                                   +SUM((S,T,IA,IGESTOS)$(IS3(S) AND IAGK_HASORPOT(Y,IA,IGESTOS)),
                                                 IHOURFRAC*IHOURSINST(S,T)*ESTOVOLTSVAL(Y,IA,IGESTOS,S,T)*(VGE_T(Y,IA,IGESTOS,S,T)/GDATA(IGESTOS,'GDFE')-VESTOLOADTS(Y,IA,IGESTOS,S,T))
                                   )
$label label_no_interseasonal_electricity_storage_price

$ifi not %ADDHSTOVOLTS%==price    $goto label_no_interseasonal_heat_storage_price
                                   +SUM((S,T,IA,IGHSTOS)$(IS3(S) AND IAGK_HASORPOT(Y,IA,IGHSTOS)),
                                                 IHOURFRAC*IHOURSINST(S,T)*HSTOVOLTSVAL(Y,IA,IGHSTOS,S,T)*(VGH_T(Y,IA,IGHSTOS,S,T)/GDATA(IGHSTOS,'GDFE')-VHSTOLOADTS(Y,IA,IGHSTOS,S,T))
                                   )
$label label_no_interseasonal_heat_storage_price

$ifi not %ADDESTOVOLT%==price    $goto label_no_intraseasonal_electricity_storage_price
                                       +  SUM((S,T,IA,IGESTO)$(IS3(S) AND IAGK_HASORPOT(Y,IA,IGESTO)),
                                                 IHOURFRAC*IHOURSINST(S,T)*ESTOVOLTVAL(Y,IA,IGESTO,S,T)*(VGE_T(Y,IA,IGESTO,S,T)/GDATA(IGESTO,'GDFE')-VESTOLOADT(Y,IA,IGESTO,S,T))
                                         )
$label label_no_intraseasonal_electricity_storage_price

$ifi not %ADDHSTOVOLT%==price    $goto label_no_intraseasonal_heat_storage_price
                                       +  SUM((S,T,IA,IGHSTO)$(IS3(S) AND IAGK_HASORPOT(Y,IA,IGHSTO)),
                                                 IHOURFRAC*IHOURSINST(S,T)*HSTOVOLTVAL(Y,IA,IGHSTO,S,T)*(VGH_T(Y,IA,IGHSTO,S,T)/GDATA(IGHSTO,'GDFE')-VHSTOLOADT(Y,IA,IGHSTO,S,T))
                                         )
$label label_no_intraseasonal_heat_storage_price


$ifi not %HYDROGEN%==yes  $goto label_no_hydrogen
$ifi not %ADDH2STOVOLTS%==price    $goto label_no_interseasonal_hydrogen_storage_price
                                   +SUM((S,T,IA,IHYDROGEN_GH2STO)$(IS3(S) AND IAGK_HASORPOT(Y,IA,IHYDROGEN_GH2STO)),
                                                 IHOURFRAC*IHOURSINST(S,T)*H2STOVOLTSVAL(Y,IA,IHYDROGEN_GH2STO,S,T)*(VHYDROGEN_GH2_T(Y,IA,IHYDROGEN_GH2STO,S,T)/GDATA(IHYDROGEN_GH2STO,'GDFE')-VHYDROGEN_STOLOADT(Y,IA,IHYDROGEN_GH2STO,S,T))
                                   )
$label label_no_interseasonal_hydrogen_storage_price
$ifi not %ADDBIOMETHSTOVOLTS%==price    $goto label_no_interseasonal_biomethane_storage_price
                                   +SUM((S,T)$(IS3(S) AND SUM((IA,IGBIOMETHANE),IAGK_HASORPOT(Y,IA,IGBIOMETHANE)) AND SUM((IA,IHYDROGEN_GH2TOBIOMETH),IAGK_HASORPOT(Y,IA,IHYDROGEN_GH2TOBIOMETH))),
                                                 IHOURFRAC*IHOURSINST(S,T)*BIOMETHSTOVOLTSVAL(Y,S,T)*(VBIOMETH_STOUNLOADT(Y,S,T)-VBIOMETH_STOLOADT(Y,S,T))
                                   )
$label label_no_interseasonal_biomethane_storage_price
$label label_no_hydrogen
