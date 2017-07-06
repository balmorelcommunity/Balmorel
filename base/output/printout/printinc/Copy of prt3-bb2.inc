* File prt3-bb2.inc.
* For updating parameters holding results for simulations with endogeneous investments.

* File last time modified 27-09-2002 (rus), 15-05-2003 (hr), 08-08-2003 (hr)

* This file is part of the Balmorel model, version 2.11 Alpha (July 2005)


* -----------------------------------------------------------------------------
* Contents:

* This file contains routines for handling of intermediate information that may
* be usefull output.

* -----------------------------------------------------------------------------

* Calculate and store results from current year:

* -----------------------------------------------------------------------------


* ELECTRICITY:


* Electricity demand (i.e. consumption) (MWh)

*   in each region each time period (MWh)
    EDqRT(IR,IS3,T) =  IHOURSINST(IS3,T) * (IDE_T_Y(IR,IS3,T)
         + SUM(DEF_U1,VDEF_T.l(IR,IS3,T,DEF_U1) )
         - SUM(DEF_D1,VDEF_T.l(IR,IS3,T,DEF_D1) ) );

*   in each region each season (MWh)
    EDqRS(IR,IS3) = SUM(T, EDqRT(IR,IS3,T));

*   in each region each year (MWh)
    EDqRY(IR) = SUM(IS3, EDqRS(IR,IS3));

*   in each country each time period (MWh)
    EDqCT(C,IS3,T) = SUM(IR$(CCCRRR(C,IR)),EDqRT(IR,IS3,T));

*   in each country each season (MWh)
    EDqCS(C,IS3) = SUM(IR$(CCCRRR(C,IR)),EDqRS(IR,IS3));

*   in each country each year (MWh)
    EDqCY(C) = SUM(IR$(CCCRRR(C,IR)),EDqRY(IR));

*..............................................................................

* Electricity generation of all (old and new) technologies individually: (MWh)
* Including electricity consumption for heat pumps

*   in each area for each time period   (MWh)
    EGqAT(IA,G,IS3,T)=(IHOURSINST(IS3,T)*(VGE_T.L(IA,G,IS3,T)+VGEN_T.L(IA,G,IS3,T)));
DISPLAY 'her er 1. del', EGqAT;

*   in each area for each season (MWh)
    EGqAS(IA,G,IS3) = SUM(T, EGqAT(IA,G,IS3,T));
DISPLAY 'her er 2. del', EGqAS;

*   in each area for each year (MWh)
    EGqAY(IA,G) = SUM(IS3, EGqAS(IA,G,IS3));
DISPLAY 'her er 3. del', EGqAY;

*   in each region for each time period (MWh)
    EGqRT(IR,G,IS3,T) = SUM(IA$(RRRAAA(IR,IA)),EGqAT(IA,G,IS3,T));

*   in each region for each season (MWh)
    EGqRS(IR,G,IS3) = SUM(IA$(RRRAAA(IR,IA)),EGqAS(IA,G,IS3));

*   in each region for each year (MWh)
    EGqRY(IR,G) = SUM(IA$(RRRAAA(IR,IA)),EGqAY(IA,G));


*   in each country for each time period (MWh)
    EGqCT(C,G,IS3,T) = SUM(IR$(CCCRRR(C,IR)),EGqRT(IR,G,IS3,T));

*   in each country for each season (MWh)
    EGqCS(C,G,IS3) = SUM(IR$(CCCRRR(C,IR)),EGqRS(IR,G,IS3));

*   in each country for each year (MWh)
    EGqCY(C,G) = SUM(IR$(CCCRRR(C,IR)),EGqRY(IR,G));

*..............................................................................

* Electricity generation of old technologies: (MWh)
* Including electricity consumption for heat pumps

*   in each area for each time period (MWh)
    EGOqAT(IA,G,IS3,T) = (IHOURSINST(IS3,T) * VGE_T.L(IA,G,IS3,T));

*   in each area for each season (MWh)
    EGOqAS(IA,G,IS3) = SUM(T, EGOqAT(IA,G,IS3,T));

*   in each area for each year (MWh)
    EGOqAY(IA,G) = SUM(IS3,EGOqAS(IA,G,IS3));


*   in each region for each time period (MWh)
    EGOqRT(IR,G,IS3,T) = SUM(IA$(RRRAAA(IR,IA)),EGOqAT(IA,G,IS3,T));

