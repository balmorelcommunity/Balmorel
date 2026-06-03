#!/bin/sh
#=============================================================================
# run_Scenario_EU.sh
#   One-shot driver for the Scenario_EU (EU + Nordic Planetary-Boundary) model:
#     1. SOLVE   the myopic 2030/2040/2050 cohorts        -> output/cohort_<yr>.gdx
#     2. REPORT  rebuild MainResults per committed year from each cohort gdx
#     3. MERGE   + audit into  output/MainResults_2030_40_50.gdx
#   Submit with:   bsub < run_Scenario_EU.sh
#=============================================================================
#BSUB -q man
#BSUB -J Scenario_EU
#BSUB -n 62
#BSUB -R "span[hosts=1]"
#BSUB -R "rusage[mem=63GB]"
#BSUB -M 63.1GB
#BSUB -W 34:00
#BSUB -o Scenario_EU_%J.out
# Notes: the EU + full-PB solve is large (~24-30 h on 62 cores, ~15 GB). The
# report/merge step is light, but pybalmorel needs ~64 GB to load the GDX, hence
# the memory above. A fast node speeds the solve, e.g. add:
#   #BSUB -R "select[model==XeonPlatinum8462Y]"

# ---- user config (edit these for your environment) --------------------------
REPO_ROOT=/work3/dhrsh/Balmorel/0_Balmorel_PB_Github/4_Balmorel_High_Res_PB_all_wo_FG_eq
SCENARIO=Scenario_EU
GAMS=/appl/gams/47.6.0
LICENSE=/work3/dhrsh/Gams/gamslice.txt
PYBALMOREL=/work3/dhrsh/miniconda3/envs/pybalmorel/bin/python
# -----------------------------------------------------------------------------

export PATH=$GAMS:$PATH
export LD_LIBRARY_PATH=$GAMS:$LD_LIBRARY_PATH
MODEL=$REPO_ROOT/$SCENARIO/model
OUTDIR=$REPO_ROOT/$SCENARIO/output
cd "$MODEL" || { echo "cannot cd to $MODEL"; exit 1; }

echo ">>>>> 1/3  SOLVE $SCENARIO (myopic 2030/2040/2050) <<<<<"
gams Balmorel license=$LICENSE profile=1 profileTol=300 threads=$LSB_DJOB_NUMPROC \
     --USEOPTIONFILE=2 limcol=0 limrow=0 solprint=off o=Balmorel_RCP26.lst
echo "  solve rc=$?"

echo ">>>>> 2/3  REPORT: rebuild MainResults per committed cohort year <<<<<"
for YR in 2030 2040 2050; do
  echo "  --- year $YR ---"
  rm -f MainResults.gdx
  gams Balmorel license=$LICENSE --USEOPTIONFILE=2 --REPORTYEAR=$YR --OUTPUT_SUMMARY=yes \
       limcol=0 limrow=0 solprint=off o=report_$YR.lst
  if [ -f MainResults.gdx ]; then
    mv -f MainResults.gdx "$OUTDIR/MainResults_$YR.gdx"
    echo "    -> MainResults_$YR.gdx"
  else
    echo "    !! MainResults.gdx NOT produced for $YR"
  fi
done

echo ">>>>> 3/3  MERGE + AUDIT -> MainResults_2030_40_50.gdx <<<<<"
# pybalmorel sets its own GAMS system_directory; clear the GAMS-47 LD path first.
( unset LD_LIBRARY_PATH; "$PYBALMOREL" "$REPO_ROOT/0_HPC_Jobs/merge_audit_3yr.py" "$OUTDIR" )
echo "  merge+audit rc=$?"
echo ">>>>> DONE -> $OUTDIR/MainResults_2030_40_50.gdx <<<<<"
