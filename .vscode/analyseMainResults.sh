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
analyse $overwrite_string --large-plot cap --filters   "Scenario in ['N2_ZCEHX', 'N10_ZCEHX', 'N30_ZCEHX', 'N50_ZCEHX', 'N70_ZCEHX', 'base_ZCEHX']" --include-backup
analyse $overwrite_string --large-plot costs --filters "Scenario in ['N2_ZCEHX', 'N10_ZCEHX', 'N30_ZCEHX', 'N50_ZCEHX', 'N70_ZCEHX', 'base_ZCEHX']"
analyse $overwrite_string --large-plot ra-plot "N2_synfheur, N10_synfheur, N30_synfheur, N50_synfheur, N70_synfheur, base_synfheur"

# Rename
mv analysis/plots/generation_capacity.pdf analysis/plots/generation_capacity_uniform.pdf
mv analysis/plots/storage_capacity.pdf analysis/plots/storage_capacity_uniform.pdf
mv analysis/plots/systemcosts.pdf analysis/plots/systemcosts_uniform.pdf
mv analysis/plots/RA-plot.pdf analysis/plots/RA-plot_uniform.pdf

# Hierarchically clustered
analyse $overwrite_string --large-plot cap --filters   "Scenario in ['N2_ZCEHX', 'N10M2_ZCEHX', 'N30M2_ZCEHX', 'N50M2_ZCEHX', 'N70M2_ZCEHX', 'base_ZCEHX']" --include-backup
analyse $overwrite_string --large-plot costs --filters "Scenario in ['N2_ZCEHX', 'N10M2_ZCEHX', 'N30M2_ZCEHX', 'N50M2_ZCEHX', 'N70M2_ZCEHX', 'base_ZCEHX']"
analyse $overwrite_string --large-plot ra-plot "N2_synfheur, N10M2_ZCEHX, N30M2_ZCEHX, N50M2_ZCEHX, N70M2_ZCEHX, base_synfheur"

# Rename
mv analysis/plots/generation_capacity.pdf analysis/plots/generation_capacity_hierarchy.pdf
mv analysis/plots/storage_capacity.pdf analysis/plots/storage_capacity_hierarchy.pdf
mv analysis/plots/systemcosts.pdf analysis/plots/systemcosts_hierarchy.pdf
mv analysis/plots/RA-plot.pdf analysis/plots/RA-plot_hierarchy.pdf