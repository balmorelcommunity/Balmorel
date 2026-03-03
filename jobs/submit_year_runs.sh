
# Get scenario choice from jobs/scenario_choice.sh
source jobs/scenario_choice.sh

# Copy scenario simex files to simex (comment out if you didnt just run investment)
/usr/bin/cp -rf simex_${scenario_name}/* simex/ 

for year in 2030 2040 2050; do
  bsub < jobs/operun_${year}.sh 
  # Uncomment to wait for two minutes, if only running operational
  # sleep 120
done
