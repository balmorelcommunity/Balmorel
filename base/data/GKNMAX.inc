* File GKNMAX.INC

* File created :  2004.03.02  hh:01

*------------------------------------------------------------------------------

* PARAMETER GKNMAX holds the maximum capacities of those production technologies
* for which investments are allowed. If not any value is specified in this table
* the default value is inf.
* Units: MW.



GKNMAX(YYY,AAA,GGG)=  INF;
*GKNMAX(Y,IA,G)$(GKNMAX(Y,IA,G) LT 0)=  0;