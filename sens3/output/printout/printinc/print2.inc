* File print2.inc.
* This file is part of the Balmorel model.


* File last time modified 17-05-2002 (rus)

* -----------------------------------------------------------------------------
* Contents:

* This file contains definitions of a number of temporary parameters and sets
* that may be used for printout of simulation results.

* -----------------------------------------------------------------------------

PARAMETERS

*------------------------------------------------------------------------------
* Define parameters for storing the results for each year in the simulation.
* These values are not used in the modelling, however, they are calculated
* because they may be convenient printout
*------------------------------------------------------------------------------

*..............................................................................
* Summations over time to get seasonal and annual values,
* Summations over technologies to get area, regional country and total values,
* Summations over geography to get regional, national and total values
*..............................................................................


* ELECTRICITY

* Electricity demand

*   in each region each time period
    EDqRT(RRR,S,T)

*   in each region each season
    EDqRS(RRR,S)

*   in each region each year
    EDqRY(RRR)


*   in each country each time period
    EDqCT(C,S,T)

*   in each country each season
    EDqCS(C,S)

*   in each country each year
    EDqCY(C)

*..............................................................................

* Electricity generation of all (old and new) technologies: (MWh)

*   in each area for each time period
    EGqAT(AAA,G,S,T)

*   in each area for each season
    EGqAS(AAA,G,S)

*   in each area for each year
    EGqAY(AAA,G)


*   in each region for each time period
    EGqRT(RRR,G,S,T)

*   in each region for each season
    EGqRS(RRR,G,S)

*   in each region for each year
    EGqRY(RRR,G)


*   in each country for each time period
    EGqCT(C,G,S,T)

*   in each country for each season
    EGqCS(C,G,S)

*   in each country for each year
    EGqCY(C,G)

*..............................................................................

* Electricity generation of old technologies: (MWh)

*   in each area for each time period
    EGOqAT(AAA,G,S,T)

*   in each area for each season
    EGOqAS(AAA,G,S)

*   in each area for each year
    EGOqAY(AAA,G)


*   in each region for each time period
    EGOqRT(RRR,G,S,T)

*   in each region for each season
    EGOqRS(RRR,G,S)

*   in each region for each year
    EGOqRY(RRR,G)


*   in each country for each time period
    EGOqCT(C,G,S,T)

*   in each country for each season
    EGOqCS(C,G,S)

*   in each country for each year
    EGOqCY(C,G)

*..............................................................................

* Electricity generation of new technologies: (MWh)

*   in each area for each time period
    EGNqAT(AAA,G,S,T)

*   in each area for each season
    EGNqAS(AAA,G,S)

*   in each area for each year
    EGNqAY(AAA,G)


*   in each region for each time period
    EGNqRT(RRR,G,S,T)

*   in each region for each season
    EGNqRS(RRR,G,S)

*   in each region for each year
    EGNqRY(RRR,G)


*   in each country for each time period
    EGNqCT(C,G,S,T)

*   in each country for each season
    EGNqCS(C,G,S)

*   in each country for each year
    EGNqCY(C,G)

*..............................................................................

* Total electricity consumption for all (old and new) heat pumps  (MWh):

*   in each country for each year
    EZG13qCY(C)


* Total electricity consumption for old heat pumps  (MWh):

*   in each country for each year
    EZGO13qCY(C)


* Total electricity consumption for new heat pumps  (MWh):

*   in each country for each year
    EZGN13qCY(C)

*..............................................................................


* Total electricity generation from all (old and new) technologies: (MWh)

*   in each area for each time period
    EZGqAT(AAA,S,T)

*   in each area for each season
    EZGqAS(AAA,S)

*   in each area for each year
    EZGqAY(AAA)


*   in each region for each time period
    EZGqRT(RRR,S,T)

*   in each region for each season
    EZGqRS(RRR,S)

*   in each region for each year
    EZGqRY(RRR)


*   in each country for each time period
    EZGqCT(C,S,T)

*   in each country for each season
    EZGqCS(C,S)

*   in each country for each year
    EZGqCY(C)


*   in all countries for each time period
    EZGqT(Y,S,T)

*   in all countries for each season
    EZGqS(Y,S)

*   in all countries for each year
    EZGqY(Y)

*..............................................................................

* Total electricity generation from old technologies: (MWh)

*   in each area for each time period
    EZGOqAT(AAA,S,T)

*   in each area for each season
    EZGOqAS(AAA,S)

*   in each area for each year
    EZGOqAY(AAA)


*   in each region for each time period
    EZGOqRT(RRR,S,T)

*   in each region for each season
    EZGOqRS(RRR,S)

*   in each region for each year
    EZGOqRY(RRR)


*   in each country for each time period
    EZGOqCT(C,S,T)

*   in each country for each season
    EZGOqCS(C,S)

*   in each country for each year
    EZGOqCY(C)


*   in all countries for each time period
    EZGOqT(Y,S,T)

*   in all countries for each season
    EZGOqS(Y,S)

*   in all countries for each year
    EZGOqY(Y)

