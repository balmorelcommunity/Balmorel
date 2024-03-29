*Import results Juan Gea Berm�dez 2019.

$ifi %ADDTECHDEV%==yes  GKFX(YYY,AAA,GGG)=0;
$ifi %ADDTECHDEV%==yes  GKFX(Y,IA,G)=GKACCUMNET(Y,IA,G);
$ifi %ADDTRANSDEV%==yes XKFX(YYY,IRRRE,IRRRI)=0;
$ifi %ADDTRANSDEV%==yes XKFX(Y,IRE,IRI)=XKACCUMNET(Y,IRE,IRI);
$ifi %HEATTRANS%==yes $ifi %ADDHEATTRANSDEV%==yes XHKFX(YYY,IAAAE,IAAAI)=0;
$ifi %HEATTRANS%==yes $ifi %ADDHEATTRANSDEV%==yes XHKFX(Y,IAE,IAI)=XHKACCUMNET(Y,IAE,IAI);
$ifi %ADDH2TRANSDEV%==yes XH2KFX(YYY,IRRRE,IRRRI)=0;
$ifi %ADDH2TRANSDEV%==yes XH2KFX(Y,IRE,IRI)=XH2KACCUMNET(Y,IRE,IRI);
$ifi %ADDHSTOVOLTS%==none  HSTOVOLTS(Y,IA,IGHSTOS,S,T)=0;
$ifi %ADDESTOVOLTS%==none  ESTOVOLTS(Y,IA,IGESTOS,S,T)=0;
$ifi %ADDHSTOVOLT%==none  HSTOVOLT(Y,IA,IGHSTO,S,T)=0;
$ifi %ADDESTOVOLT%==none  ESTOVOLT(Y,IA,IGESTO,S,T)=0;
$ifi %HYDROGEN%==yes $ifi %ADDH2STOVOLTS%==none H2STOVOLTS(Y,IA,IHYDROGEN_GH2STO,S,T)=0;
$ifi %HYDROGEN%==yes $ifi %ADDBIOMETHSTOVOLTS%==none BIOMETHSTOVOLTS(Y,S,T)=0;
$ifi %EV%==yes $ifi %ADDEVSTOS%==none  EV_VSOC_BEV(Y,IR,S,T)=0;
$ifi %EV%==yes $ifi %ADDEVSTOS%==none  EV_VSOC_PHEV(Y,IR,S,T)=0;
$ifi %EV%==yes $ifi %ADDEVSTOS%==none  EV_BEV_NETCHARGING(Y,IR,S,T)=0;
$ifi %EV%==yes $ifi %ADDEVSTOS%==none  EV_PHEV_NETCHARGING(Y,IR,S,T)=0;
$ifi %HYRSBB123%==none  VHYRS_SL(Y,IA,S)=0;
$ifi %ADDFUELPRICE%==yes FUELPRICE(Y,IA,FFF)=FUELPRICE_EXC(Y,IA,FFF);
$ifi not %UnitComm%==yes UCON(Y,IA,G,S,T)=0;
$ifi not %UnitComm%==yes UCON_STOLOAD(Y,IA,G,S,T)=0;

*Correction of hydro levels to respect limits (it can happen since the hydro balance equation only respects hydro limits in S)
$ifi not %HYRSBB123%==none VHYRS_SL(Y,IA,S)$(SUM(ISALIAS,VHYRS_SL(Y,IA,ISALIAS)) AND NOT(VHYRS_SL(Y,IA,S)))=EPS;
$ifi %RollingSeasons%==yes $ifi not %HYRSBB123%==none VHYRS_SL(Y,IA,S)$(VHYRS_SL(Y,IA,S) GT HYRSDATA(IA,"HYRSMAXVOL",S)*SUM(IGHYRS,HYRSMAXVOL_G(IA,IGHYRS)*GKFX(Y,IA,IGHYRS)))=HYRSDATA(IA,"HYRSMAXVOL",S)*SUM(IGHYRS,HYRSMAXVOL_G(IA,IGHYRS)*GKFX(Y,IA,IGHYRS));
$ifi %RollingSeasons%==yes $ifi not %HYRSBB123%==none VHYRS_SL(Y,IA,S)$(VHYRS_SL(Y,IA,S) LT HYRSDATA(IA,"HYRSMINVOL",S)*SUM(IGHYRS,HYRSMAXVOL_G(IA,IGHYRS)*GKFX(Y,IA,IGHYRS)))=HYRSDATA(IA,"HYRSMINVOL",S)*SUM(IGHYRS,HYRSMAXVOL_G(IA,IGHYRS)*GKFX(Y,IA,IGHYRS));

