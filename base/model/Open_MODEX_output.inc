File objective /objective_balmorel.csv/;
objective.pc=5;
put objective;
put "Objective value" ,"EURO", vobj.l;
putclose;

File memory /memory_balmorel.csv/;
memory.pc=5;
put memory;
put "Memory usage","Mb", system.memory, "%system.memory%";
putclose;

File timebuild /timebuild_balmorel.csv/;
timebuild.pc=5;
put timebuild;
put "Time required to built the model","Seconds", BALBASE4.resGen;
putclose;

File constraints /constraints_balmorel.csv/;
constraints.pc=5;
put constraints;
put "Number of constraints","#", BALBASE4.numEqu;
putclose;

File variables2 /variables_balmorel.csv/;
variables2.pc=5;
put variables2;
put "Number of variables","#", BALBASE4.numVar;
putclose;

File production /production_balmorel.csv/;
production.pc=5;
scalar timeslice;
put production;
put "Production per timestep [MWh]","";
loop((IR,G),
         put IR.tl;
);
put /;
put "Year", "Time";
loop((IA,G),
         put G.tl;
);
put /;
loop(Y,
         loop((S,T),
                 timeslice = (ord(S)-1)*24+ord(T);
                 put Y.tl,timeslice;
                 loop((IA,G),
                         put VGE_T.l(Y,IA,G,S,T);
                 );
                 put /;
         );
);
putclose;
