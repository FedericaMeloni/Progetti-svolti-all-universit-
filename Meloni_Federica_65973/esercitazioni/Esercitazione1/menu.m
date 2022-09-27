%l'utende inserisce un numero
n= input('inserisci il numero di un ordine del menù [1-4]: \n');

%viene stampato il piatto corrispondente a quel numero oppure un messaggio
%di avviso per i numeri a cui non corrisponde un piatto
switch n
    case 1
        disp('Spaghetti 158 cal')
    case 2
        disp('Minestra 34 cal')

    case 3
        disp('Pizza 261 cal')

    case 4
        disp('Bistecca 271 cal')

    otherwise
        disp('Non hai selezionato nessun piatto');
end