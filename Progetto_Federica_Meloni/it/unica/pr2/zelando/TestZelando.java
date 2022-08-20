package it.unica.pr2.zelando;

import java.util.List;

public class TestZelando {

 
    public static void main(String[] args) {
        // TODO code application logic here

    	
        
        Prodotto p1 = new MagliettaUomo("M", "rosso", 55.50); // taglia, colore/descrizione, prezzo

        Prodotto p2 = new Gonna("S", "verde a righe", 34.90);
        Prodotto p3 = new ScarpaDonna(37, "stivaletto in pelle", 62.80);

        Carrello c = new Carrello(new Prodotto[]{p1, p2, p3});

        assert c instanceof Carrello;
        assert c.get(0) == p1;

        
        assert c.get(2).descrizione().equals("stivaletto in pelle");

        
        assert c.costo() == p1.prezzo() + p2.prezzo() + p3.prezzo();

        assert p1 instanceof ProdottoUomo;
        assert p2 instanceof ProdottoDonna;

        assert c.nProdottiDonna() == 2;
        assert c.nProdottiUomo() == 1;
        assert c.nProdotti() == 3;

        List<ProdottoDonna> l = c.prodottiDonna();
        assert l.size() == 2; // l contiene i prodotti per donna

      
        Carrello c2 = Carrello.fromList(l); // must work with any descendant of Prodotto 

        c2 = c.nProdotti("pelle stivaletto"); // ricerca per testo
        assert c2.size() == 1;
        assert c2.get(0) == p3;
        
        System.out.print("Tutti gli assert sono stati superati");

    }

}

