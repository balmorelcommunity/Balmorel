# Submitting a Job

We refer to the [best practice guide](https://www.hpc.dtu.dk/?page_id=4204) by DTU Computing Center on how to figure out what resources to ask for. 

:::{warning}
Remember to study the log report after your job finishes, so you can be more accurate on what resources your job needs in the next submission!
:::

## Job Script

After having transferred our Balmorel model through WinSCP (see [previous page](access.md)), we need to submit a job. This means creating a job script that asks for the right amount of memory usage and time before completion. This is done through a job script, illustrated in the code snippet below. We refer to [this general guide](https://www.hpc.dtu.dk/?page_id=1416) by DTU Computing Center for the exact explanations of the different elements. Note that the paths in the `export` commands are specific to our setup at DTU's clusters. 

The bottom commands assumes that the job script is submitted from inside your Balmorel folder, and that your Balmorel project contains a "scenario1" scenario - see [how to create new scenarios](../get_started/scenario_setup.md). The `threads=$LSB_DJOB_NUMPROC` command makes sure that Balmorel does not use more cores than defined  in your job script (four in this case, due to `#BSUB -n 4`)

:::{warning}
Please make sure to switch to the solver options file `cplex.op2`, by going into the `balgams.opt` file and setting `$Setglobal USEOPTIONFILE 2`. Otherwise CPLEX will overwrite the number of chosen threads and will ue more resources than requested.
:::

```bash
#!/bin/sh 
### General options 
### -- specify queue -- 
#BSUB -q hpc
### -- set the job Name -- 
#BSUB -J My_Application
### -- ask for number of cores (default: 1) -- 
#BSUB -n 4 
### -- specify that the cores must be on the same host -- 
#BSUB -R "span[hosts=1]"
### -- specify that we need 4GB of memory per core/slot -- 
#BSUB -R "rusage[mem=4GB]"
### -- specify that we want the job to get killed if it exceeds 5 GB per core/slot -- 
#BSUB -M 5GB
### -- set walltime limit: hh:mm -- 
#BSUB -W 24:00 
### -- set the email address -- 
# please uncomment the following line and put in your e-mail address,
# if you want to receive e-mail notifications on a non-default address
##BSUB -u your_email_address
### -- send notification at start -- 
#BSUB -B 
### -- send notification at completion -- 
#BSUB -N 
### -- Specify the output and error file. %J is the job-id -- 
### -- -o and -e mean append, -oo and -eo mean overwrite -- 
#BSUB -o Output_%J.out 
#BSUB -e Output_%J.err 

# Get paths to GAMS 47
export PATH=/appl/gams/47.6.0:$PATH
export LD_LIBRARY_PATH=/appl/gams/47.6.0:$LD_LIBRARY_PATH

# Go to model folder of your scenario - this assumes that the job script is at the same level of the Balmorel folder
cd scenario1/model 
# Run Balmorel
gams Balmorel threads=$LSB_DJOB_NUMPROC
```

## Submitting the Job from PuTTY
Log in to PuTTY, change directory to inside your Balmorel folder (i.e. the `cd` command below), and submit the job that we created above using the `bsub` command. This assumes that you saved the job script as "job_script.sh". The job is now pending in a queue or is already running, you can check this using the command `bstat`.  
```bash
cd path/to/Balmorel
bsub < job_script.sh
bstat
```
If you named your output log "Output_%J.log" as in the job script above (`#BSUB -o Output_%J.out`), you can check this to see the progress of the optimisation. "%J" will be the unique job number, that the HPC assigns to the job. E.g., you could ctrl + F and search for "LOOPS IYALIAS" to see which model years have been or are being optimised. Errors are reported in the .err file.
