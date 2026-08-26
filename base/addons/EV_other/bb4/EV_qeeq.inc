                    +(
                                + VEV_G2V_BEV(IY411,IR,IS3,T)$(IHASBEV(IR) AND IY411.val>2019)
                                + VEV_G2V_PHEV(IY411,IR,IS3,T)$(IHASPHEV(IR) AND IY411.val>2019)
                    )/(1-EV_DISTLOSSLOAD(IR))
                    +(
$ifi %V2G%==yes                 - VEV_V2G_BEV(IY411,IR,IS3,T)$(IHASBEV(IR) AND IY411.val>2019)
$ifi %V2G%==yes                 - VEV_V2G_PHEV(IY411,IR,IS3,T)$(IHASPHEV(IR) AND IY411.val>2019)
* + 0 in case V2G is not yes
                    + 0)/(1-EV_DISTLOSSUNLOAD(IR))