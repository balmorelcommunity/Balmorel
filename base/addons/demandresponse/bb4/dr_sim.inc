* Areas with DR_technologies
IADR(Y,IA,DR_TECH) = YES$DR_FX(Y,IA,DR_TECH);

* Upward shift is limited by the installed capacity of the load minus the hourly load
VDR_UP.up(Y,IA,DR_TECH_SHIFT,S,T)$IADR(Y,IA,DR_TECH_SHIFT)  = IDR_FX(Y,IA,DR_TECH_SHIFT) * (1 - IDR_RATE(IA,DR_TECH_SHIFT,S,T)) ;

* Downward shift is limited by the hourly load
VDR_DOWN.up(Y,IA,DR_TECH,S,T)$IADR(Y,IA,DR_TECH)              =  MIN(IDR_FX(Y,IA,DR_TECH) * IDR_RATE(IA,DR_TECH,S,T), IDR_FX(Y,IA,DR_TECH) * (1$(not DR_DATA(DR_TECH,'DRREGLIM')) + DR_DATA(DR_TECH,'DRREGLIM') ))   ;

* Amount of shedding per week is limited by DRWEEKLYCYCL
*VDR_SHED_MAXVOL.up(Y,IA,DR_TECH_SHED,S)$IADR(Y,IA,DR_TECH_SHED) =   IDR_FX(Y,IA,DR_TECH_SHED)* DR_DATA(DR_TECH_SHED,'DRTOI') * DR_DATA(DR_TECH_SHED,'DRWEEKLYCYCL');

* Limits to total stored energy is given by the input parameters DRSTORMIN and DRSTORMAX
VDR_Store_pos.up(Y,IA,DR_TECH_SHIFT,S,T)$(IADR(Y,IA,DR_TECH_SHIFT) AND DR_DATA(DR_TECH_SHIFT,'DRSTORMAX')) =  DR_DATA(DR_TECH_SHIFT,'DRSTORMAX') * IDR_FX(Y,IA,DR_TECH_SHIFT);
VDR_Store_neg.up(Y,IA,DR_TECH_SHIFT,S,T)$(IADR(Y,IA,DR_TECH_SHIFT) AND DR_DATA(DR_TECH_SHIFT,'DRSTORMIN')) =  DR_DATA(DR_TECH_SHIFT,'DRSTORMIN') * IDR_FX(Y,IA,DR_TECH_SHIFT);

* if not storage size of shift technology is entered, shifting time data are used to calculate "storage size"
VDR_Store_pos.up(Y,IA,DR_TECH_SHIFT,S,T)$(IADR(Y,IA,DR_TECH_SHIFT) AND  NOT DR_DATA(DR_TECH_SHIFT,'DRSTORMIN'))  = SUM(T_ALIAS$DR_HHH2(DR_TECH_SHIFT,T_alias,T), IDR_FX(Y,IA,DR_TECH_SHIFT) * IDR_RATE(IA,DR_TECH_SHIFT,S,T_Alias));
VDR_Store_neg.up(Y,IA,DR_TECH_SHIFT,S,T)$(IADR(Y,IA,DR_TECH_SHIFT) AND  NOT DR_DATA(DR_TECH_SHIFT,'DRSTORMIN'))  = SUM(T_ALIAS$DR_HHH1(DR_TECH_SHIFT,T_alias,T), IDR_FX(Y,IA,DR_TECH_SHIFT) * IDR_RATE(IA,DR_TECH_SHIFT,S,T_Alias));

* The storage varible must be zero at the beginning of each season
*VDR_Store_pos.fx(Y,IA,DR_TECH_SHIFT,S,T)$(ord(T)= 1) = 0;
*VDR_Store_neg.fx(Y,IA,DR_TECH_SHIFT,S,T)$(ord(T)= 1) = 0;
