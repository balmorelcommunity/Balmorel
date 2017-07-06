* Addon for securing that Policy requrements are forfilled
* Policy requrements are given for each Policy and userdefined Policy Areas


* Policy requrements
* Construct the wished requrement by choosing a policy area 'POLAREA', a 'POLICY' and then state the data in the table.
* A Policy can be one of the following Policy Types. DO mind the units and specify technologies in POLTECH if requered
*   SHAREGROSS  implies Minimal share of electricity generation from specified technologies compared to gross electricity demand. NOTE: technologies have to be specified. Unit: Proportion
*   SHARENETTO  implies Minimal share of electricity generation from specified technologies compared to netto electricity demand. NOTE: technologies have to be specified. Unit: Proportion
*   MAXCO2      implies Maximal CO2 emission. NO technologies need to be defined. Unit: Ton CO2
*   MINPROD     implies Minimal electricity generation in from specified technologies in policy area. Unit: MWh
*   CAPTARGET   implies Minimal electricity generating capacity in policy area of specified technologies.  NOTE: technologies have to be specified. Unit: MW
*   ...         implies ...
*   ...         implies ...


TABLE POLREQ(YYY,POLAREA,POLICY)

       POLA1.POL1    POLA1.POL2
2010
2011
2012
2013
2014
2015
2016
2017
2018
2019
2020    0.5          0.7
2021
2022
2023
2024
2025
2030
2035
2040
2045
2050

;

PARAMETER IPOLREQ_Y(POLAREA,POLICY) '';
