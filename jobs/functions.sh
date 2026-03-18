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

# Get paths to GAMS 50.4.1
export PATH=/appl/gams/50.4.1:$PATH
export LD_LIBRARY_PATH=/appl/gams/50.4.1:$LD_LIBRARY_PATH
