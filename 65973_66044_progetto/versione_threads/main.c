#include "macro.h"

int main()
{
    int i, status;
    GameResult result; //risultato gioco

    pthread_t thread_astronave;	/*Thread ID dell'astronave*/
	pthread_t thread_nemici[NUM_NAVICELLE];	/*Thread ID dei nemici*/

    Object nemici[NUM_NAVICELLE]; //array nemici

    pthread_mutex_init(&mutex, NULL); //Inizializzazione del mutex

    srand(time(NULL)); // Inizializza generatore di numeri casuali

    
    initscr();				// Inizializza schermo di output
    noecho();				// Imposta modalità della tastiera
    curs_set(0); 	        // Nasconde il cursore
    keypad(stdscr,1);       // Attivo la gestione dei tasti speciali
    cbreak();			    // Disattiva l'input stdin bufferizzato


    //colori carattere-sfondo
    start_color();
    init_pair(BACKGROUND_PAIR,COLOR_BLACK,COLOR_BLACK);
    init_pair(ERASE_PAIR,COLOR_BLACK,COLOR_BLACK);
    init_pair(ASTRONAVE_PAIR,COLOR_YELLOW,COLOR_BLACK);
    init_pair(MISSILE_PAIR ,COLOR_YELLOW,COLOR_BLACK);
    init_pair(MISSILE_NAV_PAIR ,COLOR_RED,COLOR_BLACK);
    init_pair(NAV1_PAIR ,COLOR_RED,COLOR_BLACK);
    init_pair(NAV2_PAIR ,COLOR_YELLOW,COLOR_BLACK);
    init_pair(SCRITTA_PAIR ,COLOR_WHITE,COLOR_BLACK);
    bkgd(COLOR_PAIR(BACKGROUND_PAIR));

    //inizializza dimensione schermo
    screeSize(&MAXX, &MAXY); //controlla che il terminale sia della dimensione giusta
    startGame(MAXX,MAXY);    //schermata inizio gioco
   
   
    //inizializza contatore per inserimento buffer e semaforo
    contatore = 0;
    sem_init(&vuoto, 0, DIM_BUFFER);
    sem_init(&pieno, 0, 0);


    //creazione thread astronave
    pthread_create(&thread_astronave, NULL, &astronave, NULL);


    //creazione thread navicelle
    for (i = 0; i < NUM_NAVICELLE; i++)
    {  
        nemici[i].indice = i; // indice i
        pthread_create(&thread_nemici[i], NULL, &nemico,  &nemici[i]);
       
    }


    result = check( MAXX, MAXY); // il processo padre invoca la funzione di controllo
    

    //termina i processi di nemici e astronave
    pthread_cancel(thread_astronave);
    for(i=0; i < NUM_NAVICELLE; i++) {
         	pthread_cancel(thread_nemici[i]);
    }

    //distruzione mutex e semafori
    sem_destroy(&vuoto);
    sem_destroy(&pieno);
    pthread_mutex_destroy(&mutex);

      
    endGame(result, MAXX, MAXY); //stampa di fine gioco

    endwin();

    return 0;
}
