*Individual users addon

$ifi not %GROUP_DEMAND_SHIFT%==yes $goto NO_GROUP_DEMAND_SHIFT

+ (
*Removing default demand
     -SUM(DHUSER, ((DH(IY411,IA,DHUSER) * DH_VAR_T(IA,DHUSER,IS3,T)) / IDH_SUMST(IA,DHUSER))$(IDH_SUMST(IA,DHUSER) GT 0))/(1-DISLOSS_H(IA))
*Introducing new allocated demand
    +SUM((INDIVUSERS_GROUP,DHUSER,IR)$(INDIVUSERS_GROUP_A(IA,DHUSER,INDIVUSERS_GROUP) AND RRRAAA(IR,IA) AND IDH_SUMST(IA,DHUSER)),
             VINDIVUSERS_GROUPSHARE(IY411,IR,DHUSER,INDIVUSERS_GROUP)* DH_VAR_T(IA,DHUSER,IS3,T)/ IDH_SUMST(IA,DHUSER)
        )*SUM((INDIVUSERS_DEMANDTYPE,DHUSER,IR)$(INDIVUSERS_DEMANDTYPE_A(IA,DHUSER,INDIVUSERS_DEMANDTYPE) AND RRRAAA(IR,IA)),
              SUM(IAI$(RRRAAA(IR,IAI) AND INDIVUSERS_DEMANDTYPE_A(IAI,DHUSER,INDIVUSERS_DEMANDTYPE)), DH(IY411,IAI,DHUSER))
             )/(1-DISLOSS_H(IA))
  )$(INDIVUSERS_AAA(IA)
     AND SUM((INDIVUSERS_GROUP,DHUSER),INDIVUSERS_GROUP_A(IA,DHUSER,INDIVUSERS_GROUP))
     AND SUM((INDIVUSERS_DEMANDTYPE,DHUSER),INDIVUSERS_DEMANDTYPE_A(IA,DHUSER,INDIVUSERS_DEMANDTYPE)))

$label NO_GROUP_DEMAND_SHIFT













