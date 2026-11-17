* File prt3-bb2.inc.
* For updating parameters holding results for simulations with endogeneous investments.
* Note: Actually this file is also presently used for simulations without endogeneous investments, cf. prt2-bb1.inc.

* File last time modified 27-09-2002 (rus), 15-05-2003 (hr), 08-08-2003 (hr), 20090203(hr), 20110508(hr), 20160407(hr)

* This file is part of the Balmorel model.


* -----------------------------------------------------------------------------
* Contents:

* This file contains routines for handling of intermediate information that may be usefull output.

* -----------------------------------------------------------------------------

* Skip the remaining part of the file if the model did not solve properly:
$ifi %BB1%==yes IF(BALBASE1.MODELSTAT GT 2, Put logfile; PUT "Skipped file prt3-bb2.INC" / / ;  ELSE
$ifi %BB2%==yes IF(BALBASE2.MODELSTAT GT 2, Put logfile; PUT "Skipped file prt3-bb2.INC" / / ;  ELSE
$ifi %BB3%==yes IF(BALBASE3.MODELSTAT GT 2, Put logfile; PUT "Skipped file prt3-bb2.INC" / / ;  ELSE



* Calculate and store results from current year:

* -----------------------------------------------------------------------------


* ELECTRICITY:


* Electricity demand (i.e. consumption) (MWh)

*   in each region each time period (MWh)
    EDqRT(IR,S,T) =  IHOURSINST(S,T) * (IDE_T_Y(IR,S,T)
       /*  + SUM(DEF_U1,VDEF_T.l(IR,S,T,DEF_U1) )  Now DEF is addon dflexquant - not implemented. Todo
         - SUM(DEF_D1,VDEF_T.l(IR,S,T,DEF_D1) )
         + SUM(DEF_U2,VDEF_T.l(IR,S,T,DEF_U2) )
         - SUM(DEF_D2,VDEF_T.l(IR,S,T,DEF_D2) )
         + SUM(DEF_U3,VDEF_T.l(IR,S,T,DEF_U3) )
         - SUM(DEF_D3,VDEF_T.l(IR,S,T,DEF_D3) ) */ );

*   in each region each season (MWh)
    EDqRS(IR,S) = SUM(T, EDqRT(IR,S,T));

*   in each region each year (MWh)
    EDqRY(IR) = SUM(S, EDqRS(IR,S));

*   in each country each time period (MWh)
    EDqCT(C,S,T) = SUM(IR$(CCCRRR(C,IR)),EDqRT(IR,S,T));

*   in each country each season (MWh)
    EDqCS(C,S) = SUM(IR$(CCCRRR(C,IR)),EDqRS(IR,S));

*   in each country each year (MWh)
    EDqCY(C) = SUM(IR$(CCCRRR(C,IR)),EDqRY(IR));


*..............................................................................

* Electricity generation of old technologies: (MWh)
* Including electricity consumption for heat pumps

*   in each area for each time period (MWh)
    EGOqAT(IA,G,S,T) = (IHOURSINST(S,T) * VGE_T.L(IA,G,S,T))$IAGK_Y(IA,G);

*   in each area for each season (MWh)
    EGOqAS(IA,G,S) = SUM(T, EGOqAT(IA,G,S,T));

*   in each area for each year (MWh)
    EGOqAY(IA,G) = SUM(S,EGOqAS(IA,G,S));

*   in each region for each time period (MWh)
    EGOqRT(IR,G,S,T) = SUM(IA$(RRRAAA(IR,IA)),EGOqAT(IA,G,S,T));

*   in each region for each season (MWh)
    EGOqRS(IR,G,S) = SUM(IA$(RRRAAA(IR,IA)),EGOqAS(IA,G,S));

*   in each region for each year (MWh)
    EGOqRY(IR,G) = SUM(IA$(RRRAAA(IR,IA)),EGOqAY(IA,G));

*   in each country for each time period (MWh)
    EGOqCT(C,G,S,T) = SUM(IR$(CCCRRR(C,IR)),EGOqRT(IR,G,S,T));

*   in each country for each season (MWh)
    EGOqCS(C,G,S) = SUM(IR$(CCCRRR(C,IR)),EGOqRS(IR,G,S));

*   in each country for each year (MWh)
    EGOqCY(C,G) = SUM(IR$(CCCRRR(C,IR)),EGOqRY(IR,G));

*..............................................................................

* Electricity generation of new technologies: (MWh)
* Including electricity consumption for heat pumps

*   in each area for each time period (MWh)
    EGNqAT(IA,G,S,T) = (IHOURSINST(S,T) * VGEN_T.L(IA,G,S,T))$IAGKN(IA,G);

*   in each area for each season (MWh)
    EGNqAS(IA,G,S) = SUM(T, EGNqAT(IA,G,S,T));

*   in each area for each year (MWh)
    EGNqAY(IA,G) = SUM(S, EGNqAS(IA,G,S));

*   in each region for each time period (MWh)
    EGNqRT(IR,G,S,T) = SUM(IA$(RRRAAA(IR,IA)),EGNqAT(IA,G,S,T));

*   in each region for each season (MWh)
    EGNqRS(IR,G,S) = SUM(IA$(RRRAAA(IR,IA)),EGNqAS(IA,G,S));

*   in each region for each year (MWh)
    EGNqRY(IR,G) = SUM(IA$(RRRAAA(IR,IA)),EGNqAY(IA,G));

*   in each country for each time period (MWh)
    EGNqCT(C,G,S,T) = SUM(IR$(CCCRRR(C,IR)),EGNqRT(IR,G,S,T));

*   in each country for each season (MWh)
    EGNqCS(C,G,S) = SUM(IR$(CCCRRR(C,IR)),EGNqRS(IR,G,S));

*   in each country for each year (MWh)
    EGNqCY(C,G) = SUM(IR$(CCCRRR(C,IR)),EGNqRY(IR,G));

*..............................................................................

* Electricity generation of all (old and new) technologies individually: (MWh)
* Including electricity consumption for heat pumps

*   in each area for each time period   (MWh)
    EGqAT(IA,G,S,T) = EGOqAT(IA,G,S,T) + EGNqAT(IA,G,S,T);

*   in each area for each season (MWh)
    EGqAS(IA,G,S) = SUM(T, EGqAT(IA,G,S,T));


*   in each area for each year (MWh)
    EGqAY(IA,G) = SUM(S, EGqAS(IA,G,S));


*   in each region for each time period (MWh)
    EGqRT(IR,G,S,T) = SUM(IA$(RRRAAA(IR,IA)),EGqAT(IA,G,S,T));

*   in each region for each season (MWh)
    EGqRS(IR,G,S) = SUM(IA$(RRRAAA(IR,IA)),EGqAS(IA,G,S));

*   in each region for each year (MWh)
    EGqRY(IR,G) = SUM(IA$(RRRAAA(IR,IA)),EGqAY(IA,G));


*   in each country for each time period (MWh)
    EGqCT(C,G,S,T) = SUM(IR$(CCCRRR(C,IR)),EGqRT(IR,G,S,T));

*   in each country for each season (MWh)
    EGqCS(C,G,S) = SUM(IR$(CCCRRR(C,IR)),EGqRS(IR,G,S));

*   in each country for each year (MWh)
    EGqCY(C,G) = SUM(IR$(CCCRRR(C,IR)),EGqRY(IR,G));

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

* Total electricity generation from old technologies (MWh):
* Exluding electricity consumption for heat pumps

*   in each area for each time period (MWh)
    EZGOqAT(IA,S,T) = SUM(IGNOTETOH, EGOqAT(IA,IGNOTETOH,S,T));

*   in each area for each season (MWh)
    EZGOqAS(IA,S) = SUM(IGNOTETOH, EGOqAS(IA,IGNOTETOH,S));

*   in each area for each year (MWh)
    EZGOqAY(IA) = SUM(IGNOTETOH, EGOqAY(IA,IGNOTETOH));

*   in each region for each time period (MWh)
    EZGOqRT(IR,S,T) = SUM(IA$(RRRAAA(IR,IA)),EZGOqAT(IA,S,T));

*   in each region for each season (MWh)
    EZGOqRS(IR,S) = SUM(IA$(RRRAAA(IR,IA)),EZGOqAS(IA,S));

*   in each region for each year (MWh)
    EZGOqRY(IR) = SUM(IA$(RRRAAA(IR,IA)),EZGOqAY(IA));

*   in each country for each time period (MWh)
    EZGOqCT(C,S,T) = SUM(IR$(CCCRRR(C,IR)),EZGOqRT(IR,S,T));

*   in each country for each season (MWh)
    EZGOqCS(C,S) = SUM(IR$(CCCRRR(C,IR)),EZGOqRS(IR,S));

*   in each country for each year (MWh)
    EZGOqCY(C) = SUM(IR$(CCCRRR(C,IR)),EZGOqRY(IR));

*   in all countries for each time period (MWh)
    EZGOqT(Y,S,T) = SUM(C, EZGOqCT(C,S,T));

*   in all countries for each season (MWh)
    EZGOqS(Y,S) = SUM(C, EZGOqCS(C,S));

*   in all countries for each year (MWh)
    EZGOqY(Y) = SUM(C, EZGOqCY(C));

*..............................................................................

* Total electricity generation from new technologies (MWh):
* Exluding electricity consumption for heat pumps

*   in each area for each time period (MWh)
    EZGNqAT(IA,S,T) = SUM(G, EGNqAT(IA,G,S,T));

*   in each area for each season (MWh)
    EZGNqAS(IA,S) = SUM(G, EGNqAS(IA,G,S));

*   in each area for each year  EXCLUDING HEAT PUMPS (MWh)
    EZGNqAY(IA) = SUM(IGNOTETOH, EGNqAY(IA,IGNOTETOH));


*   in each region for each time period (MWh)
    EZGNqRT(IR,S,T) = SUM(IA$(RRRAAA(IR,IA)),EZGNqAT(IA,S,T));

*   in each region for each season (MWh)
    EZGNqRS(IR,S) = SUM(IA$(RRRAAA(IR,IA)),EZGNqAS(IA,S));

*   in each region for each year (MWh)
    EZGNqRY(IR) = SUM(IA$(RRRAAA(IR,IA)),EZGNqAY(IA));

*   in each country for each time period (MWh)
    EZGNqCT(C,S,T) = SUM(IR$(CCCRRR(C,IR)),EZGNqRT(IR,S,T));

*   in each country for each season (MWh)
    EZGNqCS(C,S) = SUM(IR$(CCCRRR(C,IR)),EZGNqRS(IR,S));

*   in each country for each year (MWh)
    EZGNqCY(C) = SUM(IR$(CCCRRR(C,IR)),EZGNqRY(IR));

*   in all countries for each time period (MWh)
    EZGNqT(Y,S,T) = SUM(C, EZGNqCT(C,S,T));

*   in all countries for each season (MWh)
    EZGNqS(Y,S) = SUM(C, EZGNqCS(C,S));

*   in all countries for each year (MWh)
    EZGNqY(Y) = SUM(C, EZGNqCY(C));

*..............................................................................

* Total electricity generation from all (old and new) technologies (MWh):
* Exluding electricity consumption for heat pumps

*   in each area for each time period (MWh)
    EZGqAT(IA,S,T) = EZGOqAT(IA,S,T)+ EZGNqAT(IA,S,T);

*   in each area for each season (MWh)
    EZGqAS(IA,S) = SUM(G$IGNOTETOH(G), EGqAS(IA,G,S));

*   in each area for each year (MWh)
    EZGqAY(IA) = SUM(G$IGNOTETOH(G), EGqAY(IA,G));

*   in each region for each time period (MWh)
    EZGqRT(IR,S,T) = SUM(IA$(RRRAAA(IR,IA)),EZGqAT(IA,S,T));

*   in each region for each season (MWh)
    EZGqRS(IR,S) = SUM(IA$(RRRAAA(IR,IA)),EZGqAS(IA,S));

*   in each region for each year (MWh)
    EZGqRY(IR) = SUM(IA$(RRRAAA(IR,IA)),EZGqAY(IA));

*   in each country for each time period (MWh)
    EZGqCT(C,S,T) = SUM(IR$(CCCRRR(C,IR)),EZGqRT(IR,S,T));

*   in each country for each season (MWh)
    EZGqCS(C,S) = SUM(IR$(CCCRRR(C,IR)),EZGqRS(IR,S));

*   in each country for each year (MWh)
    EZGqCY(C) = SUM(IR$(CCCRRR(C,IR)),EZGqRY(IR));

*   in all countries for each time period (MWh)
    EZGqT(Y,S,T) = SUM(C, EZGqCT(C,S,T));

*   in all countries for each season (MWh)
    EZGqS(Y,S) = SUM(C, EZGqCS(C,S));

*   in all countries for each year (MWh)
    EZGqY(Y) = SUM(C, EZGqCY(C));

*..............................................................................

* Electricity import and export from region to third regions (countries): (MWh)
* A negative number indicate export and a positive number indicate export.

*   in each time period   (MW)
*   EX3qRT(IR,S,T) = IHOURSINST(S,T) * IX3FX_T_Y(IR,S,T) * (-1);

*   TEP
    EX3qRT(IR,S,T) = (
$ifi %X3V%==yes IHOURSINST(S,T) * SUM((X3VPLACE,X3VSTEP)$X3VX(IR,X3VPLACE),VX3VEX_T.l(IR,X3VPLACE,X3VSTEP,S,T) - VX3VIM_T.l(IR,X3VPLACE,X3VSTEP,S,T))+
     (IHOURSINST(S,T) * IX3FX_T_Y(IR,S,T)) )* (-1) ;

*   in each season
    EX3qRS(IR,S)   = SUM(T, EX3qRT(IR,S,T));

*   in each year
    EX3qRY(IR)     = SUM(S,EX3qRS(IR,S));

* Electricity import and export from country to third regions (countries): (MWh)
* A negative number indicate export and a positive number indicate export.

*   in each time period
    EX3qCT(C,S,T) =  SUM(IR$(CCCRRR(C,IR)),EX3qRT(IR,S,T));

*   in each season
    EX3qCS(C,S)   =  SUM(IR$(CCCRRR(C,IR)),EX3qRS(IR,S));

*   in each year
    EX3qCY(C)     =  SUM(IR$(CCCRRR(C,IR)),EX3qRY(IR));

*..............................................................................

* Electricity export from region to other regions: (MWh)

*   in each time period
    EX1qRT(IR,S,T) = IHOURSINST(S,T) * (SUM((IRI),VX_T.L(IR,IRI,S,T)) * (-1));

*   in each season
    EX1qRS(IR,S)   = SUM(T, EX1qRT(IR,S,T));

*   in each year
    EX1qRY(IR)     = SUM(S,EX1qRS(IR,S));

* Electricity export from country to regions in other countries: (MWh)

*   in each time period
    EX1qCT(C,S,T) = IHOURSINST(S,T) * (SUM((IR,IRI)$(CCCRRR(C,IR)
    AND (NOT CCCRRR(C,IRI))), VX_T.L(IR,IRI,S,T)) * (-1));

*   in each season
    EX1qCS(C,S)   = SUM(T, EX1qCT(C,S,T));

*   in each year
    EX1qCY(C)     = SUM(S,EX1qCS(C,S));

* Electricity import to region from other regions: (MWh)

*   in each time period
    EX2qRT(IR,S,T) = IHOURSINST(S,T) * (SUM((IRE),VX_T.L(IRE,IR,S,T)));

*   in each season
    EX2qRS(IR,S)   = SUM(T, EX2qRT(IR,S,T));

*   in each year
    EX2qRY(IR)     = SUM(S,EX2qRS(IR,S));

* Electricity import to country from regions in other countries: (MWh)

*   in each time period
    EX2qCT(C,S,T)  = IHOURSINST(S,T) * (SUM((IR,IRE)$(CCCRRR(C,IR)
    AND (NOT CCCRRR(C,IRE))), VX_T.L(IRE,IR,S,T)));

*   in each season
    EX2qCS(C,S)    = SUM(T, EX2qCT(C,S,T));

*   in each year
    EX2qCY(C)      = SUM(S,EX2qCS(C,S));

*..............................................................................

* Transmission loss of electricity (MWh):

*   in each region in each time period
    EXLqRT(IR,S,T) = IHOURSINST(S,T) * (SUM((IRE),VX_T.L(IRE,IR,S,T) *
    XLOSS(IRE,IR)) * (-1));

*   in each region in each season
    EXLqRS(IR,S) =  SUM(T, EXLqRT(IR,S,T));

*   in each region per year
    EXLqRY(IR) = SUM(S,EXLqRS(IR,S));


*   in each country in each time period
    EXLqCT(C,S,T) = SUM(IR$(CCCRRR(C,IR)),EXLqRT(IR,S,T));

*   in each country in each season
    EXLqCS(C,S) = SUM(IR$(CCCRRR(C,IR)),EXLqRS(IR,S));

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


    HDqAT(IA,S,T) = IHOURSINST(S,T) * ( IDH_T_Y(IA,S,T)
       /* + SUM(DHF_U1,VDHF_T.l(IA,S,T,DHF_U1) )  Now DEF is addon dflexquant - not implemented. Todo
         - SUM(DHF_D1,VDHF_T.l(IA,S,T,DHF_D1) )
         + SUM(DHF_U2,VDHF_T.l(IA,S,T,DHF_U2) )
         - SUM(DHF_D2,VDHF_T.l(IA,S,T,DHF_D2) )
         + SUM(DHF_U3,VDHF_T.l(IA,S,T,DHF_U3) )
         - SUM(DHF_D3,VDHF_T.l(IA,S,T,DHF_D3) ) */ );

*   in each area each season
    HDqAS(IA,S)  = SUM(T, HDqAT(IA,S,T));

*   in each area each year
    HDqAY(IA) = SUM(S, HDqAS(IA,S));


*   in each region each time period
    HDqRT(IR,S,T) = SUM(IA$(RRRAAA(IR,IA)),HDqAT(IA,S,T));

*   in each region each season
    HDqRS(IR,S)  = SUM(IA$(RRRAAA(IR,IA)),HDqAS(IA,S));

*   in each region each year
    HDqRY(IR) = SUM(IA$(RRRAAA(IR,IA)),HDqAY(IA));


*   in each country each time period
    HDqCT(C,S,T) = SUM(IR$(CCCRRR(C,IR)),HDqRT(IR,S,T));

*   in each country each season
    HDqCS(C,S) = SUM(IR$(CCCRRR(C,IR)),HDqRS(IR,S));

*   in each country each year
    HDqCY(C) = SUM(IR$(CCCRRR(C,IR)),HDqRY(IR));

*..............................................................................


* Heat generation from old technologies (MWh):
* (including heat storage)

*   in each area for each time period
    HGOqAT(IA,G,S,T) = (IHOURSINST(S,T) * VGH_T.L(IA,G,S,T))$IAGK_Y(IA,G);

*   in each area for each season
    HGOqAS(IA,G,S) = SUM(T, HGOqAT(IA,G,S,T));

*   in each area for each year
    HGOqAY(IA,G) = SUM(S,HGOqAS(IA,G,S));

*   in each region for each time period (MWh)
    HGOqRT(IR,G,S,T) = SUM(IA$(RRRAAA(IR,IA)),HGOqAT(IA,G,S,T));

*   in each region for each season (MWh)
    HGOqRS(IR,G,S) = SUM(IA$(RRRAAA(IR,IA)),HGOqAS(IA,G,S));

*   in each region for each year (MWh)
    HGOqRY(IR,G) = SUM(IA$(RRRAAA(IR,IA)),HGOqAY(IA,G));


*   in each country for each time period
    HGOqCT(C,G,S,T) = SUM(IA$(ICA(C,IA)), HGOqAT(IA,G,S,T));

*   in each country for each season
    HGOqCS(C,G,S) = SUM(IA$(ICA(C,IA)), HGOqAS(IA,G,S));

*   in each country for each year
    HGOqCY(C,G) = SUM(IA$(ICA(C,IA)), HGOqAY(IA,G));

*..............................................................................

* Heat generation from new technologies (MWh):
* (including heat storage)

*   in each area for each time period
    HGNqAT(IA,G,S,T) = (IHOURSINST(S,T) * VGHN_T.L(IA,G,S,T))$IAGKN(IA,G);

*   in each area for each season
    HGNqAS(IA,G,S) = SUM(T, HGNqAT(IA,G,S,T));

*   in each area for each year
    HGNqAY(IA,G) = SUM(S,HGNqAS(IA,G,S));


*   in each region for each time period (MWh)
    HGNqRT(IR,G,S,T) = SUM(IA$(RRRAAA(IR,IA)),HGNqAT(IA,G,S,T));

*   in each region for each season (MWh)
    HGNqRS(IR,G,S) = SUM(IA$(RRRAAA(IR,IA)),HGNqAS(IA,G,S));

*   in each region for each year (MWh)
    HGNqRY(IR,G) = SUM(IA$(RRRAAA(IR,IA)),HGNqAY(IA,G));


*   in each country for each time period
    HGNqCT(C,G,S,T) = SUM(IA$(ICA(C,IA)), HGNqAT(IA,G,S,T));

*   in each country for each season
    HGNqCS(C,G,S) = SUM(IA$(ICA(C,IA)), HGNqAS(IA,G,S));

*   in each country for each year
    HGNqCY(C,G) = SUM(IA$(ICA(C,IA)), HGNqAY(IA,G));

*..............................................................................

* Heat generation from all (old and new) technologies (MWh):
* (including heat storage)

*   in each area for each time period
*    HGqAT(IA,G,S,T)=(IHOURSINST(S,T)*(VGH_T.L(IA,G,S,T)+VGHN_T.L(IA,G,S,T)));
    HGqAT(IA,G,S,T) = HGOqAT(IA,G,S,T) + HGNqAT(IA,G,S,T);
*   in each area for each season
    HGqAS(IA,G,S) = SUM(T, HGqAT(IA,G,S,T));

*   in each area for each year
    HGqAY(IA,G) = SUM(S,HGqAS(IA,G,S));


*   in each region for each time period (MWh)
    HGqRT(IR,G,S,T) = SUM(IA$(RRRAAA(IR,IA)),HGqAT(IA,G,S,T));

*   in each region for each season (MWh)
    HGqRS(IR,G,S) = SUM(IA$(RRRAAA(IR,IA)),HGqAS(IA,G,S));

*   in each region for each year (MWh)
    HGqRY(IR,G) = SUM(IA$(RRRAAA(IR,IA)),HGqAY(IA,G));


*   in each country for each time period
    HGqCT(C,G,S,T) = SUM(IA$(ICA(C,IA)), HGqAT(IA,G,S,T));

*   in each country for each season
    HGqCS(C,G,S) = SUM(IA$(ICA(C,IA)), HGqAS(IA,G,S));

*   in each country for each year
    HGqCY(C,G) = SUM(IA$(ICA(C,IA)), HGqAY(IA,G));

*..............................................................................

* Total heat generation, excluding heat storage,
* from all (old and new) technologies (MWh):

*   in each area for each time period
    HZGqAT(IA,S,T) = SUM(G, HGqAT(IA,G,S,T))-SUM(IGHSTOALL,HGqAT(IA,IGHSTOALL,S,T));

*   in each area for each season
    HZGqAS(IA,S) = SUM(T, HZGqAT(IA,S,T));

*   in each area for each year
    HZGqAY(IA) = SUM(S, HZGqAS(IA,S));

*   in each region for each time period (MWh)
    HZGqRT(IR,S,T) = SUM(IA$(RRRAAA(IR,IA)),HZGqAT(IA,S,T));

*   in each region for each season (MWh)
    HZGqRS(IR,S) = SUM(IA$(RRRAAA(IR,IA)),HZGqAS(IA,S));

*   in each region for each year (MWh)
    HZGqRY(IR) = SUM(IA$(RRRAAA(IR,IA)),HZGqAY(IA));

*   in each country for each time period
    HZGqCT(C,S,T) = SUM(IA$(ICA(C,IA)), HZGqAT(IA,S,T));

*   in each country for each season
    HZGqCS(C,S) = SUM(IA$(ICA(C,IA)), HZGqAS(IA,S));

*   in each country for each year
    HZGqCY(C) = SUM(IA$(ICA(C,IA)), HZGqAY(IA));

*   in all countries for each time period
    HZGqT(Y,S,T) = SUM(C, HZGqCT(C,S,T));

*   in all countries for each season
    HZGqS(Y,S) = SUM(C, HZGqCS(C,S));

*   in all countries for each year
    HZGqY(Y) = SUM(C, HZGqCY(C));

*..............................................................................

* Total heat generation, excluding heat storage,
* from old technologies (MWh):

*   in each area for each time period
    HZGOqAT(IA,S,T) = SUM(G, HGOqAT(IA,G,S,T))-SUM(IGHSTOALL,HGOqAT(IA,IGHSTOALL,S,T)) ;

*   in each area for each season
    HZGOqAS(IA,S) = SUM(T, HZGOqAT(IA,S,T));

*   in each area for each year
    HZGOqAY(IA) = SUM(S, HZGOqAS(IA,S));

*   in each region for each time period (MWh)
    HZGOqRT(IR,S,T) = SUM(IA$(RRRAAA(IR,IA)),HZGOqAT(IA,S,T));

*   in each region for each season (MWh)
    HZGOqRS(IR,S) = SUM(IA$(RRRAAA(IR,IA)),HZGOqAS(IA,S));

*   in each region for each year (MWh)
    HZGOqRY(IR) = SUM(IA$(RRRAAA(IR,IA)),HZGOqAY(IA));

*   in each country for each time period
    HZGOqCT(C,S,T) = SUM(IA$(ICA(C,IA)), HZGOqAT(IA,S,T));

*   in each country for each season
    HZGOqCS(C,S) = SUM(IA$(ICA(C,IA)), HZGOqAS(IA,S));

*   in each country for each year
    HZGOqCY(C) = SUM(IA$(ICA(C,IA)), HZGOqAY(IA));

*   in all countries for each time period
    HZGOqT(Y,S,T) = SUM(C, HZGOqCT(C,S,T));

*   in all countries for each season
    HZGOqS(Y,S) = SUM(C, HZGOqCS(C,S));

*   in all countries for each year
    HZGOqY(Y) = SUM(C, HZGOqCY(C));

*..............................................................................

* Total heat generation, excluding heat storage,
* from new technologies (MWh):

*   in each area for each time period
    HZGNqAT(IA,S,T) = SUM(G, HGNqAT(IA,G,S,T))-SUM(IGHSTOALL,HGNqAT(IA,IGHSTOALL,S,T));

*   in each area for each season
    HZGNqAS(IA,S) = SUM(T, HZGNqAT(IA,S,T));

*   in each area for each year
    HZGNqAY(IA) = SUM(S, HZGNqAS(IA,S));

*   in each region for each time period (MWh)
    HZGNqRT(IR,S,T) = SUM(IA$(RRRAAA(IR,IA)),HZGNqAT(IA,S,T));

*   in each region for each season (MWh)
    HZGNqRS(IR,S) = SUM(IA$(RRRAAA(IR,IA)),HZGNqAS(IA,S));

*   in each region for each year (MWh)
    HZGNqRY(IR) = SUM(IA$(RRRAAA(IR,IA)),HZGNqAY(IA));

*   in each country for each time period
    HZGNqCT(C,S,T) = SUM(IA$(ICA(C,IA)), HZGNqAT(IA,S,T));

*   in each country for each season
    HZGNqCS(C,S) = SUM(IA$(ICA(C,IA)), HZGNqAS(IA,S));

*   in each country for each year
    HZGNqCY(C) = SUM(IA$(ICA(C,IA)), HZGNqAY(IA));

*   in all countries for each time period
    HZGNqT(Y,S,T) = SUM(C, HZGNqCT(C,S,T));

*   in all countries for each season
    HZGNqS(Y,S) = SUM(C, HZGNqCS(C,S));

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
    EHFqAT(IA,G,S,T)$(IAGK_Y(IA,G) or IAGKN(IA,G)) = IHOURSINST(S,T) * (VGF_T.L(IA,G,S,T) + VGFN_T.L(IA,G,S,T));

*   in each area for each season
    EHFqAS(IA,G,S)   = SUM(T, EHFqAT(IA,G,S,T));

*   in each area for each year
    EHFqAY(IA,G)     = SUM(S,EHFqAS(IA,G,S));

*   in each region per time period
    EHFqRT(IR,G,S,T) = SUM(IA$(RRRAAA(IR,IA)),EHFqAT(IA,G,S,T));

*   in each region for each season
    EHFqRS(IR,G,S)   = SUM(IA$(RRRAAA(IR,IA)),EHFqAS(IA,G,S));

*   in each region for each year
    EHFqRY(IR,G)     = SUM(IA$(RRRAAA(IR,IA)),EHFqAY(IA,G));

*   in each country per time period
    EHFqCT(C,G,S,T) = SUM(IR$(CCCRRR(C,IR)),EHFqRT(IR,G,S,T));

*   in each country for each season
    EHFqCS(C,G,S)   = SUM(IR$(CCCRRR(C,IR)),EHFqRS(IR,G,S));

*   in each country for each year
    EHFqCY(C,G)     = SUM(IR$(CCCRRR(C,IR)),EHFqRY(IR,G));

* Fuel emissions in each region per time period
EHM1qRT(IR,S,T)=SUM(IA$RRRAAA(IR,IA),(SUM(FFF,FDATA(FFF,'FDCO2')*
   (SUM(G$(IAGK_Y(IA,G) AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * VGF_T.L(IA,G,S,T))
    +SUM(G$(IAGKN(IA,G)  AND (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))), IOF3P6 * VGFN_T.L(IA,G,S,T))
))));


*..............................................................................
* Earnings by plant (Mio OMONEY)
$ifi %DECOMPEFF%==yes $include '../../base/printinc/earnings.inc';

* Hans midletidgt ud   $include '../../base/output/printout/printinc/econ.inc';



*..............................................................................

$ONTEXT
Note: The calculation of EHM1qCY(C), EHM2qCY(C) and EHM3qCY(C) moved to the respective print files.
      Calculation of  EHM4qCY(C) and EHM5qCY(C) presently irrelevant.
* Emissions:

*   CO2 emissions in each country for each year
    EHM1qCY(C)  =
      SUM((G,S,T), IHOURSINST(S,T) * (IM_CO2(G)/1000) * 3.6 *
      SUM(IA$ICA(C,IA),(VGE_T.L(IA,G,S,T) + VGEN_T.L(IA,G,S,T)
      + GDATA(G,'GDCV')*(VGH_T.L(IA,G,S,T) + VGHN_T.L(IA,G,S,T))) /
      (GDATA(G,'GDFE')* (1-GEFFDERATE(IA,G)))));

*   SO2 emissions in each country for each year
    EHM2qCY(C)  =
      SUM((G,S,T), IHOURSINST(S,T) * (IM_SO2(G)/1000) * 3.6 *
      SUM(IA$ICA(C,IA),(VGE_T.L(IA,G,S,T) + VGEN_T.L(IA,G,S,T)
      + GDATA(G,'GDCV')*(VGH_T.L(IA,G,S,T) + VGHN_T.L(IA,G,S,T))) /
      (GDATA(G,'GDFE')* (1-GEFFDERATE(IA,G))) ));

*   NOx emissions in each country for each year
    EHM3qCY(C)  =
      SUM((G,S,T), IHOURSINST(S,T) * (GDATA(G,'GDNOX')/1000000)*3.6*
      SUM(IA$ICA(C,IA),(VGE_T.L(IA,G,S,T) + VGEN_T.L(IA,G,S,T)
      + GDATA(G,'GDCV')*(VGH_T.L(IA,G,S,T) + VGHN_T.L(IA,G,S,T))) /
      (GDATA(G,'GDFE')* (1-GEFFDERATE(IA,G))) ));
/*
*   CH4 emissions in each country for each year
    EHM4qCY(C)  =
      SUM((G,S,T), IHOURSINST(S,T) * (GDATA(G,'GDCH4')/1000000)*3.6*
      SUM(IA$ICA(C,IA),(VGE_T.L(IA,G,S,T) + VGEN_T.L(IA,G,S,T)
      + GDATA(G,'GDCV')*(VGH_T.L(IA,G,S,T) + VGHN_T.L(IA,G,S,T))) /
      (GDATA(G,'GDFE')* (1-GEFFDERATE(IA,G))) ));

*   N2O emissions in each country for each year
    EHM5qCY(C)  =
      SUM((G,S,T), IHOURSINST(S,T) * (IM_N2O(G)/1000) * 3.6 *
      SUM(IA$ICA(C,IA),(VGE_T.L(IA,G,S,T) + VGEN_T.L(IA,G,S,T)
      + GDATA(G,'GDCV')*(VGH_T.L(IA,G,S,T) + VGHN_T.L(IA,G,S,T))) /
      (GDATA(G,'GDFE')* (1-GEFFDERATE(IA,G))) ));

*/
$OFFTEXT
*..............................................................................


* Skipped to here if the model did not solve properly:
$ifi %BB1%==yes );
$ifi %BB2%==yes );
$ifi %BB3%==yes );
