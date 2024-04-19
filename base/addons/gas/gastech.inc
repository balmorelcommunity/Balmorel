* ---------------------------------------- *
*       VARIABLES
* ---------------------------------------- *

FREE Variables  u(i,e,s,t)              "Massflowrate",
                uu(i,j,s,t)             "Massflowrate ss";

POSITIVE Variables
                VPs_PIPES(e,s,t)         "Pressure in pipes squared",
                VPs_NODES(i,s,t)         "Pressure at nodes squared",
                VO(e,s,t)                "Accumulated mass in pipes";


SET MNLEG(e) /
                 EGTVED_NOERSKOV
                 NOERSKOV_BRANDE
                 BRANDE_HERNING
                 HERNING_KARUP
                 KARUP_VIBORG
                 VIBORG_LITORUP
                 DUMMY1
/;
SET SLEG(e) /
                 EGTVED_STANDST
                 STANDST_POTTEHUSE
                 POTTEHUSE_LISELSKAER
                 LISELSKAER_TERKELSBOEL
                 TERKELSBOEL_ELLUND
                 DUMMY2
/;
SET FYNLEG(e) /
                 EGTVED_LILBALLE
                 LILBALLE_TAULOV
                 TAULOV_LYNGSODDE
                 LILLEBAELT_SYD
                 LILLEBAELT_NORD
                 MIDDELFART_BILLESBOELLE
                 BILLESBOELLE_KOELBJERG
                 KOELBJERG_HOEJBY
                 HOEJBY_ULLERSLEV
                 ULLERSLEV_NYBORG
                 STOREBAELTSYD
                 STORBAELTNORD
                 KONGSMARK_SLAGELSE
                 SLAGELSE_SOROE
                 SOROE_RINGSTED
                 RINGSTED_KOEGE
                 KOEGE_KARLSLUNDE
                 KARLSLUNDE_TORSLUNDE
                 TORSLUNDE_STENLILLE
                 DUMMY3
/;
SET FINGERS(E) /
                NYBRO_VARDE
                VARDE_HELLE
                HELLE_EGTVED
                NYBRO_VARDE2
                VARDE_EGTVED2
                LITORUP_HAVERSLEV
                HAVERSLEV_ELLIDSHOEJ
                ELLIDSHOEJ_AALBORG
                TAULOV_SKAERBAEK
                TORSLUNDE_VALLENSBAEK
                VALLENSBAEK_BROENDBY
                BROENDBY_HVIDOVRE
                HVIDOVRE_VESTAMAGER
                TORSLUNDE_MAALOEV
                MAALOEV_LYNGE
                VESTAMAGER_DRAGOER
                HVIDOVRE_AVEDOERE
                VESTAMAGER_AMAGERF
                AMAGERF_SYDHAVNEN
                SYDHAVNEN_HCOERSTED
                DRAGOER_OERESUND
/;
ALIAS(MNLEG,MNLEG2);
ALIAS(SLEG,SLEG2);
ALIAS(FYNLEG,FYNLEG2);

SET FINGERPOINTS(i);
FINGERPOINTS(i) = YES$(sum(FINGERS$ARC_NODE_INC(FINGERS,i),1)>0);


SOS1 VARIABLE MN_TURN(s,t,MNLEG);

SOS1 VARIABLE S_TURN(s,t,SLEG);

SOS1 VARIABLE FYN_TURN(s,t,FYNLEG);

PARAMETER       BigM(e),
                P_PIPES(e,s,t)          "Pressure in pipes",
                P_NODES(i,s,t)          "Pressure at nodes";

BigM(e) = 4375;
* ---------------------------------------- *
*       BOUNDS
* ---------------------------------------- *

* --- SUPPLY LIMITS --- *
VSUP.UP(SOURCE,IST) = SUPPLY_MAX(SOURCE)*MWHperkNM3;
VEXP.UP(SOURCE,IST) = EXP_MAX(SOURCE)*MWHperkNM3;
VSUP.fx(i,IST)$(not SOURCE(i)) = 0;
VEXP.fx(i,IST)$(not SOURCE(i)) = 0;

* --- d LIMITS --- *
VGUD.UP(IA,IST) =   NODEDATA(IA,'Capacity')*MWHperkNM3;

