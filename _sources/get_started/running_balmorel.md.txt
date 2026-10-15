# Running Balmorel

To setup Balmorel in GAMS Studio, you can drag and drop the Balmorel.gms into GAMS Studio to create a correctly setup project. It is important to ensure that the working directory is in your/path/to/Balmorel/test_run/model, as illustrated in [the Figure](#GAMS_Studio_Setup) below.

:::{figure} ../img/GAMS_Studio_Setup.jpg 
:name: GAMS_Studio_Setup
:alt: How to check the working directory of your GAMS project
:width: 100% 
:align: center
Check your working directory by opening View/Project Explorer, and then press the gear icon ⚙️ next to "Balmorel".
:::

Make sure that Balmorel/test_run/model/Balmorel.gms is the main file and press the green run button ▶️. Balmorel should now optimise model year 2030, 2040, 2050 for Denmark and Norway using the previously specificed timesteps. 

## Command-Line Interface
Balmorel can also be run using GAMS' command-line interface (CLI). You will need to use this when [running on a HPC](../running_on_hpc.md). The commands below change directory to the relevant scenario/model folder (assuming that your command prompt is already inside the Balmorel folder) and executes Balmorel. 
```console
cd test_run/model
gams Balmorel
```
