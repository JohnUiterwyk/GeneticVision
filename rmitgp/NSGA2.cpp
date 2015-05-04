
#include <cstdlib>
#include "NSGA2.h"
#include "GeneticProgram.h"
#include "list.h"

int NSGA2::checkDominance(GeneticProgram *a, GeneticProgram *b, int numObj){
    int i;
    int flag1;
    int flag2;
	int flag3; //Flag 3 added by Geoff Lee 6/3/2013 - used to detect duplicates. Removes subsequent duplicates from the elite category, always keeps the first. Should be changed to select a random member instead to preserve exploration.
    flag1 = 0;
    flag2 = 0;
    flag3 = 0;
	
    for (i = 0 ; i < numObj ; i++){
        if (a->getObjectiveValue(i) < b->getObjectiveValue(i)){
            flag1 = 1;
        }
        else{
            if (a->getObjectiveValue(i) > b->getObjectiveValue(i)){
                flag2 = 1;
            }
			else flag3++;
        }
    }


    if (flag1 == 1 && flag2 == 0){
        return (1);
    }else{
        if (flag1 == 0 && flag2 == 1 || flag3 == numObj){
            return (-1);
        }else{
            return (0);
        }
    }
}

void NSGA2::assignRankAndCrowdingDistance (GeneticProgram **new_pop, int numObj, int popsize){
    int flag;
    int i;
    int end;
    int front_size;
    int rank=1;
    list *orig;
    list *cur;
    list *temp1, *temp2;
    orig = (list *)malloc(sizeof(list));
    cur = (list *)malloc(sizeof(list));
    front_size = 0;
    orig->index = -1;
    orig->parent = NULL;
    orig->child = NULL;
    cur->index = -1;
    cur->parent = NULL;
    cur->child = NULL;
    temp1 = orig;
    for (i=0; i<popsize; i++)
    {
        insert (temp1,i);
        temp1 = temp1->child;
    }
    do
    {
        if (orig->child->child == NULL)
        {
            new_pop[orig->child->index]->setRank(rank);
            new_pop[orig->child->index]->setCrowdingDist(INF);
            break;
        }
        temp1 = orig->child;
        insert (cur, temp1->index);
        front_size = 1;
        temp2 = cur->child;
        temp1 = del (temp1);
        temp1 = temp1->child;
        do
        {
            temp2 = cur->child;
            do
            {
                end = 0;
                flag = checkDominance (new_pop[temp1->index], new_pop[temp2->index], numObj);
                if (flag == 1)
                {
                    insert (orig, temp2->index);
                    temp2 = del (temp2);
                    front_size--;
                    temp2 = temp2->child;
                }
                if (flag == 0)
                {
                    temp2 = temp2->child;
                }
                if (flag == -1)
                {
                    end = 1;
                }
            }
            while (end!=1 && temp2!=NULL);
            if (flag == 0 || flag == 1)
            {
                insert (cur, temp1->index);
                front_size++;
                temp1 = del (temp1);
            }
            temp1 = temp1->child;
        }
        while (temp1 != NULL);
        temp2 = cur->child;
        do
        {
            new_pop[temp2->index]->setRank(rank);
            temp2 = temp2->child;
        }
        while (temp2 != NULL);
        NSGA2::assignCrowdingDistanceList (new_pop, cur->child, front_size, numObj);
        temp2 = cur->child;
        do
        {
            temp2 = del (temp2);
            temp2 = temp2->child;
        }
        while (cur->child !=NULL);
        rank+=1;
    }
    while (orig->child!=NULL);
    free (orig);
    free (cur);
    return;

}