*   in each region for each season (MWh)
    EGOqRS(IR,G,IS3) = SUM(IA$(RRRAAA(IR,IA)),EGOqAS(IA,G,IS3));

*   in each region for each year (MWh)
    EGOqRY(IR,G) = SUM(IA$(RRRAAA(IR,IA)),EGOqAY(IA,G));


*   in each country for each time period (MWh)
    EGOqCT(C,G,IS3,T) = SUM(IR$(CCCRRR(C,IR)),EGOqRT(IR,G,IS3,T));

*   in each country for each season (MWh)
    EGOqCS(C,G,IS3) = SUM(IR$(CCCRRR(C,IR)),EGOqRS(IR,G,IS3));

*   in each country for each year (MWh)
    EGOqCY(C,G) = SUM(IR$(CCCRRR(C,IR)),EGOqRY(IR,G));

*..............................................................................

* Electricity generation of new technologies: (MWh)
* Including electricity consumption for heat pumps

*   in each area for each time period (MWh)
    EGNqAT(IA,G,IS3,T) = (IHOURSINST(IS3,T) * VGEN_T.L(IA,G,IS3,T));

*   in each area for each season (MWh)
    EGNqAS(IA,G,IS3) = SUM(T, EGNqAT(IA,G,IS3,T));

*   in each area for each year (MWh)
    EGNqAY(IA,G) = SUM(IS3, EGNqAS(IA,G,IS3));


*   in each region for each time period (MWh)
    EGNqRT(IR,G,IS3,T) = SUM(IA$(RRRAAA(IR,IA)),EGNqAT(IA,G,IS3,T));

*   in each region for each season (MWh)
    EGNqRS(IR,G,IS3) = SUM(IA$(RRRAAA(IR,IA)),EGNqAS(IA,G,IS3));

*   in each region for each year (MWh)
    EGNqRY(IR,G) = SUM(IA$(RRRAAA(IR,IA)),EGNqAY(IA,G));

*   in each country for each time period (MWh)
    EGNqCT(C,G,IS3,T) = SUM(IR$(CCCRRR(C,IR)),EGNqRT(IR,G,IS3,T));

*   in each country for each season (MWh)
    EGNqCS(C,G,IS3) = SUM(IR$(CCCRRR(C,IR)),EGNqRS(IR,G,IS3));

*   in each country for each year (MWh)
    EGNqCY(C,G) = SUM(IR$(CCCRRR(C,IR)),EGNqRY(IR,G));

*..............................................................................

* Total electricity consumption for all (old and new) heat pumps (MWh):

*   in each country for each year
    EZG13qCY(C) = SUM(G$IGETOH(G), EGqCY(C,G));

* Total electricity consumption for old heat pumps (MWh):

*   in each country for each year
    EZGO13qCY(C) = SUM(IGETOH, EGOqCY(C,IGETOH));

* Total electricity consumption for new heat pumps (MWh):

*   in each country for each year
    EZGN13qCY(C) = SUM(IGETOH, EGNqCY(C,IGETOH));
*..............................................................................

* Total electricity generation from all (old and new) technologies (MWh):
* Exluding electricity consumption for heat pumps

*   in each area for each time period (MWh)
    EZGqAT(IA,IS3,T) = SUM(G$IGNOTETOH(G), EGqAT(IA,G,IS3,T));

*   in each area for each season (MWh)
    EZGqAS(IA,IS3) = SUM(G$IGNOTETOH(G), EGqAS(IA,G,IS3));

*   in each area for each year (MWh)
    EZGqAY(IA) = SUM(G$IGNOTETOH(G), EGqAY(IA,G));
DISPLAY 'her er 4. del', EZGqAY;

*   in each region for each time period (MWh)
    EZGqRT(IR,IS3,T) = SUM(IA$(RRRAAA(IR,IA)),EZGqAT(IA,IS3,T));

*   in each region for each season (MWh)
    EZGqRS(IR,IS3) = SUM(IA$(RRRAAA(IR,IA)),EZGqAS(IA,IS3));

*   in each region for each year (MWh)
    EZGqRY(IR) = SUM(IA$(RRRAAA(IR,IA)),EZGqAY(IA));
DISPLAY 'her er 5. del', EZGqRY;

*   in each country for each time period (MWh)
    EZGqCT(C,IS3,T) = SUM(IR$(CCCRRR(C,IR)),EZGqRT(IR,IS3,T));

