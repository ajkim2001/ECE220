#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>


// partners: aahant2, seltzer6
/*
Alex Kim netid:alexk4 4/11/2021
In this program we had to implement 6 functions to create a list of tuples that stores sparse matrices.
For load_tuples, we had to read an input file, scan through it, and then return a matrix of the list of tuples type.
For gv_tuples, we had to find the value at a given row and column by iterating through the matrix.
For set_tuples, we had set a value at a specific row and column. 
We also had to consider all cases where the given location could not already exist and when the value was 0.
For add_tuples, we had to set matrix A to a new matrix and then add the values in matrix B to that matrix while iterating through each element.
For destroy_tuples, we just had to make sure to free all the allocated memory for the given matrix.
*/


sp_tuples * load_tuples(char* input_file)
{
    FILE *input;
   
    input = fopen(input_file, "r"); //open file to read
    if (input == NULL) {
        return NULL;
    }

    int rows, columns;
    fscanf(input, "%d %d", &rows, &columns); //read the rows and cols at beginning
   
    // allocate new memory for myTuples and store row and col and initialize other elements
    sp_tuples *myTuples = (sp_tuples *) malloc(sizeof(sp_tuples));
    myTuples->m = rows; 
    myTuples->n = columns;
    myTuples->nz = 0;
    myTuples->tuples_head = NULL;
   
    int r, c;
    double val;
   
    //scan through input file for all information and call set_tuples to set values.
    while (fscanf(input, "%d %d %lf", &r, &c, &val) != EOF) {
        if (val != 0) {
            set_tuples(myTuples, r, c, val);
        } else if (val == 0 && gv_tuples(myTuples, r, c) != 0) {
            set_tuples(myTuples, r, c, val);
        }
        
    }
   
    // close file and return myTuples
    fclose(input);
    return myTuples;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
    sp_tuples_node *current;
    //create a pointer to current and iterate through matrix to find value at row and col given
    for(current = mat_t->tuples_head; current != NULL; current=current->next){
        if(current->row == row && current->col == col){
            return current->value;
        }
    }

    return 0;
}


void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{   
    //if there is nothing in the matrix, create a new first node by allocating memory
    if (mat_t->tuples_head == NULL) {
        sp_tuples_node * firstNode = (sp_tuples_node *) malloc(sizeof(sp_tuples_node));
        firstNode->row = row;
        firstNode->col = col;
        firstNode->value = value;
        firstNode->next = NULL;
        mat_t->tuples_head = firstNode;
        mat_t->nz = 1;
        return;
    }
    
    int found = 0; //flag that location was found

    //if location found at head
    if (mat_t->tuples_head->row == row && mat_t->tuples_head->col == col) {
        if (value == 0) { //if value 0, delete the node
            mat_t->tuples_head = mat_t->tuples_head->next;
            mat_t->nz -= 1;
            free(mat_t->tuples_head);
        } else { //set value to given value
            mat_t->tuples_head->value = value;
        }
        found = 1;
        return;
    }
   
   
    sp_tuples_node *current = mat_t->tuples_head;
    //iterate through matrix using current pointer
    for (current = mat_t->tuples_head; current->next != NULL; current=current->next) {
        //check if the next node is location we're looking for
        sp_tuples_node *nextNode = current->next;
        if (nextNode->row == row && nextNode->col == col) {
            if (value == 0) { //if value 0, delete the node
                if (nextNode->next != NULL)
                    current->next = nextNode->next;
                else
                    current->next = NULL;
                mat_t->nz -= 1;
                free(nextNode);
                return;
            } else { //set next node's value to given value
                nextNode->value = value;
                return;
            }
            found = 1;
        }
    }
    //if we could not find location
    if (!found) {
        if (value == 0) { //no need to do anything if value 0
            return;
        }
        //create index for start and place we're looking for
        int startIndex = mat_t->tuples_head->row * mat_t->n + mat_t->tuples_head->col;
        int placeIndex = row * mat_t->n + col;
        if(placeIndex < startIndex) { //if we're looking for somewhere before the start, create a new node
            sp_tuples_node * newNode = malloc(sizeof(sp_tuples_node));
            newNode->row = row;
            newNode->col = col;
            newNode->value = value;
            newNode->next = mat_t->tuples_head;
            mat_t->tuples_head = newNode;
            mat_t->nz += 1;
            return;
        }
        //iterate through using current pointer
        for (current = mat_t->tuples_head; current != NULL; current=current->next) { //check this condition
           
            sp_tuples_node *nextNode = current->next;
           
            //if the current node isn't the last in the list
            if (nextNode != NULL) {
               
                int newIndex = nextNode->row * mat_t->n + nextNode->col;
               
                //if we're looking for somewhere before the next node, put new node before
                if(placeIndex < newIndex) {
                    sp_tuples_node * newNode = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
                    newNode->row = row;
                    newNode->col = col;
                    newNode->value = value;
                    newNode->next = nextNode;
                    current->next = newNode;
                    mat_t->nz += 1;
                    return;
                }
               
            }
            else{
                //otherwise, create new node at the end
                sp_tuples_node * newNode = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
                newNode->row = row;
                newNode->col = col;
                newNode->value = value;
                current->next = newNode;
                newNode->next = NULL;
                mat_t->nz += 1;
                return;
               
               
            }
            
              
        }
       
    }
   
    return;
}


void save_tuples(char * file_name, sp_tuples * mat_t)
{
    //open file to write
    FILE *output = fopen(file_name, "w");
    fprintf(output, "%d %d\n", mat_t->m, mat_t->n);
    //iterate through using current pointer to write the entries of matrix
   sp_tuples_node *current = mat_t->tuples_head;
    for(current = mat_t->tuples_head; current != NULL; current=current->next){
        fprintf(output, "%d %d %lf\n", current->row, current->col, current->value);
    }
    //close file 
    fclose(output);
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
    //allocate new memory for new matrix with size of matA
    sp_tuples *retmat = (sp_tuples*)malloc(sizeof(sp_tuples));
    retmat->m = matA->m;
    retmat->n = matA->n;
    retmat->nz = 0;
    //use current to iterate through and set all matA to new retmat
    sp_tuples_node *current;
    for(current = matA->tuples_head; current != NULL; current=current->next){
        set_tuples(retmat, current->row, current->col, current->value);
    } 
    //use current to iterate through and add all values in matB to retmat
    for(current = matB->tuples_head; current != NULL; current=current->next){
        set_tuples(retmat, current->row, current->col, current->value + gv_tuples(retmat, current->row, current->col));
    } 
    //return new sum of matA values and matB values in retmat
	return retmat;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    //set this tuple_head to NULL to return to prevent error
    sp_tuples *tmpTuple = (sp_tuples *) malloc(sizeof(sp_tuples));
    tmpTuple->tuples_head = NULL;
    return tmpTuple;
}


	
void destroy_tuples(sp_tuples * mat_t){
    //use current pointer to increment through matrix and free all nodes
    sp_tuples_node *current = mat_t->tuples_head;
    for(current = mat_t->tuples_head; current != NULL; current=current->next){
        free(current);
    }    
    //free matrix
    free(mat_t);
    return;
}  







