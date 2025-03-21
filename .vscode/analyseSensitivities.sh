#!/bin/bash

read -p 'Overwrite? (y): ' overwrite

# Analyse results where investments in electrolysers and synfuelproducers are only allowed at the site 
# where the previous optimisation found the largest capacity

export PATH=/appl/gams/47.6.0:$PATH
source ~/miniconda3/bin/activate spatialstudy

if [ -z "${overwrite}" ] || [ "${overwrite}" = "y" ]; then
    overwrite_string="--overwrite"
fi

scenario_string="Scenario in ['N2_ZCEHX', 'N2_ZCEHX_fullyear', 'N2H1_ZCEHX', 'baseH1_ZCEHX', 'base_ZCEHX']"
analyse $overwrite_string costs --filters "${scenario_string}"
analyse $overwrite_string cap --filters "${scenario_string}"
mv analysis/plots/systemcosts.pdf analysis/plots/systemcosts_sens.pdf
mv analysis/plots/generation_capacity.pdf analysis/plots/generation_capacity_sens.pdf
mv analysis/plots/storage_capacity.pdf analysis/plots/storage_capacity_sens.pdf