void NSGA2::fillNondominatedSort (GeneticProgram **mixed_pop, GeneticProgram **new_pop, int popsize, int nobj){
    int flag;
    int i, j;
    int end;
    int front_size;
    int archieve_size;
    int rank=1;
    list *pool;
    list *elite;
    list *temp1, *temp2;
    pool = (list *)malloc(sizeof(list));
    elite = (list *)malloc(sizeof(list));
    front_size = 0;
    archieve_size=0;
    pool->index = -1;
    pool->parent = NULL;
    pool->child = NULL;
    elite->index = -1;
    elite->parent = NULL;
    elite->child = NULL;
    temp1 = pool;
    for (i=0; i<2*popsize; i++)
    {
        insert (temp1,i);
        temp1 = temp1->child;
    }
    i=0;
    do
    {
        temp1 = pool->child;
        insert (elite, temp1->index);
        front_size = 1;
        temp2 = elite->child;
        temp1 = del (temp1);
        temp1 = temp1->child;
        do
        {
            temp2 = elite->child;
            if (temp1==NULL)
            {
                break;
            }
            do
            {
                end = 0;
                flag = checkDominance (mixed_pop[temp1->index], mixed_pop[temp2->index], nobj);
                if (flag == 1)
                {
                    insert (pool, temp2->index);
                    temp2 = del (temp2);
                    front_size--;
                    temp2 = temp2->child;
                }
                if (flag == 0)
                {
                    temp2 = temp2->child;
                }
                if (flag == -1)
                {
                    end = 1;
                }
            }
            while (end!=1 && temp2!=NULL);
            if (flag == 0 || flag == 1)
            {
                insert (elite, temp1->index);
                front_size++;
                temp1 = del (temp1);
            }
            temp1 = temp1->child;
        }
        while (temp1 != NULL);
        temp2 = elite->child;
        j=i;
        if ( (archieve_size+front_size) <= popsize)
        {
            do
            {
                new_pop[i] = mixed_pop[temp2->index]->copy();
                new_pop[i]->setRank(rank);
                    archieve_size+=1;
                temp2 = temp2->child;
//				if (rank == 1)
//				{cout<< "The elite: "<<i<<": "<<new_pop[i]->getFitness()<<" "<<new_pop[i]->getObjectiveValue(0)<<" "<<new_pop[i]->getObjectiveValue(1)<<endl;}                
				i+=1;
				
            }
            while (temp2 != NULL);
            NSGA2::assignCrowdingDistanceIndices(new_pop, j, i-1, nobj);
            rank+=1;
        }
        else
        {
			//cout<< "Crowding fill :( "<<endl;
            crowdingFill (mixed_pop, new_pop, i, front_size, elite, popsize, nobj);
            archieve_size = popsize;
            for (j=i; j<popsize; j++)
            {
                new_pop[j]->setRank(rank);
            }
        }
        temp2 = elite->child;
        do
        {
            temp2 = del (temp2);
            temp2 = temp2->child;
        }
        while (elite->child !=NULL);
    }
    while (archieve_size < popsize);
    while (pool!=NULL)
    {
        temp1 = pool;
        pool = pool->child;
        free (temp1);
    }
    while (elite!=NULL)
    {
        temp1 = elite;
        elite = elite->child;
        free (temp1);
    }
    return;
}

/* Routine to fill a population with individuals in the decreasing order of crowding distance */
void NSGA2::crowdingFill (GeneticProgram **mixed_pop, GeneticProgram **new_pop, int count, int front_size, list *elite, int popsize, int nobj)
{
    int *dist;
    list *temp;
    int i, j;
    NSGA2::assignCrowdingDistanceList (mixed_pop, elite->child, front_size, nobj);
    dist = (int *)malloc(front_size*sizeof(int));
    temp = elite->child;
    for (j=0; j<front_size; j++)
    {
        dist[j] = temp->index;
        temp = temp->child;
    }
    
    //TODO: quick sort is not implemented
    //quicksort_dist (mixed_pop, dist, front_size);
    for (i=count, j=front_size-1; i<popsize; i++, j--)
    {
        new_pop[i] = mixed_pop[dist[j]]->copy();
    }
    free (dist);
    return;
}