*   in each country for each season (MWh)
    EZGqCS(C,IS3) = SUM(IR$(CCCRRR(C,IR)),EZGqRS(IR,IS3));

*   in each country for each year (MWh)
    EZGqCY(C) = SUM(IR$(CCCRRR(C,IR)),EZGqRY(IR));
DISPLAY 'her er 6. del', EZGqCY;

*   in all countries for each time period (MWh)
    EZGqT(Y,IS3,T) = SUM(C, EZGqCT(C,IS3,T));

*   in all countries for each season (MWh)
    EZGqS(Y,IS3) = SUM(C, EZGqCS(C,IS3));

*   in all countries for each year (MWh)
    EZGqY(Y) = SUM(C, EZGqCY(C));

*..............................................................................

* Total electricity generation from old technologies (MWh):
* Exluding electricity consumption for heat pumps

*   in each area for each time period (MWh)
    EZGOqAT(IA,IS3,T) = SUM(IGNOTETOH, EGOqAT(IA,IGNOTETOH,IS3,T));

*   in each area for each season (MWh)
    EZGOqAS(IA,IS3) = SUM(IGNOTETOH, EGOqAS(IA,IGNOTETOH,IS3));

*   in each area for each year (MWh)
    EZGOqAY(IA) = SUM(IGNOTETOH, EGOqAY(IA,IGNOTETOH));

*   in each region for each time period (MWh)
    EZGOqRT(IR,IS3,T) = SUM(IA$(RRRAAA(IR,IA)),EZGOqAT(IA,IS3,T));

*   in each region for each season (MWh)
    EZGOqRS(IR,IS3) = SUM(IA$(RRRAAA(IR,IA)),EZGOqAS(IA,IS3));

*   in each region for each year (MWh)
    EZGOqRY(IR) = SUM(IA$(RRRAAA(IR,IA)),EZGOqAY(IA));


*   in each country for each time period (MWh)
    EZGOqCT(C,IS3,T) = SUM(IR$(CCCRRR(C,IR)),EZGOqRT(IR,IS3,T));

*   in each country for each season (MWh)
    EZGOqCS(C,IS3) = SUM(IR$(CCCRRR(C,IR)),EZGOqRS(IR,IS3));

*   in each country for each year (MWh)
    EZGOqCY(C) = SUM(IR$(CCCRRR(C,IR)),EZGOqRY(IR));


*   in all countries for each time period (MWh)
    EZGOqT(Y,IS3,T) = SUM(C, EZGOqCT(C,IS3,T));

*   in all countries for each season (MWh)
    EZGOqS(Y,IS3) = SUM(C, EZGOqCS(C,IS3));

*   in all countries for each year (MWh)
    EZGOqY(Y) = SUM(C, EZGOqCY(C));

*..............................................................................

* Total electricity generation from new technologies (MWh):
* Exluding electricity consumption for heat pumps

*   in each area for each time period (MWh)
    EZGNqAT(IA,IS3,T) = SUM(G, EGNqAT(IA,G,IS3,T));

*   in each area for each season (MWh)
    EZGNqAS(IA,IS3) = SUM(G, EGNqAS(IA,G,IS3));

*   in each area for each year  EXCLUDING HEAT PUMPS (MWh)
    EZGNqAY(IA) = SUM(IGNOTETOH, EGNqAY(IA,IGNOTETOH));


*   in each region for each time period (MWh)
    EZGNqRT(IR,IS3,T) = SUM(IA$(RRRAAA(IR,IA)),EZGNqAT(IA,IS3,T));

*   in each region for each season (MWh)
    EZGNqRS(IR,IS3) = SUM(IA$(RRRAAA(IR,IA)),EZGNqAS(IA,IS3));

*   in each region for each year (MWh)
    EZGNqRY(IR) = SUM(IA$(RRRAAA(IR,IA)),EZGNqAY(IA));


*   in each country for each time period (MWh)
    EZGNqCT(C,IS3,T) = SUM(IR$(CCCRRR(C,IR)),EZGNqRT(IR,IS3,T));

*   in each country for each season (MWh)
    EZGNqCS(C,IS3) = SUM(IR$(CCCRRR(C,IR)),EZGNqRS(IR,IS3));

*   in each country for each year (MWh)
    EZGNqCY(C) = SUM(IR$(CCCRRR(C,IR)),EZGNqRY(IR));


