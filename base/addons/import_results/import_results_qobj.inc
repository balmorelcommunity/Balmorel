* Included into the objective function QOBJ in Balmorel.gms.


$ifi not %HYRSBB123%==price    $goto label_no_hydro_price
                                       +    SUM((IA,IS3,T)$(SUM(IGHYRS,IAGK_HASORPOT(Y,IA,IGHYRS))),
                                             IHOURFRAC*IHOURSINST(IS3,T)*WATERVAL(Y,IA,IS3)*SUM(IGHYRS$IAGK_HASORPOT(Y,IA,IGHYRS),VGE_T(Y,IA,IGHYRS,IS3,T)+VHYRS_CURT(Y,IA,IGHYRS,IS3,T))
                                             )
$label label_no_hydro_price


$ifi not %ADDESTOVOLTS%==price    $goto label_no_interseasonal_electricity_storage_price
                                   +SUM((IS3,T,IA,IGESTOS)$(IAGK_HASORPOT(Y,IA,IGESTOS)),
                                                 IHOURFRAC*IHOURSINST(IS3,T)*ESTOVOLTSVAL(Y,IA,IGESTOS,IS3,T)*(VGE_T(Y,IA,IGESTOS,IS3,T)/GDATA(IGESTOS,'GDFE')-VESTOLOADTS(Y,IA,IGESTOS,IS3,T))
                                   )
$label label_no_interseasonal_electricity_storage_price

$ifi not %ADDHSTOVOLTS%==price    $goto label_no_interseasonal_heat_storage_price
                                   +SUM((IS3,T,IA,IGHSTOS)$(IAGK_HASORPOT(Y,IA,IGHSTOS)),
                                                 IHOURFRAC*IHOURSINST(IS3,T)*HSTOVOLTSVAL(Y,IA,IGHSTOS,IS3,T)*(VGH_T(Y,IA,IGHSTOS,IS3,T)/GDATA(IGHSTOS,'GDFE')-VHSTOLOADTS(Y,IA,IGHSTOS,IS3,T))
                                   )
$label label_no_interseasonal_heat_storage_price

$ifi not %ADDESTOVOLT%==price    $goto label_no_intraseasonal_electricity_storage_price
                                       +  SUM((IS3,T,IA,IGESTO)$(IAGK_HASORPOT(Y,IA,IGESTO)),
                                                 IHOURFRAC*IHOURSINST(IS3,T)*ESTOVOLTVAL(Y,IA,IGESTO,IS3,T)*(VGE_T(Y,IA,IGESTO,IS3,T)/GDATA(IGESTO,'GDFE')-VESTOLOADT(Y,IA,IGESTO,IS3,T))
                                         )
$label label_no_intraseasonal_electricity_storage_price

$ifi not %ADDHSTOVOLT%==price    $goto label_no_intraseasonal_heat_storage_price
                                       +  SUM((IS3,T,IA,IGHSTO)$(IAGK_HASORPOT(Y,IA,IGHSTO)),
                                                 IHOURFRAC*IHOURSINST(IS3,T)*HSTOVOLTVAL(Y,IA,IGHSTO,IS3,T)*(VGH_T(Y,IA,IGHSTO,IS3,T)/GDATA(IGHSTO,'GDFE')-VHSTOLOADT(Y,IA,IGHSTO,IS3,T))
                                         )
$label label_no_intraseasonal_heat_storage_price


$ifi not %HYDROGEN%==yes  $goto label_no_hydrogen
$ifi not %ADDH2STOVOLTS%==price    $goto label_no_interseasonal_hydrogen_storage_price
                                   +SUM((IS3,T,IA,IHYDROGEN_GH2STO)$(IAGK_HASORPOT(Y,IA,IHYDROGEN_GH2STO)),
                                                 IHOURFRAC*IHOURSINST(IS3,T)*H2STOVOLTSVAL(Y,IA,IHYDROGEN_GH2STO,IS3,T)*(VHYDROGEN_GH2_T(Y,IA,IHYDROGEN_GH2STO,IS3,T)/GDATA(IHYDROGEN_GH2STO,'GDFE')-VHYDROGEN_STOLOADT(Y,IA,IHYDROGEN_GH2STO,IS3,T))
                                   )
$label label_no_interseasonal_hydrogen_storage_price
$ifi not %ADDBIOMETHSTOVOLTS%==price    $goto label_no_interseasonal_biomethane_storage_price
                                   +SUM((IS3,T)$(SUM((IA,IGBIOMETHANE),IAGK_HASORPOT(Y,IA,IGBIOMETHANE)) AND SUM((IA,IHYDROGEN_GH2TOBIOMETH),IAGK_HASORPOT(Y,IA,IHYDROGEN_GH2TOBIOMETH))),
                                                 IHOURFRAC*IHOURSINST(IS3,T)*BIOMETHSTOVOLTSVAL(Y,IS3,T)*(VBIOMETH_STOUNLOADT(Y,IS3,T)-VBIOMETH_STOLOADT(Y,IS3,T))
                                   )
$label label_no_interseasonal_biomethane_storage_price
$label label_no_hydrogen



