#include "macro.h"

/**
 * Funzione che permette di ottenere le coordinate iniziali delle navicelle a seconda del indice e delle dimensioni schermo 
 * @param indice indica l'indice della navicella
*/
Coordinate coordinateIniziali(int indice)
{
    Coordinate defaultpos;  //posizione di default

    int i;  

    i = indice / MAX_NAV_COL;
    defaultpos.x = MAXX- (NAV2_SPESSORE * 2) * (i + BORDO);
    i = indice % MAX_NAV_COL;
    defaultpos.y = 8 + ((MAXY / 4) * i);

    return defaultpos;
}

/**
 * Procedura che gestisce l'inizializzazione del missile nemico in una posizione iniziale start e il suo avanzamento
 * @param indice indica l'indice della navicella
*/
void *missileNemico (void* start)
{
    int i;
    Object missile;

    missile.pos.x = ((Coordinate*)start)->x - NAV_SPESSORE - 1;
    missile.pos.y = ((Coordinate*)start)->y + NAV_ALTEZZA / 2;
    missile.id = ID_MISSILE_NAVICELLA;
    missile.pid = pthread_self(); //identificativo
    missile.vite = 1;

//il missile avanza dinchè le vite sono maggiori di 0
    while (missile.vite > 0)
    {
        missile.old_pos = missile.pos;
        missile.pos.x --;
        usleep(MISSILE_DELAY);
        insert(missile); //inserisce missile nel buffer
    }
   
}

/**
 * Procedura che gestisce i movimenti dell'astronave e la creazione dei missili navicella
*/
void *nemico(void *args)
{
    pthread_t thread_missile;

    int status;
    Object navicellaLev1; //nemico

    int indice=((Object*)args)->indice; //indice

    navicellaLev1.pos = coordinateIniziali(indice); //coordinate iniziali navicella
    navicellaLev1.old_pos = navicellaLev1.pos;
    navicellaLev1.pid = pthread_self();
    navicellaLev1.id = ID_NAVLEV1;
    navicellaLev1.indice =indice; //indice navicella
    

    do {
 
        navicellaLev1.old_pos = navicellaLev1.pos; //vecchia posizione
	    usleep(100000);
         switch (movimento) {
            case 0:  //verso l'alto
	            usleep(100000);
                navicellaLev1.pos.y-=3;
		        movimento=1;	
			    break;

            case 1: //verso il basso
	            usleep(100000);
                navicellaLev1.pos.y+=3;
		        movimento=3;           
                break;

            case 2: //solo in avanti
	            usleep(100000);
                navicellaLev1.pos.x-=4;
		        movimento=0;
                break;

    	    case 3: // in avanti
	            usleep(100000);
			    navicellaLev1.pos.x-=4;
	   		    movimento=4;	
		        break;
	
            case 4: //verso il basso
	            usleep(100000);
    	        navicellaLev1.pos.y+=3;
		        movimento=5;
                break;	

	          case 5: //verso l'alto
	            usleep(100000);
		        navicellaLev1.pos.y-=3;
		        movimento=2;	
		        break;	
        }

        // Generazione missili
        if ((rand() - navicellaLev1.indice) % 5 == 0) {
            pthread_create(&thread_missile, NULL, &missileNemico,  &navicellaLev1.pos);

        }
     
       //inserisco la navicella nel buffer
        insert(navicellaLev1);
        usleep(NAV_DELAY);
  
    } while (true);
}