*   in all countries for each time period (MWh)
    EZGNqT(Y,IS3,T) = SUM(C, EZGNqCT(C,IS3,T));

*   in all countries for each season (MWh)
    EZGNqS(Y,IS3) = SUM(C, EZGNqCS(C,IS3));

*   in all countries for each year (MWh)
    EZGNqY(Y) = SUM(C, EZGNqCY(C));

*..............................................................................

* Electricity import and export from region to third regions (countries): (MWh)
* A negative number indicate export and a positive number indicate export.

*   in each time period   (MW)
    EX3qRT(IR,IS3,T) = IHOURSINST(IS3,T) * IX3FX_T_Y(IR,IS3,T) * (-1);

*   in each season
    EX3qRS(IR,IS3)   = SUM(T, EX3qRT(IR,IS3,T));

*   in each year
    EX3qRY(IR)     = SUM(IS3,EX3qRS(IR,IS3));


* Electricity import and export from country to third regions (countries): (MWh)
* A negative number indicate export and a positive number indicate export.

*   in each time period
    EX3qCT(C,IS3,T) =  SUM(IR$(CCCRRR(C,IR)),EX3qRT(IR,IS3,T));

*   in each season
    EX3qCS(C,IS3)   =  SUM(IR$(CCCRRR(C,IR)),EX3qRS(IR,IS3));

*   in each year
    EX3qCY(C)     =  SUM(IR$(CCCRRR(C,IR)),EX3qRY(IR));

*..............................................................................


* Electricity export from region to other regions: (MWh)

*   in each time period
    EX1qRT(IR,IS3,T) = IHOURSINST(IS3,T) * (SUM((IRI),VX_T.L(IR,IRI,IS3,T)) * (-1));

*   in each season
    EX1qRS(IR,IS3)   = SUM(T, EX1qRT(IR,IS3,T));

*   in each year
    EX1qRY(IR)     = SUM(IS3,EX1qRS(IR,IS3));


* Electricity export from country to regions in other countries: (MWh)

*   in each time period
    EX1qCT(C,IS3,T) = IHOURSINST(IS3,T) * (SUM((IR,IRI)$(CCCRRR(C,IR)
    AND (NOT CCCRRR(C,IRI))), VX_T.L(IR,IRI,IS3,T)) * (-1));

*   in each season
    EX1qCS(C,IS3)   = SUM(T, EX1qCT(C,IS3,T));

*   in each year
    EX1qCY(C)     = SUM(IS3,EX1qCS(C,IS3));


* Electricity import to region from other regions: (MWh)

*   in each time period
    EX2qRT(IR,IS3,T) = IHOURSINST(IS3,T) * (SUM((IRE),VX_T.L(IRE,IR,IS3,T)));

*   in each season
    EX2qRS(IR,IS3)   = SUM(T, EX2qRT(IR,IS3,T));

*   in each year
    EX2qRY(IR)     = SUM(IS3,EX2qRS(IR,IS3));


* Electricity import to country from regions in other countries: (MWh)

*   in each time period
    EX2qCT(C,IS3,T)  = IHOURSINST(IS3,T) * (SUM((IR,IRE)$(CCCRRR(C,IR)
    AND (NOT CCCRRR(C,IRE))), VX_T.L(IRE,IR,IS3,T)));

*   in each season
    EX2qCS(C,IS3)    = SUM(T, EX2qCT(C,IS3,T));

*   in each year
    EX2qCY(C)      = SUM(IS3,EX2qCS(C,IS3));

*..............................................................................

* Transmission loss of electricity (MWh):

*   in each region in each time period
    EXLqRT(IR,IS3,T) = IHOURSINST(IS3,T) * (SUM((IRE),VX_T.L(IRE,IR,IS3,T) *
    XLOSS(IRE,IR)) * (-1));

*   in each region in each season
    EXLqRS(IR,IS3) =  SUM(T, EXLqRT(IR,IS3,T));

*   in each region per year
    EXLqRY(IR) = SUM(IS3,EXLqRS(IR,IS3));


*   in each country in each time period
    EXLqCT(C,IS3,T) = SUM(IR$(CCCRRR(C,IR)),EXLqRT(IR,IS3,T));

*   in each country in each season
    EXLqCS(C,IS3) = SUM(IR$(CCCRRR(C,IR)),EXLqRS(IR,IS3));

*   in each country per year
    EXLqCY(C) = SUM(IR$(CCCRRR(C,IR)),EXLqRY(IR));

