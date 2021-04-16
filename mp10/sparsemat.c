#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>





sp_tuples * load_tuples(char* input_file)
{
    FILE *input;
   
    input = fopen(input_file, "r");
    if (input == NULL) {
        return NULL;
    }

    int rows, columns;
    fscanf(input, "%d %d", &rows, &columns);
   
    sp_tuples *myTuples = (sp_tuples *) malloc(sizeof(sp_tuples));
    myTuples->m = rows;
    myTuples->n = columns;
    myTuples->nz = 0;
    myTuples->tuples_head = NULL;
   
    int r, c;
    double val;
   

    while (fscanf(input, "%d %d %lf", &r, &c, &val) != EOF) {
        if (val != 0) {
            set_tuples(myTuples, r, c, val);
        } else if (val == 0 && gv_tuples(myTuples, r, c) != 0) {
            set_tuples(myTuples, r, c, val);
        }
           
        //printf("%d %d %lf", r, c, val);
        //fgetc(input);
    }
   
   
    fclose(input);
    return myTuples;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
    sp_tuples_node *current;

    for(current = mat_t->tuples_head; current != NULL; current=current->next){
        if(current->row == row && current->col == col){
            return current->value;
        }
    }

    return 0;
}


void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{  
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
   
    int found = 0;
    if (mat_t->tuples_head->row == row && mat_t->tuples_head->col == col) {
        if (value == 0) {
            mat_t->tuples_head = mat_t->tuples_head->next;
            mat_t->nz -= 1;
            free(mat_t->tuples_head);
        } else {
            mat_t->tuples_head->value = value;
        }
        found = 1;
        return;
    }
   
   
    sp_tuples_node *current = mat_t->tuples_head;

    for (current = mat_t->tuples_head; current->next != NULL; current=current->next) {
        
        sp_tuples_node *nextNode = current->next;
        if (nextNode->row == row && nextNode->col == col) {
            if (value == 0) {
                if (nextNode->next != NULL)
                    current->next = nextNode->next;
                else
                    current->next = NULL;
                mat_t->nz -= 1;
                free(nextNode);
                return;
            } else {
                nextNode->value = value;
                return;
            }
            found = 1;
            //return;
        }
    }
   
    if (!found) {
        if (value == 0) {
            return;
        }
        int startIndex = mat_t->tuples_head->row * mat_t->n + mat_t->tuples_head->col;
        int placeIndex = row * mat_t->n + col;
        if(placeIndex < startIndex) {
            sp_tuples_node * newNode = malloc(sizeof(sp_tuples_node));
            newNode->row = row;
            newNode->col = col;
            newNode->value = value;
            newNode->next = mat_t->tuples_head;
            mat_t->tuples_head = newNode;
            mat_t->nz += 1;
            return;
        }
       
        for (current = mat_t->tuples_head; current != NULL; current=current->next) { //check this condition
           
            sp_tuples_node *nextNode = current->next;
           
            
            if (nextNode != NULL) {
               
                int newIndex = nextNode->row * mat_t->n + nextNode->col;
               
               
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
    
    FILE *output = fopen(file_name, "w");
    fprintf(output, "%d %d\n", mat_t->m, mat_t->n);

   sp_tuples_node *current = mat_t->tuples_head;
    for(current = mat_t->tuples_head; current != NULL; current=current->next){
        fprintf(output, "%d %d %lf\n", current->row, current->col, current->value);
    }

    fclose(output);
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
    
    sp_tuples *retmat = (sp_tuples*)malloc(sizeof(sp_tuples));
    retmat->m = matA->m;
    retmat->n = matA->n;
    retmat->nz = 0;

    sp_tuples_node *current;
    for(current = matA->tuples_head; current != NULL; current=current->next){
        set_tuples(retmat, current->row, current->col, current->value);
    } 
    
    for(current = matB->tuples_head; current != NULL; current=current->next){
        set_tuples(retmat, current->row, current->col, current->value + gv_tuples(retmat, current->row, current->col));
    } 
    
	return retmat;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    
    return 0;
}


	
void destroy_tuples(sp_tuples * mat_t){
    
    sp_tuples_node *current = mat_t->tuples_head;
    for(current = mat_t->tuples_head; current != NULL; current=current->next){
        free(current);
    }    

    free(mat_t);
    return;
}  







