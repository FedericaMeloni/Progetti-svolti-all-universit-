#include "macro.h"


/**
 * Funzione che permette di ottenere le coordinate iniziali delle navicelle a seconda del indice e delle dimensioni schermo 
 * @param indice indica l'indice della navicella
*/
Coordinate coordinateIniziali(int indice)
{
    Coordinate defaultpos; //posizione di default

    int i;

    i = indice / MAX_NAV_COL;
    defaultpos.x = MAXX - (NAV2_SPESSORE * 2) * (i + BORDO);
    i = indice % MAX_NAV_COL;
    defaultpos.y = 8 + ((MAXY / 4) * i);

    return defaultpos;
}


/**
 * Procedura che gestisce l'inizializzazione del missile nemico in una posizione iniziale start e il suo avanzamento
 * @param indice indica l'indice della navicella
*/
void missileNemico (int pipeout, Coordinate start)
{
    int i;
    Object missile;

    missile.pos.x = start.x - NAV_SPESSORE - 1;
    missile.pos.y = start.y + NAV_ALTEZZA / 2;
    missile.id = ID_MISSILE_NAVICELLA;
    missile.pid = getpid(); //identificativo
    missile.vite = 1;

//il missile avanza dinchè le vite sono maggiori di 0
    while (missile.vite > 0)
    {
        missile.old_pos = missile.pos;
        missile.pos.x --;
        usleep(MISSILE_DELAY);
        write(pipeout, &missile, sizeof(missile)); //scrive missile nella pipe
    }
    exit(1);
}


/**
 * Procedura che gestisce i movimenti dell'astronave e la creazione dei missili navicella
 * @param pid_navicella 
 * @param n_navicella indice della navicella
*/
void nemico(int pipeout, pid_t pid_navicella, int n_navicella)
{
    int movimento=2; //tipologia di movimento iniziale ovvero in avanti

    int status;
    Object navicellaLev1; //nemico

    navicellaLev1.pos = coordinateIniziali(n_navicella); //coordinate iniziali navicella
    navicellaLev1.old_pos = navicellaLev1.pos;
    navicellaLev1.pid = getpid(); //identificatore processo
    navicellaLev1.id = ID_NAVLEV1;
    navicellaLev1.indice = n_navicella; //indice navicella
   

    // Comunico a check la struttura della navicella
    write(pipeout, &navicellaLev1, sizeof(navicellaLev1));

    do {
        navicellaLev1.old_pos = navicellaLev1.pos; //vecchia posizione
      
        switch (movimento) {
            case 0:  //verso l'alto
              	movimento=1;		
                navicellaLev1.pos.y-=3;
                break;

            case 1: //verso il basso
                navicellaLev1.pos.y+=3;
    		    movimento=3;	
                break;

            case 2: //solo in avanti
                navicellaLev1.pos.x-=4;
        		movimento=0;
                break;

            case 3: // in avanti
		        navicellaLev1.pos.x-=4;
		        movimento=4;	
		        break;
	
	        case 4://verso il basso
		        navicellaLev1.pos.y+=3;
		        movimento=5;
	            break;	

	        case 5: //verso l'alto
		        navicellaLev1.pos.y-=3;
		        movimento=2;	
                break;
        }

        // Generazione missili: vengono lanciati se il modulo con 5 del numero casuale meno indice della navicella è pari a 0
        if ((rand() - navicellaLev1.indice) % 5 == 0) {
            switch (fork()) {
                case -1:
                    perror("Errore nell'esecuzione della fork missile");
                    _exit(1);

                case 0:
                    missileNemico(pipeout, navicellaLev1.pos);
                    break;
            }
        }

        waitpid(-1, &status, WNOHANG);

        /* Comunico le coordinate correnti al processo padre */
        write(pipeout, &navicellaLev1, sizeof(navicellaLev1));
        usleep(NAV_DELAY);
    } while (true);

    exit(0);
}