*Correction of minimum fuel use per region to reflect eps
$ifi %ADDMAXFUELUSES%==yes GMAXFS(Y,CCCRRRAAA,FFF,S)$(SUM(ISALIAS,GMAXFS(Y,CCCRRRAAA,FFF,ISALIAS)) AND NOT(GMAXFS(Y,CCCRRRAAA,FFF,S)))=EPS;

$ifi not %ADDBACKUPGEN%==yes  $goto NO_BACKUPGEN
LOOP(Y,
   LOOP(C,
      LOOP(IR$CCCRRR(C,IR),
         ILOOPBREAK=0;
         LOOP(IA$(RRRAAA(IR,IA)),
            IF ((SUM(DEUSER,DE(Y,IR,DEUSER)) AND ILOOPBREAK=0),
               ILOOPBREAK=1;
               GKFX(Y,IA,G)$(GDATA(G,'GDTECHGROUP') EQ BACKUP_ELECTRICITY)=1000000;
            );
            IF (SUM(DHUSER,DH(Y,IA,DHUSER)),
               GKFX(Y,IA,G)$(GDATA(G,'GDTECHGROUP') EQ BACKUP_HEAT)=1000000;
            );
$ifi not %HYDROGEN%==yes  $goto NO_HYDROGEN
            IF (SUM(IHYDROGEN,GKFX(Y,IA,IHYDROGEN)),
               GKFX(Y,IA,G)$(GDATA(G,'GDTECHGROUP') EQ BACKUP_HYDROGEN)=1000000;
            );
            IF (SUM(IHYDROGEN_GH2TOBIOMETH,GKFX(Y,IA,IHYDROGEN_GH2TOBIOMETH)),
               GKFX(Y,IA,G)$(GDATA(G,'GDTECHGROUP') EQ BACKUP_BIOMETHANE)=1000000;
            );
$label NO_HYDROGEN
         );
      );
   );
);

GOMVCOSTO(IA,G)$(GDATA(G,'GDTECHGROUP') EQ BACKUP_ELECTRICITY AND SUM(Y,GKFX(Y,IA,G))) = GDATA(G,'GDOMVCOST0');
GOMVCOSTO(IA,G)$(GDATA(G,'GDTECHGROUP') EQ BACKUP_HEAT AND SUM(Y,GKFX(Y,IA,G))) = GDATA(G,'GDOMVCOST0');
$ifi %HYDROGEN%==yes  GOMVCOSTO(IA,G)$(GDATA(G,'GDTECHGROUP') EQ BACKUP_HYDROGEN AND SUM(Y,GKFX(Y,IA,G))) = GDATA(G,'GDOMVCOST0');
$ifi %HYDROGEN%==yes  GOMVCOSTO(IA,G)$(GDATA(G,'GDTECHGROUP') EQ BACKUP_BIOMETHANE AND SUM(Y,GKFX(Y,IA,G))) = GDATA(G,'GDOMVCOST0');
$label NO_BACKUPGEN

PARAMETER ICOUNTSSSTTT(SSS,TTT) "Count of timesteps in SSS and TTT";
PARAMETER ICOUNTSSS(SSS)        "Count of timesteps in SSS and TTT";
SCALAR ICOUNTACC "Count of timesteps accumulated";

ICOUNTACC=1
LOOP(SSS,
   LOOP(TTT,
      ICOUNTSSSTTT(SSS,TTT)=ICOUNTACC;
      ICOUNTACC=1+ICOUNTACC;
   );
);

ICOUNTACC=1
LOOP(SSS,
      ICOUNTSSS(SSS)=ICOUNTACC;
      ICOUNTACC=1+ICOUNTACC;
);

