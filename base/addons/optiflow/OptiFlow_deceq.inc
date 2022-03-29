EQUATION QOBJW                                                 "Objective function value assuming weighted objectives values technique (U)";
EQUATION QOBJQ                                                 "Objective function value assuming parameterised quantities technique (U)";
EQUATION QOBJWQ                                                "Objective function value assuming weighted objectives values and parameterised quantities technique (U)";
EQUATION QNODEBALANCE(AAA,PROC,IFLOWIN,IFLOWOUT,S,T)         "Balance of input and output FLOW in interior PROC (U/h)"
EQUATION QSOURCENODEBALANCE(AAA,PROCSOURCE,FLOW,S,T)         "Balance at Source node (U/h)";
EQUATION QSINKNODEBALANCE(AAA,PROCSINK,FLOW,S,T)             "Balance at Sink node (U/h)";
EQUATION QBUFFERNODEBALANCE(AAA,PROCBUFFER,FLOW,S,T)         "Heat balance in district heating networks - NEJ generel, but includes Heat balance.. (U/h)";
EQUATION QFLOWTBALANCE(AAA,IPROCFROM,IPROCTO,FLOW,S,T);

EQUATION QSTORAGEBALANCE(AAA,PROC,FLOW,S,T)                   "Balance at TimeLinkstorage node";
EQUATION QSTORAGEBALANCE_Y(AAA,PROC,FLOW,S)                   "Balance of Annual Storage";
EQUATION QSTORAGEBALANCE_YT(AAA,PROC,FLOW,S,T);
EQUATION QSTOVOLTLIM_T(AAA,PROC,FLOW,S,T)                     "T Storage capacity (MWh/ton)"
EQUATION QSTOVOLTLIM(AAA,PROC,FLOW,S)                        "S storage capacity (MWh/ton)" ;
*Capacity constraint of storages yt is need

EQUATION QRAMPUPPROC(AAA,IPROCFROM,IPROCTO,FLOW,S,T)        "Ramping up between time slices for units"
EQUATION QRAMPDOWNPROC(AAA,IPROCFROM,IPROCTO,FLOW,S,T)     "Ramping down between time slices for units"


EQUATION QFLOWSHAREOUT2INUP(AAA,PROC,IFLOWIN,IFLOWOUT,S,T) "Maximum shares (of inFlow) of split FLOWs leaving PROC as outFlow (share)";
EQUATION QFLOWSHAREOUT2INLO(AAA,PROC,IFLOWIN,IFLOWOUT,S,T) "Minimum shares (of inFlow) of split FLOWs leaving PROC as outFlow (share)";
EQUATION QFLOWSHAREOUT2INFX(AAA,PROC,IFLOWIN,IFLOWOUT,S,T) "Fixed shares (of inFlow) of split FLOWs leaving PROC as outFlow (share)";
EQUATION QFLOWSHAREOUT2OUTLO(AAA,PROC,IFLOWIN,IFLOWOUT,IFLOWOUT2,S,T) "Lower value of relation (index 4 divided by 5) between two split FLOWs leaving PROC (share)";
EQUATION QFLOWSHAREOUT2OUTUP(AAA,PROC,IFLOWIN,IFLOWOUT,IFLOWOUT2,S,T) "Upper value of relation (index 4 divided by 5) between two split FLOWs leaving PROC (share)";
EQUATION QFLOWSHAREOUT2OUTFX(AAA,PROC,IFLOWIN,IFLOWOUT,IFLOWOUT2,S,T) "Fixed relation (index 4 divided by 5) between two split FLOWs leaving PROC (share)";
EQUATION QFLOWSHAREIN2INUP(AAA,IPROCFROM,IPROCFROM2,PROC,IFLOWIN,IFLOWIN2,S,T) "Maximum Relationship of two inFLOWS to a PROC (relation of U1/U2)";
EQUATION QFLOWSHAREIN2INLO(AAA,IPROCFROM,IPROCFROM2,PROC,IFLOWIN,IFLOWIN2,S,T) "Minimum Relationship of two inFLOWS to a PROC (relation of U1/U2)";
EQUATION QFLOWSHAREIN2INFX(AAA,IPROCFROM,IPROCFROM2,PROC,IFLOWIN,IFLOWIN2,S,T) "Fixed Relationship of two inFLOWS to a PROC (relation of U1/U2)";

EQUATION QTRANSITNODEBALANCE(AAATRANSIT,PROC,FLOW,S,T)       "Balance of input and output FLOW in Transit PROC (U/h)"

EQUATION QINDICQUANT(FLOWINDIC)                              "Total quantity of INDIC (U)"
EQUATION QINDICINDICMIN(FLOWINDIC)                             "Minimal annual quantity of INDIC (U)";
EQUATION QINDICINDICMAX(FLOWINDIC)                             "Maximal annual quantity (sum-of-years) of INDIC (U)";

EQUATION QEQFLOW_A(AAA,PROC,FLOW)  "Constraint of FLOW consumption equals to a value in an Area in a Source,Buffer or Sink Process"
EQUATION QEQFLOW_R(RRR,PROC,FLOW)  "Constraint of FLOW consumption equals to a value in a Region in a Source,Buffer or Sink Buffer Process"
EQUATION QEQFLOW_C(C,PROC,FLOW)   "Constraint of FLOW consumption equals to a value in a Country in a Source,Buffer or Sink Buffer Process"
EQUATION QMAXFLOW_A(AAA,PROC,FLOW)  "Constraint of FLOW consumption equals to a value in an Area in a Source,Buffer or Sink Process"
EQUATION QMAXFLOW_R(RRR,PROC,FLOW)  "Constraint of FLOW consumption equals to a value in a Region in a Source,Buffer or Sink Buffer Process"
EQUATION QMAXFLOW_C(C,PROC,FLOW)   "Constraint of FLOW consumption equals to a value in a Country in a Source,Buffer or Sink Buffer Process"
EQUATION QMINFLOW_A(AAA,PROC,FLOW)  "Constraint of FLOW consumption equals to a value in an Area in a Source,Buffer or Sink Process"
EQUATION QMINFLOW_R(RRR,PROC,FLOW)  "Constraint of FLOW consumption equals to a value in a Region in a Source,Buffer or Sink Buffer Process"
EQUATION QMINFLOW_C(C,PROC,FLOW)   "Constraint of FLOW consumption equals to a value in a Country in a Source,Buffer or Sink Buffer Process"


*-------------------------------------------------------------------------------
*----- Any declarations and definitions of equations for addon:
*-------------------------------------------------------------------------------

*$ifi %inv%==yes  EQUATION  QPROCKAPACCUMNET(Y,AAA,PROC)             'NOT FINISHED Accumulated new investments minus decommissioning of previous investments due to lifetime expiration available at beginning of next year (U/h)';
$ifi %inv%==yes  EQUATION  QPROCKAP_UP(AAA,IPROCFROM,IPROCTO,FLOW,S,T)           'Capacity constraint on ..... (U/h)';
$ifi %inv%==yes  EQUATION QPROCKAUP_SCALE1(AAA,PROC)   "Equation for modelling economy of scale of new investments" ;
$ifi %inv%==yes  EQUATION QPROCKAUP_SCALE2(AAA,PROC)   "Equation for modelling economy of scale of new investments"  ;
$ifi %inv%==yes  EQUATION QPROCKAP_DEC(AAA,IPROCFROM,IPROCTO,FLOW,S,T) "Equation for modelling of decomissioning plants";

