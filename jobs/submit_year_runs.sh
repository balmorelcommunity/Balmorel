# Get scenario choice from jobs/scenario_choice.sh
source jobs/scenario_choice.sh

# Submit fullyear runs (which, in turn, will submit rolling runs)
for year in 2030 2040 2050; do
  bsub <jobs/fullyear_${year}.sh
done
