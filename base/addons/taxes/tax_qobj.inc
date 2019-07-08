* Tax(+)/subsidy(-) on fuel use for electricity generation
    + SUM((C,IS3,T), SUM(IAGK_HASORPOT(Y,IA,G)$(ICA(C,IA) AND IGE(G) AND TAX_F_EL(Y,C,G)),
         IHOURSINST(IS3,T) * TAX_F_EL(Y,C,G)  * VGE_T(Y,IA,G,IS3,T)/ (GDATA(G,'GDFE') * (1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G)))))

* Tax(+)/subsidy(-) on fuel use for heat generation
    + SUM((C,IS3,T), SUM(IAGK_HASORPOT(Y,IA,G)$(ICA(C,IA) AND IGH(G) AND TAX_F_HEAT(Y,C,G)),
         IHOURSINST(IS3,T) * TAX_F_HEAT(Y,C,G) * GDATA(G,'GDCV') * VGH_T(Y,IA,G,IS3,T)/ (GDATA(G,'GDFE') * (1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G)))))

* Tax(+)/subsidy(-) on fuel use
    + SUM((C,IS3,T), SUM(IAGK_HASORPOT(Y,IA,G)$(ICA(C,IA) AND TAX_F(Y,C,G)),
         IHOURSINST(IS3,T) * TAX_F(Y,C,G)  * VGF_T(Y,IA,G,IS3,T)))

* Tax(+)/subsidy(-) on heat generation
    + SUM((C,IS3,T), SUM(IAGK_HASORPOT(Y,IA,G)$(ICA(C,IA) AND TAX_G_HEAT(Y,C,G)),
         IHOURSINST(IS3,T) * TAX_G_HEAT(Y,C,G)  * VGE_T(Y,IA,G,IS3,T)))

* Tax(+)/subsidy(-) on heat generation
    + SUM((C,IS3,T), SUM(IAGK_HASORPOT(Y,IA,G)$(ICA(C,IA) AND TAX_G_EL(Y,C,G)),
         IHOURSINST(IS3,T) * TAX_G_EL(Y,C,G)  * VGE_T(Y,IA,G,IS3,T)))


* Tax on electricity consumption
    + SUM((C,DEUSER), TAX_DE(C,DEUSER) * SUM(IR$CCCRRR(C,IR), DE(Y,IR,DEUSER)))


$ifi %DFLEXQUANT%==yes     +  SUM((C,DEUSER), TAX_DE(C,DEUSER) * SUM(IR$CCCRRR(C,IR),
$ifi %DFLEXQUANT%==yes             SUM(DEF_U1,VDEF_T(IY411,IR,DEUSER,IS3,T,DEF_U1) ) - SUM(DEF_D1,VDEF_T(IY411,IR,DEUSER,IS3,T,DEF_D1) )
$ifi %DFLEXQUANT%==yes           + SUM(DEF_U2,VDEF_T(IY411,IR,DEUSER,IS3,T,DEF_U2) ) - SUM(DEF_D2,VDEF_T(IY411,IR,DEUSER,IS3,T,DEF_D2) )
$ifi %DFLEXQUANT%==yes           + SUM(DEF_U3,VDEF_T(IY411,IR,DEUSER,IS3,T,DEF_U3) ) - SUM(DEF_D3,VDEF_T(IY411,IR,DEUSER,IS3,T,DEF_D3) )))


* Tax on heat consumption
    + SUM((C,DHUSER), TAX_DH(C,DHUSER) * SUM(IA$ICA(C,IA), DH(Y,IA,DHUSER)))

$ifi %DFLEXQUANT%==yes      + SUM((C,DHUSER), TAX_DH(C,DHUSER) * SUM(IA$ICA(C,IA),
$ifi %DFLEXQUANT%==yes          SUM(DHF_U1,VDHF_T(IY411,IA,DHUSER,IS3,T,DHF_U1) ) - SUM(DHF_D1,VDHF_T(IY411,IA,DHUSER,IS3,T,DHF_D1) )
$ifi %DFLEXQUANT%==yes        + SUM(DHF_U2,VDHF_T(IY411,IA,DHUSER,IS3,T,DHF_U2) ) - SUM(DHF_D2,VDHF_T(IY411,IA,DHUSER,IS3,T,DHF_D2) )
$ifi %DFLEXQUANT%==yes        + SUM(DHF_U3,VDHF_T(IY411,IA,DHUSER,IS3,T,DHF_U3) ) - SUM(DHF_D3,VDHF_T(IY411,IA,DHUSER,IS3,T,DHF_D3) ) ))