* ---PRESSURE BOUNDS AND REGULATORS--- *
VPs_NODES.LO(IA,IST) = power(NODEDATA(IA,'Pressure'),2);
VPs_NODES.UP(IA,IST) = 80*80;
VPs_PIPES.UP(e,IST)$(not dummy(e))  = power(EDGEDATA(e,'PRESSURE'),2);

* --- STORAGE BOUNDS --- *
VINJ.UP(STORE,IST)       = INJ_MAX(STORE)*MWHperkNM3;
VEXT.UP(STORE,IST)       = EXT_MAX(STORE)*MWHperkNM3;
VSTOCK.UP(STORE,IST)     = STORAGE_MAX(STORE)*MWHperkNM3;

* --- FINGER BOUNDS --- *
*uu.lo(i,j,IST)$ARC(i,j) = 0;
uu.lo(i,j,IST)$ARC(i,j) = -sqrt((80*80-45*45)/sum(e$SEMIARC(e,i,j), cc(e)));
uu.up(i,j,IST)$ARC(i,j) = sqrt((80*80-45*45)/sum(e$SEMIARC(e,i,j), cc(e)));


u.lo(i,e,IST)$N(i,e) = -sqrt((80*80-45*45)/cc(e));
u.up(i,e,IST)$N(i,e) = sqrt((80*80-45*45)/cc(e));

u.lo(i,fingers(e),IST)$(ARC_NODE_INC(e,i)=1) = 0;
u.up(i,fingers(e),IST)$(ARC_NODE_INC(e,i)=-1)= 0;


* ---------------------------------------- *
*       EQUATIONS
* ---------------------------------------- *

Equations
         massbalance(i,s,t)            "Node continuity",
         ssmassbalance(i,s,t)          "SS-Node contunuity",
         linepack(e,s,t)               "Linepack",
         storagebalance(i,s,t)         "Storage balances",
         pipepressure(e,s,t,l)         "Mean pressure level in the pipes",
         flowdir_pos_MN(i,MNLEG,s,t)
         flowdir_neg_MN(i,MNLEG,s,t)
         flowdir_pos_S(i,SLEG,s,t)
         flowdir_neg_S(i,SLEG,s,t)
         flowdir_pos_FYN(i,FYNLEG,s,t)
         flowdir_neg_FYN(i,FYNLEG,s,t)

         ssflowdir_pos_MN(i,j,MNLEG,s,t)
         ssflowdir_neg_MN(i,j,MNLEG,s,t)
         ssflowdir_pos_S(i,j,SLEG,s,t)
         ssflowdir_neg_S(i,j,SLEG,s,t)
         ssflowdir_pos_FYN(i,j,FYNLEG,s,t)
         ssflowdir_neg_FYN(i,j,FYNLEG,s,t)

         linepackss(e,s,t)
         seasonstock(i,s),
         seasonlinepack(e,s)             ;

ssmassbalance(IA,IST) ..
        VSUP(IA,IST)$SOURCE(IA)
      - VEXP(IA,IST)$SOURCE(IA)
      + VEXT(IA,IST)$STORE(IA)
      - VINJ(IA,IST)$STORE(IA)
  =E= sum(j$(ARC(IA,j)),
        uu(IA,j,IST)
      )
      -sum(j$(ARC(j,IA)),
        uu(j,IA,IST)
      )
      + VGUD(IA,IST);



massbalance(IA,IST) ..
        VSUP(IA,IST)$SOURCE(IA)
      - VEXP(IA,IST)$SOURCE(IA)
      + VEXT(IA,IST)$STORE(IA)
      - VINJ(IA,IST)$STORE(IA)
  =E= sum(e$(N(IA,e)),
        u(IA,e,IST)
      )
      + VGUD(IA,IST);

linepack(e,IST(s,t)) ..
         VO(e,s,t++1)
  =E=    VO(e,s,t)
      +sum(i$(N(i,e)),
         u(i,e,s,t)
      );

linepackss(e,IST(s,t)) ..
         0
  =E=
      +sum(i$(N(i,e)),
         u(i,e,s,t)
      );

pipepressure(e,IST,l)$(not DUMMY(e))  ..
         1000*VO(e,IST)/(K(IST)*VOL(e))
  =G=    aa(l)*VPs_PIPES(e,IST)+bb(l);

storagebalance(STORE,IST(s,t))$(ord(t)<card(t)) ..
         VSTOCK(STORE,s,t+1)
  =E=    VSTOCK(STORE,s,t)
      +  VINJ(STORE,s,t)
      -  VEXT(STORE,s,t);