*..............................................................................

* Distribution loss of electricity (MWh):

*   in each region per year
    ELqRY(IR) =  ((EDqRY(IR) / (1-DISLOSS_E(IR))) - EDqRY(IR)) * (-1) ;

*   in each country per year
    ELqCY(C) =  SUM(IR$(CCCRRR(C,IR)),ELqRY(IR));

*..............................................................................


* HEAT

* Heat demand (i.e., consumption) (MWh)

*   in each area each time period

    HDqAT(IAURBH,IS3,T)  =  IHOURSINST(IS3,T) * (IDH_T_Y(IAURBH,IS3,T)
        + SUM(DHF_U,VDHF_T.l(IAURBH,IS3,T,DHF_U) )
        - SUM(DHF_D,VDHF_T.l(IAURBH,IS3,T,DHF_D) ) );

    HDqAT(IARURH,IS3,T) = IHOURSINST(IS3,T) * ( IDH_T_Y(IARURH,IS3,T)
         + SUM(DHF_U,VDHF_T.l(IARURH,IS3,T,DHF_U) )
         - SUM(DHF_D,VDHF_T.l(IARURH,IS3,T,DHF_D) ) );

*   in each area each season
    HDqAS(IA,IS3)  = SUM(T, HDqAT(IA,IS3,T));

*   in each area each year
    HDqAY(IA) = SUM(IS3, HDqAS(IA,IS3));


*   in each region each time period
    HDqRT(IR,IS3,T) = SUM(IA$(RRRAAA(IR,IA)),HDqAT(IA,IS3,T));

*   in each region each season
    HDqRS(IR,IS3)  = SUM(IA$(RRRAAA(IR,IA)),HDqAS(IA,IS3));

*   in each region each year
    HDqRY(IR) = SUM(IA$(RRRAAA(IR,IA)),HDqAY(IA));


*   in each country each time period
    HDqCT(C,IS3,T) = SUM(IR$(CCCRRR(C,IR)),HDqRT(IR,IS3,T));

*   in each country each season
    HDqCS(C,IS3) = SUM(IR$(CCCRRR(C,IR)),HDqRS(IR,IS3));

*   in each country each year
    HDqCY(C) = SUM(IR$(CCCRRR(C,IR)),HDqRY(IR));

*..............................................................................

* Heat generation from all (old and new) technologies (MWh):
* (including heat storage)

*   in each area for each time period
    HGqAT(IA,G,IS3,T)=(IHOURSINST(IS3,T)*(VGH_T.L(IA,G,IS3,T)+VGHN_T.L(IA,G,IS3,T)));

*   in each area for each season
    HGqAS(IA,G,IS3) = SUM(T, HGqAT(IA,G,IS3,T));

*   in each area for each year
    HGqAY(IA,G) = SUM(IS3,HGqAS(IA,G,IS3));


*   in each region for each time period (MWh)
    HGqRT(IR,G,IS3,T) = SUM(IA$(RRRAAA(IR,IA)),HGqAT(IA,G,IS3,T));

*   in each region for each season (MWh)
    HGqRS(IR,G,IS3) = SUM(IA$(RRRAAA(IR,IA)),HGqAS(IA,G,IS3));

*   in each region for each year (MWh)
    HGqRY(IR,G) = SUM(IA$(RRRAAA(IR,IA)),HGqAY(IA,G));


*   in each country for each time period
    HGqCT(C,G,IS3,T) = SUM(IA$(ICA(C,IA)), HGqAT(IA,G,IS3,T));

*   in each country for each season
    HGqCS(C,G,IS3) = SUM(IA$(ICA(C,IA)), HGqAS(IA,G,IS3));

*   in each country for each year
    HGqCY(C,G) = SUM(IA$(ICA(C,IA)), HGqAY(IA,G));

*..............................................................................

* Heat generation from old technologies (MWh):
* (including heat storage)

*   in each area for each time period
    HGOqAT(IA,G,IS3,T) = (IHOURSINST(IS3,T) * VGH_T.L(IA,G,IS3,T));

*   in each area for each season
    HGOqAS(IA,G,IS3) = SUM(T, HGOqAT(IA,G,IS3,T));

*   in each area for each year
    HGOqAY(IA,G) = SUM(IS3,HGOqAS(IA,G,IS3));


