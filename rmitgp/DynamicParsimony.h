#pragma once

/******************************************************************************
 Header file
 Function:		getParsimonyCoefficient
 Date created:  06/10/2011
 Written by:    Quentin Serrurier

 Based on the journal article found here:
 @inproceedings{poli2008parsimony,
  title={Parsimony pressure made easy},
  author={Poli, R. and McPhee, N.F.},
  booktitle={Proceedings of the 10th annual conference on Genetic and evolutionary computation},
  pages={1267--1274},
  year={2008},
  organization={ACM}
}

	This is a form of parsimony pressure that relies on a dynamic parsimony coefficient that is proportional to the strength of correction required, this can be used to create parsimony pressure that follows or chases a function, in our case a sine wave.
	* muz is the baseline of the function, essentially the constant offset, it is the mean size of the population members at generation zero.
	* amplitude is the aplitude of the sine wave.
	* runlength is actually half the period of the sine wave, it's used to bring the sine wave down to the baseline by the end of the run.
	*
	*
	* QCS

******************************************************************************/

#include "Population.h"

double getParsimonyCoefficient (Population * pop, double amplitude, double runlength, double muz);

double rFunction (int t, double amplitude, double period, double muzero);
