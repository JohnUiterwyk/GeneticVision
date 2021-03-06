#!/bin/bash

# To give your job a name, replace "MyJob" with an appropriate name
#PBS -N GV_EasySquare

# For R need to run on single CPU
#PBS -l nodes=1

# set your minimum acceptable walltime=hours:minutes:seconds
#PBS -l walltime=100:00:00

# Inherit the correct environment variables
# PBS -V

# Specify your email address to be notified of progress.
#PBS -M jnuiterwyk@gmail.com
# To receive an email:
#       - job is abored: 'a'
#       - job begins execution: 'b'
#       - job terminates: 'e'
#       Note: Please ensure that the PBS -M option above is set.
#
#PBS -m abe
#PBS -j oe
#PBS -o pbs_gv_run.log


# Changes directory to your execution directory (Leave as is)
cd $PBS_O_WORKDIR

# Load the environment variables for R
# module load R

# The command to actually run the job
mkdir -p output
../../bin/GeneticVision gv-config.json >> output/pbs_stdout_stream.log
