#!/bin/bash

read -p 'Overwrite? (true/false): ' overwrite

# Analyse change between groups of scenarios 

export PATH=/appl/gams/47.6.0:$PATH
source ~/miniconda3/bin/activate spatialstudy

if [ "$overwrite" = "true" ]; then
    overwrite_string="--overwrite"
fi

# include_base_scenarios=true
# analyse $overwrite_string cap --filters   "Scenario in ['N2_ZCEHX_ES', 'N2_ZCEHX',  'N10_ZCEHX_ESNC', 'N10_ZCEHX', 'N30_ZCEHX_ESNC', 'N30_ZCEHX', 'N50_ZCEHX_ESNC', 'N50_ZCEHX', 'N70_ZCEHX_ESNC', 'N70_ZCEHX']"
analyse $overwrite_string cost-change --sc-group "N2_ZCEHX_ES, N10_ZCEHX_ESNC, N30_ZCEHX_ESNC, N50_ZCEHX_ESNC, N70_ZCEHX_ESNC ; N2_ZCEHX,  N10_ZCEHX, N30_ZCEHX, N50_ZCEHX, N70_ZCEHX" --group-names "Economy of Scale;Baseline"
