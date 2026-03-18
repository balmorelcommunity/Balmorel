#!/bin/sh
### General options
### -- specify queue --
#BSUB -q man
### -- set the job Name --
#BSUB -J temporal_aggregation
### -- ask for number of cores (default: 1) --
#BSUB -n 3
### -- specify that the cores must be on the same host --
#BSUB -R "span[hosts=1]"
### -- specify that we need 4GB of memory per core/slot --
#BSUB -R "rusage[mem=5GB]"
### -- specify that we want the job to get killed if it exceeds 5 GB per core/slot --
#BSUB -M 5GB
### -- set walltime limit: hh:mm --
#BSUB -W 4:00
### -- set the email address --
# please uncomment the following line and put in your e-mail address,
# if you want to receive e-mail notifications on a non-default address
##BSUB -u mberos@dtu.dk
### -- send notification at start --
##BSUB -B
### -- send notification at completion --
#BSUB -N
### -- Specify the output and error file. %J is the job-id --
### -- -o and -e mean append, -oo and -eo mean overwrite --
#BSUB -o logs/temporal_aggregation_%J.out
#BSUB -e logs/temporal_aggregation_%J.err

# Load error handling and GAMS paths
source jobs/functions.sh

# Get scenario choice and run name from jobs/scenario_choice.sh
source jobs/scenario_choice.sh

# Define temporal aggregation parameters
scenario_to_agg=base
seasons=8
terms=24
method=kmedoids
representation=medoid

# Do aggregation
pixi run python -c "from pybalmorel import Balmorel
m=Balmorel(\".\", gams_system_directory=\"/appl/gams/50.4.1\")
m.temporal_aggregation(\"${scenario_to_agg}\", 
                      seasons=${seasons}, 
                      terms=${terms}, 
                      method=\"${method}\",
                      representation=\"${representation}\",
                      overwrite=False
)
"

# Make model folder
agg_scenario="${scenario_to_agg}_S${seasons}T${terms}"
if not [ -d "${agg_scenario}/model" ]; then
  mkdir ${agg_scenario}/model
  cp base/model/Balmorel.gms ${agg_scenario}/model/
  cp base/model/cplex.op2 ${agg_scenario}/model/
  # MANUAL CHANGES:
  rm ${agg_scenario}/data/GDATA.inc
  rm ${agg_scenario}/data/DR_DATAINPUT.inc
fi

echo "FINAL MANUAL STUFF TO DO NOW:
- Figure out which EV profile has the data, and change its suffix to 1
"
# bsub <jobs/investment.sh
