
#include "macro.h"

/**
 * Procedura inserisce l'Object item nel buffer
*/
void insert(Object item){

	//aspetta finchè non c'è uno slot vuoto
	sem_wait(&vuoto);
	pthread_mutex_lock(&mutex);	/*Blocco mutex*/
	
	buffer[contatore]=item; //inserisce
	contatore++; //aggiorno contatore
		
	pthread_mutex_unlock(&mutex);	/*Sblocco mutex*/
	sem_post(&pieno); //incrementa il semaforo

}

/**
 * Procedura che estrae l'Object item dal buffer
*/
Object extract(){

	Object item;

	sem_wait(&pieno); //aspetta finchè non c'è uno slot pieno nel buffer
	pthread_mutex_lock(&mutex);	/*Blocco mutex*/

	item = buffer[contatore-1];
	contatore--; //aggiorno contatore

	pthread_mutex_unlock(&mutex);	/*Sblocco mutex*/
	sem_post(&vuoto); //incrementiamo il semafoto vuoto

	return item; /*Ritorna l'oggetto*/
}