seasonstock(STORE,s) ..
      sum(t$(ord(t)=1),
         VSTOCK(STORE,s++1,t)
      )
  =E= sum(t$(ord(t)=card(t)),
         VSTOCK(STORE,s,t)
      +  VINJ(STORE,s,t)
      -  VEXT(STORE,s,t)
      );

ssflowdir_pos_MN(i,j,MNLEG,IST)$SEMIARC(MNLEG,i,j)      .. uu(i,j,IST)   =G= -sum(MNLEG2$(ORD(MNLEG2) LE ord(MNLEG)), MN_TURN(IST,MNLEG2))          * BigM(MNLEG);
ssflowdir_neg_MN(i,j,MNLEG,IST)$SEMIARC(MNLEG,i,j)      .. uu(i,j,IST)   =L= (1-sum(MNLEG2$(ORD(MNLEG2) LE ord(MNLEG)), MN_TURN(IST,MNLEG2)))       * BigM(MNLEG);
ssflowdir_pos_S(i,j,SLEG,IST)$SEMIARC(SLEG,i,j)         .. uu(i,j,IST)   =G= -sum(SLEG2$(ORD(SLEG2) LE ord(SLEG)), S_TURN(IST,SLEG2))               * BigM(SLEG);
ssflowdir_neg_S(i,j,SLEG,IST)$SEMIARC(SLEG,i,j)         .. uu(i,j,IST)   =L= (1-sum(SLEG2$(ORD(SLEG2) LE ord(SLEG)), S_TURN(IST,SLEG2)))            * BigM(SLEG);
ssflowdir_pos_FYN(i,j,FYNLEG,IST)$SEMIARC(FYNLEG,i,j)   .. uu(i,j,IST)   =G= -sum(FYNLEG2$(ORD(FYNLEG2) LE ord(FYNLEG)), FYN_TURN(IST,FYNLEG2))     * BigM(FYNLEG);
ssflowdir_neg_FYN(i,j,FYNLEG,IST)$SEMIARC(FYNLEG,i,j)   .. uu(i,j,IST)   =L= (1-sum(FYNLEG2$(ORD(FYNLEG2) LE ord(FYNLEG)), FYN_TURN(IST,FYNLEG2)))  * BigM(FYNLEG);

flowdir_pos_MN(i,MNLEG,IST)$N(i,MNLEG)      .. ARC_NODE_INC(MNLEG,i)*u(i,MNLEG,IST)   =G= -sum(MNLEG2$(ORD(MNLEG2) LE ord(MNLEG)), MN_TURN(IST,MNLEG2))          * BigM(MNLEG);
flowdir_neg_MN(i,MNLEG,IST)$N(i,MNLEG)      .. ARC_NODE_INC(MNLEG,i)*u(i,MNLEG,IST)   =L= (1-sum(MNLEG2$(ORD(MNLEG2) LE ord(MNLEG)), MN_TURN(IST,MNLEG2)))       * BigM(MNLEG);
flowdir_pos_S(i,SLEG,IST)$N(i,SLEG)         .. ARC_NODE_INC(SLEG,i)*u(i,SLEG,IST)     =G= -sum(SLEG2$(ORD(SLEG2) LE ord(SLEG)), S_TURN(IST,SLEG2))               * BigM(SLEG);
flowdir_neg_S(i,SLEG,IST)$N(i,SLEG)         .. ARC_NODE_INC(SLEG,i)*u(i,SLEG,IST)     =L= (1-sum(SLEG2$(ORD(SLEG2) LE ord(SLEG)), S_TURN(IST,SLEG2)))            * BigM(SLEG);
flowdir_pos_FYN(i,FYNLEG,IST)$N(i,FYNLEG)   .. ARC_NODE_INC(FYNLEG,i)*u(i,FYNLEG,IST) =G= -sum(FYNLEG2$(ORD(FYNLEG2) LE ord(FYNLEG)), FYN_TURN(IST,FYNLEG2))     * BigM(FYNLEG);
flowdir_neg_FYN(i,FYNLEG,IST)$N(i,FYNLEG)   .. ARC_NODE_INC(FYNLEG,i)*u(i,FYNLEG,IST) =L= (1-sum(FYNLEG2$(ORD(FYNLEG2) LE ord(FYNLEG)), FYN_TURN(IST,FYNLEG2)))  * BigM(FYNLEG);



