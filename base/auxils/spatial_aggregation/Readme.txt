-------------------------------------
TOOL FOR SPATIAL AGGREGATION COMMANDS
-------------------------------------

This python script may be used to aggregate areas (not regions, yet) in Balmorel,
using simple commands.

NOTE:
For AAA, CCCRRRAAA and RRRAAA, you may need to change the position of the set-ending
GAMS-command, /;
 
Running this script will replace all commands in between the following strings:
    
             * ---- PYTHON SPATIAL AGGREGATION START LOCATER ----
             ...
             ...COMMANDS ARE REPLACED HERE...
             ...
             * ---- PYTHON SPATIAL AGGREGATION END LOCATER ----

If these strings are not present in the respective .inc file in base/data,
this string and modifications will be appended to the file.


This tool is currently compatible with the following addons:
    - HYDROGEN
    - TRANSPORT
    - INDUSTRY (Note: not tested by aggregation of industry areas)
    - INDIVUSERS (Note: not tested by aggregation of individual user areas)
        
It reads the following files from base/data:
    - AAA
    - AGKN
    - CCCRRRAAA
    - DH
    - DH_VAR_T
    - GKFX
    - HYDROGEN_AGKN
    - HYDROGEN_GKFX
    - INDIVUSERS_SOLH_VAR_T
    - INDUSTRY_SOLH_VAR_T
    - INDUSTRY_XHKFX
    - RRRAAA
    - SOLH_VAR_T
    - SOLHFLH

...and creates new, modified files in the auxils folder, that can then be 
copy+pasted to the wanted, aggregated scenario data folder.