*..............................................................................

* Total electricity generation from new technologies: (MWh)

*   in each area for each time period
    EZGNqAT(AAA,S,T)

*   in each area for each season
    EZGNqAS(AAA,S)

*   in each area for each year
    EZGNqAY(AAA)


*   in each region for each time period
    EZGNqRT(RRR,S,T)

*   in each region for each season
    EZGNqRS(RRR,S)

*   in each region for each year
    EZGNqRY(RRR)


*   in each country for each time period
    EZGNqCT(C,S,T)

*   in each country for each season
    EZGNqCS(C,S)

*   in each country for each year
    EZGNqCY(C)


*   in all countries for each time period
    EZGNqT(Y,S,T)

*   in all countries for each season
    EZGNqS(Y,S)

*   in all countries for each year
    EZGNqY(Y)

*..............................................................................

* Distribution loss of electricity (MWh):

*   in each region per year
    ELqRY(RRR)

*   in each country per year
    ELqCY(C)
*..............................................................................



* Electricity export from region to other regions: (MWh)

*   in each time period
    EX1qRT(RRR,S,T)

*   in each season
    EX1qRS(RRR,S)

*   in each year
    EX1qRY(RRR)


* Electricity export from country to other countries: (MWh)

*   in each time period
    EX1qCT(C,S,T)

*   in each season
    EX1qCS(C,S)

*   in each year
    EX1qCY(C)


* Electricity import from other regions to region: (MWh)

*   in each time period
    EX2qRT(RRR,S,T)

*   in each season
    EX2qRS(RRR,S)

*   in each year
    EX2qRY(RRR)


* Electricity import from other countries to country: (MWh)

*   in each time period
    EX2qCT(C,S,T)

*   in each season
    EX2qCS(C,S)

*   in each year
    EX2qCY(C)


* Electricity net export from region to third parties countries: (MWh)

*   in each time period
    EX3qRT(RRR,S,T)

*   in each season
    EX3qRS(RRR,S)

*   in each year
    EX3qRY(RRR)


* Electricity net export from country to third parties countries: (MWh)

*   in each time period
    EX3qCT(C,S,T)

*   in each season
    EX3qCS(C,S)

*   in each year
    EX3qCY(C)
*..............................................................................

* Transmission loss of electricity (MWh):

*   in each region in each time period
    EXLqRT(RRR,S,T)

*   in each region in each season
    EXLqRS(RRR,S)

*   in each region per year
    EXLqRY(RRR)


*   in each country in each time period
    EXLqCT(C,S,T)

*   in each country in each season
    EXLqCS(C,S)

*   in each country per year
    EXLqCY(C)

*   Bottle neck income
    XBOTTLEIN(IRRRE,IRRRI,S,T) 'Bottle neck income (internal)'

* Lars: Indfoert flaskehalsindtaegter til 3. lande.
$ifi "%X3V%"=="yes" XBOTTLEX3V(RRR,X3VPLACE0,S,T) 'Bottle neck income (3. countries price dependent)'
    XBOTTLEX3(RRR,S,T) 'Bottle neck income (3. countries price independent)'



*..............................................................................



* HEAT:


* Heat demand

*   in each area each time period
    HDqAT(AAA,S,T)

*   in each area each season
    HDqAS(AAA,S)

*   in each area each year
    HDqAY(AAA)


*   in each region each time period
    HDqRT(RRR,S,T)

*   in each region each season
    HDqRS(RRR,S)

*   in each region each year
    HDqRY(RRR)


*   in each country each time period
    HDqCT(C,S,T)

*   in each country each season
    HDqCS(C,S)

*   in each country each year
    HDqCY(C)

*..............................................................................


* Heat generation of all (old and new) technologies: (MWh)

*   in each area for each time period
    HGqAT(AAA,G,S,T)

*   in each area for each season
    HGqAS(AAA,G,S)

*   in each area for each year
    HGqAY(AAA,G)


*   in each region for each time period
    HGqRT(RRR,G,S,T)

*   in each region for each season
    HGqRS(RRR,G,S)

*   in each region for each year
    HGqRY(RRR,G)


*   in each country for each time period
    HGqCT(C,G,S,T)

*   in each country for each season
    HGqCS(C,G,S)

*   in each country for each year
    HGqCY(C,G)

*..............................................................................

* Heat generation of old technologies: (MWh)

*   in each area for each time period
    HGOqAT(AAA,G,S,T)

*   in each area for each season
    HGOqAS(AAA,G,S)

*   in each area for each year
    HGOqAY(AAA,G)


*   in each region for each time period
    HGOqRT(RRR,G,S,T)

*   in each region for each season
    HGOqRS(RRR,G,S)

*   in each region for each year
    HGOqRY(RRR,G)


*   in each country for each time period
    HGOqCT(C,G,S,T)

*   in each country for each season
    HGOqCS(C,G,S)

*   in each country for each year
    HGOqCY(C,G)

*..............................................................................

* Heat generation of new technologies: (MWh)

*   in each area for each time period
    HGNqAT(AAA,G,S,T)

