#!/bin/bash

read -p 'Overwrite? (true/false): ' overwrite

export PATH=/appl/gams/47.6.0:$PATH
source ~/miniconda3/bin/activate spatialstudy

if [ -z "${overwrite}" ] || [ "${overwrite}" = "y" ]; then
    overwrite_string="--overwrite"
fi

# Analyse results for hydrogen modelled at country level 
analyse $overwrite_string cap   --filters "Scenario in ['N2_ZCEHX', 'N2H1_ZCEHX', 'N10_ZCEHX', 'N10H1_ZCEHX', 'N30_ZCEHX', 'N30H1_ZCEHX', 'N50_ZCEHX', 'N50H1_ZCEHX', 'N70_ZCEHX', 'N70H1_ZCEHX']"
analyse $overwrite_string costs --filters "Scenario in ['N2_ZCEHX', 'N2H1_ZCEHX', 'N10_ZCEHX', 'N10H1_ZCEHX', 'N30_ZCEHX', 'N30H1_ZCEHX', 'N50_ZCEHX', 'N50H1_ZCEHX', 'N70_ZCEHX', 'N70H1_ZCEHX']"