#include<stdio.h>
#include<stdlib.h>
#include "strategy.h"

//Definizione per i tipi della matrice 

#define bool char
#define true 'X'
#define false 'O'
#define empty ' '

#define strategy int
#define easy 0
#define medium 1
#define hard 2

//Definizione clear per diversi os

#ifdef WIN32
#define CLEAR() (system("cls"))
#else
#define CLEAR() (system("clear"))
#endif

//Dichiarazione tipo giocatore

struct giocatore{
    char name[10];
    int punteggio;
    bool segno;
};

//Dichiarazione Prototipi

void PrintGrid(bool grid[3][3]);
void InitGrid(bool grid[3][3]);
void StartGame(bool grid[3][3],struct giocatore * player1,struct giocatore * player2);
void StartGameCpu(bool grid[3][3],struct giocatore * player1,struct giocatore * player2,strategy s);
int InsertInGrid(bool grid[3][3],bool symbol);
int InsertInGridCpu(bool grid[3][3],bool symbol,int cell);
bool CheckWin(bool grid[3][3],int insertcell);
void Menu();
void Menu1vs1();
void Menu1vsCpu();
void InsertDatPlayer(struct giocatore * player,bool sign);
void PrintPlayer(struct giocatore player1,struct giocatore player2);
void ClearBuffer();
int EasyStrategy(struct strategylist strat);

//MAIN -- Gioco del tris semplice con possibilità di segnare il punteggio e giocare più partite

int main(){

    bool grid[3][3];
    char response='0';
    int cbuffer;
    char respo='0';

    do{
        Menu();
        scanf("%c",&response);

        switch(response){
            case '1':{
                //Inserisci i dati per i giocatori
                struct giocatore player1;
                struct giocatore player2;
                InsertDatPlayer(&player1,true);
                InsertDatPlayer(&player2,false);
                ClearBuffer();
                int turn=1;
                do{
                    Menu1vs1();
                    scanf("%c",&respo);

                    switch(respo){
                        case '1':{
                            InitGrid(grid);
                            PrintGrid(grid);

                            if(turn % 2 == 1)
                                StartGame(grid,&player1,&player2);
                            else
                                StartGame(grid,&player2,&player1);

                            ClearBuffer();
                            turn ++;
                            break;
                        }
                        case '2':{
                            PrintPlayer(player1,player2);
                            ClearBuffer();
                            break;
                        }
                        case '3':
                            break;
                        default:{
                            printf("Hai inserito un valore non valido\nPremere invio per continuare: \n");
                            scanf("%c",&respo);
                            ClearBuffer();
                            break;
                        }
                    }
                }while(respo != '3');

                ClearBuffer();
                break;
            }
            case '2':
            {
                struct giocatore player1;
                InsertDatPlayer(&player1,true);
                struct giocatore cpu;
                cpu.name[0] = 'C';
                cpu.name[1] = 'p';
                cpu.name[2] = 'u';
                cpu.name[3] = '\0';
                cpu.punteggio = 0;
                cpu.segno = false;
                int turn = 1;
                ClearBuffer();
                do{
                    Menu1vsCpu();
                    scanf("%c", &respo);

                    switch(respo){
                        case '1':{
                            InitGrid(grid);
                            PrintGrid(grid);

                            if(turn % 2 == 1)
                                StartGameCpu(grid,&player1,&cpu,easy);
                            else
                                StartGameCpu(grid,&cpu,&player1,easy);

                            ClearBuffer();
                            turn ++;

                            break;
                        }
                        case '2':{
                            PrintPlayer(player1,cpu);
                            ClearBuffer();
                            break;
                        }
                        case '3':
                            break;
                        default:{
                            printf("Hai inserito un valore non valido\nPremere invio per continuare: \n");
                            scanf("%c",&respo);
                            ClearBuffer();
                            break;
                        }
                    }
                }while(respo != '3');
                ClearBuffer();
                break;
            }
            case '3':
                break;
            default:{
                printf("Hai inserito un valore non valido\nPremere invio per continuare: \n");
                scanf("%c",&response);
                ClearBuffer();
                break;
            }
        }

    }while(response != '3');


    return 0;
}

//Prende in input la griglia e permette di stamparla in output 

