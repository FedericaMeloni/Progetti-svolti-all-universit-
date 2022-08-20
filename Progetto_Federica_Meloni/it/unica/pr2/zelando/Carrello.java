package it.unica.pr2.zelando;

import java.util.*;

//carrello è un estensione di ArrayList e contiene oggetti Prodotto
public class Carrello extends ArrayList<Prodotto> {

   
   public Carrello(Prodotto[] arrayProdotti) {
      for(Prodotto prodotto: arrayProdotti){ //alla creazione di carrello vengono inseriti i prodotti in esso
        this.add(prodotto);
      }
   }
   
   public double costo() { //ritorna la somma dei prezzi dei prodotti del carrello
        double somma = 0.0;
        for(Prodotto prodotto: this) {
             somma += prodotto.prezzo();
        }
        return somma;
        
   }
   
   public int nProdotti() { //ritorna la taglia del carrello
        return this.size();
   }


   //ritorna la somma dei prezzi dei prodotti del carrello se sono ProdottiDonna
   public int nProdottiDonna() {
       int somma = 0;
       for(Prodotto prodotto: this) {
            if (prodotto instanceof ProdottoDonna)
             somma += 1;
       }
       return somma;
   }

   //ritorna la somma dei prezzi dei prodotti del carrello se sono ProdottiUomo
   public int nProdottiUomo() {
       int somma = 0;
       for(Prodotto prodotto: this) {
            if (prodotto instanceof ProdottoUomo)
             somma += 1;
       }
       return somma;
   }

   //crea una lista di prodotti donna
   public List<ProdottoDonna> prodottiDonna() {
       List<ProdottoDonna> prodottiDonna = new ArrayList<>();

       //inseriamo i prodotti di Carrelo in prodottiDonna solo se sono istanza di ProdottoDonna
       for(Prodotto prodotto: this) {
            if (prodotto instanceof ProdottoDonna)
             prodottiDonna.add((ProdottoDonna) prodotto);
       }
       return prodottiDonna;
   }
   
   //riceve una lista e viene ritornato un carrello con quegli oggetti
   public static Carrello fromList(List<? extends Prodotto> l) {
        Carrello c = new Carrello(new Prodotto[]{});
        c.addAll(l); //aggiunge tutto il contenuto di l nel carrello
 
        return c; //ritorna il nuovo carrello
        
   }
   
  // date delle parole chiave contenute nel parametro query mette in un carrello tutte le merci che le possiedono nella descrizione
   public Carrello nProdotti(String query) {
        Carrello result = new Carrello(new Prodotto[]{});
        for(Prodotto p : this) { //fa scorrere i prodotti contenuti nel carrello
            if(match(p.descrizione(),query)) { //match ritorna vero se la descrizione del prodotto contiene le parole chiave
                result.add(p); //il prodotto viene inserito nel carrello
            }
            
        }
               
        return result;//ritorna il nuovo carrello
   }
   
//controlla che la descrizione contenga le parole inserite contenute dal parametro query
   private static boolean match(String descrizione, String query) {
        for(String q : query.split(" ")) {//elimina lo spazio e fa scorrere i caratteri
            if (!descrizione.contains(q)) {
                return false; //se il carattere non è contenuto si interrompe
            }
        }
        return true; //tutti i caratteri corrispondono
   }

}
