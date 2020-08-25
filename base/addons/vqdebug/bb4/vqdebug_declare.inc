* Latest revision 20180418 (hr)

* Note initial: the below  "$ifi not declared  IPLUSMINUS" will not be needed in final version (but it will not harm either).
$ifi not declared  IPLUSMINUS  SET IPLUSMINUS "Violation of equation"  /IPLUS "Violation of equation upwards", IMINUS  "Violation of equation downwards"/;
* Note: When placed on the left hand side of the equation
* the sign to the IMINUS and IPLUS terms should be - and +, respectively.
* This way the sign and the name will be intuitively consistent in equation listings.

POSITIVE VARIABLE VQEEQ(Y,RRR,S,T,IPLUSMINUS)                "Feasibility in electricity balance QEEQ (IMINUS is short of el, IPLUS is surplus el) (MW)";
POSITIVE VARIABLE VQHEQ(Y,AAA,S,T,IPLUSMINUS)                "Feasibility in heat balance QHEQ (IMINUS is short of heat, IPLUS is surplus heat) (MW)";
POSITIVE VARIABLE VQESTOVOLT(Y,AAA,G,S,T,IPLUSMINUS)           "Feasibility in intra-seasonal electricity storage equation QESTOVOLT (MWh)";
POSITIVE VARIABLE VQESTOVOLTS(Y,AAA,G,S,T,IPLUSMINUS)          "Feasibility in inter-seasonal electricity storage equation QESTOVOLTS (MWh)";
POSITIVE VARIABLE VQHSTOVOLT(Y,AAA,G,S,T,IPLUSMINUS)           "Feasibility in intra-seasonal heat storage equation VQHSTOVOLT (MWh)";
POSITIVE VARIABLE VQHSTOVOLTS(Y,AAA,G,S,T,IPLUSMINUS)          "Feasibility in inter-seasonal heat storage equation VQHSTOVOLTS (MWh)";
POSITIVE VARIABLE VQHYRSSEQ(Y,AAA,S,IPLUSMINUS)              "Feasibility of QHYRSSEQ (MWh)";
POSITIVE VARIABLE VQHYMAXG(Y,AAA,S,T,IPLUSMINUS)             "Feasibility of QHYMAXG (MW)";
*POSITIVE VARIABLE VGE2LEVEL(Y,AAA,G,S,DAYTYPE)              "Average load of slowly regulating production (MW)";
POSITIVE VARIABLE VQGFEQ(Y,AAA,G,S,T,IPLUSMINUS)             "Feasibility in QGFEQ (MWh)";

*$ifi %BB4%==yes   POSITIVE VARIABLE VXKACCUMGROSS(Y,IRRRE,IRRRI) "RELEVANT? Accumulated new transmission investments this BB4, at end of (ULTimo) previous (i.e., start of current) year (MW)";

POSITIVE VARIABLE VQGKNACCUMNET(Y,AAA,G,IPLUSMINUS)          "Feasibility in electricity generation capacity accumulation (MW)";
POSITIVE VARIABLE VQGKNACCUMGROSS(Y,AAA,G,IPLUSMINUS)        "Feasibility in electricity generation capacity accumulation (MW)";
POSITIVE VARIABLE VQXKNACCUMNET(Y,IRRRE,IRRRI,IPLUSMINUS)    "Feasibility in electricity transmission capacity accumulation (MW)";
POSITIVE VARIABLE VQXKNACCUMGROSS(Y,IRRRE,IRRRI,IPLUSMINUS)  "Feasibility in electricity transmission capacity accumulation (MW)";

POSITIVE VARIABLE VQHYRSMINVOL(Y,AAA,S,IPLUSMINUS)           "Feasibility of QHYRSMINVOL (MWh)";
POSITIVE VARIABLE VQHYRSMAXVOL(Y,AAA,S,IPLUSMINUS)           "Feasibility of QHYRSMAXVOL (MWh)";

