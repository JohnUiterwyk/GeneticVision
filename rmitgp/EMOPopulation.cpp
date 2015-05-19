#include "EMOPopulation.h"
#include "EMOTournamentSelection.h"
#include "NSGA2.h"
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <sys/time.h>




EMOPopulation::EMOPopulation(int size, int initSize, const char *logFileName, GPConfig *conf):
    Population(size, initSize, logFileName, conf){
        cout<<"test"<<endl;
}

bool EMOPopulation::evolve(int numGenerations)
{

    assignFitness(pop);  
    NSGA2::assignRankAndCrowdingDistance(this->pop, Population::config->numObjectives, numIndividuals);

    int i=1;
    evaluations = 0;
    for (; i<numGenerations; i++)
    {

        nextGeneration();

        /* Mohammad: If the multi-objective feature is enabled, the instance of
         * the Fitness class which is subclassed by the client program has to 
         * properly implement all the objective functions and the fitness values 
         * for all of the objectives has to be assigned to their corresponding 
         * objective value in the `objValues'  property of the GeneticProgram 
         * class when the assignFitness() method is invoked.*/


        //TODO: how this function is affected?
        computeStatistics(); //Calculate statistics for the population
		
        //TODO: How parsimony is affected by EMO?
        if(config != NULL && config->parsimonypres != NULL)
        {
            config->parsimonypres->applyParsimony(this);
        }
        evaluations += numIndividuals;   //Update the number of evaluations performed
        //TODO: Do we need this sorting procedure in EMO?
        //sortPopulation();    //Sort the population based on fitness
        writeLog();          //Write some information to the log file

        /* Decimation 
           The actual removal of individuals from the bottom of the population and the
           freeing of the memory is carried out in the numGenerationBeforeDecimation
           method.

         */

        //TODO: Is this affected by EMO?
        if ( performDecimation )
        {
            /* If the numGenerationBeforeDecimation set to a value greater than 0
               progressive decimation is performed */
            if ( i < numGenerationBeforeDecimation )
                setNumIndividuals(numIndividuals - fallPerGeneration);
            else if ( i == numGenerationBeforeDecimation )
            {
                //Decimation is completed in this step.
                setNumIndividuals(initNumIndividuals);
                performDecimation = false;
            }
        }

        //TODO: This is meaningless in EMO.
        //If the solution has been found quit and return true to
        //indicate success 
        //if (config->fitnessObject->solutionFound(pop, numIndividuals))
        //{
        //    logFile << "Solution found!\n";
        //    return true;
        //}

    }

    //TODO: not sure whether this is needed or not. it might be necessary to sort based on rank.
    //sortPopulation();
    return false;
}


void EMOPopulation::assignFitness(GeneticProgram **pop){
   config->fitnessObject->assignFitness(pop, numIndividuals);
}


void EMOPopulation::nextGeneration(){
    int *a1, *a2;
    int i;
    GeneticProgram *parent1, *parent2;
    a1 = (int *)malloc(numIndividuals*sizeof(int));
    a2 = (int *)malloc(numIndividuals*sizeof(int));
    for (i=0; i<numIndividuals ; i++)
    {
        a1[i] = a2[i] = i;
    }

    random_shuffle(a1, a1+numIndividuals);
    random_shuffle(a2, a2+numIndividuals);

    GeneticProgram **nextPop = new GeneticProgram* [numIndividuals];
    GeneticProgram **mixedpop = new GeneticProgram* [2*numIndividuals];

    for (i=0; i<numIndividuals ; i+=4)
    {
        //TODO: crowding dis in select function is not implemented.
        parent1 = EMOTournamentSelection::select(pop[a1[i]], pop[a1[i+1]], config);
        parent2 = EMOTournamentSelection::select(pop[a1[i+2]], pop[a1[i+3]], config);
        nextPop[i] = parent1->copy();
        nextPop[i+1] = parent2->copy();
        config->crossoverOperator->crossover(*(nextPop[i]), *(nextPop[i+1]), 100, config);

        parent1 = EMOTournamentSelection::select(pop[a2[i]], pop[a2[i+1]], config);
        parent2 = EMOTournamentSelection::select(pop[a2[i+2]], pop[a2[i+3]], config);
        nextPop[i+2] = parent1->copy();
        nextPop[i+3] = parent2->copy();
        config->crossoverOperator->crossover(*(nextPop[i+2]), *(nextPop[i+3]), 100, config);
    }
    free (a1);
    free (a2);

    //TODO: The Gayan's implementation of the random number generator should be used.
    //mutate some individuals
    for (i=0; i<numIndividuals; i++)
    {
        if(rand() / (double) RAND_MAX <= mutationProbability){
            nextPop[i] = pop[i]->copy();
            config->mutationOperator->mutate(*(nextPop[i]), config);
        }
    }
 
    //TODO: assignFitness to the new population
    assignFitness(nextPop);  //Evaluate the programs and assign their fitness values

    //merge the populations.
    memcpy(mixedpop, pop, sizeof(GeneticProgram*)*numIndividuals);
    memcpy(&(mixedpop[numIndividuals]), nextPop, sizeof(GeneticProgram*)*numIndividuals);

    NSGA2::fillNondominatedSort (mixedpop, pop, numIndividuals, Population::config->numObjectives);


    //copy new generation over old generation
    //for(i=0; i<numIndividuals; i++)
    //{
    //    delete (pop[i]);
    //    pop[i] = NULL;
    //}

    //delete [] pop;
    //pop = nextPop;

    //TODO: how this function is affected?
    //Write the pop to a file if it's time
    if ((generationNumber % loggingFrequency) == 0)
        writeToFile();


    generationNumber++;
}