void PrintGrid(bool grid[3][3]){
    int i,j;
    CLEAR();

    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            if(j == 2){
                printf(" %c \n", grid[i][j]);
            }
            else{
                printf(" %c |", grid[i][j]);
            }
        }
        if(i != 2){
            for(j=0; j<11; j++){
                printf("-");
            }
        }
        printf("\n");
    }
}

//Prende in input la griglia e la inizializza con tutte le celle vuote, pronta per iniziare a giocare

void InitGrid(bool grid[3][3]){
    int i,j;

    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            grid[i][j] = empty;
        }
    }
}

// Funzione che starta la partita nella versione 1 vs 1

void StartGame(bool grid[3][3],struct giocatore * player1,struct giocatore * player2){
    int exit=0;
    int count=1;
    int insertcell=0;
    bool result=empty;
    char respos;
    int cbuffer;

    while(exit==0){
        if(count % 2 == 0)
        {
            printf("Turno di %s\n",(*player2).name);
            insertcell = InsertInGrid(grid,(*player2).segno);
        }
        else   
        {
            printf("Turno di %s\n",(*player1).name);
            insertcell = InsertInGrid(grid,(*player1).segno);
        }
        PrintGrid(grid);
        count ++;
        if(count > 5){
            result = CheckWin(grid,insertcell);
            if(result == (*player1).segno)
            {
                ClearBuffer();
                printf("\nVITTORIA : %s Vince\nPremere un pulsante per continuare: \n",(*player1).name);
                (*player1).punteggio ++;
                scanf("%c",&respos);
                return;
            }
            if(result == (*player2).segno)
            {
                ClearBuffer();
                printf("\nVITTORIA : %s Vince\nPremere un pulsante per continuare: \n", (*player2).name);
                (*player2).punteggio ++;
                scanf("%c",&respos);
                return;
            }
            if(count == 10){
                ClearBuffer();
                printf("PAREGGIO\nPremere un pulsante per continuare: \n");
                scanf("%c",&respos);
                return;
            }
        }
    }
}

// Funzione che starta la partita nella versione 1 vs CPU

void StartGameCpu(bool grid[3][3],struct giocatore * player1,struct giocatore * player2,strategy s){
    int exit=0;
    int count=1;
    int insertcell=0;
    bool result=empty;
    char respos;
    int cbuffer;
    struct strategylist strat = Inizialize();

    while(exit==0){
        if(count % 2 == 0)
        {
            printf("Turno di %s\n",(*player2).name);
            if((*player2).name[0] == 'C' && (*player2).name[1] == 'p' && (*player2).name[2] == 'u'){
                insertcell = EasyStrategy(strat);
                insertcell = InsertInGridCpu(grid,(*player2).segno,insertcell);
                DeleteNode(&strat,insertcell);
            }
            else{
                insertcell = InsertInGrid(grid,(*player2).segno);
                DeleteNode(&strat,insertcell);
            }
        }
        else   
        {
            printf("Turno di %s\n",(*player1).name);
            if((*player1).name[0] == 'C' && (*player1).name[1] == 'p' && (*player1).name[2] == 'u'){
                insertcell = EasyStrategy(strat);
                insertcell = InsertInGridCpu(grid,(*player1).segno,insertcell);
                DeleteNode(&strat,insertcell);
            }
            else{
                insertcell = InsertInGrid(grid,(*player1).segno);
                DeleteNode(&strat,insertcell);
            }
        }
        PrintGrid(grid);
        count ++;
        if(count > 5){
            result = CheckWin(grid,insertcell);
            if(result == (*player1).segno)
            {
                ClearBuffer();
                printf("\nVITTORIA : %s Vince\nPremere un pulsante per continuare: \n",(*player1).name);
                (*player1).punteggio ++;
                scanf("%c",&respos);
                return;
            }
            if(result == (*player2).segno)
            {
                ClearBuffer();
                printf("\nVITTORIA : %s Vince\nPremere un pulsante per continuare: \n", (*player2).name);
                (*player2).punteggio ++;
                scanf("%c",&respos);
                return;
            }
            if(count == 10){
                ClearBuffer();
                printf("PAREGGIO\nPremere un pulsante per continuare: \n");
                scanf("%c",&respos);
                return;
            }
        }
    }
}

//Inserisce un segno nella griglia del tris scelto da un giocatore