*   in each region for each time period (MWh)
    HGOqRT(IR,G,IS3,T) = SUM(IA$(RRRAAA(IR,IA)),HGOqAT(IA,G,IS3,T));

*   in each region for each season (MWh)
    HGOqRS(IR,G,IS3) = SUM(IA$(RRRAAA(IR,IA)),HGOqAS(IA,G,IS3));

*   in each region for each year (MWh)
    HGOqRY(IR,G) = SUM(IA$(RRRAAA(IR,IA)),HGOqAY(IA,G));


*   in each country for each time period
    HGOqCT(C,G,IS3,T) = SUM(IA$(ICA(C,IA)), HGOqAT(IA,G,IS3,T));

*   in each country for each season
    HGOqCS(C,G,IS3) = SUM(IA$(ICA(C,IA)), HGOqAS(IA,G,IS3));

*   in each country for each year
    HGOqCY(C,G) = SUM(IA$(ICA(C,IA)), HGOqAY(IA,G));

*..............................................................................

* Heat generation from new technologies (MWh):
* (including heat storage)

*   in each area for each time period
    HGNqAT(IA,G,IS3,T) = (IHOURSINST(IS3,T) * VGHN_T.L(IA,G,IS3,T));

*   in each area for each season
    HGNqAS(IA,G,IS3) = SUM(T, HGNqAT(IA,G,IS3,T));

*   in each area for each year
    HGNqAY(IA,G) = SUM(IS3,HGNqAS(IA,G,IS3));


*   in each region for each time period (MWh)
    HGNqRT(IR,G,IS3,T) = SUM(IA$(RRRAAA(IR,IA)),HGNqAT(IA,G,IS3,T));

*   in each region for each season (MWh)
    HGNqRS(IR,G,IS3) = SUM(IA$(RRRAAA(IR,IA)),HGNqAS(IA,G,IS3));

*   in each region for each year (MWh)
    HGNqRY(IR,G) = SUM(IA$(RRRAAA(IR,IA)),HGNqAY(IA,G));


*   in each country for each time period
    HGNqCT(C,G,IS3,T) = SUM(IA$(ICA(C,IA)), HGNqAT(IA,G,IS3,T));

*   in each country for each season
    HGNqCS(C,G,IS3) = SUM(IA$(ICA(C,IA)), HGNqAS(IA,G,IS3));

*   in each country for each year
    HGNqCY(C,G) = SUM(IA$(ICA(C,IA)), HGNqAY(IA,G));

*..............................................................................

* Total heat generation, excluding heat storage,
* from all (old and new) technologies (MWh):

*   in each area for each time period
    HZGqAT(IA,IS3,T) = SUM(G, HGqAT(IA,G,IS3,T))-SUM(IGHSTO,HGqAT(IA,IGHSTO,IS3,T));

*   in each area for each season
    HZGqAS(IA,IS3) = SUM(T, HZGqAT(IA,IS3,T));

*   in each area for each year
    HZGqAY(IA) = SUM(IS3, HZGqAS(IA,IS3));


*   in each region for each time period (MWh)
    HZGqRT(IR,IS3,T) = SUM(IA$(RRRAAA(IR,IA)),HZGqAT(IA,IS3,T));

*   in each region for each season (MWh)
    HZGqRS(IR,IS3) = SUM(IA$(RRRAAA(IR,IA)),HZGqAS(IA,IS3));

*   in each region for each year (MWh)
    HZGqRY(IR) = SUM(IA$(RRRAAA(IR,IA)),HZGqAY(IA));


*   in each country for each time period
    HZGqCT(C,IS3,T) = SUM(IA$(ICA(C,IA)), HZGqAT(IA,IS3,T));

*   in each country for each season
    HZGqCS(C,IS3) = SUM(IA$(ICA(C,IA)), HZGqAS(IA,IS3));

*   in each country for each year
    HZGqCY(C) = SUM(IA$(ICA(C,IA)), HZGqAY(IA));


*   in all countries for each time period
    HZGqT(Y,IS3,T) = SUM(C, HZGqCT(C,IS3,T));

*   in all countries for each season
    HZGqS(Y,IS3) = SUM(C, HZGqCS(C,IS3));

*   in all countries for each year
    HZGqY(Y) = SUM(C, HZGqCY(C));

*..............................................................................

* Total heat generation, excluding heat storage,
* from old technologies (MWh):

