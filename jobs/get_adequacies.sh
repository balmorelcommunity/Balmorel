#!/bin/sh
### General options
### -- specify queue --
#BSUB -q man
### -- set the job Name --
#BSUB -J get_adequacies
### -- ask for number of cores (default: 1) --
#BSUB -n 5
### -- specify that the cores must be on the same host --
#BSUB -R "span[hosts=1]"
### -- specify that we need 4GB of memory per core/slot --
#BSUB -R "rusage[mem=2GB]"
### -- specify that we want the job to get killed if it exceeds 5 GB per core/slot --
#BSUB -M 2GB
### -- set walltime limit: hh:mm --
#BSUB -W 1:00
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
#BSUB -o logs/get_adequacies_%J.out
#BSUB -e logs/get_adequacies_%J.err

# Get paths to GAMS 47
export PATH=/appl/gams/47.6.0:$PATH
export LD_LIBRARY_PATH=/appl/gams/47.6.0:$LD_LIBRARY_PATH

# Get scenario choice and run name from jobs/scenario_choice.sh
source jobs/scenario_choice.sh

# Get adequacies
for operun in F2030 F2040 F2050 R2030 R2040 R2050; do
  pixi run analyse adequacy "${run_name}_${operun}"
done