*   in each area for each season
    HGNqAS(AAA,G,S)

*   in each area for each year
    HGNqAY(AAA,G)


*   in each region for each time period
    HGNqRT(RRR,G,S,T)

*   in each region for each season
    HGNqRS(RRR,G,S)

*   in each region for each year
    HGNqRY(RRR,G)


*   in each country for each time period
    HGNqCT(C,G,S,T)

*   in each country for each season
    HGNqCS(C,G,S)

*   in each country for each year
    HGNqCY(C,G)

*..............................................................................

* Total heat generation from all (old and new) technologies: (MWh)

*   in each area for each time period
    HZGqAT(AAA,S,T)

*   in each area for each season
    HZGqAS(AAA,S)

*   in each area for each year
    HZGqAY(AAA)


*   in each region for each time period
    HZGqRT(RRR,S,T)

*   in each region for each season
    HZGqRS(RRR,S)

*   in each region for each year
    HZGqRY(RRR)


*   in each country for each time period
    HZGqCT(C,S,T)

*   in each country for each season
    HZGqCS(C,S)

*   in each country for each year
    HZGqCY(C)


*   in all countries for each time period
    HZGqT(Y,S,T)

*   in all countries for each season
    HZGqS(Y,S)

*   in all countries for each year
    HZGqY(Y)

*..............................................................................

* Total heat generation from old technologies: (MWh)

*   in each area for each time period
    HZGOqAT(AAA,S,T)

*   in each area for each season
    HZGOqAS(AAA,S)

*   in each area for each year
    HZGOqAY(AAA)


*   in each region for each time period
    HZGOqRT(RRR,S,T)

*   in each region for each season
    HZGOqRS(RRR,S)

*   in each region for each year
    HZGOqRY(RRR)


*   in each country for each time period
    HZGOqCT(C,S,T)

*   in each country for each season
    HZGOqCS(C,S)

*   in each country for each year
    HZGOqCY(C)


*   in all countries for each time period
    HZGOqT(Y,S,T)

*   in all countries for each season
    HZGOqS(Y,S)

*   in all countries for each year
    HZGOqY(Y)

*..............................................................................

* Total heat generation from new technologies: (MWh)

*   in each area for each time period
    HZGNqAT(AAA,S,T)

*   in each area for each season
    HZGNqAS(AAA,S)

*   in each area for each year
    HZGNqAY(AAA)


*   in each region for each time period
    HZGNqRT(RRR,S,T)

*   in each region for each season
    HZGNqRS(RRR,S)

*   in each region for each year
    HZGNqRY(RRR)


*   in each country for each time period
    HZGNqCT(C,S,T)

*   in each country for each season
    HZGNqCS(C,S)

*   in each country for each year
    HZGNqCY(C)


*   in all countries for each time period
    HZGNqT(Y,S,T)

*   in all countries for each season
    HZGNqS(Y,S)

*   in all countries for each year
    HZGNqY(Y)

*..............................................................................

* Distribution loss of heat (MWh):

*   in each area per year
    HLqAY(AAA)

*   in each region per year
    HLqRY(RRR)

*   in each country per year
    HLqCY(C)

*..............................................................................

* Fuel consumption (MWh):

*   in each area per time period
    EHFqAT(AAA,G,S,T)

*   in each area for each season
    EHFqAS(AAA,G,S)

*   in each area for each year
    EHFqAY(AAA,G)

*   in each region per time period
    EHFqRT(RRR,G,S,T)

*   in each region for each season
    EHFqRS(RRR,G,S)

*   in each region for each year
    EHFqRY(RRR,G)

*   in each country per time period
    EHFqCT(C,G,S,T)

*   in each country for each season
    EHFqCS(C,G,S)

*   in each country for each year
    EHFqCY(C,G)

*..............................................................................

* Total amount of CO2 (t), SO2 (t), and NOx (kg) emission each year in country:

*   CO2 in each region for each time period
    EHM1qRT(RRR,S,T)


*   CO2 in each country for each year
    EHM1qCY(C)

*   SO2 in each country for each year
    EHM2qCY(C)

*   NOX in each country for each year
    EHM3qCY(C)

*   CH4 in each country for each year
    EHM4qCY(C)

*   N2O in each country for each year
    EHM5qCY(C)

*..............................................................................

* The total system cost that year (excluding taxes)
    SYSCOSTqE(Y)

* The total system cost that year (including taxes)
    SYSCOSTqI(Y)

* Investments made in each production technology that year
    PqCAPN(G)


* Total amount of CO2 (t), SO2 (t), and NOx (kg) emission each year Y in
* country C NOT IMPLEMENTED YEAT
  EMqCO2(C)
  EMqSO2(C)
  EMqNOX(C)

* Temporal parameter for storing values for each country (used in pc2cy.inc)
  TEMP(C);

SET

* Set of the technologies invested in (used in pc3y.inc)
  NEWP(G);

*..............................................................................

$ifi %DECOMPEFF%==yes $include '../../base/printinc/earningsdef.inc';


