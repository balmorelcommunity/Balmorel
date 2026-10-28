* File EV_varassign.inc for addon EV.
* Fixes the first year's charging infrastructure investment and accumulated capacity before the next BB4 model,
* like VGKN/VGKNACCUMNET in Balmorelbb4.sim. Without it, the next model's QV2GINFRAACCUMNET/QG2VINFRAACCUMNET
* see the previous year's accumulated capacity as a free, costless variable and rewrite it.

$ifi %TechInvest%==yes        V2G_INFRA_CAP.FX(IY411FIRST,IR)$IHASBEV(IR)     = V2G_INFRA_CAP.L(IY411FIRST,IR);
$ifi %TechInvest%==yes        G2V_INFRA_CAP.FX(IY411FIRST,IR)$IHASBEV(IR)     = G2V_INFRA_CAP.L(IY411FIRST,IR);
$ifi %TechInvest%==yes        VV2GINFRAACCUMNET.FX(IY411FIRST,IR)$IHASBEV(IR) = VV2GINFRAACCUMNET.L(IY411FIRST,IR);
$ifi %TechInvest%==yes        VG2VINFRAACCUMNET.FX(IY411FIRST,IR)$IHASBEV(IR) = VG2VINFRAACCUMNET.L(IY411FIRST,IR);
* Past years' unidirectional investment still pays its annuity in later years
$ifi %TechInvest%==yes        V2G_INFRA_EXTRA_BIS.FX(IY411FIRST,IR)$IHASBEV(IR) = V2G_INFRA_EXTRA_BIS.L(IY411FIRST,IR);
