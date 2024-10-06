#!/bin/bash

# source ~/miniconda3/bin/activate
# conda activate spatialstudy

function showHelp()
{
   echo ""
   echo "Usage: $0 [--gencap, --stocap]" 
   echo ""
   echo -e "\t --gencap Will plot generation capacities"
   echo -e "\t --stocap Will plot storage capacities"
   echo -e "\t --help Show this help message"
   exit 1 # Exit script after printing help
}

# If no commands are input, display help
if [ "$#" -eq 0 ]; then
    showHelp
    exit 0
fi


python analysis/analysis.py $@
# Based on the parsed options, run different Python scripts
# if [[ "$1" == "--gencap" ||  "$1" == "--stocap" ]]; then
#     python analysis/analysis.py "$@"
# fi
