*-------------------------------------------------------------------------------
* Price-dependant electricity exchange to places outside the simulated area
*-------------------------------------------------------------------------------

* Price (Money/MWh) for the price dependent electricity exchange.
* It will be assumed that prices should be positive.
* For import the prices should be increasing with ord(X3VSTEP0),
* for export the prices should be decreasing with ord(X3VSTEP0).

PARAMETERS
X3VPIM(YYY,RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)   "Price (Money/MWh) of price dependent imported electricity"
X3VPEX(YYY,RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)   "Price (Money/MWh) of price dependent exported electricity"

* Maximum quantity (MW) of price dependent electricity exchange per time segment:
X3VQIM(YYY,RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)   "Limit (MW) on price dependent electricity import"
X3VQEX(YYY,RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)   "Limit (MW) on price dependent electricity export"
X3VBAL(YYY,X3VPLACE)                         "Annual net-exports to third countries w. price profile MWh/year";

* Not in used
* Shadow price of balancing imports and exports according to annual values.
*X3VBALSP(YYY,X3VPLACE) "Get shadow price of the annual balance constraint"
