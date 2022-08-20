#include "macro.h"



//Sprite astronave, navicella livello 1 e livello2

char spriteAstronave[AST_ALTEZZA][AST_SPESSORE] = {"|->  ",
                                                   "|- > ",
                                                   "|- ->",
                                                   "|- > ",
                                                   "|->  ",};

char spriteNavicella[NAV_ALTEZZA][NAV_SPESSORE] = {" + ",
                                                   "-++",
                                                   " + "};


char spriteNavicellaLev2[NAV2_ALTEZZA][NAV2_SPESSORE] = {
                                                         " -+ -+",
                                                         "-+ -+ " ,
                                                         "      ",
                                                         "-+ -+ ",
                                                         " -+ -+",
                                                         };

//salva le dimensioni dello schermo
                                                     

/**
 * Procedura che inizializza le dimensioni del terminale attraverso la getmaxyx
 * @param maxx dimensione di finestra di gioco 
 * @param maxy dimensione di finestra di gioco 
*/
void screeSize(int *maxx, int *maxy)
{
    int c;
    int HudSpazio; //

    getmaxyx(stdscr, *maxy, *maxx);

    if (*maxx < 99 && *maxy < 39) //manda messaggio d'errore se lo schermo è insufficente
    {
        clear();
        attron(COLOR_PAIR(SCRITTA_PAIR));
        mvprintw(*maxy/ 2, *maxx / 2 - 20, "Dimensione schermo insufficiente");
        mvprintw(*maxy/2 + 1, *maxx / 2 - 20, "Riaprire il gioco con la finestra di almeno 100 x 40");
        refresh();
        getch();
    	endwin();
        exit(1);
    }
    //tengo lo spazio per inserire vita e punteggio a schermo
    HudSpazio = *maxy;
    HudSpazio -= 2;
    *maxy = HudSpazio;
    *maxx;

    clear();
    refresh();
}

/**
 * Procedura di inzio game, stampa la schermata di presentazione e definisce lo spazio dove si muoveranno gli oggetti
 * @param maxx dimensione di finestra di gioco 
 * @param maxy dimensione di finestra di gioco 
*/

void startGame(int maxx, int maxy)
{
    char *scritta1 [6]  = { " ____                         ____        __                _           ",
                            "/ ___| _ __   __ _  ___ ___  |  _ \\  ___ / _| ___ _ __   __| | ___ _ __ ",
                            "\\___ \\| '_ \\ / _` |/ __/ _ \\ | | | |/ _ \\ |_ / _ \\ '_ \\ / _` |/ _ \\ '__|",
                            " ___) | |_) | (_| | (_|  __/ | |_| |  __/  _|  __/ | | | (_| |  __/ |   ",
                            "|____/| .__/ \\__,_|\\___\\___| |____/ \\___|_|  \\___|_| |_|\\__,_|\\___|_|   ",
                            "      |_|                                                               "};


    char *scritta2 [3] = {"_ _  _ ____ ____ ____ ___ ____ ____ _ _  _ ",
                          "| |\\ | [__  |___ |__/  |  |    |  | | |\\ |",
                          "| | \\| ___] |___ |  \\  |  |___ |__| | | \\|"};


    int i, j;


    attron(COLOR_PAIR(SCRITTA_PAIR));

    for(i=0; i<6; i++)
        for(j=0; j < strlen(scritta1[i]); j++)
            mvaddch((maxy/2 - 6) + i, (maxx/2 - (strlen(scritta1[3]) / 2)) + j, scritta1[i][j]);

    refresh();

    sleep(1);

    for (i = 0; i < 3; i++)
        for (j = 0; j < strlen(scritta2[i]); j++)
            mvaddch((maxy / 2) + i, (maxx / 2 - (strlen(scritta2[1]) / 2)) + j, scritta2[i][j]);

    attroff(COLOR_PAIR(SCRITTA_PAIR));
   

    getch();
    clear();
    refresh();		

    //Creazione del box di gioco
    attron(COLOR_PAIR(SCRITTA_PAIR));
    WINDOW *win = newwin(maxy, maxx, 0, 0);
    box(win, ACS_VLINE, ACS_HLINE); 
    attroff(COLOR_PAIR(SCRITTA_PAIR)); 
   
    wrefresh(win);

}

