* File FDATA.inc

* This file is part of the Balmorel model, version 2.11 Alpha (April 2004).

*------------------------------------------------------------------------------

* PARAMETER FDATA contains information about emission characteristics of fuels.

* In addition it contains a name (FDACRONYM) for the fuel, note that this must be as an ACRONYM previously.
* Presnetly it also contains a numerical code identication of the individual fuels,
* however, this may become invalid, so you shold use only the FDACRONYM.


TABLE FDATA(FFF,FDATASET)   'Fuel specific values'

              FDACRONYM     FDNB    FDCO2   FDSO2   FDN2O
* Units                             kg/GJ   kg/GJ   kg/GJ
NUCLEAR       NUCLEAR       1       0       0       0
NATGAS        NATGAS        2       56.9    0       0.001
COAL          COAL          3       95      0.714   0.003
LIGNITE       LIGNITE       4       101     1.428   0.003
FUELOIL       FUELOIL       5       78      0.446   0.002
LIGHTOIL      LIGHTOIL      6       74      0.023   0.002
ORIMULSION    ORIMULSION    7       80      1.337   0.002
SHALE         SHALE         8       106     1.428   0.003
PEAT          PEAT          9       107     0.24    0.003
MUNIWASTE     MUNIWASTE     10      19      0.156   0.004
STRAW         STRAW         11      0       0.025   0.004
WOOD          WOOD          12      0       0.025   0.004
WOODWASTE     WOODWASTE     13      0       0.025   0.004
WIND          WIND          14      0       0       0
WATER         WATER         15      0       0       0
SUN           SUN           16      0       0       0
ELECTRIC      ELECTRIC      17      0       0       0
WATERRES      WATERRES              0       0       0
HEAT          HEAT
HYDROGEN      HYDROGEN
DUMMY         DUMMY         18
;