POSITIVE VARIABLE VQGKE_UP(Y,AAA,G,S,T,IPLUSMINUS)           "Feasibility in electricity generation limited by capacity (MW)";
POSITIVE VARIABLE VQGKH_UP(Y,AAA,G,S,T,IPLUSMINUS)           "Feasibility in heat generation limited by capacity (MW)";
POSITIVE VARIABLE VQXK_UP(Y,IRRRE,IRRRI,S,T,IPLUSMINUS)      "Feasibility in electricity transmission limited by capacity (MW)";

POSITIVE VARIABLE VQKFUEL(Y,CCCRRRAAA,FFF)                   "Feasibility in maximum installlable capacity (country, region and area)"
POSITIVE VARIABLE VQKTECHGROUP(Y,CCCRRRAAA,TECH_GROUP)       "Feasibility in maximum installlable capacity per technology group (country, region and area)"


POSITIVE VARIABLE VQGEQF(Y,CCCRRRAAA,FFF,IPLUSMINUS)         "Feasibility in exact fuel use by year (country, region and area) (IMINUS is short of fuel use, IPLUS is surplus fuel use"

POSITIVE VARIABLE VQUCMAXVGF(Y,AAA,G,S,T,IPLUSMINUS)         "Feasibility of QUCMAXVGF";
POSITIVE VARIABLE VQUCMINVGF(Y,AAA,G,S,T,IPLUSMINUS)         "Feasibility of QUCMINVGF";
POSITIVE VARIABLE VQUCUT(Y,AAA,G,S,T,IPLUSMINUS)         "Feasibility of VQUCUT";
POSITIVE VARIABLE VQUCDT(Y,AAA,G,S,T,IPLUSMINUS)         "Feasibility of VQUCDT";
POSITIVE VARIABLE VQUCSTARTQ(Y,AAA,G,S,T,IPLUSMINUS)         "Feasibility of QUCSTARTQ";
POSITIVE VARIABLE VQUCSTARTQ_STOLOAD_INTRA(Y,AAA,G,S,T,IPLUSMINUS)         "Feasibility of QUCSTARTQ_STOLOAD_INTRA";
POSITIVE VARIABLE VQUCSTARTQ_STOLOAD_INTER(Y,AAA,G,S,T,IPLUSMINUS)         "Feasibility of QUCSTARTQ_STOLOAD_INTER";
POSITIVE VARIABLE VQUCRAMPU(Y,AAA,G,S,T,IPLUSMINUS)          "Feasibility of QUCRAMPU";
POSITIVE VARIABLE VQUCRAMPD(Y,AAA,G,S,T,IPLUSMINUS)          "Feasibility of QUCRAMPD";
POSITIVE VARIABLE VQUCVUCON_EXISTING(Y,AAA,G,S,T,IPLUSMINUS) "Feasibility of VQUCVUCON_EXISTING";
POSITIVE VARIABLE VQUCVUCON_EXISTING_STOLOAD(Y,AAA,G,S,T,IPLUSMINUS) "Feasibility of VQUCVUCON_EXISTING_STOLOAD";

POSITIVE VARIABLE VQBMGH_T(Y,AAA,G,S,IPLUSMINUS) "Feasibility of QBMGH_T";

POSITIVE VARIABLE VHYDROGEN_QH2EQ(Y,CCCRRRAAA,S,T,IPLUSMINUS) "Feasibility in hydrogen balance QHYDROGEN_EQ and QHYDROGEN_EQ_AREA";
POSITIVE VARIABLE VQHYDROGEN_STOVOL(Y,AAA,G,S,T,IPLUSMINUS) "Feasibility in hydrogen balance QHYDROGEN_STOVOL";
POSITIVE VARIABLE VQBIOMETHANE_STOVOLTS(Y,S,T,IPLUSMINUS) "Feasibility in biomethane storage balance QBIOMETHANE_STOVOLTS";