/**
 * Procedura di fine game, riceve il risultato di fine game e stampa l'eventuale messaggio
 * @param GameResult contiene i dati di fine partita
 * @param maxx dimensione di finestra di gioco 
 * @param maxy dimensione di finestra di gioco 
*/
//prende il risultato di fine game e stampa eventuale messaggio
void endGame (GameResult result, int maxx, int maxy)
{


    char *gameover [5] = {"   ____      _      __  __   _____      ___   __     __  _____   ____  ",
                          "  / ___|    / \\    |  \\/  | | ____|    / _ \\  \\ \\   / / | ____| |  _ \\ ",
                          " | |  _    / _ \\   | |\\/| | |  _|     | | | |  \\ \\ / /  |  _|   | |_) |",
                          " | |_| |  / ___ \\  | |  | | | |___    | |_| |   \\ V /   | |___  |  _ < ",
                          "  \\____| /_/   \\_\\ |_|  |_| |_____|    \\___/     \\_/    |_____| |_| \\_\\"};
  
  

    char *winner[5] =  {     " __   __           __        __          ",
                             " \\ \\ / /__  _   _  \\ \\      / /__  _ __  ",
                             "  \\ V / _ \\| | | |  \\ \\ /\\ / / _ \\| '_ \\ ",
                             "   | | (_) | |_| |   \\ V  V / (_) | | | |",
                             "   |_|\\___/ \\__,_|    \\_/\\_/ \\___/|_| |_|"};

   
    clear();

    attron(COLOR_PAIR(SCRITTA_PAIR));

   
    int i, j;

    clear();

    attron(COLOR_PAIR(SCRITTA_PAIR));

    if (result.result == TRUE) { // il giocatore
        for (i = 0; i < 5; i++)
            for (j = 0; j < strlen(winner[i]); j++)
                mvaddch((maxy / 2 - 3) + i, (maxx / 2 - (strlen(winner[1]) / 2)) + j, winner[i][j]);
    }
    else if (result.result == FALSE) { //il giocatore perde
        for (i = 0; i < 5; i++)
            for (j = 0; j < strlen(gameover[i]); j++)
                mvaddch((maxy / 2 - 3 ) + i, (maxx / 2 - (strlen(gameover[1]) / 2)) + j, gameover[i][j]);
    }

    mvprintw((maxy/2) + 7, maxx - strlen(gameover[1]), "Punteggio ottenuto: %d", result.score);

    attroff(COLOR_PAIR(SCRITTA_PAIR));
    refresh();

    getchar();

}

/**
 * Procedura che stampa l'astronave (Quella del player)
 * @param *astronave puntatore che indica l'astronave
*/
void stampaAstronave(Object *astronave)
{
    int i, j;

    //cancella posizione precdente
    attron(COLOR_PAIR(ERASE_PAIR));
    for(i = 0; i < AST_ALTEZZA; i++)
        for(j = 0; j < AST_SPESSORE ; j++)
            mvaddch(astronave->old_pos.y + i, astronave->old_pos.x + j, ' ');
    attroff(COLOR_PAIR(ERASE_PAIR));

    //stampa
    attron(COLOR_PAIR(ASTRONAVE_PAIR));
    for(i = 0; i < AST_ALTEZZA; i++)
        for(j = 0; j < AST_SPESSORE; j++)
            mvaddch(astronave->pos.y + i, astronave->pos.x + j, spriteAstronave[i][j]);
    attroff(COLOR_PAIR(ASTRONAVE_PAIR));

    refresh();

}

