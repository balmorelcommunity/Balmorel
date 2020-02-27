
                  +(
                                + VEV_VG2V_BEV(IY411,IR,IS3,T)$(IY411.val>2019)
                                + VEV_VG2V_PHEV(IY411,IR,IS3,T)$(IY411.val>2019)
                   )/(1-EV_DISTLOSSLOAD(IR))
                   +(
$ifi %V2G%==yes                 - VEV_VV2G_BEV(IY411,IR,IS3,T)$(IY411.val>2019)
$ifi %V2G%==yes                 - VEV_VV2G_PHEV(IY411,IR,IS3,T)$(IY411.val>2019)
$ifi %STEPCHARGSCHEME%==yes     - VEV_VV2G_BEV(IY411,IR,IS3,T)$((IY411.val>2019) AND cs('v2g',IY411))
$ifi %STEPCHARGSCHEME%==yes     - VEV_VV2G_PHEV(IY411,IR,IS3,T)$((IY411.val>2019) AND cs('v2g',IY411))
                    +0)/(1-EV_DISTLOSSUNLOAD(IR))