int InsertInGrid(bool grid[3][3],bool symbol){
    int cell=1;
    char c;
    int cbuffer;

    do{
        if(cell < 1 || cell > 9)
        {
            if(cell == 1002)
                printf("Errore: cella già occupata devi inserire una nuovo cella! \n");
            else
                printf("Errore: devi inserire un numero corretto per giocare! \n");
        }

        ClearBuffer();

        printf("Inserisci la cella (da 1 a 9 in ordine sx verso dx) : \n");
        scanf("%c:",&c);
        cell = atoi(&c);

        if(cell >= 1 && cell <= 9)
        {
            if(grid[(cell-1)/3][(cell-1)%3] != empty)
                cell = 1002;
        }

    }while(cell < 1 || cell > 9);

    grid[(cell-1)/3][(cell-1)%3] = symbol;

    return cell;
}

//Funzione che prende in input la griglia e la posizione dell'ultimo simbolo inserito
//controlla quindi in base alla posizione del simbolo se è stato effettuato un tris o meno

bool CheckWin(bool grid[3][3],int insertcell){
    int row = (insertcell-1)/3;
    int col = (insertcell-1)%3;

    //CheckRow
    if(grid[row][0] == grid[row][1] && grid[row][1] == grid[row][2])
        return grid[row][0];

    //CheckColum
    if(grid[0][col] == grid[1][col] && grid[0][col] == grid[2][col])
        return grid[0][col];

    //CheckDiagonal
    if(insertcell == 1 || insertcell == 5 || insertcell == 9){
        if(grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
            return grid[0][0];
    }
    if(insertcell == 3 || insertcell == 5 || insertcell == 7){
        if(grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
            return grid[0][2];
    }

    return empty;
}

//Stampa il menu di gioco

void Menu(){

    CLEAR();
    printf("Benvenuti nel gioco del tris !!\n\n");
    printf("1 - Inizia una nuova partita 1 vs 1 \n");
    printf("2 - Inizia una nuova partita 1 vs cpu \n");
    printf("3 - Esci dal gioco \n\n");
    printf("Seleziona un operazione utilizzando il numero\n");

}

//Inserisce i dati del giocatore

void InsertDatPlayer(struct giocatore * player,bool sign){

    CLEAR();
    printf("Inserisci il nome del giocatore\n");
    scanf("%s",(*player).name);
    (*player).punteggio = 0;
    (*player).segno = sign;
}

//Stampa il sottoMenu nella categoria 1 vs 1

void Menu1vs1(){

    CLEAR();
    printf("Benvenuti nella sezione 1 vs 1 !!\n\n");
    printf("1 - Inizia una nuova partita\n");
    printf("2 - Stampa le statistiche dei giocatori \n");
    printf("3 - Torna indietro e termina lo scontro \n\n");
    printf("Seleziona un operazione utilizzando il numero\n");

}

//Stampa le statistiche della partita di 2 giocatori 1 vs 1

void PrintPlayer(struct giocatore player1,struct giocatore player2){

    char respos;

    CLEAR();
    printf("%s ha ottenuto %d vittorie \n", player1.name,player1.punteggio);
    printf("%s ha ottenuto %d vittorie \n\n\n", player2.name,player2.punteggio);

    printf("Premere un pulsante per continuare: \n");
    scanf("%c",&respos);
}

//Stampa il sottomenu per giocare 1 vs Cpu

void Menu1vsCpu(){

    CLEAR();
    printf("Benvenuti nella sezione 1 vs CPU !!\n\n");
    printf("1 - Inizia una nuova partita\n");
    printf("2 - Stampa le statistiche dei giocatori \n");
    printf("3 - Torna indietro e termina lo scontro \n\n");
    printf("Seleziona un operazione utilizzando il numero\n");
}

//Puliscce il buffer di input 

void ClearBuffer(){
    char cbuffer;
    while((cbuffer = getchar()) != '\n' && cbuffer != EOF);
}

//Inserisce nella griglia la mossa effettuata dalla cpu

int InsertInGridCpu(bool grid[3][3],bool symbol,int cell){

    grid[(cell-1)/3][(cell-1)%3] = symbol;

    return cell;
}

//Seleziona la cella vuote dove la cpu vuole compiere la mossa, mossa facile

int EasyStrategy(struct strategylist strat){
    int i=0;
    int number = (rand() % (strat.elements)) + 1;
    printf("%d\n",strat.elements);
    struct nodostrategy * node = strat.head;

    for(i=1; i<number; i++){
        node = node->next;
    }

    return node->cell;
}