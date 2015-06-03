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
ROOT_DIR=$PBS_O_WORKDIR/..
BUILD_DIR=$PBS_O_WORKDIR/../build
OUTPUT_DIR=$PBS_O_WORKDIR/../output
STDOUT_LOG=$PBS_O_WORKDIR/../output/pbs_gv_stdout.log

# Changes directory to your execution directory (Leave as is)
cd $PBS_O_WORKDIR
cd $ROOT_DIR

mkdir $OUTPUT_DIR

# Load the environment variables for R
# module load R
module load cmake >> OUTPUT_DIR/pbs_gv_stdout.log

# The command to actually run the job
mkdir $BUILD_DIR
cd $BUILD_DIR >> $STDOUT_LOG
cmake ROOT_DIR >> $STDOUT_LOG
make >> $STDOUT_LOG
cd $PBS_O_WORKDIR
