$ifi not %YEAR%==2030 $goto NOT2030
SET  Y(YYY) "Years in the simulation"                       
/                                                           
2030
/;                                                          
$label NOT2030
$ifi not %YEAR%==2040 $goto NOT2040
SET  Y(YYY) "Years in the simulation"                       
/                                                           
2040
/;                                                          
$label NOT2040
$ifi not %YEAR%==2050 $goto NOT2050
SET  Y(YYY) "Years in the simulation"                       
/                                                           
2050
/;                                                          
$label NOT2050
