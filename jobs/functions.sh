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
