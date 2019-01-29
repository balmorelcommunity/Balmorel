*** Manipulation to inputdata for Flex4RES scenario 3 and 4
** Scenario 3 only affects large consumers wheras scenario 4 affects also small consumers



********* SCENARIO 3 or 4 ***********
$ifi not %SCENARIO3OR4%==YES $goto label_scenario3OR4_DATAMANIPULATION_END
*** 2 Grid tariffs
** 2.1 Set grid tariff levels to zero
* for Balmorel technologies:
GR_PRICE_TECH(CCC,GRDATASET) = 0;

* for power intensive industry
GR_PRICE_USER(CCC,'PII',GRDATASET) = 0;
$ifi  %SCENARIO4%==YES    GR_PRICE_USER(CCC,DEUSER,GRDATASET) = 0;

** 2.2 Congestion pricing

* Set the grid tariff accroding to desired level
GR_PRICE_TECH(C,'GRDDCTOU') = 50;
GR_PRICE_USER(C,'PII','GRDDCTOU') = 50;
$ifi  %SCENARIO4%==YES    GR_PRICE_USER(C,DEUSER,'GRDDCTOU') = 50;       

$LABEL label_scenario3OR4_DATAMANIPULATION_END


