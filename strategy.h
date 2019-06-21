// strategy.h 

//Raccolta delle funzioni strategia per la cpu, con le 3 diverse difficoltà

//Cella libera

struct nodostrategyeasy{
    int cell;
    struct nodostrategyeasy * next; 
};

struct strategy{
    struct nodostrategyeasy * head;
    int elements;      //numero celle rimanenti libere
};

//Inizializza la strategia easy

struct nodostrategyeasy InizializeEasy(){

    struct nodostrategyeasy * head;
}