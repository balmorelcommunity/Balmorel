#!/bin/sh
### General options
### -- specify queue --
#BSUB -q man
### -- set the job Name --
#BSUB -J GREAT_investment
### -- ask for number of cores (default: 1) --
#BSUB -n 10
### -- specify that the cores must be on the same host --
#BSUB -R "span[hosts=1]"
### -- specify that we need 4GB of memory per core/slot --
#BSUB -R "rusage[mem=7GB]"
### -- specify that we want the job to get killed if it exceeds 5 GB per core/slot --
#BSUB -M 7GB
### -- set walltime limit: hh:mm --
#BSUB -W 24:00
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
#BSUB -o logs/GREAT_investment_%J.out
#BSUB -e logs/GREAT_investment_%J.err

# Get paths to GAMS 47
export PATH=/appl/gams/47.6.0:$PATH
export LD_LIBRARY_PATH=/appl/gams/47.6.0:$LD_LIBRARY_PATH

# Get scenario choice and run name from jobs/scenario_choice.sh
source jobs/scenario_choice.sh

# Investment optimisation
cd base/model
gams Balmorel threads=$LSB_DJOB_NUMPROC --USEOPTIONFILE=2 --SCNAME=$scenario --scenario_name="${run_name}_INV"
cd ../../

# Submit fullyear runs
bash jobs/submit_year_runs.sh
