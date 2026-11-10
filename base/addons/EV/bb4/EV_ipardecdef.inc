PARAMETERS
IEV_BEV_available(Y,S,T,RRR)               * BEVs in charger
IEV_PHEV_available(Y,S,T,RRR)              * PHEVs in charger
IEV_BEV_return(Y,S,T,RRR)                  * BEVs returning to the charger
IEV_BEV_leave(Y,S,T,RRR)                   * BEVs leaving the charger
IEV_PHEV_return(Y,S,T,RRR)                 * PHEVs returning to the charger
IEV_PHEV_leave(Y,S,T,RRR)                  * PHEVs leaving the charger
IEV_BEV_available_first(Y,S,T,RRR)         * BEVs in charger in first timestep every year
IEV_PHEV_available_first(Y,S,T,RRR)        * PHEVs in charger in first timestep every year
IEV_BEV_outofbounds(Y,S,T,RRR)             * True if EV_available went out of bounds. Negative is lower bound and positive is upper bound.
IEV_PHEV_outofbounds(Y,S,T,RRR)            * True if EV_available went out of bounds. Negative is lower bound and positive is upper bound.
;

* If available_first is not calculated in season_calc, use from max avail. Applies to every simulated season, not just the first.
$ifi not %EV_season_calc%==yes IEV_BEV_available_first(Y,S,T,IR)$(ORD(T) EQ 1 AND IHASBEV(IR)) = EV_BEV_available(Y,IR) * EV_BEV_start_share(Y,IR);
$ifi not %EV_season_calc%==yes IEV_PHEV_available_first(Y,S,T,IR)$(ORD(T) EQ 1 AND IHASPHEV(IR)) = EV_PHEV_available(Y,IR) * EV_PHEV_start_share(Y,IR);

*-------------------------------------------------*
* Season Calculation - Used if S01 is not in simulation, then EV_BEV_avilable and EV_PHEV_available will be calculated to the first season in the simulation.
* This is usefull in simulations where the profile is rapdidly changing over the first seasons.
* Only usefull when interseasonal, else its extra computational time for no gain.

$ifi not %EV_season_calc%==yes $goto NO_EV_season_calc

PARAMETERS
IEV_BEV_return_scalc(Y,SSS,TTT,RRR)                  * BEVs returning to the charger. Used in EV_season_calc
IEV_BEV_leave_scalc(Y,SSS,TTT,RRR)                   * BEVs leaving the charger. Used in EV_season_calc
IEV_PHEV_return_scalc(Y,SSS,TTT,RRR)                 * PHEVs returning to the charger. Used in EV_season_calc
IEV_PHEV_leave_scalc(Y,SSS,TTT,RRR)                  * PHEVs leaving the charger. Used in EV_season_calc
IEV_BEV_available_scalc(Y,SSS,TTT,RRR)               * BEVs in charger up to sim start
IEV_PHEV_available_scalc(Y,SSS,TTT,RRR)              * PHEVs in charger up to sim start
Scounter(S)                                          * Numerical value of S
Tcounter(T)                                          * Numerical value of T
;
* Making T to a numerical value
LOOP(T,
    LOOP(TTT,
        IF(SAMEAS(T, TTT), 
            Tcounter(T) = ORD(TTT);
        );
    );
);
LOOP(S,
    LOOP(SSS,
        IF(SAMEAS(S, SSS), 
            Scounter(S) = ORD(SSS);
        );
    );
);


* First hour in first season outside loop.
IEV_BEV_available_scalc(Y,SSS,TTT,IR)$(ORD(SSS) EQ 1 AND ORD(TTT) EQ 1 AND IHASBEV(IR)) = EV_BEV_available(Y,IR) * EV_BEV_start_share(Y,IR) + EV_BEV_available(Y,IR) * EV_BEV_leave_profile(Y,SSS,TTT,IR);
IEV_PHEV_available_scalc(Y,SSS,TTT,IR)$(ORD(SSS) EQ 1 AND ORD(TTT) EQ 1 AND IHASPHEV(IR)) = EV_PHEV_available(Y,IR) * EV_PHEV_start_share(Y,IR) + EV_PHEV_available(Y,IR) * EV_PHEV_leave_profile(Y,SSS,TTT,IR);

