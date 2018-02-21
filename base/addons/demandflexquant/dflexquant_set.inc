* File dflexquant_qheq.inc for the Balmorel model.
* For use with addon dflexquant
* Latest revision 20171023 (hr)

* Addon dflexquant: flexible price-dependent demand quantities

SET DEF                                              "Steps in elastic electricity demand";

SET DEF_D1(DEF)                                      "Downwards steps in elastic el. demand, relative data format";

SET DEF_U1(DEF)                                      "Upwards steps in elastic el. demand, relative data format";

SET DEF_D2(DEF)                                      "Downwards steps in elastic el. demand, absolute Money and MW-incremental data format";

SET DEF_U2(DEF)                                      "Upwards steps in elastic el. demand, absolute Money and MW-incremental data format";

SET DEF_D3(DEF)                                      "Downwards steps in elastic el. demand, absolute Money and fraction of nominal demand data format" ;

SET DEF_U3(DEF)                                      "Upwards steps in elastic el. demand, absolute Money and fraction of nominal demand data format";

SET DF_QP                                            "Quantity and price information for elastic demands";

PARAMETER DEF_STEPS(RRR,DEUSER,SSS,TTT,DF_QP,DEF)    "Elastic electricity demands";

SET DHF                                              "Steps in elastic heat demand";

SET DHF_D1(DHF)                                      "Downwards steps in elastic heat demand, relative data format";

SET DHF_U1(DHF)                                      "Upwards steps in elastic heat demand, relative data format";

SET DHF_D2(DHF)                                      "Downwards steps in elastic heat demand, absolute Money and MW-incremental data format";

SET DHF_U2(DHF)                                      "Upwards steps in elastic heat demand, absolute Money and MW-incremental data format";

SET DHF_D3(DHF)                                      "Downwards steps in elastic heat demand, absolute Money and fraction of nominal demand data format";

SET DHF_U3(DHF)                                      "Upwards steps in elastic heat demand, absolute Money and fraction of nominal demand data format";

PARAMETER DHF_STEPS(AAA,DHUSER,SSS,TTT,DF_QP,DHF)    "Elastic heat demands";

* For printing:

SET ODEFQUANTTYPE "Type of flexible demand quantity"
/
 UP    "Increased flexible consumption"
 DOWN  "Decreased flexible consumption"
 SUM   "Net flexible consumption increase"
/;

