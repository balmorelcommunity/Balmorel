* Location of internal set delarations and definitions used in addons  (for any addon where declarations and definitions are in the same file)


$ifi not %BB4%==yes $goto endoffile


$ifi %GRIDTARIFFS%==yes  $include   "../../base/addons/GridTariffs/GridTariffs_isetdecdef_st.inc";
$ifi %DEMANDRESPONSE%==yes      $include        "../../base/addons/demandresponse/bb4/dr_isetdecdef_st.inc";


$label endoffile
