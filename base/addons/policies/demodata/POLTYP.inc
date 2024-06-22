* Assignment of Policy Type to Policies
* Assign one Policy Type to each Policy
* Choose between:
*   SHAREGROSS   implies Minimal share of electricity generation from specified technologies compared to total electricity generation. NOTE: technologies have to be specified. Unit: Proportion
*   SHARENETTO   implies Minimal share of electricity generation from specified technologies compared to electricity demand. NOTE: technologies have to be specified. Unit: Proportion
*   MAXCO2       implies Maximal CO2 emission. NO technologies need to be defined. Unit: Ton CO2
*   MINPROD      implies Minimal electricity generation in from specified technologies in policy area. NOTE: technologies have to be specified. Unit: MWh.
*   CAPTARGET    implies Minimal electricity generating capacity in policy area of specified technologies.  NOTE: technologies have to be specified. Unit: MW


SET POLTYP(POLICY,POLICYTYPE) 'Define policy type for each policy'
/
POL1.SHAREGROSS
POL2.SHARENETTO
/;