EQUATIONS
nodepressure_all_hd(i,e,s,t,l)
nodepressure_all_tl(i,e,s,t,l)

nodepressure_finger_hd(i,fingers,s,t,l)
nodepressure_finger_tl(i,fingers,s,t,l)
nodepressure_MN_hd_lo(i,MNLEG,s,t,l)
nodepressure_MN_tl_lo(i,MNLEG,s,t,l)
nodepressure_MN_hd_hi(i,MNLEG,s,t,l)
nodepressure_MN_tl_hi(i,MNLEG,s,t,l)
nodepressure_SLEG_tl_lo(i,SLEG,s,t,l)
nodepressure_SLEG_tl_hi(i,SLEG,s,t,l)
nodepressure_SLEG_hd_lo(i,SLEG,s,t,l)
nodepressure_SLEG_hd_hi(i,SLEG,s,t,l)
nodepressure_FYN_tl_lo(i,FYNLEG,s,t,l)
nodepressure_FYN_tl_hi(i,FYNLEG,s,t,l)
nodepressure_FYN_hd_lo(i,FYNLEG,s,t,l)
nodepressure_FYN_hd_hi(i,FYNLEG,s,t,l)
eMNLEG(s,t)
eSLEG(s,t)
eFYNLEG(s,t)
;

eMNLEG(s,t)  .. sum(MNLEG,MN_TURN(s,t,MNLEG)) =e= 1;
eSLEG(s,t)   .. sum(SLEG,S_TURN(s,t,SLEG)) =e= 1;
eFYNLEG(s,t) .. sum(FYNLEG,FYN_TURN(s,t,FYNLEG)) =e= 1;

nodepressure_all_tl(i,e,IST,l)$(ARC_NODE_INC(e,i)=1)
.. VPs_NODES(i,IST)-VPs_PIPES(e,IST)
   =G= cc(e)*(alpha(l) *u(i,e,IST) + beta(l));
nodepressure_all_hd(i,e,IST,l)$(ARC_NODE_INC(e,i)=-1)
.. -VPs_NODES(i,IST)+VPs_PIPES(e,IST)
   =G=  cc(e)*(alpha(l) * (-u(i,e,IST)) + beta(l));



nodepressure_finger_tl(i,fingers(e),IST,l)$(ARC_NODE_INC(e,i)=1)
.. VPs_NODES(i,IST)-VPs_PIPES(e,IST)
   =G= cc(e)*(alpha(l) *u(i,e,IST) + beta(l));
nodepressure_finger_hd(i,fingers(e),IST,l)$(ARC_NODE_INC(e,i)=-1)
.. -VPs_NODES(i,IST)+VPs_PIPES(e,IST)
   =G=  cc(e)*(alpha(l) * (-u(i,e,IST)) + beta(l));

* LEG MN
nodepressure_MN_tl_lo(i,MNLEG,IST,l)$(ARC_NODE_INC(MNLEG,i)=1)
.. VPs_NODES(i,IST)-VPs_PIPES(MNLEG,IST)
   =G= cc(MNLEG)*(alpha(l) *u(i,MNLEG,IST) + beta(l))
     - BigM(MNLEG)*(sum(MNLEG2$(ORD(MNLEG2) LE ord(MNLEG)), MN_TURN(IST,MNLEG2)) )
   ;
nodepressure_MN_tl_hi(i,MNLEG,IST,l)$(ARC_NODE_INC(MNLEG,i)=1)
.. -VPs_NODES(i,IST)+VPs_PIPES(MNLEG,IST)
   =G= cc(MNLEG)*(alpha(l) *(-u(i,MNLEG,IST)) + beta(l))
     - BigM(MNLEG)*(1-sum(MNLEG2$(ORD(MNLEG2) LE ord(MNLEG)), MN_TURN(IST,MNLEG2)) )
   ;


nodepressure_MN_hd_lo(i,MNLEG,IST,l)$(ARC_NODE_INC(MNLEG,i)=-1)
.. VPs_NODES(i,IST)-VPs_PIPES(MNLEG,IST)
   =G= cc(MNLEG)*(alpha(l) * u(i,MNLEG,IST) + beta(l))
     - BigM(MNLEG)*(1-sum(MNLEG2$(ORD(MNLEG2) LE ord(MNLEG)), MN_TURN(IST,MNLEG2)) )
   ;
