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
#PBS -j oe
#PBS -o pbs.log
cd $PBS_O_WORKDIR/../

# Load the environment variables for cmake and gcc
module load gcc/4.9.3
module load cmake/3.2.3

# Merging Standard Output

./compile.sh 2>&1 | tee -a ./compile.log

