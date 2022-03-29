*Individual users addon

* Include the following equations in model Balbase4

$ifi not %GROUP_DEMAND_SHIFT%==yes $goto NO_GROUP_DEMAND_SHIFT
$ifi %import_results%==yes $ifi %ADDGROUP_DEMAND_SHIFT%==yes $goto NO_GROUP_DEMAND_SHIFT
QINDIVUSERS_DH
QINDIVUSERS_GROUP_MIN
QINDIVUSERS_GROUP_MAX
$label NO_GROUP_DEMAND_SHIFT