/* Routine to compute crowding distance based on ojbective function values when the population in in the form of a list */
void NSGA2::assignCrowdingDistanceList (GeneticProgram **pop, list *lst, int front_size, int nobj)
{
    int **obj_array;
    int *dist;
    int i, j;
    list *temp;
    temp = lst;
    if (front_size==1)
    {
        pop[lst->index]->setCrowdingDist(INF);
        return;
    }
    if (front_size==2)
    {
        pop[lst->index]->setCrowdingDist(INF);
        pop[lst->child->index]->setCrowdingDist(INF);
        return;
    }
    obj_array = (int **)malloc(nobj*sizeof(int));
    dist = (int *)malloc(front_size*sizeof(int));
    for (i=0; i<nobj; i++)
    {
        obj_array[i] = (int *)malloc(front_size*sizeof(int));
    }
    for (j=0; j<front_size; j++)
    {
        dist[j] = temp->index;
        temp = temp->child;
    }
    NSGA2::assignCrowdingDistance (pop, dist, obj_array, front_size, nobj);
    free (dist);
    for (i=0; i<nobj; i++)
    {
        free (obj_array[i]);
    }
    free (obj_array);
    return;
}

/* Routine to compute crowding distance based on objective function values when the population in in the form of an array */
void NSGA2::assignCrowdingDistanceIndices (GeneticProgram **pop, int c1, int c2, int nobj)
{
    int **obj_array;
    int *dist;
    int i, j;
    int front_size;
    front_size = c2-c1+1;
    if (front_size==1)
    {
        pop[c1]->setCrowdingDist(INF);
        return;
    }
    if (front_size==2)
    {
        pop[c1]->setCrowdingDist(INF);
        pop[c2]->setCrowdingDist(INF);
        return;
    }
    obj_array = (int **)malloc(nobj*sizeof(int));
    dist = (int *)malloc(front_size*sizeof(int));
    for (i=0; i<nobj; i++)
    {
        obj_array[i] = (int *)malloc(front_size*sizeof(int));
    }
    for (j=0; j<front_size; j++)
    {
        dist[j] = c1++;
    }
    NSGA2::assignCrowdingDistance (pop, dist, obj_array, front_size, nobj);
    free (dist);
    for (i=0; i<nobj; i++)
    {
        free (obj_array[i]);
    }
    free (obj_array);
    return;
}

/* Routine to compute crowding distances */
void NSGA2::assignCrowdingDistance (GeneticProgram **pop, int *dist, int **obj_array, int front_size, int nobj){
    int i, j;
    for (i=0; i<nobj; i++)
    {
        for (j=0; j<front_size; j++)
        {
            obj_array[i][j] = dist[j];
        }
        //TODO
        //quicksort_front_obj (pop, i, obj_array[i], front_size);
    }
    for (j=0; j<front_size; j++)
    {
        pop[dist[j]]->setCrowdingDist(0.0);
    }
    for (i=0; i<nobj; i++)
    {
        pop[obj_array[i][0]]->setCrowdingDist(INF);
    }
    for (i=0; i<nobj; i++)
    {
        for (j=1; j<front_size-1; j++)
        {
            if (pop[obj_array[i][j]]->getCrowdingDist() != INF)
            {
                if (pop[obj_array[i][front_size-1]]->getObjectiveValue(i) == pop[obj_array[i][0]]->getObjectiveValue(i))
                {
                    int temp = pop[obj_array[i][j]]->getCrowdingDist();
                    pop[obj_array[i][j]]->setCrowdingDist(temp += 0.0);
                }
                else
                {
                    int temp = pop[obj_array[i][j]]->getCrowdingDist();
                    pop[obj_array[i][j]]->setCrowdingDist(temp + (pop[obj_array[i][j+1]]->getObjectiveValue(i) - pop[obj_array[i][j-1]]->getObjectiveValue(i))/(pop[obj_array[i][front_size-1]]->getObjectiveValue(i) - pop[obj_array[i][0]]->getObjectiveValue(i)));
                }
            }
        }
    }
    for (j=0; j<front_size; j++)
    {
        if (pop[dist[j]]->getCrowdingDist() != INF)
        {
            pop[dist[j]]->setCrowdingDist((pop[dist[j]]->getCrowdingDist())/nobj);
        }
    }
    return;
}