*   in each area for each time period
    HZGOqAT(IA,IS3,T) = SUM(G, HGOqAT(IA,G,IS3,T))-SUM(IGHSTO,HGOqAT(IA,IGHSTO,IS3,T)) ;

*   in each area for each season
    HZGOqAS(IA,IS3) = SUM(T, HZGOqAT(IA,IS3,T));

*   in each area for each year
    HZGOqAY(IA) = SUM(IS3, HZGOqAS(IA,IS3));

*   in each region for each time period (MWh)
    HZGOqRT(IR,IS3,T) = SUM(IA$(RRRAAA(IR,IA)),HZGOqAT(IA,IS3,T));

*   in each region for each season (MWh)
    HZGOqRS(IR,IS3) = SUM(IA$(RRRAAA(IR,IA)),HZGOqAS(IA,IS3));

*   in each region for each year (MWh)
    HZGOqRY(IR) = SUM(IA$(RRRAAA(IR,IA)),HZGOqAY(IA));


*   in each country for each time period
    HZGOqCT(C,IS3,T) = SUM(IA$(ICA(C,IA)), HZGOqAT(IA,IS3,T));

*   in each country for each season
    HZGOqCS(C,IS3) = SUM(IA$(ICA(C,IA)), HZGOqAS(IA,IS3));

*   in each country for each year
    HZGOqCY(C) = SUM(IA$(ICA(C,IA)), HZGOqAY(IA));


*   in all countries for each time period
    HZGOqT(Y,IS3,T) = SUM(C, HZGOqCT(C,IS3,T));

*   in all countries for each season
    HZGOqS(Y,IS3) = SUM(C, HZGOqCS(C,IS3));

*   in all countries for each year
    HZGOqY(Y) = SUM(C, HZGOqCY(C));

*..............................................................................

* Total heat generation, excluding heat storage,
* from new technologies (MWh):

*   in each area for each time period
    HZGNqAT(IA,IS3,T) = SUM(G, HGNqAT(IA,G,IS3,T))-SUM(IGHSTO,HGNqAT(IA,IGHSTO,IS3,T));

*   in each area for each season
    HZGNqAS(IA,IS3) = SUM(T, HZGNqAT(IA,IS3,T));

*   in each area for each year
    HZGNqAY(IA) = SUM(IS3, HZGNqAS(IA,IS3));


*   in each region for each time period (MWh)
    HZGNqRT(IR,IS3,T) = SUM(IA$(RRRAAA(IR,IA)),HZGNqAT(IA,IS3,T));

*   in each region for each season (MWh)
    HZGNqRS(IR,IS3) = SUM(IA$(RRRAAA(IR,IA)),HZGNqAS(IA,IS3));

*   in each region for each year (MWh)
    HZGNqRY(IR) = SUM(IA$(RRRAAA(IR,IA)),HZGNqAY(IA));


*   in each country for each time period
    HZGNqCT(C,IS3,T) = SUM(IA$(ICA(C,IA)), HZGNqAT(IA,IS3,T));

*   in each country for each season
    HZGNqCS(C,IS3) = SUM(IA$(ICA(C,IA)), HZGNqAS(IA,IS3));

*   in each country for each year
    HZGNqCY(C) = SUM(IA$(ICA(C,IA)), HZGNqAY(IA));


*   in all countries for each time period
    HZGNqT(Y,IS3,T) = SUM(C, HZGNqCT(C,IS3,T));

*   in all countries for each season
    HZGNqS(Y,IS3) = SUM(C, HZGNqCS(C,IS3));

*   in all countries for each year
    HZGNqY(Y) = SUM(C, HZGNqCY(C));

*..............................................................................

* Distribution loss of heat (MWh):

*   in each area per year
    HLqAY(IA) =  ((HDqAY(IA) / (1-DISLOSS_H(IA))) - HDqAY(IA)) * (-1);

*   in each region per year
    HLqRY(IR) =  SUM(IA$(RRRAAA(IR,IA)),HLqAY(IA));

*   in each country per year
    HLqCY(C) = SUM(IR$(CCCRRR(C,IR)),HLqRY(IR));

*..............................................................................

* Fuel consumption (MWh):

*   in each area per time period
    EHFqAT(IA,G,IS3,T) = (IHOURSINST(IS3,T) * ((VGE_T.L(IA,G,IS3,T) + VGEN_T.L(IA,G,IS3,T) +
                      GDATA(G,'GDCV')*(VGH_T.L(IA,G,IS3,T) + VGHN_T.L(IA,G,IS3,T))) /
                      (GDATA(G,'GDFE')* GEFFDERATE(G,IA))));

