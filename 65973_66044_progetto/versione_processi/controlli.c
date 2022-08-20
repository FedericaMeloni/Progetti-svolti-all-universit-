#include "macro.h"


/**
 * Procedura che gestisce i movimenti dell'astronave e la creazione dei missili
*/
void astronave (int pipeout)
{
    int c;
    int status0; //status dei missili, up e down
    int status1;
    pid_t pidMissileUp, pidMissileDown; //pid missili
    bool shoot = true; //indica la possibilità di sparare

    Object astronave;
    astronave.id = ID_ASTRONAVE;
    astronave.pid = getpid(); //identifica il processo
    astronave.pos.x = 1;
    astronave.pos.y = MAXY / 2 -2;
    astronave.old_pos = astronave.pos;
   

    // Comunico a check le coordinate di partenza di astronave
    write(pipeout, &astronave, sizeof(astronave));

    // Lettura dei tasti
    while (true)
    {
        astronave.old_pos = astronave.pos; //Coordinate prima dello spostamento

        c = getch();

        if (c == KEY_UP && astronave.pos.y > BORDO)
            astronave.pos.y -= 1;

        if (c == KEY_DOWN && astronave.pos.y < MAXY - AST_ALTEZZA - BORDO)
            astronave.pos.y += 1;

        if (c == KEY_SPACE && shoot) //spara se il giocatore preme il teatso centrale
        {
            switch (pidMissileUp = fork()) { //creazione processi missile
                case -1:
                    perror("Errore nell'esecuzione della fork.");
                    break;

                case 0:
                    startmissiliUP(pipeout, astronave.pos);
                    break;
            }

            switch (pidMissileDown = fork()) {
                case -1:
                    perror("Errore nell'esecuzione della fork.");
                    exit(1);

                case 0:
                    startmissiliDown(pipeout,astronave.pos);
                    break;
            }

            shoot = false;
            status0 = -1;
            status1 = -1;
        }

    //attende muoiano i vecchi processi dei missili
        waitpid(pidMissileUp, &status0, WNOHANG);
        waitpid(pidMissileDown, &status1, WNOHANG);

        if(status0 != -1 && status1 != -1){ // Se entrambi i proiettili sono morti, allora la navicella alleata puo' sparare nuovamente
            shoot = true;
        }

        write(pipeout,&astronave,sizeof(astronave));
    }

}


/**
 * Procedura che gestisce il movimento del missile verso l'alto lanciati dal giocatore
 * @param astronave Coordinate della navicella 
*/
void startmissiliUP(int pipeout, Coordinate astronave)
{
    Object missile;
    //Attributi di default dei missili
    missile.pos.x = astronave.x + AST_SPESSORE;
    missile.pos.y = astronave.y + AST_ALTEZZA / 2;
    missile.vite = 1;
    missile.pid = getpid();

    missile.id = ID_MISSILE_UP;

    while (missile.vite) //finchè il missile ha delle vite vine gestito il suo movimento obliquo verso l'alto
    {
        missile.old_pos = missile.pos;

        missile.pos.x = missile.pos.x + SHIFT_VERTICALE;
        missile.pos.y --;
        usleep(MISSILE_DELAY);
        write(pipeout, &missile, sizeof(missile));
    }
    exit(1);
}

/**
 * Procedura che gestisce il movimento del missile verso il basso lanciati dal giocatore
 * @param astronave Coordinate della navicella 
*/          
void startmissiliDown(int pipeout, Coordinate astronave)
{
    Object missile;
    //Attributi di default dei missili
    missile.pos.x = astronave.x + AST_SPESSORE;
    missile.pos.y = astronave.y + AST_ALTEZZA / 2;
    missile.vite = 1;
    missile.pid = getpid();


    missile.id = ID_MISSILE_DOWN;
        
    while (missile.vite) //finchè il missile ha delle vite vine gestito il suo movimento obliquo verso il basso
    {
        missile.old_pos = missile.pos;
        missile.pos.x = missile.pos.x + SHIFT_VERTICALE;
        missile.pos.y ++;
        usleep(MISSILE_DELAY);
        write(pipeout, &missile, sizeof(missile));
    }
    exit(1);
}



