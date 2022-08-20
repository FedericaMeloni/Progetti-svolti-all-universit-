package it.unica.pr2.zelando;

//la classe prodotto definisce un prodotto con descrizione e prezzo
public class Prodotto {
    private String descrizioneProdotto;
    private double prezzo;

    Prodotto(String descrizione, double prezzo) {
        if(descrizione!= null) //se la descrizione non viene inserita viene lanciato un errore
            this.descrizioneProdotto = descrizione;
        else 
            throw new RuntimeException("descrizione non valida");
            
        this.prezzo = prezzo;
    }
    
    //ritorna descrizione del prodotto
    public String descrizione() {
        return this.descrizioneProdotto;
        
    }
    
    //ritorna prezzo del prodotto	
    public double prezzo() {
        return this.prezzo;
    }
}
