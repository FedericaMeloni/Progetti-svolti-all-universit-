#include "macro.h"

int main()
{
    int i, status;
    int pipe_check[2];   //Descrittori pipe

    GameResult result; //risultator gioco

    //pid astronave e nemici
    pid_t pidAst;
    pid_t pid_nemico[NUM_NAVICELLE];

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

    screeSize(&MAXX, &MAXY); //controlla che il terminale sia della dimensione giusta
    startGame(MAXX,MAXY);	 //schermata inizio gioco

    //Creazione pipe
    if(pipe(pipe_check) == -1) {
        perror("Errore nella creazione della pipe!");
        _exit(1);
    }

    switch (pidAst = fork()) {
        case -1:
            perror("Errore nell'esecuzione della fork.");
            _exit(1);

        case 0:
            close(pipe_check[0]);
            astronave(pipe_check[1]); //crea astronave
            break;

        default:
            for (i = 0; i < NUM_NAVICELLE; i++) //crea nemici
            {
                switch(pid_nemico[i] = fork())
                {
                    case -1:
                        perror("Errore nell'esecuzione della fork.");
                        _exit(1);

                    case 0:
                        close(pipe_check[0]);
                        nemico(pipe_check[1], pid_nemico[i], i);
                        exit(0);
                }
            }

            close(pipe_check[1]); //chiusura del descrittore di scrittura
            result = check(pipe_check[0], MAXX, MAXY); // il processo padre invoca la funzione di controllo
    }
    
    //termina i processi di nemici e astronave
    kill(pidAst,SIGKILL);
    waitpid(pidAst, &status, WCONTINUED);
    
    for(i=0; i < NUM_NAVICELLE; i++) {
        kill(pid_nemico[i], SIGKILL);
        waitpid( pid_nemico[i], &status, WCONTINUED);
    }

    endGame(result, MAXX, MAXY); //stampa di fine gioco

    endwin();

    return 0;
}
