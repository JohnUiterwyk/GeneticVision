#!/bin/bash

# To give your job a name, replace "MyJob" with an appropriate name
#PBS -N CompileGeneticVision

# For R need to run on single CPU
#PBS -l nodes=1

# set your minimum acceptable walltime=hours:minutes:seconds
#PBS -l walltime=1:00:00

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


# Changes directory to your execution directory (Leave as is)
cd $PBS_O_WORKDIR

# Load the environment variables for R
# module load R
module load cmake >> $PBS_O_WORKDIR/output/pbs_gv_stdout.log

# The command to actually run the job
mkdir build >> $PBS_O_WORKDIR/output/pbs_gv_stdout.log
cd build >> $PBS_O_WORKDIR/output/pbs_gv_stdout.log
cmake .. >> $PBS_O_WORKDIR/output/pbs_gv_stdout.log
make >> $PBS_O_WORKDIR/output/pbs_gv_stdout.log