nodepressure_MN_hd_hi(i,MNLEG,IST,l)$(ARC_NODE_INC(MNLEG,i)=-1)
.. -VPs_NODES(i,IST)+VPs_PIPES(MNLEG,IST)
   =G= cc(MNLEG)*(alpha(l) * (-u(i,MNLEG,IST)) + beta(l))
     - BigM(MNLEG)*(sum(MNLEG2$(ORD(MNLEG2) LE ord(MNLEG)), MN_TURN(IST,MNLEG2)) )
   ;

* LEG S
nodepressure_SLEG_tl_lo(i,SLEG,IST,l)$(ARC_NODE_INC(SLEG,i)=1)
.. VPs_NODES(i,IST)-VPs_PIPES(SLEG,IST)
   =G= cc(SLEG)*(alpha(l) *u(i,SLEG,IST) + beta(l))
     - BigM(SLEG)*(sum(SLEG2$(ORD(SLEG2) LE ord(SLEG)), S_TURN(IST,SLEG2)) )
   ;
nodepressure_SLEG_tl_hi(i,SLEG,IST,l)$(ARC_NODE_INC(SLEG,i)=1)
.. -VPs_NODES(i,IST)+VPs_PIPES(SLEG,IST)
   =G= cc(SLEG)*(alpha(l) *(-u(i,SLEG,IST)) + beta(l))
     - BigM(SLEG)*(1-sum(SLEG2$(ORD(SLEG2) LE ord(SLEG)), S_TURN(IST,SLEG2)) )
   ;


nodepressure_SLEG_hd_lo(i,SLEG,IST,l)$(ARC_NODE_INC(SLEG,i)=-1)
.. VPs_NODES(i,IST)-VPs_PIPES(SLEG,IST)
   =G= cc(SLEG)*(alpha(l) * u(i,SLEG,IST) + beta(l))
     - BigM(SLEG)*(1-sum(SLEG2$(ORD(SLEG2) LE ord(SLEG)), S_TURN(IST,SLEG2)) )
   ;
nodepressure_SLEG_hd_hi(i,SLEG,IST,l)$(ARC_NODE_INC(SLEG,i)=-1)
.. -VPs_NODES(i,IST)+VPs_PIPES(SLEG,IST)
   =G= cc(SLEG)*(alpha(l) * (-u(i,SLEG,IST)) + beta(l))
     - BigM(SLEG)*(sum(SLEG2$(ORD(SLEG2) LE ord(SLEG)), S_TURN(IST,SLEG2)) )
   ;

* LEG FYN
nodepressure_FYN_tl_lo(i,FYNLEG,IST,l)$(ARC_NODE_INC(FYNLEG,i)=1)
.. VPs_NODES(i,IST)-VPs_PIPES(FYNLEG,IST)
   =G= cc(FYNLEG)*(alpha(l) *u(i,FYNLEG,IST) + beta(l))
     - BigM(FYNLEG)*(sum(FYNLEG2$(ORD(FYNLEG2) LE ord(FYNLEG)), FYN_TURN(IST,FYNLEG2)) )
   ;
nodepressure_FYN_tl_hi(i,FYNLEG,IST,l)$(ARC_NODE_INC(FYNLEG,i)=1)
.. -VPs_NODES(i,IST)+VPs_PIPES(FYNLEG,IST)
   =G= cc(FYNLEG)*(alpha(l) *(-u(i,FYNLEG,IST)) + beta(l))
     - BigM(FYNLEG)*(1-sum(FYNLEG2$(ORD(FYNLEG2) LE ord(FYNLEG)), FYN_TURN(IST,FYNLEG2)) )
   ;


nodepressure_FYN_hd_lo(i,FYNLEG,IST,l)$(ARC_NODE_INC(FYNLEG,i)=-1)
.. VPs_NODES(i,IST)-VPs_PIPES(FYNLEG,IST)
   =G= cc(FYNLEG)*(alpha(l) * u(i,FYNLEG,IST) + beta(l))
     - BigM(FYNLEG)*(1-sum(FYNLEG2$(ORD(FYNLEG2) LE ord(FYNLEG)), FYN_TURN(IST,FYNLEG2)) )
   ;
