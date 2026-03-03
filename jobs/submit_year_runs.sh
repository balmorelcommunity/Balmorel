# Get scenario choice from jobs/scenario_choice.sh
source jobs/scenario_choice.sh

# Copy scenario simex files to simex (comment out if you didnt just run investment)
/usr/bin/cp -rf simex_${scenario_name}/* simex/

# Submit fullyear runs (which, in turn, will submit rolling runs)
for year in 2030 2040 2050; do
  bsub <jobs/fullyear_${year}.sh
done