//TODO: needs to be modified to output the value of all objectives.
//TODO: How the best, avg, and worst fitness is calculated in EMO?
//TODO: Does it have to happen for all objectives?
void EMOPopulation::writeLog()
{
   time_t theTime;
   time(&theTime);

   logFile << "*****************************************\n"
           << "Generation " << generationNumber << endl
           << "Time " << ctime(&theTime)
           << "BestFitness " << bestFitness << endl
           << "WorstFitness " << worstFitness << endl
           << "AverageFitness " << avgFitness << endl
           << "AverageDepth " << avgDepth << endl
           << "AverageSize " << avgSize << endl
           << "Evaluation " << evaluations << endl
           << "ParsimonyCoeff " << parscoeff << endl;
}


//TODO: How is this affected by EMO?
void EMOPopulation::computeStatistics()
{
   int i;
   double totalFitness=0.0;
   double totalDepth=0.0;
   double totalSize=0.0;
   double totalNormFitness=0.0;

   bestFitness = getBest()->getFitness();
   worstFitness = getWorst()->getFitness(); 

   for (i=0; i<numIndividuals; i++)
   {
      //Change added Normalized fitness
      pop[i]->setNormFitness(1.0 / (1.0 + pop[i]->getFitness()));
      totalNormFitness += pop[i]->getNormFitness();
      
      totalFitness += pop[i]->getFitness();   
      totalDepth += pop[i]->getDepth();
      totalSize += pop[i]->getSize();
   }

   avgNormFitness = totalNormFitness / numIndividuals;
   avgFitness = totalFitness / numIndividuals;
   avgDepth = totalDepth / numIndividuals;
   avgSize = totalSize / numIndividuals;
}


ostream& operator << (ostream& o, EMOPopulation& p)
{
   time_t theTime;
   int i;
   string s1;

   time(&theTime);
   
   int numObjectives =  p.config->numObjectives;

   o << "Population at generation " << p.generationNumber << endl 
     << "File created at " << ctime(&theTime) 
     << "numIndividuals " << p.numIndividuals << endl
     << "depthLimit " << p.depthLimit << endl
     << "initdepthLimit " << p.initdepthLimit << endl
     << "minDepth " << p.minDepth << endl
     << "returnType " << p.returnType << endl
     << "mutationRate " << p.mutationRate << endl
     << "crossoverRate " << p.crossoverRate << endl
     << "elitismRate " << p.elitismRate << endl
     << "numObjectives " <<p.config->numObjectives<<endl;

   for(i=0; i<p.numIndividuals; i++)
   {
      s1 = "";
      p.pop[i]->print(s1);
      o << "###################################\n"
        << "Individual " << i << endl;
        for(int j = 0 ; j < numObjectives ; j++){
            o<< "Fitness " <<j<<" : "<< p.pop[i]->getObjectiveValue(j) << endl;
        }
        o<< "Depth " << p.pop[i]->getDepth() << endl
        << "Size " << p.pop[i]->getSize() << endl
        << "Program " << s1 << endl;
   }

   return o;
}