*   in each area for each season
    EHFqAS(IA,G,IS3)   = SUM(T, EHFqAT(IA,G,IS3,T));

*   in each area for each year
    EHFqAY(IA,G)     = SUM(IS3,EHFqAS(IA,G,IS3));


*   in each region per time period
    EHFqRT(IR,G,IS3,T) = SUM(IA$(RRRAAA(IR,IA)),EHFqAT(IA,G,IS3,T));

*   in each region for each season
    EHFqRS(IR,G,IS3)   = SUM(IA$(RRRAAA(IR,IA)),EHFqAS(IA,G,IS3));

*   in each region for each year
    EHFqRY(IR,G)     = SUM(IA$(RRRAAA(IR,IA)),EHFqAY(IA,G));


*   in each country per time period
    EHFqCT(C,G,IS3,T) = SUM(IR$(CCCRRR(C,IR)),EHFqRT(IR,G,IS3,T));

*   in each country for each season
    EHFqCS(C,G,IS3)   = SUM(IR$(CCCRRR(C,IR)),EHFqRS(IR,G,IS3));

*   in each country for each year
    EHFqCY(C,G)     = SUM(IR$(CCCRRR(C,IR)),EHFqRY(IR,G));

*..............................................................................

* Emissions:

*   CO2 emissions in each country for each year
    EHM1qCY(C)  =
      SUM((G,IS3,T), IHOURSINST(IS3,T) * (IM_CO2(G)/1000) * 3.6 *
      SUM(IA$ICA(C,IA),(VGE_T.L(IA,G,IS3,T) + VGEN_T.L(IA,G,IS3,T)
      + GDATA(G,'GDCV')*(VGH_T.L(IA,G,IS3,T) + VGHN_T.L(IA,G,IS3,T))) /
      (GDATA(G,'GDFE')* GEFFDERATE(G,IA))));

*   SO2 emissions in each country for each year
    EHM2qCY(C)  =
      SUM((G,IS3,T), IHOURSINST(IS3,T) * (IM_SO2(G)/1000) * 3.6 *
      SUM(IA$ICA(C,IA),(VGE_T.L(IA,G,IS3,T) + VGEN_T.L(IA,G,IS3,T)
      + GDATA(G,'GDCV')*(VGH_T.L(IA,G,IS3,T) + VGHN_T.L(IA,G,IS3,T))) /
      (GDATA(G,'GDFE')* GEFFDERATE(G,IA)) ));

*   NOx emissions in each country for each year
    EHM3qCY(C)  =
      SUM((G,IS3,T), IHOURSINST(IS3,T) * (GDATA(G,'GDNOX')/1000000)*3.6*
      SUM(IA$ICA(C,IA),(VGE_T.L(IA,G,IS3,T) + VGEN_T.L(IA,G,IS3,T)
      + GDATA(G,'GDCV')*(VGH_T.L(IA,G,IS3,T) + VGHN_T.L(IA,G,IS3,T))) /
      (GDATA(G,'GDFE')* GEFFDERATE(G,IA)) ));

*   CH4 emissions in each country for each year
    EHM4qCY(C)  =
      SUM((G,IS3,T), IHOURSINST(IS3,T) * (GDATA(G,'GDCH4')/1000000)*3.6*
      SUM(IA$ICA(C,IA),(VGE_T.L(IA,G,IS3,T) + VGEN_T.L(IA,G,IS3,T)
      + GDATA(G,'GDCV')*(VGH_T.L(IA,G,IS3,T) + VGHN_T.L(IA,G,IS3,T))) /
      (GDATA(G,'GDFE')* GEFFDERATE(G,IA)) ));

*   N2O emissions in each country for each year
    EHM5qCY(C)  =
      SUM((G,IS3,T), IHOURSINST(IS3,T) * (IM_N2O(G)/1000) * 3.6 *
      SUM(IA$ICA(C,IA),(VGE_T.L(IA,G,IS3,T) + VGEN_T.L(IA,G,IS3,T)
      + GDATA(G,'GDCV')*(VGH_T.L(IA,G,IS3,T) + VGHN_T.L(IA,G,IS3,T))) /
      (GDATA(G,'GDFE')* GEFFDERATE(G,IA)) ));


*..............................................................................