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
#PBS -o pbs_gv_compile.log
cd $PBS_O_WORKDIR

# Merging Standard Output

ROOT_DIR=$PBS_O_WORKDIR/..
BUILD_DIR=$PBS_O_WORKDIR/../build
BIN_DIR=$PBS_O_WORKDIR/../bin

mkdir -p $BUILD_DIR
mkdir -p $BIN_DIR

# Set output file

# Changes directory to your execution directory (Leave as is)

cd $ROOT_DIR

# make the directories just in case

# Load the environment variables for cmake and gcc
module load gcc/4.9.2
module load cmake/3.0.1

# The command to actually run the job
cd $BUILD_DIR
cmake $ROOT_DIR
make
mv GeneticVision $BIN_DIR
rm -rf $BUILD_DIR
cd $PBS_O_WORKDIR