/**
 * Funzione che controlla gli elementi estratti dal buffer e ne gestisce la stampa/collisioni dopo averli identificati tramite ID                                                             
 * @param maxx dimensione di finestra di gioco 
 * @param maxy dimensione di finestra di gioco 
 * @return  ritorna una struct GameResult con risultato del game e punteggio
*/
GameResult check(int pipein, int maxx, int maxy) {
    int i, j, k; //indici
    int vitaPlayer = AST_VITE; //Vita astronave
    int nemiciAlive = NUM_NAVICELLE; //nemici vivi
    int score = 0; //punteggio

    GameResult session;

    //variabili che devono contenere gli elementi da leggere e stampare
    Object valore_letto, astronave;
    Object navicelle[NUM_NAVICELLE];
    Object missileNavicella;
    Object missileUp, missileDown; //missili astronave

    //Variabile gestione array di missili
    int free;
    bool foundFlag = false;
    Object arrayMissili[DIM_MISSILI];


    //Inizializzo le vite delle navicelle di livello 1
    for (i = 0; i < NUM_NAVICELLE; ++i) {
        navicelle[i].vite = 3;
    }
    //Inizializzo array dei missili navicella
    for (i = 0; i < DIM_MISSILI; ++i) {
        arrayMissili[i].vite = 0;
        arrayMissili[i].pid = -2;
    }
    missileUp.pid = -2;
    missileDown.pid = -2;

    do {
        //Legge la pipe
        read(pipein, &valore_letto, sizeof(valore_letto));

    //controlla l'id del valore letto
        switch (valore_letto.id) {

            case ID_ASTRONAVE:  //gestione astronave
                astronave = valore_letto;

                stampaAstronave(&astronave);

                break;

            case ID_MISSILE_UP: //gestione missile UP

                missileUp = valore_letto;

                eraseMissile(&missileUp); //elimina vecchia posizione missile
                stampaMissile(&missileUp);

                // Collisione con i bordi
                if (missileUp.pos.x >= maxx || missileUp.pos.y <= BORDO)
                    missileUp.vite = 0;

                //Collisione con nemici e assegna punteggi
                //se la navicella ha 3 vite da come punti SCORE1 altrimenti SCORE2
                for (i = 0; i < NUM_NAVICELLE; i++) {
                    if (navicelle[i].vite == 3) {
                        for (j = 0; j < NAV_ALTEZZA; j++) {
                            for (k = 0; k < NAV2_SPESSORE; ++k) {
                                if (missileUp.pos.y == navicelle[i].pos.y + j &&
                                    missileUp.pos.x == navicelle[i].pos.x + k) {
                                    missileUp.vite = 0;
                                    navicelle[i].vite--;
                                    score += SCORE1; //punteggio
                                }
                            }

                        }
                    } else {
                        for (j = 0; j < NAV2_ALTEZZA; j++) {
                            for (k = 0; k < NAV2_SPESSORE; ++k) {
                                if (missileUp.pos.y == navicelle[i].pos.y + j &&
                                    missileUp.pos.x == navicelle[i].pos.x + k) {
                                    missileUp.vite = 0;
                                    navicelle[i].vite--;
                                    score += SCORE2; //punteggio
                                }
                            }
                        }
                    }
                }

                //se non ha più vite termina missile up dell'astronave
                if (missileUp.vite == 0) {
                    eraseMissile(&missileUp);
                    kill(missileUp.pid, SIGHUP);
                }

                break;

            case ID_MISSILE_DOWN: //Gestione missile down

                missileDown = valore_letto;

                eraseMissile(&missileDown);//elimina posizioen precedente
                stampaMissile(&missileDown);

                // Collisione con i bordi
                if (missileDown.pos.x >= maxx || missileDown.pos.y == maxy - 2)
                    missileDown.vite = 0;

                //Collisione dei missili della navicella con nemici 
                for (i = 0; i < NUM_NAVICELLE; i++) {
                    if (navicelle[i].vite == 3) {
                        //navicella di primo livello
                        for (j = 0; j < NAV_ALTEZZA; j++) {
                            for (k = 0; k < NAV2_SPESSORE; ++k) {
                                if (missileDown.pos.y == navicelle[i].pos.y + j &&
                                    missileDown.pos.x == navicelle[i].pos.x + k) {
                                    missileDown.vite = 0;
                                    navicelle[i].vite--;
                                }
                            }

                        }
                    } else { //navicelle di secondo livello
                        for (j = 0; j < NAV2_ALTEZZA; j++) {
                            for (k = 0; k < NAV2_SPESSORE; ++k) {
                                if (missileDown.pos.y == navicelle[i].pos.y + j &&
                                    missileDown.pos.x == navicelle[i].pos.x + k) {
                                    missileDown.vite = 0;
                                    navicelle[i].vite--;
                                }
                            }
                        }
                    }
                }

                if (missileDown.vite == 0) { //il missile down non ha più vite e viene eliminato
                    eraseMissile(&missileDown);
                    kill(missileDown.pid, SIGHUP);
                }

                break;

            case ID_NAVLEV1: //Gestione navicelle

                //inizializza posizioni navicelle
                navicelle[valore_letto.indice].pos = valore_letto.pos;
                navicelle[valore_letto.indice].old_pos = valore_letto.old_pos;
                navicelle[valore_letto.indice].pid = valore_letto.pid;
		
	        	stampaNavicelle(&navicelle[valore_letto.indice]);	
                

                //Navicella raggiunge l'astronave oppure il bordo dietro l'astronave, è game over
		        if (navicelle[valore_letto.indice].pos.x < AST_SPESSORE+1 && navicelle[valore_letto.indice].pos.x > 0) {
			        vitaPlayer= 0;
                }

                //Cancello e killa la navicella nemica senza vita
                if (navicelle[valore_letto.indice].vite == 0) {
                    stampaNavicelle(&navicelle[valore_letto.indice]);
                    kill(navicelle[valore_letto.indice].pid, SIGKILL);
                    waitpid(navicelle[valore_letto.indice].pid, NULL, WCONTINUED);
                }
		
                break;


            case ID_MISSILE_NAVICELLA:  //missile nemico

                missileNavicella = valore_letto;

                //Gestione di ricerca e inserimento del missile all'interno dell array
                for (i = 0; i < DIM_MISSILI; i++) {
                    //Controlla se ci sono missili da eliminare e la prima posizione libera
                    if (arrayMissili[i].vite < 1) {
                        arrayMissili[i].pid = -2;
                        free = i;
                    }
                    //Controlla se il missile è gia presente nell'array
                    if (foundFlag == false && arrayMissili[i].pid == missileNavicella.pid) {
                        arrayMissili[i] = missileNavicella;
                        foundFlag = true;
                    }
                }
                //in caso non sia presente lo mette nella prima posizione libera
                if (foundFlag == false)
                    arrayMissili[free] = missileNavicella;

                //Reset dei flag
                foundFlag = false;


                eraseMissile(&missileNavicella); //cancella posizione precedente
                stampaMissile(&missileNavicella);

                //Missile colpisce alleato, decrementa vite
                for (i = 0; i < NUM_NAVICELLE; i++) {
                    if (navicelle[i].vite == 3) { //si controlla la navicella sia in vita

                       //la navicella è di primo livello
                        for (j = 0; j < NAV_ALTEZZA; j++) {
                            for (k = 0; k < NAV2_SPESSORE; ++k) {
                                if (missileNavicella.pos.y == navicelle[i].pos.y + j &&
                                    missileNavicella.pos.x == navicelle[i].pos.x + k) {
                                    missileNavicella.vite --;
                                }
                            }
                        }
                    } else {

                        //la navicella è di secondo livello
                        for (j = 0; j < NAV2_ALTEZZA; j++) {
                            for (k = 0; k < NAV2_SPESSORE; ++k) {
                                if (missileNavicella.pos.y == navicelle[i].pos.y + j &&
                                    missileNavicella.pos.x == navicelle[i].pos.x + k) {
                                    missileNavicella.vite --;
                                }
                            }
                        }
                    }
                }

                //missile raggiunge borbo o vita = 0;
                if (missileNavicella.pos.x <= 1)
                    missileNavicella.vite = 0;

                //missile colpisce l'astronave
                for (i = 0; i < AST_ALTEZZA; i++) {
                    for (j = 0; j < AST_SPESSORE; j++) {
                        if (missileNavicella.pos.y == astronave.pos.y + i &&
                            missileNavicella.pos.x == astronave.pos.x + j) {
                            missileNavicella.vite = 0;
                            vitaPlayer--;
                         
                        }
                    }
                }

                //kill missile
                if (missileNavicella.vite == 0) {
                    //Ricerca dell'array per togliere la vita
                    for (i = 0; i < DIM_MISSILI; i++) {
                        if (arrayMissili[i].pid == missileNavicella.pid && foundFlag == false) {
                            arrayMissili[i].vite--;
                            foundFlag = true;
                        }
                    }
                    eraseMissile(&missileNavicella);
                    kill(missileNavicella.pid, SIGHUP);
                }
                foundFlag = false;

                break;

        }

        //Calcolo nemici in vita 
        for (i = 0; i < NUM_NAVICELLE; i++) {
            if (navicelle[i].vite == 0)
                nemiciAlive--; 
	    	
        }
        if (nemiciAlive > 0) 
            nemiciAlive = NUM_NAVICELLE;


        //Stampo il punteggio
        attron(COLOR_PAIR(SCRITTA_PAIR));
        mvprintw(maxy, 1, "Vita : %d   Punteggio: %d", vitaPlayer, score);
        attroff(COLOR_PAIR(SCRITTA_PAIR));

        refresh(); //aggiorna schermo
    
    } while (vitaPlayer > 0 && nemiciAlive > 0);

    /* Kill dei missili ancora attivi a fine partita */
    kill(missileUp.pid, SIGHUP);
    kill(missileDown.pid, SIGHUP);
    for (i = 0; i < DIM_MISSILI; i++) {
        if (arrayMissili[i].pid != -2)
            kill(arrayMissili[i].pid, SIGHUP);
    }

    //ritorna il punteggio se il giocvatore vince
    if (vitaPlayer > 0) //Giocatore vince
        session.result = true;
    else if (nemiciAlive > 0) //Giocatore perde
        session.result = false;


    session.score = score; //punteggio finale

    return session;
}
