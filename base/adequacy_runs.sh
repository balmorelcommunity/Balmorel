###!/bin/sh
### General options
### -- specify queue --
#BSUB -q man
### -- set the job Name --
#BSUB -J ZCEHX_2nd_operun
### -- ask for number of cores (default: 1) --
#BSUB -n 10
### -- specify that we need a certain architecture --
#BSUB -R "select[model == XeonPlatinum8462Y]"
### -- specify that the cores must be on the same host --
#BSUB -R "span[hosts=1]"
### -- specify that we need X GB of memory per core/slot --
#BSUB -R "rusage[mem=14GB]"
### -- specify that we want the job to get killed if it exceeds X GB per core/slot --
#BSUB -M 14.1GB
### -- set walltime limit: hh:mm --
#BSUB -W 24:00
### -- set the email address --
#BSUB -u mberos@dtu.dk
### -- send notification at start --
##BSUB -B
### -- send notification at completion --
#BSUB -N
### -- Specify the output and error file. %J is the job-id --
### -- -o and -e mean append, -oo and -eo mean overwrite --
#BSUB -o ./logs/ZCEHX_2nd_operun_%J.out
#BSUB -e ./logs/ZCEHX_2nd_operun_%J.err
# here follow the commands you want to execute with input.in as the input file

### Path to GAMS binary
export PATH=/appl/gams/47.6.0:$PATH

### Activate spatialstudy environment
source ~/miniconda3/bin/activate spatialstudy

analyse adequacy base_ZCEHX_2nd --nth-max 1

for name in N10M2 N30M2 N50M2 N70M2; do

  # Remove all investment options but the largest
  # python analysis/peri-process.py base_ZCEHX inv-options --max-only
  # Running Balmorel

  # Use /bin/cp to make sure the alias'ed "cp -> cp -i" is avoided
  /bin/cp -f "simex_${name}_ZCEHX"/* simex/
  cd "${name}/model"

  # Running Balmorel
  gams Balmorel --scenario_name=${name}_ZCEHX_2nd threads=$LSB_DJOB_NUMPROC

  # Exit, if there are errors
  if [ $? -ne 0 ]; then
    echo "GAMS execution failed for scenario $name"
    exit 1
  fi

  cd ../../

  # Copy the simex folder
  # cp simex -r simex_$name

  analyse adequacy ${name}_ZCEHX_2nd --nth-max 1

  # Collect heat storage profile data
  # analyse sifnaios-profile Aalborg base_RA
done