/**
 * Procedura che stampa le navicelle nemiche
 * @param *navicella puntatore che indica la navicella
*/
void stampaNavicelle(Object *navicella)
{

    int i, j;
    int color;

    if (navicella->vite == 2)////sceglie il colore in base alle vite rimaste
        color = NAV2_PAIR;
    if (navicella->vite == 1)
        color = NAV1_PAIR;

    if (navicella->vite == 3) { //stampa navicelle primo livello
        //cancella posizione precedente
        attron(COLOR_PAIR(ERASE_PAIR));
        for (i = 0; i < NAV_ALTEZZA; i++)
            for (j = 0; j < NAV_SPESSORE; j++)
                mvaddch(navicella->old_pos.y + i, navicella->old_pos.x + j, ' ');
        attroff(COLOR_PAIR(ERASE_PAIR));

        //stampa
        attron(COLOR_PAIR(NAV1_PAIR));
        for (i = 0; i < NAV_ALTEZZA; i++)
            for (j = 0; j < NAV_SPESSORE; j++)
                mvaddch(navicella->pos.y + i, navicella->pos.x + j, spriteNavicella[i][j]);
        attroff(COLOR_PAIR(NAV1_PAIR));
    }
    else if (navicella->vite == 2 || navicella->vite == 1) // Stampa le navicelle di secondo livello
    {
        //cancella
        attron(COLOR_PAIR(ERASE_PAIR));
        for (i = 0; i < NAV2_ALTEZZA; i++)
            for (j = 0; j < NAV2_SPESSORE; j++)
                mvaddch(navicella->old_pos.y + i, navicella->old_pos.x + j, ' ');
        attroff(COLOR_PAIR(ERASE_PAIR));

        //stampa
        attron(COLOR_PAIR(color));
        for (i = 0; i < NAV2_ALTEZZA; i++)
            for (j = 0; j < NAV2_SPESSORE; j++)
                mvaddch(navicella->pos.y + i, navicella->pos.x + j, spriteNavicellaLev2[i][j]);
        attroff(COLOR_PAIR(color));
    }
    else if (navicella->vite == 0) //navicella è morta e viene cancellata 
    {
        //cancella
        attron(COLOR_PAIR(ERASE_PAIR));
        for (i = 0; i < NAV2_ALTEZZA; i++)
            for (j = 0; j < NAV2_SPESSORE; j++)
                mvaddch(navicella->old_pos.y + i, navicella->old_pos.x + j, ' ');
        attroff(COLOR_PAIR(ERASE_PAIR));

        //Imposto coordinate fuori dall'area di gioco
        navicella->pos.x = -1;
        navicella->pos.y = -1;
    }

    refresh();

}


/**
 * Procedura che stampa i missili a seconda dell'ID
 * @param *missile puntatore che indica il missile
*/
void stampaMissile(Object *missile)
{

    if (missile->id == ID_MISSILE_UP || missile->id == ID_MISSILE_DOWN) //stampa missili astronave
    {
        attron(COLOR_PAIR(ERASE_PAIR));
        mvaddch(missile->old_pos.y, missile->old_pos.x, ' ');

        attron(COLOR_PAIR(MISSILE_PAIR));
        mvaddch(missile->pos.y, missile->pos.x, sprite_missile);
        attroff(COLOR_PAIR(MISSILE_PAIR));
    }
    else if (missile->id == ID_MISSILE_NAVICELLA) //stampa missili nemico
    {
        attron(COLOR_PAIR(ERASE_PAIR));
        mvaddch(missile->old_pos.y, missile->old_pos.x, ' ');

        attron(COLOR_PAIR(MISSILE_NAV_PAIR));
        mvaddch(missile->pos.y, missile->pos.x, sprite_missile);
        attroff(COLOR_PAIR(MISSILE_NAV_PAIR));
    }
}


/**
 * Procedura che cancella il missile
 * @param *missile puntatore che indica il missile
*/
void eraseMissile(Object *missile)
{
    attron(COLOR_PAIR(ERASE_PAIR));
    mvaddch(missile->old_pos.y, missile->old_pos.x, ' ');
    mvaddch(missile->pos.y, missile->pos.x, ' ');
    attroff(COLOR_PAIR(ERASE_PAIR));
    refresh();
}
