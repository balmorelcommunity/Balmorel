#!/bin/sh
# Reusable error handling for BSUB job scripts
# Source this file at the beginning of your job script

# Exit on error, unset variables, and pipeline failures
set -e
set -u
set -o pipefail

# Trap signals and errors to prevent further execution
cleanup() {
  exit_code=$?
  if [ $exit_code -ne 0 ]; then
    echo "ERROR: Job failed with exit code $exit_code at $(date)"
    echo "Stopping execution - no further jobs will be submitted"
  fi
  exit $exit_code
}

trap cleanup EXIT SIGTERM SIGINT

# Function for checking optimality
optimality_check() {
  job_id=$1
  optimal_nr=$2
  count=$(rg -e 'LP status \(1\): optimal' logs/*_${job_id}.out --count-matches)
  if [[ "$count" -eq "$optimal_nr" ]]; then
    echo "OPTIMAL: Job ${job_id} had ${count} optimal solutions as expected"
  else
    echo "INFEASIBLE: Job ${job_id} had ${count} optimal solutions, which is not the expected ${optimal_nr}!"
    exit 1
  fi
}

# Get user settings and paths to GAMS 50.4.1
source .env
if not [ -f ".env" ]; then
  echo "No .env file found! Make one and define:
  GAMS_SYSTEM_DIR=...
  "
  exit 1
fi
export PATH=$GAMS_SYSTEM_DIR:$PATH
export LD_LIBRARY_PATH=$GAMS_SYSTEM_DIR:$LD_LIBRARY_PATH
