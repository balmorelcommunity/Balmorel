* File  for addon testbb1234 for the Balmorel model
* Last revised 20180418 (hr)

$ifi not declared  IPLUSMINUS  SET IPLUSMINUS "Violation of equation"  /IPLUS "Violation of equation upwards", IMINUS  "Violation of equation downwards"/;

FREE     VARIABLE IBB1234_VOBJ                               "Objective function value (MMoney)";
POSITIVE VARIABLE IBB1234_VGE_T(Y,AAA,G,S,T)                 "Electricity generation (MW)";
POSITIVE VARIABLE IBB1234_VGH_T(Y,AAA,G,S,T)                 "Heat generation (MW)";
POSITIVE VARIABLE IBB1234_VGF_T(Y,AAA,G,S,T)                 "Fuel consumption rate (), existing units"
POSITIVE VARIABLE IBB1234_VX_T(Y,IRRRE,IRRRI,S,T)            "Electricity export from region IRRRE to IRRRI (MW)";
POSITIVE VARIABLE IBB1234_VGKN(Y,AAA,G)                      "New generation capacity (MW)";  !! se kommentarer til YYY  i bb4.sim Hans TODO
POSITIVE VARIABLE IBB1234_VXKN(Y,IRRRE,IRRRI)                "New electricity transmission capacity (MW)";
POSITIVE VARIABLE IBB1234_VDECOM(YYY,AAA,G)                  "Decommissioned capacity(MW). NOT IN USE PRESENTLY";
$ifi %dflexquant%==yes POSITIVE VARIABLE IBB1234_VDEF_T(Y,RRR,DEUSER,S,T,DEF)  "Flexible electricity demands (MW)";
$ifi %dflexquant%==yes POSITIVE VARIABLE IBB1234_VDHF_T(Y,AAA,DHUSER,S,T,DHF)  "Flexible heat demands (MW)";
POSITIVE VARIABLE IBB1234_VGHYPMS_T(Y,AAA,S,T)               "Contents of pumped hydro storage (MWh)";
POSITIVE VARIABLE IBB1234_VHYRS_S(Y,AAA,S)                   "Hydro energy equivalent at the start of the season (MWh)";
POSITIVE VARIABLE IBB1234_VESTOLOADT(Y,AAA,S,T)              "Intra-seasonal electricity storage loading (MW)";
POSITIVE VARIABLE IBB1234_VESTOLOADTS(Y,AAA,S,T)             "Inter-seasonal electricity storage loading (MW)";
POSITIVE VARIABLE IBB1234_VHSTOLOADT(Y,AAA,S,T)              "Intra-seasonal heat storage loading (MW)";
POSITIVE VARIABLE IBB1234_VHSTOLOADTS(Y,AAA,S,T)             "Inter-seasonal heat storage loading (MW)";
POSITIVE VARIABLE IBB1234_VESTOVOLT(Y,AAA,S,T)               "Electricity storage contents at beginning of time segment (MWh)";
POSITIVE VARIABLE IBB1234_VESTOVOLTS(Y,AAA,S,T)              "Electricity storage contents at beginning of time segment (MWh)";
POSITIVE VARIABLE IBB1234_VHSTOVOLT(Y,AAA,S,T)               "Heat storage contents at beginning of time segment (MWh)";
POSITIVE VARIABLE IBB1234_VHSTOVOLTS(Y,AAA,S,T)              "Heat storage contents at beginning of time segment (MWh)";


POSITIVE VARIABLE BB1234_VQEEQ(Y,RRR,S,T,IPLUSMINUS)         "Feasibility in electricity balance QEEQ (IMINUS is short of el, IPLUS is surplus of el) (MW)";
POSITIVE VARIABLE BB1234_VQHEQ(Y,AAA,S,T,IPLUSMINUS)         "Feasibility in heat balance QHEQ (IMINUS is short of heat, IPLUS is surplus of heat) (MW)";
POSITIVE VARIABLE IBB1234_VQESTOVOLT(Y,AAA,S,T,IPLUSMINUS)   "Feasibility in intra-seasonal electricity storage equation QESTOVOLT (MWh)";
POSITIVE VARIABLE IBB1234_VQESTOVOLTS(Y,AAA,S,T,IPLUSMINUS)  "Feasibility in inter-seasonal electricity storage equation QESTOVOLTS (MWh)";
POSITIVE VARIABLE IBB1234_VQHSTOVOLT(Y,AAA,S,T,IPLUSMINUS)   "Feasibility in intra-seasonal heat storage equation VQHSTOVOLT (MWh)";
POSITIVE VARIABLE IBB1234_VQHSTOVOLTS(Y,AAA,S,T,IPLUSMINUS)  "Feasibility in inter-seasonal heat storage equation VQHSTOVOLTS (MWh)";

POSITIVE VARIABLE BB1234_QEEQ(Y,RRR,S,T)                     "Electricity balance QEEQ  (MW)";
POSITIVE VARIABLE BB1234_QHEQ(Y,AAA,S,T)                     "Heat balance QHEQ (MW)";
* More eqns
