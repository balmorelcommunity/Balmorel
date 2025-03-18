#!/bin/bash

export PATH=/appl/gams/47.6.0:$PATH
source ~/miniconda3/bin/activate spatialstudy

# Analyse results for hydrogen modelled at country level 
analyse --overwrite cap --filters "Scenario in ['N2_ZCEHX', 'N2H1_ZCEHX', 'N10_ZCEHX', 'N10H1_ZCEHX', 'N30_ZCEHX', 'N30H1_ZCEHX', 'N50_ZCEHX', 'N50H1_ZCEHX', 'N70_ZCEHX', 'N70H1_ZCEHX']"
analyse --overwrite costs --filters "Scenario in ['N2_ZCEHX', 'N2H1_ZCEHX', 'N10_ZCEHX', 'N10H1_ZCEHX', 'N30_ZCEHX', 'N30H1_ZCEHX', 'N50_ZCEHX', 'N50H1_ZCEHX', 'N70_ZCEHX', 'N70H1_ZCEHX']"