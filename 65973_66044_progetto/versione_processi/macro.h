//Librerie
#include <stdio.h>
#include <curses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include<sys/wait.h>
#include <string.h>
#include <time.h>
#include <locale.h>


//MACRO GENERALI
#define KEY_SPACE ' '
#define BORDO 1
#define MAX_NAV_COL 3 //numero massimo di navicelle per colonna
#define SCORE1 5  //punteggio ottenuto dall'uccisione delle astronavi livello 1 e 2
#define SCORE2 10

//MACRO COLORI
#define BACKGROUND_PAIR 1
#define ERASE_PAIR 2
#define ASTRONAVE_PAIR 3
#define MISSILE_PAIR 4
#define MISSILE_NAV_PAIR 5
#define NAV1_PAIR 6
#define NAV2_PAIR 7
#define SCRITTA_PAIR 8


//MACRO ID
#define ID_ASTRONAVE 'A'
#define ID_MISSILE_UP 'U'
#define ID_MISSILE_DOWN 'D'
#define ID_NAVLEV1 'N'
#define ID_MISSILE_NAVICELLA 'Q'


//MACRO ASTRONAVE
#define AST_ALTEZZA 5
#define AST_SPESSORE 5
#define AST_VITE 3


//MACRO MISSILI
#define DIM_MISSILI 50
#define sprite_missile '-'
#define MISSILE_DELAY 100000 // Ritardo velocità missili
#define SHIFT_VERTICALE 5
#define NAV_DELAY 1000000


//MACRO NAVICELLE
#define NAV_VITE 3
#define NAV_ALTEZZA 3
#define NAV_SPESSORE 3
#define NAV2_ALTEZZA 5
#define NAV2_SPESSORE 6
#define NUM_NAVICELLE 3


// Struttura che rappresenta un posizione
typedef struct {
    int x;
    int y;
} Coordinate;

typedef struct {
    int id;                 // Id dell'oggetto
    pid_t pid;              // Pid del processo proprietario
    Coordinate pos;         // Posizione attuale dell'oggetto
    Coordinate old_pos;     // Posizione precedente dell'oggetto
    int vite;               // Vita dell'oggetto
    int indice;

} Object;

typedef struct {
    bool result;
    int score;
} GameResult; //risultato partita


int MAXY, MAXX; //dimensioni schermo

//CONTROLLI
void startmissiliUP(int  pipeout, Coordinate astronave);
void startmissiliDown(int  pipeout, Coordinate astronave);
void astronave(int pipeout);
GameResult check(int pipein, int maxx, int maxy);


//GRAFICA
void stampaAstronave(Object *astronave);
void stampaNavicelle(Object *navicella);
void stampaMissile(Object *missile);
void eraseMissile(Object *missile);
void screeSize(int *maxx, int *maxy);
void startGame(int maxx, int maxy);
void endGame (GameResult result, int maxx, int maxy);

//NAVICELLE
void missileNemico (int pipeout, Coordinate start);
void nemico(int pipeout,  pid_t pid_navicella, int n_navicella);
Coordinate coordinateIniziali(int indice);
