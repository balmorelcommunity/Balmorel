#!/bin/bash

read -p 'Overwrite? (y): ' overwrite

# Analyse results where investments in electrolysers and synfuelproducers are only allowed at the site 
# where the previous optimisation found the largest capacity

export PATH=/appl/gams/47.6.0:$PATH
source ~/miniconda3/bin/activate spatialstudy

if [ -z "${overwrite}" ] || [ "${overwrite}" = "y" ]; then
    overwrite_string="--overwrite"
fi

# Uniformly clustered
analyse $overwrite_string map Electricity N2_ZCEHX    
analyse $overwrite_string map Electricity N10_ZCEHX
analyse $overwrite_string map Electricity N30_ZCEHX
analyse $overwrite_string map Electricity N50_ZCEHX
analyse $overwrite_string map Electricity N70_ZCEHX
analyse $overwrite_string map Electricity base_ZCEHX

analyse $overwrite_string map Hydrogen N2_ZCEHX  
analyse $overwrite_string map Hydrogen N10_ZCEHX
analyse $overwrite_string map Hydrogen N30_ZCEHX
analyse $overwrite_string map Hydrogen N50_ZCEHX
analyse $overwrite_string map Hydrogen N70_ZCEHX
analyse $overwrite_string map Hydrogen base_ZCEHX

# Hierarchically clustered  
analyse $overwrite_string map Electricity N10M2_ZCEHX
analyse $overwrite_string map Electricity N30M2_ZCEHX
analyse $overwrite_string map Electricity N50M2_ZCEHX
analyse $overwrite_string map Electricity N70M2_ZCEHX

analyse $overwrite_string map Hydrogen N10M2_ZCEHX
analyse $overwrite_string map Hydrogen N30M2_ZCEHX
analyse $overwrite_string map Hydrogen N50M2_ZCEHX
analyse $overwrite_string map Hydrogen N70M2_ZCEHX
