# Transmission investment caps limit total capacity

`XMAXINV` and `XH2MAXINV` cap the total transmission capacity between two regions, existing plus invested, so investment is bounded by `XMAXINV - XKFX`. Sources such as the TYNDP state target capacities, and a cap on investment alone would have to be recalculated whenever the existing capacity (`XKFX`) changes between years or data sets.