istream& operator >> (istream& i, EMOPopulation& p)
{
   const int MAXLINE = 5000;
   char line[MAXLINE];   
   string programString;
   char tmpChar;
   char range[502]; 	/* Added by Feng/Geoff Lee 3/12/2012. Used for Dynamic Selection coding.  */
   
   int individual=0;

   int iValue=0;
   double dValue=0.0;
   int objIndex = 0;

   //First loop reads the header info in the pop file
   while (true)
   {
      //Get a line of input from the stream
      if (!(i.getline(line, MAXLINE, '\n')))
      {
         if (i.eof() || i.bad())
            break;

         i.clear();
      }


      //If we read a hash at the start of the line, then
      //the header info is finished
      if (line[0] == '#')   
         break;

      if (strncmp(line, "numIndividuals", strlen("numIndividuals")) == 0)
      {
         sscanf(line+(strlen("numIndividuals")), "%d", &iValue);
         cerr << "Setting numIndividuals to supplied value " << iValue << endl;
         p.setNumIndividuals(iValue); 
      }
      else if (strncmp(line, "depthLimit", strlen("depthLimit")) == 0)
      {
         sscanf(line+(strlen("depthLimit")), "%d", &iValue);
         cerr << "Setting depthLimit to supplied value " << iValue << endl;
         p.setDepthLimit(iValue); 
      }
      else if (strncmp(line, "initdepthLimit", strlen("initdepthLimit")) == 0)
      {
         sscanf(line+(strlen("initdepthLimit")), "%d", &iValue);
         cerr << "Setting initdepthLimit to supplied value " << iValue << endl;
         p.setinitDepthLimit(iValue); 
      }
      else if (strncmp(line, "minDepth", strlen("minDepth")) == 0)
      {
         sscanf(line+(strlen("minDepth")), "%d", &iValue);
         cerr << "Setting minDepth to supplied value " << iValue << endl;
         p.setMinDepth(iValue); 
      }
      else if (strncmp(line, "returnType", strlen("returnType")) == 0)
      {
         sscanf(line+(strlen("returnType")), "%d", &iValue);
         cerr << "Setting returnType to supplied value " << iValue << endl;
         p.setReturnType(iValue); 
      }
      else if (strncmp(line, "mutationRate", strlen("mutationRate")) == 0)
      {
         sscanf(line+(strlen("mutationRate")), "%lf", &dValue);
         cerr << "Setting mutationRate to supplied value " << dValue << endl;
         p.setMutationRate(dValue); 
      }
      else if (strncmp(line, "crossoverRate", strlen("crossoverRate")) == 0)
      {
         sscanf(line+(strlen("crossoverRate")), "%lf", &dValue);
         cerr << "Setting crossoverRate to supplied value " << dValue << endl;
         p.setCrossoverRate(dValue); 
      }
      else if (strncmp(line, "elitismRate", strlen("elitismRate")) == 0)
      {
         sscanf(line+(strlen("elitismRate")), "%lf", &dValue);
         cerr << "Setting elitismRate to supplied value " << dValue << endl;
         p.setElitismRate(dValue); 
      }
      else if (strncmp(line, "numObjectives", strlen("numObjectives")) == 0)
      {
         sscanf(line+(strlen("numObjectives")), "%lf", &dValue);
         cerr << "Setting elitismRate to supplied value " << dValue << endl;
         p.config->numObjectives = dValue;
      }
      else
      {
         cerr << "Ignoring line " << line << endl;
      }
   }

   while (true)
   {
      if (individual >= p.numIndividuals)
         break;

      if (!(i.getline(line, MAXLINE, '\n')))
      {
         if (i.eof() || i.bad())
            break;

         i.clear();
      }

      if (line[0] == '#')
      {
         individual++;
		 objIndex=0;
         continue;
      }

      if (strncmp(line, "Individual", strlen("Individual")) == 0)
      {
         sscanf(line+(strlen("Individual")), "%d", &iValue);
         cerr << "Reading individual " << iValue 
              << " into slot " << individual << endl;
      }
      else if (strncmp(line, "Fitness", strlen("Fitness")) == 0)
      {
         sscanf(line+(strlen("Fitness")), "%lf", &dValue);
         cerr << "Setting fitness to " << dValue << endl;
         p.pop[individual]->setObjectiveValue(objIndex++, dValue);
         //p.pop[individual]->setFitness(dValue);
      }
	  else if (strncmp(line, "Range", strlen("Range")) == 0) 	/* Added by Feng/Geoff Lee 3/12/2012. Used for Dynamic Selection coding.  */
		{
			sscanf(line+(strlen("Range")), "%s", range);
			// cerr << "Setting range to " << range << endl;
			p.pop[individual]->setRange(range);
		}	  
      else if (strncmp(line, "Program", strlen("Program")) == 0)
      {
         programString = line + strlen("Program");

         if ((signed)i.gcount() != MAXLINE && strlen(line) == MAXLINE-1)
         {
            do 
            {
               i.get(tmpChar);
               programString.append(1, tmpChar);
            } while (tmpChar != '\n');
         }

         p.pop[individual]->parseProgram(programString);          
      }
      else
      {
         cerr << "Ignoring line " << line << endl;
      }
   }

   if (individual < p.getNumIndividuals()-1)
   {
      cerr << "**** Warning ****" << endl
           << "Number of programs in population file is less than " 
           << p.getNumIndividuals() << endl;
   }

   return i;
}

//TODO: Not sure if these should be modified.
void EMOPopulation::writeToFile()
{
   char filename[50];
   ofstream outputFile;

   sprintf(filename, "gen_%06d.gen", generationNumber);
   outputFile.open(filename);
  
   if (outputFile.good()) 
      outputFile << *this;
   else
      throw string("Population::writeToFile Error could not open file");

   outputFile.close();

   if (useCompression)
      compressFile(filename);
	  
   sprintf(filename, "gen_latest.gen"); 
   outputFile.open(filename);
  
   if (outputFile.good()) 
      outputFile << *this;
   else
      throw string("Population::writeToFile Error could not open file");

   outputFile.close();   	  
}

void EMOPopulation::readFromFile(char *fileName)
{
   ifstream inputFile;

   inputFile.open(fileName);

   if (inputFile.good())
      inputFile >> *this;
   else
      throw string("Population::readFromFile Error could not open file");

   inputFile.close();
}

void EMOPopulation::setMutationProbability(double m){
    mutationProbability = m;
}

double EMOPopulation::getMutationProbability(){
    return mutationProbability;
}
