# The first and last season take their neighbours' EV profiles

The EV leave and return profiles simulate a closed year in which every vehicle starts S01 and ends S52 on the charger, so S01 holds a start-up transient and S52 a return spike, which cancel out only when all 52 seasons are simulated and linked. With `EV_fix_year_edges` (on by default), S01 and S52 take the profiles of S02 and S51, and the year starts from the share of the fleet that the original S01 transient leaves on the charger (`EV_*_start_share`).