* Creating loop, to ensure it goes through all timesteps
LOOP(S$(ORD(S) EQ CARD(S)),
    LOOP(SSS$(ORD(SSS) LE Scounter(S)),
* Making these calculations and S loop before the rest for computational time
* Calculating the return and leave of EVs up to the last season in simulation, so every simulated season has a starting point
        IEV_BEV_return_scalc(Y,SSS,TTT,IR)$(IHASBEV(IR)) = EV_BEV_available(Y,IR) * EV_BEV_return_profile(Y,SSS,TTT,IR);
        IEV_BEV_leave_scalc(Y,SSS,TTT,IR)$(IHASBEV(IR)) = EV_BEV_available(Y,IR) * EV_BEV_leave_profile(Y,SSS,TTT,IR);

        IEV_PHEV_return_scalc(Y,SSS,TTT,IR)$(IHASPHEV(IR)) = EV_PHEV_available(Y,IR) * EV_PHEV_return_profile(Y,SSS,TTT,IR);
        IEV_PHEV_leave_scalc(Y,SSS,TTT,IR)$(IHASPHEV(IR)) = EV_PHEV_available(Y,IR) * EV_PHEV_leave_profile(Y,SSS,TTT,IR);
        LOOP(TTT,
* If NOT first season but first hour, use last seasons last hour
            IEV_BEV_available_scalc(Y,SSS,TTT,IR)$(ORD(TTT) EQ 1 AND ORD(SSS) GT 1 AND IHASBEV(IR)) = SUM(ITTTALIAS$(ORD(ITTTALIAS) EQ CARD(ITTTALIAS)),IEV_BEV_available_scalc(Y,SSS-1,ITTTALIAS,IR)) + IEV_BEV_return_scalc(Y,SSS,TTT,IR) + IEV_BEV_leave_scalc(Y,SSS,TTT,IR);
            IEV_PHEV_available_scalc(Y,SSS,TTT,IR)$(ORD(TTT) EQ 1 AND ORD(SSS) GT 1 AND IHASPHEV(IR)) = SUM(ITTTALIAS$(ORD(ITTTALIAS) EQ CARD(ITTTALIAS)),IEV_PHEV_available_scalc(Y,SSS-1,ITTTALIAS,IR)) + IEV_PHEV_return_scalc(Y,SSS,TTT,IR) + IEV_PHEV_leave_scalc(Y,SSS,TTT,IR);
* If NOT first hour, add returning/leaving to last hour
            IEV_BEV_available_scalc(Y,SSS,TTT,IR)$(ORD(TTT) GT 1 AND IHASBEV(IR)) = IEV_BEV_available_scalc(Y,SSS,TTT-1,IR) + IEV_BEV_return_scalc(Y,SSS,TTT,IR) + IEV_BEV_leave_scalc(Y,SSS,TTT,IR);
            IEV_PHEV_available_scalc(Y,SSS,TTT,IR)$(ORD(TTT) GT 1 AND IHASPHEV(IR)) = IEV_PHEV_available_scalc(Y,SSS,TTT-1,IR) + IEV_BEV_return_scalc(Y,SSS,TTT,IR) + IEV_BEV_leave_scalc(Y,SSS,TTT,IR);
        );
    );
);

* The available in first hour, is the available for the previous hour, due to it later getting +/- return/leave EVs. Done per simulated season: without it, seasons after the first start from an empty charger and IEV_BEV_available is clamped to 0 for the first hours of the season.

LOOP(T$(ORD(T) EQ 1),
    LOOP(TTT,
        LOOP(S,
            LOOP(SSS$(ORD(SSS) EQ Scounter(S)),
* If first simulation timestep is T001 and not S01, then available first hour is available last hour last season
                IF(Tcounter(T) EQ 1 AND ORD(TTT) EQ CARD(TTT) AND Scounter(S) GT 1,
                    IEV_BEV_available_first(Y,S,T,IR)$(IHASBEV(IR)) = IEV_BEV_available_scalc(Y,SSS-1,TTT,IR);
                    IEV_PHEV_available_first(Y,S,T,IR)$(IHASPHEV(IR)) = IEV_PHEV_available_scalc(Y,SSS-1,TTT,IR);
                );
* If first simulation timestep is T001 S01, then available is max available (times the start share, see EV_pardefine.inc)
                IF(Tcounter(T) EQ 1 AND Scounter(S) EQ 1,
                    IEV_BEV_available_first(Y,S,T,IR)$(IHASBEV(IR)) = EV_BEV_available(Y,IR) * EV_BEV_start_share(Y,IR);
                    IEV_PHEV_available_first(Y,S,T,IR)$(IHASPHEV(IR)) = EV_PHEV_available(Y,IR) * EV_PHEV_start_share(Y,IR);
                );
* If first simulation timestep is not T001, then use T-1 as available.
                IF(Tcounter(T) EQ ORD(TTT) AND ORD(TTT) GT 1,
                    IEV_BEV_available_first(Y,S,T,IR)$(IHASBEV(IR)) = IEV_BEV_available_scalc(Y,SSS,TTT-1,IR);
                    IEV_PHEV_available_first(Y,S,T,IR)$(IHASPHEV(IR)) = IEV_PHEV_available_scalc(Y,SSS,TTT-1,IR);
                );
            );
        );
    );
);


* Cleaning not used Parameters in simulation
IEV_BEV_return_scalc(Y,SSS,TTT,IR) = 0;
IEV_BEV_leave_scalc(Y,SSS,TTT,IR) = 0;
IEV_PHEV_return_scalc(Y,SSS,TTT,IR) = 0;
IEV_PHEV_leave_scalc(Y,SSS,TTT,IR) = 0;
IEV_BEV_available_scalc(Y,SSS,TTT,IR) = 0;
IEV_PHEV_available_scalc(Y,SSS,TTT,IR) = 0;

