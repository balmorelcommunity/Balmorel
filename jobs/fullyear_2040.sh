#!/bin/sh
### General options
### -- specify queue --
#BSUB -q man
### -- set the job Name --
#BSUB -J GREAT_fullyear_2040
### -- ask for number of cores (default: 1) --
#BSUB -n 10
### -- specify that the cores must be on the same host --
#BSUB -R "span[hosts=1]"
### -- specify that we need 4GB of memory per core/slot --
#BSUB -R "rusage[mem=10GB]"
### -- specify that we want the job to get killed if it exceeds 5 GB per core/slot --
#BSUB -M 10GB
### -- set walltime limit: hh:mm --
#BSUB -W 32:00
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
#BSUB -o logs/GREAT_fullyear_2040_%J.out
#BSUB -e logs/GREAT_fullyear_2040_%J.err

# Get paths to GAMS 47
export PATH=/appl/gams/50.4.1:$PATH
export LD_LIBRARY_PATH=/appl/gams/50.4.1:$LD_LIBRARY_PATH

# Get scenario choice and run name from jobs/scenario_choice.sh
source jobs/scenario_choice.sh

# Check if simex exists, create if not
if not [ -d "${PWD}/O2040/simex" ]; then
  mkdir O2040/simex
fi

# Copy or overwrite simex files from investment run, use /usr/bin/cp to avoid interactive mode defined in ~/.bashrc
/usr/bin/cp -rf $investment_scenario/simex/* O2040/simex/

# Full year simulation
cd O2040
cat data/T_full.inc > data/T.inc
cd model
cat balopt_full.opt > balopt.opt
gams Balmorel threads=$LSB_DJOB_NUMPROC --USEOPTIONFILE=2 --SCNAME=$scenario --scenario_name="${run_name}_F2040"
cat balopt.opt > balopt_full.opt
cd ../../

# Submit rolling horizon run
bsub <jobs/rolling_2040.sh