nodepressure_FYN_hd_hi(i,FYNLEG,IST,l)$(ARC_NODE_INC(FYNLEG,i)=-1)
.. -VPs_NODES(i,IST)+VPs_PIPES(FYNLEG,IST)
   =G= cc(FYNLEG)*(alpha(l) * (-u(i,FYNLEG,IST)) + beta(l))
     - BigM(FYNLEG)*(sum(FYNLEG2$(ORD(FYNLEG2) LE ord(FYNLEG)), FYN_TURN(IST,FYNLEG2)) )
   ;



EQUATIONS
ssnodepressure_finger(i,j,fingers,s,t,l)
ssnodepressure_MN_lo(i,j,MNLEG,s,t,l)
ssnodepressure_MN_hi(i,j,MNLEG,s,t,l)
ssnodepressure_SLEG_lo(i,j,SLEG,s,t,l)
ssnodepressure_SLEG_hi(i,j,SLEG,s,t,l)
ssnodepressure_FYN_lo(i,j,FYNLEG,s,t,l)
ssnodepressure_FYN_hi(i,j,FYNLEG,s,t,l)
 ;



ssnodepressure_finger(i,j,fingers,IST,l)$(SEMIARC(fingers,i,j))
.. VPs_NODES(i,IST)-VPs_NODES(j,IST)
   =G= cc(fingers)*(alpha(l) *uu(i,j,IST) + beta(l));

* LEG MN
ssnodepressure_MN_lo(i,j,MNLEG,IST,l)$(SEMIARC(MNLEG,i,j))
.. VPs_NODES(i,IST)-VPs_NODES(j,IST)
   =G= cc(MNLEG)*(alpha(l) *uu(i,j,IST) + beta(l))
     - BigM(MNLEG)*(sum(MNLEG2$(ORD(MNLEG2) LE ord(MNLEG)), MN_TURN(IST,MNLEG2)) )
   ;
ssnodepressure_MN_hi(i,j,MNLEG,IST,l)$(SEMIARC(MNLEG,i,j))
.. -VPs_NODES(i,IST)+VPs_NODES(j,IST)
   =G= cc(MNLEG)*(alpha(l) *(-uu(i,j,IST)) + beta(l))
     - BigM(MNLEG)*(1-sum(MNLEG2$(ORD(MNLEG2) LE ord(MNLEG)), MN_TURN(IST,MNLEG2)) )
   ;

* LEG S
ssnodepressure_SLEG_lo(i,j,SLEG,IST,l)$(SEMIARC(SLEG,i,j))
.. VPs_NODES(i,IST)-VPs_NODES(j,IST)
   =G= cc(SLEG)*(alpha(l) *uu(i,j,IST) + beta(l))
     - BigM(SLEG)*(sum(SLEG2$(ORD(SLEG2) LE ord(SLEG)), S_TURN(IST,SLEG2)) )
   ;
ssnodepressure_SLEG_hi(i,j,SLEG,IST,l)$(SEMIARC(SLEG,i,j))
.. -VPs_NODES(i,IST)+VPs_NODES(j,IST)
   =G= cc(SLEG)*(alpha(l) *(-uu(i,j,IST)) + beta(l))
     - BigM(SLEG)*(1-sum(SLEG2$(ORD(SLEG2) LE ord(SLEG)), S_TURN(IST,SLEG2)) )
   ;


* LEG FYN
ssnodepressure_FYN_lo(i,j,FYNLEG,IST,l)$(SEMIARC(FYNLEG,i,j))
.. VPs_NODES(i,IST)-VPs_NODES(j,IST)
   =G= cc(FYNLEG)*(alpha(l) *uu(i,j,IST) + beta(l))
     - BigM(FYNLEG)*(sum(FYNLEG2$(ORD(FYNLEG2) LE ord(FYNLEG)), FYN_TURN(IST,FYNLEG2)) )
   ;
ssnodepressure_FYN_hi(i,j,FYNLEG,IST,l)$(SEMIARC(FYNLEG,i,j))
.. -VPs_NODES(i,IST)+VPs_NODES(j,IST)
   =G= cc(FYNLEG)*(alpha(l) *(-uu(i,j,IST)) + beta(l))
     - BigM(FYNLEG)*(1-sum(FYNLEG2$(ORD(FYNLEG2) LE ord(FYNLEG)), FYN_TURN(IST,FYNLEG2)) )
   ;