$label NO_EV_season_calc
*-------------------------------------------------*
* Normalization


$ifi not %EV_normalization%==yes  $goto NO_EV_normalization
* If normilzation is activated but all timesteps is activated, skip to reduce computational time.
PARAMETERS

IEV_BEV_leave_profile(Y,S,T,RRR)           * Placeholder for normalization
IEV_BEV_return_profile(Y,S,T,RRR)          * Placeholder for normalization
IEV_PHEV_leave_profile(Y,S,T,RRR)          * Placeholder for normalization
IEV_PHEV_return_profile(Y,S,T,RRR)         * Placeholder for normalization
IEV_BEV_leave_scale(Y,S,RRR)               * Rescaling of normalized BEV leave flows to the hourly weekly total
IEV_BEV_return_scale(Y,S,RRR)              * Rescaling of normalized BEV return flows to the hourly weekly total
IEV_PHEV_leave_scale(Y,S,RRR)              * Rescaling of normalized PHEV leave flows to the hourly weekly total
IEV_PHEV_return_scale(Y,S,RRR)             * Rescaling of normalized PHEV return flows to the hourly weekly total
$ifi not %EV_season_calc%==yes Tcounter(T)                                * Numerical value of T
;
if (CARD(T) = 168,
* If T = T001*T168, and normalization is yes, then dont normalize.
else
$ifi %EV_season_calc%==yes $goto EV_season_calc2
* Making T to a numerical value
    LOOP(T,
        LOOP(TTT,
            IF(SAMEAS(T, TTT), 
                Tcounter(T) = ORD(TTT);
            );
        );
    );
$label EV_season_calc2
* Loop through all chosen Years and Seasons, and go through T001*168.
    LOOP(TTT$T(TTT),
* If there is only 1 time step chosen. Normalized by total amount of time
        IEV_BEV_leave_profile(Y,S,T,IR)$(CARD(T) EQ 1 AND IHASBEV(IR)) = SUM(ITTTALIAS, EV_BEV_leave_profile(Y,S,ITTTALIAS,IR))/CARD(ITTTALIAS);
        IEV_BEV_return_profile(Y,S,T,IR)$(CARD(T) EQ 1 AND IHASBEV(IR)) = SUM(ITTTALIAS, EV_BEV_return_profile(Y,S,ITTTALIAS,IR))/CARD(ITTTALIAS);
        IEV_PHEV_leave_profile(Y,S,T,IR)$(CARD(T) EQ 1 AND IHASPHEV(IR)) = SUM(ITTTALIAS, EV_PHEV_leave_profile(Y,S,ITTTALIAS,IR))/CARD(ITTTALIAS);
        IEV_PHEV_return_profile(Y,S,T,IR)$(CARD(T) EQ 1 AND IHASPHEV(IR)) = SUM(ITTTALIAS, EV_PHEV_return_profile(Y,S,ITTTALIAS,IR))/CARD(ITTTALIAS);
* If its the last timestep and not the only time step. Normalized by the difference from the very last time and current time. Normalized by the range + 1, to include both start and end step.
        IEV_BEV_leave_profile(Y,S,T,IR)$(ORD(T) EQ CARD(T) AND NOT CARD(T) EQ 1 AND IHASBEV(IR)) = SUM(ITTTALIAS$(ORD(ITTTALIAS) GE (Tcounter(T-1) + FLOOR((Tcounter(T) - Tcounter(T-1) - 1)/2) + 1)), EV_BEV_leave_profile(Y,S,ITTTALIAS,IR))/(CARD(TTT) - (Tcounter(T-1) + FLOOR((Tcounter(T) - Tcounter(T-1) - 1)/2) + 1) + 1);
        IEV_BEV_return_profile(Y,S,T,IR)$(ORD(T) EQ CARD(T) AND NOT CARD(T) EQ 1 AND IHASBEV(IR)) = SUM(ITTTALIAS$(ORD(ITTTALIAS) GE (Tcounter(T-1) + FLOOR((Tcounter(T) - Tcounter(T-1) - 1)/2) + 1)), EV_BEV_return_profile(Y,S,ITTTALIAS,IR))/(CARD(TTT) - (Tcounter(T-1) + FLOOR((Tcounter(T) - Tcounter(T-1) - 1)/2) + 1) + 1);
        IEV_PHEV_leave_profile(Y,S,T,IR)$(ORD(T) EQ CARD(T) AND NOT CARD(T) EQ 1 AND IHASPHEV(IR)) = SUM(ITTTALIAS$(ORD(ITTTALIAS) GE (Tcounter(T-1) + FLOOR((Tcounter(T) - Tcounter(T-1) - 1)/2) + 1)), EV_PHEV_leave_profile(Y,S,ITTTALIAS,IR))/(CARD(TTT) - (Tcounter(T-1) + FLOOR((Tcounter(T) - Tcounter(T-1) - 1)/2) + 1) + 1);
        IEV_PHEV_return_profile(Y,S,T,IR)$(ORD(T) EQ CARD(T) AND NOT CARD(T) EQ 1 AND IHASPHEV(IR)) = SUM(ITTTALIAS$(ORD(ITTTALIAS) GE (Tcounter(T-1) + FLOOR((Tcounter(T) - Tcounter(T-1) - 1)/2) + 1)), EV_PHEV_return_profile(Y,S,ITTTALIAS,IR))/(CARD(TTT) - (Tcounter(T-1) + FLOOR((Tcounter(T) - Tcounter(T-1) - 1)/2) + 1) + 1);
* If its the first time step and not the only time step. Normalized by the counter ITTTALIAS.
        IEV_BEV_leave_profile(Y,S,T,IR)$(ORD(T) EQ 1 AND NOT CARD(T) EQ 1 AND IHASBEV(IR)) = SUM(ITTTALIAS$(ORD(ITTTALIAS) LE (Tcounter(T) + FLOOR((Tcounter(T+1) - Tcounter(T) - 1)/2))), EV_BEV_leave_profile(Y,S,ITTTALIAS,IR))/(Tcounter(T) + FLOOR((Tcounter(T+1) - Tcounter(T) - 1)/2));
        IEV_BEV_return_profile(Y,S,T,IR)$(ORD(T) EQ 1 AND NOT CARD(T) EQ 1 AND IHASBEV(IR)) = SUM(ITTTALIAS$(ORD(ITTTALIAS) LE (Tcounter(T) + FLOOR((Tcounter(T+1) - Tcounter(T) - 1)/2))), EV_BEV_return_profile(Y,S,ITTTALIAS,IR))/(Tcounter(T) + FLOOR((Tcounter(T+1) - Tcounter(T) - 1)/2));
        IEV_PHEV_leave_profile(Y,S,T,IR)$(ORD(T) EQ 1 AND NOT CARD(T) EQ 1 AND IHASPHEV(IR)) = SUM(ITTTALIAS$(ORD(ITTTALIAS) LE (Tcounter(T) + FLOOR((Tcounter(T+1) - Tcounter(T) - 1)/2))), EV_PHEV_leave_profile(Y,S,ITTTALIAS,IR))/(Tcounter(T) + FLOOR((Tcounter(T+1) - Tcounter(T) - 1)/2));
        IEV_PHEV_return_profile(Y,S,T,IR)$(ORD(T) EQ 1 AND NOT CARD(T) EQ 1 AND IHASPHEV(IR)) = SUM(ITTTALIAS$(ORD(ITTTALIAS) LE (Tcounter(T) + FLOOR((Tcounter(T+1) - Tcounter(T) - 1)/2))), EV_PHEV_return_profile(Y,S,ITTTALIAS,IR))/(Tcounter(T) + FLOOR((Tcounter(T+1) - Tcounter(T) - 1)/2));
* If its not the first, last or only time step. Normalized by the difference from last time and current time. UB+1 and LB-1 due to constraint being LE/GE and not LT/GT, and therefor need to include start/end T..
        IEV_BEV_leave_profile(Y,S,T,IR)$(NOT ORD(T) EQ 1 AND NOT ORD(T) EQ CARD(T) AND NOT CARD(T) EQ 1 AND IHASBEV(IR)) = SUM(ITTTALIAS$(ORD(ITTTALIAS) GE (Tcounter(T-1) + FLOOR((Tcounter(T) - Tcounter(T-1) - 1)/2) + 1) AND ORD(ITTTALIAS) LE (Tcounter(T) + FLOOR((Tcounter(T+1) - Tcounter(T) - 1)/2))), EV_BEV_leave_profile(Y,S,ITTTALIAS,IR))/(((Tcounter(T) + FLOOR((Tcounter(T+1) - Tcounter(T) - 1)/2)) - (Tcounter(T-1) + FLOOR((Tcounter(T) - Tcounter(T-1) - 1)/2) + 1)) + 1);
        IEV_BEV_return_profile(Y,S,T,IR)$(NOT ORD(T) EQ 1 AND NOT ORD(T) EQ CARD(T) AND NOT CARD(T) EQ 1 AND IHASBEV(IR)) = SUM(ITTTALIAS$(ORD(ITTTALIAS) GE (Tcounter(T-1) + FLOOR((Tcounter(T) - Tcounter(T-1) - 1)/2) + 1) AND ORD(ITTTALIAS) LE (Tcounter(T) + FLOOR((Tcounter(T+1) - Tcounter(T) - 1)/2))), EV_BEV_return_profile(Y,S,ITTTALIAS,IR))/(((Tcounter(T) + FLOOR((Tcounter(T+1) - Tcounter(T) - 1)/2)) - (Tcounter(T-1) + FLOOR((Tcounter(T) - Tcounter(T-1) - 1)/2) + 1)) + 1);
        IEV_PHEV_leave_profile(Y,S,T,IR)$(NOT ORD(T) EQ 1 AND NOT ORD(T) EQ CARD(T) AND NOT CARD(T) EQ 1 AND IHASPHEV(IR)) = SUM(ITTTALIAS$(ORD(ITTTALIAS) GE (Tcounter(T-1) + FLOOR((Tcounter(T) - Tcounter(T-1) - 1)/2) + 1) AND ORD(ITTTALIAS) LE (Tcounter(T) + FLOOR((Tcounter(T+1) - Tcounter(T) - 1)/2))), EV_PHEV_leave_profile(Y,S,ITTTALIAS,IR))/(((Tcounter(T) + FLOOR((Tcounter(T+1) - Tcounter(T) - 1)/2)) - (Tcounter(T-1) + FLOOR((Tcounter(T) - Tcounter(T-1) - 1)/2) + 1)) + 1);
        IEV_PHEV_return_profile(Y,S,T,IR)$(NOT ORD(T) EQ 1 AND NOT ORD(T) EQ CARD(T) AND NOT CARD(T) EQ 1 AND IHASPHEV(IR)) = SUM(ITTTALIAS$(ORD(ITTTALIAS) GE (Tcounter(T-1) + FLOOR((Tcounter(T) - Tcounter(T-1) - 1)/2) + 1) AND ORD(ITTTALIAS) LE (Tcounter(T) + FLOOR((Tcounter(T+1) - Tcounter(T) - 1)/2))), EV_PHEV_return_profile(Y,S,ITTTALIAS,IR))/(((Tcounter(T) + FLOOR((Tcounter(T+1) - Tcounter(T) - 1)/2)) - (Tcounter(T-1) + FLOOR((Tcounter(T) - Tcounter(T-1) - 1)/2) + 1)) + 1);
    );

* The SOC balance weights each T by CHRONOHOUR, but a window can be longer than its CHRONOHOUR, so window averages alone
* misstate the weekly driving energy. Rescale each week's leave and return flows to the hourly week's totals, times the
* share of the week the selected T cover. Investment runs with evenly spaced T are already within ~1 % and are left out.
$ifi %TechInvest%==yes $goto NO_EV_normalization_rescale
    IEV_BEV_leave_scale(Y,S,IR)$(IHASBEV(IR) AND SUM(T, IEV_BEV_leave_profile(Y,S,T,IR)*CHRONOHOUR(S,T)))
        = SUM(ITTTALIAS, EV_BEV_leave_profile(Y,S,ITTTALIAS,IR)) * SUM(T, CHRONOHOUR(S,T))/CARD(ITTTALIAS) / SUM(T, IEV_BEV_leave_profile(Y,S,T,IR)*CHRONOHOUR(S,T));
    IEV_BEV_return_scale(Y,S,IR)$(IHASBEV(IR) AND SUM(T, IEV_BEV_return_profile(Y,S,T,IR)*CHRONOHOUR(S,T)))
        = SUM(ITTTALIAS, EV_BEV_return_profile(Y,S,ITTTALIAS,IR)) * SUM(T, CHRONOHOUR(S,T))/CARD(ITTTALIAS) / SUM(T, IEV_BEV_return_profile(Y,S,T,IR)*CHRONOHOUR(S,T));
    IEV_PHEV_leave_scale(Y,S,IR)$(IHASPHEV(IR) AND SUM(T, IEV_PHEV_leave_profile(Y,S,T,IR)*CHRONOHOUR(S,T)))
        = SUM(ITTTALIAS, EV_PHEV_leave_profile(Y,S,ITTTALIAS,IR)) * SUM(T, CHRONOHOUR(S,T))/CARD(ITTTALIAS) / SUM(T, IEV_PHEV_leave_profile(Y,S,T,IR)*CHRONOHOUR(S,T));
    IEV_PHEV_return_scale(Y,S,IR)$(IHASPHEV(IR) AND SUM(T, IEV_PHEV_return_profile(Y,S,T,IR)*CHRONOHOUR(S,T)))
        = SUM(ITTTALIAS, EV_PHEV_return_profile(Y,S,ITTTALIAS,IR)) * SUM(T, CHRONOHOUR(S,T))/CARD(ITTTALIAS) / SUM(T, IEV_PHEV_return_profile(Y,S,T,IR)*CHRONOHOUR(S,T));
    IEV_BEV_leave_profile(Y,S,T,IR)$IEV_BEV_leave_scale(Y,S,IR) = IEV_BEV_leave_profile(Y,S,T,IR) * IEV_BEV_leave_scale(Y,S,IR);
    IEV_BEV_return_profile(Y,S,T,IR)$IEV_BEV_return_scale(Y,S,IR) = IEV_BEV_return_profile(Y,S,T,IR) * IEV_BEV_return_scale(Y,S,IR);
    IEV_PHEV_leave_profile(Y,S,T,IR)$IEV_PHEV_leave_scale(Y,S,IR) = IEV_PHEV_leave_profile(Y,S,T,IR) * IEV_PHEV_leave_scale(Y,S,IR);
    IEV_PHEV_return_profile(Y,S,T,IR)$IEV_PHEV_return_scale(Y,S,IR) = IEV_PHEV_return_profile(Y,S,T,IR) * IEV_PHEV_return_scale(Y,S,IR);
$label NO_EV_normalization_rescale


* Replace data with the internal normalized parameters
    EV_BEV_leave_profile(Y,S,T,IR) = IEV_BEV_leave_profile(Y,S,T,IR);
    EV_BEV_return_profile(Y,S,T,IR) = IEV_BEV_return_profile(Y,S,T,IR);
    EV_PHEV_leave_profile(Y,S,T,IR) = IEV_PHEV_leave_profile(Y,S,T,IR);
    EV_PHEV_return_profile(Y,S,T,IR) = IEV_PHEV_return_profile(Y,S,T,IR);
    
* Cleaning not used Parameters in simulation
    IEV_BEV_leave_profile(Y,S,T,RRR) = 0;
    IEV_BEV_return_profile(Y,S,T,RRR) = 0;
    IEV_PHEV_leave_profile(Y,S,T,RRR) = 0;
    IEV_PHEV_return_profile(Y,S,T,RRR) = 0;
    EV_BEV_leave_profile(YYY,SSS,TTT,RRR)$((NOT Y(YYY)) OR (NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
    EV_BEV_return_profile(YYY,SSS,TTT,RRR)$((NOT Y(YYY)) OR (NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
    EV_PHEV_leave_profile(YYY,SSS,TTT,RRR)$((NOT Y(YYY)) OR (NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
    EV_PHEV_return_profile(YYY,SSS,TTT,RRR)$((NOT Y(YYY)) OR (NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
);



$label NO_EV_normalization

*-------------------------------------------------*
* Internal parameters which should be in this file


* Amount of returning and leaving EVs
IEV_BEV_return(Y,S,T,IR)$(IHASBEV(IR)) = EV_BEV_available(Y,IR) * EV_BEV_return_profile(Y,S,T,IR);
IEV_BEV_leave(Y,S,T,IR)$(IHASBEV(IR)) = EV_BEV_available(Y,IR) * EV_BEV_leave_profile(Y,S,T,IR);

IEV_PHEV_return(Y,S,T,IR)$(IHASPHEV(IR)) = EV_PHEV_available(Y,IR) * EV_PHEV_return_profile(Y,S,T,IR);
IEV_PHEV_leave(Y,S,T,IR)$(IHASPHEV(IR)) = EV_PHEV_available(Y,IR) * EV_PHEV_leave_profile(Y,S,T,IR);





* Calculate amount of available EVs in each time step. If its the first timestep then all EVs are available.
* If INTERSEASONAL
$ifi not %EV_INTERSEASONAL%==yes  $goto NO_EV_INTERSEASONAL

* If first season and first hour use maximum avail
IEV_BEV_available(Y,S,T,IR)$(ORD(T) EQ 1 AND ORD(S) EQ 1 AND IHASBEV(IR)) = IEV_BEV_available_first(Y,S,T,IR) + IEV_BEV_return(Y,S,T,IR) + IEV_BEV_leave(Y,S,T,IR);
IEV_PHEV_available(Y,S,T,IR)$(ORD(T) EQ 1 AND ORD(S) EQ 1 AND IHASPHEV(IR)) = IEV_PHEV_available_first(Y,S,T,IR) + IEV_PHEV_return(Y,S,T,IR) + IEV_PHEV_leave(Y,S,T,IR);

* Creating loop, to ensure one season is created at a time
* Looping through Y and IR aswell to get them controlled in IF statements.
LOOP(Y,
    LOOP(S,
        LOOP(T,
            LOOP(IR$(IHASBEV(IR) OR IHASPHEV(IR)),
* If NOT first season but first hour, use last seasons last hour
                IEV_BEV_available(Y,S,T,IR)$(ORD(T) EQ 1 AND ORD(S) GT 1) = SUM(ITALIAS$(ORD(ITALIAS) EQ CARD(ITALIAS)),IEV_BEV_available(Y,S-1,ITALIAS,IR)) + IEV_BEV_return(Y,S,T,IR) + IEV_BEV_leave(Y,S,T,IR);
                IEV_PHEV_available(Y,S,T,IR)$(ORD(T) EQ 1 AND ORD(S) GT 1) = SUM(ITALIAS$(ORD(ITALIAS) EQ CARD(ITALIAS)),IEV_PHEV_available(Y,S-1,ITALIAS,IR)) + IEV_PHEV_return(Y,S,T,IR) + IEV_PHEV_leave(Y,S,T,IR);

* If NOT first hour, add returning/leaving to last hour
                IEV_BEV_available(Y,S,T,IR)$(ORD(T) GT 1) = IEV_BEV_available(Y,S,T-1,IR) + IEV_BEV_return(Y,S,T,IR) + IEV_BEV_leave(Y,S,T,IR);
                IEV_PHEV_available(Y,S,T,IR)$(ORD(T) GT 1) = IEV_PHEV_available(Y,S,T-1,IR) + IEV_PHEV_return(Y,S,T,IR) + IEV_PHEV_leave(Y,S,T,IR); 
                
* Ensure there is never less than 0 EVs or more than EV_BEV_available/EV_PHEV_available. Cases this happend: Not all T used or bad profile
                IF(IEV_BEV_available(Y,S,T,IR) < 0,
                    IEV_BEV_leave(Y,S,T,IR) = MIN((IEV_BEV_leave(Y,S,T,IR) - IEV_BEV_available(Y,S,T,IR)), 0);
                    IEV_BEV_available(Y,S,T,IR) = 0;
                    IEV_BEV_outofbounds(Y,S,T,IR) = -1;
                );
                IF(IEV_BEV_available(Y,S,T,IR) > EV_BEV_available(Y,IR),
                    IEV_BEV_return(Y,S,T,IR) = MAX((IEV_BEV_return(Y,S,T,IR) - (IEV_BEV_available(Y,S,T,IR) - EV_BEV_available(Y,IR))), 0);
                    IEV_BEV_available(Y,S,T,IR) = EV_BEV_available(Y,IR);
                    IEV_BEV_outofbounds(Y,S,T,IR) = 1;
                );
                IF(IEV_PHEV_available(Y,S,T,IR) < 0,
                    IEV_PHEV_leave(Y,S,T,IR) = MIN((IEV_PHEV_leave(Y,S,T,IR) - IEV_PHEV_available(Y,S,T,IR)), 0);
                    IEV_PHEV_available(Y,S,T,IR) = 0;
                    IEV_PHEV_outofbounds(Y,S,T,IR) = -1;
                );
                IF(IEV_PHEV_available(Y,S,T,IR) > EV_PHEV_available(Y,IR),
                    IEV_PHEV_return(Y,S,T,IR) = MAX((IEV_PHEV_return(Y,S,T,IR) - (IEV_PHEV_available(Y,S,T,IR) - EV_PHEV_available(Y,IR))), 0);
                    IEV_PHEV_available(Y,S,T,IR) = EV_PHEV_available(Y,IR);
                    IEV_PHEV_outofbounds(Y,S,T,IR) = 1;
                );
            );
        );
    );
);

* If INTRASEASONAL
$label NO_EV_INTERSEASONAL
$ifi %EV_INTERSEASONAL%==yes  $goto YES_EV_INTERSEASONAL

IEV_BEV_available(Y,S,T,IR)$(ORD(T) EQ 1 AND IHASBEV(IR)) = IEV_BEV_available_first(Y,S,T,IR) + IEV_BEV_return(Y,S,T,IR) + IEV_BEV_leave(Y,S,T,IR);
IEV_PHEV_available(Y,S,T,IR)$(ORD(T) EQ 1 AND IHASPHEV(IR)) = IEV_PHEV_available_first(Y,S,T,IR) + IEV_PHEV_return(Y,S,T,IR) + IEV_PHEV_leave(Y,S,T,IR);

* Creating loop, to ensure one season is created at a time
* Looping through Y and IR aswell to get them controlled in IF statements.
LOOP(Y,
    LOOP(S,
        LOOP(T,
            LOOP(IR$(IHASBEV(IR) OR IHASPHEV(IR)),
* If NOT first hour, add returning/leaving to last hour
                IEV_BEV_available(Y,S,T,IR)$(ORD(T) GT 1) = IEV_BEV_available(Y,S,T-1,IR) + IEV_BEV_return(Y,S,T,IR) + IEV_BEV_leave(Y,S,T,IR);
                IEV_PHEV_available(Y,S,T,IR)$(ORD(T) GT 1) = IEV_PHEV_available(Y,S,T-1,IR) + IEV_PHEV_return(Y,S,T,IR) + IEV_PHEV_leave(Y,S,T,IR); 
                
* Ensure there is never less than 0 EVs or more than EV_BEV_available/EV_PHEV_available. Cases this happend: Not all T used or bad profile
                IF(IEV_BEV_available(Y,S,T,IR) < 0,
                    IEV_BEV_leave(Y,S,T,IR) = MIN((IEV_BEV_leave(Y,S,T,IR) - IEV_BEV_available(Y,S,T,IR)), 0);
                    IEV_BEV_available(Y,S,T,IR) = 0;
                    IEV_BEV_outofbounds(Y,S,T,IR) = -1;
                );
                IF(IEV_BEV_available(Y,S,T,IR) > EV_BEV_available(Y,IR),
                    IEV_BEV_return(Y,S,T,IR) = MAX((IEV_BEV_return(Y,S,T,IR) - (IEV_BEV_available(Y,S,T,IR) - EV_BEV_available(Y,IR))), 0);
                    IEV_BEV_available(Y,S,T,IR) = EV_BEV_available(Y,IR);
                    IEV_BEV_outofbounds(Y,S,T,IR) = 1;
                );
                IF(IEV_PHEV_available(Y,S,T,IR) < 0,
                    IEV_PHEV_leave(Y,S,T,IR) = MIN((IEV_PHEV_leave(Y,S,T,IR) - IEV_PHEV_available(Y,S,T,IR)), 0);
                    IEV_PHEV_available(Y,S,T,IR) = 0;
                    IEV_PHEV_outofbounds(Y,S,T,IR) = -1;
                );
                IF(IEV_PHEV_available(Y,S,T,IR) > EV_PHEV_available(Y,IR),
                    IEV_PHEV_return(Y,S,T,IR) = MAX((IEV_PHEV_return(Y,S,T,IR) - (IEV_PHEV_available(Y,S,T,IR) - EV_PHEV_available(Y,IR))), 0);
                    IEV_PHEV_available(Y,S,T,IR) = EV_PHEV_available(Y,IR);
                    IEV_PHEV_outofbounds(Y,S,T,IR) = 1;
                );
            );
        );
    );
);


$label YES_EV_INTERSEASONAL

IEV_BEV_available(Y,S,T,IR)$(IHASBEV(IR)) = 2*IEV_BEV_available(Y,S,T,IR);
IEV_BEV_return(Y,S,T,IR)$(IHASBEV(IR)) = 2* IEV_BEV_return(Y,S,T,IR);
IEV_BEV_leave(Y,S,T,IR)$(IHASBEV(IR)) = 2*IEV_BEV_leave(Y,S,T,IR);

*Option here to make grid loss for either load or unload. Currently there is no loss on ELEC_STO and therefor not on EV, else it would create unfair competition
Parameters
EV_DISTLOSSLOAD(RRR)
EV_DISTLOSSUNLOAD(RRR)
;
*EV_DISTLOSSLOAD(IR)=DISLOSS_E(IR);
* 0 for now due to electrical storage is 0.
EV_DISTLOSSLOAD(IR)=0;
EV_DISTLOSSUNLOAD(IR)=0;



*-------------------------------------------------*
* Charging infrastructure lifetime.
* IEV_INFRA_ALIVE(Yinv,Y) = 1 if infrastructure invested in Yinv is in place, and its annuity paid, in Y.
* Same rule as IYHASANNUITYG in Balmorelbb4.inc, with EV_INFRA_LIFETIME instead of GDLIFETIME.
SCALAR    IEV_INFRA_ANNUITY             'Annuity factor of EV charging infrastructure (fraction)';
PARAMETER IEV_INFRA_ALIVE(Y,Y)          'Charging infrastructure invested in Y (first index) is in place in Y (second index) (0,1)';
PARAMETER IEV_INFRA_LEFT(Y,Y)           'Remaining lifetime of charging infrastructure invested in Y (first index) at the beginning of Y (second index) (years)';
PARAMETER IEV_INFRA_NINV(Y)             'Number of charging infrastructure investments made within Y';

IEV_INFRA_ANNUITY = DISCOUNTRATE/(1-(1+DISCOUNTRATE)**(-EV_INFRA_LIFETIME));

LOOP(IYALIAS,
  LOOP(Y$(ORD(Y) EQ ORD(IYALIAS)), IEV_INFRA_LEFT(IYALIAS,Y) = EV_INFRA_LIFETIME;);
);
LOOP(IYALIAS,
  ILOOPBREAK = 0;
  IEV_INFRA_NINV(IYALIAS) = MAX(1, ROUND(IWEIGHTY(IYALIAS)/EV_INFRA_LIFETIME));
  LOOP(Y$(ORD(Y) GE ORD(IYALIAS) AND (ILOOPBREAK EQ 0)),
    IF (ORD(Y) EQ ORD(IYALIAS),
      IEV_INFRA_ALIVE(IYALIAS,Y) = 1;
      IF (IEV_INFRA_LEFT(IYALIAS,Y)*IEV_INFRA_NINV(IYALIAS) LE IWEIGHTY(Y), ILOOPBREAK = 1;);
      IEV_INFRA_LEFT(IYALIAS,Y+1)$(ORD(Y) NE CARD(IYALIAS2)) = EV_INFRA_LIFETIME*IEV_INFRA_NINV(IYALIAS) - IWEIGHTY(Y);
    );
    IF (ORD(Y) GT ORD(IYALIAS),
      IF (IEV_INFRA_LEFT(IYALIAS,Y) GT IWEIGHTY(Y),
        IEV_INFRA_ALIVE(IYALIAS,Y) = 1;
        IEV_INFRA_LEFT(IYALIAS,Y+1)$(ORD(Y) NE CARD(IYALIAS2)) = IEV_INFRA_LEFT(IYALIAS,Y) - IWEIGHTY(Y);
      );
      IF ((IEV_INFRA_LEFT(IYALIAS,Y) GE IWEIGHTY(IYALIAS)/2) AND (IEV_INFRA_LEFT(IYALIAS,Y) LE IWEIGHTY(Y)),
        IEV_INFRA_ALIVE(IYALIAS,Y) = 1;
        ILOOPBREAK = 1;
      );
      IF ((IEV_INFRA_LEFT(IYALIAS,Y) LT IWEIGHTY(IYALIAS)/2) AND (IEV_INFRA_LEFT(IYALIAS,Y) LE IWEIGHTY(Y)),
        IEV_INFRA_ALIVE(IYALIAS,Y) = 0;
        ILOOPBREAK = 1;
      );
    );
  );
);
