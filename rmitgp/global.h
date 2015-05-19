/* This file contains the variable and function declarations */



double eta_c;
double eta_m;

void merge(population *pop1, population *pop2, population *pop3);
void copy_ind (individual *ind1, individual *ind2);

void quicksort_front_obj(population *pop, int objcount, int obj_array[], int obj_array_size);
void q_sort_front_obj(population *pop, int objcount, int obj_array[], int left, int right);
void quicksort_dist(population *pop, int *dist, int front_size);
void q_sort_dist(population *pop, int *dist, int left, int right);
