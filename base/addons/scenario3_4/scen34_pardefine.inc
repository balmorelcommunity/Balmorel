*** Manipulation to inputdata for Flex4RES scenario 3 and 4
** Scenario 3 only affects large consumers wheras scenario 4 affects also small consumers



********* SCENARIO 3 or 4 ***********
$ifi not %SCENARIO3OR4%==YES $goto label_scenario3OR4_DATAMANIPULATION_END

*$ifi  %SCENARIO4%==YES    GR_PRICE_USER(C,DEUSER,'GRDDCY') = 50;

$LABEL label_scenario3OR4_DATAMANIPULATION_END


