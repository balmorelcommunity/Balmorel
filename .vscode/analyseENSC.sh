#!/bin/bash
read -p 'Include base scenarios? (true/false): ' include_base_scenarios
read -p 'Overwrite? (true/false): ' overwrite

# Analyse results where investments in electrolysers and synfuelproducers are only allowed at the site 
# where the previous optimisation found the largest capacity

export PATH=/appl/gams/47.6.0:$PATH
source ~/miniconda3/bin/activate spatialstudy

if [ -z "${overwrite}" ] || [ "${overwrite}" = "y" ]; then
    overwrite_string="--overwrite"
fi

# include_base_scenarios=true
if $include_base_scenarios; then
    analyse $overwrite_string cap --filters   "Scenario in ['N2_ZCEHX_ES', 'N2_ZCEHX',  'N10_ZCEHX_ESNC', 'N10_ZCEHX', 'N30_ZCEHX_ESNC', 'N30_ZCEHX', 'N50_ZCEHX_ESNC', 'N50_ZCEHX', 'N70_ZCEHX_ESNC', 'N70_ZCEHX']"
    analyse $overwrite_string costs --filters "Scenario in ['N2_ZCEHX_ES', 'N2_ZCEHX',  'N10_ZCEHX_ESNC', 'N10_ZCEHX', 'N30_ZCEHX_ESNC', 'N30_ZCEHX', 'N50_ZCEHX_ESNC', 'N50_ZCEHX', 'N70_ZCEHX_ESNC', 'N70_ZCEHX']"
else
    analyse $overwrite_string cap --filters "Scenario in ['N2_ZCEHX_ES', 'N10_ZCEHX_ESNC', 'N30_ZCEHX_ESNC', 'N50_ZCEHX_ESNC', 'N70_ZCEHX_ESNC']"
    analyse $overwrite_string costs --filters "Scenario in ['N2_ZCEHX_ES', 'N10_ZCEHX_ESNC', 'N30_ZCEHX_ESNC', 'N50_ZCEHX_ESNC', 'N70_ZCEHX_ESNC']"
fi