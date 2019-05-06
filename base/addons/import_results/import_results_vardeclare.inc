

$ifi not %HYRSBB123%==contprice    $goto label_no_hydro_contprice
POSITIVE VARIABLE   VHYRS_SDELTAMWHPOS(Y,AAA,S)    'Positive delta between hydro storage content in previous runs and the one in this run';
POSITIVE VARIABLE   VHYRS_SDELTAMWHNEG(Y,AAA,S)    'Negative delta between hydro storage content in previous runs and the one in this run';
$label  label_no_hydro_contprice


$ifi not %ADDELECSTORCONT%==yes    $goto label_no_intraseasonal_electricity_storage_content
POSITIVE VARIABLE   VESTOVOLTSDELTAMWHPOS(Y,AAA,G,S,T)   'Positive delta between electricity interseasonal storage content in previous runs and the one in this run';
POSITIVE VARIABLE   VESTOVOLTSDELTAMWHNEG(Y,AAA,G,S,T)   'Negative delta between electricity interseasonal storage content in previous runs and the one in this run';
$label  label_no_intraseasonal_electricity_storage_content

$ifi not %ADDHEATSTORCONT%==yes    $goto label_no_intraseasonal_heat_storage_content
POSITIVE VARIABLE   VHSTOVOLTSDELTAMWHPOS(Y,AAA,G,S,T)   'Positive delta between heat interseasonal storage content in previous runs and the one in this run';
POSITIVE VARIABLE   VHSTOVOLTSDELTAMWHNEG(Y,AAA,G,S,T)   'Negative delta between heat interseasonal storage content in previous runs and the one in this run';
$label label_no_intraseasonal_heat_storage_content

