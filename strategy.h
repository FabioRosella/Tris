// strategy.h 

#include<malloc.h>

//Raccolta delle funzioni strategia per la cpu, con le 3 diverse difficoltà

//Cella libera

struct nodostrategy{
    int cell;
    struct nodostrategy * next; 
};

struct strategylist{
    struct nodostrategy * head;
    int elements;      //numero celle rimanenti libere
    struct nodostrategy * tail;
};

//Inizializza la strategia easy

struct strategylist InizializeEasy(){

    struct strategylist strategy;
    int i=0;
    strategy.head = malloc(sizeof(struct nodostrategy));
    strategy.tail = strategy.head;
    strategy.tail->next = NULL;
    strategy.tail->cell = 1;

    for(i=2; i<=9; i++){
        strategy.tail->next = malloc(sizeof(struct nodostrategy));
        strategy.tail = strategy.tail->next;
        strategy.tail->next = NULL;
        strategy.tail->cell = i;
    }

    return strategy;
}

//Elimina un nodo dalla lista strategyeasy

void DeleteNode(struct strategylist * strategy,int key){

    struct nodostrategy * node = strategy->head;
    struct nodostrategy * freenode = NULL;

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