// strategy.h 

#include<malloc.h>

//Raccolta delle funzioni strategia per la cpu, con le 3 diverse difficoltà

//Cella libera

struct nodostrategyeasy{
    int cell;
    struct nodostrategyeasy * next; 
};

struct strategyeasy{
    struct nodostrategyeasy * head;
    int elements;      //numero celle rimanenti libere
    struct nodostrategyeasy * tail;
};

//Inizializza la strategia easy

struct strategyeasy InizializeEasy(){

    struct strategyeasy strategy;
    int i=0;
    strategy.head = malloc(sizeof(struct nodostrategyeasy));
    strategy.tail = strategy.head;
    strategy.tail->next = NULL;
    strategy.tail->cell = 1;

    for(i=2; i<=9; i++){
        strategy.tail->next = malloc(sizeof(struct nodostrategyeasy));
        strategy.tail = strategy.tail->next;
        strategy.tail->next = NULL;
        strategy.tail->cell = i;
    }

    return strategy;
}

//Elimina un nodo dalla lista strategyeasy

void DeleteNode(struct strategyeasy * strategy,int key){

    struct nodostrategyeasy * node = strategy->head;
    struct nodostrategyeasy * freenode = NULL;

    if(strategy->head->cell == key)
    {
        strategy->head = node->next;
        free(node);
        strategy->elements --;
        return;
    }

    while(node->next != NULL){
        if(node->next->cell == key){
            if(node->next->next == NULL)
            {
                strategy->elements --;
                freenode = node->next;
                node->next = NULL;
                free(freenode);
                strategy->tail = node;
                return;
            }
            else{
                strategy->elements --;
                freenode = node->next;
                node->next = node->next->next;
                free(freenode);
                return;
            }
        }

        node = node->next;
    }
}