*-------------------------------------------------------------------------------
* PB_setdefine.inc  --  Set declarations for the Planetary Boundaries add-on
*-------------------------------------------------------------------------------
* Part of the Balmorel Planetary Boundaries (PB) add-on.
*
* Declares the three abstract GAMS sets used throughout the PB add-on. Their
* elements are populated downstream by PB_setdeclare.inc (which $INCLUDEs the
* scenario-specific or base set-definition files).
*
* PB_LCA_DATASET     LCA impact-category x suffix labels
*                    (e.g. LCA_CO2_constr, LCA_PM_prod_elec, etc.)
*                    used as the third index of the PB_LCA_DATA_* tables.
*
* PB_THRESHOLDS_SET  Sector-level Safe Operating Space (SOS) thresholds, one
*                    element per impact category (e.g. SOS_CO2_sector).
*
* PB_GDTYPE_SET      Generator-type labels for the PB_LCA_DATA layout
*                    (e.g. CAR_EV_ONLY_BATTERY, GEXT, GCND).
*
* Authors: Theo Balanza & Dhruv Sharma
*-------------------------------------------------------------------------------

SET PB_LCA_DATASET;
SET PB_THRESHOLDS_SET;
SET PB_GDTYPE_SET;
