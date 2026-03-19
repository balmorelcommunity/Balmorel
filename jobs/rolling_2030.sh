#!/bin/sh
### General options
### -- specify queue --
#BSUB -q man
### -- set the job Name --
#BSUB -J GREAT_rolling_2030
### -- ask for number of cores (default: 1) --
#BSUB -n 10
### -- specify that the cores must be on the same host --
#BSUB -R "span[hosts=1]"
### -- specify that we need 4GB of memory per core/slot --
#BSUB -R "rusage[mem=4GB]"
### -- specify that we want the job to get killed if it exceeds 5 GB per core/slot --
#BSUB -M 4GB
### -- set walltime limit: hh:mm --
#BSUB -W 10:00
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
#BSUB -o logs/GREAT_rolling_2030_%J.out
#BSUB -e logs/GREAT_rolling_2030_%J.err

# Load error handling and GAMS paths
source jobs/functions.sh

# Get scenario choice and run name from jobs/scenario_choice.sh
source jobs/scenario_choice.sh

# Rolling horison simulation
cd O2030
cat data/T_roll.inc >data/T.inc
cd model
cat balopt_roll.opt >balopt.opt
gams Balmorel threads=$LSB_DJOB_NUMPROC --USEOPTIONFILE=2 --SCNAME=$scenario --scenario_name="${run_name}_R2030"
