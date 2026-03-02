
# Get scenario choice from jobs/scenario_choice.sh
source jobs/scenario_choice.sh

# Copy scenario simex files to simex
/usr/bin/cp -rf simex_${scenario_name}/* simex/ 

for year in 2030 2040 2050; do
  bsub < jobs/operun_${year}.sh 
done
