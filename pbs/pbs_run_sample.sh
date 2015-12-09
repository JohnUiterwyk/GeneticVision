#!/bin/bash
# Usage: qsub pbs-script
# Prepared By: Sudarshan Ramachandran, Network Engineer, VPAC, 15 Apr 2003
#	       sram@vpac.org
# Mods by DRB, 28/7/04 - mpiexec, better doc etc.

# NOTE: To activate a PBS option, remove the whitespace between the '#' and 'PBS'
# As a bare minimum you must set number of cpus and application name.

# Declares the shell that interprets the job script.
# PBS -S /bin/bash

# To give your job a name, replace "MyJob" with an appropriate name
# PBS -N MyJob

# Select the number of CPUs, if using mpirun.ch_gm need to adjust that line too.

# For Serial Jobs:
# PBS -l nodes=1

# For Parallel Jobs: ie. To reserve 8 nodes with 1 processors each, ie 8cpus.
# PBS -l nodes=8

# For Parallel Jobs: ie. To reserve 4 nodes with 2 processors each, ie 8cpus.
# PBS -l nodes=4:ppn=2

# For Parallel jobs with an odd number of processes; eg. 5 CPUs:
# Request 2 full nodes 'nodes=2', with 2 CPUs each 'ppn=2' and 1 extra CPU '+1'
# PBS -l nodes=2:ppn=2+1

# set your minimum acceptable walltime=hours:minutes:seconds
# PBS -l walltime=xx:xx:xx

## Specify your email address to be notified of progress.
# PBS -M yourname@domain

# To receive an email:
# 	- job is abored: 'a'
#	- job begins execution: 'b'
# 	- job terminates: 'e'
# 	Note: Please ensure that the PBS -M option above is set.
#
# PBS -m abe

# To capture to your root dir (rather than working dir ):
#	- output stream: 'o'
#	  The output stream will be saved as job_name.osequence
#	- error stream:	 'e'
#	  The error stream will be saved as job_name.esequence

# PBS -k oe

# Changes directory to your execution directory (Leave as is)
cd $PBS_O_WORKDIR

# Command to run a job, either mpi or serial :
# For mpi its mpiexec
# Serial or single cpu app need only the app name and any options.

# Usage: mpiexec ./program
# Usage: ./program