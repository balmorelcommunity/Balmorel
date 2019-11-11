* Included into the objective function QOBJ in Balmorel.gms.


$ifi not %HYRSBB123%==price    $goto label_no_hydro_price
                                       +    SUM((IA,S)$(IS3(S) AND SUM(IGHYRS,IAGK_HASORPOT(Y,IA,IGHYRS)) AND IVHYRS_SL(Y,IA)),
                                             WATERVAL(Y,IA,S)*(VHYRS_S(Y,IA,S)-VHYRS_S(Y,IA,S++1))/SSIZE(S)
                                             )
$label label_no_hydro_price


$ifi not %ADDESTOVOLTS%==price    $goto label_no_interseasonal_electricity_storage_price
                                   +SUM((S,T,IA,IGESTOS)$(IS3(S) AND IAGK_HASORPOT(Y,IA,IGESTOS) AND IESTOVOLTS(Y,IA,IGESTOS)),
                                                 IHOURSINST(S,T)*ESTOVOLTSVAL(Y,IA,IGESTOS,S,T)*(VESTOVOLTS(Y,IA,IGESTOS,S,T)-
                                                (VESTOVOLTS(Y,IA,IGESTOS,S,T+1) + SUM(ITALIAS$(ORD(ITALIAS) EQ 1),VESTOVOLTS(Y,IA,IGESTOS,S++1,ITALIAS)$(ORD(T) EQ CARD(T))))
                                                 )/SSIZE(S)
                                   )


$label label_no_interseasonal_electricity_storage_price

$ifi not %ADDHSTOVOLTS%==price    $goto label_no_interseasonal_heat_storage_price
                                   +SUM((S,T,IA,IGHSTOS)$(IS3(S) AND IAGK_HASORPOT(Y,IA,IGHSTOS) AND IHSTOVOLTS(Y,IA,IGHSTOS)),
                                                 IHOURSINST(S,T)*HSTOVOLTSVAL(Y,IA,IGHSTOS,S,T)*(VHSTOVOLTS(Y,IA,IGHSTOS,S,T)-
                                                (VHSTOVOLTS(Y,IA,IGHSTOS,S,T+1) + SUM(ITALIAS$(ORD(ITALIAS) EQ 1),VHSTOVOLTS(Y,IA,IGHSTOS,S++1,ITALIAS)$(ORD(T) EQ CARD(T))))
                                                 )/SSIZE(S)
                                   )
$label label_no_interseasonal_heat_storage_price

$ifi not %ADDESTOVOLT%==price    $goto label_no_intraseasonal_electricity_storage_price
                                       +  SUM((S,T,IA,IGESTO)$(IS3(S) AND IAGK_HASORPOT(Y,IA,IGESTO) AND IESTOVOLT(Y,IA,IGESTO)),
                                                 IHOURSINST(S,T)*ESTOVOLTVAL(Y,IA,IGESTO,S,T)*(VGE_T(Y,IA,IGESTO,S,T)-VESTOLOADT(Y,IA,IGESTO,S,T))
                                         )
$label label_no_intraseasonal_electricity_storage_price

$ifi not %ADDHSTOVOLT%==price    $goto label_no_intraseasonal_heat_storage_price
                                       +  SUM((S,T,IA,IGHSTO)$(IS3(S) AND IAGK_HASORPOT(Y,IA,IGHSTO) AND IHSTOVOLT(Y,IA,IGHSTO)),
                                                 IHOURSINST(S,T)*HSTOVOLTVAL(Y,IA,IGHSTO,S,T)*(VGH_T(Y,IA,IGHSTO,S,T)-VHSTOLOADT(Y,IA,IGHSTO,S,T))
                                         )
$label label_no_intraseasonal_heat_storage_price



