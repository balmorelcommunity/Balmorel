
Loop(Y,

PUT "--------------------------------------------------------------------------------"/;
PUT "Profitability of installed capacities, "Y.TL:4":"/;
PUT "The table contains all units in G."/;
PUT "--------------------------------------------------------------------------------"//;

put        file_profit        ;

LOOP(C,
PUT "--------------------------------------------------------------------------------"/;
PUT C.TL ":" /;
PUT "--------------------------------------------------------------------------------"//;


$setglobal format txt
LOOP(IA$ICA(C,IA),

PUT IA.TL ":" /;
OProfitable(OPROFITLABELS,G)=0;
OProfitable('Revenue electricity',G)$IAGK_Y(IA,G) = Rev_E(Y,IA,G)            ;
OProfitable('Revenue heat',G)$IAGK_Y(IA,G) = Rev_H(Y,IA,G)                   ;
OProfitable('Fuel costs',G)$IAGK_Y(IA,G) = -Fuel_C(Y,IA,G)                   ;
OProfitable('Variable O&M costs',G)$IAGK_Y(IA,G) = -VOM_C(Y,IA,G)            ;
OProfitable('Fixed O%M costs',G)$IAGK_Y(IA,G) = -FOM_C(Y,IA,G)               ;
OProfitable('CO2 costs',G)$IAGK_Y(IA,G) = -CO2Costs(Y,IA,G)                  ;
OProfitable('Taxes',G)$IAGK_Y(IA,G) = -Tax_C(Y,IA,G)                         ;
OProfitable('Profit (no cap. costs)',G)$IAGK_Y(IA,G) = Profitability(Y,IA,G) ;
$libinclude gams2tbl OProfitable


);
);
);


