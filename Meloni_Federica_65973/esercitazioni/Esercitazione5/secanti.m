function [x,k]=secanti(fun,x0,x1,tol,kmax)

% I parametri della funzione sono:
%       x0 -> punto iniziale 
%       x1 -> punto iniziale
%       fun -> funzione di cui valutare uno zero
%       tolx -> tolleranza per la radice
%       kmax -> limite superiore al numero di iterazioni
%
%   I valori di ritorno sono:
%       x -> la soluzione trovata
%       k -> il numero di iterazioni impiegate per ottenere la soluzione
%       

flag = 1;% indicatore di arresto per il ciclo while
k = 1; %numero di iterazioni

%calcolo funzioni nei due punti iniziali
new_x0 =fun(x0); 
new_x1 = fun(x1);

%variabile che ospiterà il risultato, verrà aggiornata ad ogni while
x_new =((x0*new_x1)-(x1*new_x0)) / (new_x1-new_x0); 


while flag %flag è un indicatore d'arresto
    k = k+1;
    x0=x1;
    x1 = x_new; %aggiornamento punti di partenza

    %calcolo le funzioni nei nuovi punti  x1 e x0 appena aggiornati
    new_x0 = new_x1; %valore della funzione in x1
    new_x1 = fun(x1);
    
 
    x_new = ((x0*new_x1)-(x1*new_x0)) / (new_x1-new_x0);  %risultato dell'iterazione
  
    %condizioni per proseguire il ciclo altrimenti il ciclo viene terminato
    flag =  (abs(x_new-x0) > tol*abs(x0) && (k<kmax) && (abs(fun(x_new)) >1e-10));
end

if (k>=kmax) %numero massimo di iterazioni raggiunto
    warning('N. massimo di iterazioni raggiunto');
    x = inf;
else
    x = x_new;
end
    
