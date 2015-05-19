#ifndef _EMOPOPULATION_H_
#define _EMOPOPULATION_H_

/****************************************************************
 * Class: EMOPopulation.h
 * Description: 
 * Written by: Mohammad Nabi Omidvar
 * Date Created: 16 Mar 2011
 ***************************************************************/

#include "Population.h"

class EMOPopulation : public Population{

    private:
        double mutationProbability;

    public:


        EMOPopulation(int size, int initSize, const char *logFileName, GPConfig *conf);
        virtual bool evolve(int numGenerations);
        virtual void nextGeneration();

        //TODO: To be implemented for EMO
        virtual void writeLog();
        virtual void computeStatistics( );
        virtual void writeToFile();
        virtual void readFromFile(char *fileName);
        void assignFitness(GeneticProgram **pop);
        virtual void setMutationProbability(double m);
        virtual double getMutationProbability();
        friend ostream& operator << (ostream& o, EMOPopulation& p);
        friend istream& operator >> (istream& i, EMOPopulation& p);
};

#endif
